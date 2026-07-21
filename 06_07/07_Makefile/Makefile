
CC = gcc
TARGET = ${BUILD_DIR}/helloworld
CFLAGS = -g -Wall
CFLAGS += -I ./include

#保存源文件目录
SRC_DIR = ./src
#保存头文件的目录
INCLUDE_DIR =  ./include
#保存目标文件 可执行文件
BUILD_DIR = ./build

#查找所有的.c文件 wildcard : 表示makefile子函数，用于查找所有.c
SRCS = ${wildcard ${SRC_DIR}/*.c}
#patsubst 表示替换 所有.c替换成.o
OBJS = ${patsubst ${SRC_DIR}/%.c, ${BUILD_DIR}/%.o, ${SRCS}}


${TARGET}:${OBJS}
	mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} $^ -o $@

install:
	cp ${TARGET} /usr/bin

uninstall:
	rm /usr/bin/${TARGET}

clean:
	rm -rf ${BUILD_DIR}

	#rm /usr/bin/${TARGET} ./${TARGET} -rf
	#rm *.o -rf

${BUILD_DIR}/%.o : ${SRC_DIR}/%.c
	mkdir -p ${BUILD_DIR}
	${CC} -c ${CFLAGS} $< -o $@


#%.o:%.c
#	gcc -c $^ -o $@

#hello.o:hello.c
#	gcc -c $^ -o $@
#world.o:world.c
#	gcc -c $^ -o $@
#test.o:test.c
#	gcc -c $^ -o $@


