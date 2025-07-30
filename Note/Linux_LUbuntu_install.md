# Refer
- [Ubuntu variants](https://ubuntu.com/desktop/flavors)
- [Install Lubuntu](https://manual.lubuntu.me/stable/1/1.3/installation.html)
- [Master boot record](https://en.wikipedia.org/wiki/Master_boot_record)
- [How can setup UEFI mode](https://askubuntu.com/questions/1253586/how-can-lubuntu-20-04-lts-be-installed-in-a-usb-which-can-boot-into-both-uefi)
- Nội dung
    - [so sánh bản phân phối Flavors](#so-sánh-các-bản-phân-phối-ubuntu-ubuntu-flavors)
    - [Tạo usb boot Lubuntu trên Ubuntu](#tạo-usb-boot-lubuntu)
    - [Lưu ý quan trọng khi đổi giao diện Flavors](#lưu-ý-quan-trong-khi-chuyển-đổi-giữa-các-giao-diện-ubuntu-flavors)

## I. Giới thiệu tổng quan về Boot Mode và Bảng phân vùng

Khi cài đặt hệ điều hành Linux, việc lựa chọn chế độ khởi động (Boot Mode) và kiểu bảng phân vùng là rất quan trọng để đảm bảo khả năng tương thích và hiệu suất.

* **Legacy BIOS (Chế độ kế thừa)**:
    * Sử dụng bảng phân vùng **MBR (Master Boot Record)**.
    * MBR nằm ở sector 0 của ổ đĩa, có dung lượng 512 byte. MBR bao gồm mã khởi động (bootstrap code - 446 bytes) và bảng phân vùng (64 bytes, hỗ trợ tối đa 4 phân vùng chính).
    * Hỗ trợ ổ đĩa có dung lượng tối đa 2TB.
    * Bootloader (ví dụ: GRUB) được cài đặt vào MBR và phần còn lại có thể nằm trong vùng "gap" giữa MBR và phân vùng đầu tiên (thường là sau sector 1 và trước sector 2048) hoặc trong một phân vùng riêng biệt.
    * Quá trình khởi động diễn ra tuần tự: BIOS tìm đến MBR, tải bootloader, sau đó bootloader tải hệ điều hành.

* **UEFI (Unified Extensible Firmware Interface)**:
    * Sử dụng bảng phân vùng **GPT (GUID Partition Table)**.
    * GPT hỗ trợ ổ đĩa có dung lượng lớn hơn 2TB và cho phép tạo nhiều phân vùng hơn (lên đến 128 phân vùng theo mặc định).
    * **Yêu cầu một phân vùng riêng biệt gọi là EFI System Partition (ESP)**, thường có kích thước từ 100MB đến 500MB và được định dạng FAT32. Các file bootloader (ví dụ: `.efi` của GRUB hoặc Windows Boot Manager) được lưu trữ trong ESP.
    * UEFI cung cấp khả năng khởi động nhanh hơn, bảo mật tốt hơn (ví dụ: Secure Boot) và tương thích tốt với các loại ổ đĩa hiện đại như NVMe.
    * Khi một ổ đĩa được định dạng GPT, nó vẫn chứa một "Protective MBR" ở sector 0. MBR này không dùng để khởi động hệ điều hành Legacy mà chỉ để ngăn các công cụ cũ không hiểu GPT ghi đè lên dữ liệu trên ổ đĩa GPT.

* **Tương thích ngược (Dual Boot/Legacy-UEFI)**:
    * Một ổ đĩa vật lý có thể được định dạng là GPT và hỗ trợ MBR. Nhưng không thể hoạt động song song để khởi động cả hai chế độ Legacy và UEFI trên cùng một ổ đĩa một cách trực tiếp.

## II. So sánh các bản phân phối Ubuntu (Ubuntu Flavors)

| Phân phối (Flavor) | Desktop Environment (DE)  | Ưu điểm chính                               | Dung lượng RAM (idle) | Đối tượng phù hợp        | Nguồn tham khảo |
|:-------------------|:--------------------------|:--------------------------------------------|:-----------------------|:-------------------------|:----------------|
| **Ubuntu** | GNOME                     | Đẹp, hiện đại, dễ dùng, tích hợp tốt        | ~900–1.2 GB            | Người mới, máy mạnh     |       |
| **Kubuntu** | KDE Plasma                | Cực kỳ đẹp, nhiều tùy chỉnh, nhẹ hơn GNOME  | ~700–1 GB              | Người thích đồ họa đẹp, tùy biến |       |
| **Xubuntu** | XFCE                      | Rất nhẹ, ổn định, tối giản                   | ~400–500 MB            | Máy cũ, cấu hình yếu    |       |
| **Lubuntu** | LXQt                      | Nhẹ nhất, đơn giản, rất nhanh               | ~300–400 MB            | Máy rất cũ, netbook     |    |
| **Ubuntu MATE** | MATE                      | Giao diện giống GNOME 2, thân thiện         | ~500–600 MB            | Người thích truyền thống|       |
| **Ubuntu Budgie** | Budgie                    | Đẹp, hiện đại, đơn giản, thanh lịch         | ~700–800 MB            | Người dùng bình thường  |       |
| **Ubuntu Studio** | KDE Plasma (tùy biến)     | Hỗ trợ đồ họa, audio/video, nghệ thuật số   | ~800–1 GB+             | Nhà sáng tạo nội dung   |       |
| **Edubuntu** | GNOME (hướng giáo dục)    | Cho giáo viên, trường học, trẻ em           | ~900 MB                | Trường học, lớp học     |       |
| **Ubuntu Unity** | Unity                     | Giao diện cũ của Ubuntu (2010–2017), đơn giản| ~700–800 MB           | Fan Unity cũ            |       |
| **Ubuntu Kylin** | UKUI (LXQt-based)         | Bản dành cho Trung Quốc (tiếng Trung, app riêng)| ~700–800 MB        | Người dùng Trung Quốc   |       |

---

### Ghi nhớ:

* **Kernel** và **package base** của các bản phân phối Ubuntu (flavors) là như nhau (Ubuntu base).
* Sự khác biệt chính nằm ở **Desktop Environment (DE)** và các **ứng dụng cài sẵn ban đầu**.
* Tất cả các flavors đều được **Canonical bảo trì hoặc cộng đồng hợp tác chính thức** và có thể cập nhật, nâng cấp như nhau (ví dụ từ 22.04 lên 24.04).
* Bạn có thể cài đặt các DE khác nhau trên cùng một hệ thống, nhưng cần lưu ý quản lý để tránh xung đột hoặc lỗi giao diện.

### Gợi ý chọn bản phân phối:

| Mục đích sử dụng          | Gợi ý bản phân phối           |
|:--------------------------|:------------------------------|
| Máy cũ, RAM < 2GB         | Lubuntu, Xubuntu              |
| Ưu tiên hệ điều hành nhẹ   | Xubuntu, Ubuntu MATE          |
| Ưu tiên giao diện đẹp      | Kubuntu, Ubuntu Budgie        |
| Dùng cho sáng tạo (DAW)   | Ubuntu Studio                 |
| Chạy thử, cài nhanh        | Lubuntu (ISO nhẹ, cài nhanh)  |
| Trường học, giáo dục      | Edubuntu                      |
| Máy mạnh, dễ dùng          | Ubuntu (GNOME), Kubuntu       |




## III. Tạo USB Boot Lubuntu

Lubuntu được chọn vì các lý do sau:
* Dung lượng file ISO nhỏ (khoảng 3.1GB cho bản 24.04 LTS), phù hợp với USB có dung lượng hạn chế.
* Nhẹ và có giao diện thân thiện với người dùng Windows.
* Hướng tới phân khúc lập trình ứng dụng từ Qt.

### 1. Tải Lubuntu 24.04.2 LTS

* Truy cập trang tải xuống chính thức của Lubuntu: [Download 24.04 LTS](https://lubuntu.me/downloads/)
* Chỉ tải file `.iso` (disk image). File `.iso` là một bản chụp chính xác của hệ điều hành, bao gồm các gói phụ trợ cần thiết để chạy ổn định.
* Lưu ý: Lubuntu 24.04 LTS chỉ hỗ trợ kiến trúc 64 bit.

### 2. Chuẩn bị USB trước khi tạo USB boot

* **Bước 1: Liệt kê thiết bị block (`lsblk`)**
    Sử dụng công cụ `lsblk` (list block devices) để xem danh sách các thiết bị lưu trữ dạng block như ổ cứng, thẻ nhớ, USB đang kết nối với hệ thống.
    ```bash
    lsblk
    ```
    hoặc để có thêm thông tin về định dạng file system:
    ```bash
    lsblk -f
    ```
    Đảm bảo xác định đúng tên thiết bị USB của bạn (ví dụ: `/dev/sdb`, `/dev/sdc`, v.v.). **Tuyệt đối không nhầm lẫn với ổ đĩa hệ thống chính của bạn để tránh mất dữ liệu.** Tên USB thường có dạng `sdX` và các phân vùng con là `sdXi` (ví dụ: `sdb1`, `sdb2`).

* **Bước 2: Ngắt kết nối các phân vùng của USB (`umount`)**
    Các phân vùng trên USB cần được ngắt kết nối (`unmount`) để hệ thống không bị "khóa" chúng khi ghi file ISO.
    ```bash
    sudo umount /dev/sdX1 # Thay sdX1 bằng tên phân vùng cụ thể của USB, ví dụ: /dev/sdb1
    # hoặc để ngắt kết nối tất cả các phân vùng trên USB đó:
    sudo umount /dev/sdX* # Thay sdX bằng tên thiết bị USB (ví dụ: /dev/sdb)
    ```
    Lưu ý rằng bản thân thiết bị `sdX` (ví dụ: `/dev/sdb`) không thể bị `unmount` vì nó đại diện cho phần cứng USB đang cắm vào máy.


### 3. Ghi file ISO vào USB boot (`dd`)

Sử dụng công cụ `dd` (data duplicator) để ghi file ISO vào USB.
```bash
sudo dd if=/path/to/your.iso of=/dev/sdX bs=4M status=progress oflag=sync
```
  - if=/path/to/your.iso: Đường dẫn đến file Lubuntu `.iso` bạn đã tải về.
  - of=/dev/sdX: Tên thiết bị USB đã xác định ở bước trên (ví dụ: /dev/sdb). Đảm bảo không thêm số thứ tự phân vùng (ví dụ: không dùng /dev/sdb1).
  - bs=4M: Kích thước khối (block size) để đọc từ input và ghi ra output, 4M thường cho tốc độ tốt.
  - status=progress: Hiển thị tiến trình ghi.
  - oflag=sync: Đảm bảo tất cả dữ liệu được ghi vật lý xuống USB trước khi lệnh dd kết thúc.

Sau khi lệnh dd hoàn tất, sử dụng lệnh `sync` để đảm bảo mọi dữ liệu đã được ghi hoàn toàn xuống USB và không còn trong bộ đệm của hệ thống.
  - ```bash
    sync # fflush toàn bộ tiến trình trnog hệ thống trong đó có dd để đảm bảo mọi file đã được ghi xuống.
          # nó sẽ blocking cho đến khi fflush hết
          # đôi khi dd không chờ fflush mà nó tắt luôn thì gây thiếu dữ liệu khi rút usb đột ngột hoặc reject sớm
    ```

## IV. cài hệ điều hành
### 1. Cấu hình quản lý ổ cứng (Disable/AHCI/RAID)
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

### 2. Cấu hình quản lý bootmode (Legacy - HDD/Sata - Not recommed NVME)
- Tiếp theo, mặc định khi cài theo kiểu `Erase disk` thì sẽ tạo lại bảng `MBR`
  - `MBR` thì chỉ hỗ trợ tạo 4 partitions và quản lý đến 2TB
  - `GPT` có thể  tạo lớn hơn và nhiều phân vùng hơn nhưng không hỗ trợ boot Legacy (chọn ổ cứng tuần tự) cho máy cũ
- Vì vậy chỉ có thể dùng Legacy boot mode để duyệt tuần tự ổ qua `MBR`
- Sau khi cài LUbuntu bằng `Erase disk` hệ thống `MBR` được setup nhưng nó có thể không biết cách khởi động `Lubuntu` vì vậy khi restart máy báo `No boot device found`   
  Phải làm sao? khi này cần cài thêm cho nó bootloaer tên là `GRUB`
  - Lưu ý cái này là cài `Linux`, còn `Window` không dùng `GRUB` mà dùng phần mềm riêng và tự động của nó.
  - Nếu cài `Window` sau linux thì phải cấu hình lại `GRUB` là `bootloader` nếu không không thể tìm ra Linux do đang dùng `window bootloader`
    - Như vậy `GRUB` có thể tìm ra Window nhưng ngược lại thì không 

- Sự khác nhau giữa Legacy/UEFI:
  - Legacy là chuẩn boot kiểu cũ, hỗ trợ trình tìm bootloader trong `MBR` nằm tại địa chỉ 0x0000, tại sector 0
  - UEFI là chuẩn boot kiểu mới, hỗ tợ tìm file cấu hình trong `GPT` tại partition 1 (Khoảng 100MiB - 500MiB)
    bên cạnh đó sector 0 có thể sẽ được nạp 1 `PMBR` để tương thích ngược với legacy nhằm mục đích bảo vệ phân vùng `GPT` bị ghi nhầm.
  - Khi cấu hình phân vùng ta phải để chừa ra 1 đến 2MB để GRUB bootloader có chỗ để lưu vì `MBR` chỉ có ` 1 sector `


#### Cấu hình hệ thống file system
- `ntfs` cho Window
- `ext4` cho linux

### 3. Cấu hình lại GRUB cho hệ thống Legacy (HDD, SATA, maybe support NVME (notrecommend))
#### Với `MBR` được giới thiệu trong wiki, nó nằm ở đầu ổ đĩa nơi mà BIOS tìm đến để nạp Bootloader tại đây ra RAM:
  - MBR có cấu trúc classic bao gồm:
    - Bootstrap code area ở địa chỉ  `0x0000`, tổng size `446 bytes`
      - Dùng để chứa chương trình tìm `bootloader`
    - `0x01BE` , `0x01CE` , `0x01DE`, `0x01EE` mỗi phần này rộng 16byte để lưu mô tả các `partitions` từ 1 - 4 như đã nói trên thì MBR chỉ hỗ trợ 4 partions (thiết kế cứng luôn)
      - Mỗi partition có thể là 1 hệ điều hành, các partion khác có thể không cần có mặt ở đây.
      - Mặc định bootloader cơ bản nhất chỉ nhìn partion đầu tiên và nhảy luôn vào hệ điều hành
    - Tại `0x01FE` sau đó là 2 byte `Boot signature`
  - => tổng MBR là 512 byte (== 1 sector cho ổ cứng)
  - ngoài ra trong Wiki đề cập 1 số cấu trúc khác nhưng không đi sâu hơn nữa.

#### Tiếp theo là bootloader `GRUB`
- GRUB là bootloader sau đời sau, có hỗ trợ quản lý vấn đề chạy được nhiều hệ điều hành trên 1 máy.
  - Như logic trên thì có thể có đến 4 hệ điều hành chạy song song nhưng GRUB hỗ trợ mở rộng hơn.
  - `GRUB` (Grand Unified Bootloader) cung cấp giao diện lựa chọn trực quan thay vì chỉ boot luôn vào phân
  vùng đầu tiên.
    - Bootloader GRUB nằm tại `Bootloader` của `MBR`
    - Phần thứ 2 của chương trình nằm strong vùng `gap` được thiết kế ở giữa `MBR` và `partition 1`
      - Các chương trình chia ổ cứng, quản lý ổ yêu cầu `partition 1` luôn phải bắt đầu ở vị trí 
      bắt đầu từ sector 2048. như vậy Theo lý thuyết phần MBR có thể mở rộng ra 2048 lần ban đầu.
        - Vùng gap tương đương 2047 sector khoảng (gần 1MB)
        - Vì vậy chương trình này cho khả năng quản lý vượt trội hơn.
    
  - `GPT` sẽ không nói ở đây dù nó khá vượt trội


#### Nạp `GRUB` cho `MBR`:
- `GRUB` chỉ support `Linux` hoặc OS like Unix
  - Nếu 1 window được cài vào hệ thống, bootloader riêng của nó sẽ ghi đè MBR để xóa GRUB
- Trong `USB Boot` mở terminal:
  - OK giờ thực hiện cẩn thận `grub-install` và `update-grub`
  - Trong `USB boot terminal` nhảy đến mục `/mnt` để `mount` với LUbuntu vừa cài.
    - Gõ `lsblk` để tìm tên của ổ cứng, ở đây có thể là:
      - `sdX` cho SSD `sata` hoặc `nvme0n1` hoặc tương tự cho SSD `nvme`
    - Gõ `lsblk -f` để xem tên của ổ là gì, ở dây bên trong `nvme0n1` có 1 phân vùng con là `nvme0n1p1` là vùng nhớ cho OS Lubuntu đã cài.
    - Giờ trong `/mnt` tạo thư mục tên là `local_lubun_root` hoặc gì đó tùy
- Giờ cấu hình liên kết với hệ điều hành Lubuntu để cài hệ thống `GRUB`:
  - chạy tập lệnh:
  ```bash
  sudo mount /dev/nvme0n1p1 local_lubun_root # mount với hệ thống file thật (chương trình khác vẫn được mount nhưng có cảnh báo readonly hoặc gì đó)

  sudo mount --bind /dev  local_lubun_root/dev # file ảo phải bind thì không có hệ thông file để link
  sudo mount -t proc proc local_lubun_root/proc # tạo lại 1 cây process ảo cho chroot
  sudo mount -t sys sys  local_lubun_root/sys   # tạo lại cấu trúc hệ thống ảo cho chroot về kernel, ổ cứng , ...

  sudo chroot local_lubun_root

  ```

  - Giờ ta đang trong hệ thông file của Lubuntu rồi, thực hiện các bước sau để cài đặt `GRUB` và đăng ký
  cho Lubuntu 1 file config, sau này `GRUB` tìm đến nó
    - Tìm đến ổ cứng để cài `GRUB`
    ```bash
    lsblk -f # duyệt ổ cứng, tìm tên đại diện cho ổ cứng ,  
    ```
      - Lưu ý ổ cứng chứ không phải các partion hay ổ con
        - Ví dụ:
          - `nvme0n1` chứ không phải `nvme0n1p1`
          - `sdX` chứ không phải `sdXi`

    - Cài `GRUB` theo chế độ `legacy mode` hỗ trợ ssd sata, hdd nhưng nvme hầu như không hỗ trợ nếu bios Legacy đời cũ không hiểu giao tiếp nvme và thường bị bỏ qua khi duyệt:
      ```bash
      grub-install /dev/[harddrive] # ổ tùy máy nhưng không bên dùng Legacy cho nvme, chỉ nên HDD hoặc sata
                                    # grub-install chỉ nên gọi 1 lần để đánh dấu đây là hệ điều hành chính

      update-grub # cập nhật file GRUB config cho hệ điều hành
      ```
    - Phần sau sẽ nói về `GRUB` theo chế độ `UEFI` hỗ trợ tốt cho sata và nvme

#### 3.5 Cách chuyển qua lại các OS
- Để giảm số lần ghi lại bootloader `GRUB` bằng `grub-install` ta thống nhất 1 hệ điều hành chính sẽ được boot mặc định
  - `grub-install` không chỉ có tác dụng ghi bootloader, nó còn có trường thông tin cảu hệ điều hành cuối cùng gọi nó
    - Vì vậy mỗi lần boot là nó nhảy luôn vào hệ điều hành chính
- Để kích hoạt chế độ chọn OS, ta thực hiện vào OS chính và kiểm tra:
  ```bash
  cat /etc/default/grub | grep OS_PROBER
  # Nếu GRUB_DISABLE_OS_PROBER=true thì sửa thành false để cho phép `os-prober` tìm các partions chức hệ điều hành

  # Giờ cần cài os-prober, phần mềm này được `update-grub` tự động gọi ra để quét ổ cứng
  sudo apt update
  sudo apt install os-prober

  # Cập nhật danh sách hệ điều hành
  sudo update-grub # gọi đến `os-prober` và cập nhật vào file config

  ```
- Ưu điểm cách này là có thể vào đưuọc nhiều hệ điều hành khi khởi động
  - Không cần thiết phải cài os-prober trên các hệ điều hành khác vì hiệu ứng vẫn tương tự chả khác gì mà 
  còn phải tốn cồn thêm 1 lần `grub-install` dễ gây lỗi nội dung `MBR`


### 4. Cấu hệ thống UEFI (HDD, SATA, NVME)
- [Setup GPT partion](https://askubuntu.com/questions/1253586/how-can-lubuntu-20-04-lts-be-installed-in-a-usb-which-can-boot-into-both-uefi)
- Bên trong USB boot có thể chọn chế độ `Manual partition` và làm theo cấu hình link trên

### 5 Cấu hình hệ thống UEFI hỗ trợ thêm cho Legacy mode
- Chạy 2 hướng dẫn trên theo thứ tự:
  - Tạo `UEFI` boot ở phân vùng 1
  - Khi cài `Legacy boot` ở phân vùng 0 thì GRUB thấy có `GPT` header, nó kiểm tra và liên kết với phân vùng vài MB đã tạo
    - Nó sẽ ghi lại PMBR thành dạng MBR đặc biệt có thể trỏ đến partition Bootloader
    - Nếu hhông nó cài booloader luôn ở sector 1 theo chuẩn legacy

# Lưu ý quan trong khi chuyển đổi giữa các giao diện Ubuntu (Flavors)
- Tốt nhất là cứ tải các bản DE về nhưng đừng gỡ bản cũ vì nó gây lỗi giao diện nếu khoogn biết thao tác.
- Giữ lại bản cũ đôi khi dễ hơn khi chuyển qua lại các giao diện qua đăng nhập


## V. Xử lý lỗi
### 1 Lỗi Khởi động màn hình terminal sau khi cài Lubuntu

### 2 Lỗi thiếu driver card mạng


### 3 Cài bộ gõ tiếng việt