/* ready.c */

#include <xinu.h>

qid16	readylist;

state ready(pid32 proc, bool8 resch)
{
	register struct procEntry *proptr;
	
	if(isbadpid(proc))
	{
		return SYSERR;
	}

	proptr = &proctab[proc];
	proptr->prstate = PR_READY;
	insert(proc, readylist, proptr->prprio);

	if(resch == RESCHED_YES)
	{
		resched();
	}
	return OK;
}
