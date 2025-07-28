# Refer
- [Ubuntu variants](https://ubuntu.com/desktop/flavors)
- Nội dung
    - [so sánh bản phân phối Flavors](#so-sánh-các-bản-phân-phối-ubuntu-ubuntu-flavors)
    - [Tạo usb boot Lubuntu trên Ubuntu](#tạo-usb-boot-lubuntu)
    - [Lưu ý quan trọng khi đổi giao diện Flavors](#lưu-ý-quan-trong-khi-chuyển-đổi-giữa-các-giao-diện-ubuntu-flavors)

# So sánh các bản phân phối Ubuntu (Ubuntu Flavors)

| Phân phối (Flavor) | Desktop Environment (DE)  | Ưu điểm chính                               | Dung lượng RAM (idle) | Đối tượng phù hợp        |
|--------------------|---------------------------|---------------------------------------------|------------------------|--------------------------|
| **Ubuntu**         | GNOME                     | Đẹp, hiện đại, dễ dùng, tích hợp tốt        | ~900–1.2 GB            | Người mới, máy mạnh     |
| **Kubuntu**        | KDE Plasma                | Cực kỳ đẹp, nhiều tùy chỉnh, nhẹ hơn GNOME  | ~700–1 GB              | Người thích đồ họa đẹp, tùy biến |
| **Xubuntu**        | XFCE                      | Rất nhẹ, ổn định, tối giản                   | ~400–500 MB            | Máy cũ, cấu hình yếu    |
| **Lubuntu**        | LXQt                      | Nhẹ nhất, đơn giản, rất nhanh               | ~300–400 MB            | Máy rất cũ, netbook     |
| **Ubuntu MATE**    | MATE                      | Giao diện giống GNOME 2, thân thiện         | ~500–600 MB            | Người thích truyền thống|
| **Ubuntu Budgie**  | Budgie                    | Đẹp, hiện đại, đơn giản, thanh lịch         | ~700–800 MB            | Người dùng bình thường  |
| **Ubuntu Studio**  | KDE Plasma (tùy biến)     | Hỗ trợ đồ họa, audio/video, nghệ thuật số   | ~800–1 GB+             | Nhà sáng tạo nội dung   |
| **Edubuntu**       | GNOME (hướng giáo dục)    | Cho giáo viên, trường học, trẻ em           | ~900 MB                | Trường học, lớp học     |
| **Ubuntu Unity**   | Unity                     | Giao diện cũ của Ubuntu (2010–2017), đơn giản| ~700–800 MB           | Fan Unity cũ            |
| **Ubuntu Kylin**   | UKUI (LXQt-based)         | Bản dành cho Trung Quốc (tiếng Trung, app riêng)| ~700–800 MB        | Người dùng Trung Quốc   |

---

## ✅ Ghi nhớ:

- **Kernel** (hạt nhân) và **package base** là như nhau (Ubuntu base).
- Chỉ khác nhau **DE (desktop environment)** và **app cài sẵn ban đầu**.
- Tất cả đều:
  - Được **Canonical bảo trì hoặc cộng đồng hợp tác chính thức**.
  - Có thể cập nhật, nâng cấp như nhau (ví dụ từ 22.04 lên 24.04).
  - Có thể cài DE khác nếu bạn thích mix (nhưng nên biết cách quản lý).

---

## 🔍 Gợi ý chọn bản:

| Mục đích dùng             | Gợi ý bản phân phối           |
|---------------------------|-------------------------------|
| Máy cũ, RAM < 2GB         | Lubuntu, Xubuntu              |
| Muốn hệ điều hành nhẹ     | Xubuntu, Ubuntu MATE          |
| Ưu tiên giao diện đẹp     | Kubuntu, Ubuntu Budgie        |
| Dùng cho sáng tạo (DAW)   | Ubuntu Studio                 |
| Chạy thử, cài nhanh       | Lubuntu (ISO nhẹ, cài nhanh)  |
| Trường học, giáo dục      | Edubuntu                      |
| Máy mạnh, dễ dùng         | Ubuntu (GNOME), Kubuntu       |


# Tạo usb boot Lubuntu
- Sở dĩ chọn Lubuntu vì 3 lý do:
  - Usb chỉ có 3.5GB
  - Lubuntu rất nhẹ và có giao diện hướng tới người dùng Window
  - Lubuntu hướng tới phân khúc lập trình app từ Qt
## 1. Tải Lubuntu 24.04.2
- [Download 24.04 LTS](https://lubuntu.me/downloads/)
  - Chỉ tải file .iso cho usb boot. `iso` hay disk image là 1 bản chụp chuẩn xác của phần mềm hệ thống (hệ điều hành hoặc đĩa DVD/CD cũ) đang chạy ổn định nhưng yêu cầu là khi chạy nó phải được mount như 1 ổ độc lập hoặc tải tòan bộ vào RAM để chạy an toàn. (Bao gồm các gói phụ trợ để nó chạy tốt ). 
  - Lubuntu chỉ còn hỗ trợ 64 bit
  - Dung lượng 3.1GB cho bản 24.04LTS

## 2. Chuẩn bị trước khi tạo USB boot
- Đầu tiên cần sử dụng công cụ `lsblk` (list block device) để duyệt hệ thống thiết bị dạng block gồm:
ổ cứng, thẻ nhớ, ... miễn là chúng lưu dữ liêụ dạng block.
  ```bash
  lsblk
  ```
- Đảm bảo `usb` dùng để boot phải được tìm thấy dưới dạng `sdX` và các phân vùng con của nó là `sdXi`
  - Ví dụ:  
  ![lsblk terminal](./img/Linux_lsblk_usbboot.png)
  - Thêm option `-f` để thêm thông tin
  ![lsblk terminal](./img/Linux_lsblk_usbboot_2.png)
- Sau đó thực hiện lệnh `unmount` để unmount các phân vùng ảo `sdXi` được tạo ra từ `sdX`
  - Lưu ý rằng device `sdX` là không thể unmount vì nó đại diện phần cứng usb đang cắm vào máy, nhìn ảnh trên nó không hề có mount point như `sdXi`
  ``` bash
  ~$ sudo umount /dev/sdb
  umount: /dev/sdb: not mounted.
  ```
  - Ví dụ trên cần gỡ `sdb1` để hệ thống không block nó khi nạp `iso`:
  ```bash
  sudo umount /dev/sdb1
  
  # hoặc đơn giản hơn là 
  sudo umount /dev/sdb* # không dùng "" vì nó ngăn mở rộng *

  ```
- OK giờ kiểm tra lại `lsblk -f` xem sdXi còn `mountpoint` không nếu nó mất như sdX là ok rồi.

## 3. Tải iso vào usb boot
- Công cụ sử dụng giờ là `dd` - data duplicator.
- Gọi lệnh chép file vào usb:  
  - `sudo dd if=/path/to/your.iso of=/dev/sdX bs=4M status=progress oflag=sync`
  - if là input file, of là output file, bs là block size read từ input -> output 
- Cuối dùng là dùng công cụ `sync`
  - ```bash
    sync # fflush toàn bộ tiến trình trnog hệ thống trong đó có dd để đảm bảo mọi file đã được ghi xuống.
          # nó sẽ blocking cho đến khi fflush hết
          # đôi khi dd không chờ fflush mà nó tắt luôn thì gây thiếu dữ liệu khi rút usb đột ngột hoặc reject sớm
    ```
## 4. cài hệ điều hành
### Cấu hình quản lý ổ cứng
- Linux yêu cầu cấu hình BIOS nhận dạng ổ cứng là `AHCI` thay vì `RAID`, các chế độ BIOS hỗ trợ Harddrive:
  - `Disable` dùng cho đời cũ như HDD
  - `AHCI` hỗ trợ cấu hình HDD, SSD chạy độc lập, chỉ dùng được 1 ổ ở 1 thời điểm
  - `RAID` hỗ trợ chạy song song nhiều ổ SSD, HDD.
    - RAID mode 0 cần ổ >= 2, tổng dung lượng các ổ gộp thành 1 ổ
      - hỏng 1 ổ là hỏng hết dữ liệu
    - RAID mode >=1 thì ưu tiên chạy song song các ổ và mỗi ổ lưu back up của ổ chính
      - An toàn dữ liệu vì có back up
- Linux `không có firmware nhân diện RAID` nên khi cài USBboot mà dùng mode `RAID` sẽ không thấy được ổ cứng
  - `Phải set sang AHCI`

### Cấu hình hệ thống file
- `ntfs` cho Window
- `ext4` cho linux

# Lưu ý quan trong khi chuyển đổi giữa các giao diện Ubuntu (Flavors)
- Tốt nhất là cứ tải các bản DE về nhưng đừng gỡ bản cũ vì nó gây lỗi giao diện nếu khoogn biết thao tác.
- Giữ lại bản cũ đôi khi dễ hơn khi chuyển qua lại các giao diện qua đăng nhập