
CC = gcc
OBJS = main.o
CFLAGS = -I ../include

all:${OBJS}
	
%.o : %.c
	${CC} -c ${CFLAGS} $< -o $@

clean:
	rm -f *.o



