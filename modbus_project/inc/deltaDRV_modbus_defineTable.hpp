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

/* DRV modbus address Table */
/* --------------------------------------------------------------------- */
#define servo_onoff_len 1
enum class servo_onoff_adr:int
{	/* Servo oN/OFF modbus address */
	j5j6 	= 0,
	axis12	= 1,
	axis34 	= 2,
	j1j2 	= 6,
	j3j4 	= 7,
};
enum class servo_onoff_cmd:uint16_t
{	/* Servo oN/OFF command */
	H_ON 	= 0x0100,
	L_ON 	= 0x0001,
	HL_ON	= 0x0101,
	HL_OFF	= 0x0000
};
#define servo_alarm_reset_len 1
enum class servo_alarm_reset_adr:int
{	/* Servo Alarm Reset */
	j5j6 	= 32,
	axis12	= 33,
	axis34	= 34,
	j1j2 	= 38,
	j3j4 	= 39,
	ALL 	= 384
};
enum class servo_alarm_reset_cmd:uint16_t
{	/* Servo oN/OFF command */
	H_reset	= 0x0100,
	L_reset	= 0x0001,
	HL_reset= 0x0101
};
#define robot_info_PUU_len 2
enum class robot_info_PUU_adr:int
{	/* Robot Information "Joint Position" PUU */
	j5 = 128,
	j6 = 130,
	a1 = 132,
	a2 = 134,
	a3 = 136,
	a4 = 138,
	j1 = 152,
	j2 = 154,
	j3 = 156,
	j4 = 158
};
#define robot_info_veloctiy_len 2
#define robot_info_veloctiy_Resolution (float)0.1 /* rpm */
enum class robot_info_vel_adr:int
{	/* Robot Information "Joint Velocity" 0.1rpm */
	j5 = 160,
	j6 = 162,
	a1 = 164,
	a2 = 166,
	a3 = 168,
	a4 = 170,
	j1 = 184,
	j2 = 186,
	j3 = 188,
	j4 = 190
};
#define robot_info_current_len 2
#define robot_info_current_Resolution (float)0.01 /* % percent */
enum class robot_info_cur_adr:int
{	/* Robot Information "Joint Current" 0.01% */
	j5 = 192,
	j6 = 194,
	a1 = 196,
	a2 = 198,
	a3 = 200,
	a4 = 202,
	j1 = 216,
	j2 = 218,
	j3 = 220,
	j4 = 222
};
#define robot_info_Cartesian_len 2
#define robot_info_Cartesian_Resolution (float)1 /* to be confirmed */
enum class robot_info_CartesianPos_adr:int
{	/* Robot Information "Cartesion Posture" */
	X = 240,
	Y = 242,
	Z = 244,
	RX = 246,
	RY = 248,
	RZ = 250,
	Speed = 254
};
#define robot_info_jDegPos_len 2
#define robot_info_jDegPos_Resolution (float)0.001 /* Degree(?) */
enum class robot_info_jDegPos_adr:int
{	/* Servo Motor Information "Degree Position" */
	j1 = 360,
	j2 = 362,
	j3 = 364,
	j4 = 366,
	j5 = 336,
	j6 = 338
};
#define robot_info_temp_len 1
enum class robot_info_temp_adr:int
{	/* Robot Information Temperature */
	j1 = 272,
	j2 = 273,
	j3 = 274,
	j4 = 275,
	j5 = 276,
	j6 = 277
};
#define robot_info_FramePosture_len 1
enum class robot_info_FramePosture_adr:int
{	/* Robot Information "Robot Frame" */
	/* Robot Information "Cartesion Posture" */
	userframe = 226,
	toolframe = 227,
	Posture = 228
};
#define robot_info_JRC_len 1
enum class robot_info_JRC_adr:int
{	/* Robot Information "Joint index" */
	j1234 = 268,
	j56	  = 269
};
#define robot_status_len 1
enum class robot_status_adr:int
{	/* Robot System Status */
	motion 	 = 224,
	system 	 = 312,
	OPmode 	 = 313,
	TPmode 	 = 315,
	DRVready = 514
};
#define error_code_len 1
enum class error_code_adr:int
{	/* error code */
	j5 		= 320,
	j6 		= 321,
	a1 		= 322,
	a2 		= 323,
	a3 		= 324,
	a4 		= 325,
	j1 		= 332,
	j2 		= 333,
	j3 		= 334,
	j4 		= 335,
	system 	= 480,
	DRV		= 511,
	warning = 526
};
#define user_DIO_moniter_len 2
enum class user_DIO_moniter_adr:int
{	/* Digital Input & Output */
	DI = 762,
	DO = 764
};
#define user_DO_setup_len 1
#define user_DO_setup_cmd(do) (0x0001<<do)
enum class user_DO_setup_adr:int
{	/* Digital Output */
	DI = 766
};
#define JOG_config_motion_len 1
#define JOG_config_acc_len 2
#define JOG_config_dec_len 2
#define JOG_config_dis_len 2
#define JOG_config_ang_len 2
#define JOG_config_speed_len 1
enum class JOG_config_adr:int
{	/* JOG config */
	motion 		= 768,
	JOG_acc 	= 778,
	JOG_dec 	= 780,
	JOG_dis 	= 800,
	JOG_ang		= 802,
	JOG_speed	= 804
};
enum class JOG_config_motion_cmd:uint16_t
{	/* JOG motion */
	j5_jog_add = 1,
	j5_jog_dec = 2,
	j6_jog_add = 3,
	j6_jog_dec = 4,
	a1_jog_add = 5,
	a1_jog_dec = 6,
	a2_jog_add = 7,
	a2_jog_dec = 8,
	a3_jog_add = 9,
	a3_jog_dec = 10,
	a4_jog_add = 11,
	a4_jog_dec = 12,
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
	a1_continuous_jog_add = 405,
	a1_continuous_jog_dec = 406,
	a2_continuous_jog_add = 407,
	a2_continuous_jog_dec = 408,
	a3_continuous_jog_add = 409,
	a3_continuous_jog_dec = 410,
	a4_continuous_jog_add = 411,
	a4_continuous_jog_dec = 412,
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
	a1_gohome = 1408,
	a2_gohome = 1409,
	a3_gohome = 1410,
	a4_gohome = 1411,
	j5_gohome = 2001,
	j6_gohome = 2002,
	jALL_gohome = 1405,
	robot_movP = 301,
	robot_movL = 302,
	j1_movGOTO = 312,
	j2_movGOTO = 313,
	j3_movGOTO = 314,
	j4_movGOTO = 315,
	j5_movGOTO = 316,
	j6_movGOTO = 317,
	a1_movGOTO = 318,
	a2_movGOTO = 319,
	a3_movGOTO = 320,
	a4_movGOTO = 321,
	stop = 1000
};
#define goto_target_len 1
enum class goto_target_adr:int
{	/* goto target information */
	flag  = 799,
	a12	  = 810,
	a34	  = 811,
	j1234 = 814,
	j56	  = 815,
	X	  = 816,
	Y	  = 818,
	Z	  = 820,
	RX	  = 822,
	RY	  = 824,
	RZ	  = 826,
	UFTF	= 828,
	posture	= 829,
	CoordinateSystem = 830,
	TFgroup	= 831
};
enum class goto_posture_cmd:uint16_t
{
	RNU = 0,
	LNU = 1,
	RND = 2,
	LND = 3,
	RHU = 4,
	LHU = 5,
	RHD = 6,
	LHD = 7
};
enum class goto_CoordinateSystem_cmd:uint16_t
{
	WCS = 0,
	PCS = 1
};
#define RL_control_len 1
enum class RL_control_adr:int
{	/* Robot Language Control */
	executive_status= 531,
	executive_line 	= 532,
	script_ID 		= 544,
	script_control 	= 552
};
enum class RL_script_cmd:uint16_t
{	/* Robot Language Control */
	open = 1,
	run = 2,
	stop = 3,
	pause = 4,
	step = 5,
	open_and_run = 6
};
#define device_data_len 1
enum class device_data_adr:int
{	
	/* User self-service */
	Buffer = 4096,
	/* User self-service(?) */
	Latch = 12288
};
#define DMCNET_Equipmen_len 1
enum class DMCNET_Equipmen_adr:int
{	/* DMCNET DIO */
	DMCNET_Equipmen_DI3  = 0x9820,
	DMCNET_Equipmen_DI4  = 0x9828,
	DMCNET_Equipmen_DI5  = 0x9830,
	DMCNET_Equipmen_DI6  = 0x9838,
	DMCNET_Equipmen_DI7  = 0x9840,
	DMCNET_Equipmen_DI8  = 0x9848,
	DMCNET_Equipmen_DI9  = 0x9850,
	DMCNET_Equipmen_DI10 = 0x9858,
	DMCNET_Equipmen_DI11 = 0x9860,
	DMCNET_Equipmen_DI12 = 0x9868,
	DMCNET_Equipmen_DO3  = 0x9c20,
	DMCNET_Equipmen_DO4  = 0x9c28,
	DMCNET_Equipmen_DO5  = 0x9c30,
	DMCNET_Equipmen_DO6  = 0x9c38,
	DMCNET_Equipmen_DO7  = 0x9c40,
	DMCNET_Equipmen_DO8  = 0x9c48,
	DMCNET_Equipmen_DO9  = 0x9c50,
	DMCNET_Equipmen_DO10 = 0x9c58,
	DMCNET_Equipmen_DO11 = 0x9c60,
	DMCNET_Equipmen_DO12 = 0x9c68
};
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
