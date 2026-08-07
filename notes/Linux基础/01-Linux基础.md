# 第一课：Linux基础与终端操作

## 1. Linux桌面环境

### 核心概念
- Linux下所有操作都在**终端**中运行
- 所有设备都以**文件**方式体现
- 所有文件都从**根目录(/)** 开始

### 打开终端的方式
```bash
# 方法1：鼠标右键 => 打开终端
# 方法2：Alt + F2，输入 gnome-terminal
# 方法3：应用程序 => 系统工具 => 终端
```

### 关闭终端
```bash
exit
```

## 2. 终端窗口操作

### 字体调整
| 操作 | 临时生效 | 永久生效 |
|------|----------|----------|
| 放大字体 | `Ctrl + Shift + +` | 编辑 → 首选项 → 设置字体 |
| 缩小字体 | `Ctrl + -` | 同上 |

### 窗口管理
| 操作 | 快捷键 |
|------|--------|
| 最大化窗口 | `Alt + F10` |
| 最小化窗口 | `Alt + F9` |
| 切换窗口 | `Alt + Tab` |
| 新建标签页 | `Ctrl + Shift + T` |
| 切换标签页 | `Alt + 数字(1,2,3...)` |

## 3. 系统管理命令

### 重启系统
```bash
reboot
shutdown -r now
init 6
```

### 关机
```bash
shutdown -h now
init 0
poweroff
```

## 4. 查看系统信息

### 发行版本
```bash
cat /etc/issue
lsb_release -a
```

示例输出：
```
Red Hat Enterprise Linux Server release 6.5 (Santiago)
```

### 内核版本
```bash
uname -r
# 输出示例：2.6.32-431.el6.i686

# 版本号说明：
# 2 - 主版本号（系统架构重大变化时更改）
# 6 - 次版本号（奇数=测试版，偶数=稳定版）
# 32 - 修订版本号
```

### 系统平台
```bash
uname -m
# i686    = 32位系统
# x86_64  = 64位系统
```

### 完整系统信息
```bash
uname -a
# 输出示例：
# Linux www.kening.com 2.6.32-431.el6.i686 #1 SMP Sun Nov 10 22:20:22 EST 2013 i686 i686 i386 GNU/Linux
```

## 5. Linux文件系统结构

```
/
├── boot/          # 启动镜像文件（如 vmlinuz-2.6.32-431.el6.i686）
├── home/          # 普通用户的家目录（/home/username）
├── lib/           # 库文件
│   ├── libc.so.6  # C库文件（.so=动态库，.a=静态库）
├── mnt/           # 默认挂载目录（Windows共享等）
├── root/          # root用户的家目录
├── sys/           # 驱动模块
├── proc/          # 进程信息（虚拟目录）
├── sbin/          # 管理员指令
├── bin/           # 普通用户指令
├── usr/           # 用户安装软件目录
│   └── include/   # 系统头文件目录
├── dev/           # 设备文件目录
│   ├── 字符设备
│   └── 块设备
├── media/         # 挂载U盘、光盘、硬盘（支持fat，不支持ntfs）
├── opt/           # 扩展包存放目录
└── etc/           # 配置文件目录
```

## 6. 基本命令

### Tab键 - 自动补齐
- **命令补齐**：输入部分命令后按Tab键
- **文件补齐**：输入部分文件名后按Tab键

**注意**：
- 按一次无反应 → 可能有多个匹配或输入错误
- 再按一次Tab → 显示所有匹配项（多个匹配时）
- 仍然无响应 → 输入错误

### man - 帮助手册
```bash
man + 手册编号 + 命令
# 退出：按 q
```

**man手册共8本：**

| 编号 | 内容 | 说明 |
|------|------|------|
| 1 | User Commands | 普通用户指令 |
| 2 | System Calls | 系统调用函数 |
| 3 | C Library Functions | C库函数 |
| 4 | Devices and Special Files | 设备驱动文件 |
| 5 | File Formats and Conventions | 文件格式说明 |
| 6 | Games | 游戏开发相关 |
| 7 | Miscellanea | 网络开发说明 |
| 8 | System Administration | 管理员指令 |

### ls - 显示目录内容
```bash
ls [选项] [目录名]
```

**常用选项：**

| 选项 | 说明 |
|------|------|
| `-a` | 显示所有文件（包括隐藏文件） |
| `-i` | 显示文件索引号(inode) |
| `-l` | 长格式显示详细信息 |

#### 文件类型（ls -l 第一个字符）
| 字符 | 类型 |
|------|------|
| `-` | 普通文件 |
| `d` | 目录文件 |
| `c` | 字符设备文件 |
| `b` | 块设备文件 |
| `l` | 软链接文件 |
| `s` | 套接字文件 |
| `p` | 管道文件 |

#### 文件权限（第2-10个字符）
```
权限格式：rwxrwxrwx
         │││ │││ │││
         │││ │││ └┴┴─ 其他用户权限
         │││ └┴┴────── 属组权限
         └┴┴────────── 属主权限

r = 读    w = 写    x = 执行    - = 无权限
```

#### ls -l 输出示例
```bash
[root@www test]# ls -l
总用量 16
-rw-r--r-- 1 root root 3587 5月  20 20:51 1st.txt
-rwxr-xr-x 1 root root 4643 5月  20 19:27 a.out
-rw-r--r-- 1 root root   89 5月  20 19:27 hello.c
```

**各列含义：**
1. 文件类型和权限
2. 硬链接数
3. 属主
4. 属组
5. 文件大小
6. 时间（atime/ctime/mtime）
7. 文件名

## 7. 课件下载

从Windows共享目录下载课件：
```bash
# Windows下
Win + R → 输入 \\172.18.71.234
用户名：admin
进入 share 目录

# Linux下挂载
挂载点：/mnt/hgfs/windows_share_dir_name
```

---

