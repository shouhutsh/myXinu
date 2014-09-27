/* intr.c */

#include <xinu.h>
#include <stdio.h>

intmask disable(void)
{
	printf("禁止中断\n");
	return OK;
}


void restore(intmask mask)
{
	printf("设置中断掩码\n");
}
