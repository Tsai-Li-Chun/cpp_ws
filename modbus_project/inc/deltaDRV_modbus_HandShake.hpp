/** ******************************************************
	* @file		deltaDRV_modbus_HandShake.hpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __deltaDRV_modbus_HandShake_HPP__
#define __deltaDRV_modbus_HandShake_HPP__


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <stdint.h>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "deltaDRV_modbus_defineTable.hpp"
#include "modbus/modbus.h"
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */
/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */

/* conversion u16 to float structure */
union modbus_u16tofloat
{
    float f;
    uint16_t u16[ (sizeof(float))/sizeof(uint16_t) ];
};

/* conversion u18 to u16 structure */
union modbus_u8tou16
{
    uint16_t u16;
    uint8_t u8[ (sizeof(uint16_t))/sizeof(uint8_t) ];
};

/* Extern Typedef End */


/* Extern Class -------------------------------------------*/
/* Extern Class Begin */

class deltaDRV_modbus_HandShake
{
/* private members */
private:
	/* create modbus_communication_structure */
	modbus_t* mb;
	/* libmodbus return value(ReturnCode) */
	int rc;

	/* 設定連結函數 */
	int Modbus_slave_connect(int slave);

/* public members */
public:
	/* constructor */
	deltaDRV_modbus_HandShake(const char* IP,const int port,const int slave);
	/* destructor */
	~deltaDRV_modbus_HandShake();

	/* read robot information PUU */
	int robot_info_PUU(robot_info_PUU_adr adr, modbus_u16tofloat *puu);
	int robot_info_PUU_ALL(modbus_u16tofloat *puu);
	/* read robot information veloctiy */
	int robot_info_vel(robot_info_vel_adr adr, modbus_u16tofloat *vel);
	int robot_info_vel_ALL(modbus_u16tofloat *vel);
	/* read robot information current */
	int robot_info_cur(robot_info_cur_adr adr, modbus_u16tofloat *cur);
	int robot_info_cur_ALL(modbus_u16tofloat *cur);
	/* read robot information Cartesian Position */
	int robot_info_CartesianPos(robot_info_CartesianPos_adr adr, modbus_u16tofloat *cp);
	int robot_info_CartesianPos_ALL(modbus_u16tofloat *cp);
	/* read robot information joint Degree Position */
	int robot_info_jDegPos(robot_info_jDegPos_adr adr, modbus_u16tofloat *jdp);
	int robot_info_jDegPos_ALL(modbus_u16tofloat *jdp);
	/* read robot information Temperature */
	int robot_info_temp(robot_info_temp_adr adr, modbus_u16tofloat *temp);
	int robot_info_temp_ALL(modbus_u16tofloat *temp);
	/* read robot information Frame Posture */
	int robot_info_FramePosture(robot_info_FramePosture_adr adr, modbus_u16tofloat *fp);
	/* read robot information Joint index */
	int robot_info_JRC(robot_info_JRC_adr adr, modbus_u16tofloat *jrc);
	/* read Robot System Status */
	int robot_status(robot_status_adr adr, modbus_u16tofloat *status);
	/* read Joint error code */
	int error_code(error_code_adr adr, modbus_u16tofloat *code);
	/* read DI & DO data */
	int user_DIO_moniter(user_DIO_moniter_adr adr, modbus_u16tofloat *data);
	/* read target position status */
	int goto_target_flag(JOG_config_adr adr, modbus_u16tofloat *flg);
	/* read Robot Language status */
	int RL_control_status(RL_control_adr adr, modbus_u16tofloat *status);

	/* setup delta robot servo on/off */
	int servo_onoff(servo_onoff_adr adr, servo_onoff_cmd cmd, modbus_u16tofloat *servo);
	/* delta robot alarm reset */
	int servo_alarm_reset(servo_alarm_reset_adr adr, servo_alarm_reset_cmd cmd);	
	/* setup JOG config */
	int JOG_config_motion(JOG_config_adr adr, JOG_config_motion_cmd motion);
	int JOG_config_acc(JOG_config_adr adr, uint32_t acc);
	int JOG_config_dec(JOG_config_adr adr, uint32_t *dec);
	int JOG_config_dis(JOG_config_adr adr, uint32_t *dis);
	int JOG_config_ang(JOG_config_adr adr, uint32_t *ang);
	int JOG_config_speed(JOG_config_adr adr, uint16_t *speed);
	/* setup target cartesian coordinate position */
	int goto_target_X(goto_target_adr adr, modbus_u16tofloat x);
	int goto_target_Y(goto_target_adr adr, modbus_u16tofloat y);
	int goto_target_Z(goto_target_adr adr, modbus_u16tofloat z);
	int goto_target_RX(goto_target_adr adr, modbus_u16tofloat rx);
	int goto_target_RY(goto_target_adr adr, modbus_u16tofloat ry);
	int goto_target_RZ(goto_target_adr adr, modbus_u16tofloat rz);
	/* setup target config */
	int goto_target_UFTF(goto_target_adr adr, uint16_t uftf);
	int goto_target_posture(goto_target_adr adr, goto_posture_cmd pos);
	int goto_target_CoordinateSystem(goto_target_adr adr, goto_CoordinateSystem_cmd cs);
	/* setup Robot Language Control */
	int RL_control(RL_control_adr adr, RL_script_cmd cmd);
	int RL_control_line(RL_control_adr adr, uint16_t line);
	/* setup DO status */
	int user_DO_setup(user_DO_setup_adr adr, uint16_t *status);

};


/* Extern Class End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */
/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */


#endif /*__deltaDRV_modbus_HandShake_HPP__ */

/* ***** END OF deltaDRV_modbus_HandShake.HPP ***** */
