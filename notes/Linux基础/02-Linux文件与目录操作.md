# 第二课：Linux文件与目录操作

## 1. 文件权限管理

### 权限数字表示法
| 权限 | 数字 | 二进制 |
|------|------|--------|
| rwx | 7 | 111 |
| rw- | 6 | 110 |
| r-x | 5 | 101 |
| r-- | 4 | 100 |
| -wx | 3 | 011 |
| -w- | 2 | 010 |
| --x | 1 | 001 |
| --- | 0 | 000 |

**权限对象：**
- `u` - 属主（user）
- `g` - 属组（group）
- `o` - 其他用户（other）
- `a` - 所有用户（all）

### chmod - 修改文件权限

**符号方式：**
```bash
# 格式：chmod [对象][操作符][权限] 文件名

# 属主添加可执行权限
chmod u+x hello.c

# 删除属组读权限
chmod g-r hello.c

# 指定其他用户权限
chmod o=rx hello.c

# 所有用户指定可读可写
chmod a=rw hello.c

# 同时设置多组权限
chmod u=rwx,g=rx,o=r hello.c
```

**数字方式：**
```bash
# 格式：chmod [三位数字] 文件名

# 设置权限为 rwxr-xr-- (754)
chmod 754 hello.c

# 设置权限为 rw-rw-rw- (666)
chmod 666 hello.c
```

### chown - 修改文件属主和属组

```bash
# 修改文件属主
chown jim hello.c

# 修改文件属组
chown :mary hello.c

# 同时修改属主和属组
chown jim:mary hello.c
```

### 创建用户

```bash
# 创建用户
useradd jim
useradd mary

# 查看用户信息
id jim
# 输出：uid=500(jim) gid=506(jim) 组=506(jim)
```

## 2. 链接文件

### 硬链接
```bash
# 创建硬链接
ln srcfile destfile
```

**特点：**
- 相当于给文件做个备份
- 硬链接文件索引号（inode）相同
- **不能对目录创建硬链接**
- 删除源文件，硬链接文件仍可访问

### 软链接（符号链接）
```bash
# 创建软链接
ln -s srcfile destfile
```

**特点：**
- 相当于给文件创建快捷方式
- 软链接文件索引号不同
- **可以对目录创建软链接**
- 删除源文件，软链接文件失效

## 3. 目录操作

### cd - 切换目录

**路径类型：**
- **绝对路径**：从根目录 `/` 开始
- **相对路径**：从当前工作目录开始

**特殊路径符号：**
| 符号 | 含义 |
|------|------|
| `.` | 当前工作目录 |
| `..` | 上级目录 |
| `~` | 当前用户家目录 |
| `-` | 上次所在的工作目录 |

```bash
# 示例
cd /              # 切换到根目录
cd ..             # 切换到上级目录
cd ~              # 切换到家目录
cd -              # 切换到上次所在的目录
cd ../../..       # 向上切换三级目录
```

### pwd - 显示当前工作目录

```bash
pwd
# 输出示例：/test/aa/bb
```

### mkdir - 创建目录

```bash
# 创建单级目录
mkdir testdir

# 递归创建多级目录
mkdir -p /test/aa/bb/cc/dd

# 使用 tree 命令查看目录结构
tree
```

### rmdir - 删除空目录

```bash
# 删除空目录
rmdir testdir

# 删除非空目录（推荐使用 rm -r）
rm testdir -rf
```

## 4. 文件操作

### touch - 创建文件

```bash
# 创建单个文件
touch a.txt

# 创建多个文件
touch file1.txt file2.txt file3.txt
```

### rm - 删除文件

```bash
# 删除文件
rm filename

# 强制删除，无需确认
rm -f filename

# 递归删除目录及其内容
rm -rf dirname

# 删除所有 .c 文件
rm *.c
```

**通配符：**
| 符号 | 含义 |
|------|------|
| `*` | 任意多个字符 |
| `?` | 任意一个字符 |

### cp - 复制文件

```bash
# 格式：cp [选项] 源文件 目标文件

# 复制文件
cp a.txt b.txt

# 复制时跳过确认（使用完整路径）
/bin/cp a.txt b.txt
# 或使用转义符
\cp a.txt b.txt

# 递归复制目录
cp aa bb -r

# 复制所有 .c 文件到 /tmp
cp *.c /tmp
```

### mv - 移动或重命名

```bash
# 重命名文件
mv oldname.txt newname.txt

# 移动文件到目录
mv filename.txt /tmp/

# 移动并重命名
mv filename.txt /tmp/newname.txt
```

## 5. 文件内容查看

### cat - 显示文件内容

```bash
# 显示文件内容
cat filename

# 显示行号
cat -n filename

# 显示特殊字符（如换行符 $）
cat -E filename
```

### more - 分屏显示（向后翻页）

```bash
more filename
# 操作：
# - 空格键：向下翻页
# - Enter键：向下滚动一行
# - q：退出
```

### less - 分屏显示（可前后翻页）

```bash
less filename
# 操作：
# - 方向键：上下滚动
# - q：退出
```

### head - 查看文件前N行

```bash
# 默认显示前10行
head filename

# 显示前3行
head -n 3 filename
```

### tail - 查看文件后N行

```bash
# 默认显示后10行
tail filename

# 显示后2行
tail -n 2 filename
```

## 6. 重定向

### 特殊文件（设备文件）

| 设备 | 文件指针 | 文件描述符 |
|------|----------|------------|
| 输入设备（键盘、鼠标） | stdin | 0 |
| 输出设备（显示器、打印机） | stdout | 1 |
| 错误输出 | stderr | 2 |

### 输出重定向

```bash
# 清空正确输出重定向（>）
echo hello > a.txt

# 追加正确输出重定向（>>）
echo hello >> a.txt

# 清空错误输出重定向（2>）
ls /nonexist 2> error.txt

# 追加错误输出重定向（2>>）
ls /nonexist 2>> error.txt

# 同时重定向正确和错误输出（&> 或 &>>）
command &> output.txt
command &>> output.txt

# 黑洞文件 - 丢弃输出
ping 192.168.2.254 > /dev/null
```

### 输入重定向

```bash
# 从文件读取输入
passwd jim < ./a.txt

# Here Document（结束标记）
cat << AAA
hello
world
AAA
```

## 7. 文件时间戳

使用 `stat` 命令查看文件时间信息：

```bash
stat filename
```

**三种时间：**
| 时间 | 含义 | 触发操作 |
|------|------|----------|
| atime | 访问时间 | cat, more, less, head, tail |
| ctime | 属性修改时间 | chmod, chown |
| mtime | 内容修改时间 | vim编辑、重定向写入 |

**注意**：修改文件内容（mtime）会同时触发ctime更新

---

**下一课预告**：Vim编辑器详解
