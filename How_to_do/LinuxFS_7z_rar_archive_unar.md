# [Refer](https://itsfoss-com.translate.goog/use-7zip-ubuntu-linux/?_x_tr_sl=en&_x_tr_tl=vi&_x_tr_hl=vi&_x_tr_pto=tc)

# Archive / unarchive
- [p7zip-full](#p7zip-full)
- [p7zip-rar](#p7zip-rar)
- [unrar](#unrar) another method extract rar5 if `7z` can't do


| Mức nén (`-mx=N`) | Tên gọi   | Tốc độ nén  | Kích thước nén (vs gốc) | Tốn CPU | RAM dùng    | Dùng khi nào                         |
|-------------------|-----------|--------------|--------------------------|---------|-------------|--------------------------------------|
| `-mx=0`           | Store     | 🚀 Rất nhanh | 🔲 100%                  | ⚪ Thấp | 🔽 10 MB     | Không cần nén, chỉ chia file         |
| `-mx=1`           | Fastest   | 🚀 Rất nhanh | 🔲 ~98–99%               | ⚪ Thấp | 🔽 16 MB     | Nén nhanh, không quan trọng dung lượng |
| `-mx=3`           | Fast      | ⚡ Nhanh      | 🔲 ~95–97%               | ⚪ Thấp–vừa | 🔽 24 MB | Backup nhẹ, chia sẻ nhanh            |
| `-mx=5`           | Normal    | ⚖️ Trung bình | 🔲 ~90–95%               | ⚪ Vừa  | 🔼 ~64 MB    | Dùng mặc định                        |
| `-mx=7`           | Maximum   | 🕒 Chậm hơn   | 🔲 ~85–90%               | 🔥 Cao | 🔼 ~128 MB   | Nén lưu trữ dài lâu                  |
| `-mx=9`           | Ultra     | 🐢 Rất chậm   | 🔲 ~82–88%               | 🔥🔥 Rất cao | 🔼 ~256 MB | Tối ưu dung lượng, nặng CPU          |



## p7zip-full
## p7zip-rar

## command
- extract, enter password if need, create output folder if need
```bash
7z x -pYOUR_PASSWORD -o"./output_dir" file.7z
```
- archive a file/folder
```bash
7z a -t7z -o"Output folder link" -mx=7 -p"Password" -v2g  "archive name" "file folder want archive"
# -t type 7z 
# -o out folder link
# -mx from -mx1 -> -mx9 compress level
# -v  Volume size / split when archive {b/k/m/g}
# archive_name  output file name

```


## unrar
```bash
# install
sudo apt install unrar

# extract
unrar x -op"output_folder" -p"password" "filename" 

```
