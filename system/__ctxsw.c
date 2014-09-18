/* __ctxsw.c */

#include <xinu.h>
#include <stdio.h>

/* 模拟同名函数 */

void ctxsw(void * oldstk, void * newstk)
{
	printf("已切换进程上下文\n");
}
