/** ******************************************************
	* @file		cas_lab_safetysystem_classType.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "cas_lab_safetysystem_classType.hpp"
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

/** * @brief Constructor
 	* @param none
 	* @return None
**	**/
cas_lab_safetysystem_classType::cas_lab_safetysystem_classType()
{
	display_mode = 1;

	remoteIO_IP.resize(remoteIO_quantity);
	remoteIO_IP[fence] = remoteIO_IP_fence;
	remoteIO_IP[camera_robot] = remoteIO_IP_camera_root;
	remoteIO_IP[guide_robot] = remoteIO_IP_guide_root;
	remoteIO_IP[stand] = remoteIO_IP_stand;

	for(flc1=0; flc1<remoteIO_quantity; flc1++)
		remoteIO[flc1] = std::make_shared<wise4060_HandShake>(remoteIO_IP[flc1].c_str(), wise4060_port, wise4060_slave);

	std::cout << "[Create] cas_lab_safetysystem object successfully!" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl << std::endl;
}
/** * @brief destructor
 	* @param none
 	* @return None
**	**/
cas_lab_safetysystem_classType::~cas_lab_safetysystem_classType()
{

	std::cout << "[Delete] cas_lab_safetysystem object successfully!" << std::endl;
}


/** * @brief get DI data of remoteIO[number]
	* @param int number,
 	* @return none
**	**/
void cas_lab_safetysystem_classType::get_remoteIO_DI(int number)
{
		/* get fence remoteIO ALL DI */
		remoteIO[number]->wise4060_readALLDI();
		remoteIO[number]->get_DI_status(DI_status[number]);
}


/** * @brief verify totalAP is working and connected.
	* @param none
 	* @return int, verify result, 0:online, 1:disconnected
**	**/
int cas_lab_safetysystem_classType::verify_totalAP(void)
{	/* check total AP is working and connected */
	ipAddress = total_AP_IP;
	command = std::string("ping -c 1 -w 1 ") + ipAddress + std::string(" > /dev/null");
	/* check total AP is working and connected */
	if( system(command.c_str()) != 0 )
	{	/* totalAP not connected */
		std::cout << TC_ERROR << ipAddress << " is not connected" << TC_RESET << std::endl;
		cas_lab_state.network = network_total_AP_err;
		display_mode = module_network_err;
		return EXIT_FAILURE;
	}
	else
	{	/* totalAP online */
		std::cout << ipAddress << " is connected" << std::endl;
		cas_lab_state.network = network_healthy;
		return EXIT_SUCCESS;
	}
}
/** * @brief verify moduleAP is working and connected.
	* @param none
 	* @return int, number of online moduleAP
**	**/
int cas_lab_safetysystem_classType::verify_moduleAP(void)
{	
	/* undone */
	return 0;
}
/** * @brief verify remoteIO is working and connected.
	* @param none
 	* @return int, number of online remoteIOs
**	**/
int cas_lab_safetysystem_classType::verify_remoteIO(void)
{	/* check remoteIO is working and connected */
	online_remoteIO_quantity = 0;
	/* sequentially evaluate the status of all remoteIO */
	for(flc1=(remoteIO_quantity-1); flc1<=0; flc1--)
	{
		std::cout << "[verify_remoteIO]" << flc1  << " : ";
		/* check the remoteIO is online */
		rc = remoteIO[flc1]->isConnect();
		if(rc != 1)
		{	/* if disconnected, attempt to reconnect */
			std::cout << TC_ERROR << "remoteIO IP:" << remoteIO_IP[flc1].c_str() << " connection lost!" << std::endl;
			rc = remoteIO[flc1]->reConnect();
			if(rc != 0)
			{	/* reconnection failed */
				cas_lab_state.network = (static_cast<uint8_t>(flc1));
				std::cout << "    >> remoteIO IP:" << remoteIO_IP[flc1].c_str() << " reconnection failed!" << TC_RESET << std::endl;
			}
			else
			{	/* reconnection successfully */
				online_remoteIO_quantity += 1;
				std::cout << TC_RESET << "    >> remoteIO IP:" << remoteIO_IP[flc1].c_str() << " reconnection successfully!" << std::endl;
			}
		}
		else
		{	/* already online */
			online_remoteIO_quantity += 1;
			std::cout << "remoteIO IP:" << remoteIO_IP[flc1].c_str() << " still online" << std::endl;
		}
	}

	/* display remoteIO number of faulty */
	if( online_remoteIO_quantity < remoteIO_quantity )
		std::cout << TC_ERROR << "number of faulty remoteIO in the CAS lab: " \
		<< (remoteIO_quantity-online_remoteIO_quantity) << TC_RESET << std::endl;
	else
		std::cout << "CAS Lab remoteIO All functioning normally!" << TC_RESET << std::endl;
	std::cout << std::endl;

	return online_remoteIO_quantity;
}


/** * @brief check if the fence door is open.
	* @param none
 	* @return uint8_t, check result, 0:close, 1:open
**	**/
uint8_t cas_lab_safetysystem_classType::check_fence_door(void)
{
	/* get remoteIO[fence] DI data */
	get_remoteIO_DI(fence);
	/* set the status of the fence door */
	if( DI_status[fence][fence] == DI_signal_efficient )
	{	/* fence door is close */
		cas_lab_state.fence = fence_close;
		std::cout << "[check_fence_door] close" << std::endl;
		return fence_close;
	}
	else
	{	/* fence door is open */
		cas_lab_state.fence = fence_open;
		std::cout << TC_ERROR << "[check_fence_door] open!" << TC_RESET << std::endl;
		return fence_open;
	}
}
/** * @brief check if the camera robot EMS is pressed.
	* @param none
 	* @return uint8_t, check result, 0:EMSon, 1:EMSoff
**	**/
uint8_t cas_lab_safetysystem_classType::check_camera_robot_EMS(void)
{
	/* get remoteIO[fence&camera_robot] DI data */
	get_remoteIO_DI(fence);
	get_remoteIO_DI(camera_robot);
	/* set the status of the camera robot EMS */
	if( (DI_status[fence][camera_robot]==DI_EMS_off) &&
	   (DI_status[camera_robot][camera_robot]==DI_EMS_off) )
	{	/* camera robot EMS is off, normal working */
		cas_lab_state.camera_robot = camera_robot_EMS_off;
		std::cout << "[check_camera_robot] EMS_off" << std::endl;
		return camera_robot_EMS_off;
	}
	else
	{	/* camera robot EMS is on, prohibit working */
		cas_lab_state.camera_robot = camera_robot_EMS_on;
		std::cout << TC_ERROR << "[check_camera_robot] EMS_on!" << TC_RESET << std::endl;
		return camera_robot_EMS_on;
	}
}
/** * @brief check if the guide robot EMS is pressed.
	* @param none
 	* @return uint8_t, check result, 0:EMSon, 1:EMSoff
**	**/
uint8_t cas_lab_safetysystem_classType::check_guide_robot_EMS(void)
{
	/* get remoteIO[fence&guide_robot] DI data */
	get_remoteIO_DI(fence);
	get_remoteIO_DI(guide_robot);
	/* set the status of the guide robot EMS */
	if( (DI_status[fence][guide_robot]==DI_EMS_off) &&
	   (DI_status[guide_robot][guide_robot]==DI_EMS_off) )
	{	/* guide robot EMS is off, normal working */
		cas_lab_state.guide_robot = guide_robot_EMS_off;
		std::cout << "[check_guide_robot] EMS_off" << std::endl;
		return guide_robot_EMS_off;
	}
	else
	{	/* guide robot EMS is on, prohibit working */
		cas_lab_state.guide_robot = guide_robot_EMS_on;
		std::cout << TC_ERROR << "[check_guide_robot] EMS_on!" << TC_RESET << std::endl;
		return guide_robot_EMS_on;
	}
}
/** * @brief check if the stand EMS is pressed.
	* @param none
 	* @return uint8_t, check result, 0:EMSon, 1:EMSoff
**	**/
uint8_t cas_lab_safetysystem_classType::check_stand_EMS(void)
{
	/* get remoteIO[stand] DI data */
	get_remoteIO_DI(stand);
	/* set the status of the stand EMS */
	if( (DI_status[stand][stand]==DI_EMS_off) )
	{	/* stand EMS is off, normal working */
		cas_lab_state.stand = stand_EMS_off;
		std::cout << "[check_stand] EMS_off" << std::endl;
		return stand_EMS_off;
	}
	else
	{	/* stand EMS is on, prohibit working */
		cas_lab_state.stand = stand_EMS_on;
		std::cout << TC_ERROR << "[check_stand] EMS_on!" << TC_RESET << std::endl;
		return stand_EMS_on;
	}
}
/** * @brief check if the AGV EMS is pressed.
	* @param none
 	* @return uint8_t, check result, 0:EMSon, 1:EMSoff
**	**/
uint8_t cas_lab_safetysystem_classType::check_AGV_EMS(void)
{
	/* get remoteIO[fence&AGV] DI data */
	get_remoteIO_DI(fence);
	get_remoteIO_DI(camera_robot);
	get_remoteIO_DI(guide_robot);
	/* set the status of the AGV EMS */
	if( (DI_status[fence][AGV]==DI_EMS_off) &&
	   (DI_status[camera_robot][AGV]==DI_EMS_off) &&
	   (DI_status[guide_robot][AGV]==DI_EMS_off) )
	{	/* AGV EMS is off, normal working */
		cas_lab_state.AGV = AGV_EMS_off;
		std::cout << "[check_AGV] EMS_off" << std::endl;
		return AGV_EMS_off;
	}
	else
	{	/* AGV EMS is on, prohibit working */
		cas_lab_state.AGV = AGV_EMS_on;
		std::cout << TC_ERROR << "[check_AGV] EMS_on!" << TC_RESET << std::endl;
		return AGV_EMS_on;
	}
}


/** * @brief implement actions on the indicator lights and STO of each module.
	* @param none
 	* @return none
**	**/
void cas_lab_safetysystem_classType::CAS_LAB_action(void)
{
	// /* set StackLight Display Mode */
	// set_StackLight_DisplayMode();

	if( cas_lab_state.network == network_total_AP_err) 
		display_mode = module_network_err;
	else if( cas_lab_state.network == network_fence_remoteIO_err )
		display_mode = module_network_err;
	else if( cas_lab_state.fence == fence_open )
		display_mode = module_fence_err;
	else
	{
		/* STO actions based on the status of camera robot */
		action_camera_robot_STO();
		/* STO actions based on the status of guide robot */
		action_guide_robot_STO();
		/* STO actions based on the status of stand */
		action_stand_STO();
		/* STO actions based on the status of AGV */
		action_AGV_STO();
	}
}
/** * @brief STO actions based on the status of camera robot.
	* @param none
 	* @return none
**	**/
void cas_lab_safetysystem_classType::action_camera_robot_STO(void)
{
	if( cas_lab_state.fence == fence_close )
		if( cas_lab_state.network != network_camera_robot_AP_err )
		if( cas_lab_state.network != network_camera_robot_remoteIO_err )
			if( cas_lab_state.camera_robot == camera_robot_EMS_off )
				STOoff_camera_robot();
	else
	{
		display_mode = module_camera_robot_err;
		STOon_camera_robot();
	}
}
/** * @brief STO actions based on the status of guide robot.
	* @param none
 	* @return none
**	**/
void cas_lab_safetysystem_classType::action_guide_robot_STO(void)
{
	if( cas_lab_state.fence == fence_close )
		if( cas_lab_state.network != network_guide_robot_AP_err )
		if( cas_lab_state.network != network_guide_robot_remoteIO_err )
			if( cas_lab_state.guide_robot == guide_robot_EMS_off )
				STOoff_guide_robot();
	else
	{
		display_mode = module_guide_robot_err;
		STOon_guide_robot();
	}
}
/** * @brief STO actions based on the status of stand.
	* @param none
 	* @return none
**	**/
void cas_lab_safetysystem_classType::action_stand_STO(void)
{
	if( cas_lab_state.fence == fence_close )
		if( cas_lab_state.network != network_stand_AP_err)
		if( cas_lab_state.network != network_stand_remoteIO_err)
			if( cas_lab_state.stand == stand_EMS_off )
				STOoff_stand();
	else
	{
		display_mode = module_stand_err;
		STOon_stand();
	}
}
/** * @brief STO actions based on the status of AGV.
	* @param none
 	* @return none
**	**/
void cas_lab_safetysystem_classType::action_AGV_STO(void)
{
	if( cas_lab_state.fence == fence_close )
		if( cas_lab_state.network != network_camera_robot_AP_err )
		if( cas_lab_state.network != network_camera_robot_remoteIO_err )
		if( cas_lab_state.network != network_guide_robot_AP_err )
		if( cas_lab_state.network != network_guide_robot_remoteIO_err )
				if( cas_lab_state.AGV == AGV_EMS_off )
					STOoff_AGV();
	else
	{
		display_mode = module_AGV_err;
		STOon_AGV();
	}
}
/** * @brief StackLight actions based on the status of DisplayMode.
	* @param none
 	* @return none
**	**/
void cas_lab_safetysystem_classType::action_StackLight(void)
{

}

/* activate the STO mechanism of the camera robot */
uint8_t cas_lab_safetysystem_classType::STOon_camera_robot(void)
{
	rc = remoteIO[camera_robot]->wise4060_writeDO(camera_robot_STO_adr,
												  static_cast<int>(DO_STO_enable));
	return rc;
}
/* deactivate the STO mechanism of the camera robot */
uint8_t cas_lab_safetysystem_classType::STOoff_camera_robot(void)
{
	rc = remoteIO[camera_robot]->wise4060_writeDO(camera_robot_STO_adr,
												  static_cast<int>(DO_STO_disable));
	return rc;
}
/* activate the STO mechanism of the guide robot */
uint8_t cas_lab_safetysystem_classType::STOon_guide_robot(void)
{
	rc = remoteIO[guide_robot]->wise4060_writeDO(guide_robot_STO_adr,
												 static_cast<int>(DO_STO_enable));
	return rc;
}	
/* deactivate the STO mechanism of the guide robot */
uint8_t cas_lab_safetysystem_classType::STOoff_guide_robot(void)
{
	rc = remoteIO[guide_robot]->wise4060_writeDO(guide_robot_STO_adr,
												 static_cast<int>(DO_STO_disable));
	if( cas_lab_state_old.guide_robot == guide_robot_EMS_on )
		remoteIO[guide_robot]->wise4060_DO_pulse(guide_robot_reset_adr,1);
	return rc;
}	
/* activate the STO mechanism of the stand */
uint8_t cas_lab_safetysystem_classType::STOon_stand(void)
{
	rc = remoteIO[stand]->wise4060_writeDO(stand_STO_adr,
												 static_cast<int>(DO_STO_enable));
	return rc;
}			
/* deactivate the STO mechanism of the stand */
uint8_t cas_lab_safetysystem_classType::STOoff_stand(void)
{
	rc = remoteIO[stand]->wise4060_writeDO(stand_STO_adr,
												 static_cast<int>(DO_STO_disable));
	return rc;
}		
/* activate the STO mechanism of the AGV */
uint8_t cas_lab_safetysystem_classType::STOon_AGV(void)
{
	rc = remoteIO[AGV]->wise4060_writeDO(AGV_STO_adr,
												 static_cast<int>(DO_STO_enable));
	return rc;
}		
/* deactivate the STO mechanism of the AGV */
uint8_t cas_lab_safetysystem_classType::STOoff_AGV(void)
{
	rc = remoteIO[AGV]->wise4060_writeDO(AGV_STO_adr,
												 static_cast<int>(DO_STO_disable));
	return rc;
}		


/** * @brief cas_lab_safetysystem_classType main function
	* @param none
 	* @return lab_state, cas lab working state
**	**/
lab_state cas_lab_safetysystem_classType::run(void)
{
	display_mode = module_ALL_healthy;
	/* verify that totalAP is online before executing the program */
	while( verify_totalAP() == EXIT_SUCCESS )
	{
		/* verify moduleAPs is working and connected. */
		verify_moduleAP();
		/* verify remoteIOs is working and connected. */
		verify_remoteIO();

		/*  */
		if( cas_lab_state.network != network_fence_remoteIO_err )
		{
			/* check if the fence door is open */
			if( check_fence_door() == fence_close )
			{
				/* check cas lab module EMS */
				check_camera_robot_EMS();
				check_guide_robot_EMS();
				check_stand_EMS();
				check_AGV_EMS();
			}

			/* implement actions on the indicator lights and STO of each module */
			CAS_LAB_action();
		}

		display_mode_old = display_mode;
		cas_lab_state_old = cas_lab_state;
		time_us_old = time_us;
		std::cout << "-------------------------------------------------" << std::endl << std::endl;
		// std::cout << static_cast<int>(cas_lab_state.network) << std::endl;
		usleep(1000*1000);
	}

	std::cout << TC_ERROR << "CAS Lab network is down, unable to operate" << TC_RESET << std::endl;
	return cas_lab_state;
}


/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF cas_lab_safetysystem_classType.cpp ***** */
