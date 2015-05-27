#include "2048.h"
#include <accacia.h>
#include "2048nc.h"

void nc_printboard()
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
			mvprintw(((row-9)/2) + i*2,((col-32)/2) + j*10,"%d    \t",
                    board[i][j]);
            attrset(0);
        }
}

int nc_gameinit()
{
	int c;
	int i;
	char hashi[17];
	randinsertboard();
	randinsertboard();
	nc_printboard();
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
		nc_printboard();
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
void nc_Winner(){
	clear();
	mvprintw(row/2,(col-10)/2, "WINNER! :)");
}

void nc_Loser(){
	clear();
	mvprintw(row/2,(col-8)/2, "LOSER :(");
}
