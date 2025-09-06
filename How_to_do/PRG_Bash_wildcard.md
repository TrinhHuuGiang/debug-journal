# topic:
- [wildcard](#wildcard-globbing-bash---tóm-tắt)
- [wildcard recursive](#đệ-qui-với-wild-card-và-find)
- [wildcard with link has spaces](#wildcard--đường-dẫn-có-space-trong-bash)

# Wildcard (Globbing) Bash - Tóm tắt
Ký tự:
*       : 0 hoặc nhiều ký tự
?       : 1 ký tự
[abc]   : 1 ký tự trong danh sách
[!abc]  : 1 ký tự không trong danh sách
[a-z]   : 1 ký tự trong range
**      : 0 hoặc nhiều thư mục con (Bash 4+, shopt -s globstar)

Cách dùng:
- Lệnh bình thường: ls file*, cp file* → expand file list trong mục hiện tại với các phần tử  chuỗi trả về trong `""`
- Trong vòng lặp, ví dụ: ` for f in file*; do cp "$f" dest/; done `
  - phải có `"$f"` vì khi này nếu f có space sẽ lỗi phân tích chuỗi
- So sánh: [[ $var == file* ]] → pattern string, không đọc file

# đệ qui với wild card và find
- Dùng find để match đệ quy an toàn với space:
  - `find . -name "*.txt" -print0 | xargs -0 cp -t dest/`
    - `.` là mục hiện tại
    - `-name "*.txt"` wild card các file có đuôi .txt
    - `-print0` in tên file kèm null character (\0)
    - `xargs` đọc từ stdin, tạo command line từ các input.
    - `-0` đọc null-terminated strings (\0) từ `stdin`
    - `cp -t dest/` `-t` know next string is output folder
      - if with out space the output folder at the last argument -> wrong when `xargs` append argument split from `stdin`.

# Wildcard + đường dẫn có space trong Bash

- Cách 1: escape space bằng \
  - cp link\ to\ folder/*.bib dest/

- Cách 2: quote đường dẫn
  - cp "link to folder"/*.bib dest/

