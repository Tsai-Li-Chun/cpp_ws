/** ******************************************************
	* @file		Modbus_Handshake.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <stdio.h>
#include <iostream>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "Modbus_Handshake.hpp"
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
Modbus_Handshake::Modbus_Handshake(const char* IP, int port, int slave)
{
	/* 初始化modbus通訊設定 */
	mb = modbus_new_tcp(IP,port);
	if( Modbus_slave_connect(slave) != 0 )
		printf("Modbus TCP Mode Setup Failure!\n");

	/* 鍵盤緩衝區初始化函數 */
	kb_event_init();

	vel.f = 0; yaw.f = 0;
	modbus_write_bit(mb,9,TRUE);
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
Modbus_Handshake::Modbus_Handshake(const char* device, int BR, char parity, int data_bit, int stop_bit, int slave)
{
	/* 初始化modbus通訊設定 */
	mb = modbus_new_rtu(device,BR,parity,data_bit,stop_bit);
	if( Modbus_slave_connect(slave) != 0 )
		printf("Modbus RTU Mode Setup Failure!\n");
	
	/* 鍵盤文件初始化函數 */
	kb_event_init();
}

/** * @brief Setup SlaveID & Connect
 	* @param slave(int) Modbus Device ID, default 1
 	* @return int 
**	**/
int Modbus_Handshake::Modbus_slave_connect(int slave)
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
		return rc;
	}
	else
	{	/* 若連結成功,打印訊息 */
		printf("Slave ID \"%d\" Connect Success\n", slave);
		printf("%s\n",modbus_strerror(errno));
	}

	/* 程式正常結束,返回0 */
	return 0;
}

/** * @brief 鍵盤文件初始化函數
 	* @param None
 	* @return None 
**	**/
int Modbus_Handshake::kb_event_init(void)
{
	/* 已只讀模式開啟鍵盤文件,並設置為非阻塞 */
	keys_fd = open("/dev/input/event6",O_RDONLY|O_NONBLOCK);
	if(keys_fd == (-1))
	{	/* 若開啟失敗,打印消息並跳出 */
		printf("Open /dev/input/event6 Error");
		return -1;
	}
	/* 關閉終端機本身緩衝區返饋 */
	system("stty -echo");
	return 0;
}

/** * @brief Destructor
 	* @param None
 	* @return None
**	**/
Modbus_Handshake::~Modbus_Handshake()
{
	/* 關閉連結 */
	modbus_close(mb);
	/* 釋放modbus通訊結構體的位址 */
	modbus_free(mb);
	/* 打印關閉訊息 */
	printf("modbus connect close\n");
	/* 開啟終端機本身緩衝區返饋 */
	system("stty echo");
}


/** * @brief 獲取鍵盤方向鍵轉車子方向函數
 	* @param None
 	* @return None
**	**/
void Modbus_Handshake::keyborad_to_cardir(void)
{
	/* 讀取鍵盤文件內容,若讀取資料結構錯誤,跳回迴圈開頭 */
	// if( read(keys_fd,&kb,sizeof(kb)) != sizeof(kb) ) continue;
	/* 讀取鍵盤文件內容 */
	read(keys_fd,&kb,sizeof(kb));
	/* 若事件為按鈕按下事件 */
	if( kb.type == EV_KEY )
	{	/* 獲取鍵值與該鍵按放狀態 */
		if( kb.code == KEY_UP ) up = kb.value;
		if( kb.code == KEY_DOWN ) down = kb.value;
		if( kb.code == KEY_LEFT ) left = kb.value;
		if( kb.code == KEY_RIGHT ) right = kb.value;
		/* 打印獲取鍵值與該鍵按放狀態,除錯用 */
		// printf("%d,%d\n",kb.code,kb.value);
		/* 依鍵值與按放狀態換車子方向 */
		yaw.f = left>0? 0.8 : right>0? -0.8 : 0;
		vel.f = up>0? 0.8 : down>0? -0.8 : 0;
		modbus_write_registers(mb,21,2,vel.ch);
		modbus_write_registers(mb,25,2,vel.ch);
	}
}

/** * @brief 發送車子速度指令
 	* @param None
 	* @return None
**	**/
void Modbus_Handshake::send_speed(void)
{
	// vel_d.f = 0.2;
	// yaw_d.f = 0.2;
	// modbus_write_registers(mb,14,2,vel_d.ch);
	// modbus_write_registers(mb,18,2,yaw_d.ch);
	// vel.f = 0.5; vel_d.f = 0.2;
	// modbus_write_registers(mb,21,2,vel.ch);
	// modbus_write_registers(mb,14,2,vel_d.ch);
	// yaw.f = 0.5; yaw_d.f = 0.2;
	// modbus_write_registers(mb,25,2,yaw.ch);
	// modbus_write_registers(mb,18,2,yaw_d.ch);
	vel.f = 0.5;
	modbus_write_registers(mb,4,2,vel.ch);
}

float Modbus_Handshake::getvel(void)
{
	return vel.f;
}
float Modbus_Handshake::getyaw(void)
{
	return yaw.f;
}


/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF Modbus_Handshake.cpp ***** */