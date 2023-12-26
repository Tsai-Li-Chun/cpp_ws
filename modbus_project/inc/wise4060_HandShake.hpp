/** ******************************************************
	* @file		wise4060_HandShake.h
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __wise4060_HandShake_HPP__
#define __wise4060_HandShake_HPP__


/* System Includes ------------------------------------------*/
/* System Includes Begin */
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "WISE4060_ModbusAddressTable.hpp"
#include "modbus/modbus.h"
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */
/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */

union modbus_u16tofloat
{
    float f;
    uint16_t ch[ (sizeof(float))/sizeof(uint16_t) ];
};

union modbus_u8tou16
{
    uint16_t u16;
    uint8_t u8[ (sizeof(uint16_t))/sizeof(uint8_t) ];
};

/* Extern Typedef End */


/* Extern Class -------------------------------------------*/
/* Extern Class Begin */

/* 宣告modbus通訊物件 */
class wise4060_HandShake
{
/* 私有成員 */
private:
	/* create modbus_communication_structure */
	modbus_t* mb;

	/* libmodbus return value(ReturnCode) */
	int rc;
	/* for temporary IO status */
	uint8_t DIO_tmp=0;
	/* for status of each input channel */
	uint8_t DI_status[wise4060_input_quantity];
	/* for status of each output channel */
	uint8_t DO_status[wise4060_output_quantity];

	/* 設定連結函數 */
	int Modbus_slave_connect(int slave);

/* 公有成員 */
public:
	/* 建構函數 - TCP模式 */
	wise4060_HandShake(const char* IP, int port, int slave);
	/* 建構函數 - RTU模式 */
	wise4060_HandShake(const char* device, int BR, char parity='N', int data_bit=8, int stop_bit=1, int slave=1);
	/* 解建構函數 */
	~wise4060_HandShake();

	/* read single input channel function */
	int wise4060_readDI(DI_Address channel);
	/* read ALL input channel function */
	int wise4060_readALLDI(void);
	/* read single output channel function */
	int wise4060_readDO(DO_Address channel);
	/* read ALL output channel function */
	int wise4060_readALLDO(void);
	/* write single output channel function */
	int wise4060_writeDO(DO_Address channel,const int onoff);
	/* write ALL output channel function */
	int wise4060_writeALLDO(const uint8_t *onoff);

	/* get DI_status value */
	void get_DI_status(uint8_t *din);
	/* get DO_status value */
	void get_DO_status(uint8_t *dout);
};

/* Extern Class End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */
/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */


#endif /*__wise4060_HandShake_HPP__ */

/* ***** END OF wise4060_HandShake.HPP ***** */