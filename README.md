# Nachos-project
Đồ án 1 của môn Hệ điều hành

## Cách hoạt động nhóm
- Tạo branch mới để code
- Push và merge khi thêm một syscall mới (xử lý conflict nếu có)

## Các file cần thay đổi khi thêm một syscall
* userprog/exception.cc
* userprog/syscall.h
* userprog/ksyscall.h
* test/start.S
* test/Makefile

## Lệnh cần thiết để tạo một system call (ở root của repo)
```
cd NachOS-4.0
cd code/build.linux
make depend
make
cd ../../coff2noff
make
cd ../code/test
make
cd ..
build.linux/nachos -x test/<file-test>

```

