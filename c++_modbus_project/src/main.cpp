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
	uint8_t tab_reg[nb];
	/* 宣告存放libmodbus-API的return值 */
	int rc;
	uint32_t to_sec;
	uint32_t to_usec;

	/* 初始化modbus通訊設定 */
	mb = modbus_new_tcp("192.168.0.183",502);
	rc = modbus_set_slave(mb,1);
	std::cout << rc << " : " << modbus_strerror(errno) << std::endl;
	/* 建立連結 */
	rc = modbus_connect(mb);
	std::cout << rc << " : " << modbus_strerror(errno) << std::endl;


	modbus_get_byte_timeout( mb ,&to_sec ,&to_usec );
	std::cout << unsigned(to_sec) << " -- " << unsigned(to_usec) << std::endl;
	modbus_get_response_timeout( mb ,&to_sec ,&to_usec );
	std::cout << unsigned(to_sec) << " -- " << unsigned(to_usec) << std::endl;

	/* FC02,讀取DI暫存器,從start_address開始往後讀nb個 */
	rc = modbus_read_input_bits(mb, start_address, nb, tab_reg);
	std::cout << rc << std::endl;
	for( int i=0; i<rc; i++ )
		std::cout << unsigned(tab_reg[i]) << std::endl;

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