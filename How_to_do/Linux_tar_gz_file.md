### tar.gz
- This is combine of 2 step packaging: `tar`- non compressive, group folder to 1 file. And `gzip` compressive and archive 1 file only.
    ```bash
    # Extract tar.gz
    gunzip app.tar.gz        # unzip to app.tar
    tar -xf app.tar          # create app/ directory from tar
    ```
    - another unarchive method:
    ```bash
    tar -xzf app.tar.gz
    ```
