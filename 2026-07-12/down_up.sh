#!/bin/bash

IP=192.168.2.254
SHAREDIR=/ken
HOMEWORKDIR=/homework


#1 检测网络是否连接

if ! ping $IP -c 1 &> /dev/null
then
	echo "no link"
	exit
fi

#2 检测nfs是否启动
if ! showmount -e $IP &> /dev/null
then
	echo "nfs false"
	exit
fi

#3 下载课件还是上传作业
umount -l /mnt &> /dev/null

if [ $1 = "down" ]
then
	mount $IP:$SHAREDIR /mnt
	cp /mnt/* /workfile -rf
	umount /mnt
elif [ $1 = "up" ]
then
	mount $IP:$HOMEWORKDIR /mnt
	cp /254_张三 /mnt -rf
	umount /mnt
else
	echo "format : filename + down | up"
fi	












