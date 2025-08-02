- Filter, remove old commit
- Install
```bash
sudo apt install git-filter-repo
```
- Check commit
```bash
git log --grep="Commit name"

#return
commit SHA
Author
Date
```

- Remove commit
```bash
# b"" is convert to binary
git filter-repo --commit-callback '
    if commit.original_id == b"SHA string":
        commit.skip()
'
```