/** ******************************************************
	* @file		deltaDRV_modbus_HandShake.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <iostream>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "deltaDRV_modbus_HandShake.hpp"
/* User Includes End */

/* namespace ------------------------------------------------*/
/* namespace Begin */
/* namespace End */


/* Define ---------------------------------------------------*/
/* Define Begin */
/* Define End */


/* Typedef --------------------------------------------------*/
/* Typedef Begin */
/* Typedef End */


/* Class --------------------------------------------------*/
/* Class Begin */
/* Class End */


/* Variables ------------------------------------------------*/
/* Variables Begin */
/* Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */



/* ---------------------------------------------------------*/
/* ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩ Program ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩ ---------------------------*/
/* ---------------------------------------------------------*/
/* Program Begin */

/** * @brief Constructor - TCP Mode
 	* @param IP(char*) Modbus Device IP Address
 	* @param port(int) communication port, default 502
 	* @param slave(int) Modbus Device ID, default 1
 	* @return None
**	**/
deltaDRV_modbus_HandShake::deltaDRV_modbus_HandShake(const char* IP,const int port,const int slave)
{
	/* 初始化modbus通訊設定 */
	mb = modbus_new_tcp(IP,port);
	if( Modbus_slave_connect(slave) != 0 )
		printf("Modbus TCP Mode Setup Failure!\n");
}

/** * @brief destructor
 	* @param None
 	* @return None
**	**/
deltaDRV_modbus_HandShake::~deltaDRV_modbus_HandShake()
{
	/* close connect */
	modbus_close(mb);
	/* release the address of the modbus_communication_structure */
	modbus_free(mb);
	/* 打印關閉訊息 */
	printf("modbus connect close\n");
}

/** * @brief Setup SlaveID & Connect
 	* @param slave(int) Modbus Device ID, default 1
 	* @return int 
**	**/
int deltaDRV_modbus_HandShake::Modbus_slave_connect(int slave)
{
	/* 宣告libmodbus-API的ReturnCode變數 */
	int rc;
	/* 初始化是否成功判斷 */
	if( mb == NULL )
	{	/* 若初始化失敗,打印訊息,退出程序 */
		printf("%s\n",modbus_strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
	{	/* 若初始化成功,打印訊息 */
		printf("Initialize modbus_t Structure Success\n");
	}

	/* 設定欲通訊的modbus-slaveID */
	rc = modbus_set_slave(mb,slave);
	if( rc != 0 )
	{	/* 若設定失敗,打印訊息,退出建構函數 */
		printf("modbus set slave Failure!\n");
		return rc;
	}
	else
	{	/* 若slaveID設定成功,打印訊息 */
		printf("Setup Slave ID \"%d\" Success\n", slave);
	}

	/* 建立連結 */
	rc = modbus_connect(mb);
	if( rc != 0 )
	{	/* 若設定失敗,打印訊息,退出建構函數 */
		printf("modbus connect Failure!\n");
		printf("%s\n",modbus_strerror(errno));
		return rc;
	}
	else
	{	/* 若連結成功,打印訊息 */
		printf("Slave ID \"%d\" Connect Success\n", slave);
	}

	/* 程式正常結束,返回0 */
	return 0;
}

/** * @brief read delta robot servo on/off
 	* @param ServoOnOff*(servo), ServoOnOff pointer for storing the result.
 	* @return int, result execution
**	**/
int deltaDRV_modbus_HandShake::read_deltaDRV_Servo(ServoOnOff *servo)
{
	u16tmp_ptr = &_deltaDRV_servo_status._j6j5;
	for( int i=0; i<ServoOnOff_qan; i++ )
	{
		rc = modbus_read_registers(mb, ServoOnOff_adr[i], ServoOnOff_len, u16tmp_ptr);
		if(rc==(-1)) return (-1);
		u16tmp_ptr++;
	}
	return rc;
}

/** * @brief read robot information PUU
 	* @param InfoPUU*(puu), InfoPUU pointer for storing the result.
 	* @return int, result execution
**	**/
int deltaDRV_modbus_HandShake::read_deltaDRV_info_PUU(InfoPUU *puu)
{
	i32tmp_ptr = &_deltaDRV_info_PUU._j5;
	for( int i=0; i<InfoPUU_qan; i++ )
	{
		rc = modbus_read_registers(mb, InfoPUU_adr[i], InfoPUU_len, tmp_u16i32.u16);
		if(rc==(-1)) return (-1);
		*i32tmp_ptr = tmp_u16i32.i32;
		i32tmp_ptr++;
	}
	*puu = _deltaDRV_info_PUU;
	return rc;
}

/** * @brief read robot information veloctiy
 	* @param InfoVel*(vel), InfoVel pointer for storing the result.
 	* @return int, result execution
**	**/
int deltaDRV_modbus_HandShake::read_deltaDRV_info_vel(InfoVel *vel)
{
	ftmp_ptr = &_deltaDRV_info_vel._j5;
	for( int i=0; i<InfoVel_qan; i++ )
	{
		rc = modbus_read_registers(mb, InfoVel_adr[i], InfoVel_len, tmp_u16float.u16);
		if(rc==(-1)) return (-1);
		*ftmp_ptr = tmp_u16float.f*InfoVel_Resolution;
		ftmp_ptr++;
	}
	*vel = _deltaDRV_info_vel;
	return rc;
}

/** * @brief read robot information current
 	* @param InfoCur*(cur), InfoCur pointer for storing the result.
 	* @return int, result execution
**	**/
int deltaDRV_modbus_HandShake::read_deltaDRV_info_cur(InfoCur *cur)
{
	ftmp_ptr = &_deltaDRV_info_cur._j5;
	for( int i=0; i<InfoCur_qan; i++ )
	{
		rc = modbus_read_registers(mb, InfoCur_adr[i], InfoCur_len, tmp_u16float.u16);
		if(rc==(-1)) return (-1);
		*ftmp_ptr = tmp_u16float.f*InfoCur_Resolution;
		ftmp_ptr++;
	}
	*cur = _deltaDRV_info_cur;
	return rc;
}

/** * @brief read robot information Cartesian Position
 	* @param InfoCartesianPos*(cur), InfoCartesianPos pointer for storing the result.
 	* @return int, result execution
**	**/
int deltaDRV_modbus_HandShake::read_deltaDRV_info_CartesianPos(InfoCartesianPos *cp)
{
	ftmp_ptr = &_deltaDRV_info_CartesianPos._X;
	for( int i=0; i<InfoCartesianPos_qan; i++ )
	{
		rc = modbus_read_registers(mb, InfoCartesianPos_adr[i], InfoCartesianPos_len, tmp_u16float.u16);
		if(rc==(-1)) return (-1);
		*ftmp_ptr = tmp_u16float.f*InfoCartesianPos_Resolution;
		ftmp_ptr++;
	}
	*cp = _deltaDRV_info_CartesianPos;
	return rc;
}

/** * @brief read robot information joint Degree Position
 	* @param InfojDegPos*(jdp), InfojDegPos pointer for storing the result.
 	* @return int, result execution
**	**/
int deltaDRV_modbus_HandShake::read_deltaDRV_info_jDegPos(InfojDegPos *jdp)
{
	ftmp_ptr = &_deltaDRV_info_jDegPos._j1;
	for( int i=0; i<InfojDegPos_qan; i++ )
	{
		rc = modbus_read_registers(mb, InfojDegPos_adr[i], InfojDegPos_len, tmp_u16float.u16);
		if(rc==(-1)) return (-1);
		*ftmp_ptr = tmp_u16float.f*InfojDegPos_Resolution;
		ftmp_ptr++;
	}
	*jdp = _deltaDRV_info_jDegPos;
	return rc;
}




/** * @brief read Robot Device Data Buffer
 	* @param int adr, adrress
 	* @param int nb, quantity
 	* @param uint16_t* data, data
 	* @return int, result execution
**	**/
int deltaDRV_modbus_HandShake::read_deltaDRV_DataBuffer(int adr, int nb, uint16_t *data)
{
	rc = modbus_read_registers(mb, adr, nb, data);
	return rc;
}
/** * @brief write Robot Device Data Buffer
 	* @param int adr, adrress
 	* @param int nb, quantity
 	* @param uint16_t* data, data
 	* @return int, result execution
**	**/
int deltaDRV_modbus_HandShake::write_deltaDRV_DataBuffer(int adr, uint16_t data)
{
	rc = modbus_write_register(mb, adr, data);
	return rc;
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF deltaDRV_modbus_HandShake.cpp ***** */
