CC = gcc
OBJS = hello.o world.o test.o
CFLAGS = -I ../include

all:${OBJS}
	
%.o : %.c
	${CC} -c ${CFLAGS} $< -o $@

clean:
	rm -f *.o



