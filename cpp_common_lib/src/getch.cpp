#include <stdio.h>
#include <termios.h>

#include "terminal/getch.h"

namespace cupid
{
static struct termios old_term;
static struct termios new_term;

/* Initialize new terminal i/o settings */
void init_termios(int echo) 
{  
	tcgetattr(0, &old_term); /* grab old terminal i/o settings */  
	new_term = old_term; /* make new settings same as old settings */  
	new_term.c_lflag &= ~ICANON; /* disable buffered i/o */  
	new_term.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */  
	tcsetattr(0, TCSANOW, &new_term); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void reset_termios(void) 
{  
	tcsetattr(0, TCSANOW, &old_term);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{  
	char ch;  
	init_termios(echo); 
	ch = getchar();  
	reset_termios();  
	return ch;
}

/* Read 1 character without echo */
char cupid_getch() 
{  
	return getch_(0);
}

/* Read 1 character with echo */
char cupid_getche() 
{  
	return getch_(1);
}

} // end of namespace cupid
