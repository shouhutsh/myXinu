/* kernel.h */

typedef unsigned char		byte;
typedef unsigned int		word;
typedef unsigned long		dword;
typedef char			int8;
typedef short			int16;
typedef int			int32;
typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef unsigned long long	uint64;


typedef byte	bool8;
typedef int16	qid16;
typedef int32	pid32;
typedef int32	status;
typedef int16	pri16;
typedef uint16	intmask;


typedef int32	syscall;
#define SYSERR	(-1)
#define OK	(1)


#define TRUE	(1)
#define FALSE	(0)


#define QUANTUM	2


extern	qid16	readylist;
