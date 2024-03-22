/** ******************************************************
	* @file		cas_lab_StandDefineTable.hpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __cas_lab_StandDefineTable_HPP__
#define __cas_lab_StandDefineTable_HPP__


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <stdint.h>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "ADAM5000_DefineTable.hpp"
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */

#define arm_M5_pin_valid 1
#define arm_M5_pin_invalid 0
#define robot_action_valid 1
#define robot_action_invalid 0
#define robot_action_init 255

#define time_blank_short 1000
#define time_blank_long 10000

/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */
/* Extern Typedef End */


/* Extern Class -------------------------------------------*/
/* Extern Class Begin */

/* define deltaDRV robot control-BOX modbus address */
enum class robot_adr:int
{	
	action_cmd = 0x1Eff,
	regulate = 0x1F00,
	item_state= 0x1F01,
	toolATCcheck = 0x1F02,
	rs4 	 = 0x1F03,
	rs3 	 = 0x1F04,
	rs2 	 = 0x1F05,
	rs1  	 = 0x1F06,
	kinetrol = 0x1F11,
	brake 	 = 0x1F12,
	gripper  = 0x1F13,
	toolATC	 = 0x1F21,
	fixture  = 0x1F22
};
/* define cas_lab stand system remoteIO-input modbus address */
enum class stand_adr_in:int
{	
	noitem 	 = static_cast<int>(adam5000_DI::DI_2_00),
	lowitem  = static_cast<int>(adam5000_DI::DI_2_01),
	highitem = static_cast<int>(adam5000_DI::DI_2_02),
	ATCcheck = static_cast<int>(adam5000_DI::DI_2_04),
	rs4 	 = static_cast<int>(adam5000_DI::DI_2_05),
	rs3 	 = static_cast<int>(adam5000_DI::DI_2_06),
	rs2 	 = static_cast<int>(adam5000_DI::DI_2_07),
	rs1  	 = static_cast<int>(adam5000_DI::DI_2_08)
};
/* define cas_lab stand system remoteIO-input modbus address */
enum class stand_adr_out:int
{
	regulate 	  = static_cast<int>(adam5000_AO::AO_1_0),
	kinetrol_up   = static_cast<int>(adam5000_DO::DO_3_00),
	kinetrol_down = static_cast<int>(adam5000_DO::DO_3_01),
	brake 		  = static_cast<int>(adam5000_DO::DO_3_02),
	gripper_open  = static_cast<int>(adam5000_DO::DO_3_03),
	gripper_close = static_cast<int>(adam5000_DO::DO_3_04),
	security	  = static_cast<int>(adam5000_DO::DO_3_05),
	value1_lock   = static_cast<int>(adam5000_DO::DO_4_00),
	value1_unlock = static_cast<int>(adam5000_DO::DO_4_01),
	value2_lock   = static_cast<int>(adam5000_DO::DO_4_02),
	value2_unlock = static_cast<int>(adam5000_DO::DO_4_03),
	value3_lock   = static_cast<int>(adam5000_DO::DO_4_04),
	value3_unlock = static_cast<int>(adam5000_DO::DO_4_05),
	value4_lock   = static_cast<int>(adam5000_DO::DO_4_06),
	value4_unlock = static_cast<int>(adam5000_DO::DO_4_07),
};

/* define cas_lab stand system 3ARMs M5 brake state */
enum class armM5_brake:uint16_t
{
	lock = 1,
	release = 2
};
/* define cas_lab stand system 3ARMs M5 brake state */
enum class armM5_kinetrol:uint16_t
{
	up = 1,
	down = 2
};
/* define cas_lab stand system 3ARMs M5 payload state */
enum class armM5_item_state:uint16_t
{
	invalid_item = 0,
	no_item   = 1,
	low_item  = 2,
	high_item = 3
};
/* define cas_lab stand system 3ARMs M5 to tools ATC connect check */
enum class armM5_toolATC_check:uint16_t
{
	not_connect = 0,
	connect = 1
};
/* define cas_lab stand system 3ARMs M5 to tools ATC working state */
enum class armM5_toolATC_state:uint16_t
{
	lock = 1,
	release = 2
};
/* define cas_lab stand system 3ARMs M5 reed switch state */
enum class armM5_fixture_state:uint16_t
{
	open = 1,
	close = 2
};
/* define cas_lab stand system 3ARMs M5 reed switch state */
enum class armM5_ReedSwitch_state:uint16_t
{
	not_place = 0,
	in_place = 1
};

/* Extern Class End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */

struct stand_state
{
	armM5_item_state arm_M5_item;
	uint8_t no_gravity_3ARMs;		/* reference arm_M5_item_state */
};

/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */


#endif /*__cas_lab_StandDefineTable_HPP__ */

/* ***** END OF cas_lab_StandDefineTable.HPP ***** */
