/** ******************************************************
	* @file		hantas_screwdriver_controller.hpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __hantas_screwdriver_controller_HPP__
#define __hantas_screwdriver_controller_HPP__


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "modbus/modbus.h"
#include "hantas_M5_DefineTable.hpp"
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */

#define TC_RESET "\033[0m"			// Normal 
#define TC_ERROR "\033[31m[ERROR] " // Red
#define TC_CLOSE "\x1B[2J\x1B[H "	// close

#define hantas_screwdriver_ip "192.168.1.200"
#define hantas_screwdriver_port 5000
#define hantas_screwdriver_slaveID 0
#define deltaDRV_ip "192.168.1.1"
#define deltaDRV_port 502
#define deltaDRV_slaveID 2

#define robot_cmd_adr 0x1EFD
#define robot_cmd_lock_screw 1
#define robot_cmd_take_out_screw 2

#define Monitoring_Status_adr 3212
#define realtime_Speed_adr 3301
#define realtime_CurrentPreset_adr 3303
#define realtime_TorqueUp_adr 3304
#define realtime_FasteningOK_adr 3305
#define realtime_Ready_adr 3306
#define realtime_MotorRUN_adr 3307
#define realtime_AlarmNO_adr 3308
#define realtime_Forward_Loosening_adr 3309
#define realtime_ScrewCountValue_adr 3310
#define realtime_MotorTemperature_adr 3313
#define RemoteControl_AlarmReset_adr 4000
#define RemoteControl_DriverLock_adr 4001
#define RemoteControl_Start_adr 4003
#define RemoteControl_PresetChange_adr 4004
#define RemoteControl_Forward_Loosening_adr 4005

#define Forward (uint16_t)0
#define Loosening (uint16_t)1



/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */
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


#endif /*__hantas_screwdriver_controller_HPP__ */

/* ***** END OF hantas_screwdriver_controller.HPP ***** */
