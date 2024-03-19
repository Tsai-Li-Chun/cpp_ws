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
	float*				ftmp_ptr;
	uint16_t*			u16tmp_ptr;
	int16_t*			i16tmp_ptr;
	uint32_t*			u32tmp_ptr;
	int32_t*			i32tmp_ptr;
	modbus_u16tofloat 	tmp_u16float;
	modbus_u16tou32	  	tmp_u16u32;
	modbus_u16toi32	  	tmp_u16i32;
	/* delta DRVcontrol robot informatiom */
	ServoOnOff 		 _deltaDRV_servo_status;
	InfoPUU 		 _deltaDRV_info_PUU;
	InfoVel 		 _deltaDRV_info_vel;
	InfoCur			 _deltaDRV_info_cur;
	InfoCartesianPos _deltaDRV_info_CartesianPos;
	InfojDegPos		 _deltaDRV_info_jDegPos;
	InfoTemp		 _deltaDRV_info_temp;
	InfoFramePosture _deltaDRV_info_FramePosture;
	RobotStatus 	 _deltaDRV_status;
	ErrorCode 		 _deltaDRV_ErrorCode;
	JOGConfig 		 _deltaDRV_JOGConfig;
	gotoTarget 		 _deltaDRV_GOTOTarget;
	UserDIO_moniter  _deltaDRV_DIO_moniter;
	RL_control 		 _deltaDRV_RLStatus;

	/* 設定連結函數 */
	int Modbus_slave_connect(int slave);

/* public members */
public:
	/* constructor */
	deltaDRV_modbus_HandShake(const char* IP,const int port,const int slave);
	/* destructor */
	~deltaDRV_modbus_HandShake();

	/* read delta robot servo on/off */
	int read_deltaDRV_Servo(ServoOnOff *servo);
	/* read robot information PUU */
	int read_deltaDRV_info_PUU(InfoPUU *puu);
	/* read robot information veloctiy */
	int read_deltaDRV_info_vel(InfoVel *vel);
	/* read robot information current */
	int read_deltaDRV_info_cur(InfoCur *cur);
	/* read robot information Cartesian Position */
	int read_deltaDRV_info_CartesianPos(InfoCartesianPos *cp);
	/* read robot information joint Degree Position */
	int read_deltaDRV_info_jDegPos(InfojDegPos *jdp);
	/* read robot information Temperature */
	int read_deltaDRV_info_temp(InfoTemp *temp);
	/* read robot information Frame Posture */
	int read_deltaDRV_info_FramePosture(InfoFramePosture *fp);
	// /* read robot information Joint index */
	// int read_deltaDRV_info_JRC(uint16_t *jrc);
	/* read Robot System Status */
	int read_deltaDRV_status(RobotStatus *rs);
	/* read Joint error code */
	int read_deltaDRV_ErrorCode(ErrorCode *code);
	/* read DI & DO data */
	int read_deltaDRV_userDIO(UserDIO_moniter *data);
	/* read delta robot JOG config */
	int read_deltaDRV_JOGConfig(JOGConfig *jog);
	/* read delta robot goto target */
	int read_deltaDRV_gotoTarget(gotoTarget *gotoT);
	/* read Robot Language status */
	int read_deltaDRV_RLStatus(RL_control *status);

	/* setup delta robot servo on/off */
	int setup_Servo(ServoOnOff servo);
	/* delta robot alarm reset */
	int setup_AlarmReset(ServoAlarmReset_cmd cmd);	
	/* setup JOG config */
	int setup_JOGConfig(JOGConfig jog);
	/* setup goto target */
	int setup_gotoTarget(gotoTarget gotoT);
	/* setup Robot Language Control */
	int setup_RLControl(RL_control rl);
	/* setup DO status */
	int setup_userDO(uint16_t *status);

	/* read Robot Device Data Buffer */
	int read_deltaDRV_DataBuffer(int adr, int nb, uint16_t *data);
	/* write Robot Device Data Buffer */
	int write_deltaDRV_DataBuffer(int adr, uint16_t data);
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
