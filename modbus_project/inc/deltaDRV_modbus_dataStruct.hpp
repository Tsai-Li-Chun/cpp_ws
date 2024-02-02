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
struct ServoOnOff
{
    uint16_t _j6j5;
    uint16_t ex_axis21;
    uint16_t ex_axis43;
    uint16_t j4j3;
    uint16_t j2j1_;
};
/* deltaDRV robot information joint PUU  */
struct InfoPUU
{
    int32_t _j5;
    int32_t j6;
    int32_t ex_axis1;
    int32_t ex_axis2;
    int32_t ex_axis3;
    int32_t ex_axis4;
    int32_t j1;
    int32_t j2;
    int32_t j3;
    int32_t j4_;
};
/* deltaDRV robot information joint velocity  */
struct InfoVel
{
    float _j5;
    float j6;
    float ex_axis1;
    float ex_axis2;
    float ex_axis3;
    float ex_axis4;
    float j1;
    float j2;
    float j3;
    float j4_;
};
/* deltaDRV robot information joint current  */
struct InfoCur
{
    float _j5;
    float j6;
    float ex_axis1;
    float ex_axis2;
    float ex_axis3;
    float ex_axis4;
    float j1;
    float j2;
    float j3;
    float j4_;
};
/* deltaDRV robot information Cartesian Position  */
struct InfoCartesianPos
{
    float _X;
    float Y;
    float Z;
    float RX;
    float RY;
    float RZ;
    float Speed_;
};
/* deltaDRV robot information joint Degree Position  */
struct InfojDegPos
{
    float _j1;
    float j2;
    float j3;
    float j4;
    float j5;
    float j6_;
};
/* deltaDRV robot information joint Temperature  */
struct InfoTemp
{
    float _j1;
    float j2;
    float j3;
    float j4;
    float j5;
    float j6_;
};
/* deltaDRV robot Frame Posture  */
struct InfoFramePosture
{
    int16_t _userFrame;
    int16_t toolFrame;
    int16_t posture_;
};
/* deltaDRV Robot System Status  */
struct RobotStatus
{
    int16_t _motion;
    int16_t system;
    int16_t OPmode;
    int16_t TPmode;
    int16_t DRVready_;
};
/* deltaDRV Joint error code  */
struct ErrorCode
{
    uint16_t _j5;
    uint16_t j6;
    uint16_t ex_axis1;
    uint16_t ex_axis2;
    uint16_t ex_axis3;
    uint16_t ex_axis4;
    uint16_t j1;
    uint16_t j2;
    uint16_t j3;
    uint16_t j4;
    uint16_t system;
    uint16_t DRV;
    uint16_t warning_;
};
/* deltaDRV JOG config status */
struct JOGConfig
{
    uint16_t motion;
    uint32_t ACC;
    uint32_t DEC;
    uint32_t move_dis;
    uint32_t move_ang;
    uint16_t speed;
};
/* deltaDRV goto target */
struct gotoTarget
{
    uint16_t PositionFlag;
    // uint16_t ex_axis12;
    // uint16_t ex_axis34;
    // uint16_t JointIndex1234;
    // uint16_t JointIndex56;
    InfoCartesianPos CarPos;
    uint16_t UFTF;
    uint16_t posture;
    uint16_t CoordinateSystem;
    uint16_t TFgroup;
};
/* deltaDRV DI & DO data  */
struct UserDIO_moniter
{
    uint32_t DI;
    uint32_t DO;
};
/* deltaDRV Robot Language Control */
struct RL_control
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
