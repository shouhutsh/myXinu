#include <xinu.h>
#include <stdio.h>

struct procEntry	proctab[NPROC];
pid32  currproc;
qid16  readylist;
uint32 preempt;

static void init();

int main(void)
{
	int i;

	init();

	for(i = 0; i < 3; ++i)
	{
		sched_cntl(DEFER_START);
	}

	resched();

	for(i = 0; i < 3; ++i)
	{
		sched_cntl(DEFER_STOP);
	}

	return 0;
}

void init()
{
	int i;
	struct procEntry *proc;

	currproc = 0;
	readylist = newqueue();

	proc = &proctab[currproc];
	proc->prstate = PR_CURR;
	proc->prprio  = 10;

	for(i = currproc+1; i < currproc+3; i++)
	{
		proc = &proctab[i];
		proc->prstate = PR_READY;
		proc->prprio  = 5*i;
		insert(i, readylist, proc->prprio);
	}

	Defer.ndefers = 0;
	Defer.hasattempt = FALSE;
}
