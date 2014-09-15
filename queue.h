/* queue.h */

#ifndef NQENT
#define NQENT	(NPROC + 4 + NSEM + NSEM)
#endif

#define EMPTY	(-1)

#define MAXKEY	0x7FFFFFFF
#define MINKEY	0x80000000

struct qentry	{
	int32	qkey;
	qid16	qnext;
	qid16	qprev;
};

extern	struct qentry	queuetab[];


#define queuehead(q)	(q)
#define queuetail(q)	((q) + 1)
#define firstid(q)	(queuetab[queuehead(q)].qnext)
#define lastid(q)	(queuetab[queuetail(q)].qprev)
#define firstkey(q)	(queuetab[firstid(q)].qkey)
#define lastkey(q)	(queuetab[lastid(q)].qkey)
#define isqueue(q)	(firstid(q)>=NPROC && firstid(q)<NQENT)

#define isbadqid(q)	((q)<0 || (q)>NQENT-1)


pid32	getfirst(qid16);
pid32	getlast(qid16);
pid32	getitem(pid32);
pid32	enqueue(pid32, qid16);
pid32	dequeue(qid16);
qid16	newqueue(void);
