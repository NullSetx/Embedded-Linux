
CC = gcc
TARGET = helloworld
OBJS = hello.o world.o
OBJS += test.o


${TARGET}:${OBJS}
	${CC} main.c $^ -o $@

install:
	cp ${TARGET} /usr/bin

uninstall:
	rm /usr/bin/${TARGET}

clean:
	rm /usr/bin/${TARGET} ./${TARGET} -rf
	rm *.o -rf

#%.o:%.c
#	gcc -c $^ -o $@

#hello.o:hello.c
#	gcc -c $^ -o $@
#world.o:world.c
#	gcc -c $^ -o $@
#test.o:test.c
#	gcc -c $^ -o $@


