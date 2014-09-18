
CC	= gcc
CFLAGS	= -g -Wall -I../include 


SYSTEM_FOLDER	= ../system/

QUEUE_FILES	= queue.c
RESCHED_FILES	=							\
	__ctxsw.c	insert.c	queue.c		resched.c	\
	sched_cntl.c

QUEUE_TEST	= ${QUEUE_FILES:%=${SYSTEM_FOLDER}%}
RESCHED_TEST	= ${RESCHED_FILES:%=${SYSTEM_FOLDER}%}


all:	queue.test resched.test 

queue.test: queuetest.c ${QUEUE_TEST}
	$(CC) $(CFLAGS) -o $@ $^

resched.test: reschedtest.c ${RESCHED_TEST}
	$(CC) $(CFLAGS) -o $@ $^


clean:
	@echo clean
	@rm -f *.test
