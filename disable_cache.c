#include <linux/init.h>
#include <linux/module.h>
#include <asm/smap.h>
MODULE_LICENSE("Dual BSD/GPL");
static int disable_cache_init(void)
{
        printk(KERN_ALERT "Disabling L1 and L2 caches.\n");
        stac();
        barrier_nospec();
        write_cr0(read_cr0() | (1 << 30));
        printk(KERN_ALERT "cr0 0x%32lx\n",read_cr0());
        __asm__(".att_syntax noprefix\n\t"
                "wbinvd\n\t");
        clac();
        return 0;
}
static void disable_cache_exit(void)
{

        printk(KERN_ALERT "Enabling L1 and L2 caches.\n");
        stac();
        barrier_nospec();
        write_cr0(read_cr0() & (~(1 << 30)));
        __asm__(".att_syntax noprefix\n\t"
                "wbinvd\n\t");
        printk(KERN_ALERT "cr0 0x%32lx\n",read_cr0());
        clac();
}
module_init(disable_cache_init);
module_exit(disable_cache_exit);