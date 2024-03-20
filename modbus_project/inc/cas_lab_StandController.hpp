/** ******************************************************
	* @file		cas_lab_StandController.hpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __cas_lab_StandController_HPP__
#define __cas_lab_StandController_HPP__


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <sys/time.h>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "cas_lab_StandDefineTable.hpp"
#include "ADAM5000_HandShake.hpp"
#include "deltaDRV_modbus_HandShake.hpp"
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */
/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */
/* Extern Typedef End */


/* Extern Class -------------------------------------------*/
/* Extern Class Begin */

/* define stand system control object */
class cas_lab_StandController
{
/* private member */
private:
	/* define return code */
	int rc;
	/* define variable used for delay time */
	struct timeval tv;
	long delay_time_us_old,delay_time_us;
	/* create deltaDRV-BOX control object */
	deltaDRV_modbus_HandShake deltaDRV_ctl;
	/* create remotIO(ADAM5000) control object  */
	ADAM5000_HandShake adam5000_ctl;

	/* deltaDRV robot control-BOX handshake api */
	int read_deltaDRV_cmd(void);					/* read action commands(total) from deltaDRV */
	int read_deltaDRV_regulate(uint16_t* data);		/* read action commands(regulate) from deltaDRV */
	int read_deltaDRV_kinetrol(uint16_t* data);		/* read action commands(kinetrol) from deltaDRV */
	int read_deltaDRV_brake(uint16_t* data);		/* read action commands(brake) from deltaDRV */
	int read_deltaDRV_gripper(uint16_t* data);		/* read action commands(gripper) from deltaDRV */
	int read_deltaDRV_toolATC(uint16_t* data);		/* read action commands(toolATC) from deltaDRV */
	int read_deltaDRV_fixture(uint16_t* data);		/* read action commands(fixtrue) from deltaDRV */
	// int set_deltaDRV_cmd(void);						/* set action commands(total) to deltaDRV */
	int set_deltaDRV_item(uint16_t data);			/* set action commands(item) to deltaDRV */
	int set_deltaDRV_toolATC_check(uint16_t data);	/* set action commands(toolATC_check) to deltaDRV */
	int set_deltaDRV_ReedSwitch1(uint16_t data);	/* set action commands(ReedSwitch1) to deltaDRV */
	int set_deltaDRV_ReedSwitch2(uint16_t data);	/* set action commands(ReedSwitch2) to deltaDRV */
	int set_deltaDRV_ReedSwitch3(uint16_t data);	/* set action commands(ReedSwitch3) to deltaDRV */
	int set_deltaDRV_ReedSwitch4(uint16_t data);	/* set action commands(ReedSwitch4) to deltaDRV */
	int set_deltaDRV_kinetrol(uint16_t data);		/* set action commands(kinetrol) to deltaDRV */
	int set_deltaDRV_brake(uint16_t data);			/* set action commands(brake) to deltaDRV */
	int set_deltaDRV_gripper(uint16_t data);		/* set action commands(gripper) to deltaDRV */
	int set_deltaDRV_toolATC(uint16_t data);		/* set action commands(toolATC) to deltaDRV */
	int set_deltaDRV_fixture(uint16_t data);		/* set action commands(fixture) to deltaDRV */

	/* stand IO control module adam5000 handshake */
	int read_adma5000_cmd(void);	/* read adam5000 input state */
	int read_adam5000_noitem(uint16_t* data);		/* read no-item state from adam5000 */
	int read_adam5000_lowitem(uint16_t* data);		/* read low-item state from adam5000 */
	int read_adam5000_highitem(uint16_t* data);		/* read high-item state from adam5000 */
	int read_adam5000_toolATC_check(uint16_t* data);/* read toolATC_check state from adam5000 */
	int read_adam5000_ReedSwitch1(uint16_t* data);	/* read ReedSwitch1 state from adam5000 */
	int read_adam5000_ReedSwitch2(uint16_t* data);	/* read ReedSwitch2 state from adam5000 */
	int read_adam5000_ReedSwitch3(uint16_t* data);	/* read ReedSwitch3 state from adam5000 */
	int read_adam5000_ReedSwitch4(uint16_t* data);	/* read ReedSwitch4 state from adam5000 */
	// int set_adma5000_cmd(void);		/* set adam5000 output signal */
	int set_adam5000_kinetrolUp(uint16_t data);		/* set kinetrol_up signal to adam5000 */
	int set_adam5000_kinetrolDown(uint16_t data);	/* set kinetrol_down signal to adam5000 */
	int set_adam5000_brake(uint16_t data);			/* set brake signal to adam5000 */
	int set_adam5000_gripperOpen(uint16_t data);	/* set gripper_open signal to adam5000 */
	int set_adam5000_gripperClose(uint16_t data);	/* set gripper_close signal to adam5000 */
	int set_adam5000_security(uint16_t data);		/* set security signal to adam5000 */
	int set_adam5000_value1_lock(uint16_t data);	/* set value1_lock signal to adam5000 */
	int set_adam5000_value1_unlock(uint16_t data);	/* set value1_unlock signal to adam5000 */
	int set_adam5000_value2_lock(uint16_t data);	/* set value2_lock signal to adam5000 */
	int set_adam5000_value2_unlock(uint16_t data);	/* set value2_unlock signal to adam5000 */
	int set_adam5000_value3_lock(uint16_t data);	/* set value3_lock signal to adam5000 */
	int set_adam5000_value3_unlock(uint16_t data);	/* set value3_unlock signal to adam5000 */
	int set_adam5000_value4_lock(uint16_t data);	/* set value4_lock signal to adam5000 */
	int set_adam5000_value4_unlock(uint16_t data);	/* set value4_unlock signal to adam5000 */

/* public member */
public:
	cas_lab_StandController();	/* constructor */
	~cas_lab_StandController();	/* destructor */

	void init(void); 		  /* cas lab stand system initialization */
	int arm_M5_set_payload(uint16_t kg);
	int arm_M5_brake(bool onoff);
	int arm_M5_kinetrol(bool onoff);
	int arm_M5_toolATC(bool onoff);
	int arm_M5_fixture(bool onoff);
	stand_state run(void);	  /* main function */
	void delay_1ms(int time); /* delay function */

};

/* Extern Class End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */
/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */


#endif /*__cas_lab_StandController_HPP__ */

/* ***** END OF cas_lab_StandController.HPP ***** */
