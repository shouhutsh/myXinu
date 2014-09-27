
extern void	ctxsw(void *, void *);

extern status	insert(pid32, qid16, pri16);

extern void	resched(void);

extern status	sched_cntl(int32);

extern intmask	disable(void);

extern void	restore(intmask);

extern status	ready(pid32, bool8);
