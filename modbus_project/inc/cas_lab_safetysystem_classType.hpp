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
#include <memory>
#include <iostream>
#include <unistd.h>
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
	/* for loop count */
	int flc1,flc2,flc3;
	/* libmodbus Return Code */
	int rc;
	// /* online remoteIO quantity */
	// int online_remoteIO_quantity;
	/* create string data type variable for the IP address  */
	std::string ipAddress;
	/* create string data type variable for the to termanal command */
	std::string command;
	/* create data structure for the work status of cas lab */
	lab_state cas_lab_state;
	/* craeate cas lab remoteIO IP list */
	std::vector<std::string> remoteIO_IP;

	std::shared_ptr<wise4060_HandShake> remoteIO[remoteIO_quantity];
	// wise4060_HandShake *remoteIO[remoteIO_quantity];

	int verify_totalAP(void);	/* verify total AP */
	int verify_moduleAP(void);	/* verify module AP */
	int verify_remoteIO(void);	/* verify remoteIO */

/* public number */
public:
	
	cas_lab_safetysystem_classType();	/* constructor */
	~cas_lab_safetysystem_classType();	/* destructor */

	int check_fence_door(void);		/* check if the fence door is open  */
	int check_camera_robot_EMS(void);	/* Check if the camera robot EMS is pressed  */
	int check_guide_robot_EMS(void);	/* Check if the guide robot EMS is pressed  */
	int check_AGV_EMS(void);			/* Check if the AGV EMS is pressed  */

	/* main function */
	lab_state run(void);

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
