/** ******************************************************
	* @file		cas_lab_StandController.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <iostream>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "cas_lab_StandController.hpp"
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

/** * @brief constructor
	* @param none
 	* @return none
**	**/
cas_lab_StandController::cas_lab_StandController():
	deltaDRV_ctl(DRV_modbus_IP, DRV_modbus_port, DRV_modbus_slave),
	adam5000_ctl(adam5000_modbus_IP, adam5000_modbus_port,adam5000_modbus_slave)
{
	std::cout << "[cas_lab_StandController] create Succress!" << std::endl;
}
/** * @brief destructor
	* @param none
 	* @return none
**	**/
cas_lab_StandController::~cas_lab_StandController()
{
	std::cout << "[cas_lab_StandController] release!" << std::endl;
}


/** * @brief read adam5000 input state
	* @param none
 	* @return int, read data result
**	**/
int cas_lab_StandController::read_adma5000_cmd(void)
{
	return 0;
}
/** * @brief read no-item state from adam5000
	* @param uint16_t* data, address where the read results are stored
 	* @return int, read data result
**	**/
int cas_lab_StandController::read_adam5000_noitem(uint16_t* data)
{
	adam5000_ctl.adam5000_readDI(static_cast<adam5000_DI>(cas_stand_adr_in::noitem));
	return rc;
}
int read_adam5000_lowitem(uint16_t* data);		/* read low-item state from adam5000 */
int read_adam5000_highitem(uint16_t* data);		/* read high-item state from adam5000 */
int read_adam5000_toolATC_check(uint16_t* data);/* read toolATC_check state from adam5000 */
int read_adam5000_ReedSwitch1(uint16_t* data);	/* read ReedSwitch1 state from adam5000 */
int read_adam5000_ReedSwitch2(uint16_t* data);	/* read ReedSwitch2 state from adam5000 */
int read_adam5000_ReedSwitch3(uint16_t* data);	/* read ReedSwitch3 state from adam5000 */
int read_adam5000_ReedSwitch4(uint16_t* data);	/* read ReedSwitch4 state from adam5000 */


/** * @brief delay function
	* @param none
 	* @return stand_state, stand system state
**	**/
stand_state cas_lab_StandController::run(void)
{

}


/** * @brief cas lab stand system initialization
	* @param none
 	* @return none
**	**/
void cas_lab_StandController::init(void)
{
	/* stand system IO initialization  */
	/* deltaDRV control-BOX modbus handshake area data initialization  */

}

/** * @brief delay function
	* @param int time, delay time, unit 1ms
 	* @return none
**	**/
void cas_lab_StandController::delay_1ms(int time)
{
	gettimeofday(&tv, NULL);
	delay_time_us_old = ((tv.tv_sec*1000000)+tv.tv_usec);
	while(1)
	{
		gettimeofday(&tv, NULL);
		delay_time_us = ((tv.tv_sec*1000000)+tv.tv_usec);
		if( (delay_time_us-delay_time_us_old) > (time*1000) )
			break;
	}
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF cas_lab_StandController.cpp ***** */
