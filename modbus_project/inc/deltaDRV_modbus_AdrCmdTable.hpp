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

#define DRV_modbus_IP "192.168.1.1"
#define DRV_modbus_port 502
#define DRV_modbus_slave 2

/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */
/* Extern Typedef End */


/* Extern Class -------------------------------------------*/
/* Extern Class Begin */

/* DRV modbus address Table */
/* --------------------------------------------------------------------- */

/* Servo ON/OFF modbus address and command */
#define ServoOnOff_len 1
#define ServoOnOff_qan 5
const int ServoOnOff_adr[ServoOnOff_qan] = {0, 1, 2, 6, 7};
enum class ServoOnOff_con:int
{	j5j6 	= 0,
	axis12	= 1,
	axis34 	= 2,
	j1j2 	= 3,
	j3j4 	= 4		};
enum class ServoOnOff_cmd:uint16_t
{	H_ON 	= 0x0100,
	L_ON 	= 0x0001,
	HL_ON	= 0x0101,
	HL_OFF	= 0x0000	};
/* Servo Alarm Reset and command */
#define ServoAlarmReset_len 1
#define ServoAlarmReset_qan 6
const int ServoAlarmReset_adr[ServoAlarmReset_qan] = {32, 33, 34, 38, 39, 384};
enum class ServoAlarmReset_con:int
{	j5j6 	= 0,
	axis12	= 1,
	axis34	= 2,
	j1j2 	= 3,
	j3j4 	= 4,
	ALL 	= 5	};
enum class ServoAlarmReset_cmd:uint16_t
{	H_reset	= 0x0100,
	L_reset	= 0x0001,
	HL_reset= 0x0101	};
/* Robot Information "Joint Position" PUU */
#define InfoPUU_len 2
#define InfoPUU_qan 10
const int InfoPUU_adr[InfoPUU_qan] = {128, 130, 132, 134, 136, 138, 152, 154, 156, 158};
enum class InfoPUU_con:int
{	j5 = 0,
	j6 = 1,
	axis1 = 2,
	axis2 = 3,
	axis3 = 4,
	axis4 = 5,
	j1 = 6,
	j2 = 7,
	j3 = 8,
	j4 = 9	};
/* Robot Information "Joint Velocity" 0.1rpm */
#define InfoVel_len 2
#define InfoVel_qan 10
#define InfoVel_Resolution (float)0.1 /* rpm */
const int InfoVel_adr[InfoVel_qan] = {160, 162, 164, 166, 168, 170, 184, 186, 188, 190};
enum class InfoVel_con:int
{	j5 = 0,
	j6 = 1,
	axis1 = 2,
	axis2 = 3,
	axis3 = 4,
	axis4 = 5,
	j1 = 6,
	j2 = 7,
	j3 = 8,
	j4 = 9	};
/* Robot Information "Joint Current" 0.01% */
#define InfoCur_len 2
#define InfoCur_qan 10
#define InfoCur_Resolution (float)0.01 /* % percent */
const int InfoCur_adr[InfoCur_qan] = {192, 194, 196, 198, 200, 202, 216, 218, 220, 222};
enum class InfoCur_con:int
{	j5 = 0,
	j6 = 1,
	axis1 = 2,
	axis2 = 3,
	axis3 = 4,
	axis4 = 5,
	j1 = 6,
	j2 = 7,
	j3 = 8,
	j4 = 9	};
/* Robot Information "Cartesion Posture" */
#define InfoCartesianPos_len 2
#define InfoCartesianPos_qan 7
#define InfoCartesianPos_Resolution (float)0.001 /* to be confirmed */
const int InfoCartesianPos_adr[InfoCartesianPos_qan] = {240, 242, 244, 246, 248, 250, 254};
enum class InfoCartesianPos_con:int
{	X= 0,
	Y = 1,
	Z = 2,
	RX = 3,
	RY = 4,
	RZ = 5,
	Speed = 6	};
/* Servo Motor Information "Degree Position" */
#define InfojDegPos_len 2
#define InfojDegPos_qan 6
#define InfojDegPos_Resolution (float)0.001 /* Degree(?) */
const int InfojDegPos_adr[InfojDegPos_qan] = {360, 362, 364, 366, 336, 338};
enum class InfojDegPos_con:int
{	j1 = 0,
	j2 = 1,
	j3 = 2,
	j4 = 3,
	j5 = 4,
	j6 = 5	};
/* Robot Information Temperature */
#define InfoTemp_len 1
#define InfoTemp_qan 6
const int InfoTemp_adr[InfoTemp_qan] = {272, 273, 274, 275, 276, 277};
enum class InfoTemp_con:int
{	j1 = 0,
	j2 = 1,
	j3 = 2,
	j4 = 3,
	j5 = 4,
	j6 = 5	};
/* Robot Information "Robot Frame" and "Cartesion Posture" */
#define InfoFramePosture_len 1
#define InfoFramePosture_qan 3
const int InfoFramePosture_adr[InfoFramePosture_qan] = {226, 227, 228};
enum class InfoFramePosture_con:int
{	userframe= 0,
	toolframe= 1,
	Posture = 2		};
/* Robot Information "Joint index" */
#define InfoJRC_len 1
#define InfoJRC_qan 2
const int InfoJRC_adr[InfoJRC_qan] = {268, 269};
enum class InfoJRC_con:int
{	j1234 = 0,
	j56	  = 1		};
/* Robot System Status */
#define RobotStatus_len 1
#define RobotStatus_qan 5
const int RobotStatus_adr[RobotStatus_qan] = {224, 312, 313, 315, 514};
enum class RobotStatus_con:int
{	motion	= 0,
	system	= 1,
	OPmode	= 2,
	TPmode	= 3,
	DRVready= 4	};
/* error code */
#define ErrorCode_len 1
#define ErrorCode_qan 13
const int ErrorCode_adr[ErrorCode_qan] = {320, 321, 322, 323, 324, 325, 332, 333, 334, 335, 480, 511, 526};
enum class ErrorCode_con:int
{	j5		= 0,
	j6 		= 1,
	axis1	= 2,
	axis2	= 3,
	axis3	= 4,
	axis4	= 5,
	j1 		= 6,
	j2 		= 7,
	j3 		= 8,
	j4 		= 9,
	system 	= 10,
	DRV		= 11,
	warning = 12	};
/* Digital Input & Output */
#define UserDIO_moniter_len 2
#define UserDIO_moniter_qan 2
const int UserDIO_moniter_adr[UserDIO_moniter_qan] = {762, 764};
enum class UserDIO_moniter_con:int
{	DI = 762,
	DO = 764	};
/* Digital Output */
#define UserDO_setup_len 1
#define UserDO_setup_cmd(bit) (0x0001<<bit)
#define UserDO_setup_adr 766
/* JOG config */
#define JOGConfig_qan 6
const int JOGConfig_len[JOGConfig_qan] = {1, 2, 2, 2, 2, 1};
const int JOGConfig_adr[JOGConfig_qan] = {768, 778, 780, 800, 802, 804};
enum class JOGConfig_con:int
{	motion	= 0,
	acc 	= 1,
	dec 	= 2,
	dis 	= 3,
	ang		= 4,
	speed	= 5	};
enum class JOGConfigMotion_cmd:uint16_t
{	j5_jog_add = 1,
	j5_jog_dec = 2,
	j6_jog_add = 3,
	j6_jog_dec = 4,
	axis1_jog_add = 5,
	axis1_jog_dec = 6,
	axis2_jog_add = 7,
	axis2_jog_dec = 8,
	axis3_jog_add = 9,
	axis3_jog_dec = 10,
	axis4_jog_add = 11,
	axis4_jog_dec = 12,
	j1_jog_add = 25,
	j1_jog_dec = 26,
	j2_jog_add = 27,
	j2_jog_dec = 28,
	j3_jog_add = 29,
	j3_jog_dec = 30,
	j4_jog_add = 31,
	j4_jog_dec = 32,
	CarX_jog_add = 201,
	CarX_jog_dec = 202,
	CarY_jog_add = 203,
	CarY_jog_dec = 204,
	CarZ_jog_add = 205,
	CarZ_jog_dec = 206,
	CarRX_jog_add = 207,
	CarRX_jog_dec = 208,
	CarRY_jog_add = 209,
	CarRY_jog_dec = 210,
	CarRZ_jog_add = 211,
	CarRZ_jog_dec = 212,
	j5_continuous_jog_add = 401,
	j5_continuous_jog_dec = 402,
	j6_continuous_jog_add = 403,
	j6_continuous_jog_dec = 404,
	axis1_continuous_jog_add = 405,
	axis1_continuous_jog_dec = 406,
	axis2_continuous_jog_add = 407,
	axis2_continuous_jog_dec = 408,
	axis3_continuous_jog_add = 409,
	axis3_continuous_jog_dec = 410,
	axis4_continuous_jog_add = 411,
	axis4_continuous_jog_dec = 412,
	j1_continuous_jog_add = 425,
	j1_continuous_jog_dec = 426,
	j2_continuous_jog_add = 427,
	j2_continuous_jog_dec = 428,
	j3_continuous_jog_add = 429,
	j3_continuous_jog_dec = 430,
	j4_continuous_jog_add = 431,
	j4_continuous_jog_dec = 432,
	CarX_continuous_jog_add = 601,
	CarX_continuous_jog_dec = 602,
	CarY_continuous_jog_add = 603,
	CarY_continuous_jog_dec = 604,
	CarZ_continuous_jog_add = 605,
	CarZ_continuous_jog_dec = 606,
	CarRX_continuous_jog_add = 607,
	CarRX_continuous_jog_dec = 608,
	CarRY_continuous_jog_add = 609,
	CarRY_continuous_jog_dec = 610,
	CarRZ_continuous_jog_add = 611,
	CarRZ_continuous_jog_dec = 612,
	j1_gohome = 1401,
	j2_gohome = 1402,
	j3_gohome = 1403,
	j4_gohome = 1404,
	axis1_gohome = 1408,
	axis2_gohome = 1409,
	axis3_gohome = 1410,
	axis4_gohome = 1411,
	j5_gohome = 2001,
	j6_gohome = 2002,
	jALL_gohome = 1405,
	deltaDRV_movP = 301,
	deltaDRV_movL = 302,
	j1_movGOTO = 312,
	j2_movGOTO = 313,
	j3_movGOTO = 314,
	j4_movGOTO = 315,
	j5_movGOTO = 316,
	j6_movGOTO = 317,
	axis1_movGOTO = 318,
	axis2_movGOTO = 319,
	axis3_movGOTO = 320,
	axis4_movGOTO = 321,
	stop = 1000					};
/* goto target information */
#define gotoTarget_qan 15
const int gotoTarget_len[gotoTarget_qan] = {1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   1,   1,   1,   1};
const int gotoTarget_adr[gotoTarget_qan] = {799, 810, 811, 814, 815, 816, 818, 820, 822, 824, 826, 828, 829, 830, 831};
enum class gotoTarget_con:int
{	flag = 0,
	axis12= 1,
	axis34= 2,
	JI1234= 3,
	JI56  = 4,
	X	  = 5,
	Y	  = 6,
	Z	  = 7,
	RX	  = 8,
	RY	  = 9,
	RZ	  = 10,
	UFTF	= 11,
	posture	= 12,
	CoordinateSystem = 13,
	TFgroup	= 14	};
enum class gotoPosture_cmd:uint16_t
{	RNU = 0,
	LNU = 1,
	RND = 2,
	LND = 3,
	RHU = 4,
	LHU = 5,
	RHD = 6,
	LHD = 7	};
enum class gotoCoordinateSystem_cmd:uint16_t
{	WCS = 0,
	PCS = 1	};
/* Robot Language Control */
#define RL_control_len 1
#define RL_control_qan 4
const int RL_control_adr[RL_control_qan] = {531, 532, 544, 552};
enum class RL_control_con:int
{	executive_status= 0,
	executive_line 	= 1,
	script_ID 		= 2,
	script_control 	= 3	};
enum class RL_script_cmd:uint16_t
{	open = 1,
	run = 2,
	stop = 3,
	pause = 4,
	step = 5,
	open_and_run = 6	};
/* delta DRVcontrol User self-service area */
#define DeviceData_len 1
#define DeviceData_qan 4
const int DeviceData_adr[DeviceData_qan] = {4086, 8191, 12288, 16383};
enum class DeviceData_con:int
{	
	/* User self-service */
	Buffer = 0,
	Buffer_end = 1,
	/* User self-service(?) */
	Latch = 2,
	Latch_end = 3
};
/* DMCNET DIO */
#define DMCNET_Equipmen_len 1
#define DMCNET_Equipmen_qan 20
const int DMCNET_Equipmen_adr[DMCNET_Equipmen_qan] =
								   { 0x9820, 0x9828, 0x9830, 0x9838, 0x9840,
									 0x9848, 0x9850, 0x9858, 0x9860, 0x9868,
									 0x9c20, 0x9c28, 0x9c30, 0x9c38, 0x9c40,
									 0x9c48, 0x9c50, 0x9c58, 0x9c60, 0x9c68	};
enum class DMCNET_Equipmen_con:int
{	DMCNET_Equipmen_DI3 = 0,
	DMCNET_Equipmen_DI4  = 1,
	DMCNET_Equipmen_DI5  = 2,
	DMCNET_Equipmen_DI6  = 3,
	DMCNET_Equipmen_DI7  = 4,
	DMCNET_Equipmen_DI8  = 5,
	DMCNET_Equipmen_DI9  = 6,
	DMCNET_Equipmen_DI10 = 7,
	DMCNET_Equipmen_DI11 = 8,
	DMCNET_Equipmen_DI12 = 9,
	DMCNET_Equipmen_DO3  = 10,
	DMCNET_Equipmen_DO4  = 11,
	DMCNET_Equipmen_DO5  = 12,
	DMCNET_Equipmen_DO6  = 13,
	DMCNET_Equipmen_DO7  = 14,
	DMCNET_Equipmen_DO8  = 15,
	DMCNET_Equipmen_DO9  = 16,
	DMCNET_Equipmen_DO10 = 17,
	DMCNET_Equipmen_DO11 = 18,
	DMCNET_Equipmen_DO12 = 19	};
/* --------------------------------------------------------------------- */
/* DRV modbus address Table END */


/* Extern Class End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */
/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */


#endif /*__deltaDRV_modbus_defineTable_HPP__ */

/* ***** END OF deltaDRV_modbus_defineTable.HPP ***** */
