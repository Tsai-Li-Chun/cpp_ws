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

/** * @brief read robot information PUU
 	* @param robot_info_PUU_adr(adr), modbus register address
	* @param int32_t(puu), returned data
 	* @return int, result execution
**	**/
int deltaDRV_modbus_HandShake::read_deltaDRV_info_PUU(deltaDRV_info_PUU *puu)
{
	int8_t len=0;
	rc = modbus_read_registers(mb, static_cast<int>(deltaDRV_info_PUU_adr::axis1),
								   static_cast<int>(deltaDRV_info_PUU_len),
								   tmp_u16i32.u16 );
	return rc;
}


/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF deltaDRV_modbus_HandShake.cpp ***** */
