# Linux Kernel Module for Disable CPU Cache

Disable all the cpu cache (L1, L2 and L3)

## How to Use?

### to disable cache
``` shell
make
sudo insmod disable_cache.ko
```

### to re-enable cache

``` shell
sudo rmmod disable_cache
# I would suggest reboot the computer
```