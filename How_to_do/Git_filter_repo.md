- Filter, remove old commit
    - warning : Any old signature will wrong with repo after remove commit
        - `Verified` -> `Unverified`
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

- If after remove, repo missing remote:
```bash
git remote add origin [repo link]

#repo will block push because difference history
git push --force origin master # force push
```


