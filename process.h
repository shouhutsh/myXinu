/* process.h */

#ifndef NPROC
#define NPROC		8
#endif

#define PR_FREE		0


#define isbadpid(p)	((pid32)(p) < 0 || \
			 (pid32)(p) >= NPROC || \
			 (proctab[p].prstate == PR_FREE))


struct procEntry{
	
};


extern	struct procEntry	proctab[]; 
