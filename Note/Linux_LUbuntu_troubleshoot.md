# Troubleshoot LUbuntu after installed
- Booting
    - [OS reboot display white black terminal]
- Missing driver
    - [Auto find missing driver](#2-using-default-check-driver-software-additionnal-drivers)
- Internet
    - [Wifi connect faied](#wifi-connect-faied)
    - [Internet connected but can't browse DNS](#internet-connected-but-cant-browse-some-webpage)
- Keyboard
    - [Missing Vietnamese]
    - [Touchpad tap-to-click fail](#1-touchpad-tap-to-click-fail)


## Internet connect faied

### 1. Missing Broadcom wireless driver
- Firt try `lspci | grep -i network` to check exist a Network module
    ```bash
    lspci | grep -i network
    
    -> Network controller: Broadcom Inc. and subsidiaries BCM43142 802.11bgn (rev 01)
    ```
- If network card interface exist like above try connect: Ethernet cable or a USB wifi 
- Now in `terminal` download:
    ```bash
    sudo apt update # fetch newest app list
    
    sudo apt install bcmwl-kernel-source
    ```
- After that, remove cable, usb then `reboot`

### 2. Using default check driver software `Additionnal Drivers`
- It can find on `Search bar` but if not exist:
    ``` bash
    sudo apt update
    sudo apt install software-properties-gtk
    ```
- Then check by tab `Additional Drivers`, install driver by list suggested

## Internet connected but can't browse some webpage
### 1. Missing register a DNS server
- Right click on `wifi` on the right down, `Edit connection`
- In `Connection interface` of current Wifi connected the setup IPv4 settings:
    - Field `Additional DNS server` input:
    ```txt
    8.8.8.8, 1.1.1.1
    ```
- After update ip of Google, Cloudflare then Save
- Try connect to webpage


## Keyboard troubleshoot
### 1. Touchpad tap-to-click fail
s
