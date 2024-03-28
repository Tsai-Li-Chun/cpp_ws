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
	int i,gripper_number;
	/* define return code */
	int rc;
	/* define variable used for delay time */
	struct timeval tv;
	long delay_time_us_old,delay_time_us,delay_count,delay_count_old;
	/* create deltaDRV-BOX control object */
	deltaDRV_modbus_HandShake deltaDRV_ctl;
	/* create remotIO(ADAM5000) control object  */
	ADAM5000_HandShake adam5000_ctl;
	/* action flag */
	bool action_regulate,action_kinetrol,action_gripper,action_brake,action_toolATC,action_fixture;
	/* robot action information */
	uint16_t robot_info_regulate_kg ,robot_info_item 	,robot_info_toolATC_check ,\
			 robot_info_RS1 	 ,robot_info_RS2 	,robot_info_RS3 , robot_info_RS4 ,\
			 robot_info_kinetrol ,robot_info_brake	,robot_info_gripper ,robot_cmd ,\
			 robot_info_kinetrol_old ,robot_info_brake_old	,robot_info_gripper_old ,\
			 robot_info_toolATC  ,robot_info_fixture ,\
			 robot_info_toolATC_old  ,robot_info_fixture_old ,robot_info_regulate_kg_old;
	/* arm M5 action information - digital */
	uint8_t  armM5_info_RS1			,armM5_info_RS2		 	  ,armM5_info_RS3 	  		,armM5_info_RS4 ,\
			 armM5_info_noitem		,armM5_info_lowitem	 	  ,armM5_info_highitem 		,\
			 armM5_info_brake		,armM5_info_security 	  ,armM5_info_toolATC_check ,\
			 armM5_info_kinetrolUP	,armM5_info_kinetrolDOWN  ,\
			 armM5_info_gripperOPEN	,armM5_info_gripperCLOSE  ,\
			 armM5_info_value1_lock ,armM5_info_value1_unlock ,\
			 armM5_info_value2_lock ,armM5_info_value2_unlock ,\
			 armM5_info_value3_lock ,armM5_info_value3_unlock ,\
			 armM5_info_value4_lock ,armM5_info_value4_unlock;
	/* arm M5 action information - analogy */
	uint16_t  armM5_info_regulate;
	float  armM5_info_regulate_float;
	float regulate_kg2bar;
	// const float regulate_bar2v = 0.83333;
	// const float regulate_v2bin = 409.6;
	const float regulate_bar2bin = 341.333;
	const float regulate_kg2bar_a=(-0.374);
	const float regulate_kg2bar_b=0.124;

	/* deltaDRV robot control-BOX handshake api */
	int read_deltaDRV_total(void);					/* read action commands(total) from deltaDRV */
	int read_deltaDRV_cmd(robot_adr adr, uint16_t* data);
	int set_deltaDRV_total(void);						/* set action commands(total) to deltaDRV */


	/* stand IO control module adam5000 handshake */
	int read_adam5000_total(void);	/* read adam5000 input state */
	int read_adam5000_cmd(stand_adr_in ch, uint8_t* data);
	int set_adam5000_total(void);		/* set adam5000 output signal */
	int set_adam5000_cmd(stand_adr_out ch, uint8_t data);
	int set_adam5000_cmd(stand_adr_out ch, uint16_t data);

	bool check_robot_cmd(void);		/* check robot cmd */
	void check_action(void);		/* robot modbus data processing */
	void action_stand(void);		/* stand IO action execution */
	void adaminfo2robotinfo(void);	/* adam information to robot handshake information */

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
	void run(void);	  /* main function */
	void delay_1ms(int time); /* delay function */

		int set_deltaDRV_cmd(robot_adr adr, uint16_t data);

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
