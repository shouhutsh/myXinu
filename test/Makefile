

CC	= gcc
CFLAGS	= -g -Wall -I../include 

FOLD_SYS = ../system

all:	testQueue

testQueue: testQueue.c $(FOLD_SYS)/queue.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	@echo clean
	@rm -f testQueue
