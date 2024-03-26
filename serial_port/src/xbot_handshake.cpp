/** ******************************************************
	* @file		xbot_handshake.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <stdio.h>	// C library headers
#include <string.h>	// C library headers
#include <fcntl.h>	// contains file controls like  O_RDWR
#include <errno.h>	// error integer and strerror() function
#include <termios.h>// contains POSIX terminal control definitions
#include <unistd.h>	// write(), read(), close()
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
/* User Includes End */

/* namespace ------------------------------------------------*/
/* namespace Begin */
/* namespace End */


/* Define ---------------------------------------------------*/
/* Define Begin */
/* Define End */


/* Typedef --------------------------------------------------*/
/* Typedef Begin */
/* Typedef End */


/* Class --------------------------------------------------*/
/* Class Begin */
/* Class End */


/* Variables ------------------------------------------------*/
/* Variables Begin */
/* Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */



/* ---------------------------------------------------------*/
/* ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩ Program ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩ ---------------------------*/
/* ---------------------------------------------------------*/
/* Program Begin */

/** * @brief  Program entry point.
	* @param argc(int) Number of input parameters
 	* @param argv(int) input parameters
 	* @return (int) Program Error.
**	**/
int main(int argc, char **argv)
{
	/* create serial port access configurtion struct */
	struct termios tty;
	/* open device file = connect device */
	int serial_port = open("/dev/ttyUSB0", O_RDWR);
	/* check device connect */
	if( serial_port < 0 )
		printf("Error %i from open: %s\n",errno ,strerror(errno));
	/* read in serial port existing settings */
	if(tcgetattr(serial_port, &tty) != 0)
    	printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
	
	/* main quit */
	return 0;
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF xbot_handshake.cpp ***** */
