/** ******************************************************
	* @file		deltaDRV_modbus_defineTable.hpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __deltaDRV_modbus_defineTable_HPP__
#define __deltaDRV_modbus_defineTable_HPP__


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include "stdint.h"
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */

#define DRV_modbus_IP "192.168.1.2"
#define DRV_modbus_port 502
#define DRV_modbus_slave 1

/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */
/* Extern Typedef End */


/* Extern Class -------------------------------------------*/
/* Extern Class Begin */

enum class servo_OnOff:int
{
	robot_j5j6 = 0,
	external_axis12 = 1,
	external_axis34 = 2,
	robot_j1j2 = 6,
	robot_j3j4 = 7,
};

/* Extern Class End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */
/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */


#endif /*__deltaDRV_modbus_defineTable_HPP__ */

/* ***** END OF deltaDRV_modbus_defineTable.HPP ***** */
