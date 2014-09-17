/* defer.h */

#define DEFER_START	1
#define DEFER_STOP	2


struct defer{
	int32	ndefers;
	bool8	hasattempt;
};

extern	struct defer	Defer;
