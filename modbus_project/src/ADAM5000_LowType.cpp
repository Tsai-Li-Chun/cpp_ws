/** ******************************************************
	* @file		ADAM5000_LowType.cpp
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
#include "ADAM5000_HandShake.hpp"
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
	int j = 0;
	int i = static_cast<int>(adam5000_DO::DO_3_00);
	bool onoff = true;
	/* digital module status */
	uint8_t DIO_status[digital_module_quantity][digital_channel];
	/* analogy module status */
	uint16_t AIO_status[analogy_channel];
	ADAM5000_HandShake _adam5000_ctl(adam5000_modbus_IP, adam5000_modbus_port,adam5000_modbus_slave);
	sleep(3);
	std::cout << TC_CLOSE << std::endl;

	while(1)
	{
		for(j=static_cast<int>(adam5000_DI::DI_2_00);j<=static_cast<int>(adam5000_DI::DI_2_15);j++)
			_adam5000_ctl.adam5000_readDI(static_cast<adam5000_DI>(j));
		_adam5000_ctl.adam5000_setDO(static_cast<adam5000_DO>(i) ,onoff);
		onoff = (!onoff);
		if(onoff)
		{
			i++;
			if(i>static_cast<int>(adam5000_DO::DO_4_15))
				i = static_cast<int>(adam5000_DO::DO_3_00);
		}
		for(j=static_cast<int>(adam5000_DO::DO_3_00);j<=static_cast<int>(adam5000_DO::DO_4_15);j++)
			_adam5000_ctl.adam5000_readDO(static_cast<adam5000_DO>(j));
		// for(j=static_cast<int>(adam5000_DO::DO_4_00);j<static_cast<int>(adam5000_DO::DO_4_15);j++)
		// 	_adam5000_ctl.adam5000_readDO(static_cast<adam5000_DO>(j));
		// _adam5000_ctl.adam5000_readDO_slot(slot4_DO_x56);
		for(j=static_cast<int>(adam5000_DI::DI_2_00);j<=static_cast<int>(adam5000_DI::DI_2_15);j++)
			DIO_status[0][(j%16)] = _adam5000_ctl.get_DI_status(static_cast<adam5000_DI>(j));
		for(j=static_cast<int>(adam5000_DO::DO_3_00);j<=static_cast<int>(adam5000_DO::DO_4_15);j++)
			DIO_status[(j/16-1)][(j%16)] = _adam5000_ctl.get_DO_status(static_cast<adam5000_DO>(j));
		// for(j=static_cast<int>(adam5000_DO::DO_4_00);j<=static_cast<int>(adam5000_DO::DO_4_15);j++)
		// 	DIO_status[2][(j%16)] = _adam5000_ctl.get_DIO_status(static_cast<adam5000_DO>(j));

		std::cout << i << " , " << onoff << std::endl;
		printf("slot2_DI_x51 :");
		for(j=0;j<16;j++)
			printf(" %2x",DIO_status[slot2_DI_x51][j]);
		printf("\n");
		printf("slot3_DO_x56 :");
		for(j=0;j<16;j++)
			printf(" %2x",DIO_status[slot3_DO_x56][j]);
		printf("\n");
		printf("slot4_DO_x56 :");
		for(j=0;j<16;j++)
			printf(" %2x",DIO_status[slot4_DO_x56][j]);
		printf("\n");
		sleep(1);
		std::cout << TC_CLOSE << std::endl;
	}
	/* main quit */
	return 0;
}
/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF ADAM5000_LowType.cpp ***** */
