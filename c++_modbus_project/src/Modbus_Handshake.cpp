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
	kbhit_init();
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
	
	/* 鍵盤緩衝區初始化函數 */
	kbhit_init();
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

/** * @brief 鍵盤緩衝區初始化函數
 	* @param None
 	* @return None 
**	**/
int Modbus_Handshake::kbhit_init(void)
{	/* Use termios to turn off line buffering */
	int rc = 0;
	termios term;
	tcgetattr(STDIN, &term);
	term.c_lflag &= ~ICANON;
	rc = tcsetattr(STDIN, TCSANOW, &term);
	setbuf(stdin, NULL);
	if( rc != 0 )
	{	/* 若設定失敗,打印訊息,退出建構函數 */
		printf("KeyBoard Buffer SetUp Failure!\n");
		return rc;
	}

	/* 若連結成功,打印訊息 */
	printf("KeyBoard Buffer SetUp Success\n");
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
}


/** * @brief 判斷鍵盤緩衝區有無資料函數
 	* @param None
 	* @return int, 緩衝區有資料(1), 反之(0)
**	**/
int Modbus_Handshake::_kbhit(void)
{
	bytesWaiting = 0;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}


/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF Modbus_Handshake.cpp ***** */