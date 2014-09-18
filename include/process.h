/* process.h */

#ifndef NPROC
#define NPROC		8
#endif

/* 进程的状态 */
#define PR_FREE		0	//空闲
#define PR_CURR		1	//当前
#define PR_READY	2	//就绪
#define PR_RECV		3	//接受
#define PR_SLEEP	4	//睡眠
#define PR_SUSP		5	//挂起
#define PR_WAIT		6	//等待
#define PR_RECTIM	7	//接收超时


#define isbadpid(p)	((p) < 0 || \
			 (p) >= NPROC || \
			 (proctab[(p)].prstate == PR_FREE))


struct procEntry{
	uint16	prstate;	//状态
	pri16	prprio;		//优先级
	char *	prstkptr;	//栈指针
};


extern	struct procEntry	proctab[]; 


extern	pid32	currproc;
