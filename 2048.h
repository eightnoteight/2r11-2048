#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <float.h>
#include <setjmp.h>
#include <signal.h>
#include <ncurses.h>
int row,col;
char hash[17];
typedef enum { False, True } boool;
int board[4][4] = {
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}
};
void swap(int *p, int *q){
	int temp;
	temp=*p;
	*p=*q;
	*q=temp;
}