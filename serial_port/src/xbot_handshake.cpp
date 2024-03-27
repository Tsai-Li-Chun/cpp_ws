/** ******************************************************
	* @file		xbot_handshake.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <iostream>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "xbot_handshake.hpp"
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

xbot_HandShake::xbot_HandShake()
{
	/* open device file = connect device */
	serial_port = open(PortName, O_RDWR | O_NOCTTY | O_SYNC);
	if( serial_port < 0 )	/* check device connect */
		printf("Error %i from open: %s\n",errno ,strerror(errno));
	/* read in serial port existing settings */
	if( tcgetattr(serial_port, &tty) != 0)
		printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));

	// tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
	// tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
	// tty.c_cflag &= ~CSIZE; 	// Clear all bits that set the data size 
	// tty.c_cflag &= ~CRTSCTS;// Disable RTS/CTS hardware flow control (most common)
	// tty.c_cflag &= ~CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)
	// // tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)
	// tty.c_cflag |= CS8; 	// 8 bits per byte (most common)
	// tty.c_cflag |= CREAD; // Turn on READ & ignore ctrl lines (CLOCAL = 1)
	tty.c_cflag &= ~(PARENB | CSTOPB | CSIZE | CRTSCTS | CLOCAL);
	tty.c_cflag |= (CS8 | CREAD);

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
	cfsetispeed(&tty, BuatRate);
	cfsetospeed(&tty, BuatRate);
	// Save tty settings, also checking for error
	if (tcsetattr(serial_port, TCSANOW, &tty) != 0)
		printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));

	memset(&read_buf, '\0', sizeof(read_buf));
}
xbot_HandShake::~xbot_HandShake()
{
	/* disconnect from the AAA document */
	close(serial_port);
}


void xbot_HandShake::chech_control_cmd(void)
{

}
void xbot_HandShake::chech_xbot_heartbeat(void)
{
	tcflush(serial_port, TCIOFLUSH);
	num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
    std::cout << TC_CLOSE << TC_RESET << std::endl;
	printf("%li , Read %i bytes : ",count ,num_bytes);
	for( i=0; i<num_bytes; i++ )
		printf("%02x ",read_buf[i]);
	printf("\n");
	if(num_bytes==20)
	{
		u16tou8_tmp.u8[0] = read_buf[0];
		u16tou8_tmp.u8[1] = read_buf[1];
		xbot_heartbeat.head = u16tou8_tmp.u16;
        printf("head               = 0x%04x\n",xbot_heartbeat.head);
		xbot_heartbeat.len = read_buf[2];
		printf("len                = %i bytes\n",xbot_heartbeat.len);
        xbot_heartbeat.cmd_type = read_buf[3];
		printf("cmd_type           = 0x%02x\n",xbot_heartbeat.cmd_type);
		xbot_heartbeat.car_id = read_buf[4];
		printf("car_id             = 0x%02x\n",xbot_heartbeat.car_id);
		xbot_heartbeat.battery = read_buf[5];
		printf("battery            = %i %%\n",xbot_heartbeat.battery);
		u16tou8_tmp.u8[0] = read_buf[6];
		u16tou8_tmp.u8[1] = read_buf[7];
		xbot_heartbeat.prescribed_speed = u16tou8_tmp.u16;
		printf("prescribed_speed   = %i m/h\n",xbot_heartbeat.prescribed_speed);
		xbot_heartbeat.movement_state = read_buf[8];
		printf("movement_state     = 0x%02x\n",xbot_heartbeat.movement_state);
		xbot_heartbeat.avoidance_stop = read_buf[9];
		printf("avoidance_stop     = 0x%02x\n",xbot_heartbeat.avoidance_stop);
		xbot_heartbeat.arrive_stop = read_buf[10];
		printf("arrive_stop        = 0x%02x\n",xbot_heartbeat.arrive_stop);
		xbot_heartbeat.cmd_stop = read_buf[11];
		printf("cmd_stop           = 0x%02x\n",xbot_heartbeat.cmd_stop);
		u16tou8_tmp.u8[0] = read_buf[12];
		u16tou8_tmp.u8[1] = read_buf[13];
		xbot_heartbeat.realtime_speed = u16tou8_tmp.u16;
		printf("realtime_speed     = %i m/s\n",xbot_heartbeat.realtime_speed);
		xbot_heartbeat.current_waypoint = read_buf[14];
		printf("current_waypoint   = 0x%02x\n",xbot_heartbeat.current_waypoint);
		xbot_heartbeat.prescribed_waypoint = read_buf[15];
		printf("prescribed_waypoint= 0x%02x\n",xbot_heartbeat.prescribed_waypoint);
		xbot_heartbeat.error_code = read_buf[16];
		printf("error_code         = %i\n",xbot_heartbeat.error_code);
		xbot_heartbeat.max_waypoint = read_buf[17];
		printf("max_waypoint       = %i\n",xbot_heartbeat.max_waypoint);
		xbot_heartbeat.operation_mode = read_buf[18];
		printf("operation_mode     = 0x%02x\n",xbot_heartbeat.operation_mode);
		xbot_heartbeat.CRC = read_buf[19];
		printf("CRC                = 0x%02x\n",xbot_heartbeat.CRC);
		std::cout << TC_RESET;
	}
	count++;
}
bool xbot_HandShake::check_waypoint_reached(void)
{
	chech_xbot_heartbeat();
	if( xbot_heartbeat.arrive_stop==1 )
	{
        if(xbot_heartbeat.realtime_speed == 0)
        {
            if( xbot_heartbeat.movement_state == 1 )
            {
                std::cout << std::endl << "reached the target waypoint!" << std::endl;
                return 0;
            }
        }
	}

	std::cout << "En route to the destination waypoint......" << std::endl;
	return 1;
}


void xbot_HandShake::send_xbot_waypoint_cmd(uint8_t waypoint)
{
	msg[0] = 0x00;
	msg[1] = 0x01;
	msg[2] = 0x04;
	msg[3] = 0xA5;
	msg[4] = 0x5A;
	msg[5] = 0x08;
	msg[6] = 0x23;
	msg[7] = 0x9D;
	msg[8] = waypoint;
	msg[9] = 0x00;
	// msg[10] = calculate_CRC();
	calculate_CRC();	// set msg[10] CRC
	msg[11] = '\0';
	write(serial_port, msg, sizeof(msg));
    printf("send to xbot waypoint command : 0x%02x\n",msg[8]);
    printf("send to xbot CRC     : 0x%02x\n",msg[10]);
}


void xbot_HandShake::run(void)
{

}


uint8_t xbot_HandShake::calculate_CRC(void)
{
	msg[10] = msg[3]+msg[4]+msg[5]+msg[6]+msg[7]+msg[8]+msg[9];
	return msg[10];
}


/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF xbot_handshake.cpp ***** */
