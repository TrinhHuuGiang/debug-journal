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
- **best unarchive method keep save hard drive life cycle:**
    ```bash
    zcat < app.tar.gz | tar xf -
    # `tar` file do not create, only read `.tart.gz` and redirect to stdin of `zcat`
    # `<` bind stdin of `zcat` to file `app.tar.gz`
    # `zcat` analyzes file then write each block data to stdout, `tar` using stdin read then create destination folder
    ```