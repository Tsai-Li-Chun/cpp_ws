/** ******************************************************
	* @file		main.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <unistd.h>
#include <iostream>
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
	uint8_t i;
	int delay_time=0;
	char c[255];

	/* 隨便顯示些東西證明程式運作 */
	std::cout << "modbus" << std::endl;
	/* 建立modbus通訊物件 */
	Modbus_Handshake MH("192.168.0.161");

    while (1)
	{
		if( delay_time == 500 )
		{
			printf("program runiong...\n");
			delay_time = 0;
		}
		else
		{
			delay_time++;
			usleep(1000);
		}
		fflush(stdout);
		i=0;
		while( MH._kbhit() )
		{
			c[i] = getchar();
			i++;
		}
		if(i != 0)
		{
			printf("%d:\n",i);
			for( int j=0;j<i; j++ )
			printf("%d\n",c[j]);
		}
    }

	/* main quit */
	return 0;
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF main.cpp ***** */