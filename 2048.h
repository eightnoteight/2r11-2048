#ifndef _2048_H
#define _2048_H 1

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
#include <accacia.h>

extern int row,col;
extern char hash[17];
extern int board[4][4];

#ifndef A_ITALIC
#define A_ITALIC 0
#endif

#ifndef USE_ACCACIA
#define UP_KEY 259
#define DOWN_KEY 258
#define LEFT_KEY 260
#define RIGHT_KEY 261
#define ENTER 10
#else
#define UP_KEY 'w'
#define DOWN_KEY 's'
#define LEFT_KEY 'a'
#define RIGHT_KEY 'd'
#define ENTER 10
#endif

int boardcount();

int legalmoves();

int nzcb();

int boardcheck();

void randinsertboard();

void zerodrag(int* p, int* q, int* r, int* s);

void sumsitup(int* p, int* q, int* r, int* s);

inline void bunchcall(int* p, int* q, int* r, int* s);

char* hashgen();

#endif
