## References
- [win32openssh](https://github.com/PowerShell/Win32-OpenSSH)

## How to create SSH server
### 1. Setup `win32openssh` rar file for window
- Download right version ` OpenSSH-Win64.zip ` or `  OpenSSH-Win32.zip ` for window architecture
- extract zip file in a special folder

#### Run `ssh-keygen -A`
- This command auto create a folder `C:\ProgramData\ssh` and put `server public and private key` for several asymmetric cryptographic algorithm like rsa, ed25519

#### Automatic install `sshd` by script following
- In the folder extract, run file `./install-sshd.ps1` as `administrator`
    - If can run script, check `ExecutionPolicy`
    ```powershell
    Get-ExecutionPolicy
    # Restricted ,  RemoteSigned,   Unrestricted

    # If restricted, system is block running script
    # change to RemoteSigned if still can't, change to Unrestricted
    Set-ExecutionPolicy Unrestricted
    ```
- After executed, start `sshd` to create `ssh server`, by default Port is `22`:
    ```powershell
    Start-Service sshd
    ```
- Now try connect to this `ssh` server.

#### Create `sshd-config` if wanna modify connection method
- By default, after run script install sshd above, sshd will screate [C:\ProgramData\ssh\sshd_config](../Some_bugs/Linux_Lubuntu_24_04/doc/sshd_config_default)
- Solution to modify connection method is modify this file or copy `sshd_config_default` in the install rar file folder, rename to `sshd_config` then modify, service ssh will prioritize using this config file:
    - Any feild wanna change, uncomment it then change state, example a config accept administrator login with password:
    ```bash
    port 1024 #default 22
    PermitRootLogin yes
    PasswordAuthentication yes
    PermitEmptyPassword no
    ```
- Rerun `sshd` service:
```powershell
Stop-Service sshd
Start-Service sshd
```

### 2. Try ssh, sftp
- [Refer to](https://github.com/TrinhHuuGiang/Learn-sqlite-and-linux/blob/master/Linux_command/Note/p2/_001_termux_install_ssh.md)
