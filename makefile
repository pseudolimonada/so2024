CC     = gcc
FLAGS  = -Wall -Wextra -g

PROGS  = sysmanager main
OBJS1  = sysmanager.o 
OBJS2  = main.o logs.o
DEPS  = logs.h

all:	${PROGS}

clean:
	rm ${PROGS} *.o *~

sysmanager:	${OBJS1}
	${CC} ${FLAGS} ${OBJS1} -o $@

main:	${OBJS2} ${DEPS}
	${CC} ${FLAGS} ${OBJS2} -o $@

%.o: %.c
	${CC} ${FLAGS} -c $< -o $@