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

	bool wise4060_readDI(uint8_t channel);
	uint8_t wise4060_readALLDI(void);
	bool wise4060_writeDO(uint8_t channel);
	uint8_t wise4060_writeALLDO(void);
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