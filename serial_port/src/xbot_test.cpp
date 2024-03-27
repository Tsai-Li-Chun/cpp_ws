/** ******************************************************
	* @file		xbot_test.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <iostream>
#include <stdio.h>	// C library headers
#include <string.h>	// C library headers
#include <fcntl.h>	// contains file controls like  O_RDWR
#include <errno.h>	// error integer and strerror() function
#include <termios.h>// contains POSIX terminal control definitions
#include <unistd.h>	// write(), read(), close(), sleep()
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "deltaDRV_modbus_HandShake.hpp"
#include "xbot_handshake.hpp"
/* User Includes End */

/* namespace ------------------------------------------------*/
/* namespace Begin */
/* namespace End */


/* Define ---------------------------------------------------*/
/* Define Begin */
#define control_cmd_adr 0x1EFE
#define max_waypoint 2
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
	int rc;
	uint16_t control_cmd;
	xbot_HandShake xbot_HS;
	deltaDRV_modbus_HandShake deltaDRV_ctl(DRV_modbus_IP, DRV_modbus_port, DRV_modbus_slave);
	rc = deltaDRV_ctl.write_deltaDRV_DataBuffer(control_cmd_adr,0);
	std::cout << rc << ", " << "xbot_HS create finish, write Set control_cmd_adr to 0" << std::endl;

	while(1)
	{
		rc = deltaDRV_ctl.read_deltaDRV_DataBuffer(control_cmd_adr,1,&control_cmd);
		std::cout << rc << ", " << "read control_cmd_adr data : " << control_cmd << std::endl;
		if( control_cmd == 0 )
		{
			xbot_HS.chech_xbot_heartbeat();
		}
		else if( (control_cmd>=1) && (control_cmd<=max_waypoint) )
		{
			printf("receive control go to waypoint command : 0x%02x\n",control_cmd);
			xbot_HS.send_xbot_waypoint_cmd(control_cmd);
			while(xbot_HS.check_waypoint_reached())
			{
				deltaDRV_ctl.read_deltaDRV_DataBuffer(control_cmd_adr,1,&control_cmd);
			};
			rc = deltaDRV_ctl.write_deltaDRV_DataBuffer(control_cmd_adr,100);
			std::cout << rc << ", " << "xbot_HS create finish, write Set control_cmd_adr to 0" << std::endl;

		}
		else
			std::cout << TC_ERROR << "control_cmd Error!" << TC_RESET << std::endl;
		std::cout << "-----------------------------------------" << std::endl << std::endl;
		deltaDRV_ctl.read_deltaDRV_DataBuffer(control_cmd_adr,1,&control_cmd);
	}	

	/* main quit */
	return 0;
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF xbot_test.cpp ***** */
