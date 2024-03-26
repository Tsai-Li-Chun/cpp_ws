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
#include <unistd.h>	// write(), read(), close(), sleep()
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
	// Allocate memory for read buffer, set size according to your needs
	long count = 1;
	int i,num_bytes = 0;
	char read_buf[256];
	/* create serial port access configurtion struct */
	struct termios tty;
	/* open device file = connect device */
	int serial_port = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_SYNC);
	/* check device connect */
	if( serial_port < 0 )
		printf("Error %i from open: %s\n",errno ,strerror(errno));
	/* read in serial port existing settings */
	if( tcgetattr(serial_port, &tty) != 0)
    	printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));

	tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
	tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
	tty.c_cflag &= ~CSIZE; 	// Clear all bits that set the data size 
	tty.c_cflag |= CS8; 	// 8 bits per byte (most common)
	tty.c_cflag &= ~CRTSCTS;// Disable RTS/CTS hardware flow control (most common)
	// tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)
	tty.c_cflag |= CREAD; // Turn on READ & ignore ctrl lines (CLOCAL = 1)
	tty.c_cflag &= ~CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

	// tty.c_lflag &= ~ICANON;
	// tty.c_lflag &= ~ECHO;	// Disable echo
	// tty.c_lflag &= ~ECHOE;	// Disable erasure
	// tty.c_lflag &= ~ECHONL;	// Disable new-line echo
	// tty.c_lflag &= ~ISIG;	// Disable interpretation of INTR, QUIT and SUSP
	tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN | ECHOE);
	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
	tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

	tty.c_oflag &= ~OPOST;	// Prevent special interpretation of output bytes (e.g. newline chars)
	tty.c_oflag &= ~ONLCR;	// Prevent conversion of newline to carriage return/line feed
	// tty.c_oflag &= ~OXTABS;	// Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
	// tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

	tty.c_cc[VTIME] = 50;	// Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
	tty.c_cc[VMIN] = 0;

	// Set in/out baud rate to be 9600
	cfsetispeed(&tty, B9600);
	cfsetospeed(&tty, B9600);

	// Save tty settings, also checking for error
	if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
		printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
		return 1;
	}
	memset(&read_buf, '\0', sizeof(read_buf));

	while(1)
	{
		// Read bytes. The behaviour of read() (e.g. does it block?,
		// how long does it block for?) depends on the configuration
		// settings above, specifically VMIN and VTIME
		tcflush(serial_port, TCIOFLUSH);
		num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
		printf("%li , Read %i bytes : ",count ,num_bytes);
		for( i=0; i<num_bytes; i++ )
			printf("%02x ",read_buf[i]);
		printf("\n");
		count++;
		// // print bytes length and read_buf data
		// if( num_bytes == read_buf[2] )
		// {
		// 	printf("Read %i bytes : ",num_bytes);
		// 	for( i=0; i<num_bytes; i++ )
		// 		printf("%02x ",read_buf[i]);
		// 	printf("\n");
		// }
		// else
		// {
		// 	printf(" num_bytes != read_buf[2]\n");
		// }
		// // sleep(1);
	}	
	/* main quit */
	return 0;
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF xbot_handshake.cpp ***** */
