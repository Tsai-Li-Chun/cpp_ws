/** ******************************************************
	* @file		xbot_handshake.hpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __xbot_handshake_HPP__
#define __xbot_handshake_HPP__


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


/* Define ---------------------------------------------------*/
/* Define Begin */

/* define std::cout special display command */
#define TC_RESET "\033[0m"			// Normal 
#define TC_ERROR "\033[31m[ERROR] " // Red
#define TC_CLOSE "\x1B[2J\x1B[H "	// close
/* define serial port information */
#define PortName "/dev/ttyUSB0"
#define BuatRate B9600

/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */
/* Extern Typedef End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */

/* conversion u16 to u8 structure */
union modbus_u16tou8
{
    uint16_t u16;
    uint8_t  u8[ (sizeof(uint16_t))/sizeof(uint8_t) ];
};

/* define xbot heartbeat message format */
struct xbot_heartbeat_struct
{
	uint16_t head;					/* A5 5A */
	uint8_t  len;					/* message length */
	uint8_t  cmd_type;				/* command type, 21:query, 23:set, 25:heartbeat */
	uint8_t  car_id;				/* xbot car id */
	uint8_t  battery ;				/* battery power */
	uint16_t prescribed_speed;		/* prescribedspeed */
	uint8_t  movement_state;		/* 1:car moving, 0:car still */
	uint8_t  avoidance_stop;		/* 1:stop because of obstacles */
	uint8_t  arrive_stop;			/* 1:stop because of arrive waypoint */
	uint8_t  cmd_stop;				/* 1:stop because of command */
	uint16_t realtime_speed;		/* car current speed */
	uint8_t  current_waypoint;		/* car current waypoint */
	uint8_t  prescribed_waypoint;	/* prescribed waypoint */
	uint8_t  error_code;			/* error code */
	uint8_t  max_waypoint;			/* maximum number of waypoints */
	uint8_t  operation_mode;		/* operation mode */
	uint8_t  CRC;					/* CRC check number */
};


/* Extern Variables End */


/* Extern Class -------------------------------------------*/
/* Extern Class Begin */

/* define xbotAGV control object */
class xbot_HandShake
{
/* private mamber */
private:
	int i;
	modbus_u16tou8 u16tou8_tmp; 
	/* number of communications */
	long count = 1;
	/* serial port input buffer data length */
	int num_bytes = 0;
	/* serial port input buffer data */
	uint8_t read_buf[256];
	/* serial port semd buffer data */
	uint8_t msg[12];
	/* create serial port access configurtion struct */
	struct termios tty;
	/* device file */
	int serial_port;
	/* xbot heartbeat data */
	xbot_heartbeat_struct xbot_heartbeat;

	uint8_t calculate_CRC(void);


/* public mamber */
public:
	xbot_HandShake();	/* constructor */
	~xbot_HandShake();	/* destructor */

	void chech_control_cmd(void);		/* confirm control command(go to waypoint) */
	void chech_xbot_heartbeat(void);	/* check xbot heart beat command */
	bool check_waypoint_reached(void);	/* confirm if the waypoint has been reached */

	void send_xbot_waypoint_cmd(uint8_t waypoint);	/* send command to xbot */
	
	void run(void);		/* main function */
};

/* Extern Class End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */


#endif /*__xbot_handshake_HPP__ */

/* ***** END OF xbot_handshake.HPP ***** */
