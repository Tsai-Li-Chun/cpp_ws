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
#include "deltaDRV_modbus_AdrCmdTable.hpp"
#include "deltaDRV_modbus_dataStruct.hpp"
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
/* conversion u16 to u32 structure */
union modbus_u16tou32
{
    uint32_t u32;
    uint16_t u16[ (sizeof(uint32_t))/sizeof(uint16_t) ];
};
/* conversion u16 to u32 structure */
union modbus_u16toi32
{
    int32_t i32;
    uint16_t u16[ (sizeof(int32_t))/sizeof(uint16_t) ];
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
	/* data buffer */
	modbus_u16tofloat tmp_u16float;
	modbus_u16tou32	  tmp_u16u32;
	modbus_u16toi32	  tmp_u16i32;

	/* 設定連結函數 */
	int Modbus_slave_connect(int slave);

	/* read delta robot servo on/off */
	int read_deltaDRV_Servo(servo_onoff_adr adr, deltaDRV_servo_status *servo);
	/* read delta robot JOG config */
	int read_deltaDRV_JOGConfig(JOG_config_adr adr, deltaDRV_JOGConfig *jog);
	/* setup JOG one config */
	int setup_JOGConfigMotion(JOG_config_adr adr, JOG_config_motion_cmd motion);
	int setup_JOGConfigAcc(JOG_config_adr adr, uint32_t acc);
	int setup_JOGConfigDec(JOG_config_adr adr, uint32_t *dec);
	int setup_JOGConfigDis(JOG_config_adr adr, uint32_t *dis);
	int setup_JOGConfigAng(JOG_config_adr adr, uint32_t *ang);
	int setup_JOGConfigSpeed(JOG_config_adr adr, uint16_t *speed);
	/* read delta robot goto target */
	int read_deltaDRV_gotoTarget(goto_target_adr adr, deltaDRV_GOTOTarget *gotoT);
	/* setup target one cartesian coordinate position */
	int setup_gotoTargetX(goto_target_adr adr, float x);
	int setup_gotoTargetY(goto_target_adr adr, float y);
	int setup_gotoTargetZ(goto_target_adr adr, float z);
	int setup_gotoTargetRX(goto_target_adr adr, float rx);
	int setup_gotoTargetRY(goto_target_adr adr, float ry);
	int setup_gotoTargetRZ(goto_target_adr adr, float rz);
	/* setup target one config */
	int setup_gotoTargetUFTF(goto_target_adr adr, uint16_t uftf);
	int setup_gotoTargetPosture(goto_target_adr adr, goto_posture_cmd pos);
	int setup_gotoTargetCoordinateSystem(goto_target_adr adr, goto_CoordinateSystem_cmd cs);

/* public members */
public:
	/* constructor */
	deltaDRV_modbus_HandShake(const char* IP,const int port,const int slave);
	/* destructor */
	~deltaDRV_modbus_HandShake();

	/* read robot information PUU */
	int read_deltaDRV_info_PUU(deltaDRV_info_PUU *puu);
	/* read robot information veloctiy */
	int read_deltaDRV_info_vel(deltaDRV_info_vel_adr adr, deltaDRV_info_vel *vel);
	/* read robot information current */
	int read_deltaDRV_info_cur(deltaDRV_info_cur_adr adr, deltaDRV_info_cur *cur);
	/* read robot information Cartesian Position */
	int read_deltaDRV_info_CartesianPos(deltaDRV_info_CartesianPos_adr adr, deltaDRV_info_CartesianPos *cp);
	/* read robot information joint Degree Position */
	int read_deltaDRV_info_jDegPos(deltaDRV_info_jDegPos_adr adr, deltaDRV_info_jDegPos *jdp);
	/* read robot information Temperature */
	int read_deltaDRV_info_temp(deltaDRV_info_temp_adr adr, deltaDRV_info_temp *temp);
	/* read robot information Frame Posture */
	int read_deltaDRV_info_FramePosture(deltaDRV_info_FramePosture_adr adr, deltaDRV_info_FramePosture *fp);
	// /* read robot information Joint index */
	// int read_deltaDRV_info_JRC(deltaDRV_info_JRC_adr adr, uint16_t *jrc);
	/* read Robot System Status */
	int read_deltaDRV_status(deltaDRV_status_adr adr, deltaDRV_status *status);
	/* read Joint error code */
	int read_deltaDRV_ErrorCode(error_code_adr adr, deltaDRV_ErrorCode *code);
	/* read DI & DO data */
	int read_deltaDRV_userDIO(user_DIO_moniter_adr adr, deltaDRV_DIO_moniter *data);
	/* read target position status */
	int read_deltaDRV_gotoTargetFlag(goto_target_adr adr, uint16_t *flg);
	/* read Robot Language status */
	int read_deltaDRV_RLStatus(RL_control_adr adr, deltaDRV_RLStatus *status);

	/* setup delta robot servo on/off */
	int setup_Servo(servo_onoff_adr adr, deltaDRV_servo_status servo);
	/* delta robot alarm reset */
	int setup_AlarmReset(servo_alarm_reset_adr adr, servo_alarm_reset_cmd cmd);	
	/* setup JOG config */
	int setup_JOGConfig(JOG_config_adr adr, deltaDRV_JOGConfig jog);
	/* setup goto target */
	int setup_gotoTarget(goto_target_adr adr, deltaDRV_GOTOTarget gotoT);
	/* setup Robot Language Control */
	int setup_RLControl(RL_control_adr adr, deltaDRV_RLStatus rl);
	/* setup DO status */
	int setup_userDO(user_DO_setup_adr adr, uint16_t *status);
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
