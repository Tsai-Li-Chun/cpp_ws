/** ******************************************************
	* @file		CASLab_SafetySystemDefineTable.hpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __CASLab_SafetySystemDefineTable_HPP__
#define __CASLab_SafetySystemDefineTable_HPP__


/* System Includes ------------------------------------------*/
/* System Includes Begin */
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "WISE4060_ModbusAddressTable.hpp"
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */

#define fence_remoteIO_IP "192.168.1.11"
#define camera_root_remoteIO_IP "192.168.1.12"
#define guide_root_remoteIO_IP "192.168.1.13"
#define stand_remoteIO_IP "192.168.1.14"

/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */

struct state
{
	/* 0:healthy, 1: */
	uint8_t network;
	uint8_t fence;
	uint8_t camera_robot;
	uint8_t guide_robot;
	uint8_t stand;
};

/* Extern Typedef End */


/* Extern Class -------------------------------------------*/
/* Extern Class Begin */
/* Extern Class End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */
/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */


#endif /*__CASLab_SafetySystemDefineTable_HPP__ */

/* ***** END OF CASLab_SafetySystemDefineTable.HPP ***** */
