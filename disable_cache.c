#include <linux/init.h>
#include <linux/module.h>
#include <asm/smap.h>
MODULE_LICENSE("Dual BSD/GPL");
static int disable_cache_init(void)
{

        printk(KERN_ALERT "Disabling L1 and L2 caches.\n");
        stac();
        barrier_nospec();
        __asm__(".att_syntax noprefix\n\t"
                "movq    cr0,rax\n\t"
                "or      (1 << 30),rax\n\t"
                "movq    rax,cr0\n\t"
                "wbinvd\n\t"
                ".att_syntax noprefix\n\t"
        : : : "rax" );
        clac();
        return 0;
}
static void disable_cache_exit(void)
{

        printk(KERN_ALERT "Enabling L1 and L2 caches.\n");
        stac();
        barrier_nospec();
        __asm__(".att_syntax noprefix\n\t"
                "movq    cr0,rax\n\t"
                "and     (~(1 << 30)),rax\n\t"
                "movq    rax,cr0\n\t"
                "wbinvd\n\t"
                ".att_syntax noprefix\n\t"
        : : : "rax" );
        clac();
}
module_init(disable_cache_init);
module_exit(disable_cache_exit);