CC     = gcc
FLAGS  = -Wall -Wextra -g
PROGS  = exe/sysmanager exe/main
OBJS1  = exe/sysmanager.o exe/logs.o exe/authmanager.o
OBJS2  = exe/main.o exe/logs.o
DEPS  = src/logs.h

all:	${PROGS}

clean:
	rm ${PROGS} exe/*.o *~

exe/sysmanager:	${OBJS1} ${DEPS}
	${CC} ${FLAGS} ${OBJS1} -o $@

exe/main:	${OBJS2} ${DEPS}
	${CC} ${FLAGS} ${OBJS2} -o $@

exe/authmanager.o: src/authmanager.c ${DEPS}
	${CC} -pthread ${FLAGS} -c $< -o $@

exe/%.o: src/%.c 
	${CC} ${FLAGS} -c $< -o $@