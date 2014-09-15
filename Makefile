

CC	= gcc
CFLAGS	= -g -Wall -I. 

all:	testQueue

testQueue: testQueue.c queue.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	@echo clean
	@rm -f testQueue
