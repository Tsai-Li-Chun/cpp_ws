/** ******************************************************
	* @file		main.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <iostream>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>

/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "main.hpp"
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

/** * @brief  Program entry point.
 	* @param argc(int) Number of input parameters
 	* @param argv(int) input parameters
 	* @return (int) Program Error.
**	**/
int main(int argc, char **argv)
{
	/* 隨便顯示些東西證明程式運作 */
	std::cout << "modbus" << std::endl;
	/* 關閉終端機本身緩衝區返饋 */
	system("stty -echo");
	/* 建立modbus通訊物件 */
	Modbus_Handshake MH("192.168.0.161");

	/* main loop */
	while(1)
	{
		// MH.keyborad_to_cardir();
		MH.send_speed();
		usleep(100*1000);
		// printf("%d,%d\n",MH.getvel(),MH.getyaw());
	}

	/* main quit */
	return 0;
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF main.cpp ***** */