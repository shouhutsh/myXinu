/* insert.c */

#include <xinu.h>

status insert(pid32 proc, qid16 queue, pri16 prio)
{
	if(isbadpid(proc) || isbadqid(queue))
	{
		return SYSERR;
	}

	pid32 curr, prev;

	curr = firstid(queue);
	//NOTE 这个qkey表达什么意思呢？在这里似乎是优先级。
	//但是procEntry里不是已经有prprio了吗？
	while(queuetab[curr].qkey >= prio)
	{
		curr = queuetab[curr].qnext;
	}

	prev = queuetab[curr].qprev;
	queuetab[proc].qprev = prev;
	queuetab[proc].qnext = curr;
	queuetab[proc].qkey  = prio;
	queuetab[prev].qnext = proc;
	queuetab[curr].qprev = proc;

	return OK;
}
