# Linux create new ssh-key for authentication:
- Go to folder `~.ssh`
- Type `ssh-keygen -t rsa -b 4096`
    - Enter -> notype location -> default ssh-rsa file
        - using authentication

# Create new ssh-key for sign git commit gpg:
- Type `ssh-keygen -t rsa -b 4096`
    - but now type file name "sign_commit_git"
    - Now `git config -l` to see all config
        - `git config --global user.name=GiangTrinh`
        - `git config --global user.email=giangtrinhvnbl2k2@gmail.com`
        - `git config --global user.signingkey=~/.shh/sign_commit_git.pub`
        - `git config --global gpg.format ssh`
        - `git config --global commit.gpgsign true`

# Last one:
    - Go to github -> setting-> add SSH and GPG key
    - Nhớ backup key ở đâu đó an toàn vì hỏng lap 1 lần là nhớ đời rồi