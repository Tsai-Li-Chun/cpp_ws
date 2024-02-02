/** ******************************************************
	* @file		deltaDRV_test.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <iostream>
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

	deltaDRV_modbus_HandShake deltaDRV_modbus_HS(DRV_modbus_IP, DRV_modbus_port, DRV_modbus_slave);
	
	rc = deltaDRV_modbus_HS.read_deltaDRV_info_PUU(&_deltaDRV_info_PUU);
	std::cout << "rc : " << rc << std::endl;
	std::cout << "PUU a1 : " << _deltaDRV_info_PUU.ex_axis1 << std::endl;
	std::cout << "PUU a2 : " << _deltaDRV_info_PUU.ex_axis2 << std::endl;
	std::cout << "PUU a3 : " << _deltaDRV_info_PUU.ex_axis3 << std::endl;
	std::cout << "PUU a4 : " << _deltaDRV_info_PUU.ex_axis4 << std::endl;
	std::cout << "PUU j1 : " << _deltaDRV_info_PUU.j1 << std::endl;
	std::cout << "PUU j2 : " << _deltaDRV_info_PUU.j2 << std::endl;
	std::cout << "PUU j3 : " << _deltaDRV_info_PUU.j3 << std::endl;
	std::cout << "PUU j4 : " << _deltaDRV_info_PUU.j4_ << std::endl;
	std::cout << "PUU j5 : " << _deltaDRV_info_PUU._j5 << std::endl;
	std::cout << "PUU j6 : " << _deltaDRV_info_PUU.j6 << std::endl;

	/* main quit */
	return 0;
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF deltaDRV_test.cpp ***** */
