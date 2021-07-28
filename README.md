# Linux Kernel Module for Disabling Intel's CPU Caches

Disable all the intel's cpu caches (L1, L2 and L3)
* Temporarily disable the supervisor mode access prevention, so that it can work with Linux kernel 5.0+.
* The operation on CR0 is executed on all smp cores. 

## How to Use?

### to disable cache

``` shell
# install linux header files
sudo apt install linux-headers-$(uname -r)

# clone code
git clone git@github.com:HongshiTan/disable_cache.git

# compile the kernel module
cd disable_cache
make

# install the module
sudo insmod disable_cache.ko
```

### to re-enable cache

``` shell
sudo rmmod disable_cache
# I would suggest to reboot the computer.
# Disabling the cache would have influence on interrupt handling and make the critical phase much longer.
```
## Reference
[How can the L1, L2, L3 CPU caches be turned off on modern x86/amd64 chips?](https://stackoverflow.com/questions/48360238/how-can-the-l1-l2-l3-cpu-caches-be-turned-off-on-modern-x86-amd64-chips)
