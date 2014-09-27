/* semaphore.h */

#ifndef NSEM
#define NSEM		45
#endif

#define SE_FREE		0
#define SE_USED		1

struct semEntry{
	byte	sestate;	//状态
	int32	secount;	//信号量计数
	qid16	sequeue;	//等待此信号量的进程队列
};

extern	struct semEntry		semtab[];

#define isbadsid(sem)		((sem)<0 || (sem)>=NSEM)
