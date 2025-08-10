# Syntax download
## Download 
```bash
curl -O [link download]

#  optional:
#   -# is display progress bar
#   -s is not display progress
```

## Stop download
```bash
# type Ctrl + C
# raw file still exist for continue
```

## Continue download
```bash
curl -C - -O https://example.com/file.iso

# note: some web site limit time link, sure that link is right
```
