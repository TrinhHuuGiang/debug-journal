- Refer: https://stackoverflow.com/questions/139261/how-to-create-a-file-with-a-given-size-in-linux

Some time RAM, SWAP file, SWAP partition are run out of. 
- RAM and partition can't be easily expanded

The solution is expand SWAP file
1. check swapfile is using or exist in management:
    - Check `/swapfile` status:
        ```bash
            swapon -v
                # this comman return verbose mode of enable swap object
            NAME           TYPE      SIZE USED PRIO
            /dev/nvme0n1p1 partition   2G   0B   -2
        ```
        - Here can see `swapfile` not enable, only have 2GB swap from partition
    - Check `/swapfile` exist or enable:
        ``` bash
            # 1. check root
            ls /
                # swapfile has to exist here or was deleted by user


            # 2. check in config file system table
            cat /etc/fstab
                # the below line should exist here or is deleted or commented by user
            #/swapfile   swap    swap    defaults   0 0
        ```
        - Here can see `swapfile` is comment by user to disable auto bind it at reboot
2. Disable and check exist `swapfile` before modify it
    - command `sudo swapoff /swapfile`
        ```bash
            # if it on -> off success

            # if it off
            sudo swapoff /swapfile
                # warn not exist
            swapoff: /swapfile: swapoff failed: Invalid argument
        ```
    - check sure it exist in `/etc/fstab`:
        - if not exist of comment line `/swapfile   swap    swap    defaults   0 0`
            - write or uncomment it

3. Some method modify `swapfile` size:
    1. Legacy method using `dd` to write into `/swapfile` to expand or minimize it
        - `sudo dd if=/dev/zero of=/swapfile bs=1M count=4096`
            - if: input file
            - /dev/zero: virtual file stream `full zero`
            - of: output file
            - /swapfile: auto make swap file or overwrite on it
            - bs: block size each time write on file
            - count: time write to file
                - example: `writesize = bs*count = 4GB` -> real write to file
                - if `input size` < `writesize` -> write = input size
                    - the `/dev/zero` is unlimited size
                - if `output size` < `writesize` -> dd truncate it
                - if `output size` > `writesize` -> dd write to expand it
        - now format new metadata swapsize and type swap
            ```bash
                # sudo read / write
                sudo chmod 600 /swapfile
                # sudo make swap
                sudo mkswap /swapfile
            ```
        - now `sudo swapon /swapsize` to enable swap file
    2. Modern method `fallocate`, this save, only alloc, don't write to file (faster and safer harddrive).
        ```bash
            sudo swapoff /swapfile

            # realloc swap file
            sudo fallocate -l 6G /swapfile
                # -l is length in Byte, see in --help
                #   maybe G (GiB), T (TiB), ...
            
            #format swap file
            sudo chmod 600 /swapfile
            sudo mkswap /swapfile
            sudo swapon /swapfile
        ```