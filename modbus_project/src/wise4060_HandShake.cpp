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
	mb = modbus_new_tcp(IP,port);
	if( Modbus_slave_connect(slave) != 0 )
		printf("Modbus TCP Mode Setup Failure!\n");
	
	/* reset the variable to zero  */
	for(int i=0; i<wise4060_input_quantity; i++)
		DI_status[i]=0xFF;
	for(int i=0; i<wise4060_output_quantity; i++)
		DO_status[i]=0xFF;
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
	mb = modbus_new_rtu(device,BR,parity,data_bit,stop_bit);
	if( Modbus_slave_connect(slave) != 0 )
		printf("Modbus RTU Mode Setup Failure!\n");
	
	/* reset the variable to zero  */
	for(int i=0; i<wise4060_input_quantity; i++)
		DI_status[i]=0xFF;
	for(int i=0; i<wise4060_output_quantity; i++)
		DO_status[i]=0xFF;
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
	printf("modbus connect close\n");
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

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF wise4060_HandShake.cpp ***** */