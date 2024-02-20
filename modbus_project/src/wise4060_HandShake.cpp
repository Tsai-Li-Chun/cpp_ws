/** ******************************************************
	* @file		wise4060_HandShake.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <iostream>
#include <stdio.h>
#include <string.h>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "wise4060_HandShake.hpp"	
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
wise4060_HandShake::wise4060_HandShake(const char* IP, int port, int slave)
{
	/* 初始化modbus通訊設定 */
	std::cout << "Modbus TCP Mode Setup : " << IP << std::endl;
	mb = modbus_new_tcp(IP,port);
	if( Modbus_slave_connect(slave) != 0 )
		std::cout << TC_ERROR << "Modbus TCP Mode Setup : " << IP << TC_RESET << std::endl;
	else
	{
		std::cout << "[Create] ModbusTCP(" << IP << ") controller object Success!" << std::endl;
	}
	// /* save original timeout */
	// modbus_get_response_timeout(mb, &response_to_sec, &response_to_usec);
	// std::cout << "response timeout: " << response_to_sec << " : " << response_to_usec << std::endl;
	std::cout << "------------------------------------------------" << std::endl << std::endl;

	/* reset the variable to zero  */
	for(int i=0; i<wise4060_input_quantity; i++)
		DI_status[i]=0xFF;
	for(int i=0; i<wise4060_output_quantity; i++)
		DO_status[i]=0xFF;

	modbus_name = IP;
}

/** * @brief Constructor - RTU Mode
 	* @param device(char*) Modbus Device File path
 	* @param BR(int) Baud Rate
 	* @param parity(int) even/odd parity, default 'N'
 	* @param data_bit(int) DataBit Length, default 8(bit)
 	* @param stop_bit(int) StopBit Length, default 1(bit)
 	* @param slave(int) Modbus Device ID, default 1
 	* @return None
**	**/
wise4060_HandShake::wise4060_HandShake(const char* device, int BR, char parity, int data_bit, int stop_bit, int slave)
{
	/* 初始化modbus通訊設定 */
	std::cout << "Modbus RTU Mode Setup : " << device << std::endl;
	mb = modbus_new_rtu(device,BR,parity,data_bit,stop_bit);
	if( Modbus_slave_connect(slave) != 0 )
		std::cout << TC_ERROR << "Modbus RTU Mode Setup : " << device << TC_RESET << std::endl;
	else
		std::cout << "[Create] ModbusRTU(" << device << ") controller object Success!" << std::endl;
	std::cout << "------------------------------------------------" << std::endl << std::endl;
	
	/* reset the variable to zero  */
	for(int i=0; i<wise4060_input_quantity; i++)
		DI_status[i]=0xFF;
	for(int i=0; i<wise4060_output_quantity; i++)
		DO_status[i]=0xFF;

	modbus_name = device;
}

/** * @brief Setup SlaveID & Connect
 	* @param slave(int) Modbus Device ID, default 1
 	* @return int 
**	**/
int wise4060_HandShake::Modbus_slave_connect(int slave)
{
	/* 宣告libmodbus-API的ReturnCode變數 */
	int rc;
	/* 初始化是否成功判斷 */
	if( mb == NULL )
	{	/* 若初始化失敗,打印訊息,退出程序 */
		std::cout << TC_ERROR << modbus_strerror(errno) << TC_RESET << std::endl;;
		exit(EXIT_FAILURE);
	}
	else
	{	/* 若初始化成功,打印訊息 */
		std::cout << "Initialize modbus_t Structure Success" << std::endl;
	}

	/* 設定欲通訊的modbus-slaveID */
	rc = modbus_set_slave(mb,slave);
	if( rc != 0 )
	{	/* 若設定失敗,打印訊息,退出建構函數 */
		std::cout << TC_ERROR << "Setup modbus slave Failure! : " << slave << TC_RESET << std::endl;
		return rc;
	}
	else
	{	/* 若slaveID設定成功,打印訊息 */
		std::cout << "Setup modbus slave(" << slave << ") Success!" << std::endl;
	}

	/* 建立連結 */
	rc = modbus_connect(mb);
	if( rc != 0 )
	{	/* 若設定失敗,打印訊息,退出建構函數 */
		std::cout << TC_ERROR << "Connect modbusIP:slave(" \
			<< modbus_name << ":" << slave << " Failure!" << std::endl;
		std::cout << "    >> " << modbus_strerror(errno) << TC_RESET << std::endl;
		return rc;
	}
	else
	{	/* 若連結成功,打印訊息 */
		std::cout << "Connect modbusIP:slave(" << modbus_name << ":" << slave << " Success!" << std::endl;
	}

	/* 程式正常結束,返回0 */
	return 0;
}

/** * @brief Destructor
 	* @param None
 	* @return None
**	**/
wise4060_HandShake::~wise4060_HandShake()
{
	/* close connect */
	modbus_close(mb);
	/* release the address of the modbus_communication_structure */
	modbus_free(mb);
	/* 打印關閉訊息 */
	std::cout << "modbus connect close : " << modbus_name << std::endl;
}

/** * @brief read single input channel function
 	* @param DI_Address channel, specify the channel to read
 	* @return int, result execution
**	**/
int wise4060_HandShake::wise4060_readDI(DI_Address channel)
{
	int addr = (int)channel;
	int shift = addr - (int)DI_Address::DI_0;
	rc = modbus_read_input_bits(mb, addr, 1, &DI_status[shift]);
	return rc;
}

/** * @brief read ALL input channel function
 	* @param None
 	* @return int, result execution
**	**/
int wise4060_HandShake::wise4060_readALLDI(void)
{
	int addr = (int)DI_Address::DI_0;
	rc = modbus_read_input_bits(mb, addr, wise4060_input_quantity, DI_status);
	return rc;
}

/** * @brief read single output channel function
 	* @param DO_Address channel, specify the channel to read
 	* @return int, result execution
**	**/
int wise4060_HandShake::wise4060_readDO(DO_Address channel)
{
	int addr = (int)channel;
	int shift = addr - (int)DO_Address::DO_0;
	rc = modbus_read_bits(mb, addr, 1, &DO_status[shift]);
	return rc;
}

/** * @brief read ALL output channel function
 	* @param None
 	* @return int, result execution
**	**/
int wise4060_HandShake::wise4060_readALLDO(void)
{
	int addr = (int)DO_Address::DO_0;
	rc = modbus_read_bits(mb, addr, wise4060_output_quantity, DO_status);
	return rc;
}

/** * @brief write single output channel function
 	* @param uint8_t channel, specify the channel to write
 	* @param int onoff, output status
 	* @return int, result execution
**	**/
int wise4060_HandShake::wise4060_writeDO(DO_Address channel,const int onoff)
{
	int addr = (int)channel;
	int shift = addr - (int)DO_Address::DO_0;
	rc = modbus_write_bit(mb, addr, onoff);
	DO_status[shift] = (uint8_t)onoff;
	return rc;
}

/** * @brief write ALL output channel function
 	* @param uint8_t[4] channel, specify the channel to write
 	* @return int, result execution
**	**/
int wise4060_HandShake::wise4060_writeALLDO(const uint8_t *onoff)
{
	int addr = (int)DO_Address::DO_0;
	rc = modbus_write_bits(mb, addr, wise4060_output_quantity, onoff);
	memcpy(DO_status, onoff, wise4060_output_quantity);
	return rc;
}

/** * @brief get DI_status value
 	* @param uint8_t *din, returning specified value using pointers
 	* @return None
**	**/
void wise4060_HandShake::get_DI_status(uint8_t *din)
{
	// memcpy(din, DI_status, wise4060_input_quantity);
	for(int i=0; i<wise4060_input_quantity; i++)
		din[i] = DI_status[i];
}

/** * @brief get DO_status value
 	* @param uint8_t *dout, returning specified value using pointers
 	* @return None
**	**/
void wise4060_HandShake::get_DO_status(uint8_t *dout)
{
	memcpy(dout, DO_status, wise4060_output_quantity);
}

/** * @brief verify connection status
 	* @param none
 	* @return int, connection status, 1:connected, 0:disconnected
**	**/
int wise4060_HandShake::isConnect(void)
{
	module_name = 0;
	rc = modbus_read_registers(mb, 210, 1, &module_name);
	return (module_name == 0x4060);
	// rc = modbus_connect(mb);
	// return rc;
}

/** * @brief reconnection to modbus
 	* @param none
 	* @return int, reconnection result, 0:success, -1:fail
**	**/
int wise4060_HandShake::reConnect(void)
{
	// rc = modbus_read_registers(mb, 210, 1, &module_name);
	// return (module_name == 0x4060);
	rc = modbus_connect(mb);
	return rc;
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF wise4060_HandShake.cpp ***** */