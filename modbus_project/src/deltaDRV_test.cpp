/** ******************************************************
	* @file		deltaDRV_test.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <iostream>
#include <unistd.h>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "deltaDRV_modbus_HandShake.hpp"
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

ServoOnOff 		 _deltaDRV_servo_status;
InfoPUU 		 _deltaDRV_info_PUU;
InfoVel 		 _deltaDRV_info_vel;
InfoCur			 _deltaDRV_info_cur;
InfoCartesianPos _deltaDRV_info_CartesianPos;
InfojDegPos		 _deltaDRV_info_jDegPos;
InfoTemp		 _deltaDRV_info_temp;
InfoFramePosture _deltaDRV_info_FramePosture;
RobotStatus 	 _deltaDRV_status;
ErrorCode 		 _deltaDRV_ErrorCode;
JOGConfig 		 _deltaDRV_JOGConfig;
gotoTarget 		 _deltaDRV_GOTOTarget;
UserDIO_moniter  _deltaDRV_DIO_moniter;
RL_control 		 _deltaDRV_RLStatus;

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
	uint16_t i = 1;
	uint16_t data;

	deltaDRV_modbus_HandShake deltaDRV_modbus_HS(DRV_modbus_IP, DRV_modbus_port, DRV_modbus_slave);
	
	while(1)
	{
		deltaDRV_modbus_HS.read_deltaDRV_DataBuffer(0x3201,1,&data);
		printf("%4x\n",data);
		deltaDRV_modbus_HS.write_deltaDRV_DataBuffer(0x3201,i);
		if(i==0)	i=1;
		else if(i==1) i=0;
		sleep(3);
	}

	/* main quit */
	return 0;
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF deltaDRV_test.cpp ***** */
