/** ******************************************************
	* @file		ADAM5000_HandShake.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <iostream>
#include <string.h>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "ADAM5000_HandShake.hpp"
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
 	* @param ip(char*) Modbus Device IP Address
 	* @param port(int) communication port, default 502
 	* @param slave(int) Modbus Device ID, default 1
 	* @return None
**	**/
ADAM5000_HandShake::ADAM5000_HandShake(const char* ip,const int port,const int slave)
{
	/* 初始化modbus通訊設定 */
	robot_mt = modbus_new_tcp(ip,port);
	/* 初始化是否成功判斷 */
	if( robot_mt == NULL )
	{	/* 若初始化失敗,打印訊息,退出程序 */
		std::cout << TC_ERROR << modbus_strerror(errno) << TC_RESET << std::endl;
		// printf("%s\n",);
		exit(EXIT_FAILURE);
	}
	else	/* 若初始化成功,打印訊息 */
		std::cout << "Initialize modbus_t Structure Success" << std::endl;

	/* 設定欲通訊的modbus-slaveID */
	rc = modbus_set_slave(robot_mt,slave);
	if( rc != 0 )
	{	/* 若設定失敗,打印訊息,退出建構函數 */
		std::cout << TC_ERROR << "set modbus slave Failure!" << TC_RESET << std::endl;
		exit(EXIT_FAILURE);
	}
	else	/* 若slaveID設定成功,打印訊息 */
		std::cout << "set modbus slave [" << slave << "] Success!" << std::endl;

	/* 建立連結 */
	rc = modbus_connect(robot_mt);
	if( rc != 0 )
	{	/* 若設定失敗,打印訊息,退出建構函數 */
		std::cout << TC_ERROR << "connect modbus Failure!" << std::endl;
		std::cout << "    ==> " << modbus_strerror(errno) << TC_RESET << std::endl;
		// exit(EXIT_FAILURE);
	}
	else	/* 若連結成功,打印訊息 */
		std::cout << "[Create ADAM5000_HandShake] connect modbus slave [" << slave << "] Success!" << std::endl;
}


/** * @brief destructor
 	* @param None
 	* @return None
**	**/
ADAM5000_HandShake::~ADAM5000_HandShake()
{
	/* close connect */
	modbus_close(robot_mt);
	/* release the address of the modbus_communication_structure */
	modbus_free(robot_mt);
	/* 打印關閉訊息 */
	printf("modbus connect close\n");
}

/** * @brief calculate DIO_status col
 	* @param adam5000_DI channel, specify the channel to read
 	* @return int, col value
**	**/
int ADAM5000_HandShake::ts_DIO_status_col(adam5000_DI ch)
{
	return (static_cast<int>(ch)/16)-1;
}
int ADAM5000_HandShake::ts_DIO_status_col(adam5000_DO ch)
{
	return (static_cast<int>(ch)/16)-1;
}
/** * @brief calculate DIO_status row
 	* @param adam5000_DI channel, specify the channel to read
 	* @return int, row value
**	**/
int ADAM5000_HandShake::ts_DIO_status_row(adam5000_DI ch)
{
	return (static_cast<int>(ch)%16);
}
int ADAM5000_HandShake::ts_DIO_status_row(adam5000_DO ch)
{
	return (static_cast<int>(ch)%16);
}
/** * @brief calculate AIO_status row
 	* @param adam5000_AO channel, specify the channel to read
 	* @return int, row value
**	**/
int ADAM5000_HandShake::ts_AIO_status_row(adam5000_AO ch)
{
	return static_cast<int>(ch);
}

/** * @brief read single digital input
 	* @param adam5000_DI ch, specify the channel to read
 	* @return int, result execution
**	**/
int ADAM5000_HandShake::adam5000_readDI(adam5000_DI ch)
{
	rc = modbus_read_input_bits(robot_mt, static_cast<int>(ch), 1,
							   &DIO_status[ts_DIO_status_col(ch)][ts_DIO_status_row(ch)]);
	return rc;
}
/** * @brief read slotx ALL digital input
 	* @param int slotx, specify the slot to read
 	* @return int, result execution
**	**/
int ADAM5000_HandShake::adam5000_readDI_slot(int slotx)
{
	rc = modbus_read_input_bits(robot_mt, (slotx+1)*digital_channel, digital_channel,
							   DIO_status[slotx]);
	return rc;
}

/** * @brief set single digital output
 	* @param adam5000_DO ch, specify the channel to set
 	* @param bool v, on or off
 	* @return int, result execution
**	**/
int ADAM5000_HandShake::adam5000_setDO(adam5000_DO ch, bool v)
{
	rc = modbus_write_bit(robot_mt, static_cast<int>(ch), v);
	return rc;
}
/** * @brief read single digital output
 	* @param adam5000_DO ch, specify the channel to read
 	* @return int, result execution
**	**/
int ADAM5000_HandShake::adam5000_readDO(adam5000_DO ch)
{
	rc = modbus_read_bits(robot_mt, static_cast<int>(ch), 1,
						  &DIO_status[ts_DIO_status_col(ch)][ts_DIO_status_row(ch)]);
	return rc;
}
/** * @brief read slotx ALL digital output
 	* @param int slotx, specify the slot to read
 	* @return int, result execution
**	**/
int ADAM5000_HandShake::adam5000_readDO_slot(int slotx)
{
	rc = modbus_read_bits(robot_mt, (slotx+1)*digital_channel, digital_channel,
						  DIO_status[slotx]);
	return rc;
}

/** * @brief set single analogy output
 	* @param adam5000_AO ch, specify the channel to set
 	* @return int, result execution
**	**/
int ADAM5000_HandShake::adam5000_setAO(adam5000_AO ch, uint16_t v)
{
	rc = modbus_write_register(robot_mt, static_cast<int>(ch), v);
	return rc;
}
/** * @brief read single digital output
 	* @param adam5000_DO ch, specify the channel to read
 	* @return int, result execution
**	**/
int ADAM5000_HandShake::adam5000_readAO(adam5000_AO ch)
{
	rc = modbus_read_registers(robot_mt, static_cast<int>(ch), 1,
						  &AIO_status[ts_AIO_status_row(ch)]);
	return rc;
}

uint8_t ADAM5000_HandShake::get_DIO_status(adam5000_DI ch)
{
	return DIO_status[ts_DIO_status_col(ch)][ts_DIO_status_row(ch)];
}
uint8_t ADAM5000_HandShake::get_DIO_status(adam5000_DO ch)
{
	return DIO_status[ts_DIO_status_col(ch)][ts_DIO_status_row(ch)];
}
void ADAM5000_HandShake::get_DIO_status_slot(int slotx, uint8_t *data)
{
	// data = DIO_status[slotx];
	memcpy(data, DIO_status[slotx], digital_channel);
	// return DIO_status[slotx];
}
uint16_t ADAM5000_HandShake::get_AIO_status(adam5000_AO ch)
{
	return AIO_status[ts_AIO_status_row(ch)];
}


/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF ADAM5000_HandShake.cpp ***** */
