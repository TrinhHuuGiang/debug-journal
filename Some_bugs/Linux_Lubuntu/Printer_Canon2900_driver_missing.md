# Download canon printer driver from cannon:
## Error: `Package libglade2-0 is not installed`
- When try install Debian pakage `cndrvcups-capt_2.71-1_amd64.deb`, `cndrvcups-common_3.21-1_amd64.deb`
    - Error occur missing `libglade2-0` library:
        ```bash
        dpkg: dependency problems prevent configuration of cndrvcups-capt:
        cndrvcups-capt depends on libglade2-0 (>= 1:2.5.1); however:
        Package libglade2-0 is not installed.
        cndrvcups-capt depends on cndrvcups-common (>= 3.21); however:
        Package cndrvcups-common is not installed.

        dpkg: error processing package cndrvcups-capt (--install):
        dependency problems - leaving unconfigured
        Errors were encountered while processing:
        cndrvcups-capt
        ```
- Solution: 
    - [Get package deb for x86 or x64](https://www.ubuntuupdates.org/package/core/plucky/universe/base/libglade2-0)
    - `sudo dpkg -i [deb file]`
    - After that reinstall `cndrvcups-common_3.21-1_amd64.deb` then `cndrvcups-capt_2.71-1_amd64.deb`