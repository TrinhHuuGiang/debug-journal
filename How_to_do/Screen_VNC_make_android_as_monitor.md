Note:
- **To make android as a monitor for linux we need `VNC Viewer`**
- **To connect to android, linux need `VNC Server`**
  - x11vnc : if wanna share to others and work on current destop
  - tigervnc: if wanna create new desktop server independence with main desktop
  - realvnc (ignore server): suitable for client, complicated when implement on server 
Topic:
- [Android viewer](#android-side)
- [Linux server](#linux-side)
- [Run server](#run-a-server)
  

# 1. Android side
- Download: VNC Viewer version 3.6.1.42089 by `RealVNC` available for android higher 4.4
  - [link to download at Uptodown.com](https://vnc-viewer.en.uptodown.com/android/download/1049524381)

# 2. Linux side
- Download: `x11vnc` see: https://wiki.archlinux.org/title/X11vnc
1. install
  ```bash
    # menu application
    sudo apt update

    # install
    sudo apt install x11vnc
  ```
2. run simple server
  ```bash
    # normal desktop :0 , no authen, only share
    # port default 5900, run foreground and has kill by Ctrl + C or process manager
    x11vnc

    # optional if have a tigervnc server or some vnc server created a virtual destop
    x11vnc -display :1 # if another virtual desktop has code :1
                        # port = 5900 + desktop number = 5901
  ```
- Warning from `Arch`:  
*This will set up the VNC server with no authentication password. This means that anybody who has access to the computer's network can see and control your X session. You can simply set a password, as described below.*

3. Connect to server tips:
- Can config network static ip to easy finds server

4. Authen and accept interract (comming soon)

   

# 3. Other sharing VNC
### Tiger VNC (comming soon)
- TigerVNC open source and support create and share new session, independence with working monitor. It useful for other user use remote monitor but not interract with main monitor.
- Dowload: 2025 version 1.15
  - [link to download VNC server](https://sourceforge.net/projects/tigervnc/files/stable/1.15.0/)
  - [link to download source code `tar.gz` at Github](https://github.com/TigerVNC/tigervnc/releases/tag/v1.15.0)
1. Install `deb` for `ubuntu-20.04LTS / amd64`:
  - other Linux check : `cat /etc/os-release`
  - download: [tigervncserver_1.15.0-1ubuntu1_amd64.deb](https://sourceforge.net/projects/tigervnc/files/stable/1.15.0/ubuntu-20.04LTS/amd64/)
    - it about 1.3MB
  - in download copy to expected folder and do:
    ```bash
      # cp to expected folder
      cp ./tigervncserver_1.15.0-1ubuntu1_amd64.deb [link to save folder]
      cd [ save folder ]
  
      # install
      sudo dpkg -i ./tigervncserver_1.15.0-1ubuntu1_amd64.deb

      # if missing dependencies check and install them
      sudo apt-get install -f

      # reinstall
      sudo dpkg -i ./tigervncserver_1.15.0-1ubuntu1_amd64.deb
    ```
2. Install by `apt` - Recommend if missing dependecies package
```bash
  # get newest package list
  sudo apt update

  # find tiger vnc
  apt list | grep -in  tigervnc
    
    WARNING: apt does not have a stable CLI interface. Use with caution in scripts.
    
    105106:tigervnc-common/jammy-updates,jammy-security 1.12.0+dfsg-4ubuntu0.22.04.1 amd64
    105107:tigervnc-scraping-server/jammy-updates,jammy-security 1.12.0+dfsg-4ubuntu0.22.04.1 amd64
    105108:tigervnc-standalone-server/jammy-updates,jammy-security 1.12.0+dfsg-4ubuntu0.22.04.1 amd64
    105109:tigervnc-tools/jammy-updates,jammy-security 1.12.0+dfsg-4ubuntu0.22.04.1 amd64
    105110:tigervnc-viewer/jammy-updates,jammy-security 1.12.0+dfsg-4ubuntu0.22.04.1 amd64
    105111:tigervnc-xorg-extension/jammy-updates,jammy-security 1.12.0+dfsg-4ubuntu0.22.04.1 amd64
    105112:tigervncserver/now 1.15.0-1ubuntu1 amd64 [residual-config]

  # install tigervnc-standalone-server
  sudo apt install tigervnc-standalone-server

  ## ok now we find new apps
  vncconfig   vncpasswd   vncserver   vncsession  

```

3. Run a server
- `vncpassword`
  - Alway setup password for vnc sesstion, else when `vncserver`  is creating still need input a password
  ```bash
    vncpassword
  
    # then input password and authen
  ```
  - we can recall above script to reset password
---
- `vncserver`
  - Note: Viewer now only see and interract with black screen will be created by server.
  - After set password, run server:
  - Run `vncserver -localhost no` to create a server connect to any netword (if yes this only connect to loopback 127.0.0.1), and a `:servernumber` will represent for this server
    - Port `5900 + servernumber` will auto open to share server screen
  - Run `vncserver -list` to check list of server and port, by default pỏt
  - Run kill a server `vncserver -kill :servernumber`, `servernumber` by default order 1, 2 ,3 ...
---
- Last one, implement UI for this session: :( may be comming soon

### RealVNC
- The RealVNC server need free licenses for offline but waste time to set up so i ignore it
