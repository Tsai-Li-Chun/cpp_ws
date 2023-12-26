/** ******************************************************
	* @file		deltaDRV_modbus_HandShake.hpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __deltaDRV_modbus_HandShake_HPP__
#define __deltaDRV_modbus_HandShake_HPP__


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <stdint.h>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "deltaDRV_modbus_defineTable.hpp"
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */
/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */

/* conversion u16 to float structure */
union modbus_u16tofloat
{
    float f;
    uint16_t ch[ (sizeof(float))/sizeof(uint16_t) ];
};

/* conversion u18 to u16 structure */
union modbus_u8tou16
{
    uint16_t u16;
    uint8_t u8[ (sizeof(uint16_t))/sizeof(uint8_t) ];
};

/* Extern Typedef End */


/* Extern Class -------------------------------------------*/
/* Extern Class Begin */

class deltaDRV_modbus_HandShake
{
/* private members */
private:

/* public members */
public:
	/* constructor */
	deltaDRV_modbus_HandShake();
	/* destructor */
	~deltaDRV_modbus_HandShake();
};

/* Extern Class End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */
/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */


#endif /*__deltaDRV_modbus_HandShake_HPP__ */

/* ***** END OF deltaDRV_modbus_HandShake.HPP ***** */
