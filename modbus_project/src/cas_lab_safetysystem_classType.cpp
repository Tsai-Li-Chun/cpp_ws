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
	display_time_us = 0;
	display_time_us_old = 0;
	display_mode = 99;
	display_mode_old = 0;

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
		// switch(number)
		// {
		// 	case 0: printf("fence       : "); break;
		// 	case 1: printf("camera_robot: "); break;
		// 	case 2: printf("guide_robot : "); break;
		// 	case 3: printf("stand       : "); break;
		// }
		// printf("%02x , %02x , %02x , %02x\n",DI_status[number][0],DI_status[number][1],DI_status[number][2],DI_status[number][3]);
}
/** * @brief get DO data of remoteIO[number]
	* @param int number,
 	* @return none
**	**/
void cas_lab_safetysystem_classType::get_remoteIO_DO(int number)
{
		/* get fence remoteIO ALL DO */
		remoteIO[number]->wise4060_readALLDO();
		remoteIO[number]->get_DO_status(DO_status[number]);
		// switch(number)
		// {
		// 	case 0: printf("fence       : "); break;
		// 	case 1: printf("camera_robot: "); break;
		// 	case 2: printf("guide_robot : "); break;
		// 	case 3: printf("stand       : "); break;
		// }
		// printf("%02x , %02x , %02x , %02x\n",DO_status[number][0],DO_status[number][1],DO_status[number][2],DO_status[number][3]);
}


/** * @brief verify totalAP is working and connected.
	* @param none
 	* @return int, verify result, 0:online, 1:disconnected
**	**/
int cas_lab_safetysystem_classType::verify_totalAP(void)
{
	debug_message.clear();
	// debug_message = "";
	/* check total AP is working and connected */
	ipAddress = total_AP_IP;
	command = std::string("ping -c 1 -w 1 ") + ipAddress + std::string(" > /dev/null");
	/* check total AP is working and connected */
	if( system(command.c_str()) != 0 )
	{	/* totalAP not connected */
		debug_message = debug_message + TC_ERROR + ipAddress + " is not connected" + TC_RESET + "\n";
		// std::cout << TC_ERROR << ipAddress << " is not connected" << TC_RESET << std::endl;
		cas_lab_state.network = network_total_AP_err;
		return EXIT_FAILURE;
	}
	else
	{	/* totalAP online */
		debug_message = debug_message + ipAddress + " is connected" + "\n";
		// std::cout << ipAddress << " is connected" << std::endl;
		cas_lab_state.network = network_healthy;
		display_mode = module_ALL_healthy;
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
	for(flc1=(remoteIO_quantity-1); flc1>=0; flc1--)
	{
		debug_message = debug_message + "[verify_remoteIO]" + std::to_string(flc1) + " : ";
		// std::cout << "[verify_remoteIO]" << flc1  << " : ";
		/* check the remoteIO is online */
		rc = remoteIO[flc1]->isConnect();
		if(rc != 1)
		{	/* if disconnected, attempt to reconnect */
			debug_message = debug_message + TC_ERROR + "remoteIO IP:" + remoteIO_IP[flc1].c_str() + " connection lost!" + "\n";
			// std::cout << TC_ERROR << "remoteIO IP:" << remoteIO_IP[flc1].c_str() << " connection lost!" << std::endl;
			rc = remoteIO[flc1]->reConnect();
			if(rc != 0)
			{	/* reconnection failed */
				cas_lab_state.network = (static_cast<uint8_t>(flc1));
				debug_message = debug_message + "    >> remoteIO IP:" + remoteIO_IP[flc1].c_str() + " reconnection failed!" + TC_RESET + "\n";
				// std::cout << "    >> remoteIO IP:" << remoteIO_IP[flc1].c_str() << " reconnection failed!" << TC_RESET << std::endl;
			}
			else
			{	/* reconnection successfully */
				online_remoteIO_quantity += 1;
				debug_message = debug_message + TC_RESET + "    >> remoteIO IP:" + remoteIO_IP[flc1].c_str() + " reconnection successfully!" + "\n";
				// std::cout << TC_RESET << "    >> remoteIO IP:" << remoteIO_IP[flc1].c_str() << " reconnection successfully!" << std::endl;
			}
		}
		else
		{	/* already online */
			online_remoteIO_quantity += 1;
			debug_message = debug_message + "remoteIO IP:" + remoteIO_IP[flc1].c_str() + " still online" + "\n";
			// std::cout << "remoteIO IP:" << remoteIO_IP[flc1].c_str() << " still online" << std::endl;
		}
	}

	/* display remoteIO number of faulty */
	if( online_remoteIO_quantity < remoteIO_quantity )
		debug_message = debug_message + TC_ERROR + "number of faulty remoteIO in the CAS lab: "\
					 + std::to_string(remoteIO_quantity-online_remoteIO_quantity) + TC_RESET + "\n\n";
		// std::cout << TC_ERROR << "number of faulty remoteIO in the CAS lab: " \
		// << (remoteIO_quantity-online_remoteIO_quantity) << TC_RESET << std::endl;
	else
		debug_message = debug_message + "CAS Lab remoteIO All functioning normally!" + TC_RESET + "\n\n";
		// std::cout << "CAS Lab remoteIO All functioning normally!" << TC_RESET << std::endl;
	// std::cout << std::endl;

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
		debug_message = debug_message + "[check_fence_door] close" + "\n";
		// std::cout << "[check_fence_door] close" << std::endl;
		return fence_close;
	}
	else
	{	/* fence door is open */
		cas_lab_state.fence = fence_open;
		debug_message = debug_message + TC_ERROR + "[check_fence_door] open!" + TC_RESET + "\n";
		// std::cout << TC_ERROR << "[check_fence_door] open!" << TC_RESET << std::endl;
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
	if( DI_status[fence][camera_robot] == DI_EMS_off )
		if( DI_status[camera_robot][camera_robot] == DI_EMS_off )
	{	/* camera robot EMS is off, normal working */
		cas_lab_state.camera_robot = camera_robot_EMS_off;
		debug_message = debug_message + "[check_camera_robot] EMS_off" + "\n";
		// std::cout << "[check_camera_robot] EMS_off" << std::endl;
		return camera_robot_EMS_off;
	}
	
	/* camera robot EMS is on, prohibit working */
	cas_lab_state.camera_robot = camera_robot_EMS_on;
	debug_message = debug_message + TC_ERROR + "[check_camera_robot] EMS_on!" + TC_RESET + "\n";
	// std::cout << TC_ERROR << "[check_camera_robot] EMS_on!" << TC_RESET << std::endl;
	return camera_robot_EMS_on;
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
	if( DI_status[fence][guide_robot] == DI_EMS_off )
		if( DI_status[guide_robot][guide_robot] == DI_EMS_off )
	{	/* guide robot EMS is off, normal working */
		cas_lab_state.guide_robot = guide_robot_EMS_off;
		debug_message = debug_message + "[check_guide_robot] EMS_off" + "\n";
		// std::cout << "[check_guide_robot] EMS_off" << std::endl;
		return guide_robot_EMS_off;
	}
	
	/* guide robot EMS is on, prohibit working */
	cas_lab_state.guide_robot = guide_robot_EMS_on;
	debug_message = debug_message + TC_ERROR + "[check_guide_robot] EMS_on!" + TC_RESET + "\n";
	// std::cout << TC_ERROR << "[check_guide_robot] EMS_on!" << TC_RESET << std::endl;
	return guide_robot_EMS_on;
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
	if( DI_status[stand][stand] == DI_EMS_off )
	{	/* stand EMS is off, normal working */
		cas_lab_state.stand = stand_EMS_off;
		debug_message = debug_message + "[check_stand] EMS_off" + "\n";
		// std::cout << "[check_stand] EMS_off" << std::endl;
		return stand_EMS_off;
	}
	
	/* stand EMS is on, prohibit working */
	cas_lab_state.stand = stand_EMS_on;
	debug_message = debug_message + TC_ERROR + "[check_stand] EMS_on!" + TC_RESET + "\n";
	// std::cout << TC_ERROR << "[check_stand] EMS_on!" << TC_RESET << std::endl;
	return stand_EMS_on;
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
	if( DI_status[fence][AGV] == DI_EMS_off )
		if( DI_status[camera_robot][AGV] == DI_EMS_off )
			if( DI_status[guide_robot][AGV] == DI_EMS_off )
	{	/* AGV EMS is off, normal working */
		cas_lab_state.AGV = AGV_EMS_off;
		debug_message = debug_message + "[check_AGV] EMS_off" + "\n";
		// std::cout << "[check_AGV] EMS_off" << std::endl;
		return AGV_EMS_off;
	}
	
	/* AGV EMS is on, prohibit working */
	cas_lab_state.AGV = AGV_EMS_on;
	debug_message = debug_message + TC_ERROR + "[check_AGV] EMS_on!" + TC_RESET + "\n";
	// std::cout << TC_ERROR << "[check_AGV] EMS_on!" << TC_RESET << std::endl;
	return AGV_EMS_on;
}


/** * @brief implement actions on the indicator lights and STO of each module.
	* @param none
 	* @return none
**	**/
void cas_lab_safetysystem_classType::CAS_LAB_action(void)
{
	/* STO actions based on the status of camera robot */
	action_camera_robot_STO();
	/* STO actions based on the status of guide robot */
	action_guide_robot_STO();
	/* STO actions based on the status of stand */
	action_stand_STO();
	/* STO actions based on the status of AGV */
	action_AGV_STO();

	/* StackLight actions based on the status of DisplayMode */
	action_StackLight();
}
/** * @brief STO actions based on the status of camera robot.
	* @param none
 	* @return none
**	**/
void cas_lab_safetysystem_classType::action_camera_robot_STO(void)
{
	debug_message = debug_message + "[action_camera_robot_STO] ";
	if( cas_lab_state.fence == fence_close )
		if( cas_lab_state.network != network_camera_robot_AP_err )
		if( cas_lab_state.network != network_camera_robot_remoteIO_err )
			if( cas_lab_state.camera_robot == camera_robot_EMS_off )
	{
		// std::cout << "[action_camera_robot_STO] STOoff_camera_robot" << std::endl;
		STOoff_camera_robot();
		return;
	}
	// std::cout << TC_ERROR << "[action_camera_robot_STO] STOon_camera_robot" << TC_RESET << std::endl;
	STOoff_camera_robot();
}
/** * @brief STO actions based on the status of guide robot.
	* @param none
 	* @return none
**	**/
void cas_lab_safetysystem_classType::action_guide_robot_STO(void)
{
	debug_message = debug_message + "[action_guide_robot_STO] ";
	if( cas_lab_state.fence == fence_close )
		if( cas_lab_state.network != network_guide_robot_AP_err )
		if( cas_lab_state.network != network_guide_robot_remoteIO_err )
			if( cas_lab_state.guide_robot == guide_robot_EMS_off )
	{
		// std::cout << "[action_guide_robot_STO] STOoff_guide_robot" << std::endl;
		STOoff_guide_robot();
		return;
	}
	// std::cout << TC_ERROR << "[action_guide_robot_STO] STOon_guide_robot" << TC_RESET << std::endl;
	STOoff_guide_robot();
}
/** * @brief STO actions based on the status of stand.
	* @param none
 	* @return none
**	**/
void cas_lab_safetysystem_classType::action_stand_STO(void)
{
	debug_message = debug_message + "[action_stand_STO] ";
	if( cas_lab_state.fence == fence_close )
		if( cas_lab_state.network != network_stand_AP_err)
		if( cas_lab_state.network != network_stand_remoteIO_err)
			if( cas_lab_state.stand == stand_EMS_off )
	{
		// std::cout << "[action_stand_STO] STOoff_stand" << std::endl;
		STOoff_stand();
		return;
	}
	// std::cout << TC_ERROR << "[action_stand_STO] STOon_stand" << TC_RESET << std::endl;
	STOoff_stand();
}
/** * @brief STO actions based on the status of AGV.
	* @param none
 	* @return none
**	**/
void cas_lab_safetysystem_classType::action_AGV_STO(void)
{
	debug_message = debug_message + "[action_AGV_STO] ";
	if( cas_lab_state.fence == fence_close )
		if( cas_lab_state.network != network_camera_robot_AP_err )
		if( cas_lab_state.network != network_camera_robot_remoteIO_err )
		if( cas_lab_state.network != network_guide_robot_AP_err )
		if( cas_lab_state.network != network_guide_robot_remoteIO_err )
				if( cas_lab_state.AGV == AGV_EMS_off )
	{
		// std::cout << "[action_AGV_STO] STOoff_AGV" << std::endl;
		STOoff_AGV();
		return;
	}

	// std::cout << TC_ERROR << "[action_AGV_STO] STOon_AGV" << TC_RESET << std::endl;
	STOoff_AGV();
}

/* activate the STO mechanism of the camera robot */
uint8_t cas_lab_safetysystem_classType::STOon_camera_robot(void)
{
	rc = remoteIO[camera_robot]->wise4060_writeDO(camera_robot_STO_adr,
												  static_cast<int>(DO_STO_enable));
	if(rc==1)	debug_message = debug_message + TC_ERROR + "STOon_camera_robot Success!" + TC_RESET + "\n";
	else	debug_message = debug_message + TC_ERROR + "STOon_camera_robot Fail!" + TC_RESET + "\n";
	return rc;
}
/* deactivate the STO mechanism of the camera robot */
uint8_t cas_lab_safetysystem_classType::STOoff_camera_robot(void)
{
	rc = remoteIO[camera_robot]->wise4060_writeDO(camera_robot_STO_adr,
												  static_cast<int>(DO_STO_disable));
	// if(rc==1)	std::cout << "STOoff_camera_robot Success!" << std::endl;
	// else	std::cout << TC_ERROR << "STOoff_camera_robot Fail!" << TC_RESET << std::endl;
	if(rc==1)	debug_message += "STOoff_camera_robot Success!\n";
	else	debug_message = debug_message + TC_ERROR + "STOoff_camera_robot Fail!" + TC_RESET + "\n";
	return rc;
}
/* activate the STO mechanism of the guide robot */
uint8_t cas_lab_safetysystem_classType::STOon_guide_robot(void)
{
	rc = remoteIO[guide_robot]->wise4060_writeDO(guide_robot_STO_adr,
												 static_cast<int>(DO_STO_enable));
	// if(rc==1)	std::cout << "STOon_guide_robot Success!" << std::endl;
	// else	std::cout << TC_ERROR << "STOon_guide_robot Fail!" << TC_RESET << std::endl;
	if(rc==1)	debug_message = debug_message + TC_ERROR + "STOon_guide_robot Success!" + TC_RESET + "\n";
	else	debug_message = debug_message + TC_ERROR + "STOon_guide_robot Fail!" + TC_RESET + "\n";
	return rc;
}	
/* deactivate the STO mechanism of the guide robot */
uint8_t cas_lab_safetysystem_classType::STOoff_guide_robot(void)
{
	rc = remoteIO[guide_robot]->wise4060_writeDO(guide_robot_STO_adr,
												 static_cast<int>(DO_STO_disable));
	if(rc==1)	debug_message += "STOoff_guide_robot EMS Success!\n";
	else	debug_message = debug_message + TC_ERROR + "STOoff_guide_robot EMS Fail!" + TC_RESET + "\n";

	if( cas_lab_state_old.guide_robot == guide_robot_EMS_on )
	{
		rc += remoteIO[guide_robot]->wise4060_DO_pulse(guide_robot_reset_adr,1);
		if(rc==2)	debug_message += "                         STOoff_guide_robot RESET Success!\n";
		else	debug_message = debug_message + "                         " + TC_ERROR + "STOoff_guide_robot RESET Fail!" + TC_RESET + "\n";
	}
	return rc;
}
/* activate the STO mechanism of the stand */
uint8_t cas_lab_safetysystem_classType::STOon_stand(void)
{
	rc = remoteIO[stand]->wise4060_writeDO(stand_STO_adr,
								 static_cast<int>(DO_STO_enable));
	// if(rc==1)	std::cout << "STOon_stand Success!" << std::endl;
	// else	std::cout << TC_ERROR << "STOon_stand Fail!" << TC_RESET << std::endl;
	if(rc==1)	debug_message = debug_message + TC_ERROR + "STOon_stand Success!" + TC_RESET + "\n";
	else	debug_message = debug_message + TC_ERROR + "STOon_stand Fail!" + TC_RESET + "\n";
	return rc;
}			
/* deactivate the STO mechanism of the stand */
uint8_t cas_lab_safetysystem_classType::STOoff_stand(void)
{
	rc = remoteIO[stand]->wise4060_writeDO(stand_STO_adr,
								 static_cast<int>(DO_STO_disable));
	// if(rc==1)	std::cout << "STOoff_stand Success!" << std::endl;
	// else	std::cout << TC_ERROR << "STOoff_stand Fail!" << TC_RESET << std::endl;
	if(rc==1)	debug_message += "STOoff_stand Success!\n";
	else	debug_message = debug_message + TC_ERROR + "STOoff_stand Fail!" + TC_RESET + "\n";
	return rc;
}		
/* activate the STO mechanism of the AGV */
uint8_t cas_lab_safetysystem_classType::STOon_AGV(void)
{
	rc = remoteIO[camera_robot]->wise4060_writeDO(AGV_STO_adr,
								 static_cast<int>(DO_STO_enable));
	rc += remoteIO[guide_robot]->wise4060_writeDO(AGV_STO_adr,
								 static_cast<int>(DO_STO_enable));
	// if(rc==2)	std::cout << "STOon_AGV Success!" << std::endl;
	// else	std::cout << TC_ERROR << "STOon_AGV Fail!" << TC_RESET << std::endl;
	if(rc==2)	debug_message = debug_message + TC_ERROR + "STOon_AGV Success!" + TC_RESET + "\n";
	else	debug_message = debug_message + TC_ERROR + "STOon_AGV Fail!" + TC_RESET + "\n";
	return rc;
}		
/* deactivate the STO mechanism of the AGV */
uint8_t cas_lab_safetysystem_classType::STOoff_AGV(void)
{
	rc = remoteIO[camera_robot]->wise4060_writeDO(AGV_STO_adr,
								 static_cast<int>(DO_STO_disable));
	rc += remoteIO[guide_robot]->wise4060_writeDO(AGV_STO_adr,
								 static_cast<int>(DO_STO_disable));
	// if(rc==2)	std::cout << "STOoff_AGV Success!" << std::endl;
	// else	std::cout << TC_ERROR << "STOoff_AGV Fail!" << TC_RESET << std::endl;
	if(rc==2)	debug_message += "STOoff_AGV Success!\n";
	else	debug_message = debug_message + TC_ERROR + "STOoff_AGV Fail!" + TC_RESET + "\n";
	return rc;
}		


/** * @brief set StackLight Display Mode.
	* @param none
 	* @return none
**	**/
void cas_lab_safetysystem_classType::set_StackLight_DisplayMode(void)
{
	for(flc1=0; flc1<remoteIO_quantity; flc1++)
	{
		get_remoteIO_DO(flc1);
		// printf("%d , %02x , %02x , %02x , %02x\n",flc1,DO_status[flc1][3],DO_status[flc1][2],DO_status[flc1][1],DO_status[flc1][0]);
		// std::cout << flc1 << ": " << DO_status[flc1][0] << " , ";
		// std::cout << DO_status[flc1][1] << " , ";
		// std::cout << DO_status[flc1][2] << " , ";
		// std::cout << DO_status[flc1][3] << " , " << std::endl;;
	}
	if( cas_lab_state.network == network_total_AP_err)
		display_mode = module_network_err;
	else if( cas_lab_state.network == network_fence_remoteIO_err )
		display_mode = module_network_err;
	else if( cas_lab_state.network == network_camera_robot_remoteIO_err )
		display_mode = module_camera_robot_err;
	else if( cas_lab_state.network == network_guide_robot_remoteIO_err )
		display_mode = module_guide_robot_err;
	else if( cas_lab_state.network == network_stand_remoteIO_err )
		display_mode = module_stand_err;
	else if( cas_lab_state.fence == fence_open )
		display_mode = module_fence_err;
	else if( cas_lab_state.camera_robot == camera_robot_EMS_on )
		display_mode = module_camera_robot_err;
	else if( cas_lab_state.guide_robot == guide_robot_EMS_on )
		display_mode = module_guide_robot_err;
	else if( cas_lab_state.stand == stand_EMS_on )
		display_mode = module_stand_err;
	else if( cas_lab_state.AGV == AGV_EMS_on )
		display_mode = module_AGV_err;
	else if( DO_status[camera_robot][camera_robot] == DI_EMS_on )
		display_mode = module_camera_robot_err;
	else if( DO_status[camera_robot][AGV] == DI_EMS_on )
		display_mode = module_AGV_err;
	else if( DO_status[guide_robot][guide_robot] == DI_EMS_on )
		display_mode = module_guide_robot_err;
	else if( DO_status[guide_robot][AGV] == DI_EMS_on )
		display_mode = module_AGV_err;
	else if( DO_status[stand][stand] == DI_EMS_on )
		display_mode = module_stand_err;
}
/** * @brief StackLight actions based on the status of DisplayMode.
	* @param none
 	* @return none
**	**/
void cas_lab_safetysystem_classType::action_StackLight(void)
{
	/* set StackLight Display Mode */
	set_StackLight_DisplayMode();
	/* get system time and convert to microseconds */
	gettimeofday(&tv, NULL);
	display_time_us = ((tv.tv_sec*1000000)+tv.tv_usec);
	/* flashing actions based on the status of display_mode */
	if( display_mode >= module_camera_robot_err )
	if( display_mode <= module_AGV_err )
		if( display_mode != display_mode_old )
	{
		red_flash_count = display_mode*2;
		display_HL_change = true;
		display_LED_change = false;
		display_time_us_old = display_time_us;
		display_mode_old = display_mode;
	}

	if( (display_time_us-display_time_us_old)>flash_interval )
	{
		// std::cout << "display_HL_change reverse" << std::endl;
		display_HL_change = (!display_HL_change);
		if( red_flash_count<=0 )	
		{
			// std::cout << "display_LED_change reset" << std::endl;
			display_LED_change = (!display_LED_change);
			if(display_LED_change)
				red_flash_count=2;
			if(!display_LED_change)
				red_flash_count=display_mode*2;
		}
	}

	if( display_mode == module_ALL_healthy )
	{	/* if safetysystem is healthy, not error */
		remoteIO[fence]->wise4060_writeDO(fence_GLED_adr,1);
		remoteIO[fence]->wise4060_writeDO(fence_YLED_adr,0);
		remoteIO[fence]->wise4060_writeDO(fence_RLED_adr,0);
	}
	else if(display_mode == module_fence_err)
	{	/* if fence door open or totalEMS on */
		if( display_HL_change == false )
		{
			std::cout << "display_mode == module_fence_err LED LOW" << std::endl;
			remoteIO[fence]->wise4060_writeDO(fence_GLED_adr,0);
			remoteIO[fence]->wise4060_writeDO(fence_YLED_adr,0);
			remoteIO[fence]->wise4060_writeDO(fence_RLED_adr,0);
		}
		else
		{
			std::cout << "display_mode == module_fence_err LED HIGH" << std::endl;
			remoteIO[fence]->wise4060_writeDO(fence_GLED_adr,1);
			remoteIO[fence]->wise4060_writeDO(fence_YLED_adr,1);
			remoteIO[fence]->wise4060_writeDO(fence_RLED_adr,1);
		}
		// remoteIO[fence]->wise4060_writeDO(fence_GLED_adr,static_cast<int>(display_HL_change));
		// remoteIO[fence]->wise4060_writeDO(fence_YLED_adr,static_cast<int>(display_HL_change));
		// remoteIO[fence]->wise4060_writeDO(fence_RLED_adr,static_cast<int>(display_HL_change));
	}
	else
	{
		remoteIO[fence]->wise4060_writeDO(fence_GLED_adr,0);
		if( display_LED_change == false )
		{	/* Red LED */
			remoteIO[fence]->wise4060_writeDO(fence_YLED_adr,0);
			if( display_HL_change == false )
				remoteIO[fence]->wise4060_writeDO(fence_RLED_adr,0);
			else
				remoteIO[fence]->wise4060_writeDO(fence_RLED_adr,1);
		}
		else
		{	/* Yellow LED */
			remoteIO[fence]->wise4060_writeDO(fence_RLED_adr,0);
			if( display_HL_change == false )
				remoteIO[fence]->wise4060_writeDO(fence_YLED_adr,0);
			else
				remoteIO[fence]->wise4060_writeDO(fence_YLED_adr,1);
		}
		red_flash_count--;
	}
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

		/* check cas lab EMS status */
		if( cas_lab_state.network != network_fence_remoteIO_err )
		{	/* check if the fence door is open */
			if( check_fence_door() == fence_close )
			{	/* check cas lab module EMS */
				check_camera_robot_EMS();
				check_guide_robot_EMS();
				check_stand_EMS();
				check_AGV_EMS();
			}
			/* implement actions on the indicator lights and STO of each module */
			CAS_LAB_action();
		}

		cas_lab_state_old = cas_lab_state;
		std_cout();
		std_cout_close();
		delay_1ms(1);	/* delay 1ms */
	}
	// std_cout();
	std::cout << TC_ERROR << "CAS Lab network is down, unable to operate" << TC_RESET << std::endl;
	return cas_lab_state;
}
/** * @brief cas lab module initialization
	* @param none
 	* @return none
**	**/
void cas_lab_safetysystem_classType::init(void)
{
	delay_1ms(1000);
	debug_message.clear();
	// debug_message = "";

	STOon_camera_robot();
	STOon_guide_robot();
	STOon_stand();
	STOon_AGV();
	cas_lab_state_old.guide_robot = guide_robot_EMS_on;
	delay_1ms(1000);
	STOoff_camera_robot();
	STOoff_guide_robot();
	STOoff_stand();
	STOoff_AGV();
	delay_1ms(1000);
	gettimeofday(&tv, NULL);
	
	display_time_us=0;
	TC_close_time_us_old = ((tv.tv_sec*1000000)+tv.tv_usec);
	display_time_us_old = TC_close_time_us_old;
	delay_time_us_old = TC_close_time_us_old;
	display_mode=module_fence_err; display_mode_old=0;

	std::cout << debug_message.c_str();
	debug_message.clear();
	// debug_message = "";

	std::cout << "    >>> cas_lab_SafetySystem controller initialization completed!" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl << std::endl;
	delay_1ms(3000);
}


void cas_lab_safetysystem_classType::delay_1ms(int time)
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


void cas_lab_safetysystem_classType::std_cout(void)
{
	debug_message += "cas_lab_state.network      : ";
	// std::cout << "cas_lab_state.network      : ";
	switch(cas_lab_state.network)
	{
		case 0: debug_message += "network_fence_remoteIO_err\n"; break;
		// case 0: std::cout << "network_fence_remoteIO_err" << std::endl; break;
		case 1: debug_message += "network_camera_robot_remoteIO_err\n"; break;
		// case 1: std::cout << "network_camera_robot_remoteIO_err" << std::endl; break;
		case 2: debug_message += "network_guide_robot_remoteIO_err\n"; break;
		// case 2: std::cout << "network_guide_robot_remoteIO_err" << std::endl; break;
		case 3: debug_message += "network_stand_remoteIO_err\n"; break;
		// case 3: std::cout << "network_stand_remoteIO_err" << std::endl; break;
		case 4: debug_message += "network_total_AP_err\n"; break;
		// case 4: std::cout << "network_total_AP_err" << std::endl; break;
		case 5: debug_message += "network_camera_robot_AP_err\n"; break;
		// case 5: std::cout << "network_camera_robot_AP_err" << std::endl; break;
		case 6: debug_message += "network_guide_robot_AP_err\n"; break;
		// case 6: std::cout << "network_guide_robot_AP_err" << std::endl; break;
		case 7: debug_message += "network_stand_AP_err\n"; break;
		// case 7: std::cout << "network_stand_AP_err" << std::endl; break;
		case 99:debug_message += "network_healthy\n"; break;
		// case 99:std::cout << "network_healthy" << std::endl; break;
		default:debug_message += "not network state\n"; break;
		// default:std::cout << "not network state" << std::endl; break;
	}
	debug_message += "cas_lab_state.fence        : ";
	// std::cout << "cas_lab_state.fence        : ";
	switch(cas_lab_state.fence)
	{
		case 0: debug_message += "fence_close\n"; break;
		// case 0: std::cout << "fence_close" << std::endl; break;
		case 1: debug_message += "fence_open\n"; break;
		// case 1: std::cout << "fence_open" << std::endl; break;
		default:debug_message += "not fence state\n"; break;
		// default:std::cout << "not fence state" << std::endl; break;
	}
	debug_message += "cas_lab_state.camera_robot : ";
	// std::cout << "cas_lab_state.camera_robot : ";
	switch(cas_lab_state.camera_robot)
	{
		case 0: debug_message += "camera_robot_EMS_off\n"; break;
		// case 0: std::cout << "camera_robot_EMS_off" << std::endl; break;
		case 1: debug_message += "camera_robot_EMS_on\n"; break;
		// case 1: std::cout << "camera_robot_EMS_on" << std::endl; break;
		default:debug_message += "not camera_robot state\n"; break;
		// default:std::cout << "not camera_robot state" << std::endl; break;
	}
	debug_message += "cas_lab_state.guide_robot  : ";
	// std::cout << "cas_lab_state.guide_robot  : ";
	switch(cas_lab_state.guide_robot)
	{
		case 0: debug_message += "guide_robot_EMS_off\n"; break;
		// case 0: std::cout << "guide_robot_EMS_off" << std::endl; break;
		case 1: debug_message += "guide_robot_EMS_on\n"; break;
		// case 1: std::cout << "guide_robot_EMS_on" << std::endl; break;
		default:debug_message += "not guide_robot state\n"; break;
		// default:std::cout << "not guide_robot state" << std::endl; break;
	}
	debug_message += "cas_lab_state.stand        : ";
	// std::cout << "cas_lab_state.stand        : ";
	switch(cas_lab_state.stand)
	{
		case 0: debug_message += "stand_EMS_off\n"; break;
		// case 0: std::cout << "stand_EMS_off" << std::endl; break;
		case 1: debug_message += "stand_EMS_on\n"; break;
		// case 1: std::cout << "stand_EMS_on" << std::endl; break;
		default:debug_message += "not stand state\n"; break;
		// default:std::cout << "not stand state" << std::endl; break;
	}
	debug_message += "cas_lab_state.AGV          : ";
	// std::cout << "cas_lab_state.AGV          : ";
	switch(cas_lab_state.AGV)
	{
		case 0: debug_message += "AGV_EMS_off\n"; break;
		// case 0: std::cout << "AGV_EMS_off" << std::endl; break;
		case 1: debug_message += "AGV_EMS_on\n"; break;
		// case 1: std::cout << "AGV_EMS_on" << std::endl; break;
		default:debug_message += "not AGV state\n"; break;
		// default:std::cout << "not AGV state" << std::endl; break;
	}
	debug_message += "display_mode : ";
	// std::cout << "display_mode : ";
	switch(display_mode)
	{
		case 1: debug_message += "module_camera_robot_err\n"; break;
		// case 1: std::cout << "module_camera_robot_err" << std::endl; break;
		case 2: debug_message += "module_guide_robot_err\n"; break;
		// case 2: std::cout << "module_guide_robot_err" << std::endl; break;
		case 3: debug_message += "module_stand_err\n"; break;
		// case 3: std::cout << "module_stand_err" << std::endl; break;
		case 4: debug_message += "module_AGV_err\n"; break;
		// case 4: std::cout << "module_AGV_err" << std::endl; break;
		case 5: debug_message += "module_ALL_healthy\n"; break;
		// case 5: std::cout << "module_ALL_healthy" << std::endl; break;
		case 6: debug_message += "module_network_err\n"; break;
		// case 6: std::cout << "module_network_err" << std::endl; break;
		case 7: debug_message += "module_fence_err\n"; break;
		// case 7: std::cout << "module_fence_err" << std::endl; break;
		default:debug_message += "not display_mode state\n"; break;
		// default:std::cout << "not display_mode state" << std::endl; break;
	}
	debug_message = debug_message + "-------------------------------------------------\n\n";
	// std::cout << "-------------------------------------------------" << std::endl << std::endl;
}
void cas_lab_safetysystem_classType::std_cout_close(void)
{
	gettimeofday(&tv, NULL);
	TC_close_time_us = ((tv.tv_sec*1000000)+tv.tv_usec);
	if( (TC_close_time_us-TC_close_time_us_old) > (1000*1000) )
	{
		std::cout << TC_CLOSE << (TC_close_time_us-TC_close_time_us_old) << "\n" << debug_message.c_str() << std::endl;
		// std::cout << TC_CLOSE << debug_message.c_str();
		TC_close_time_us_old = TC_close_time_us;
	}
	// else
	// 	std::cout << TC_CLOSE << debug_message.c_str();
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF cas_lab_safetysystem_classType.cpp ***** */
