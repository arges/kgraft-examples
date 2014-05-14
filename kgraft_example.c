#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kgraft.h>
#include <linux/kallsyms.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/capability.h>
#include <linux/ptrace.h>

static bool new_capable(int cap)
{
        printk(KERN_DEBUG "Calling the new capable!\n");
        return ns_capable(&init_user_ns, cap);
}
KGR_PATCHED_FUNCTION(patch, capable, new_capable);

static struct kgr_patch patch = {
	.patches = {
		KGR_PATCH(capable),
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
