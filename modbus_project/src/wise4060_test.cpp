/** ******************************************************
	* @file		main.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <iostream>
#include <unistd.h>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "wise4060_HandShake.hpp"
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

	/* 存放4組DI狀態用陣列 */
	uint8_t DI_status[wise4060_input_quantity];
	/* 存放4組DO狀態用陣列 */
	uint8_t DO_status[wise4060_output_quantity];

	/* 指定欲操作的DI */
	DI_Address current_di;
	/* 指定欲操作的DO */
	DO_Address current_do;

	/* 建立modbus通訊物件 */
	wise4060_HandShake wise4060(wise4060_IP, wise4060_port, wise4060_slave);

	/* 依序讀取 DI 0-3 */
	printf("wise4060_readDI:\n");
	for (int i=static_cast<int>(DI_Address::DI_0); i<=static_cast<int>(DI_Address::DI_3); i++)
	{
        current_di = static_cast<DI_Address>(i);
		wise4060.wise4060_readDI(current_di);
		wise4060.get_DI_status(DI_status);
		printf("%02x , %02x , %02x , %02x\n",DI_status[3],DI_status[2],DI_status[1],DI_status[0]);
    }
	printf("\n");

	/* 1次讀取 DI 0-3 */
	printf("wise4060_readALLDI:\n");
	wise4060.wise4060_readALLDI();
	wise4060.get_DI_status(DI_status);
	printf("%02x , %02x , %02x , %02x\n\n",DI_status[3],DI_status[2],DI_status[1],DI_status[0]);

	/* 依序讀寫 DO 0-3 */
	for(int i=static_cast<int>(DO_Address::DO_0); i<=static_cast<int>(DO_Address::DO_3); i++)
	{
		printf("wise4060_read and write DO_%d:\n",i-16);
		current_do = static_cast<DO_Address>(i);
		wise4060.wise4060_writeDO(current_do,true);
		wise4060.wise4060_readDO(current_do);
		wise4060.get_DO_status(DO_status);
		printf("%02x , %02x , %02x , %02x\n",DO_status[3],DO_status[2],DO_status[1],DO_status[0]);
		sleep(2);
		wise4060.wise4060_writeDO(current_do,false);
		wise4060.wise4060_readDO(current_do);
		wise4060.get_DO_status(DO_status);
		printf("%02x , %02x , %02x , %02x\n",DO_status[3],DO_status[2],DO_status[1],DO_status[0]);
		sleep(2);
	}

	// /* main loop */
	// while(1)
	// {
	// }

	/* main quit */
	return 0;
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF main.cpp ***** */