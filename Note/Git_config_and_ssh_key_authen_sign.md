# Linux create new ssh-key for authentication:
- Go to folder `~.ssh`, if not exist, try command below to add rawkey and auto create folder
- Type `ssh-keygen -t rsa -b 4096`
    - Enter -> notype location -> default ssh-rsa file
        - using authentication

# Create new ssh-key for sign git commit gpg:
- Chữ ký số giúp xác thực rằng commit đến từ nguồn đáng tin cậy
- Type `ssh-keygen -t rsa -b 4096`
    - but now type file name "sign_commit_git"
    - Now `git config -l` to see all config
        - `git config --global user.name "GiangTrinh"`
        - `git config --global user.email "giangtrinhvnbl2k2@gmail.com"`
        - `git config --global user.signingkey ~/.ssh/sign_commit_git.pub`
        - `git config --global gpg.format ssh` // đây là cấu hình ký ssh thay cho gpg
        - `git config --global commit.gpgsign true` // true để tự động ký

# Last one:
    - Go to github -> setting-> add SSH and GPG key
    - Nhớ backup key ở đâu đó an toàn vì hỏng lap 1 lần là nhớ đời rồi


# Add file `config` for manage SSH
- Each link ssh have format like this:
    ```ssh
    git@github.com:TrinhHuuGiang/note-for-future.git
    |       |
    User   Host 
- Each link ssh will send to server name as `Hostname`
- In folder `~/.ssh/` create filde `config` and add these field:
    ```bash
    Host github.com
            HostName github.com
            User git
            IdentityFile ~/.ssh/SSH/authen_git
            IdentitiesOnly yes # make sure only execute ssh 1 time
                                # with this Host
    
    Host [Host]
        HostName [HostName]
        User [User]
        IdentityFile [ssh file link]
        IdentitiesOnly yes


    ```

# Refer
- https://docs.github.com/en/authentication/managing-commit-signature-verification/telling-git-about-your-signing-key