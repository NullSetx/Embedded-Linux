# Linux系统编程与网络编程

> 开始时间：2026-07-25

---

## 更新日志

| 日期 | 章节 | 更新内容 |
|------|------|----------|
| 2026-07-25 | 第1-6章 | 新建笔记：系统编程概述、标准IO回顾、sys IO（open/close/read/write/lseek）、文件描述符与dup/dup2/fcntl、非阻塞IO、文件权限与umask、stat/lstat文件属性、文件类型检测、课后作业 |

---

## 课程结构

| 模块 | 内容 | 天数 |
|------|------|------|
| sys IO | 文件IO | 2天 |
| 进程/线程 | 进程管理、多线程 | 4天 |
| TCP/UDP | 网络编程 | 2天 |
| 项目 | 综合实践 | 2天 |

---

## 第1章 系统编程概述

### 1.1 什么是系统编程

系统编程（sys）就是 kernel 给上层用户提供可编程接口，用户通过这些接口操作 kernel。

Linux 是类 Unix 操作系统，核心就是 **kernel**。

### 1.2 Kernel 五大子系统

| 子系统 | 功能 |
|--------|------|
| **文件系统** | 将硬盘/U盘抽象成文件系统（驱动），方便用户访问 |
| **内存管理** | 虚拟内存（4G）、物理内存（DDR）、页表映射 |
| **进程管理** | 进程创建/调度/销毁、五态模型 |
| **设备驱动** | 硬件设备抽象 |
| **网络协议** | TCP/UDP |

### 1.3 虚拟内存布局

```
4G 虚拟内存空间
├── 0-3G : 用户空间 (user)
│   ├── stack  : 局部变量、临时变量、调用函数分配空间
│   ├── heap   : 动态内存 malloc/calloc/realloc → free
│   │            valgrind ./a.out  检测内存泄漏
│   ├── DS     : 已初始化全局变量和静态变量 (data segment)
│   ├── BSS    : 未初始化全局变量和静态变量
│   ├── RO     : 只读数据段
│   ├── const  : 常量
│   └── code   : 代码段（.text）
│
└── 3-4G : 内核空间 (kernel)
```

**页表存储机制**：把虚拟内存映射到物理内存（DDR）上。

```c
// 01_env_val.c — 变量在内存中的位置
int a = 1;    // BSS 段（未初始化/零值）
int b = 123;  // RO 段（已初始化）

int main(int argc, char *argv[])
{
    printf("a : %d\n", a);
    return 0;
}
```

const 修饰的局部变量是"伪常量"，可以通过指针修改：

```c
// 02_const.c
const int e = 123;  // 全局 const，不可修改

int main(int argc, char *argv[])
{
    const int a = 10;          // 局部 const = 伪常量
    *((int *)&a) = 20;         // 通过指针绕过 const 修改
    printf("a : %d\n", a);     // 输出 20
    return 0;
}
```

### 1.4 进程管理基础

**进程**：一段可执行程序，必须放在内存中运行。

| 特性 | 说明 |
|------|------|
| **动态性** | 动态产生、动态消亡 |
| **独享性** | 每个进程的内存空间独立 |
| **并发性** | 多个进程竞争 CPU 资源 |
| **异步性** | 某一时刻 CPU 只能运行一段程序 |

- 进程唯一标识：**PID**（进程号）
- 进程由父进程创建，祖先进程 = **1号进程（init）**
- 所有进程都由 1 号进程直接或间接创建

**五态模型**：

```
新建态 → 就绪态 → 运行态 → 终止态
              ↕
            挂起态
```

**进程间通信（IPC）六种方式**：

1. 信号
2. 管道
3. 消息队列
4. 共享内存
5. 信号量
6. 套接字（socket）

---

## 第2章 标准IO回顾

C 标准库文件操作 → sys IO 的映射关系：

### 2.1 标准IO函数速查

| 函数 | 作用 |
|------|------|
| `fopen(path, mode)` | 打开文件 |
| `fclose(fp)` | 关闭文件 |
| `fgetc/fputc` | 字符读写 |
| `fgets/fputs` | 字符串读写 |
| `fread/fwrite` | 按块读写（二进制：size 参数有效） |
| `fprintf/fscanf` | 格式化读写 |
| `fseek/ftell/rewind` | 文件定位 |
| `perror/errno/strerror` | 错误处理 |

### 2.2 mode 映射表

| C 标准 mode | sys IO flags |
|-------------|--------------|
| `r` | `O_RDONLY` |
| `r+` | `O_RDWR` |
| `w` | `O_WRONLY \| O_CREAT \| O_TRUNC` |
| `w+` | `O_RDWR \| O_CREAT \| O_TRUNC` |
| `a` | `O_WRONLY \| O_CREAT \| O_APPEND` |
| `a+` | `O_RDWR \| O_CREAT \| O_APPEND` |

`b` 后缀（rb/wb/ab）表示二进制模式，`fread/fwrite` 的 size 参数生效。

---

## 第3章 系统IO（sys IO）

### 3.1 头文件与公共宏

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// share.h 中的调试宏
#define ERRP(con, info, ret) do {              \
    if (con) {                                 \
        printf(#info " error Line:%d File:%s\n", __LINE__, __FILE__); \
        ret;                                   \
    }                                          \
} while(0)

#define PRI_D(val) printf(#val ": %d\n", val)
#define PRI_O(val) printf(#val ": %#o\n", val)
```

### 3.2 open — 打开文件

```c
int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
```

| 参数 | 说明 |
|------|------|
| `pathname` | 文件路径（绝对/相对） |
| `flags` | 打开标志位 |
| `mode` | 创建文件时的权限（仅 O_CREAT 时有效） |

**flags 标志位**：

| 标志 | 含义 |
|------|------|
| `O_RDONLY` | 只读（文件不存在则失败，存在则从头读） |
| `O_WRONLY` | 只写 |
| `O_RDWR` | 可读可写 |
| `O_APPEND` | 追加 |
| `O_CREAT` | 文件不存在则创建 |
| `O_TRUNC` | 打开时清空文件 |
| `O_NONBLOCK` | 非阻塞模式 |

**返回值**：
- 成功：文件描述符（fd），遵循**未使用最小 fd** 原则
- 失败：-1

```c
// 03_open.c — 只读打开
fd = open(argv[1], O_RDONLY);
ERRP(fd == -1, open, goto ERR1);
printf("fd : %d\n", fd);
close(fd);
```

### 3.3 close — 关闭文件

```c
int close(int fd);
```

### 3.4 标准文件描述符

| fd | 宏 | 含义 |
|----|-----|------|
| 0 | `STDIN_FILENO` | 标准输入（键盘） |
| 1 | `STDOUT_FILENO` | 标准输出（屏幕） |
| 2 | `STDERR_FILENO` | 标准错误 |

### 3.5 read — 读数据

```c
ssize_t read(int fd, void *buf, size_t count);
```

| 参数 | 说明 |
|------|------|
| `fd` | 文件描述符 |
| `buf` | 存储数据的缓冲区地址 |
| `count` | 缓冲区大小 |

**返回值**：
- 成功：实际读取的字节数
- 0：文件结尾（EOF）
- -1：失败

```c
// 04_read.c — 只读打开后尝试写（会失败）
fd = open(argv[1], O_RDONLY);
ERRP(fd == -1, open, goto ERR1);

ret = write(fd, &ch, 1);  // 以只读方式打开，写操作失败
```

### 3.6 write — 写数据

```c
ssize_t write(int fd, const void *buf, size_t count);
```

**返回值**：
- 成功：实际写入的字节数
- -1：失败

```c
// 05_write.c — 创建并写入
fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC);
ERRP(-1 == fd, open, goto ERR1);

ch = 'A';
ERRP(write(fd, &ch, 1) != 1, write, goto ERR2);
close(fd);
```

```c
// 06_append.c — 追加模式
fd = open(argv[1], O_RDWR | O_CREAT | O_APPEND);
ERRP(-1 == fd, open, goto ERR1);

write(fd, &ch, 1);  // 数据追加到文件末尾
```

### 3.7 最大文件描述符测试

进程默认最大打开文件数 = 1024（0~1023）。

```c
// 07_max_fd.c — 测试最大fd
while (1) {
    fd = open(argv[1], O_RDONLY);
    if (fd == -1) break;
    printf("fd : %d\n", fd);
}
```

### 3.8 lseek — 文件定位

```c
off_t lseek(int fd, off_t offset, int whence);
```

| whence 值 | 含义 |
|-----------|------|
| `SEEK_SET` | 从文件开头偏移 |
| `SEEK_CUR` | 从当前位置偏移 |
| `SEEK_END` | 从文件末尾偏移 |

**技巧**：`lseek(fd, 0, SEEK_END)` 可获取文件大小。

```c
// 08_lseek.c — lseek 基本用法
lseek(fd, 0, SEEK_SET);  // 回到文件开头
// ...
printf("size : %d\n", lseek(fd, 0, SEEK_END));  // 获取文件大小
```

```c
// 09_loop_read.c — 循环读取 + 文件大小
char buf[64];

for (i = 0; i < 5; i++) {
    bzero(buf, sizeof(buf));
    read(fd, buf, sizeof(buf));
    printf("buf : %s\n", buf);
    lseek(fd, 0, SEEK_SET);  // 每次读取后回到开头
}
printf("size : %d\n", lseek(fd, 0, SEEK_END));
```

### 3.9 文件描述符共享（dup/dup2）

多个 fd 指向同一个文件，共享偏移量。

```c
int dup(int oldfd);
int dup2(int oldfd, int newfd);
```

- `dup`：复制 fd，返回新的最小可用 fd
- `dup2`：将 newfd 指向 oldfd（若 newfd 已打开则先关闭）

```c
// 10_mul_user_file.c — dup/dup2 示例
fd1 = open("./test", O_WRONLY | O_CREAT | O_TRUNC);
write(fd1, "hello", 5);        // 写入 "hello"

fd2 = dup2(fd1, 1);            // fd2(=1, stdout) 也指向 test 文件
write(fd2, "world", 5);        // "world" 写入 test 文件（不是屏幕！）

// 结果：test 文件内容为 "helloworld"
```

**dup2 实现重定向**：

```c
// 11_changle_dircent.c — 重定向
fd = open("./test", O_WRONLY | O_CREAT | O_APPEND);
close(1);                          // 关闭 stdout
fd1 = fcntl(fd, F_DUPFD, 1);      // 将 fd 复制到 1（stdout）

write(1, "test", 4);              // 本该输出到屏幕，实际写入 test 文件
printf("hello\n");                 // 同样写入 test 文件
```

### 3.10 fcntl — 文件控制

```c
int fcntl(int fd, int cmd, ... /* arg */);
```

**cmd 指令**：

| 指令 | 作用 |
|------|------|
| `F_DUPFD` | 复制文件描述符（同 dup） |
| `F_GETFL` | 获取文件状态标志 |
| `F_SETFL` | 设置文件状态标志 |

`F_DUPFD` 第三个参数指定起始 fd 号：`fcntl(fd, F_DUPFD, 88)` ≈ `dup2(fd, 88)`。

### 3.11 非阻塞IO

默认情况下键盘输入是阻塞的。通过 `fcntl` + `O_NONBLOCK` 取消阻塞：

```c
// 12_input.c — 取消键盘阻塞
void cancel_block(int fd)
{
    int flag;

    flag = fcntl(fd, F_GETFL);     // 获取当前标志（默认可读可写）
    printf("flag : %#o\n", flag);

    flag |= O_NONBLOCK;            // 添加非阻塞标志
    fcntl(fd, F_SETFL, flag);
}

int main(int argc, char *argv[])
{
    char name[64] = "tom";

    cancel_block(0);               // 取消 stdin 阻塞

    while (1) {
        printf("%s\n", name);      // 不等待输入，高速循环
        scanf("%s", name);         // 无输入时不会阻塞
    }
    return 0;
}
```

---

## 第4章 文件权限

### 4.1 umask

创建文件时的实际权限 = `mode & ~umask`

```
mode  = 111 111 111  (0777)
umask = 000 010 010  (0022, 默认)
      & 111 101 101  = 0755 = rwxr-xr-x
```

```c
// 13_touch.c — 创建文件并指定权限
umask(0);  // 先清零 umask，让权限完全由 mode 决定

fd = open(argv[1], O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
// S_IRWXU = 00700, S_IRWXG = 00070, S_IRWXO = 00007
// 最终权限 = 0777 & ~0 = 0777
```

### 4.2 权限数字对照

| 数字 | 权限 | 数字 | 权限 |
|------|------|------|------|
| 7 | rwx | 3 | -wx |
| 6 | rw- | 2 | -w- |
| 5 | r-x | 1 | --x |
| 4 | r-- | 0 | --- |

### 4.3 creat 函数

```c
int creat(const char *pathname, mode_t mode);
```

等价于：`open(pathname, O_CREAT | O_WRONLY | O_TRUNC, mode)`

---

## 第5章 文件属性

### 5.1 stat / lstat / fstat

```c
int stat(const char *path, struct stat *buf);
int fstat(int fd, struct stat *buf);
int lstat(const char *path, struct stat *buf);
```

| 函数 | 区别 |
|------|------|
| `stat` | 获取文件属性，符号链接则穿透 |
| `lstat` | 获取文件属性，符号链接返回链接自身信息 |
| `fstat` | 通过 fd 获取文件属性 |

### 5.2 struct stat 结构体

```c
struct stat {
    dev_t     st_dev;     // 包含文件的设备 ID
    ino_t     st_ino;     // inode 号（文件唯一标识）
    mode_t    st_mode;    // 文件权限和类型
    nlink_t   st_nlink;   // 硬链接数
    uid_t     st_uid;     // 所有者 UID
    gid_t     st_gid;     // 所有者 GID
    dev_t     st_rdev;    // 设备 ID（特殊文件）
    off_t     st_size;    // 文件大小（字节）
    blksize_t st_blksize; // 文件系统 IO 块大小
    blkcnt_t  st_blocks;  // 分配的 512B 块数量
    time_t    st_atime;   // 最后访问时间
    time_t    st_mtime;   // 最后修改时间
    time_t    st_ctime;   // 最后状态变更时间
};
```

```c
// 14_stat.c — 获取并打印所有属性
struct stat s;
stat(argv[1], &s);

PRI_D(s.st_dev);     // 设备ID
PRI_D(s.st_ino);     // inode号
PRI_O(s.st_mode);    // 权限（八进制）
PRI_D(s.st_nlink);   // 硬链接数
PRI_D(s.st_uid);     // 用户UID
PRI_D(s.st_gid);     // 用户组GID
PRI_D(s.st_size);    // 文件大小
PRI_D(s.st_atime);   // 最后访问时间
PRI_D(s.st_mtime);   // 最后修改时间
PRI_D(s.st_ctime);   // 最后状态变更时间
```

### 5.3 文件类型检测宏

| 宏 | 文件类型 |
|----|----------|
| `S_ISREG(m)` | 普通文件 |
| `S_ISDIR(m)` | 目录 |
| `S_ISCHR(m)` | 字符设备 |
| `S_ISBLK(m)` | 块设备 |
| `S_ISFIFO(m)` | 管道（FIFO） |
| `S_ISLNK(m)` | 符号链接 |
| `S_ISSOCK(m)` | 套接字 |

### 5.4 权限位检测

| 宏 | 含义 |
|----|------|
| `S_IRUSR` | 所有者读 |
| `S_IWUSR` | 所有者写 |
| `S_IXUSR` | 所有者执行 |
| `S_IRGRP` | 组读 |
| `S_IWGRP` | 组写 |
| `S_IXGRP` | 组执行 |
| `S_IROTH` | 其他读 |
| `S_IWOTH` | 其他写 |
| `S_IXOTH` | 其他执行 |

```c
// 15_file_type.c — 模拟 ls -l 第一列（文件类型 + 所有者权限）
struct stat s;
lstat(argv[1], &s);
mode_t m = s.st_mode;

// 文件类型
if (S_ISREG(m))      putchar('-');
else if (S_ISDIR(m)) putchar('d');
else if (S_ISCHR(m)) putchar('c');
else if (S_ISBLK(m)) putchar('b');
else if (S_ISFIFO(m))putchar('p');
else if (S_ISLNK(m)) putchar('l');
else if (S_ISSOCK(m))putchar('s');

// 所有者权限
if ((m & S_IRUSR) == S_IRUSR) putchar('r'); else putchar('-');
if ((m & S_IWUSR) == S_IWUSR) putchar('w'); else putchar('-');
if ((m & S_IXUSR) == S_IXUSR) putchar('x'); else putchar('-');

putchar('\n');
```

---

## 第6章 课后作业

| 序号 | 作业 | 要点 |
|------|------|------|
| 1 | 用 sys IO 实现 cp 命令 | `open + read + write + close` |
| 2 | UID → 用户名转换 | 读取 `/etc/passwd` 解析用户信息 |
| 3 | GID → 组名转换 | 读取 `/etc/group` 解析组信息 |
| 4 | 实现 `ll filename` | 综合 stat + 文件类型 + 权限位 + UID/GID 转换 |

---

## 本章小结

```
Linux系统编程概述  ████████████████████
标准IO回顾        ████████████████████
sys IO 读写       ████████████████████
文件描述符/重定向  ████████████████████
fcntl/非阻塞IO    ████████████████████
文件权限/umask    ████████████████████
stat/文件属性     ████████████████████
文件类型检测      ████████████████████
```
