# Topic
- Both of `nuhup` and `setsid` using to keep running backgound process
  - And some tips when using with `sudo`
- (Not recommended) nohup – “no hanging up” (ignore SIGHUP, signal 1)
  - **Purpose**: Prevent a process from being terminated when the terminal closes or the user logs out.
  - Behavior with sudo in background process:
    - If the command requires sudo and password is not cached  
      running `nohup sudo ... &` or `sudo nohup ... &`  will be hanging because sudo needs a tty to ask for a password.
    - Does not detach from the shell or controlling terminal  
      → background jobs can still be stopped (SIGTTIN/SIGTTOU) if the process interacts with the terminal.
    - `nohup sudo ... &` mean sudo after set ignore SIGUP, but `sudo` still be stopped when end terminal get (SIGTTIN/SIGTTOU)
    - `sudo nohup ... &` mean sudo is parent `nohub`, end terminal -> kill sudo -> kill nohub -> end process
---
- (Recommended) setsid – “set session ID” (create a new session, fork current job)
  - Purpose: Fork the process into a new session, detached from the controlling terminal.
  - Ideal for daemons, servers, and long-running background processes.
  - Behavior with sudo in background process:
    - **Warn** `setsid sudo ... &` will fail because sudo in fork process will requires a password and there is no tty.
    - Solution:
      - run `sudo -v` first to cache the password
        - and always run `sudo setsid ... &`, sudo is asked password above then fork
--- 
- (Recommended for sudo background task) **sudo -b `command`**
  - flag `-b` has behavior similar with `sudo -v` and `sudo setsid ... &`, user will be asked password if not input before and
  - fork task to new process in background
