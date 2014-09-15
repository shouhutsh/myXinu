/* process.h */

#ifndef NPROC
#define NPROC		8
#endif

#define PR_FREE		0


#define isbadpid(p)	((p) < 0 || \
			 (p) >= NPROC || \
			 (proctab[(p)].prstate == PR_FREE))


struct procEntry{
	uint16	prstate;
};


extern	struct procEntry	proctab[]; 
