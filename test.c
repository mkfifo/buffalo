#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#include "codes.h"

int main(){
	struct termios term, bkp;

	if( tcgetattr(1, &term) ){
		perror("failed to get termios\n");
		exit(1);
	}
	bkp = term;
	term.c_lflag = 0; // set non-canonical
	term.c_cc[VTIME] = 0; // set timeout
	term.c_cc[VMIN] = 1; // set read to return after it has one char available
	//tcflush(1, TCIFLUSH);
	if( tcsetattr(1, TCSANOW, &term) ){
		perror("Failed to set termios\n");
		exit(1);
	}

	// prepare terminal
	t_clear();
	f_normal();
	c_line0();

	//write(1, "hello\n", 6);
	char chs[7] = {0, 0, 0, 0, 0, 0, 0};
	int alive = 1;
	int interactive = 0;

	// testing
	f_normal();
	b_red();
	fputs("hello", stdout);
	f_blue();
	fputs("world", stdout);
	f_normal();
	
	int h = t_getheight();
	int i;
	c_goto(0,0);
	fputs("0", stdout);
	c_goto(1,1);
	fputs("1", stdout);
	c_goto(2,2);
	fputs("2", stdout);
	c_goto(h-3, h-3);
	fputs("-3", stdout);
	c_goto(h-2, h-2);
	fputs("-2", stdout);
	c_goto(h-1, h-1);
	fputs("-1", stdout);
	c_goto(h, h);
	fputs("-0", stdout);
	fflush(stdout);

	// main loop
	while( alive ){
		chs[0]=chs[1]=chs[2]=chs[3]=chs[4]=chs[5]=chs[6]=0;
		read(0, &chs, 7);
		/*write(1, "got:", 4);
			write(1, chs, 1);
			printf("%d\n", chs[0]); */
		if( chs[0] == '!' )
			break;
		if( chs[0] == '@' ){
			c_scrlu(1);
			continue;
		}
		if( chs[0] == '#' ){
			c_scrld(1);
			continue;
		}
		printf("%u %u %u %u %u %u %u\n", chs[0], chs[1], chs[2], chs[3], chs[4], chs[5], chs[6]);
		//write(1, chs, 2);
	}

	if( tcsetattr(1, TCSANOW, &bkp) ){
		perror("failed to reset termios setting back to the backup\n");
		exit(1);
	}
	// tidy up a little
	t_clear();
	c_line0();
	f_normal();
}
