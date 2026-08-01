# Linux网络编程

> 开始时间：2026-07-31

---

## 更新日志

| 日期 | 章节 | 更新内容 |
|------|------|----------|
| 2026-08-01 | 第3-8章 | TCP/IP基础（IP地址/IPv4-IPv6/ARP-RARP/回环地址/网卡配置/ping）、TCP三次握手与四次挥手、Socket编程基础（socket/connect/bind/listen/accept+字节序转换htonl-htons-ntohl-ntohs+IP地址转换inet_addr-inet_ntoa）、TCP数据传输（send/recv/字符串传输）、多进程并发服务器（fork+accept）、TCP文件传输（文本文件/大视频文件+usleep流控）、课后作业（tell聊天、端口扫描） |
| 2026-07-31 | 第1-2章 | 新建笔记：OSI七层参考模型（物理层/数据链路层/网络层/传输层）、TCP/IP四层模型、大小端模式、以太网帧格式（64-1518字节）、TCP vs UDP对比、课后作业（奇偶校验） |

---

## 课程结构

| 模块 | 内容 | 天数 |
|------|------|------|
| TCP/UDP | 网络编程 | 2天 |
| 项目 | 综合实践 | 2天 |

---

## 第1章 网络编程概述

### 1.1 OSI 七层参考模型

| 层号 | 名称 | 设备 | 核心功能 | 数据单位 |
|------|------|------|----------|----------|
| 7 | **应用层** | — | 用户与网络的接口 | 数据段 |
| 6 | **表示层** | — | 加密/解密、压缩/解压缩 | 数据段 |
| 5 | **会话层** | — | 建立、管理、终止会话 | 数据段 |
| 4 | **传输层** | — | 端到端通讯（TCP/UDP） | 数据包 |
| 3 | **网络层** | 路由器 | 地址翻译、协议转换、路由选择 | 数据帧 |
| 2 | **数据链路层** | 交换机 | 自动寻址、数据有效性检测 | 比特流 |
| 1 | **物理层** | 集线器 | 信号放大、扩展物理接口 | 比特流 |

#### 物理层 — 集线器

- 信号放大
- 扩展网络物理接口
- 确保比特流（0/1）在物理线路上的传输

#### 数据链路层 — 交换机

具备自动寻址能力和交换作用。

**数据有效性检测：**

| 方法 | 原理 |
|------|------|
| **奇偶校验** | 统计数据中 1 的个数是奇数还是偶数 |
| **和校验** | 将数据累加，看结果是 0 还是 1 |

#### 网络层 — 路由器

具有地址翻译、协议转换和数据格式转换等功能。

### 1.2 TCP/IP 四层模型

| TCP/IP 层 | 对应 OSI 层 | 数据单位 |
|-----------|-------------|----------|
| **应用层** | 应用层 + 表示层 + 会话层 | 数据段 |
| **传输层** | 传输层 | 数据包 |
| **网络层（Internet）** | 网络层 | 数据帧 |
| **主机到网络** | 数据链路层 + 物理层 | 比特流 |

### 1.3 大小端模式

| 模式 | 规则 | 常见 CPU |
|------|------|----------|
| **大端模式** | 高字节存低地址，低字节存高地址 | 网络字节序（统一使用） |
| **小端模式** | 高字节存高地址，低字节存低地址 | x86/ARM（多数） |

> 网络通讯统一使用**大端模式**（网络字节序）。

### 1.4 以太网帧格式

```
Ethernet II 帧结构：
┌──────────┬──────────┬──────────┬──────────┬──────────┐
│ 目的MAC  │ 源MAC    │ 类型     │ 数据     │ CRC校验  │
│ 6 字节   │ 6 字节   │ 2 字节   │ 46~1500  │ 4 字节   │
└──────────┴──────────┴──────────┴──────────┴──────────┘

最小帧长：64 字节（6+6+2+46+4）
最大帧长：1518 字节（6+6+2+1500+4）
```

**MAC 地址**：48 比特 = 6 字节
- 前 3 字节：IEEE 分配给厂商的厂商代码
- 后 3 字节：网络适配器编号

### 1.5 TCP vs UDP

| 特性 | TCP | UDP |
|------|-----|-----|
| 连接方式 | 面向连接 | 面向非连接 |
| 可靠性 | 可靠（确认/重传） | 不可靠 |
| 顺序 | 保证顺序 | 不保证顺序 |
| 开销 | 大 | 小 |
| 适用场景 | 文件传输、Web | 直播、视频通话 |

---

## 第2章 课后作业

### 2.1 奇偶校验

输入一个无符号整型，判断其二进制中 1 的个数是奇校验还是偶校验：

```c
// 17_check.c
int check_odd_even(int num) {
    int i, count = 0;

    for (i = 31; i >= 0; i--) {
        if ((num >> i) & 1)
            count++;
    }

    return count % 2;        // 1 = 奇校验，0 = 偶校验
}

int main(void) {
    unsigned int num;
    printf("input number : ");
    scanf("%u", &num);

    if (check_odd_even(num))
        printf("odd check!\n");     // 奇数个 1
    else
        printf("even check!\n");    // 偶数个 1

    return 0;
}
```

> 逐位右移 &1 统计 1 的个数 → 模 2 判断奇偶。

---

---
## 第3章 TCP/IP 基础

### 3.1 IP 地址

```
IP = 网络号(net) + 主机号(host)
```

| 版本 | 位数 | 地址空间 |
|------|------|----------|
| **IPv4** | 32 bit | 约 43 亿 |
| **IPv6** | 128 bit | 约 3.4×10³⁸ |

### 3.2 ARP 与 RARP

| 协议 | 方向 | 作用 |
|------|------|------|
| **ARP** (Address Resolution Protocol) | IP → MAC | 通过 IP 地址获取 MAC 地址 |
| **RARP** (Reverse ARP) | MAC → IP | 通过 MAC 地址获取 IP 地址 |

### 3.3 本地回环地址

```
127.0.0.1 → 本机
```

常用于本机网络测试，不走物理网卡。

### 3.4 IP 地址配置

**临时配置**：
```bash
ifconfig eth0 192.168.0.?
```

**网卡配置文件**：
```bash
vim /etc/sysconfig/network-scripts/ifcfg-Auto_eth0
```

**图形界面**：
```bash
system-config-network
```

### 3.5 ping 命令

| 功能 | 说明 |
|------|------|
| 检测网络连通性 | 本机与被测主机之间网络是否相通 |
| 检测网速 | 本机与被测主机之间的网络延迟 |
| 测试 DNS | 域名解析是否有效 |

```bash
ping 192.168.2.254 -c 3    # 发送 3 次 ping 包
# Ctrl + C 终止
```

**通**：`64 bytes from 192.168.2.254: icmp_seq=1 ttl=64 time=0.039 ms`

**不通**：`Destination Host Unreachable`（100% packet loss）

---

## 第4章 TCP 三次握手与四次挥手

协议（protocol）是通讯双方都要遵守的一系列规则。

### 4.1 三次握手（建立连接）

```
客户端                          服务器
  |                               |
  |------ SYN (seq=X) ---------->|  第一次：客户端发送 SYN 包
  |                               |         序列号 X，SYN=1
  |                               |
  |<--- SYN+ACK (seq=Y,ack=X+1)--|  第二次：服务器回复 SYN+ACK
  |                               |         序列号 Y，确认号 X+1
  |                               |         SYN=1, ACK=1
  |                               |
  |------ ACK (ack=Y+1) -------->|  第三次：客户端发送 ACK
  |                               |         确认号 Y+1，ACK=1
  |                               |
  |<===== 连接建立，通讯开始 =====>|
```

### 4.2 四次挥手（断开连接）

数据发送完成后，双方通讯状态须拆除（断开连接，四次挥手）。

> 挥手过程中确保双方数据都已传输完毕才关闭连接。

---

## 第5章 TCP Socket 编程基础

### 5.1 TCP 编程流程

```
客户端                              服务器
socket()                            socket()
  |                                   |
connect()                            bind()
  |                                   |
  |  --------- SYN --------->        listen()
  |                                   |
  |  <------- SYN+ACK -------        accept()
  |                                   |
  |  --------- ACK --------->          |
  |                                   |
send()/recv()                    recv()/send()
  |                                   |
close()                            close()
```

**关键概念**：

| 描述符 | 用途 |
|--------|------|
| `sd` | 服务器用于**连接用户** |
| `fd` | 用于**区分不同的用户**，通过 fd 进行数据处理 |

**端口号**：

| 类型 | 说明 |
|------|------|
| **服务端口号** | 用于建立连接，服务指定（固定） |
| **数据端口号** | 用于传输数据，系统随机分配 |

### 5.2 头文件

```c
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
```

### 5.3 socket — 创建网络套接字

```c
int socket(int domain, int type, int protocol);
```

| 参数 | 选项 | 说明 |
|------|------|------|
| `domain` | `AF_INET` | IPv4 地址家族 |
| `type` | `SOCK_STREAM` | TCP 协议 |
| | `SOCK_DGRAM` | UDP 协议 |
| | `SOCK_RAW` | 原始套接字 |
| `protocol` | `0` | 由 type 决定（TCP 或 UDP） |
| | `IPPROTO_TCP` | 显式指定 TCP |
| | `IPPROTO_UDP` | 显式指定 UDP |

**返回值**：成功返回套接字文件描述符，失败 `-1`。

```c
sd = socket(AF_INET, SOCK_STREAM, 0);
```

### 5.4 struct sockaddr_in — 套接字地址结构体

```c
struct sockaddr_in {
    sa_family_t    sin_family;    // 地址家族 AF_INET（2 字节）
    in_port_t      sin_port;      // 端口号 0~65535（2 字节）
    struct in_addr sin_addr;      // IP 地址（4 字节）
};

struct in_addr {
    uint32_t       s_addr;        // 网络字节序的 IP 地址
};
// 结构体总大小：16 字节
```

### 5.5 字节序转换函数

网络字节序统一使用**大端模式**。x86/ARM 是小端，需要转换。

```c
#include <arpa/inet.h>

uint32_t htonl(uint32_t hostlong);   // 主机→网络（长整型，4 字节）
uint16_t htons(uint16_t hostshort);  // 主机→网络（短整型，2 字节）
uint32_t ntohl(uint32_t netlong);    // 网络→主机（长整型）
uint16_t ntohs(uint16_t netshort);   // 网络→主机（短整型）
```

**命名规则**：`h`=host, `n`=network, `l`=long(32bit), `s`=short(16bit)

```c
ser.sin_port = htons(10086);    // 端口号用 htons（16 位）
```

### 5.6 IP 地址转换函数

```c
in_addr_t inet_addr(const char *cp);        // 字符串 IP → 网络字节序
in_addr_t inet_network(const char *cp);     // 字符串 IP → 二进制网络字节序
char *inet_ntoa(struct in_addr in);         // 网络字节序 → 字符串 IP
```

```c
ser.sin_addr.s_addr = inet_addr("192.168.2.254");    // 指定 IP
ser.sin_addr.s_addr = INADDR_ANY;                     // 绑定本机所有 IP
```

### 5.7 connect — 客户端请求连接

```c
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

| 参数 | 说明 |
|------|------|
| `sockfd` | socket 返回的套接字描述符 |
| `addr` | `struct sockaddr_in` 地址（需实例化，强转） |
| `addrlen` | 结构体大小 `sizeof(ser)` |

**返回值**：成功 `0`，失败 `-1`。

```c
// 02_tcp/client.c
struct sockaddr_in ser;
ser.sin_family = AF_INET;
ser.sin_port = htons(PORT);
ser.sin_addr.s_addr = inet_addr(argv[1]);

ret = connect(sd, (struct sockaddr *)&ser, sizeof(ser));
```

### 5.8 bind — 服务器绑定端口和 IP

```c
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

| 参数 | 说明 |
|------|------|
| `sockfd` | socket 返回的套接字描述符 |
| `addr` | `struct sockaddr_in` 地址（需实例化，强转） |
| `addrlen` | 结构体大小 |

**返回值**：成功 `0`，失败 `-1`。

### 5.9 listen — 服务器监听

```c
int listen(int sockfd, int backlog);
```

| 参数 | 说明 |
|------|------|
| `sockfd` | socket 返回的套接字描述符 |
| `backlog` | 最大监听用户个数（如 `50`） |

**返回值**：成功 `0`，失败 `-1`。

### 5.10 accept — 服务器接受连接

```c
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

| 参数 | 说明 |
|------|------|
| `sockfd` | socket 返回的套接字描述符 |
| `addr` | 输出：保存客户端地址信息（**不需要实例化**） |
| `addrlen` | 输入/输出：结构体大小指针 |

**返回值**：成功返回新的文件描述符 `fd`（用于与该客户端通讯），失败 `-1`。

```c
// 02_tcp/server.c
struct sockaddr_in src, from;
int len = sizeof(from);

src.sin_family = AF_INET;
src.sin_port = htons(PORT);
src.sin_addr.s_addr = inet_addr("192.168.2.254");
bind(sd, (struct sockaddr *)&src, sizeof(src));

listen(sd, 50);

fd = accept(sd, (struct sockaddr *)&from, &len);
```

### 5.11 基本 TCP 通讯完整示例

**客户端** `02_tcp/client.c`：
```c
sd = socket(AF_INET, SOCK_STREAM, 0);
ser.sin_family = AF_INET;
ser.sin_port = htons(PORT);
ser.sin_addr.s_addr = inet_addr(argv[1]);
connect(sd, (struct sockaddr *)&ser, sizeof(ser));
close(sd);
```

**服务器** `02_tcp/server.c`：
```c
sd = socket(AF_INET, SOCK_STREAM, 0);
src.sin_family = AF_INET;
src.sin_port = htons(PORT);
src.sin_addr.s_addr = inet_addr("192.168.2.254");
bind(sd, (struct sockaddr *)&src, sizeof(src));
listen(sd, 50);
fd = accept(sd, (struct sockaddr *)&from, &len);
close(fd);
close(sd);
```

### 5.12 显示客户端信息

```c
// 03_tcp_userinfo/server.c — 获取连接客户端的 IP 和端口
fd = accept(sd, (struct sockaddr *)&from, &len);
printf("ip : %s port : %d\n",
    inet_ntoa(from.sin_addr),     // 网络序 IP → 字符串
    ntohs(from.sin_port));        // 网络序端口 → 主机序
```

---

## 第6章 TCP 数据传输

### 6.1 send — 发送数据

```c
ssize_t send(int sockfd, const void *buf, size_t len, int flags);
```

| 参数 | 说明 |
|------|------|
| `sockfd` | 套接字文件描述符 |
| `buf` | 待发送数据地址 |
| `len` | 发送数据字节数 |
| `flags` | 标志位，通常 `0` |

**返回值**：成功返回实际发送字节数，失败 `-1`。

### 6.2 recv — 接收数据

```c
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
```

| 参数 | 说明 |
|------|------|
| `sockfd` | 套接字文件描述符 |
| `buf` | 接收数据缓冲区 |
| `len` | 缓冲区大小 |
| `flags` | 标志位，通常 `0` |

**返回值**：成功返回实际接收字节数，`0` 表示对端关闭，失败 `-1`。

> 也可用 `read`/`write` 在套接字上读写，等效于 `recv`/`send` 的 flags=0 情况。

### 6.3 字符串收发

```c
// 04_tcp_string/client.c — 客户端发送字符串
GETLINES("input send string : ", buf);
write(sd, buf, strlen(buf) + 1);    // +1 包含 '\0'
```

```c
// 04_tcp_string/server.c — 服务器接收字符串
read(fd, buf, sizeof(buf));
printf("ip : %s port : %d message : %s\n",
    inet_ntoa(from.sin_addr), ntohs(from.sin_port), buf);
```

### 6.4 交互式聊天客户端

```c
// 05_tcp_fork/client.c — 循环发送，输入 exit 退出
while (1) {
    GETLINES("input send string : ", buf);
    write(sd, buf, strlen(buf) + 1);

    if (!strcmp(buf, "exit"))
        break;
}
```

---

## 第7章 多进程并发服务器

一个服务器需要同时处理多个客户端连接 → 使用 `fork` 为每个客户端创建子进程。

### 7.1 设计模式

```
while (1) {
    fd = accept(sd, ...);       // 接受新连接
    if (fork() == 0) {          // 子进程处理该客户端
        do_work(fd, from);
        exit(0);
    }
    // 父进程继续 accept 下一个连接
}
```

### 7.2 完整实现

```c
// 05_tcp_fork/server.c
void do_work(int fd, struct sockaddr_in from) {
    char buf[128];
    while (1) {
        read(fd, buf, sizeof(buf));
        printf("ip : %s port : %d message : %s\n",
            inet_ntoa(from.sin_addr), ntohs(from.sin_port), buf);

        if (!strcmp(buf, "exit"))
            break;
    }
}

int main(int argc, char *argv[]) {
    // socket + bind + listen
    sd = socket(AF_INET, SOCK_STREAM, 0);
    src.sin_family = AF_INET;
    src.sin_port = htons(atoi(argv[1]));
    src.sin_addr.s_addr = INADDR_ANY;         // 绑定本机所有 IP
    bind(sd, (struct sockaddr *)&src, sizeof(src));
    listen(sd, 50);

    while (1) {
        fd = accept(sd, (struct sockaddr *)&from, &len);
        if (fork() == 0) {                    // 子进程
            close(sd);                        // 子进程不需要监听套接字
            do_work(fd, from);
            exit(0);
        }
        close(fd);                            // 父进程不需要客户端 fd
    }
}
```

> 子进程关闭 `sd`（不需要监听），父进程关闭 `fd`（不需要处理数据）。  
> 使用命令行参数传入端口号 `atoi(argv[1])`，灵活指定。

---

## 第8章 TCP 文件传输

### 8.1 文本文件传输

客户端读取文件内容 → `send` 发送 → 服务器 `recv` 接收 → 打印输出。

```c
// 07_tcp_file/client.c — 客户端发送文件
fd = open(argv[3], O_RDONLY);                 // 打开文件
while (1) {
    memset(buf, 0, sizeof(buf));
    ret = read(fd, buf, sizeof(buf) - 1);     // 读文件
    if (ret == 0) break;                      // 读完

    send(sd, buf, ret, 0);                    // 发送（只发实际读到的字节）
    sleep(1);                                 // 流控：1 秒间隔
}
```

```c
// 07_tcp_file/server.c — 服务器接收文件内容
fd = accept(sd, (struct sockaddr *)&from, &len);
while (1) {
    memset(buf, 0, sizeof(buf));
    ret = recv(fd, buf, sizeof(buf), 0);      // 接收
    if (ret == 0) break;                      // 对端关闭
    printf("%s", buf);
}
```

### 8.2 大文件（视频）传输

核心区别：缓冲区要大（100KB+），`usleep` 微秒级流控，服务器将数据写入文件而非打印。

```c
// 08_tcp_film/client.c — 客户端发送视频
char buf[102400];                              // 100KB 缓冲区
fd = open(argv[3], O_RDONLY);

while (1) {
    memset(buf, 0, sizeof(buf));
    ret = read(fd, buf, sizeof(buf) - 1);
    if (ret == 0) break;

    send(sd, buf, ret, 0);
    usleep(10000);                             // 10ms 间隔（流控）
}
```

```c
// 08_tcp_film/server.c — 服务器接收视频写入文件
char buf[102400];                              // 100KB 缓冲区
fd = accept(sd, (struct sockaddr *)&from, &len);
fd1 = creat(argv[2], 0666);                   // 创建输出文件

while (1) {
    memset(buf, 0, sizeof(buf));
    ret = recv(fd, buf, sizeof(buf), 0);
    if (ret == 0) break;

    write(fd1, buf, ret);                      // 写入文件
}
close(fd1);
```

> 发送大文件要点：大缓冲区 + `usleep` 流控 + 接收端写文件 `write(fd1, buf, ret)`。

---

## 第9章 课后作业

### 9.1 多线程求素数（复习）

10 个线程分段统计 3000~6000 的素数个数，每个线程通过 `pthread_exit` 返回堆上分配的计数：

```c
// 01_mul_prime.c
#define NUM 10
#define MIN 3000
#define MAX 6000
#define STEP (MAX - MIN) / NUM

void *count_prime(void *data) {
    int min = *(int *)data;
    int max = min + STEP;
    int *count = malloc(sizeof(int));
    *count = 0;

    for (int i = min; i < max; i++) {
        int j;
        for (j = 2; j < i; j++)
            if (i % j == 0) break;
        if (i == j) (*count)++;
    }

    pthread_exit(count);        // 返回堆上的计数
}

int main(void) {
    for (i = 0; i < NUM; i++) {
        min[i] = MIN + i * STEP;
        pthread_create(pthid + i, NULL, count_prime, &min[i]);
    }
    for (i = 0; i < NUM; i++) {
        pthread_join(pthid[i], (void **)&p);
        result += *p;
        free(p);                // 释放线程 malloc 的内存
        p = NULL;
    }
    printf("result : %d\n", result);
}
```

### 9.2 端口扫描

遍历 0~65535 端口，测试哪些端口可以连接：

```c
// 06_check_port.c
for (i = 0; i < 65535; i++) {
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1) break;

    ser.sin_port = htons(i);
    ret = connect(sd, (struct sockaddr *)&ser, sizeof(ser));
    if (ret == 0)
        printf("%d ", i);            // 该端口可用

    close(sd);
}
```

> 每次 connect 后 close，避免资源耗尽。

### 9.3 TCP 版 tell 聊天

实现基于 TCP 的一对一双向聊天程序（类似之前的 FIFO tell）。

---

## 本章小结

```
网络编程概述      ████████████████████
OSI 七层模型      ████████████████████
TCP/IP 四层模型   ████████████████████
大小端/字节序     ████████████████████
以太网帧格式      ████████████████████
TCP vs UDP       ████████████████████
TCP/IP 基础      ████████████████████
三次握手/四次挥手 ████████████████████
Socket 编程基础  ████████████████████
字节序/IP 转换   ████████████████████
TCP 数据传输     ████████████████████
多进程并发服务器  ████████████████████
TCP 文件传输     ████████████████████
课后作业         ████████████████████
```
