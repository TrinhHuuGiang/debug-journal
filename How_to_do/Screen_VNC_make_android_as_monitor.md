Note:
- **To make android as a monitor for linux we need `VNC Viewer`**
- **To connect to android, linux need `VNC Server`**

Topic:
- [Android viewer](android-side)
- [Linux server](linux-side)
- [Run server](run-a-server)
  

# 1. Android side
- Download: VNC Viewer version 3.6.1.42089 by `RealVNC` available for android higher 4.4
  - [link to download at Uptodown.com](https://vnc-viewer.en.uptodown.com/android/download/1049524381)

# 2. Linux side
- I recommend TigerVNC because it open source
  - The RealVNC server need free licenses for offline but waste time to set up
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

# 3. Run a server
