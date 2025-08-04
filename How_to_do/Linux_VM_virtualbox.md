# Content
- [Install virtualbox]
- [Compare with other duplicate machine solution]

# Install
- virtual box: https://www.virtualbox.org/wiki/Linux_Downloads
- virtual box extension pack:
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
- NAT or `Network Address Translation` is the default mode and is suitable for most users who need to browse the internet from their VM. In this mode, the VM is assigned a `private IP` address `within a virtual network` created by VirtualBox. The host OS acts as a router, translating the VM's network traffic so it appears to originate from the host's IP address. This allows the VM to access the internet and the host's local network. 
    - However, devices on the external network cannot directly access the VM unless you configure Port Forwarding on both `Home router` and `Virtual box`. It is normal because now VM acts as a server.

---
- `Bridged Adapter` 
    - The VM will obtain its own IP address from your network's DHCP server (usually your router), making it a peer on the network. This mode is ideal for running servers within the VM, as it allows other devices on the network to access it directly via its own IP address (Still need port forward it acts as a server).

---
- `Host-only adapter` This mode creates `a private network `between `the host` machine `and the VM`. The VM and the host can communicate with each other using `virtual IP addresses` assigned within this `private network`. This mode is perfect for scenarios where you need to `isolate the VM from the internet` and the external network while still allowing communication with the host. It does not require an active Wi-Fi or Ethernet connection on the host.
    - Very useful and easy setup in private share file beetween 2 host OS and VM by `scp`, `sftp`, or `ssh`

---
- Internal Network
    - This mode creates a completely isolated virtual network that exists only between VMs connected to it. The VMs can communicate with each other, but they are completely cut off from the host machine and any external networks. This is the ideal mode for setting up secure and isolated test environments, such as a multi-tier web application or a penetration testing lab.


### 2. tab `Serial port`

### 3. tab `USB`
- Refer: https://www.youtube.com/watch?v=h-EOHbVqsJg

- Here we need install `Virtualbox extension pack` otherwise default can't connect usb.
    ```bash
    virtualbox --help

    # my version is 7.0.16 Ubuntu
    Oracle VM VirtualBox VM Selector v7.0.16_Ubuntu
    Copyright (C) 2005-2024 Oracle and/or its affiliates

    No special options.

    If you are looking for --startvm and related options, you need to use VirtualBoxVM.
    ```
- Find extension is suitable with virtualbox current version on internet.
    - Example here is 7.0.16: https://download.virtualbox.org/virtualbox/7.0.16/
    - Note if web facing with error like this:
    ![error download](../Some_bugs/Linux_Lubuntu_24_04/img/error_down_extension)
    - Solution is `save this page as` when right click on link 
    - Now go to `Virtual Box` -> `File` -> `Tools`-> `Extension package manager`
        - Add the file downloaded
        - Open `Terminal` then add current user to group `vboxusers` otherwise can't choose usb port.
        ```bash
        sudo adduser $USER vboxusers #add user to vbox group. 
        # Delete out group: sudo gpasswd -d $USER vboxusers
        # Check group: groups $USER

        sudo reboot # next session will valid 
        ```
        - After reboot, connect your usb device
        - Then go to Settings for `Virtual machine` want install usb, choose type of usb driver exist, Save then Run

### 4. tab `Shared folder`
#### VM is a linux
-[youtube](https://www.youtube.com/watch?v=h_adwDledYM)

#### VM with window
- The same on youtube

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

