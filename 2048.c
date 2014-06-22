#include "2048.h"

#define UP_KEY 259
#define DOWN_KEY 258
#define LEFT_KEY 260
#define RIGHT_KEY 261
#define ENTER 10

void printboard()
{
	int i,j;
	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			mvprintw(((row-9)/2) + i*2,((col-32)/2) + j*10,"%d   ", board[i][j]);
		}
	}
}
int boardcount()
{
	int pint=0,i,j;
	for (i = 0; i < 4; ++i)
		for (j = 0; j < 4; ++j)
			if (board[i][j])
				pint++;
	return pint;
}
void randboard()
{
	int f,s,i,p;
	static call=1;
	if (call--)
		srand(time(NULL));

	f=rand()%16;
	board[f/4][f%4]=2;
	s=rand()%15;
	p=0;
	while(true)
	{
		if (board[p/4][p%4])
		{
			p++;
			s++;
		}
		if (p==s)
			break;
		p++;
	}
	board[p/4][p%4]=2;
	return ;
}
int boardcheck()
{
	return 0;
}
void zerodrag(int* p, int* q, int* r, int* s)
{
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
void sumsitup(int* p, int* q, int* r, int* s)
{
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
void randinsertboard()
{
	int s=rand()%(16-nzcb());
	int p=0;
	while(true)
	{
		if (board[p/4][p%4])
		{
			p++;
			s++;
		}
		if (p==s)
			break;
		p++;
	}
	board[p/4][p%4]=2;
}
int nzcb()
{
	int nonz=0,i,j;
	for (i = 0; i < 4; ++i)
		for (j = 0; j < 4; ++j)
			if (board[i][j])
				nonz++;
	return nonz;
}
inline void bunchcall(int* p, int* q, int* r, int* s)
{
	zerodrag(p,q,r,s);
	sumsitup(p,q,r,s);
}
boool gameinit()
{
	int c;
	int co;
	int i;
	printboard();
	randboard();
	while((c=getch())!=27)
	{
		co=boardcount();
		switch(c)
		{
			case UP_KEY:
				for(i=0;i<4;++i)
					bunchcall(&board[0][i],&board[1][i],&board[2][i],&board[3][i]);
				break;
			case DOWN_KEY:
				for(i=0;i<4;++i)
					bunchcall(&board[3][i],&board[2][i],&board[1][i],&board[0][i]);
				break;
			case LEFT_KEY:
				for(i=0;i<4;++i)
					bunchcall(&board[i][0],&board[i][1],&board[i][2],&board[i][3]);
				break;
			case RIGHT_KEY:
				for(i=0;i<4;++i)
					bunchcall(&board[i][3],&board[i][2],&board[i][1],&board[i][0]);
				break;		
		}
		randinsertboard();
		printboard();
		switch(boardcheck())
		{
			case 1:
				return 1;
				break;/*not required*/
			case -1:
				return 0;
				break;/*not required*/
			case 0:
				continue;
				break;/*not required*/
		}
	}
}
void Winner()
{

}
void Loser()
{

}
int main(int argc, char const *argv[])
{
	initscr();
	raw();
	noecho();
	curs_set(0);
	keypad(stdscr,TRUE);
	getmaxyx(stdscr,row,col);
	if (gameinit())
		Winner();
	else
		Loser();
	getch();
	endwin();
	return 0;
}