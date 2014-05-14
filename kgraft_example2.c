#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kgraft.h>
#include <linux/kallsyms.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/capability.h>
#include <linux/ptrace.h>

#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/time.h>
#include <linux/kernel_stat.h>
#include <linux/cputime.h>

static int new_uptime_proc_show(struct seq_file *m, void *v)
{
        struct timespec uptime;
        struct timespec idle;
        u64 idletime;
        u64 nsec;
        u32 rem;
        int i;

        idletime = 0;
        for_each_possible_cpu(i)
                idletime += (__force u64) kcpustat_cpu(i).cpustat[CPUTIME_IDLE];

        get_monotonic_boottime(&uptime);
        nsec = cputime64_to_jiffies64(idletime) * TICK_NSEC;
        idle.tv_sec = div_u64_rem(nsec, NSEC_PER_SEC, &rem);
        idle.tv_nsec = rem;
        seq_printf(m, "%lu.%02lu %lu.%02lu\n",
                        (unsigned long) uptime.tv_sec,
                        (uptime.tv_nsec / (NSEC_PER_SEC / 100)),
                        (unsigned long) idle.tv_sec,
                        (idle.tv_nsec / (NSEC_PER_SEC / 100)));
        
	printk(KERN_DEBUG "Check out that uptime!\n");
        return 0;
}
KGR_PATCHED_FUNCTION(patch, uptime_proc_show, new_uptime_proc_show);

static struct kgr_patch patch = {
	.patches = {
		KGR_PATCH(uptime_proc_show),
		KGR_PATCH_END
	}
};
static int __init kgr_patcher_init(void)
{
        /* removing not supported (yet?) */
        __module_get(THIS_MODULE);
        /* +4 to skip push rbb / mov rsp,rbp prologue */
        kgr_start_patching(&patch);
        return 0;
}

static void __exit kgr_patcher_cleanup(void)
{
        printk(KERN_ERR "removing now buggy!\n");
}

module_init(kgr_patcher_init);
module_exit(kgr_patcher_cleanup);

MODULE_LICENSE("GPL");
