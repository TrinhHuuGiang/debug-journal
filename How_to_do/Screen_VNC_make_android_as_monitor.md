Note:
- **To make android as a monitor for linux we need `VNC Viewer`**
- **To connect to android, linux need `VNC Server`**

# 1. Android side
- Download: VNC Viewer version 3.6.1.42089 by `RealVNC` available for android higher 4.4
  - [link to download at Uptodown.com](https://vnc-viewer.en.uptodown.com/android/download/1049524381)

# 2. Linux side
- I recommend TigerVNC because it open source
  - The RealVNC server need free licenses for offline but waste time to set up
- Dowload: 2025 version 1.15
  - [link to download VNC server](https://sourceforge.net/projects/tigervnc/files/stable/1.15.0/)
  - 
  - [link to download source code `tar.gz` at Github](https://github.com/TigerVNC/tigervnc/releases/tag/v1.15.0)
- Install `deb` for `ubuntu-24.04LTS / amd64`:
  - download: [tigervncserver_1.15.0-1ubuntu1_amd64.deb](https://sourceforge.net/projects/tigervnc/files/stable/1.15.0/ubuntu-24.04LTS/amd64/)
    - it about 1.7MB
  - in download copy to expected folder and do:
    ```bash
      # cp to expected folder
      cp ./tigervncserver_1.15.0-1ubuntu1_amd64.deb [link to save folder]
      cd [ save folder ]
  
      # install
      sudo dpkg -i ./tigervncserver_1.15.0-1ubuntu1_amd64.deb
    ```
