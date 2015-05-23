#include "2048.h"
#include "2048ac.h"

void ac_printboard() {
    int i,j, x, y = 10;
    int bkcolor = 0;
    accacia_drawbox(row / 2 - 1, y - 1, 40, 25, AC_BCOLOR_WHITE);
    accacia_drawbox(row / 2, y, 38, 23, AC_BCOLOR_BLACK);
    for (i = 0; i < 4; ++i, y += 6) {
        x = row / 2;
	for (j = 0; j < 4; ++j, x += 10) {
            switch(board[i][j]) {
                case 0:
                    accacia_textcolor(AC_TCOLOR_WHITE);
                    bkcolor = AC_BCOLOR_BLUE;
                    break;
                case 2:
                    accacia_textcolor(AC_TCOLOR_RED);
                    bkcolor = AC_BCOLOR_GREEN;
                    break;
                case 4:
                    accacia_textcolor(AC_TCOLOR_GREEN);
                    bkcolor = AC_BCOLOR_YELLOW;
                    break;
                case 8:
                    accacia_textcolor(AC_TCOLOR_YELLOW);
                    bkcolor = AC_BCOLOR_CYAN;
                    break;
                case 16:
                    accacia_textcolor(AC_TCOLOR_BLUE);
                    bkcolor = AC_BCOLOR_RED;
                    break;
                case 32:
                    accacia_textcolor(AC_TCOLOR_MAGENTA);
                    bkcolor = AC_BCOLOR_CYAN;
                    break;
                case 64:
                    accacia_textstyle(AC_TSTYLE_BOLD);
                    accacia_textcolor(AC_TCOLOR_RED);
                    bkcolor = AC_BCOLOR_GREEN;
                    break;
                case 128:
                    accacia_textstyle(AC_TSTYLE_BOLD);
                    accacia_textcolor(AC_TCOLOR_GREEN);
                    bkcolor = AC_BCOLOR_YELLOW;
                    break;
                case 256:
                    accacia_textstyle(AC_TSTYLE_BOLD);
                    accacia_textcolor(AC_TCOLOR_BLACK);
                    bkcolor = AC_BCOLOR_WHITE;
                    break;
                case 512:
                    accacia_textstyle(AC_TSTYLE_BOLD);
                    accacia_textcolor(AC_TCOLOR_BLUE);
                    bkcolor = AC_BCOLOR_RED;
                    break;
                case 1024:
                    accacia_textstyle(AC_TSTYLE_BOLD);
                    accacia_textcolor(AC_TCOLOR_MAGENTA);
                    bkcolor = AC_BCOLOR_CYAN;
                    break;
                case 2048:
                    accacia_textstyle(AC_TSTYLE_BOLD);
                    accacia_textcolor(AC_TCOLOR_CYAN);
                    bkcolor = AC_BCOLOR_RED;
                    break;
            }
            accacia_drawbox(x, y, 8, 5, bkcolor);
            accacia_gotoxy(x + 2, y + 2);printf("%.4d", board[i][j]);
            accacia_screennormalize();
            accacia_gotoxy(1,1);printf("w = Up / s = Down / a = Left / d = Right / ESC = Quit\n");
            accacia_delline();
        }
    }
}

int ac_gameinit() {
    int c = 'i';
    int i;
    char hashi[17];
    randinsertboard();
    randinsertboard();
    ac_printboard();
    while (c != 27) {
        if (accacia_kbhit()) {
            c = accacia_getch();
	    strcpy(hashi,hashgen());
	    switch(c) {
	        case UP_KEY:
		    for(i=0;i<4;++i) {
		        bunchcall(&board[0][i], &board[1][i], &board[2][i], &board[3][i]);
                    }
		    break;
	        case DOWN_KEY:
		    for(i=0;i<4;++i) {
		        bunchcall(&board[3][i], &board[2][i], &board[1][i], &board[0][i]);
                    }
		    break;
		case LEFT_KEY:
		    for(i=0;i<4;++i) {
		        bunchcall(&board[i][0], &board[i][1], &board[i][2], &board[i][3]);
                    }
		    break;
		case RIGHT_KEY:
		    for(i=0;i<4;++i) {
		        bunchcall(&board[i][3], &board[i][2], &board[i][1], &board[i][0]);
                    }
		    break;
	    }
	    if (strcmp(hashi,hashgen())!=0) {
		randinsertboard();
            }
	    ac_printboard();
	    switch(boardcheck()) {
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
    return 0;
}

void ac_Winner() {
    accacia_clrscr();
    while (!accacia_kbhit()) {
        accacia_textstyle(AC_TSTYLE_BOLD);
        accacia_textcolor(AC_TCOLOR_GREEN);
        accacia_gotoxy(row / 3 + 18, col / 2);printf("W    I    N    N    E    R    !   :)\n");
        accacia_delay(100);
        accacia_textstyle(AC_TSTYLE_DEFAULT);
        accacia_textcolor(AC_TCOLOR_GREEN);
        accacia_gotoxy(row / 3 + 18, col / 2);printf("W    I    N    N    E    R    !   :)\n");
        accacia_delay(100);
    }
}

void ac_Loser() {
    accacia_clrscr();
    while (!accacia_kbhit()) {
        accacia_textstyle(AC_TSTYLE_BOLD);
        accacia_textcolor(AC_TCOLOR_RED);
        accacia_gotoxy(row / 3 + 22, col / 2);printf("L    O    S    E    R     :(\n");
        accacia_delay(100);
        accacia_textstyle(AC_TSTYLE_DEFAULT);
        accacia_textcolor(AC_TCOLOR_RED);
        accacia_gotoxy(row / 3 + 22, col / 2);printf("L    O    S    E    R     :(\n");
        accacia_delay(100);
    }
}
