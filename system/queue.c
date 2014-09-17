/* queue.c */

#include <xinu.h>

struct queEntry	queuetab[NQENT];

pid32	getitem(pid32 pid)
{
	if(isbadpid(pid))
	{
		return SYSERR;
	}

	qid16	prev, next;

	prev = queuetab[pid].qprev;
	next = queuetab[pid].qnext;

	queuetab[prev].qnext = queuetab[pid].qnext;
	queuetab[next].qprev = queuetab[pid].qprev;

	return pid;
}

pid32	getfirst(qid16 qid)
{
	if(isbadqid(qid))
	{
		return EMPTY;
	}
	
	return getitem(firstid(qid));
}

pid32	getlast(qid16 qid)
{
	if(isbadqid(qid))
	{
		return EMPTY;
	}

	return getitem(lastid(qid));
}

pid32	enqueue(pid32 pid, qid16 qid)
{
	if(isbadpid(pid) || isbadqid(qid))
	{
		return SYSERR;
	}

	qid16 prev, tail;
	
	prev = lastid(qid);
	tail = queuetail(qid);

	queuetab[pid].qprev = prev;
	queuetab[pid].qnext = tail;

	queuetab[prev].qnext = pid;
	queuetab[tail].qprev = pid;

	return pid;
}

pid32	dequeue(qid16 qid)
{
	if(isbadqid(qid))
	{
		return SYSERR;
	}
	else if (isqueue(qid))
	{
		return EMPTY;
	}

	pid32 pid;

	pid = getfirst(qid);
	queuetab[pid].qprev = EMPTY;
	queuetab[pid].qnext = EMPTY;

	return pid;
}

qid16	newqueue(void)
{
	static qid16 nextque = NPROC;

	qid16 qid, head, tail;

	qid = nextque;
	if(isbadqid(qid))
	{
		return SYSERR;
	}
	nextque += 2;

	head = queuehead(qid);
	tail = queuetail(qid);

	queuetab[head].qnext = tail;
	queuetab[head].qprev = EMPTY;
	queuetab[head].qkey  = MAXKEY;
	queuetab[tail].qnext = EMPTY;
	queuetab[tail].qprev = head;
	queuetab[tail].qkey  = MINKEY;
	return qid;
}
