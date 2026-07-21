CC = gcc
SUBDIRS = app src
TARGET = demo
CFLAGS = -I ./include
OBJS = ./app/main.o ./src/hello.o ./src/world.o ./src/test.o

all: ${SUBDIRS} ${TARGET}

${SUBDIRS}:
	${MAKE} -C $@

${TARGET} : ${OBJS}
	${CC} ${CFLAGS} $^ -o $@

#Makefile嵌套shell语句，则需要用到;和续行符
#Makefile 要取出shell变量的值，则需要$$号
#all:
	#for dir in ${SUBDIRS};	\
	#do						\
		#${MAKE} -C $$dir;	\
	#done

clean:
	for dir in ${SUBDIRS};			\
	do								\
		${MAKE} -C $$dir clean;		\
	done

	rm -f demo

