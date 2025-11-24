# SYSTEMD TUTORIAL
## 1. TỔNG QUAN VỀ SYSTEMD
systemd là hệ thống quản lý service của Linux hiện đại.
Nó dùng để:
- Khởi chạy service từ lúc máy boot.
- Chạy service khi user login.
- Quản lý tiến trình, socket, timer.
- Thay thế cách init.d cũ.

Công cụ điều khiển: `systemctl`

## 2. PHÂN LOẠI SERVICE

### A. System Service (dịch vụ hệ thống)
- Chạy với quyền root
- Chạy ngay từ lúc boot
- Không phụ thuộc user
- File đặt tại:
  - `/etc/systemd/system/`
  - `/lib/systemd/system/` (của distro)
- Dùng cho: nginx, sshd, docker, cron…

Lệnh:
```
sudo systemctl start tên.service
sudo systemctl stop tên.service
sudo systemctl enable tên.service
sudo systemctl disable tên.service
```

### B. User Service (dịch vụ user)
- Chạy khi user login
- Không cần sudo
- File đặt tại:
  - `~/.config/systemd/user/`
- Truy cập được `/run/user/$UID`
- Dùng cho script cá nhân, app nền

Lệnh:
```
systemctl --user start tên.service
systemctl --user stop tên.service
systemctl --user enable tên.service
systemctl --user disable tên.service
```

---

## 3. TẠO FILE SERVICE

### A. Tạo System Service

#### 1. Tạo script
```
sudo nano /usr/local/bin/myjob.sh
```

Nội dung:
```
#!/bin/bash
echo "Hello from system service" >> /tmp/test.log
```

Cho quyền chạy:
```
sudo chmod +x /usr/local/bin/myjob.sh
```

#### 2. Tạo file service
```
sudo nano /etc/systemd/system/myjob.service
```

Nội dung:
```
[Unit]
Description=My system-level job

[Service]
Type=oneshot
ExecStart=/usr/local/bin/myjob.sh

[Install]
WantedBy=multi-user.target
```

---

### B. Tạo User Service (cho /run/user/$UID)

#### 1. Tạo script
```
mkdir -p ~/.local/bin
nano ~/.local/bin/myjob.sh
```

Nội dung:
```
#!/bin/bash
mkdir -p /run/user/$UID/my-runtime
echo "Created runtime dir" >> /tmp/myuserjob.log
```

Cho quyền:
```
chmod +x ~/.local/bin/myjob.sh
```

#### 2. Tạo file service
```
mkdir -p ~/.config/systemd/user
nano ~/.config/systemd/user/myjob.service
```

Nội dung:
```
[Unit]
Description=My user-level job

[Service]
Type=oneshot
ExecStart=%h/.local/bin/myjob.sh

[Install]
WantedBy=default.target
```

---

## 4. CHẠY SERVICE

### System service
```
sudo systemctl daemon-reload
sudo systemctl start myjob.service
sudo systemctl enable myjob.service
```

### User service
```
systemctl --user daemon-reload
systemctl --user start myjob.service
systemctl --user enable myjob.service
```

