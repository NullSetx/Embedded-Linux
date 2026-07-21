CC = gcc
OBJS = ../build/hello.o ../build/world.o ../build/test.o
CFLAGS = -I ../include

all:${OBJS}
	
../build/%.o : %.c
	${CC} -c ${CFLAGS} $< -o $@

clean:
	rm -f ../build/*.o



