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
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
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

union modbus_32Format
{
    float f;
    uint16_t ch[ (sizeof(f))/sizeof(uint16_t) ];
};

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
	/* 宣告檔案描述符 */
	int keys_fd;
	/* 宣告input事件結構體 */
	input_event kb;
	/* 宣告按鍵指標 */
	int up=0,down=0,left=0,right=0;
	/* 宣告中心速度&角速度 */
	modbus_32Format vel,yaw;
	modbus_32Format vel_d,yaw_d;

	/* 設定連結函數 */
	int Modbus_slave_connect(int slave);
	/* 鍵盤文件初始化函數 */
	int kb_event_init(void);

/* 公有成員 */
public:
	/* 建構函數 - TCP模式 */
	Modbus_Handshake(const char* IP, int port=502, int slave=1);
	/* 建構函數 - RTU模式 */
	Modbus_Handshake(const char* device, int BR, char parity='N', int data_bit=8, int stop_bit=1, int slave=1);
	/* 解建構函數 */
	~Modbus_Handshake();
	/* 獲取鍵盤方向鍵轉車子方向函數 */
	void keyborad_to_cardir(void);
	/* 發送車子速度指令 */
	void send_speed(void);

	float getvel(void);
	float getyaw(void);

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