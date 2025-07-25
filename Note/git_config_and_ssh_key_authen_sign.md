# Linux create new ssh-key for authentication:
- Go to folder `~.ssh`
- Type `ssh-keygen -t rsa -b 4096`
    - Enter -> notype location -> default ssh-rsa file
        - using authentication

# Create new ssh-key for sign git commit gpg:
- Chữ ký số giúp xác thực rằng commit đến từ nguồn đáng tin cậy
- Type `ssh-keygen -t rsa -b 4096`
    - but now type file name "sign_commit_git"
    - Now `git config -l` to see all config
        - `git config --global user.name=GiangTrinh`
        - `git config --global user.email=giangtrinhvnbl2k2@gmail.com`
        - `git config --global user.signingkey ~/.ssh/sign_commit_git.pub` // chỉ nhập link không cần `=`
        - `git config --global gpg.format ssh` // đây là cấu hình ký ssh thay cho gpg
        - `git config --global commit.gpgsign true` // true để tự động ký

# Last one:
    - Go to github -> setting-> add SSH and GPG key
    - Nhớ backup key ở đâu đó an toàn vì hỏng lap 1 lần là nhớ đời rồi

# Refer
- https://docs.github.com/en/authentication/managing-commit-signature-verification/telling-git-about-your-signing-key