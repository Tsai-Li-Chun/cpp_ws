/** ******************************************************
	* @file		main.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <iostream>
#include <memory>
#include "modbus/modbus.h"
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "main.hpp"
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

/** * @brief  Program entry point.
 	* @param argc(int) : Number of input parameters
 	* @param argv(int) : input parameters
 	* @return (int) Program Error.
**	**/
int main(int argc, char **argv)
{
	/* 隨便顯示些東西證明程式運作 */
	std::cout << "modbus" << std::endl;

	/* 建立modbus通訊結構體 */
	modbus_t *mb;
	/* 建立資料暫存陣列 */
	uint16_t tab_reg[32];
	/* 宣告存放libmodbus-API的return值 */
	int rc;

	/* 初始化modbus通訊設定 */
	mb = modbus_new_tcp("192.168.0.161",502);
	/* 建立連結 */
	rc = modbus_connect(mb);
	// /* FC03,讀取AO暫存器,從start_address開始往後讀nb個 */
	// rc = modbus_read_registers(mb, start_address, nb, tab_reg);
	/* 打印錯誤狀態 */
	std::cout << modbus_strerror(errno) << std::endl;

	/* 關閉連結 */
	modbus_close(mb);
	/* 釋放modbus通訊結構體的位址 */
	modbus_free(mb);

	/* main quit */
	return 0;
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF main.cpp ***** */