/** ******************************************************
	* @file		Modbus_Handshake.h
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __Modbus_Handshake_HPP__
#define __Modbus_Handshake_HPP__


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <termios.h>
#include <sys/ioctl.h>
#include "modbus/modbus.h"
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
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
class Modbus_Handshake
{
/* 私有成員 */
private:
	/* 建立modbus通訊結構體 */
	modbus_t* mb;
	/* kbhit用設定文件旗標 */
	const int STDIN = 0;
	/* kbhit用判斷鍵盤緩衝區有無資料旗標 */
	int bytesWaiting;

	/* 設定連結函數 */
	int Modbus_slave_connect(int slave);
	/* 鍵盤緩衝區初始化函數 */
	int kbhit_init(void);

/* 公有成員 */
public:
	/* 建構函數 - TCP模式 */
	Modbus_Handshake(const char* IP, int port=502, int slave=1);
	/* 建構函數 - RTU模式 */
	Modbus_Handshake(const char* device, int BR, char parity='N', int data_bit=8, int stop_bit=1, int slave=1);
	/* 解建構函數 */
	~Modbus_Handshake();
	/* 判斷鍵盤緩衝區有無資料函數 */
	int _kbhit(void);

};

/* Extern Class End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */
/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */


#endif /*__ Modbus_Handshake_HPP__ */

/* ***** END OF Modbus_Handshake.HPP ***** */