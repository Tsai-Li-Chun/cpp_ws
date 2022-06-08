/**
 Linux (POSIX) implementation of _kbhit().
 Morgan McGuire, morgan@cs.brown.edu
 */
#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <iostream>
// #include <stropts.h>

int _kbhit()
{
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized)
	{
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

//////////////////////////////////////////////
//    Simple demo of _kbhit()

#include <unistd.h>



int maain(int argc, char** argv)
{
	uint8_t i;
	char c[255];
	int delay_time=0;
	system("stty -echo");
    while (1)
	{
		if( delay_time == 500 )
		{
			printf("program runiong...\n");
			delay_time = 0;
		}
		else
		{
			delay_time++;
			usleep(1000);
		}
		fflush(stdout);
		i=0;
		while( _kbhit() )
		{
			c[i] = getchar();
			i++;
		}
		if(i != 0)
		{
			printf("%d:\n",i);
			for( int j=0;j<i; j++ )
			printf("%d\n",c[j]);
		}
    }
    printf("\nDone.\n");

    return 0;
} 