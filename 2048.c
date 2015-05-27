#include "2048.h"
#ifndef USE_ACCACIA
#include "2048nc.h"
#else
#include "2048ac.h"
#endif

int row,col;

char hash[17];

int board[4][4] = {
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
};

static void swap(int *p, int *q) {
    int temp;
    temp=*p;
    *p=*q;
    *q=temp;
}

static void printboard() {
#ifndef USE_ACCACIA
    nc_printboard();
#else
    ac_printboard();
#endif
}

static int gameinit() {
#ifndef USE_ACCACIA
    nc_gameinit();
#else
    ac_gameinit();
#endif
}

static void Winner() {
#ifndef USE_ACCACIA
    nc_Winner();
#else
    ac_Winner();
#endif
}

static void Loser() {
#ifndef USE_ACCACIA
    nc_Loser();
#else
    ac_Loser();
#endif
}

int boardcount() {
    int pint=0,i,j;
    for (i = 0; i < 4; ++i)
	for (j = 0; j < 4; ++j)
		if (board[i][j])
			pint++;
    return pint;
}

int legalmoves() {
    int i,j;
    for (i = 0; i < 4; i++) 
        for (j = 0; j < 3; j++) 
            if (board[i][j] == board[i][j+1])
                return 1;
    for (i = 0; i < 4; i++) 
        for (j = 0; j < 3; j++) 
            if (board[j][i] == board[j][i+1])
                return 1;
    return 0;
}

int nzcb() {
    int nonz=0,i,j;
    for (i = 0; i < 4; ++i)
	for (j = 0; j < 4; ++j)
		if (board[i][j])
			nonz++;
    return nonz;
}

int boardcheck() {
    int i,j;
    for (i = 0; i < 4; ++i)
        for (j = 0; j < 4; ++j)
        {
            if (board[i][j] == 2048)
                return 1;
        }
    if (nzcb() == 16 && !legalmoves())
        return -1;
    return 0;
}

void randinsertboard() {
    if ((16-nzcb())==0)
	return;
    /*assert((16-nzcb())!=0); remove the assert after 
     * checking checkboardfunction() */
    int s=rand()%(16-nzcb()), p;
    for(p=0;p<=s;++p)
	if (board[p/4][p%4])
		s++;
    board[s/4][s%4]=2;
}

void zerodrag(int* p, int* q, int* r, int* s) {
    int* pint[5]={p,q,r,s};
    int j,k;
    for (j = 0; j < 4; ++j)
    {
        k=j;
	while((k!=4)&&((*pint[k])==0))
	    k++;
	if (k==4)
	    break;
	swap(pint[j],pint[k]);
    }
}

void sumsitup(int* p, int* q, int* r, int* s) {
    int* pint[5]={p,q,r,s};
    int i;
    int nzc=0; /* nzc is non zero count */
    for (i = 0; i < 4; ++i)
        if (*pint[i])
	    nzc++;
    for (i = 0; i < nzc-1; ++i)
        if (*pint[i]==*pint[i+1])
	{
	    *pint[i]*=2;
	    *pint[i+1]=0;
	    zerodrag(p,q,r,s);
	}
}

inline void bunchcall(int* p, int* q, int* r, int* s) {
    zerodrag(p,q,r,s);
    sumsitup(p,q,r,s);
}

char* hashgen() {
    int i;
    for (i = 0; i < 16; ++i)
    {
        hash[i]=board[i/4][i%4]+48;
    }
    hash[16]='\0';
    return hash;
}

int main(int argc, char const *argv[]) {
#ifndef USE_ACCACIA
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    raw();
    noecho();
    curs_set(0);
    keypad(stdscr,TRUE);
    getmaxyx(stdscr,row,col);
#else
    row = 80;
    col = 30;
    accacia_clrscr();
#endif
    srand(time(NULL));
    if (gameinit()) {
        Winner();
    } else {
        Loser();
    }
#ifndef USE_ACCACIA
    accacia_getch();
    endwin();
#else
    accacia_delay(100);
    accacia_screennormalize();
    accacia_clrscr();
#endif
    return 0;
}
