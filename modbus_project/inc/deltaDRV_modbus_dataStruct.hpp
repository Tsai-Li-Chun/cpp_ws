/** ******************************************************
	* @file		deltaDRV_modbus_dataStruct.hpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __deltaDRV_modbus_dataStruct_HPP__
#define __deltaDRV_modbus_dataStruct_HPP__


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include "stdint.h"
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */
/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */
/* Extern Typedef End */


/* Extern Class -------------------------------------------*/
/* Extern Class Begin */
/* Extern Class End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */

/* deltaDRV robot servo status */
struct deltaDRV_servo_status
{
    uint16_t j6j5;
    uint16_t ex_axis21;
    uint16_t ex_axis43;
    uint16_t j4j3;
    uint16_t j2j1;
};
/* deltaDRV robot information joint PUU  */
struct deltaDRV_info_PUU
{
    int32_t ex_axis1;
    int32_t ex_axis2;
    int32_t ex_axis3;
    int32_t ex_axis4;
    int32_t j1;
    int32_t j2;
    int32_t j3;
    int32_t j4;
    int32_t j5;
    int32_t j6;
};
/* deltaDRV robot information joint velocity  */
struct deltaDRV_info_vel
{
    float ex_axis1;
    float ex_axis2;
    float ex_axis3;
    float ex_axis4;
    float j1;
    float j2;
    float j3;
    float j4;
    float j5;
    float j6;
};
/* deltaDRV robot information joint current  */
struct deltaDRV_info_cur
{
    float ex_axis1;
    float ex_axis2;
    float ex_axis3;
    float ex_axis4;
    float j1;
    float j2;
    float j3;
    float j4;
    float j5;
    float j6;
};
/* deltaDRV robot information Cartesian Position  */
struct deltaDRV_info_CartesianPos
{
    float X;
    float Y;
    float Z;
    float RX;
    float RY;
    float RZ;
    float Speed;
};
/* deltaDRV robot information joint Degree Position  */
struct deltaDRV_info_jDegPos
{
    float j1;
    float j2;
    float j3;
    float j4;
    float j5;
    float j6;
};
/* deltaDRV robot information joint Temperature  */
struct deltaDRV_info_temp
{
    float j1;
    float j2;
    float j3;
    float j4;
    float j5;
    float j6;
};
/* deltaDRV robot Frame Posture  */
struct deltaDRV_info_FramePosture
{
    int16_t user_frame;
    int16_t tool_frame;
    int16_t posture;
};
/* deltaDRV Robot System Status  */
struct deltaDRV_status
{
    int16_t motion;
    int16_t system;
    int16_t OPmode;
    int16_t TPmode;
    int16_t DRVready;
};
/* deltaDRV Joint error code  */
struct deltaDRV_ErrorCode
{
    uint16_t ex_axis1;
    uint16_t ex_axis2;
    uint16_t ex_axis3;
    uint16_t ex_axis4;
    uint16_t j1;
    uint16_t j2;
    uint16_t j3;
    uint16_t j4;
    uint16_t j5;
    uint16_t j6;
    uint16_t system;
    uint16_t DRV;
    uint16_t warning;
};
/* deltaDRV JOG config status */
struct deltaDRV_JOGConfig
{
    uint16_t motion;
    uint32_t ACC;
    uint32_t DEC;
    uint32_t move_dis;
    uint32_t move_ang;
    uint16_t speed;
};
/* deltaDRV goto target */
struct deltaDRV_GOTOTarget
{
    uint16_t PositionFlag;
    // uint16_t ex_axis12;
    // uint16_t ex_axis34;
    // uint16_t JointIndex1234;
    // uint16_t JointIndex56;
    deltaDRV_info_CartesianPos CarPos;
    uint16_t UFTF;
    uint16_t posture;
    uint16_t CoordinateSystem;
    uint16_t TFgroup;
};
/* deltaDRV DI & DO data  */
struct deltaDRV_DIO_moniter
{
    uint32_t DI;
    uint32_t DO;
};
/* deltaDRV Joint error code  */
struct deltaDRV_RLStatus
{
    uint16_t executive_status;
    uint16_t executive_line;
    uint16_t script_ID;
    uint16_t script_control;
};

/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */


#endif /*__deltaDRV_modbus_dataStruct_HPP__ */

/* ***** END OF deltaDRV_modbus_dataStruct.HPP ***** */