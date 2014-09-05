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
		for (j = 0; j < 4; ++j)
        {
            switch(board[i][j])
            {
                case 0:
                    attron(COLOR_PAIR(7)|A_DIM);
                    break;
                case 2:
                    attron(COLOR_PAIR(1)|A_ITALIC);
                    break;
                case 4:
                    attron(COLOR_PAIR(2)|A_ITALIC);
                    break;
                case 8:
                    attron(COLOR_PAIR(3)|A_ITALIC);
                    break;
                case 16:
                    attron(COLOR_PAIR(4)|A_ITALIC);
                    break;
                case 32:
                    attron(COLOR_PAIR(5)|A_ITALIC);
                    break;
                case 64:
                    attron(COLOR_PAIR(1)|A_BOLD|A_ITALIC);
                    break;
                case 128:
                    attron(COLOR_PAIR(2)|A_BOLD|A_ITALIC);
                    break;
                case 256:
                    attron(COLOR_PAIR(3)|A_BOLD|A_ITALIC);
                    break;
                case 512:
                    attron(COLOR_PAIR(4)|A_BOLD|A_ITALIC);
                    break;
                case 1024:
                    attron(COLOR_PAIR(5)|A_BOLD|A_ITALIC);
                    break;
                case 2048:
                    attron(COLOR_PAIR(6)|A_BOLD|A_ITALIC|A_UNDERLINE);
                    break;
            }
			mvprintw(((row-9)/2) + i*2,((col-32)/2) + j*10,"%d\t",
                    board[i][j]);
            attrset(0);
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
boool legalmoves()
{
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
int nzcb()
{
	int nonz=0,i,j;
	for (i = 0; i < 4; ++i)
		for (j = 0; j < 4; ++j)
			if (board[i][j])
				nonz++;
	return nonz;
}
int boardcheck()
{
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
void randinsertboard()
{
	if ((16-nzcb())==0)
		return;
	/*assert((16-nzcb())!=0); remove the assert after 
     * checking checkboardfunction() */
	int s=rand()%(16-nzcb()),p;
	for(p=0;p<=s;++p)
		if (board[p/4][p%4])
			s++;
	board[s/4][s%4]=2;
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
inline void bunchcall(int* p, int* q, int* r, int* s)
{
	zerodrag(p,q,r,s);
	sumsitup(p,q,r,s);
}
char* hashgen()
{
	int i;
	for (i = 0; i < 16; ++i)
	{
		hash[i]=board[i/4][i%4]+48;
	}
	hash[16]='\0';
	return hash;
}
boool gameinit()
{
	int c;
	int i;
	char hashi[17];
	randinsertboard();
	randinsertboard();
	printboard();
	while((c=getch())!=27)
	{
		strcpy(hashi,hashgen());
		switch(c)
		{
			case UP_KEY:
				for(i=0;i<4;++i)
					bunchcall(&board[0][i],
                              &board[1][i],
                              &board[2][i],
                              &board[3][i]);
				break;
			case DOWN_KEY:
				for(i=0;i<4;++i)
					bunchcall(&board[3][i],
                              &board[2][i],
                              &board[1][i],
                              &board[0][i]);
				break;
			case LEFT_KEY:
				for(i=0;i<4;++i)
					bunchcall(&board[i][0],
                              &board[i][1],
                              &board[i][2],
                              &board[i][3]);
				break;
			case RIGHT_KEY:
				for(i=0;i<4;++i)
					bunchcall(&board[i][3],
                              &board[i][2],
                              &board[i][1],
                              &board[i][0]);
				break;		
		}
		if (strcmp(hashi,hashgen())!=0)
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
    return 0;
}
void Winner(){
	clear();
	mvprintw(row/2,(col-10)/2, "WINNER! :)");
}

void Loser(){
	clear();
	mvprintw(row/2,(col-8)/2, "LOSER :(");
}
int main(int argc, char const *argv[])
{
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
	srand(time(NULL));
	if (gameinit())
		Winner();
	else
		Loser();
	getch();
	endwin();
	return 0;
}
