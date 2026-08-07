# Linux系统编程与网络编程

> 开始时间：2026-07-25

---

## 更新日志

| 日期 | 章节 | 更新内容 |
|------|------|----------|
| 2026-07-31 | 第33-38章 | 消息队列传文件（作业回顾）、线程基础（pthread_self/pthread_create/线程vs进程对比）、线程数据共享与参数传递（全局/堆/栈、int\*/struct\*/二级指针）、线程退出与等待（pthread_exit/pthread_join/返回值模式）、互斥锁（静态/动态初始化、lock/unlock/trylock/destroy、多线程写文件）、线程清理函数（pthread_cleanup_push/pop、二级指针释放） |
| 2026-07-30 | 第27-31章 | 作业回顾（定时器链表封装、tell一对一聊天）、消息队列（msgget/ftok/msgsnd/msgrcv/msgctl+结构体类型化消息）、共享内存（shmget/shmat/shmdt/shmctl+独立进程读写）、多进程写文件竞争、信号量（semget/semctl/semop+lock/unlock封装+多进程加锁写文件）、IPC资源管理（ipcs/ipcrm）、课后作业 |
| 2026-07-29 | 第21-26章 | 作业回顾（守护进程）、vfork与fork对比、信号（kill/signal/SIG_DFL/SIG_IGN/SIG_ERR、alarm闹钟、setitimer定时器）、exec族函数（6个函数+system+environ）、匿名管道pipe（父子/兄弟进程通讯、SIGPIPE、管道容量64K）、有名管道fifo（mkfifo+access）、课后作业 |
| 2026-07-28 | 第15-20章 | 作业回顾（tree实现、加密解密）、用户管理命令与特殊权限位（SUID/SGID/Sticky）、fork与heap独享性、进程退出8种方式（return/exit/_exit/atexit/abort）、进程等待（wait/waitpid/WIFEXITED/WEXITSTATUS）、孤儿进程/僵尸进程/守护进程、进程组与会话（getpgid/setsid）、资源限制（getrlimit/setrlimit）、课后作业 |、用户管理命令与特殊权限位（SUID/SGID/Sticky）、fork与heap独享性、进程退出8种方式（return/exit/_exit/atexit/abort）、进程等待（wait/waitpid/WIFEXITED/WEXITSTATUS）、孤儿进程/僵尸进程/守护进程、进程组与会话（getpgid/setsid）、资源限制（getrlimit/setrlimit）、课后作业 |
| 2026-07-27 | 第7-14章 | sys IO综合（cp实现、文件类型位运算查表）、用户与组信息（getpwuid/getgrnam/getspnam）、口令加密（crypt）、时间函数（time/ctime/localtime/strftime）、文件系统操作（readlink/mkdir/chmod/chown/link/symlink/chdir/getcwd）、目录操作（opendir/readdir/closedir）、进程基础（fork/getpid/getppid、内存独享性验证）、课后作业 |、用户与组信息（getpwuid/getgrnam/getspnam）、口令加密（crypt）、时间函数（time/ctime/localtime/strftime）、文件系统操作（readlink/mkdir/chmod/chown/link/symlink/chdir/getcwd）、目录操作（opendir/readdir/closedir）、进程基础（fork/getpid/getppid、内存独享性验证）、课后作业 |
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

| 函数 | 作用 | 返回值 |
|------|------|--------|
| `fopen(path, mode)` | 打开文件 | 成功: `FILE*`，失败: `NULL` |
| `fclose(fp)` | 关闭文件 | 成功: `0`，失败: `EOF` |
| `fgetc(fp)` | 读一个字符 | 成功: 字符(转`int`)，失败/EOF: `EOF` |
| `fputc(c, fp)` | 写一个字符 | 成功: 写入的字符，失败: `EOF` |
| `fgets(buf, n, fp)` | 读一行字符串 | 成功: `buf`，失败/EOF: `NULL` |
| `fputs(s, fp)` | 写字符串 | 成功: 非负值，失败: `EOF` |
| `fread(buf, sz, n, fp)` | 按块读 | 成功: 实际读取块数，失败/EOF: `0` |
| `fwrite(buf, sz, n, fp)` | 按块写 | 成功: 实际写入块数，失败: `0` |
| `fprintf(fp, fmt, ...)` | 格式化写 | 成功: 写入字节数，失败: 负值 |
| `fscanf(fp, fmt, ...)` | 格式化读 | 成功: 匹配项数，失败/EOF: `EOF` |
| `fseek(fp, off, whence)` | 文件定位 | 成功: `0`，失败: 非0 |
| `ftell(fp)` | 获取当前位置 | 成功: 偏移量，失败: `-1L` |
| `rewind(fp)` | 回到开头(`fseek(fp,0,SEEK_SET)`) | 无返回值 |
| `perror(msg)` | 打印 errno 对应错误信息 | 无返回值 |

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

**返回值**：
- 成功：`0`
- 失败：`-1`（errno 设置错误码）

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

**返回值**：
- 成功：新的文件偏移量（距文件开头的字节数）
- 失败：`-1`

**技巧**：`lseek(fd, 0, SEEK_END)` 返回文件大小。

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

**返回值**：
- 成功：新的文件描述符
- 失败：`-1`

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

| 指令 | 作用 | 返回值 |
|------|------|--------|
| `F_DUPFD` | 复制文件描述符 | 新 fd |
| `F_GETFL` | 获取文件状态标志 | 标志值 |
| `F_SETFL` | 设置文件状态标志 | `0` |

所有 cmd 失败均返回 `-1`。

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

```c
mode_t umask(mode_t mask);   // 设置文件权限掩码，返回旧 umask 值（总是成功）
```

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

**返回值**：
- 成功：文件描述符（fd）
- 失败：`-1`

---

## 第5章 文件属性

### 5.1 stat / lstat / fstat

```c
int stat(const char *path, struct stat *buf);
int fstat(int fd, struct stat *buf);
int lstat(const char *path, struct stat *buf);
```

**返回值**：成功 `0`，失败 `-1`。

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

## 第7章 sys IO 综合练习

### 7.1 实现 cp 命令

```c
// 01_cp.c — 用 sys IO 实现文件拷贝
int main(int argc, char *argv[])
{
    char buf[1024];
    int fdr, fdw;
    int ret;

    fdr = open(argv[1], O_RDONLY);
    fdw = creat(argv[2], 0777);

    while (1) {
        ret = read(fdr, buf, sizeof(buf));
        if (ret <= 0) break;
        write(fdw, buf, ret);
    }

    close(fdr);
    close(fdw);
    return 0;
}
```

### 7.2 文件类型检测 — 位运算优化

上一章用 `S_ISREG(m)` 等宏逐个判断，本质是 `m & S_IFMT` 与文件类型掩码比较。

**文件类型位掩码**（`st_mode & S_IFMT` 的结果）：

| 宏 | 八进制值 | 右移12位 | 类型 | 查表字符 |
|----|----------|----------|------|----------|
| `S_IFSOCK` | 0140000 | 12 | socket | s |
| `S_IFLNK` | 0120000 | 10 | symlink | l |
| `S_IFREG` | 0100000 | 8 | regular | - |
| `S_IFBLK` | 0060000 | 6 | block | b |
| `S_IFDIR` | 0040000 | 4 | directory | d |
| `S_IFCHR` | 0020000 | 2 | char | c |
| `S_IFIFO` | 0010000 | 1 | FIFO | p |

**查表法一行输出文件类型和权限**：

```c
// 03_stat.c — 优化版
char type[] = " pc d b - l s";  // 索引: 0~7 对应 (mode>>12) & 0xF 后的值
                                 // 索引: 1=p,2=c,3=空格,4=d,5=空格,6=b,7=空格,8=-,9=空格,10=l,11=空格,12=s

char *mode_str[] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};

struct stat s;
stat(argv[1], &s);

// 类型 + 三组权限
printf("%c%s%s%s\n",
    type[(s.st_mode & S_IFMT) >> 12],          // 文件类型
    mode_str[(s.st_mode & S_IRWXU) >> 6],       // owner rwx
    mode_str[(s.st_mode & S_IRWXG) >> 3],       // group rwx
    mode_str[s.st_mode & S_IRWXO]);             // other rwx
```

> 输出示例：`-rwxr-xr-x` 或 `drwx------`

---

## 第8章 用户与组信息管理

### 8.1 /etc/passwd — 用户帐号信息

```c
#include <pwd.h>

struct passwd {
    char   *pw_name;    // 用户名
    char   *pw_passwd;  // 密码（已移至 shadow）
    uid_t   pw_uid;     // 用户 ID
    gid_t   pw_gid;     // 组 ID
    char   *pw_gecos;   // 真实姓名
    char   *pw_dir;     // 家目录
    char   *pw_shell;   // shell 程序
};
```

**API 函数**：

| 函数 | 作用 | 返回值 |
|------|------|--------|
| `getpwuid(uid)` | 通过 UID 获取用户信息 | 成功: `struct passwd*`，失败: `NULL` |
| `getpwnam(name)` | 通过用户名获取用户信息 | 成功: `struct passwd*`，失败: `NULL` |
| `getpwent()` | 循环遍历，每次返回下一项 | 成功: `struct passwd*`，结束/失败: `NULL` |
| `setpwent()` | 重置到文件头 | `void` |
| `endpwent()` | 关闭 passwd 文件 | `void` |

```c
// 04_get_user_info.c — UID→用户名 + 遍历
struct passwd *pw;

// 按 UID 查询
pw = getpwuid(atoi(argv[1]));
printf("name : %s uid : %d shell : %s\n", pw->pw_name, pw->pw_uid, pw->pw_shell);

// 遍历所有用户
while ((pw = getpwent()) != NULL)
    printf("name : %s uid : %d\n", pw->pw_name, pw->pw_uid);

setpwent();  // 回到文件头，可再次遍历
endpwent();
```

```c
// 02_uid_name.c — 通过解析 /etc/passwd 用 UID 反查用户名（纯字符串解析）
fp = fopen(argv[1], "r");
while (fgets(buf, sizeof(buf), fp) != NULL) {
    // /etc/passwd 格式: name:x:UID:GID:...
    if (atoi(strchr(strchr(buf, ':') + 1, ':') + 1) == atoi(argv[2])) {
        *(strchr(buf, ':')) = '\0';   // 截断得到用户名
        printf("%s\n", buf);
    }
}
```

### 8.2 /etc/group — 用户组信息

```c
#include <grp.h>

struct group {
    char   *gr_name;    // 组名
    char   *gr_passwd;  // 组密码
    gid_t   gr_gid;     // 组 ID
    char  **gr_mem;     // 组成员用户名列表（NULL 结尾）
};
```

| 函数 | 作用 | 返回值 |
|------|------|--------|
| `getgrnam(name)` | 通过组名获取组信息 | 成功: `struct group*`，失败: `NULL` |
| `getgrgid(gid)` | 通过 GID 获取组信息 | 成功: `struct group*`，失败: `NULL` |
| `getgrent()` | 循环遍历 | 成功: `struct group*`，结束/失败: `NULL` |
| `setgrent()` | 重置到文件头 | `void` |
| `endgrent()` | 关闭 group 文件 | `void` |

```c
// 05_get_group_info.c — 获取组成员列表
struct group *gr = getgrnam(argv[1]);
for (int i = 0; gr->gr_mem[i] != NULL; i++)
    printf("%s\n", gr->gr_mem[i]);
```

### 8.3 /etc/shadow — 用户密码信息

```c
#include <shadow.h>

struct spwd {
    char *sp_namp;     // 用户名
    char *sp_pwdp;     // 加密后的密码（密文）
    // ... 密码过期相关字段
};
```

| 函数 | 作用 | 返回值 |
|------|------|--------|
| `getspnam(name)` | 通过用户名获取密码信息 | 成功: `struct spwd*`，失败: `NULL` |
| `getspent()` | 循环遍历 | 成功: `struct spwd*`，结束/失败: `NULL` |
| `setspent()` | 重置到文件头 | `void` |
| `endspent()` | 关闭 shadow 文件 | `void` |

```c
// 06_get_passwd_info.c
struct spwd *sp = getspnam(argv[1]);
printf("sp->sp_pwdp : %s\n", sp->sp_pwdp);  // 打印加密密码
```

---

## 第9章 口令加密（crypt）

### 9.1 crypt 函数

```c
// 需定义宏 + 链接 -lcrypt
#define _XOPEN_SOURCE         // 必须放在所有 include 之前
#include <unistd.h>

char *crypt(const char *key, const char *salt);
```

- `key`：用户输入的明文密码
- `salt`：密钥（从 shadow 密文中提取）
- 返回值：成功返回密文（密钥+加密结果），失败返回 `NULL`
- 编译需加 `-lcrypt`

### 9.2 密码验证流程

shadow 中存储的密文格式：`$1$salt$encrypted`，需从中提取 salt。

```c
// 07_crypt.c — 密码验证
#define _XOPEN_SOURCE
#include <shadow.h>

struct spwd *sp = getspnam(argv[1]);
char salt[64], key[64];

// 从 sp->sp_pwdp 提取 salt（"$1$salt$..." → "$1$salt$"）
strcpy(tmp, sp->sp_pwdp);
*(strrchr(tmp, '$') + 1) = '\0';
strcpy(salt, tmp);

// 用户输入 → 加密 → 比对
GETLINES("input key : ", key);
char *passwd = crypt(key, salt);

if (strcmp(sp->sp_pwdp, passwd) == 0)
    printf("login ok!\n");
else
    printf("passwd input error!\n");
```

---

## 第10章 时间函数

### 10.1 基本时间函数

时间起点：**1970-01-01 00:00:00 (UTC)**，`time_t` 表示从此时起的秒数。

```c
#include <time.h>

time_t time(time_t *tloc);   // 参数可为 NULL，返回秒数（同时写入 *tloc）
```

**返回值**：成功返回从 epoch 起的秒数，失败返回 `(time_t)-1`。

```c
time_t t;
t = time(NULL);          // 仅通过返回值获取
// 或 time(&t);          // 同时写入 t
```

### 10.2 函数一览

| 函数 | 作用 | 返回值 |
|------|------|--------|
| `time(&t)` | 获取当前秒数（参数可为 NULL） | 成功: 秒数(`time_t`)，失败: `(time_t)-1` |
| `ctime(&t)` | 秒数 → 字符串（自带换行） | 成功: `char*`（静态缓冲区），失败: `NULL` |
| `ctime_r(&t, buf)` | `ctime` 线程安全版 | 成功: `buf`，失败: `NULL` |
| `gmtime(&t)` | 秒数 → UTC 时间 `struct tm` | 成功: `struct tm*`（静态），失败: `NULL` |
| `gmtime_r(&t, &result)` | `gmtime` 线程安全版 | 成功: `result` 指针，失败: `NULL` |
| `localtime(&t)` | 秒数 → 本地时间 `struct tm` (UTC+8) | 成功: `struct tm*`（静态），失败: `NULL` |
| `localtime_r(&t, &result)` | `localtime` 线程安全版 | 成功: `result` 指针，失败: `NULL` |
| `mktime(&tm)` | `struct tm` → 秒数 | 成功: `time_t`，失败: `(time_t)-1` |
| `asctime(&tm)` | `struct tm` → 字符串 | 成功: `char*`（静态），失败: `NULL` |
| `asctime_r(&tm, buf)` | `asctime` 线程安全版 | 成功: `buf`，失败: `NULL` |

### 10.3 struct tm 结构体

```c
struct tm {
    int tm_sec;    // 秒   (0-59)
    int tm_min;    // 分   (0-59)
    int tm_hour;   // 时   (0-23)
    int tm_mday;   // 日   (1-31)
    int tm_mon;    // 月   (0-11, +1 得实际月份)
    int tm_year;   // 年   (从 1900 起算, +1900 得实际年份)
    int tm_wday;   // 星期 (0=周日)
    int tm_yday;   // 年中第几天
    int tm_isdst;  // 夏令时标志
};
```

```c
// 08_time.c
time_t t;
struct tm *tm;

t = time(NULL);
printf("time : %s\n", ctime(&t));            // 字符串输出

tm = localtime(&t);                           // 本地时间
printf("%d-%d-%d %d:%d:%d\n",
    tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
    tm->tm_hour, tm->tm_min, tm->tm_sec);
```

### 10.4 strftime — 格式化时间

```c
size_t strftime(char *s, size_t max, const char *format, const struct tm *tm);
```

**常用格式符**：

| 格式 | 含义 | 示例 |
|------|------|------|
| `%Y` | 四位年份 | 2026 |
| `%y` | 两位年份 | 26 |
| `%m` | 月份 | 07 |
| `%d` | 日期 | 27 |
| `%H` | 24小时制 | 15 |
| `%M` | 分钟 | 30 |
| `%S` | 秒 | 45 |
| `%w` | 星期几(0=日) | 1 |
| `%D` | = `%m/%d/%y` | 07/27/26 |

```c
// 09_time_format.c
time_t t = time(NULL);
struct tm *tm = localtime(&t);
char buf[1024];

strftime(buf, sizeof(buf), "%Y/%m/%d(%D) %H:%M:%S", tm);
printf("buf : %s\n", buf);  // 输出: 2026/07/27(07/27/26) 15:30:45
```

---

## 第11章 文件系统操作

### 11.1 readlink — 读取符号链接

```c
ssize_t readlink(const char *path, char *buf, size_t bufsiz);
```

读取符号链接指向的目标文件路径，不穿透链接。

**返回值**：成功返回写入 `buf` 的字节数（不含 `\0`），失败 `-1`。

```c
// 10_file_syslink.c
char buf[128];
ret = readlink(argv[1], buf, sizeof(buf));
printf("%s -> %s\n", argv[1], buf);
```

### 11.2 文件和目录操作

| 函数 | 作用 | 返回值 |
|------|------|--------|
| `creat(path, mode)` | 创建文件 | 成功: fd，失败: `-1` |
| `remove(path)` | 删除文件或空目录 | 成功: `0`，失败: `-1` |
| `unlink(path)` | 删除文件 | 成功: `0`，失败: `-1` |
| `mkdir(path, mode)` | 创建目录 | 成功: `0`，失败: `-1` |
| `rmdir(path)` | 删除空目录 | 成功: `0`，失败: `-1` |

### 11.3 权限和属主

```c
int chmod(const char *path, mode_t mode);     // 改变权限
int fchmod(int fd, mode_t mode);              // 通过 fd 改权限

int chown(const char *path, uid_t owner, gid_t group);   // 改属主和属组
int fchown(int fd, uid_t owner, gid_t group);
int lchown(const char *path, uid_t owner, gid_t group);  // 符号链接本身
```

以上所有函数返回值：成功 `0`，失败 `-1`。

```c
// 11_chmod.c
chmod(argv[1], 0777);
// 或使用宏：
chmod(argv[1], S_IRWXU | S_IRWXG | S_IRWXO);
```

```c
// 12_chown.c
chown(argv[1], atoi(argv[2]), atoi(argv[3]));
// 创建用户: useradd   创建组: groupadd
```

### 11.4 硬链接和软链接

```c
int link(const char *oldpath, const char *newpath);     // 创建硬链接
int symlink(const char *oldpath, const char *newpath);  // 创建软链接（符号链接）
```

**返回值**：成功 `0`，失败 `-1`。

| | 硬链接 | 软链接 |
|------|------|------|
| inode | 相同 | 不同 |
| 跨文件系统 | 不行 | 可以 |
| 删除原文件 | 仍可访问 | 断链失效 |
| 指向目录 | 不允许 | 可以 |

### 11.5 工作目录操作

```c
int chdir(const char *path);                 // 切换工作目录，成功 0，失败 -1
int fchdir(int fd);                          // 通过 fd 切换，成功 0，失败 -1

char *getcwd(char *buf, size_t size);        // 获取当前路径，成功返回 buf，失败 NULL
char *getwd(char *buf);                      // 同上（已废弃）
char *get_current_dir_name(void);            // malloc 返回路径，失败 NULL（需 free）
```

```c
// 13_chdir.c — 切换目录并查看
#define _GNU_SOURCE                // get_current_dir_name 需要
printf("pwd : %s\n", get_current_dir_name());
chdir("..");
printf("pwd : %s\n", get_current_dir_name());
printf("pwd : %s\n", getcwd(buf, sizeof(buf)));
```

### 11.6 获取系统信息

```c
#include <sys/utsname.h>
int uname(struct utsname *buf);  // 获取系统名称/版本/架构等信息，成功 0，失败 -1
```

---

## 第12章 目录操作

### 12.1 目录流操作

```c
#include <dirent.h>

DIR *opendir(const char *name);         // 打开目录，成功返回目录流指针，失败 NULL
int closedir(DIR *dirp);                // 关闭目录，成功 0，失败 -1
struct dirent *readdir(DIR *dirp);      // 读取目录项，成功返回 dirent*，结束/失败返回 NULL
```

### 12.2 struct dirent 结构体

```c
struct dirent {
    ino_t          d_ino;       // inode 号
    off_t          d_off;       // 下一项偏移量（上层无需关心）
    unsigned short d_reclen;    // 当前结构体大小
    unsigned char  d_type;      // 文件类型
    char           d_name[256]; // 文件名
};
```

**d_type 类型常量**：

| 宏 | 文件类型 |
|----|----------|
| `DT_REG` | 普通文件 |
| `DT_DIR` | 目录 |
| `DT_CHR` | 字符设备 |
| `DT_BLK` | 块设备 |
| `DT_FIFO` | 命名管道 |
| `DT_LNK` | 符号链接 |
| `DT_SOCK` | socket |
| `DT_UNKNOWN` | 未知 |

```c
// 14_opendir.c — 遍历目录（跳过隐藏文件）
DIR *dir = opendir(argv[1]);
struct dirent *d;

while ((d = readdir(dir)) != NULL) {
    if (d->d_name[0] == '.') continue;  // 跳过 . .. 和隐藏文件
    printf("inode : %d  type : %d  name : %s\n", d->d_ino, d->d_type, d->d_name);
}
closedir(dir);
```

---

## 第13章 进程基础

### 13.1 进程概念回顾

**进程**：一段可执行代码，存放在内存中运行。

| 特性 | 说明 |
|------|------|
| 动态性 | 动态产生、动态消亡 |
| 独享性 | 每个进程的内存空间独立 |
| 并发性 | 多进程竞争 CPU |
| 异步性 | 任一时刻 CPU 只运行一段程序 |

### 13.2 五态模型细化

```
新建态 → 就绪态 → 运行态 → 终止态
              ↕
            挂起态（阻塞态）
```

- **新建态**：建立进程所需资源（进程表项、文件表项、打开文件、缓冲区、分配变量堆栈等）
- **就绪态**：等待 CPU 将程序调入内存
- **运行态**：获得 CPU 资源并在内存中运行
- **挂起态**：因 IO 请求或中断而挂起（阻塞）
- **终止态**：系统回收进程创建时分配的所有资源

### 13.3 ps -aux 进程状态

| 状态 | 含义 |
|------|------|
| D | 不可中断睡眠（通常等待 IO） |
| R | 运行中或可运行 |
| S | 可中断睡眠（等待事件完成） |
| T | 停止（作业控制信号或正在被跟踪） |
| X | 死亡（不应看到） |
| Z | 僵尸进程（已终止但父进程未回收） |
| < | 高优先级 |
| N | 低优先级 |
| s | 会话领导者 |
| l | 多线程 |
| + | 前台进程组 |

### 13.4 获取进程号

```c
#include <unistd.h>

pid_t getpid();   // 获取当前进程 PID
pid_t getppid();  // 获取父进程 PPID
```

```c
// 16_pid.c
printf("pid : %d\n", getpid());
printf("ppid : %d\n", getppid());
```

### 13.5 fork — 创建子进程

```c
pid_t fork(void);
```

**fork 调用一次，返回两次**：

| 返回值 | 含义 |
|--------|------|
| `> 0` | 在父进程中，值为子进程 PID |
| `0` | 在子进程中 |
| `-1` | 失败 |

子进程是父进程的**拷贝**——复制父进程的所有资源（代码、数据、堆栈、打开文件等）。

```c
// 17_fork.c
pid_t ret = fork();

if (ret == -1) {
    printf("fork failed!\n");
} else if (ret == 0) {
    printf("child!  pid = %d  ppid = %d\n", getpid(), getppid());
} else {
    printf("parent! pid = %d  ppid = %d\n", getpid(), getppid());
    printf("parent! ret = %d (child pid)\n", ret);
}
```

### 13.6 父子进程内存独享性验证

**验证1：栈变量**

```c
// 18_stack.c — 父子各自修改栈变量，互不影响
int count = 1122;  // 栈变量

if (fork() == 0) {
    // 子进程
    count = 3344;                           // 子进程修改
    printf("child  : count = %d\n", count); // 3344
} else {
    // 父进程
    printf("parent : count = %d\n", count); // 1122 (不变!)
}
```

**验证2：全局变量（DS段）**

```c
// 19_env.c — 父子各自修改全局变量，互不影响
int e = 12345;  // DS 段（全局变量）

if (fork() == 0) {
    printf("child  e = %d\n", e);  // 12345
    e = 5678;                       // 子进程修改
    printf("child  e = %d\n", e);  // 5678
} else {
    sleep(1);
    printf("parent e = %d\n", e);  // 12345 (不变!)
}
```

> **结论**：fork 后父子进程的内存空间完全独立，各自修改变量互不影响。"拷贝"是写时复制（COW）。

### 13.7 进程间通信（IPC）方式

1. 信号
2. 管道
3. 消息队列
4. 共享内存
5. 信号量
6. 套接字（socket）

---

## 第14章 课后作业

| 序号 | 作业 | 要点 |
|------|------|------|
| 1 | 实现 tree 命令 | 递归遍历目录，缩进打印树形结构（综合 opendir/readdir/stat） |
| 2 | 实现加密解密算法 | 将 "hello" 每字节高4位与低4位交换，实现可逆加密 |

---

## 第15章 作业回顾与用户管理

### 15.1 实现 tree 命令

递归遍历目录树，用 `static int lev` 控制缩进层级，`chdir` 进入子目录。

```c
// 01_tree.c — 递归实现 tree
void my_tree(const char *path)
{
    DIR *dir = NULL;
    struct dirent *d = NULL;
    static int lev = 0;          // 当前层级（static 跨递归保持）

    dir = opendir(path);
    if (dir == NULL) return;

    chdir(path);                 // 进入目标目录

    while ((d = readdir(dir)) != NULL) {
        if (d->d_name[0] == '.') continue;  // 跳过隐藏文件
        for (int i = 0; i < lev; i++)
            printf("|   ");
        printf("|-- %s\n", d->d_name);

        if (d->d_type == DT_DIR) {
            lev++;
            my_tree(d->d_name);  // 递归进入子目录
            lev--;
        }
    }
    chdir("..");                 // 返回上级目录
    closedir(dir);
}
```

### 15.2 加密解密算法

每字节高4位与低4位交换，**加密和解密是同一个操作**（对称可逆）。

```c
// 02_my_crypt.c — 高4位 ↔ 低4位
unsigned char my_crypt(unsigned char old, unsigned char *new)
{
    if (new == NULL)
        return ((old & 0xf0) >> 4) | ((old & 0x0f) << 4);
    else
        *new = ((old & 0xf0) >> 4) | ((old & 0x0f) << 4);
}

// 'h' = 0110 1000 → 密文 = 1000 0110 (再调用一次即解密还原)
```

### 15.3 用户管理命令

| 命令 | 作用 |
|------|------|
| `useradd username` | 添加用户（自动创建同名组） |
| `userdel -r username` | 删除用户（-r 删除家目录） |
| `passwd username` | 设置用户密码 |
| `usermod` | 修改用户信息 |
| `groupadd groupname` | 创建用户组 |
| `gpasswd groupname` | 设置组密码 |

> 未设置密码的用户不能登录。用户帐号 `/etc/passwd`，密码 `/etc/shadow`，组 `/etc/group`，组密码 `/etc/gshadow`。

### 15.4 特殊权限位

| 宏 | 八进制值 | 含义 | 适用 |
|----|----------|------|------|
| `S_ISUID` | 0004000 | Set UID — 其他用户执行时获得属主权限 | 可执行文件 |
| `S_ISGID` | 0002000 | Set GID — 目录内新文件继承目录属组 | 目录 |
| `S_ISVTX` | 0001000 | Sticky — 仅文件所有者可删除自己文件 | 目录（如 /tmp） |

```bash
# SUID: 属主 x → s
chmod u+s filename    # 或 chmod 4755 filename
# SGID: 属组 x → s
chmod g+s dirname     # 或 chmod 2755 dirname
# Sticky: 其他 x → t
chmod o+t dirname     # 或 chmod 1755 dirname
```

---

## 第16章 进程退出

### 16.1 一段程序的结构

一段程序 ≥ 1 个进程，一个进程 ≥ 1 个线程。

### 16.2 进程退出 8 种方式

**5 种正常退出**：

| 方式 | 说明 |
|------|------|
| `return` (from main) | 语言级别，控制权交给调用函数，堆栈返回 |
| `exit(status)` | 系统级别，控制权交给系统，**刷新缓冲区**，做清理 |
| `_exit(status)` / `_Exit(status)` | 系统级别，**不刷新缓冲区**，不做清理 |
| `pthread_exit()` | 最后一个线程调用 |
| 最后一个线程正常响应 | 线程自然结束 |

**3 种异常退出**：

| 方式 | 说明 |
|------|------|
| `abort()` | 发送 `SIGABRT`(6) 信号终止 |
| 接收到信号后默认响应 | 如 `kill(pid, signo)` |
| 最后一个线程取消响应 | 线程被取消 |

### 16.3 return vs exit

| | return | exit |
|------|------|------|
| 性质 | 关键字 | 函数 |
| 级别 | 语言级别 | 系统级别 |
| 控制权 | 交给调用函数 | 交给系统 |
| 资源 | 堆栈返回/释放 | 整个进程空间销毁 |

```c
// 05_return.c — return 只结束当前函数
void test(void) {
    printf("this is test!\n");
    return;     // test() 结束，main 继续
}
// 输出: main start → this is test! → main end

// 06_exit.c — exit 直接结束进程
void test(void) {
    printf("this is test!\n");
    exit(0);    // 整个进程结束
}
// 输出: main start → this is test! （不会打印 main end）
```

### 16.4 exit vs _exit

```c
// 07_exit.c
printf("main start ...");     // 无 \n，数据在缓冲区
exit(0);                       // 会刷新缓冲区 → 输出上面的内容
_exit(0);                      // 不刷新缓冲区 → 上面内容丢失
```

| | exit | _exit |
|------|------|------|
| 刷新缓冲区 | 会 | 不会 |
| 清理工作 | 做（atexit 回调等） | 不做 |

### 16.5 atexit — 退出清理函数

```c
int atexit(void (*function)(void));
```

**返回值**：成功 `0`，失败非 `0`。

注册函数在进程正常退出时自动调用，**注册顺序与执行顺序相反**（栈结构，先注册后执行）。

```c
// 08_atexit.c
atexit(test);     // 3. 最后执行
atexit(hello);    // 2. 第二执行
atexit(world);    // 1. 先执行

// 输出顺序: world! → hello! → 6 => hello world!
```

**应用：释放多级指针**（先释放内层，后释放外层）：

```c
// 09_free.c — 注册顺序 = 申请: 由高到低；执行顺序 = 释放: 由低到高
int **p = NULL;
p = (int **)malloc(sizeof(int *));   // 先申请外层
*p = (int *)malloc(sizeof(int));     // 再申请内层

atexit(free_01);   // free(p)    —— 后注册，后执行
atexit(free_02);   // free(*p)   —— 先注册，先执行（先释放内层）
```

### 16.6 abort — 异常终止

```c
#include <stdlib.h>
void abort(void);   // 发送 SIGABRT(6)，无返回值
```

```c
// 11_abort.c
abort();             // 进程异常终止
printf("world!\n");  // 不会执行
```

### 16.7 kill — 发送信号

```c
#include <signal.h>
int kill(pid_t pid, int sig);
```

**返回值**：成功 `0`，失败 `-1`。

```c
// 12_kill.c — 子进程杀死父进程
if (fork() == 0) {
    kill(getppid(), 6);    // 向父进程发送 SIGABRT
}
```

---

## 第17章 进程等待

### 17.1 wait / waitpid

```c
#include <sys/wait.h>

pid_t wait(int *status);       // 等待任意子进程退出
pid_t waitpid(pid_t pid, int *status, int options);
```

**返回值**：成功返回退出的子进程 PID，失败 `-1`。

**waitpid 的 pid 参数**：

| pid 值 | 等待对象 |
|--------|----------|
| `< -1` | 进程组 ID = `|pid|` 的任意子进程 |
| `-1` | 任意子进程（等同 wait） |
| `0` | 与父进程同组的任意子进程 |
| `> 0` | 指定 PID 的子进程 |

**options**：`0` 阻塞等待，`WNOHANG` 非阻塞。

### 17.2 退出状态宏

| 宏 | 作用 |
|----|------|
| `WIFEXITED(status)` | 正常退出时为真 |
| `WEXITSTATUS(status)` | 获取退出码（低 8 位，0~255） |
| `WIFSIGNALED(status)` | 信号终止时为真 |
| `WTERMSIG(status)` | 获取终止信号编号 |

```c
// 14_wait.c
int status;
wait(&status);

if (WIFEXITED(status))
    printf("正常退出, exit code: %d\n", WEXITSTATUS(status));
if (WIFSIGNALED(status))
    printf("信号终止, signal: %d\n", WTERMSIG(status));
```

### 17.3 等待多个子进程

```c
// 15_mul_fork.c — 创建 10 个子进程，逐一等待
for (i = 0; i < MAX; i++) {
    if (fork() == 0) {
        printf("child: pid = %d ppid = %d\n", getpid(), getppid());
        exit(0);           // 子进程立即退出，防止创建孙子进程
    }
}

for (i = 0; i < MAX; i++)
    wait(NULL);            // 回收 10 个子进程
```

> **关键**：子进程执行完任务后立即 `exit`，否则子进程会继续 `for` 循环创建新进程。

### 17.4 多进程求素数

```c
// 16_prime.c — 10 个进程并行计算 3000~6000 的素数个数
#define NUM 10
#define MIN 3000
#define MAX 6000
#define STEP (MAX - MIN) / NUM

// 每个子进程计算一个区间，结果通过 exit 返回
for (i = 0; i < NUM; i++) {
    if (fork() == 0) {
        exit(count_prime(MIN + i * STEP, MIN + (i + 1) * STEP));
    }
}

// 父进程汇总
for (i = 0; i < NUM; i++) {
    wait(&status);
    if (WIFEXITED(status))
        count += WEXITSTATUS(status);
}
```

> exit 返回值只有低 8 位有效（0~255），如果素数个数超过 255 需要用文件或其他 IPC 方式汇总。

---

## 第18章 进程特殊状态

### 18.1 孤儿进程

父进程先结束，子进程仍在运行 → 子进程变为**孤儿进程**，被 **1 号进程（init）收养**。

```c
// 17_orphan.c
if (fork() == 0) {
    while (1) {
        printf("child: pid = %d ppid = %d\n", getpid(), getppid());
        usleep(100000);
    }
}
// 父进程立即退出，子进程的 ppid 变为 1
```

### 18.2 僵尸进程

子进程运行结束，但父进程忙（未调用 wait 回收）→ 子进程变为**僵尸进程**。

- 僵尸进程只保留进程表项，不占用内存
- 僵尸进程**杀不死**（已经死了，只是没被回收）
- 大量僵尸进程会耗尽 PID 资源

```c
// 18_zombie.c
if (fork() == 0) {
    printf("child: %d\n", getpid());
    exit(0);                  // 子进程退出
}
while (1) usleep(100000);     // 父进程忙，不 wait → 僵尸
```

> `ps aux | grep Z` 可查看僵尸进程。

### 18.3 守护进程（daemon）

一直运行于后台，接收用户指令后执行响应操作。

**6 个创建步骤**：

| 步骤 | 操作 | 目的 |
|------|------|------|
| 1 | fork 并退出父进程 | 子进程变孤儿 |
| 2 | `setsid()` | 创建新会话，摆脱原终端/进程组/会话 |
| 3 | 关闭所有 fd (0~1023) | 释放无用资源 |
| 4 | `chdir("/")` | 切换工作目录到根（防止卸载） |
| 5 | `umask(0)` | 重置权限掩码 |
| 6 | 信号处理 | 接收信号后优雅退出 |

```c
// 19_daemon.c — 手动实现守护进程
if (fork() != 0) exit(0);                    // 1. 创建孤儿进程
setsid();                                    // 2. 创建新会话

for (int i = 0; i < 1024; i++) close(i);     // 3. 关闭文件描述符

chdir("/");                                  // 4. 切换到根目录
umask(0);                                    // 5. 重置 umask

// 6. 守护进程主循环...
```

**系统提供的 daemon 函数**：

```c
#include <unistd.h>
int daemon(int nochdir, int noclose);  // 成功 0，失败 -1
// nochdir=0: 切换到 /
// noclose=0: 关闭所有 fd 并重定向 stdin/stdout/stderr 到 /dev/null
```

```c
// 21_sys_daemon.c — 一行创建守护进程
daemon(0, 0);
```

---

## 第19章 进程组与资源限制

### 19.1 进程组与会话

```c
#include <unistd.h>

// 获取进程组 ID
pid_t getpgid(pid_t pid);      // 获取指定进程的进程组，成功返回 pgid，失败 -1
pid_t getpgrp(void);           // 获取当前进程组，总是成功

// 设置进程组
int setpgid(pid_t pid, pid_t pgid);  // 成功 0，失败 -1

// 会话
pid_t getsid(pid_t pid);            // 获取会话 ID，成功返回 sid，失败 -1
pid_t setsid(void);                 // 创建新会话，成功返回新 sid，失败 -1
```

`sedsid()` 的作用：摆脱原终端、原进程组、原会话的影响。

### 19.2 获取/设置资源限制

```c
#include <sys/time.h>
#include <sys/resource.h>

int getrlimit(int resource, struct rlimit *rlim);
int setrlimit(int resource, const struct rlimit *rlim);
```

**返回值**：成功 `0`，失败 `-1`。

```c
struct rlimit {
    rlim_t rlim_cur;  // 软限制（当前生效值）
    rlim_t rlim_max;  // 硬限制（软限制的上限）
};
```

**常用 resource**：

| 宏 | 含义 |
|----|------|
| `RLIMIT_NOFILE` | 最大打开文件描述符数 |
| `RLIMIT_STACK` | 栈空间大小 |

```c
// 20_getrlimit.c — 查看并修改最大 fd 数
struct rlimit rt;
getrlimit(RLIMIT_NOFILE, &rt);
printf("cur: %d  max: %d\n", rt.rlim_cur, rt.rlim_max);  // 默认 1024

rt.rlim_cur = 3;                         // 限制为 3 个 fd
setrlimit(RLIMIT_NOFILE, &rt);
// 之后最多只能打开 3 个文件（0,1,2 已被占用）
```

---

## 第20章 课后作业

| 序号 | 作业 | 要点 |
|------|------|------|
| 1 | 实现守护进程 | 每秒向文件写一行（含时间戳），写满 100 行后退出 |

---

## 第21章 vfork

### 21.1 作业回顾：守护进程

```c
// 01_daemon.c — daemon + 定时写文件（100行后退出）
int count = 0;
daemon(0, 0);                       // 创建守护进程

fd = creat("/tmp/test", 0644);
while (count < 100) {
    write(fd, "hello\n", 6);
    count++;
    usleep(1000000);                // 1秒
}
close(fd);
```

### 21.2 vfork vs fork

```c
pid_t vfork(void);  // 创建子进程，成功返回同 fork，失败返回 -1
```

| | fork | vfork |
|------|------|-------|
| 内存空间 | **独享**（写时复制 COW） | **共享**父进程地址空间 |
| 执行顺序 | 父子并发，不确定 | 子进程**优先**运行，父进程阻塞 |
| 子进程 return | 可以 | **不能**（会导致父进程崩溃），必须用 `_exit`/`exit` |

```c
// 02_vfork.c — vfork 共享内存验证
int count = 100;

if (vfork() == 0) {
    count = 200;                         // 修改的是父进程的 count!
    printf("child  => count : %d\n", count);  // 200
    exit(0);                             // 必须用 exit!
}
printf("parent => count : %d\n", count);      // 200（被子进程改了!）
```

> vfork 子进程必须调用 `_exit()` 或 `exit()`，调用 `return` 会导致父进程访问已释放的栈帧而崩溃。

---

## 第22章 信号（Signal）

信号是**软中断机制**，用于进程间异步通知。信号默认处理方式都是**终止进程**。

### 22.1 常用信号

`kill -l` 查看所有信号（1~64）。

| 信号 | 编号 | 触发方式 | 默认行为 |
|------|------|----------|----------|
| `SIGHUP` | 1 | Ctrl+\ | 终止 |
| `SIGINT` | 2 | Ctrl+C | 终止 |
| `SIGQUIT` | 3 | Ctrl+\\ | 终止+core dump |
| `SIGABRT` | 6 | `abort()` | 终止+core dump |
| `SIGKILL` | 9 | `kill -9` | **不可捕捉/忽略** |
| `SIGALRM` | 14 | `alarm()` 超时 | 终止 |
| `SIGPIPE` | 13 | 管道读端关闭时写 | 终止 |
| `SIGSTOP` | 19 | | **不可捕捉/忽略**（暂停） |

### 22.2 kill — 发送信号

```c
#include <signal.h>

int kill(pid_t pid, int sig);
```

**返回值**：成功 `0`，失败 `-1`。

```c
// 03_kill.c
kill(pid, SIGKILL);    // 杀死指定进程
kill(pid, SIGINT);     // 发送 Ctrl+C
kill(getpid(), signo); // 给自己发信号
```

### 22.3 signal — 捕捉/设置信号处理

```c
typedef void (*sighandler_t)(int);

sighandler_t signal(int signum, sighandler_t handler);
```

| handler 值 | 含义 |
|------------|------|
| `SIG_DFL` | 恢复默认处理 |
| `SIG_IGN` | 忽略信号 |
| 自定义函数 `void func(int sig)` | 信号到达时回调 |

**返回值**：成功返回**前一个**处理函数的地址，失败返回 `SIG_ERR`。

```c
// 04_signal.c — 捕捉 SIGINT (Ctrl+C)
void hello(int sig) {
    printf("hello! sig=%d\n", sig);
}

signal(SIGINT, hello);   // 注册自定义处理 → Ctrl+C 不再终止
// 5秒后恢复默认
sleep(5);
signal(SIGINT, SIG_DFL); // 恢复默认 → Ctrl+C 终止
```

### 22.4 哪些信号不可改变

```c
// 05_check.c — 遍历 1~64，signal 返回 SIG_ERR 的即不可捕捉
for (i = 1; i <= 64; i++) {
    if (signal(i, SIG_DFL) == SIG_ERR)
        printf("%d ", i);     // 9(SIGKILL) 和 19(SIGSTOP) 不可改变
}
```

### 22.5 alarm — 闹钟信号

```c
unsigned int alarm(unsigned int seconds);
```

`seconds` 秒后向进程发送 `SIGALRM`。若参数为 `0` 则取消之前的闹钟。**返回值**：前一个闹钟的剩余秒数。

```c
// 06_alarm.c — 循环闹钟
void dididi(int sig) {
    printf("sig : %d didi...\n", sig);
    alarm(1);                 // 重新定闹钟（循环）
}

signal(SIGALRM, dididi);
alarm(3);                     // 3秒后第一次触发

while (count--)
    pause();                  // 暂停等待任意信号，收到信号后返回
```

> `pause()` 使进程休眠，直到收到一个信号。

### 22.6 setitimer — 精确定时器

```c
#include <sys/time.h>

int getitimer(int which, struct itimerval *curr_value);
int setitimer(int which, const struct itimerval *new_value, struct itimerval *old_value);
```

**返回值**：成功 `0`，失败 `-1`。

**which 定时器类型**：

| 宏 | 信号 | 计时方式 |
|----|------|----------|
| `ITIMER_REAL` | `SIGALRM`(14) | 真实时间（wall clock），可 sleep 等待 |
| `ITIMER_VIRTUAL` | `SIGVTALRM`(26) | 用户态 CPU 时间，必须**轮询** |
| `ITIMER_PROF` | `SIGPROF`(27) | 用户态+内核态 CPU 时间，必须轮询 |

```c
struct itimerval {
    struct timeval it_interval;  // 循环间隔时间
    struct timeval it_value;     // 第一次触发时间
};

struct timeval {
    long tv_sec;                 // 秒
    long tv_usec;                // 微秒（1/1000 秒）
};
```

```c
// 07_setitimer.c — 机器时间定时器（可 sleep）
struct itimerval it;
signal(SIGALRM, didi);                 // 捕捉闹钟信号

it.it_value.tv_sec = 3;                // 3秒后第一次触发
it.it_value.tv_usec = 100;
it.it_interval.tv_sec = 0;             // 之后每 0.1 秒循环
it.it_interval.tv_usec = 100000;

setitimer(ITIMER_REAL, &it, NULL);
getchar();                             // sleep 方式等待
```

```c
// 08_mul_setitimer.c — 同时使用 ITIMER_REAL + ITIMER_VIRTUAL
signal(SIGALRM, didi);                 // ITIMER_REAL → SIGALRM
signal(SIGVTALRM, world);              // ITIMER_VIRTUAL → SIGVTALRM

// 定时器1: 真实时间，每1秒
it.it_interval.tv_sec = 1;
setitimer(ITIMER_REAL, &it, NULL);

// 定时器2: 用户态时间，每2秒
it1.it_interval.tv_sec = 2;
setitimer(ITIMER_VIRTUAL, &it1, NULL);

while (1);                             // 必须轮询（VIRTUAL 不能 sleep）
```

> `ITIMER_VIRTUAL` 和 `ITIMER_PROF` 必须用 `while(1)` 轮询，不能用 sleep/getchar 等待。

---

## 第23章 exec 族函数

exec 族函数用新程序**替换**当前进程映像（PID 不变），**不创建新进程**。

### 23.1 system — 执行 shell 命令

```c
#include <stdlib.h>
int system(const char *command);  // 内部 fork+exec，返回命令状态
```

```c
// exec/01_demo.c
system("clear");
system("ls -l -a");
// system 会阻塞等待命令执行完毕
```

### 23.2 环境变量

```c
extern char **environ;   // 全局环境变量指针

// 或通过 main 第三个参数获取
int main(int argc, char *argv[], char **env);
```

```c
// exec/03_env.c — 遍历环境变量
int main(int argc, char *argv[], char **env) {
    for (int i = 0; env[i] != NULL; i++)
        printf("%s\n", env[i]);    // 输出所有 NAME=VALUE
}
```

### 23.3 exec 6 个函数

```c
#include <unistd.h>

// l = list（可变参数）, v = vector（数组）, p = PATH 搜索, e = 自定义环境
int execl(const char *path, const char *arg, ..., NULL);
int execlp(const char *file, const char *arg, ..., NULL);
int execle(const char *path, const char *arg, ..., NULL, char *const envp[]);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execve(const char *filename, char *const argv[], char *const envp[]);
```

**命名规则**：

| 后缀 | 含义 |
|------|------|
| `l` | 参数用可变参数列表（list），`NULL` 结尾 |
| `v` | 参数用字符串数组（vector） |
| `p` | 从 `PATH` 环境变量搜索可执行文件 |
| `e` | 可指定自定义环境变量数组 |

**返回值**：只有失败才返回 `-1`（成功则进程被替换，不会返回）。

```c
// exec/04_exec.c — 6 种调用对比
execl("/bin/ls", "ls", "-l", "-a", "-i", NULL);
execlp("ls", "ls", "-l", "-a", "-i", NULL);     // 从 PATH 搜索
execle("/bin/ls", "ls", "-l", "-a", "-i", NULL, env);
execv("/bin/ls", ar);                            // ar = {"ls", "-l", "-a", "-i", NULL}
execvp("ls", ar);
execve("/bin/ls", ar, env);                      // 最底层，其余5个都是对它的封装
```

**exec 的重要特点**：
- 替换整个进程映像，**exec 之后的代码不会执行**（除非 exec 失败）
- PID 不变，PPID 不变，继承原进程的 fd（除非设置了 FD_CLOEXEC）

### 23.4 自定义环境变量

```c
// exec/06_my_env.c — 父进程传递自定义环境变量给子程序
char *my_ar[] = {"hello", "world", "123", "test", NULL};
char *my_env[] = {"name=tom", "id=100086", "sex=F", NULL};

execve("/path/to/program", my_ar, my_env);
```

```c
// exec/05_access_ar_env.c — 子程序读取 argc/argv/env
for (i = 0; i < argc; i++)
    printf("argv[%d] = %s\n", i, argv[i]);

for (i = 0; env[i] != NULL; i++)
    printf("%s\n", env[i]);
```

### 23.5 管道 + exec 综合：cat /etc/passwd | grep root

```c
// exec/07_cmd.c — 兄弟进程通过管道 + exec 实现 shell 管道
int fd[2];
pipe(fd);

if (fork() == 0) {
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);          // 标准输出 → 管道写端
    execlp("cat", "cat", "/etc/passwd", NULL);
    exit(0);
}

close(fd[1]);
wait(NULL);
dup2(fd[0], STDIN_FILENO);               // 标准输入 → 管道读端
execlp("grep", "grep", "root", NULL);
```

---

## 第24章 匿名管道（pipe）

### 24.1 通讯模式

| 模式 | 说明 |
|------|------|
| 单工 | 管道只能读或只能写 |
| **半双工** | 一端固定读、另一端固定写（匿名/有名管道都是半双工） |
| 全双工 | 一端既可读也可写 |

### 24.2 匿名管道

只能用于**父子进程**或**兄弟进程**之间通讯。

```c
#include <unistd.h>

int pipe(int pipefd[2]);
```

- `pipefd[0]`：读端
- `pipefd[1]`：写端
- **返回值**：成功 `0`，失败 `-1`

```c
// pipe/01_creat.c — 创建并查看 fd
int fd[2];
pipe(fd);
printf("fd[0] : %d  fd[1] : %d\n", fd[0], fd[1]);  // 如 fd[0]=3, fd[1]=4
```

### 24.3 基本读写

```c
// pipe/02_write.c — 写端写入
write(fd[1], "hello", 5);

// pipe/03_read.c — 读端读取
char buf[128];
read(fd[0], buf, sizeof(buf));
printf("buf : %s\n", buf);
```

### 24.4 父子进程管道通讯

```c
// pipe/04_fork.c — 子进程写 → 父进程读
pipe(fd);

if (fork() == 0) {
    close(fd[0]);                  // 子进程关闭读端
    write(fd[1], "hello", 5);      // 写入
    close(fd[1]);
    exit(0);
}

wait(NULL);
close(fd[1]);                      // 父进程关闭写端
read(fd[0], buf, sizeof(buf));     // 读取
```

### 24.5 管道容量

匿名管道一次最多写入 **64KB** 数据。

```c
// pipe/05_size.c — 测试管道最大容量
while (1) {
    ret = write(fd[1], buf, sizeof(buf));
    count++;
    printf("count : %d\n", count);
    // 写满 64KB 后 write 阻塞
}
```

### 24.6 SIGPIPE — 管道异常信号

如果管道读端关闭，写端继续写入 → 触发 `SIGPIPE`(13)。

```c
// pipe/06_signal.c — 捕捉 SIGPIPE
signal(SIGPIPE, hello);

if (fork() == 0) {
    exit(0);                       // 子进程退出，管道的读端随之关闭
}

close(fd[0]);                      // 父进程也关读端
sleep(1);
write(fd[1], "hello", 6);         // 读端不存在 → SIGPIPE
```

### 24.7 兄弟进程通讯：cat /etc/passwd | grep root

```c
// pipe/my_pipe.c — 两个子进程通过管道通讯
pipe(fd);

// 第一个子进程：执行 cat，输出重定向到管道写端
if (fork() == 0) {
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    execl("/bin/cat", "cat", "/etc/passwd", NULL);
    exit(0);
}

// 第二个子进程：执行 grep，输入重定向到管道读端
if (fork() == 0) {
    dup2(fd[0], STDIN_FILENO);
    close(fd[1]);
    execl("/bin/grep", "grep", "root", NULL);
    exit(0);
}

// 父进程关闭两端，等待所有子进程
close(fd[0]); close(fd[1]);
wait(NULL); wait(NULL);
```

---

## 第25章 有名管道（FIFO）

有名管道通过**管道文件**通讯，可实现**任意进程**之间的通讯。

### 25.1 通讯流程

1. 创建管道文件（`mkfifo`）
2. 判断文件是否存在（`access`）
3. 打开文件（`open`）
4. 读写（`read`/`write`）
5. 关闭（`close`）

### 25.2 access — 检查文件存在/权限

```c
#include <unistd.h>
int access(const char *pathname, int mode);
```

| mode | 含义 |
|------|------|
| `F_OK` | 检查文件是否存在 |
| `R_OK` | 检查读权限 |
| `W_OK` | 检查写权限 |
| `X_OK` | 检查执行权限 |

**返回值**：成功 `0`，失败 `-1`。

### 25.3 mkfifo — 创建有名管道

```c
#include <sys/stat.h>
int mkfifo(const char *pathname, mode_t mode);
```

**返回值**：成功 `0`，失败 `-1`。如果文件已存在则创建失败。

```c
// fifo/01_creat.c — 先判断再创建
if (access(argv[1], F_OK) != 0) {
    mkfifo(argv[1], 0644);           // 文件不存在才创建
}
```

### 25.4 同一进程读写

```c
// fifo/02_data.c — 同进程内通过 FIFO 读写
fd = open(argv[1], O_RDWR);

if (fork() == 0) {
    write(fd, "hello", 6);           // 子进程写
    exit(0);
}
wait(NULL);
read(fd, buf, sizeof(buf));          // 父进程读
printf("buf : %s\n", buf);

close(fd);
unlink(argv[1]);                     // 删除管道文件
```

### 25.5 独立进程通讯（send / recv）

**发送端**：

```c
// fifo/03_send.c
fd = open(argv[1], O_RDWR);
while (1) {
    GETLINES("input send data : ", buf);
    write(fd, buf, strlen(buf) + 1);
    if (strcmp(buf, "exit") == 0) break;
}
close(fd);
unlink(argv[1]);
```

**接收端**：

```c
// fifo/04_recv.c
fd = open(argv[1], O_RDWR);
while (1) {
    read(fd, buf, sizeof(buf));
    printf("message : %s\n", buf);
    if (strcmp(buf, "exit") == 0) break;
}
close(fd);
unlink(argv[1]);
```

> 两个进程分别运行，通过同一个 FIFO 文件通讯。FIFO 是**半双工**模式，固定一端读一端写。

---

## 第26章 课后作业

| 序号 | 作业 | 要点 |
|------|------|------|
| 1 | 封装定时器（链表） | `struct timer_t` 含 time/count_time/data/回调函数指针，用链表管理多个定时任务 |
| 2 | 一对一聊天（tell） | 用 FIFO 实现两个进程互相收发消息 |

---

## 第27章 作业回顾

### 27.1 定时器链表封装

利用 `setitimer` + 链表实现多个定时任务管理。

**数据结构**：

```c
// 01_timer.c — 定时器节点
typedef void (PRI)(void *);

struct timer_t {
    int time;             // 定时器定时间隔
    int count_time;       // 累加计数器
    PRI *print;           // 回调函数指针
    void *data;           // 回调参数
    int flag;             // 0=循环, 1=一次性

    struct timer_t *next;
    struct timer_t *prev;
};

// 双向循环链表头
struct timer_t head = {.next = &head, .prev = &head};
```

**核心逻辑**：

```c
// 添加定时器（尾插）
void add_timer(int time, PRI *func, void *data, int flag) {
    struct timer_t *new = malloc(sizeof(struct timer_t));
    new->time = time;  new->count_time = 0;
    new->print = func; new->data = data;  new->flag = flag;
    // 尾插入双向循环链表
    new->next = &head;  new->prev = head.prev;
    head.prev->next = new;  head.prev = new;
}

// 信号回调：遍历链表，count_time++，等于 time 时触发
void travel(int sig) {
    struct timer_t *tail, *save;
    for (tail = head.next; tail != &head; tail = save) {
        save = tail->next;
        tail->count_time++;
        if (tail->count_time == tail->time) {
            tail->print(tail->data);
            tail->count_time = 0;
            if (tail->flag) {           // 一次性 → 删除节点
                tail->next->prev = tail->prev;
                tail->prev->next = tail->next;
                free(tail);
            }
        }
    }
}

// 初始化：signal + setitimer
void init_timer(int t) {
    signal(SIGALRM, travel);
    struct itimerval it;
    it.it_value.tv_sec = 2;
    it.it_interval.tv_sec = t;       // 每秒检查一次
    setitimer(ITIMER_REAL, &it, NULL);
}
```

### 27.2 tell — 一对一聊天

利用**两个 FIFO** 实现全双工通讯（zhangsan ↔ lisi）：

| 管道 | 方向 |
|------|------|
| `./ztol` | zhangsan → lisi |
| `./ltoz` | lisi → zhangsan |

每个程序用 `fork` 分出读子进程和写父进程，用 VT 码控制光标位置：

```c
// 02_tell/zhangsan.c 核心结构
fdw = open("./ztol", O_RDWR);    // zhangsan 写端
fdr = open("./ltoz", O_RDWR);    // zhangsan 读端

if (fork() == 0) {
    // 子进程：收 lisi 消息
    while (1) {
        read(fdr, buf, sizeof(buf));
        printf("\033[%d;10Hlisi : \033[K%s\033[u", OUTPUT, buf);
    }
}
// 父进程：发消息
while (1) {
    printf("\033[%d;10Hzhangsan : \033[K\033[s", INPUT);
    fgets(buf, sizeof(buf), stdin);
    write(fdw, buf, strlen(buf) + 1);
    if (!strcmp(buf, "goodbye")) break;
}
```

---

## 第28章 消息队列（Message Queue）

### 28.1 IPC 资源管理

```bash
ipcs -q           # 查看消息队列
ipcs -m           # 查看共享内存
ipcs -s           # 查看信号量

ipcrm -q msgid    # 删除消息队列（或 ipcrm -Q key）
ipcrm -m shmid    # 删除共享内存（或 ipcrm -M key）
ipcrm -s semid    # 删除信号量（或 ipcrm -S key）
```

### 28.2 ftok — 生成 IPC key

```c
#include <sys/ipc.h>

key_t ftok(const char *pathname, int proj_id);
```

**返回值**：成功返回 key，失败 `-1`。

**key 生成规则（32bit）**：

```
key = (proj_id 低8位) << 24 | 0x02 << 16 | (inode 低16位)
```

```c
// 03_msg/02_ftok.c — 验证 key 生成
key = ftok(argv[1], 123);

stat(argv[1], &s);
num = (123 << 24) | (0x2 << 16) | (s.st_ino & 0xffff);
// num == key
```

### 28.3 msgget — 创建/获取消息队列

```c
#include <sys/msg.h>

int msgget(key_t key, int msgflg);
```

| 参数 | 说明 |
|------|------|
| `key` | `ftok()` 返回值或 `IPC_PRIVATE` |
| `msgflg` | `IPC_CREAT`（不存在则创建）或 `IPC_CREAT \| IPC_EXCL`（存在则报错） |

**返回值**：成功返回消息队列 ID，失败 `-1`。

```c
// 03_msg/01_creat.c
int msgid = msgget(123, IPC_CREAT);       // 直接用数字 key
int msgid = msgget(ftok(".", 123), IPC_CREAT);  // 用 ftok
```

### 28.4 msgsnd — 发送消息

```c
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
```

| 参数 | 说明 |
|------|------|
| `msqid` | 消息队列 ID |
| `msgp` | 发送数据地址 |
| `msgsz` | 数据大小（字节） |
| `msgflg` | `0` 阻塞，`IPC_NOWAIT` 非阻塞 |

**返回值**：成功 `0`，失败 `-1`。

```c
// 03_msg/03_send.c
char buf[128];
GETLINES("input send string : ", buf);
msgsnd(msgid, buf, strlen(buf) + 1, 0);
```

### 28.5 msgrcv — 接收消息

```c
ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
```

| 参数 | 说明 |
|------|------|
| `msgtyp` | `0` 不关心类型（队列方式），`> 0` 指定类型 |
| `msgflg` | `0` 阻塞等待 |

**返回值**：成功返回实际读取字节数，失败 `-1`。

```c
// 03_msg/04_recv.c
char buf[128];
msgrcv(msgid, buf, sizeof(buf), 0, 0);    // 不区分类型
printf("buf : %s\n", buf);
```

### 28.6 msgctl — 消息队列控制

```c
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
```

| cmd | 作用 |
|-----|------|
| `IPC_STAT` | 获取消息队列属性 |
| `IPC_SET` | 修改消息队列属性 |
| `IPC_RMID` | **删除消息队列** |

**返回值**：成功 `0`，失败 `-1`。

```c
// 03_msg/05_msgctl.c
msgctl(msgid, IPC_RMID, 0);    // 删除消息队列
```

### 28.7 结构体类型化消息

消息可以带类型（`long type`），接收时按类型筛选：

```c
// 03_msg/struct/data.h
struct cls_t {
    long type;               // 必须！消息类型（> 0）
    char name[64];
    char sex;
    int id;
};

struct tea_t {
    long type;               // 必须！消息类型
    int age;
    char name[64];
};
```

```c
// send.c — 发送（type 区分学生/老师）
struct cls_t cls = {1, "tom", 'M', 10086};
struct tea_t tea = {2, 40, "laozhang"};

msgsnd(msgid, &cls, sizeof(cls), 0);
msgsnd(msgid, &tea, sizeof(tea), 0);
```

```c
// recv.c — 按类型接收
if (atoi(argv[1]) == 1)
    msgrcv(msgid, &cls, sizeof(cls), 1, 0);    // 只要学生
else
    msgrcv(msgid, &tea, sizeof(tea), 2, 0);    // 只要老师
```

> 消息结构体第一个成员必须是 `long type`，且值必须 > 0。

---

## 第29章 共享内存（Shared Memory）

### 29.1 操作流程

```
ftok → shmget(创建) → shmat(映射到进程) → 读写 → shmdt(解映射) → shmctl(IPC_RMID 销毁)
```

### 29.2 shmget — 创建共享内存

```c
#include <sys/shm.h>

int shmget(key_t key, size_t size, int shmflg);
```

| 参数 | 说明 |
|------|------|
| `key` | `ftok()` 返回值 |
| `size` | 共享内存大小（字节），内核按 PAGE_SIZE 向上取整 |
| `shmflg` | `IPC_CREAT`，可 `|` 权限（如 `0666`） |

**返回值**：成功返回共享内存 ID，失败 `-1`。

```c
// 04_shm/01_creat.c
key_t key = ftok(".", 0x55);
int shmid = shmget(key, 1024, IPC_CREAT);
```

### 29.3 shmat — 映射到进程

```c
void *shmat(int shmid, const void *shmaddr, int shmflg);
```

| 参数 | 说明 |
|------|------|
| `shmaddr` | 指定映射地址，`NULL` 由系统选择 |
| `shmflg` | `0` 可读可写，`SHM_RDONLY` 只读 |

**返回值**：成功返回进程中的映射地址，失败 `(void *)-1`。

```c
// 04_shm/02_shmat.c
char *mem = shmat(shmid, NULL, 0);    // 返回可读可写地址
```

### 29.4 读写数据

共享内存映射后，像普通内存一样直接读写：

```c
// 04_shm/03_data.c — 写入 + 读出
strcpy(mem, "hello");                  // 写入共享内存
printf("mem : %s\n", mem);             // 读取
```

### 29.5 shmdt — 解映射

```c
int shmdt(const void *shmaddr);
```

**返回值**：成功 `0`，失败 `-1`。

```c
// 04_shm/04_shmdt.c
shmdt(mem);    // 解映射后不能再访问 mem
```

### 29.6 shmctl — 共享内存控制/销毁

```c
int shmctl(int shmid, int cmd, struct shmid_ds *buf);
```

| cmd | 作用 |
|-----|------|
| `IPC_STAT` | 获取共享内存属性 |
| `IPC_SET` | 修改共享内存属性 |
| `IPC_RMID` | **删除共享内存** |

**返回值**：成功 `0`，失败 `-1`。

```c
// 04_shm/05_shmctl.c
shmctl(shmid, IPC_RMID, 0);
```

### 29.7 独立进程共享内存通讯

两个进程通过同样的 `ftok` + `shmget` 获取同一个共享内存：

```c
// 04_shm/string/write.c — 写进程
shmid = shmget(ftok(".", 0x55), 1024, IPC_CREAT);
mem = shmat(shmid, NULL, 0);
strcpy(mem, buf);                     // 写入

// 04_shm/string/read.c — 读进程
shmid = shmget(ftok(".", 0x55), 1024, IPC_CREAT);
mem = shmat(shmid, NULL, 0);
printf("buf : %s\n", mem);            // 读出
```

> 共享内存不提供同步机制，需要配合**信号量**实现互斥。

---

## 第30章 多进程文件竞争

### 30.1 问题演示

10 个进程同时向同一文件写入 → 数据**交叉覆盖**，文件内容错乱：

```c
// 05_mul_file.c — 10 个进程同时写文件（无锁）
void do_work(int fd) {
    char buf[128] = "hello world\n";
    for (int line = LINE; line > 0; line--) {
        for (int i = 0; i < strlen(buf); i++)
            write(fd, &buf[i], 1);     // 逐字符写 → 易被打断!
    }
}

for (i = 0; i < MAX; i++) {
    if (fork() == 0) { do_work(fd); exit(0); }
}
```

---

## 第31章 信号量（Semaphore）

信号量是**进程间的锁**，用于保护共享资源的互斥访问，本身不传输数据。

### 31.1 semget — 创建信号量

```c
#include <sys/sem.h>

int semget(key_t key, int nsems, int semflg);
```

| 参数 | 说明 |
|------|------|
| `key` | `ftok()` 返回值 |
| `nsems` | 信号量个数（通常 1 把锁） |
| `semflg` | `IPC_CREAT` |

**返回值**：成功返回信号量 ID，失败 `-1`。

```c
// 06_sem/01_creat.c
key_t key = ftok(".", 0x66);
int semid = semget(key, 1, IPC_CREAT);    // 创建 1 把锁
```

### 31.2 semctl — 初始化/控制

```c
int semctl(int semid, int semnum, int cmd, ...);
```

| 参数 | 说明 |
|------|------|
| `semid` | 信号量 ID |
| `semnum` | 锁索引号（从 0 开始） |
| `cmd` | `SETVAL` 设值，`IPC_RMID` 删除 |

**返回值**：成功 `0`，失败 `-1`。

```c
// 06_sem/02_init.c — 初始化锁为打开状态
int val = 1;                                      // 正数 = 打开
semctl(semid, 0, SETVAL, val);                    // 初始化第 0 号锁
```

### 31.3 semop — 加锁/解锁

```c
int semop(int semid, struct sembuf *sops, unsigned nsops);
```

```c
struct sembuf {
    unsigned short sem_num;    // 锁索引号
    short          sem_op;     // 负数=加锁(P操作), 正数=解锁(V操作)
    short          sem_flg;    // 0 阻塞，IPC_NOWAIT 非阻塞
};
```

**返回值**：成功 `0`，失败 `-1`。

### 31.4 lock/unlock 封装

```c
// 06_sem/03_sem_lock_unlock.c — 封装加锁/解锁
int lock(int semid, int num) {
    struct sembuf op;
    op.sem_num = num;
    op.sem_op = -1;            // P 操作：信号量 -1（如已是 0 则阻塞等待）
    op.sem_flg = 0;
    return semop(semid, &op, 1);
}

int unlock(int semid, int num) {
    struct sembuf op;
    op.sem_num = num;
    op.sem_op = 1;             // V 操作：信号量 +1（唤醒等待者）
    op.sem_flg = 0;
    return semop(semid, &op, 1);
}
```

### 31.5 多进程加锁写文件

```c
// 06_sem/04_mul_file.c — 信号量保护多进程写文件
void do_work(int fd, int semid) {
    lock(semid, 0);                      // 加锁（其他进程阻塞等待）
    // ... 写文件（临界区）...
    unlock(semid, 0);                    // 解锁
}

// main:
int semid = init_sem();                  // 创建 + 初始化

for (i = 0; i < MAX; i++) {
    if (fork() == 0) {
        do_work(fd, semid);
        exit(0);
    }
}
```

> **注意**：不可重复加锁（已持有锁的进程再次 lock 会死锁）。

### 31.6 独立模块化

```c
// 06_sem/05_sem.c — 信号量初始化封装为独立函数
int init_sem(void) {
    key_t key = ftok(".", 0x66);
    int semid = semget(key, 1, IPC_CREAT);
    semctl(semid, 0, SETVAL, 1);         // 初始化为打开
    return semid;
}
```

---

## 第32章 课后作业

| 序号 | 作业 | 要点 |
|------|------|------|
| 1 | 消息队列实现文件发送和接收 | 读取文件内容 → msgsnd 分段发送 → msgrcv 接收 → 写入新文件 |
| 2 | 信号量锁模块化 | 锁实现作为独立子文件（`.c/.h`），文件操作作为主文件调用 lock/unlock |

---

---
## 第33章 消息队列传文件（作业回顾）

### 33.1 设计思路

用消息队列实现文件传输：发送端逐字节读取文件 → `msgsnd` 发送 → 接收端 `msgrcv` 逐字节接收 → 输出。

```
发送端(send.c)          消息队列          接收端(recv.c)
   |                      |                    |
   |-- read(fd, &ch, 1) ->|                    |
   |-- msgsnd(msgid, &ch, 1, 0) -->|           |
   |                       |-- msgrcv(msgid, &ch, 1, 0, IPC_NOWAIT) -->|
   |                       |                    |-- putchar(ch)
```

### 33.2 公共头文件 data.h

```c
#ifndef __DATA_H__
#define __DATA_H__

struct cls_t {
    long type;
    char name[64];
    char sex;
    int id;
};

struct tea_t {
    long type;
    int age;
    char name[64];
};

#endif
```

### 33.3 发送端 send.c

```c
// 01_file/send.c
key = ftok(".", 123);
msgid = msgget(key, IPC_CREAT);

fd = open(argv[1], O_RDONLY);

while (1) {
    ret = read(fd, &ch, 1);
    if (ret == 0) break;              // 文件读完

    ret = msgsnd(msgid, &ch, 1, 0);   // 逐字节发送
    if (ret == -1) break;
}
```

### 33.4 接收端 recv.c

```c
// 01_file/recv.c
key = ftok(".", 123);
msgid = msgget(key, IPC_CREAT);

while (1) {
    ret = msgrcv(msgid, &ch, 1, 0, IPC_NOWAIT);  // 非阻塞接收
    if (ret != 1) break;

    putchar(ch);
    fflush(NULL);                     // 立即刷新输出
}
```

> 接收端使用 `IPC_NOWAIT` 非阻塞模式，消息队列为空时返回 `-1` 退出循环。

### 33.5 Makefile

```makefile
all:
    gcc send.c -o send
    gcc recv.c -o recv
clean:
    rm send recv -rf
```

---

## 第34章 线程基础

### 34.1 什么是线程

线程是一段可执行代码在内存中运行，识别线程的唯一标识是**线程号**。

```
进程 = 资源管理的最小单位
线程 = 执行流的最小单位

一个程序 ≥ 一个进程 ≥ 一个线程
```

### 34.2 进程与线程对比

| 维度 | 进程 | 线程 |
|------|------|------|
| **执行效率** | 低（切换有时间开销） | 高（切换几乎无开销） |
| **数据安全** | 高（一个进程异常不影响其他） | 低（一个线程异常，整个进程崩溃） |
| **资源** | 独立地址空间 | 共享进程地址空间 |
| **创建/销毁** | 开销大 | 开销小 |

**结论**：追求效率用线程，追求安全用进程。

### 34.3 线程特性

| 特性 | 说明 |
|------|------|
| **动态性** | 线程生命周期：创建 → 就绪 → 运行 → 阻塞 → 终止 |
| **共享性** | 同一进程的线程共享内存和资源 |
| **并发性** | 多个线程可以同时运行（时间片轮转） |
| **异步性** | 线程以不可预知的速度向前推进 |

### 34.4 pthread_self — 获取线程号

```c
#include <pthread.h>

pthread_t pthread_self(void);
typedef unsigned long int pthread_t;    // %lu 打印
```

**返回值**：当前线程的线程号。

```c
// 02_pthread.c
printf("pthid : %lu\n", pthread_self());    // 线程号
printf("pid  : %d\n", getpid());            // 进程号（同进程内相同）
```

> 编译链接时需加 `-pthread`。

### 34.5 pthread_create — 创建线程

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine)(void *), void *arg);
```

| 参数 | 说明 |
|------|------|
| `thread` | 输出：保存新创建线程的线程号 |
| `attr` | 线程属性，`NULL` 表示默认属性 |
| `start_routine` | 线程执行函数，**返回类型必须是 `void *`，参数必须是 `void *`** |
| `arg` | 传递给线程执行函数的参数 |

**返回值**：成功 `0`，失败返回错误号（非零）。

```c
// 03_creat.c
void *hello(void *data) {
    printf("pthid : %lu  pid : %d\n", pthread_self(), getpid());
    return NULL;
}

int main(void) {
    pthread_t pthid;
    pthread_create(&pthid, NULL, hello, NULL);
    pthread_join(pthid, NULL);    // 等待线程结束
    return 0;
}
```

---

## 第35章 线程数据共享与参数传递

### 35.1 数据共享规则

| 内存区域 | 是否共享 | 说明 |
|----------|----------|------|
| **全局变量（DS 段）** | ✅ 共享 | 所有线程访问同一变量 |
| **堆（malloc）** | ✅ 共享 | 只要有指针就能访问 |
| **栈（局部变量）** | ❌ 独享 | 每个线程有独立栈空间 |

```c
// 04_val.c — 验证共享性
int global = 100;                        // DS 段：所有线程共享

void *hello(void *data) {
    int *heap = malloc(sizeof(int));     // 堆：每个线程有自己的堆变量
    *heap = 200;

    printf("global : %d\n", global);     // 共享，都是 100
    printf("heap   : %d\n", *heap);      // 各自独立的堆数据
    // 局部变量在栈上，各自独立
}
```

### 35.2 参数传递 — int 指针

```c
// 05_arg.c — 通过 int* 传参，线程修改后主线程可见
void *hello(void *data) {
    int *p = (int *)data;
    *p = 100;                            // 修改指向的值
    return NULL;
}

int main(void) {
    int a = 10;
    pthread_t pthid;
    pthread_create(&pthid, NULL, hello, &a);
    pthread_join(pthid, NULL);
    printf("a : %d\n", a);               // 输出 100（被线程修改）
}
```

### 35.3 参数传递 — 结构体指针

```c
// 06_struct.c — 必须传结构体地址，不能强转值
struct cls_t cls;
cls.a = 10;

// 正确：
pthread_create(&pthid, NULL, hello, &cls);      // 传地址

// 错误（编译警告）：
pthread_create(&pthid, NULL, hello, (void *)cls.a);  // 不能将值当指针
```

> `void *` 是 8 字节指针，不能将 4 字节 int 或结构体值强转为指针传递。必须传地址。

### 35.4 参数传递 — 二级指针（线程内 malloc）

```c
// 08_malloc.c — 线程分配内存，主线程使用
void *hello(void *data) {
    struct cls_t **cls = (struct cls_t **)data;
    *cls = malloc(sizeof(struct cls_t));  // 线程内 malloc
    (*cls)->id = 10086;
    return NULL;
}

int main(void) {
    struct cls_t *cls = NULL;
    pthread_t pthid;

    pthread_create(&pthid, NULL, hello, &cls);  // 传二级指针
    pthread_join(pthid, NULL);

    printf("id : %d\n", cls->id);         // 主线程访问线程 malloc 的内存
    free(cls);
}
```

> 通过二级指针，线程可以给主线程"返回"一个 malloc 出来的内存。

### 35.5 多线程异常演示

```c
// 09_mul_pthread.c — 10 个线程，第 5 个 abort
for (i = 0; i < 10; i++)
    pthread_create(&pthid[i], NULL, hello, NULL);

// hello 中：第 5 个线程调用 abort() → 整个进程终止
```

```c
// 10_mul_process.c — 10 个进程，第 5 个 abort
for (i = 0; i < 10; i++) {
    if (fork() == 0) {
        if (i == 5) abort();             // 只有第 5 个进程终止
    }
}
```

> 对比验证：线程不安全（一个 abort 全部死），进程安全（一个 abort 不影响其他）。

---

## 第36章 线程退出与等待

### 36.1 pthread_exit — 线程退出

```c
void pthread_exit(void *retval);
```

| 参数 | 说明 |
|------|------|
| `retval` | 线程执行函数的返回值，可被 `pthread_join` 获取 |

```c
// 11_exit_join.c
void *hello(void *data) {
    printf("thread running ...\n");
    pthread_exit(NULL);          // 退出当前线程
    printf("never run\n");       // 不会执行
}

int main(void) {
    pthread_t pthid;
    pthread_create(&pthid, NULL, hello, NULL);
    pthread_join(pthid, NULL);   // 等待线程结束
    printf("main end\n");
}
```

### 36.2 pthread_join — 线程等待

```c
int pthread_join(pthread_t thread, void **retval);
```

| 参数 | 说明 |
|------|------|
| `thread` | 要等待的线程号 |
| `retval` | 输出：保存线程 `pthread_exit` 的返回值 |

**返回值**：成功 `0`，失败返回错误号（非零）。

### 36.3 线程返回值模式

```c
// 12_exit_ret.c — 三种安全的返回值方式
void *hello(void *data) {
    static int a = 100;                  // 方式1：static 变量（生命周期全局）
    int *p = malloc(sizeof(int));        // 方式2：malloc 堆内存（需 free）
    *p = 200;

    // pthread_exit(&a);                 // 安全：static 不随函数结束销毁
    // pthread_exit(p);                  // 安全：堆内存，调用者 free
    // pthread_exit(&data);              // 危险：局部变量地址，函数结束即无效
}

int main(void) {
    void *ret;
    pthread_join(pthid, &ret);
    printf("ret : %d\n", *(int *)ret);   // 读取线程返回值
}
```

> 不能返回线程函数**局部变量**的地址，函数结束后栈内存无效。

### 36.4 线程与 fork 交互

```c
// 13_pthread_pro_relation.c — 线程中调用 fork
void *hello(void *data) {
    pid_t pid = fork();
    if (pid == 0) {
        // 子进程：仅继承调用 fork 的那个线程
        printf("child pid : %d\n", getpid());
    }
}
```

> `fork` 后子进程只包含调用 `fork` 的那个线程，其他线程在子进程中消失。

---

## 第37章 互斥锁（Mutex）

### 37.1 问题引入

10 个线程各写 1000 行到同一文件 → 不加锁时数据混乱/丢失：

```c
// 不加锁：10线程 × 1000行 = 预期10000行，实际可能只有9000+
// 因为 write 不是原子操作，多个线程同时写会互相覆盖
```

### 37.2 静态锁初始化

```c
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
```

### 37.3 动态锁初始化与销毁

```c
int pthread_mutex_init(pthread_mutex_t *restrict mutex,
                       const pthread_mutexattr_t *restrict attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
```

| 参数 | 说明 |
|------|------|
| `mutex` | 锁变量地址 |
| `attr` | 锁属性，`NULL` 表示快速互斥锁（默认） |

**返回值**：成功 `0`，失败返回错误号。

### 37.4 加锁与解锁

```c
int pthread_mutex_lock(pthread_mutex_t *mutex);       // 加锁（阻塞等待）
int pthread_mutex_trylock(pthread_mutex_t *mutex);     // 尝试加锁（非阻塞）
int pthread_mutex_unlock(pthread_mutex_t *mutex);      // 解锁
```

**返回值**：成功 `0`，失败返回错误号。

### 37.5 多线程加锁写文件

```c
// 14_mul_file.c — 10 线程 + 互斥锁写文件，数据完整
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *func(void *data) {
    int fd = (int)data;
    int i = 0;

    pthread_mutex_lock(&mutex);          // 加锁：进入临界区

    while (1) {
        if (i == 1000) {
            pthread_mutex_unlock(&mutex);// 解锁：离开临界区
            pthread_exit(NULL);
        }

        snprintf(buf, sizeof(buf), "pthid : %lu pid : %d line : %d\n",
                 pthread_self(), getpid(), i);
        write(fd, buf, strlen(buf));
        i++;
    }

    pthread_mutex_unlock(&mutex);        // 解锁
    pthread_exit(NULL);
}
```

> **注意**：互斥锁不可重复加锁（同一个线程连续 lock 两次会死锁）。  
> **对比**：信号量用于多进程，互斥锁用于多线程。

---

## 第38章 线程清理函数

### 38.1 pthread_cleanup_push — 注册清理函数

```c
void pthread_cleanup_push(void (*routine)(void *), void *arg);
void pthread_cleanup_pop(int execute);
```

| 参数 | 说明 |
|------|------|
| `routine` | 清理时要执行的函数指针 |
| `arg` | 传递给清理函数的参数 |
| `execute` | `0` 不执行清理函数，**非零** 执行 |

### 38.2 三条重要规则

1. **注册顺序与执行顺序相反**（栈结构：先注册后执行）
2. **push 和 pop 必须一一对应**（编译器强制检查）
3. **清理函数是否执行取决于 pop 的参数和代码位置**

### 38.3 基本用法

```c
// 15_clean.c
void hello(void *data) {
    printf("hello! a = %d\n", *(int *)data);
}
void world(void *data) {
    printf("world!\n");
}

int main(void) {
    int a = 10;

    pthread_cleanup_push(hello, &a);     // 先注册
    pthread_cleanup_push(world, NULL);   // 后注册

    printf("=================\n");

    pthread_cleanup_pop(1);              // 先执行（后注册的先执行）→ world!
    pthread_cleanup_pop(1);              // 后执行（先注册的后执行）→ hello! a = 10
}
```

输出：
```
main start ...
=================
world!
hello! a = 10
main end ...
```

### 38.4 二级指针释放模式

```c
// 16_free.c — 清理函数用于 free 二级指针
void hello(void *data) {
    free(data);                          // 释放外层指针（int **）
}
void world(void *data) {
    free(data);                          // 释放内层指针（int *）
}

int main(void) {
    int **p = malloc(sizeof(int *));     // 外层
    *p = malloc(sizeof(int));            // 内层

    pthread_cleanup_push(hello, p);      // 先注册：释放 p
    pthread_cleanup_push(world, *p);     // 后注册：释放 *p（内层先释放）

    pthread_cleanup_pop(1);              // 先执行 world → free(*p)
    pthread_cleanup_pop(1);              // 后执行 hello → free(p)
}
```

> 释放顺序与分配顺序相反：先释放内层 `*p`，再释放外层 `p`。与注册顺序一致。

---

## 本章小结

```
Linux系统编程概述  ████████████████████
sys IO 读写       ████████████████████
文件描述符/重定向  ████████████████████
文件权限/umask    ████████████████████
stat/文件属性     ████████████████████
文件系统操作      ████████████████████
目录操作          ████████████████████
进程基础/fork     ████████████████████
进程退出机制      ████████████████████
进程等待/wait     ████████████████████
孤儿/僵尸/守护    ████████████████████
进程组/资源限制   ████████████████████
信号/signal       ████████████████████
定时器/alarm      ████████████████████
exec 族函数       ████████████████████
匿名管道 pipe     ████████████████████
有名管道 fifo     ████████████████████
消息队列 msg      ████████████████████
共享内存 shm      ████████████████████
信号量 sem        ████████████████████
线程基础          ████████████████████
数据共享/参数传递 ████████████████████
线程退出/等待     ████████████████████
互斥锁 mutex      ████████████████████
线程清理函数      ████████████████████
```
