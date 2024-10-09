/** ******************************************************
	* @file		cas_lab_safetysystem_classType.hpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __cas_lab_safetysystem_classType_HPP__
#define __cas_lab_safetysystem_classType_HPP__


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <chrono>
#include <memory>
#include <iostream>
#include <stdio.h>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "CASLab_SafetySystemDefineTable.hpp"
#include "wise4060_HandShake.hpp"
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */
/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */
/* Extern Typedef End */


/* Extern Class -------------------------------------------*/
/* Extern Class Begin */

class cas_lab_safetysystem_classType
{
/* private number */
private:
	char buffer[1024];
	FILE* pipe;
	/* for loop count */
	int flc1,flc2,flc3;
	/* StackLight Display Mode */
	int display_mode, display_mode_old,red_flash_count;
	bool display_HL_change,display_LED_change;
	bool camera_robot_AP_err,guide_robot_AP_err;
	/* current program time(us), previous program time(us) */
	int64_t STO_time_diff;
	int64_t display_time_diff;
	std::chrono::system_clock::time_point STO_time_ms;
	std::chrono::system_clock::time_point STO_time_ms_old;
	std::chrono::system_clock::time_point display_time_ms;
	std::chrono::system_clock::time_point display_time_ms_old;
	/* current program time(us), previous program time(us) */
	/* libmodbus Return Code */
	int rc;
	/* online remoteIO quantity */
	int online_remoteIO_quantity;
	/* create string data type variable for the IP address  */
	std::string ipAddress;
	/* create string data type variable for the to termanal command */
	std::string command;
	std::string debug_message;
	/* create data structure for the work status of cas lab */
	lab_state cas_lab_state, cas_lab_state_old;
	/* craeate cas lab remoteIO IP list */
	std::vector<std::string> remoteIO_IP;
	
	/* for status of each input channel */
	uint8_t DI_status[remoteIO_quantity][wise4060_input_quantity];
	/* for status of each output channel */
	uint8_t DO_status[remoteIO_quantity][wise4060_output_quantity];

	std::shared_ptr<wise4060_HandShake> remoteIO[remoteIO_quantity];
	// wise4060_HandShake *remoteIO[remoteIO_quantity];

	void get_remoteIO_DI(int number); /* get DI data of remoteIO[number] */
	void get_remoteIO_DO(int number); /* get DO data of remoteIO[number] */

	int ping_AP(std::string ip);/* ping AP ip */
	int verify_totalAP(void);	/* verify total AP */
	int verify_moduleAP(void);	/* verify module AP */
	int verify_remoteIO(void);	/* verify remoteIO */

	uint8_t check_fence_door(void);			/* check if the fence door is open */
	uint8_t check_camera_robot_EMS(void);	/* check if the camera robot EMS is pressed */
	uint8_t check_guide_robot_EMS(void);	/* check if the guide robot EMS is pressed */
	uint8_t check_stand_EMS(void);			/* check if the stand EMS is pressed */
	uint8_t check_AGV_EMS(void);			/* check if the AGV EMS is pressed */

	void CAS_LAB_action(void);			/* implement actions on the indicator lights and STO of each module */
	void action_camera_robot_STO(void);	/* STO actions based on the status of camera robot */
	void action_guide_robot_STO(void);	/* STO actions based on the status of guide robot */
	void action_stand_STO(void);		/* STO actions based on the status of stand */
	void action_AGV_STO(void);			/* STO actions based on the status of AGV */

	uint8_t STOon_camera_robot(void);	/* activate the STO mechanism of the camera robot */
	uint8_t STOoff_camera_robot(void);	/* deactivate the STO mechanism of the camera robot */
	uint8_t STOon_guide_robot(void);	/* activate the STO mechanism of the guide robot */
	uint8_t STOoff_guide_robot(void);	/* deactivate the STO mechanism of the guide robot */
	uint8_t STOon_stand(void);			/* activate the STO mechanism of the stand */
	uint8_t STOoff_stand(void);			/* deactivate the STO mechanism of the stand */
	uint8_t STOon_AGV(void);			/* activate the STO mechanism of the AGV */
	uint8_t STOoff_AGV(void);			/* deactivate the STO mechanism of the AGV */

	void set_StackLight_DisplayMode(void);	/* set StackLight Display Mode */

/* public number */
public:
	
	cas_lab_safetysystem_classType();	/* constructor */
	~cas_lab_safetysystem_classType();	/* destructor */

	/* cas lab module initialization */
	void init(void);
	/* main function */
	lab_state run(void);
	/* delay function */
	void delay_1ms(int time, bool printSW);
	/* StackLight actions based on the status of DisplayMode */
	void action_StackLight(void);
};

/* Extern Class End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */
/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */


#endif /*__cas_lab_safetysystem_classType_HPP__ */

/* ***** END OF cas_lab_safetysystem_classType.HPP ***** */
