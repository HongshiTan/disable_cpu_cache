#include <linux/init.h>
#include <linux/module.h>
#include <asm/smap.h>
#include <linux/smp.h>

MODULE_LICENSE("Dual BSD/GPL");


static void disable_cache(void * arg)
{
    int cpuid = smp_processor_id();
    printk(KERN_ALERT "Disabling L1 and L2 caches on CPU %d.\n", cpuid);
    stac();
    barrier_nospec();
    write_cr0(read_cr0() | (1 << 30));
    printk(KERN_ALERT "CPU %d cr0 0x%32lx\n",cpuid, read_cr0());
    __asm__(".att_syntax noprefix\n\t"
            "wbinvd\n\t");
    clac();
    return;
}

static void enable_cache(void * arg)
{
    int cpuid = smp_processor_id();
    printk(KERN_ALERT "Enabling L1 and L2 caches on CPU %d.\n", cpuid);
    stac();
    barrier_nospec();
    write_cr0(read_cr0() & (~(1 << 30)));
    __asm__(".att_syntax noprefix\n\t"
            "wbinvd\n\t");
    printk(KERN_ALERT "CPU %d cr0 0x%32lx\n",cpuid, read_cr0());
    clac();
    return;
}

static int disable_cache_init(void)
{
    disable_cache(NULL);
    // all cpus need to execute
    smp_call_function(disable_cache,NULL,1);
    return 0;
}
static void disable_cache_exit(void)
{
    enable_cache(NULL);
    smp_call_function(enable_cache,NULL,1);
    return;

}
module_init(disable_cache_init);
module_exit(disable_cache_exit);