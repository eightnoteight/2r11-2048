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
			mvprintw(((row-9)/2) + i*2,((col-32)/2) + j*8,"%d", board[i][j]);
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
void zerodrag()
{
	for (i = 0; i < 4; ++i)
	{
		/*drag out the non zero's*/
		for (j = 0; j < 4; ++j)
			if (board[j][i]==0)
				for (k = j+1; k < 4; ++k)
				{
					board[k-1]=board[k];
					board[k]=0;
				}
	}
}
void boardup(int a)
{
	int i,p,s;
	for (i = 0; i < 4; ++i)
	{
		/*drag out the non zero's*/
		zerodrag();/* i think it works without this line */
		for (j = 1; j < 4; ++j)
		{
			if (board[j][i]==board[j-1][i])
				board[j-1][i]*=2;
			zerodrag();
		}
	}
	s=rand()%(16-a);
	p=0;
	while(true)
	{
		if (p==s)
			break;
		p++;
		if (board[p/4][p%4])
		{
			p++;
			s++;
		}
	}
	board[p/4][p%4]=2;
}
void boarddown(int a)
{
	int i,p,s;
	for (i = 0; i < 4; ++i)
	{
		if(board[3][i]==board[2][i])
		{
			board[3][i] += board[2][i];
			board[2][i] = board[1][i];
			board[1][i] = board[0][i];
			board[0][i] = 0;
		}
		if (board[2][i]==board[1][i])
		{
			board[2][i] += board[1][i];
			board[1][i] = board[0][i];
			board[0][i] = 0;
		}
		if (board[1][i]==board[0][i])
		{
			board[1][i] += board[0][i];
			board[0][i] = 0;
		}
	}
	s=rand()%(16-a);
	p=0;
	while(true)
	{
		if (p==s)
			break;
		p++;
		if (board[p/4][p%4])
		{
			p++;
			s++;
		}
	}
	board[p/4][p%4]=2;
}
void boardleft(int a)
{
	int i,p,s;
	for (i = 0; i < 4; ++i)
	{
		if(board[i][0]==board[i][1])
		{
			board[i][0] += board[i][1];
			board[i][1] = board[i][2];
			board[i][2] = board[i][3];
			board[i][3] = 0;
		}
		if (board[i][1]==board[i][2])
		{
			board[i][1] += board[i][2];
			board[i][2] = board[i][3];
			board[i][3] = 0;
		}
		if (board[i][2]==board[i][3])
		{
			board[i][2] += board[i][3];
			board[i][3] = 0;
		}
	}
	s=rand()%(16-a);
	p=0;
	while(true)
	{
		if (p==s)
			break;
		p++;
		if (board[p/4][p%4])
		{
			p++;
			s++;
		}
	}
	board[p/4][p%4]=2;
}
void boardright(int a)
{
	int i,p,s;
	for (i = 0; i < 4; ++i)
	{
		if(board[i][3]==board[i][2])
		{
			board[i][3] += board[i][2];
			board[i][2] = board[i][1];
			board[i][1] = board[i][0];
			board[i][0] = 0;
		}
		if (board[i][2]==board[i][1])
		{
			board[i][2] += board[i][1];
			board[i][1] = board[i][0];
			board[i][0] = 0;
		}
		if (board[i][1]==board[i][0])
		{
			board[i][1] += board[i][0];
			board[i][0] = 0;
		}
	}
	s=rand()%(16-a);
	p=0;
	while(true)
	{
		if (p==s)
			break;
		p++;
		if (board[p/4][p%4])
		{
			p++;
			s++;
		}
	}
	board[p/4][p%4]=2;
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
		if (p==s)
			break;
		p++;
		if (board[p/4][p%4])
		{
			p++;
			s++;
		}
	}
	board[p/4][p%4]=2;
	return ;
}
int boardcheck()
{
	return 0;
}
boool gameinit()
{
	int c;
	int co;
	printboard();
	randboard();
	while((c=getch())!=27)
	{
		co=boardcount();
		switch(c)
		{
			case UP_KEY:
				boardup(co);
				break;
			case DOWN_KEY:
				boarddown(co);
				break;
			case LEFT_KEY:
				boardleft(co);
				break;
			case RIGHT_KEY:
				boardright(co);
				break;		
		}
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