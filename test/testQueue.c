#include <xinu.h>
#include <stdio.h>

struct procEntry	proctab[NPROC];

int main(void)
{
	qid16 qid;

	int i;

	printf("%d", NQENT);
	qid = newqueue();

	for(i = 0; i < 3; i++)
	{
		proctab[i].prstate = !PR_FREE;
		enqueue(i, qid);
	}

	getfirst(qid);
	getlast(qid);

	dequeue(qid);

	return 0;
}
