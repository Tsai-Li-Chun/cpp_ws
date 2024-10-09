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

#define remoteIO_quantity 3
#define total_AP_IP "192.168.1.5"
#define camera_robot_AP_IP "192.168.1.6"
#define guide_robot_AP_IP "192.168.1.7"
#define remoteIO_IP_fence "192.168.1.11"
#define remoteIO_IP_camera_root "192.168.1.12"
#define remoteIO_IP_guide_root "192.168.1.13"
#define remoteIO_IP_stand "192.168.1.14"

/* cas lab module err code */
#define module_camera_robot_err (uint8_t)1
#define module_guide_robot_err 	(uint8_t)2
#define module_stand_err 		(uint8_t)3
#define module_AGV_err 			(uint8_t)4
#define module_ALL_healthy 		(uint8_t)5
#define module_network_err 		(uint8_t)6
#define module_fence_err 		(uint8_t)7

/* network error code */
#define network_fence_remoteIO_err			(uint8_t)0
#define network_camera_robot_remoteIO_err	(uint8_t)1
#define network_guide_robot_remoteIO_err	(uint8_t)2
#define network_stand_remoteIO_err			(uint8_t)3
#define network_total_AP_err				(uint8_t)4
#define network_camera_robot_AP_err			(uint8_t)5
#define network_guide_robot_AP_err			(uint8_t)6
#define network_stand_AP_err				(uint8_t)7
#define network_healthy						(uint8_t)99
/* fence error code */
#define fence_close	(uint8_t)0
#define fence_open	(uint8_t)1
/* camera_robot error code */
#define camera_robot_EMS_off (uint8_t)0
#define camera_robot_EMS_on	 (uint8_t)1
#define camera_robot_STO_adr (DO_Address)DO_Address::DO_1
/* guide_robot error code */
#define guide_robot_EMS_off (uint8_t)0
#define guide_robot_EMS_on (uint8_t)1
#define guide_robot_STO_adr (DO_Address)DO_Address::DO_2
#define guide_robot_reset_adr (DO_pulse_FixedTotal_Address)DO_pulse_FixedTotal_Address::DO_0
/* AGV error code */
#define AGV_EMS_off (uint8_t)0
#define AGV_EMS_on (uint8_t)1
#define AGV_STO_adr (DO_Address)DO_Address::DO_3
/* stand error code */
#define stand_EMS_off (uint8_t)0
#define stand_EMS_on (uint8_t)1
#define stand_STO_adr (DO_Address)DO_Address::DO_3

/* remoteIO DI/O signal, refer to actual wire */
#define DI_signal_efficient (uint8_t)1
#define DI_signal_invalid (uint8_t)0
#define DI_EMS_off (uint8_t)1
#define DI_EMS_on (uint8_t)0
#define DO_LED_enable (uint8_t)1
#define DO_LED_disable (uint8_t)0
#define DO_STO_enable (uint8_t)0
#define DO_STO_disable (uint8_t)1

/* parameters for controlling the StackLight  */
#define STO_interval (long)500	/* 500ms */
#define flash_interval (long)200	/* 100ms */
#define fence_GLED_adr (DO_Address)DO_Address::DO_3
#define fence_YLED_adr (DO_Address)DO_Address::DO_2
#define fence_RLED_adr (DO_Address)DO_Address::DO_1

/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */

enum remoteIO_number
{
	fence = 0,
	camera_robot = 1,
	guide_robot = 2,
	stand = 3,
	AGV = 3
};

struct lab_state
{
	uint8_t network;		/* reference network error code */
	uint8_t fence;			/* reference fence error code */
	uint8_t AGV;			/* reference stand error code */
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
