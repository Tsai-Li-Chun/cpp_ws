/** ******************************************************
	* @file		ADAM5000_HandShake.hpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __ADAM5000_HandShake_HPP__
#define __ADAM5000_HandShake_HPP__


/* System Includes ------------------------------------------*/
/* System Includes Begin */
// #include <stdio.h>
#include <errno.h>
#include <stdlib.h>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "ADAM5000_DefineTable.hpp"
#include "modbus/modbus.h"
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */
/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */
/* Extern Typedef End */


/* Extern Class -------------------------------------------*/
/* Extern Class Begin */

/* define ADAM5000 communication control object */
class ADAM5000_HandShake
{
/* private member */
private:
	/* define return code */
	int rc;
	/* 宣告libmodbus-API的ReturnCode變數 */
	modbus_t *robot_mt;
	/* digital module status */
	uint8_t DIO_status[digital_module_quantity][digital_channel];
	/* analogy module status */
	uint16_t AIO_status[analogy_channel];

	int ts_DIO_status_col(adam5000_DI ch);	/* calculate DIO_status col */
	int ts_DIO_status_col(adam5000_DO ch);	/* calculate DIO_status col */
	int ts_DIO_status_row(adam5000_DI ch);	/* calculate DIO_status row */
	int ts_DIO_status_row(adam5000_DO ch);	/* calculate DIO_status row */
	int ts_AIO_status_row(adam5000_AO ch);	/* calculate AIO_status row */

/* public member */
public:
	ADAM5000_HandShake(const char *ip,const int port=502,const  int slave=1);	/* constructor */
	~ADAM5000_HandShake();	/* destructor */

	int adam5000_readDI(adam5000_DI ch);/* read single digital input */
	int adam5000_readDI_slot(int slotx);	/* read slotx ALL digital input */
	int adam5000_setDO(adam5000_DO ch, bool v); /* set single digital output */
	int adam5000_readDO(adam5000_DO ch);	/* read single digital output */
	int adam5000_readDO_slot(int slotx);	/* read slotx ALL digital output */

	int adam5000_setAO(adam5000_AO ch, uint16_t v);	/* set single analogy output */
	int adam5000_readAO(adam5000_AO ch);	/* read ALL analogy output */

	uint8_t get_DIO_status(adam5000_DI ch);	/* get slotx specify ch */
	uint8_t get_DIO_status(adam5000_DO ch);	/* get slotx specify ch */
	void get_DIO_status_slot(int slotx, uint8_t *data);/* get slotx ALL ch */
	uint16_t get_AIO_status(adam5000_AO ch);/* get slotx ALL ch */
};

/* Extern Class End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */
/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */


#endif /*__ADAM5000_HandShake_HPP__ */

/* ***** END OF ADAM5000_HandShake.HPP ***** */
