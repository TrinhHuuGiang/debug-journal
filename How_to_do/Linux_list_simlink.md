# Linux Links Quick Lookup
- **Inode** Identify unique index of a file
- **Hard Link:** create a points to inode, multiple names = same data, deleting one link doesn't delete data.  
    - 
    ```bash
    # a simple scene about inode and hardlink
    ls -li ./

    397073 drwxrwxr-x  4 giangtrinh giangtrinh 4096 Thg 8  25 18:46  WINE_app_data 
    ```
    - In the example above, `397073` is Inode and `4` is number hardlink point to this Inode
    - When number hardlink >1, file still exist, when deleted all hardlink to file => file deleted
    - **Note:** Hardlink can't link to `folder`, only accept link to a file
- **Soft Link (Symlink):** points to file path, can link files/dirs, deleting target → broken link.
    - Softlink do not effect on `Hardlink number`, delete softlink do not effect on Inode (file/folder)
    - Delete all hardlink, the Softlink will not able access to that link (trash file)
- **Simple explain Effect of Deleting:** No hard link no file, Softlink not effect to file
