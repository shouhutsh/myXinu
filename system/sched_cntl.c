/* sched_cntl.c */

#include <xinu.h>

struct defer	Defer;

status	sched_cntl(int32 deferState)
{
	switch(deferState)
	{
		case DEFER_START:
			if(Defer.ndefers++ == 0)
			{
				Defer.hasattempt = FALSE;
			}
			return OK;

		case DEFER_STOP:
			if(Defer.ndefers <= 0)
			{
				return SYSERR;
			}
			if(--Defer.ndefers==0 && Defer.hasattempt==TRUE)
			{
				resched();
			}
			return OK;

		default:
			return SYSERR;
	}
}
