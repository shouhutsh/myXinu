/* semaphore.c */

#include <xinu.h>

static	sid32	newsem(void);

syscall semcount(sid32 sem)
{
	intmask mask;
	int32 count;

	mask = disable();
	if(isbadsid(sem) || semtab[sem].sestate==SE_FREE)
	{
		restore(mask);
		return SYSERR;
	}
	count = semtab[sem].secount;
	restore(mask);
	return count;
}

sid32	semcreate(int32 count)
{
	intmask mask;
	sid32 sem;

	mask = disable();
	if(count<0 || (sem=newsem())==SYSERR)
	{
		restore(mask);
		return SYSERR;
	}

	semtab[sem].secount = count;
	restore(mask);
	return sem;
}

syscall semdelete(sid32 sem)
{
	intmask mask;
	struct semEntry *semptr;

	mask = disable();
	if(isbadsid(sem))
	{
		restore(mask);
		return SYSERR;
	}

	semptr = &semtab[sem];
	if(semptr->sestate == SE_FREE)
	{
		restore(mask);
		return SYSERR;
	}
	semptr->sestate = SE_FREE;

	while(semptr->secount++ < 0)
	{
		ready(getfirst(semptr->sequeue), RESCHED_NO);
	}
	resched();
	restore(mask);
	return OK;
}

syscall semreset(sid32 sem, int32 count)
{
	intmask mask;
	struct	semEntry * semptr;
	qid16	queue;
	pid32	proc;

	mask = disable();
	if(isbadsid(sem) || count<0 || semtab[sem].sestate==SE_FREE)
	{
		restore(mask);
		return SYSERR;
	}

	semptr = &semtab[sem];
	queue  = semptr->sequeue;
	//NOTE 这里的循环条件和semdelete里的应该是一样的
	while((proc = getfirst(queue)) != EMPTY)
	{
		ready(proc, RESCHED_NO);
	}

	semptr->secount = count;
	resched();
	restore(mask);
	return OK;
}

static sid32 newsem(void)
{
	static sid32 nextsem = 0;
	sid32 sem;
	int32 i;

	for(i = 0; i < NSEM; ++i)
	{
		sem = nextsem++;
		if(nextsem >= NSEM)
		{
			nextsem = 0;
		}
		if(semtab[sem].sestate == SE_FREE)
		{
			semtab[sem].sestate = SE_USED;
			return sem;
		}
	}
	return SYSERR;
}


syscall signal(sid32 sem)
{
	intmask mask;
	struct semEntry *semptr;	

	mask = disable();
	if(isbadsid(sem))
	{
		restore(mask);
		return SYSERR;
	}

	semptr = &semtab[sem];
	if(semptr->sestate == SE_FREE)
	{
		restore(mask);
		return SYSERR;
	}

	if(semptr->secount++ < 0)
	{
		ready(dequeue(semptr->sequeue), RESCHED_YES);
	}

	restroe(mask);
	return OK;
}

syscall wait(sid32 sem)
{
	intmask mask;
	struct semEntry *semptr;
	struct procEntry *procptr;

	if(isbadsid(sem))
	{
		restore(mask);
		return SYSERR;
	}

	semptr = &semtab[sem];
	if(semptr->sestate == SE_FREE)
	{
		restore(mask);
		return SYSERR;
	}

	if(--semptr->secount < 0)
	{
		procptr = &proctab[currproc];
		procptr->prstate = PR_WAIT;
		procptr->prsem = sem;
		enqueue(currproc, semptr->sequeue);
		resched();
	}

	restore(mask);
	return OK;
}
