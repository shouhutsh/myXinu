/* resched.c */

#include <xinu.h>

void resched(void)
{
	struct procEntry * procOld;
	struct procEntry * procNew;

	if(Defer.ndefers > 0)
	{
		Defer.hasattempt = TRUE;
		return ;
	}

	procOld = &proctab[currproc];
	if(procOld->prstate == PR_CURR)
	{
		if(procOld->prprio > firstkey(readylist))
		{
			return ;
		}

		procOld->prstate = PR_READY;
		insert(currproc, readylist, procOld->prprio);
	}

	currproc = dequeue(readylist);
	procNew  = &proctab[currproc];
	procNew->prstate = PR_CURR;

	preempt = QUANTUM;	//NOTE 重置时间片，但我目前不太清楚作用

	ctxsw(&procOld->prstkptr, &procNew->prstkptr);
}
