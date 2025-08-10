## References (man 1,4,5,7,8)
- [file-hierarchy(7) — Linux manual page](https://man7.org/linux/man-pages/man7/file-hierarchy.7.html)
    - [Note](#file-hierarchy)
        - [Filesystem kernel support /proc/filesystems](#procfilesystems)
- [filesystems(5) — Linux manual page](https://man7.org/linux/man-pages/man5/filesystems.5.html)
    - [Note](#file-system)

    
#### File system
- [filesystems(5) — Linux manual page](https://man7.org/linux/man-pages/man5/filesystems.5.html)
- The file system can devided into 3 types:
    - Long-term filesystem: File is real and keep in hard drive like HDD, SSD, USB, SD.
        - Common as: EXT4 (EXT3, EXT2,...), FAT32, NTFS, ...
    - Short-term filesystem: File is real and keep in RAM
        - Sometime it called  `tmpfs`
        - It very useful when some program generate file for use in short term like games, latex pdf preview, ...
            - Advantage than `long-term`: handle problem write life cycle of hard drive; access, generate file faster.
            - Disadvantage obvious that RAM is quite small and has to predict how many RAM should allocate for project.
                - Another thing is lost file when shutdown PC.
    - Pseudo filesystem: File only generate when be required
        - Some file system like: `/proc`(procfs), `/sys`(sysfs), `/dev`(devtmpfs), ...
- Common file systems:
    - minix: the file system using the first time run Linux. Maximum partition size is 64MB.
    - ext1, ext2, ext3, ext4: 
        - `ext` (extended filesystem) is an elaborate extension of the minix filesystem. Partition size upto GB but has been removed from the kernel (in Linux 2.1.21)
        - `ext2` the second extended filesystem was designed as an extension `ext`. Upto 2TB
        - `ext3` = `ext2` + `journaling` help system fast recover after trouble. Backward compatibility with `ext2`
        -  `ext4` is a set of upgrades to ext3 including substantial performance and reliability enhancements, plus large increases in volume, file, and directory size limits. Backward compatibility with `ext2`, `ext3`.
    - `msdos`, `vfat`, `fat32`: file system on Window, vfat = fat32/16 (8.3 filename) + longer filename.
    - `iso9660`
    - `tmpfs`
    - `pseudo filesystems`, something else: `/proc` (process and system status), `/sys` (config device and kernel runtime), `/dev` (connect to devices are attached)
    - ... other network filesystem

##### /proc/filesystems
```bash
cat  /proc/filesystems

# nodev (nodive) == virtual filesystem
nodev   sysfs  # 
nodev   tmpfs
nodev   bdev
nodev   proc
nodev   cgroup
nodev   cgroup2
nodev   devtmpfs
nodev   configfs
nodev   debugfs
nodev   tracefs
nodev   securityfs
nodev   sockfs
nodev   bpf
nodev   pipefs
nodev   ramfs
nodev   hugetlbfs
nodev   devpts
        ext3
        ext2
        ext4
        squashfs
        vfat
nodev   ecryptfs
        fuseblk
nodev   fuse
nodev   fusectl
nodev   efivarfs
nodev   mqueue
nodev   pstore
        btrfs
nodev   autofs
nodev   binfmt_misc

```

#### File hierarchy

General structure of root `/`, only root has permission:
|folder | purpose|
|-|-|
|/boot, /efi | These sometime a boot partitions kernel spend for bootloader Legacy mode or UEFI mode put config file and call back boot program|
|/etc|  System-specific configuration, application can be design to put config file here but should fall back to defaults if configuration is missing |
|/home| The location contain user's home directory, each user has permiss to asscess them home folder and can't access another users home if not in them group|
|/root| `root` file folder, only for unique root user|
|/srv| The place to store general server payload |
|/tmp| Place small temporary files and this usually mount add a `tmpfs`live on RAM, and . The file has to small because `/tmp` is limited (default RAM storage / 2). Also, files that are not accessed within a certain time may be automatically deleted. |
|/run|A "tmpfs" file system for system packages to place runtime data, socket files, and similar. This directory is flushed on boot|
|/run/log/|Runtime system logs. System components may place private logs in this directory.|
|/run/user/|Contains per-user runtime directories, each usually individually mounted "tmpfs" instances. Always writable, flushed at each reboot and when the user logs out.|
|||
|||
