/** ******************************************************
	* @file		WISE4060_ModbusAddressTable.hpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __WISE4060_ModbusAddressTable_HPP__
#define __WISE4060_ModbusAddressTable_HPP__


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include "stdint.h"
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */

#define wise4060_IP "192.168.1.6"
#define wise4060_port 502
#define wise4060_slave 1

/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */
/* Extern Typedef End */


/* Extern Class -------------------------------------------*/
/* Extern Class Begin */

enum class DI_Address:uint8_t
{
	DI_0 = 1,
	DI_1 = 2,
	DI_2 = 3,
	DI_3 = 4
};
enum class DO_Address:uint8_t
{
	DO_0 = 17,
	DO_1 = 18,
	DO_2 = 19,
	DO_3 = 20
};

/* Extern Class End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */
/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */


#endif /*__WISE4060_ModbusAddressTable_HPP__ */

/* ***** END OF WISE4060_ModbusAddressTable.HPP ***** */
