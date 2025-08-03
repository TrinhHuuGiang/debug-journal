# Content
- [Install virtualbox]
- [Compare with other duplicate machine solution]

# Install
- virtual box: https://www.virtualbox.org/wiki/Linux_Downloads
```bash
sudo apt update
sudo apt install virtualbox
```
## Basic setup virtual machine
- Download `.iso` of OS then choose tab `New` in virtual box GUI
    - Or we con choose a `Virtual machine` are available when choose `Type` of OS then Virtual box suggest them versions are available
- Setup hardware pre install VM:
    - Base memory, numer processor: Accept about 25 - 50% resources
        - Example: 8GB ram -> accept 2GB - 4GB (main OS has 4GB rest to running)
        - numer processor: 4 core -> 1-2 core
    - Harddisk:
        - Depend on purpose size hardisk create maybe = `OS iso size` + `purpose`
            - If tick `Pre-allocate Full Size`, size will dynamic increase at runtime but still limit by setup size hardisk
## After install VM, try `Settings` to register hardware with main OS
### 1. tab `Network`:
- NAT using the same ip with main OS when connect internet but register by OS an virtual IP  
help distinguish whose package
- Bridged Adapter, VM give new IP from network differ from main OS IP
- Other solution: Host-Only Adapter, Internal Network,...
### 2. tab `Serial port`
### 3. tab `USB`

### 4. tab `Shared folder`
#### VM is a linux
-[youtube](https://www.youtube.com/watch?v=h_adwDledYM)


#### VM with window



# Error log
## 1. VirtualBox can't operate in VMX root mode. 
- [refer turn of KVM](https://askubuntu.com/questions/373469/how-to-disable-kvm-for-installing-vmware-player)

```bash
VirtualBox can't operate in VMX root mode. Please disable the KVM kernel extension, recompile your kernel and reboot (VERR_VMX_IN_VMX_ROOT_MODE).
```
- KVM (Kernel-based Virtual Machine) is the default built-in virtualization technology for Linux Kerel for some VMs like `qemu`,...

- Solution turn of `KVM` on short term:
    ```bash
    lsmod | grep kvm

    # return 
    kvm_intel             487424  0              # remove it first
    kvm_amd # if use amd it have this form
    kvm                  1425408  1 kvm_intel    # remove kvm

    # short-term remove, reboot auto on
    # longterm we need write it to a `blacklist` file of `modprobe`
    sudo rmmod kvm_intel  # if CPU Intel  or using `sudo modprobe -r kvm_intel`  
    # sudo rmmod kvm_amd    # if CPU AMD
    sudo rmmod kvm
    ```
- Turn on if return using KVM
```bash
sudo modprobe kvm_intel
```




# Compare with wine, docker, dual OS
## wine

## Docker


## Dual OS


# How to install

