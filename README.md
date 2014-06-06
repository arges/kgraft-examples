kgraft-examples
---------------

A way to build the kgraft samples easily and additional scripts.

Install anything you need to build a kernel module.
Then type `make`.

Insert the module:
`sudo insmod kgraft_patcher.ko`

Check dmesg, and you'll need to wait for everything to converge.

If you are impatient you can use the hurryup.sh script.

Tested on Ubuntu Utopic with the following build:
http://people.canonical.com/~arges/kgraft-utopic/

Git tree for kernel sources here:
http://zinc.ubuntu.com/git?p=arges/ubuntu-utopic.git;a=shortlog;h=refs/heads/kgraft-utopic

Original sources here:
https://git.kernel.org/cgit/linux/kernel/git/jirislaby/kgraft.git/

Thanks to Jiri for his help via email on getting this working.
