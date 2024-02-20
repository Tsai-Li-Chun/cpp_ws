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
#include <vector>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "WISE4060_ModbusAddressTable.hpp"
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */

#define remoteIO_quantity 4
#define total_AP_IP "192.168.1.5"
#define remoteIO_IP_fence "192.168.1.11"
#define remoteIO_IP_camera_root "192.168.1.12"
#define remoteIO_IP_guide_root "192.168.1.13"
#define remoteIO_IP_stand "192.168.1.15"

/* network error code */
#define network_healthy						(uint8_t)0
#define network_total_AP_err				(uint8_t)1
#define network_camera_robot_AP_err			(uint8_t)2
#define network_guide_robot_AP_err			(uint8_t)3
#define network_stand_AP_err				(uint8_t)4
#define network_fence_remoteIO_err			(uint8_t)5
#define network_camera_robot_remoteIO_err	(uint8_t)6
#define network_guide_robot_remoteIO_err	(uint8_t)7
#define network_stand_remoteIO_err			(uint8_t)8
/* fence error code */
#define fence_close (uint8_t)0
#define fence_open (uint8_t)1
/* camera_robot error code */
#define camera_robot_EMS_on (uint8_t)0
#define camera_robot_EMS_off (uint8_t)1
/* guide_robot error code */
#define guide_robot_EMS_on (uint8_t)0
#define guide_robot_EMS_off (uint8_t)1
/* stand error code */
#define AGV_EMS_on (uint8_t)0
#define AGV_EMS_off (uint8_t)1


/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */

enum remoteIO_number
{
	remoteIO_number_fence = 0,
	remoteIO_number_camera_robot = 1,
	remoteIO_number_guide_robot = 2,
	remoteIO_number_stand = 3
};

struct lab_state
{
	uint8_t network;		/* reference network error code */
	uint8_t fence;			/* reference fence error code */
	uint8_t camera_robot;	/* reference camera_robot error code */
	uint8_t guide_robot;	/* reference guide_robot error code */
	uint8_t stand;			/* reference stand error code */
};

/* Extern Typedef End */


/* Extern Class -------------------------------------------*/
/* Extern Class Begin */
/* Extern Class End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */
extern std::vector<std::string> remoteIO_IP;
/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */


#endif /*__CASLab_SafetySystemDefineTable_HPP__ */

/* ***** END OF CASLab_SafetySystemDefineTable.HPP ***** */
