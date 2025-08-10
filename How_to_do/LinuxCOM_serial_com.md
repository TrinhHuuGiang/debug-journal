## Refer
- [Terminal for serial communicate devices with Linux](https://www.reddit.com/r/embedded/comments/x9b4wf/best_terminal_for_serial_comms_between_device_and/)
- [Using minicom](https://www.youtube.com/watch?v=zqeCHRouxy4)

## Test minicom
```bash
sudo apt install minicom
# sudo apt-get install minicom

# Then sure that user is in group `dialout` to get access serial port
sudo adduser $USER dialout
```

### Get help
```bash
minicom --help

# help
Usage: minicom [OPTION]... [configuration]
A terminal program for Linux and other unix-like systems.

(*) -b, --baudrate         : set baudrate (ignore the value from config)
(*) -D, --device           : set device name (ignore the value from config)
(*) -s, --setup            : enter setup mode
  -o, --noinit           : do not initialize modem & lockfiles at startup
  -m, --metakey          : use meta or alt key for commands
  -M, --metakey8         : use 8bit meta key for commands
  -l, --ansi             : literal; assume screen uses non IBM-PC character set
  -L, --iso              : don't assume screen uses ISO8859
  -w, --wrap             : Linewrap on
  -H, --displayhex       : display output in hex
  -z, --statline         : try to use terminal's status line
  -7, --7bit             : force 7bit mode
  -8, --8bit             : force 8bit mode
  -c, --color=on/off     : ANSI style color usage on or off
  -a, --attrib=on/off    : use reverse or highlight attributes on or off
  -t, --term=TERM        : override TERM environment variable
  -S, --script=SCRIPT    : run SCRIPT at startup
  -d, --dial=ENTRY       : dial ENTRY from the dialing directory
  -p, --ptty=TTYP        : connect to pseudo terminal
  -C, --capturefile=FILE : start capturing to FILE
  --capturefile-buffer-mode=MODE : set buffering mode of capture file
  -F, --statlinefmt      : format of status line
  -R, --remotecharset    : character set of communication partner
  -v, --version          : output version information and exit
  -h, --help             : show help
  configuration          : configuration file to use
```

### Error default no such file or directory at first time install
```bash
giangtrinh@giangtrinhLU:~$ minicom
minicom: cannot open /dev/modem: No such file or directory

giangtrinh@giangtrinhLU:~$ sudo minicom
minicom: cannot open /dev/modem: No such file or directory
```
- Problem is `/dev/modem` is default serial type of `minicom`.
    - Solution `setup minicom` before using, see menu above:
        ```bash
        minicom -s

        #Now in menu setup go to `Serial port setup`
        #Modify Serial Device to /dev/tty0 or port expecting
        # If dont know which port to connect try run `dmesg -w` in another terminal
        #    then re plug serial device, system log will show name of device `/dev/...`
        ```
    - Another method we can input argument by option above:
        ```bash
        #example connect a serial device have `/dev/ttyUSB0` with baud 9600
        # Here I create a temporary file on Ram at `/tmp` to protect not to record real files
        # and avoid wearing SSD drive
        minicom -D /dev/ttyUSB0 -b 9600 -C "/tmp/___minicom_tmp_record___"

        # Now in window of `minicom` type some thing 
        # Open new terminal then `tail -f "/tmp/___minicom_tmp_record___"`
        # here anything receive from serial will log frequency
        ```