/** ******************************************************
	* @file		cas_lab_safetysystem_classType.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <string>
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
	display_mode = 99;
	display_mode_old = 0;

	remoteIO_IP.resize(remoteIO_quantity);
	remoteIO_IP[fence] = remoteIO_IP_fence;
	remoteIO_IP[camera_robot] = remoteIO_IP_camera_root;
	remoteIO_IP[guide_robot] = remoteIO_IP_guide_root;
	// remoteIO_IP[stand] = remoteIO_IP_stand;

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

/** * @brief use ping to check if the target system is up and running.
	* @param string(ip), target ip
 	* @return int, verify result, 0:running, 1:showdown
**	**/
int cas_lab_safetysystem_classType::ping_AP(std::string ip)
{
// 	STO_time_ms = std::chrono::system_clock::now();
// 	command = std::string("ping -n 1 -w 10 ") + ip;
// #if defined(__OS_LINUX__)
// 	pipe = popen(command.c_str(), "r");
// #elif defined(__OS_WIN__)
// 	pipe = _popen(command.c_str(), "r");
// #endif
// 	if(pipe == NULL)
// 	{
// 		std::cout << TC_ERROR << ip << " _popen Fail!\n" << TC_RESET;
// 		exit(1);
// 	}
// 	while(fgets(buffer,1024,pipe)!=NULL);
// #if defined(__OS_LINUX__)
// 	pclose(pipe);
// #elif defined(__OS_WIN__)
// 	_pclose(pipe);
// #endif
// 	command = std::string(buffer);
// 	// if( command.find("ms")==command.npos )	return 1;

// 	// flc3=0; rc=0;
// 	// while( (flc3=command.find("ms",flc3)) != command.npos )
// 	// { flc3++; rc++; }
// 	// if(rc!=3)
// 	// 	return 1;
	
// 	STO_time_diff = std::chrono::duration_cast<std::chrono::milliseconds>(STO_time_ms - STO_time_ms_old).count();
// 	std::cout << "ping " << command << ": " << STO_time_diff << "\n";
	return 0;
}

/** * @brief verify totalAP is working and connected.
	* @param none
 	* @return int, verify result, 0:online, 1:disconnected
**	**/
int cas_lab_safetysystem_classType::verify_totalAP(void)
{
	debug_message.clear();
	debug_message = "";
	cas_lab_state_old = cas_lab_state;
	// debug_message = "";

	// ipAddress = camera_robot_AP_IP;
	// camera_robot_AP_err = ping_AP(ipAddress);
	// // if(camera_robot_AP_err)
	// // 	std::cout << TC_ERROR << "camera_robot system not running!" << TC_RESET << std::endl;
	// ipAddress = guide_robot_AP_IP;
	// guide_robot_AP_err = ping_AP(ipAddress);
	// // if(guide_robot_AP_err)
	// // 	std::cout << TC_ERROR << "guide_robot system not running!" << TC_RESET << std::endl;

	/* check total AP is working and connected */
	ipAddress = total_AP_IP;
	rc = ping_AP(ipAddress);
	if( rc!=0 )
	{	/* totalAP not connected */
		// debug_message = debug_message + TC_ERROR + ipAddress + " is not connected" + TC_RESET + "\n";
		std::cout << TC_ERROR << ipAddress << " is not connected\n" << TC_RESET;
		cas_lab_state.network = network_total_AP_err;
		display_mode = module_network_err;
		return EXIT_FAILURE;
	}
	else
	{	/* totalAP online */
		// debug_message = debug_message + ipAddress + " is connected" + "\n";
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
		// debug_message = debug_message + "[verify_remoteIO]" + std::to_string(flc1) + " : ";
		// std::cout << "[verify_remoteIO]" << flc1  << " : ";
		/* check the remoteIO is online */
		if(flc1!=1)
		{
			rc = remoteIO[flc1]->isConnect();
			if(rc != 1)
			{	/* if disconnected, attempt to reconnect */
				// debug_message = debug_message + TC_ERROR + "remoteIO IP:" + remoteIO_IP[flc1].c_str() + " connection lost!" + "\n";
				// std::cout << TC_ERROR << "remoteIO IP:" << remoteIO_IP[flc1].c_str() << " connection lost!" << std::endl;
				rc = remoteIO[flc1]->reConnect();
				if(rc != 0)
				{	/* reconnection failed */
					cas_lab_state.network = (static_cast<uint8_t>(flc1));
					if( flc1==0 )
					{
						display_mode = module_network_err;
						std::cout << TC_ERROR << remoteIO_IP[flc1].c_str() << " reconnection failed!\n" << TC_RESET;
					}
					if( flc1==1 && !camera_robot_AP_err )
					{
						display_mode = module_network_err;
						std::cout << TC_ERROR << remoteIO_IP[flc1].c_str() << " reconnection failed!\n" << TC_RESET;
					}
					if( flc1==2 && !guide_robot_AP_err )
					{
						display_mode = module_network_err;
						std::cout << TC_ERROR << remoteIO_IP[flc1].c_str() << " reconnection failed!\n" << TC_RESET;
					}
				}
				else
				{	/* reconnection successfully */
					online_remoteIO_quantity += 1;
					// debug_message = debug_message + TC_RESET + "    >> remoteIO IP:" + remoteIO_IP[flc1].c_str() + " reconnection successfully!" + "\n";
					// std::cout << TC_RESET << "    >> remoteIO IP:" << remoteIO_IP[flc1].c_str() << " reconnection successfully!" << std::endl;
				}
			}
			else
			{	/* already online */
				online_remoteIO_quantity += 1;
				// debug_message = debug_message + "remoteIO IP:" + remoteIO_IP[flc1].c_str() + " still online" + "\n";
				// std::cout << "remoteIO IP:" << remoteIO_IP[flc1].c_str() << " still online" << std::endl;
			}
		}
	}

	// /* display remoteIO number of faulty */
	// if( online_remoteIO_quantity < remoteIO_quantity )
	// 	debug_message = debug_message + TC_ERROR + "number of faulty remoteIO in the CAS lab: "\
	// 				 + std::to_string(remoteIO_quantity-online_remoteIO_quantity) + TC_RESET + "\n\n";
	// 	// std::cout << TC_ERROR << "number of faulty remoteIO in the CAS lab: " \
	// 	// << (remoteIO_quantity-online_remoteIO_quantity) << TC_RESET << std::endl;
	// else
	// 	debug_message = debug_message + "CAS Lab remoteIO All functioning normally!" + TC_RESET + "\n\n";
	// 	// std::cout << "CAS Lab remoteIO All functioning normally!" << TC_RESET << std::endl;
	// // std::cout << std::endl;

	return online_remoteIO_quantity;
}


/** * @brief check if the fence door is open.
	* @param none
 	* @return uint8_t, check result, 0:close, 1:open
**	**/
uint8_t cas_lab_safetysystem_classType::check_fence_door(void)
{
	/* get remoteIO[fence] DI data */
	// get_remoteIO_DI(fence);
	/* set the status of the fence door */
	if( DI_status[fence][fence] == DI_signal_efficient )
	{	/* fence door is close */
		cas_lab_state.fence = fence_close;
		// debug_message = debug_message + "[check_fence_door] close" + "\n";
		// std::cout << "[check_fence_door] close" << std::endl;
		return fence_close;
	}
	else
	{	/* fence door is open */
		cas_lab_state.fence = fence_open;
		display_mode = module_fence_err;
		// debug_message = debug_message + TC_ERROR + "[check_fence_door] open!" + TC_RESET + "\n";
		std::cout << TC_ERROR << "[check_fence_door] open!\n" << TC_RESET;
		return fence_open;
	}
}
/** * @brief check if the camera robot EMS is pressed.
	* @param none
 	* @return uint8_t, check result, 0:EMSon, 1:EMSoff
**	**/
uint8_t cas_lab_safetysystem_classType::check_camera_robot_EMS(void)
{
	/* check camera AP is working and connected */
	// ipAddress = camera_robot_AP_IP;
	// rc = ping_AP(ipAddress);
	if( camera_robot_AP_err!=0 )
	{
		std::cout << TC_ERROR << "camera_robot system not running!\n" << TC_RESET;
		cas_lab_state.camera_robot = camera_robot_EMS_off;
		return camera_robot_EMS_off;
	}
	else
	{
		/* set the status of the camera robot EMS */
		if( DI_status[fence][camera_robot] == DI_EMS_off )
			if( DI_status[camera_robot][camera_robot] == DI_EMS_off )
		{	/* camera robot EMS is off, normal working */
			cas_lab_state.camera_robot = camera_robot_EMS_off;
			// debug_message = debug_message + "[check_camera_robot] EMS_off" + "\n";
			// std::cout << "[check_camera_robot] EMS_off" << std::endl;
			return camera_robot_EMS_off;
		}
		
		/* camera robot EMS is on, prohibit working */
		cas_lab_state.camera_robot = camera_robot_EMS_on;
		display_mode = module_camera_robot_err;
		// debug_message = debug_message + TC_ERROR + "[check_camera_robot] EMS_on!" + TC_RESET + "\n";
		std::cout << TC_ERROR << "[check_camera_robot] EMS_on!\n" << TC_RESET;
		return camera_robot_EMS_on;
	}
}
/** * @brief check if the guide robot EMS is pressed.
	* @param none
 	* @return uint8_t, check result, 0:EMSon, 1:EMSoff
**	**/
uint8_t cas_lab_safetysystem_classType::check_guide_robot_EMS(void)
{
	/* check guide AP is working and connected */
	// ipAddress = guide_robot_AP_IP;
	// rc = ping_AP(ipAddress);
	if( guide_robot_AP_err!=0 )
	{
		std::cout << TC_ERROR << "guide_robot system not running!\n" << TC_RESET;
		cas_lab_state.guide_robot = guide_robot_EMS_off;
		return camera_robot_EMS_off;
	}
	else
	{
		/* set the status of the guide robot EMS */
		if( DI_status[fence][guide_robot] == DI_EMS_off )
			if( DI_status[guide_robot][guide_robot] == DI_EMS_off )
		{	/* guide robot EMS is off, normal working */
			cas_lab_state.guide_robot = guide_robot_EMS_off;
			// debug_message = debug_message + "[check_guide_robot] EMS_off" + "\n";
			// std::cout << "[check_guide_robot] EMS_off" << std::endl;
			return guide_robot_EMS_off;
		}
		
		/* guide robot EMS is on, prohibit working */
		cas_lab_state.guide_robot = guide_robot_EMS_on;
		display_mode = module_guide_robot_err;
		// debug_message = debug_message + TC_ERROR + "[check_guide_robot] EMS_on!" + TC_RESET + "\n";
		std::cout << TC_ERROR << "[check_guide_robot] EMS_on!\n" << TC_RESET;
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
	if( DI_status[stand][stand] == DI_EMS_off )
	{	/* stand EMS is off, normal working */
		cas_lab_state.stand = stand_EMS_off;
		// debug_message = debug_message + "[check_stand] EMS_off" + "\n";
		// std::cout << "[check_stand] EMS_off" << std::endl;
		return stand_EMS_off;
	}
	
	/* stand EMS is on, prohibit working */
	cas_lab_state.stand = stand_EMS_on;
	display_mode = module_stand_err;
	// debug_message = debug_message + TC_ERROR + "[check_stand] EMS_on!" + TC_RESET + "\n";
	std::cout << TC_ERROR << "[check_stand] EMS_on!\n" << TC_RESET;
	return stand_EMS_on;
}
/** * @brief check if the AGV EMS is pressed.
	* @param none
 	* @return uint8_t, check result, 0:EMSon, 1:EMSoff
**	**/
uint8_t cas_lab_safetysystem_classType::check_AGV_EMS(void)
{
	/* get remoteIO[fence&AGV] DI data */
	// get_remoteIO_DI(fence);
	// get_remoteIO_DI(camera_robot);
	// get_remoteIO_DI(guide_robot);
	/* set the status of the AGV EMS */
	if( DI_status[fence][AGV] == DI_EMS_off )
		if( DI_status[camera_robot][AGV] == DI_EMS_off )
			if( DI_status[guide_robot][AGV] == DI_EMS_off )
	{	/* AGV EMS is off, normal working */
		cas_lab_state.AGV = AGV_EMS_off;
		// debug_message = debug_message + "[check_AGV] EMS_off" + "\n";
		// std::cout << "[check_AGV] EMS_off" << std::endl;
		return AGV_EMS_off;
	}
	
	/* AGV EMS is on, prohibit working */
	cas_lab_state.AGV = AGV_EMS_on;
	display_mode = module_AGV_err;
	// debug_message = debug_message + TC_ERROR + "[check_AGV] EMS_on!" + TC_RESET + "\n";
	std::cout << TC_ERROR << "[check_AGV] EMS_on!\n" << TC_RESET;
	return AGV_EMS_on;
}


/** * @brief implement actions on the indicator lights and STO of each module.
	* @param none
 	* @return none
**	**/
void cas_lab_safetysystem_classType::CAS_LAB_action(void)
{
	/* STO actions based on the status of camera robot */
	// action_camera_robot_STO();
	/* STO actions based on the status of guide robot */
	action_guide_robot_STO();
	/* STO actions based on the status of stand */
	// action_stand_STO();
	/* STO actions based on the status of AGV */
	// action_AGV_STO();

	/* StackLight actions based on the status of DisplayMode */
	// action_StackLight();
}
/** * @brief STO actions based on the status of camera robot.
	* @param none
 	* @return none
**	**/
void cas_lab_safetysystem_classType::action_camera_robot_STO(void)
{
	// debug_message = debug_message + "[action_camera_robot_STO] ";
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
	STOon_camera_robot();
}
/** * @brief STO actions based on the status of guide robot.
	* @param none
 	* @return none
**	**/
void cas_lab_safetysystem_classType::action_guide_robot_STO(void)
{
	// debug_message = debug_message + "[action_guide_robot_STO] ";
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
	STOon_guide_robot();
}
/** * @brief STO actions based on the status of stand.
	* @param none
 	* @return none
**	**/
void cas_lab_safetysystem_classType::action_stand_STO(void)
{
	// debug_message = debug_message + "[action_stand_STO] ";
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
	STOon_stand();
}
/** * @brief STO actions based on the status of AGV.
	* @param none
 	* @return none
**	**/
void cas_lab_safetysystem_classType::action_AGV_STO(void)
{
	// debug_message = debug_message + "[action_AGV_STO] ";
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
	STOon_AGV();
}

/* activate the STO mechanism of the camera robot */
uint8_t cas_lab_safetysystem_classType::STOon_camera_robot(void)
{
	rc = remoteIO[camera_robot]->wise4060_writeDO(camera_robot_STO_adr,
												  static_cast<int>(DO_STO_enable));
	// if(rc==1)	debug_message = debug_message + TC_ERROR + "STOon_camera_robot Success!" + TC_RESET + "\n";
	// else	debug_message = debug_message + TC_ERROR + "STOon_camera_robot Fail!" + TC_RESET + "\n";
	if(rc==1)	std::cout << TC_ERROR << "STOon_camera_robot Success!\n" << TC_RESET;
	else		std::cout << TC_ERROR << "STOon_camera_robot Fail!\n" << TC_RESET;
	// if(rc!=1) debug_message = debug_message + TC_ERROR + "STOon_camera_robot Fail!" + TC_RESET + "\n";
	return rc;
}
/* deactivate the STO mechanism of the camera robot */
uint8_t cas_lab_safetysystem_classType::STOoff_camera_robot(void)
{
	rc = remoteIO[camera_robot]->wise4060_writeDO(camera_robot_STO_adr,
												  static_cast<int>(DO_STO_disable));
	// if(rc==1)	debug_message += "STOoff_camera_robot Success!\n";
	// else	debug_message = debug_message + TC_ERROR + "STOoff_camera_robot Fail!" + TC_RESET + "\n";
	// if(rc!=1) debug_message = debug_message + TC_ERROR + "STOoff_camera_robot Fail!" + TC_RESET + "\n";
	if(rc!=1) std::cout << TC_ERROR << "STOoff_camera_robot Fail!\n" << TC_RESET;
	return rc;
}
/* activate the STO mechanism of the guide robot */
uint8_t cas_lab_safetysystem_classType::STOon_guide_robot(void)
{
	rc = remoteIO[guide_robot]->wise4060_writeDO(guide_robot_STO_adr,
												 static_cast<int>(DO_STO_enable));
	// if(rc==1)	debug_message = debug_message + TC_ERROR + "STOon_guide_robot Success!" + TC_RESET + "\n";
	// else	debug_message = debug_message + TC_ERROR + "STOon_guide_robot Fail!" + TC_RESET + "\n";
	if(rc==1)	std::cout << TC_ERROR << "STOon_guide_robot Success!\n" << TC_RESET;
	else		std::cout << TC_ERROR << "STOon_guide_robot Fail!\n" << TC_RESET;
	// if(rc!=1) debug_message = debug_message + TC_ERROR + "STOon_guide_robot Fail!" + TC_RESET + "\n";
	return rc;
}	
/* deactivate the STO mechanism of the guide robot */
uint8_t cas_lab_safetysystem_classType::STOoff_guide_robot(void)
{
	rc = remoteIO[guide_robot]->wise4060_writeDO(guide_robot_STO_adr,
												 static_cast<int>(DO_STO_disable));
	// if(rc==1)	debug_message += "STOoff_guide_robot EMS Success!\n";
	// else	debug_message = debug_message + TC_ERROR + "STOoff_guide_robot EMS Fail!" + TC_RESET + "\n";
	// if(rc!=1) debug_message = debug_message + TC_ERROR + "STOoff_guide_robot EMS Fail!" + TC_RESET + "\n";
	if(rc!=1) std::cout << TC_ERROR << "STOoff_guide_robot EMS Fail!\n" << TC_RESET;
	// debug_message = debug_message + std::to_string(rc) + " : ";

	if( (cas_lab_state_old.guide_robot==guide_robot_EMS_on) || (cas_lab_state_old.fence==fence_open) || (cas_lab_state_old.network==network_guide_robot_remoteIO_err) )
	{
		rc = remoteIO[guide_robot]->wise4060_DO_pulse(guide_robot_reset_adr,1);
		// if(rc==2)	debug_message += "STOoff_guide_robot RESERT Success!\n";
		// else	debug_message = debug_message + TC_ERROR + "STOoff_guide_robot RESET Fail!" + TC_RESET + "\n";
		// if(rc!=2) debug_message = debug_message + TC_ERROR + "STOoff_guide_robot RESET Fail!" + TC_RESET + "\n";
		if(rc!=2) std::cout << TC_ERROR << "STOoff_guide_robot RESET Fail!\n" << TC_RESET;
		// std::cout << rc << " : ";
		// debug_message = debug_message + std::to_string(rc) + " : ";
		// if(rc==2)	debug_message += "                     STOoff_guide_robot RESET Success!\n";
		// else	debug_message = debug_message + "                     " + TC_ERROR + "STOoff_guide_robot RESET Fail!" + TC_RESET + "\n";
	}
	return rc;
}
/* activate the STO mechanism of the stand */
uint8_t cas_lab_safetysystem_classType::STOon_stand(void)
{
	rc = remoteIO[stand]->wise4060_writeDO(stand_STO_adr,
								 static_cast<int>(DO_STO_enable));
	// if(rc==1)	debug_message = debug_message + TC_ERROR + "STOon_stand Success!" + TC_RESET + "\n";
	// else	debug_message = debug_message + TC_ERROR + "STOon_stand Fail!" + TC_RESET + "\n";
	if(rc==1)	std::cout << TC_ERROR << "STOon_stand Success!\n" << TC_RESET;
	else		std::cout << TC_ERROR << "STOon_stand Fail!\n" << TC_RESET;
	// if(rc!=1) debug_message = debug_message + TC_ERROR + "STOon_stand Fail!" + TC_RESET + "\n";
	return rc;
}			
/* deactivate the STO mechanism of the stand */
uint8_t cas_lab_safetysystem_classType::STOoff_stand(void)
{
	rc = remoteIO[stand]->wise4060_writeDO(stand_STO_adr,
								 static_cast<int>(DO_STO_disable));
	// if(rc==1)	debug_message += "STOoff_stand Success!\n";
	// else	debug_message = debug_message + TC_ERROR + "STOoff_stand Fail!" + TC_RESET + "\n";
	// if(rc!=1) debug_message = debug_message + TC_ERROR + "STOoff_stand Fail!" + TC_RESET + "\n";
	if(rc!=1) std::cout << TC_ERROR << "STOoff_stand Fail!\n" << TC_RESET;
	return rc;
}		
/* activate the STO mechanism of the AGV */
uint8_t cas_lab_safetysystem_classType::STOon_AGV(void)
{
	rc = remoteIO[camera_robot]->wise4060_writeDO(AGV_STO_adr,
								 static_cast<int>(DO_STO_enable));
	rc += remoteIO[guide_robot]->wise4060_writeDO(AGV_STO_adr,
								 static_cast<int>(DO_STO_enable));
	if(rc==2)	debug_message = debug_message + TC_ERROR + "STOon_AGV Success!\n" + TC_RESET;
	else	debug_message = debug_message + TC_ERROR + "STOon_AGV Fail!\n" + TC_RESET;
	// if(rc!=2) debug_message = debug_message + TC_ERROR + "STOon_AGV Fail!\n" + TC_RESET;
	return rc;
}		
/* deactivate the STO mechanism of the AGV */
uint8_t cas_lab_safetysystem_classType::STOoff_AGV(void)
{
	rc = remoteIO[camera_robot]->wise4060_writeDO(AGV_STO_adr,
								 static_cast<int>(DO_STO_disable));
	rc += remoteIO[guide_robot]->wise4060_writeDO(AGV_STO_adr,
								 static_cast<int>(DO_STO_disable));
	// if(rc==2)	debug_message += "STOoff_AGV Success!\n";
	// else	debug_message = debug_message + TC_ERROR + "STOoff_AGV Fail!" + TC_RESET;
	if(rc!=2) debug_message = debug_message + TC_ERROR + "STOoff_AGV Fail!" + TC_RESET;
	return rc;
}		


/** * @brief set StackLight Display Mode.
	* @param none
 	* @return none
**	**/
void cas_lab_safetysystem_classType::set_StackLight_DisplayMode(void)
{
	// for(flc2=0; flc2<remoteIO_quantity; flc2++)
	// {
	// 	get_remoteIO_DO(flc2);
	// 	// printf("%d , %02x , %02x , %02x , %02x\n",flc2,DO_status[flc2][3],DO_status[flc2][2],DO_status[flc2][1],DO_status[flc2][0]);
	// 	// std::cout << flc2 << ": " << DO_status[flc2][0] << " , ";
	// 	// std::cout << DO_status[flc2][1] << " , ";
	// 	// std::cout << DO_status[flc2][2] << " , ";
	// 	// std::cout << DO_status[flc2][3] << " , " << std::endl;
	// }
	if( cas_lab_state.network == network_total_AP_err)
		// std::cout << "network_total_AP_err" << std::endl;
		display_mode = module_network_err;
	else if( cas_lab_state.network == network_fence_remoteIO_err )
		// std::cout << "network_fence_remoteIO_err" << std::endl;
		display_mode = module_network_err;
	else if( cas_lab_state.network == network_camera_robot_remoteIO_err )
		// std::cout << "network_camera_robot_remoteIO_err" << std::endl;
		display_mode = module_camera_robot_err;
	else if( cas_lab_state.network == network_guide_robot_remoteIO_err )
		// std::cout << "network_guide_robot_remoteIO_err" << std::endl;
		display_mode = module_guide_robot_err;
	// else if( cas_lab_state.network == network_stand_remoteIO_err )
	// 	display_mode = module_stand_err;
	else if( cas_lab_state.fence == fence_open )
		// std::cout << "fence_open" << std::endl;
		display_mode = module_fence_err;
	else if( cas_lab_state.camera_robot == camera_robot_EMS_on )
		// std::cout << "camera_robot_EMS_on" << std::endl;
		display_mode = module_camera_robot_err;
	else if( cas_lab_state.guide_robot == guide_robot_EMS_on )
		// std::cout << "guide_robot_EMS_on" << std::endl;
		display_mode = module_guide_robot_err;
	// else if( cas_lab_state.stand == stand_EMS_on )
	// 	display_mode = module_stand_err;
	else if( cas_lab_state.AGV == AGV_EMS_on )
		// std::cout << "AGV_EMS_on" << std::endl;
		display_mode = module_AGV_err;
	else if( DO_status[camera_robot][camera_robot] == DI_EMS_on )
		// std::cout << "module_camera_robot_err" << std::endl;
		display_mode = module_camera_robot_err;
	else if( DO_status[camera_robot][AGV] == DI_EMS_on )
		// std::cout << "module_camera_robot_AGV_err" << std::endl;
		display_mode = module_AGV_err;
	else if( DO_status[guide_robot][guide_robot] == DI_EMS_on )
		// std::cout << "module_guide_robot_err" << std::endl;
		display_mode = module_guide_robot_err;
	else if( DO_status[guide_robot][AGV] == DI_EMS_on )
		// std::cout << "module_guide_robot_AGV_err" << std::endl;
		display_mode = module_AGV_err;
	// else if( DO_status[stand][stand] == DI_EMS_on )
	// 	display_mode = module_stand_err;
}
/** * @brief StackLight actions based on the status of DisplayMode.
	* @param none
 	* @return none
**	**/
void cas_lab_safetysystem_classType::action_StackLight(void)
{
	/* set StackLight Display Mode */
	// set_StackLight_DisplayMode();
	/* flashing actions based on the status of display_mode */
	if( display_mode >= module_camera_robot_err )
		if( display_mode <= module_AGV_err )
			if( display_mode != display_mode_old )
	{
		red_flash_count = display_mode*2;
		display_HL_change = true;
		display_LED_change = false;
		display_mode_old = display_mode;
	}

	if( display_mode == module_ALL_healthy )
	{	/* if safetysystem is healthy, not error */
		remoteIO[fence]->wise4060_writeDO(fence_GLED_adr,1);
		remoteIO[fence]->wise4060_writeDO(fence_YLED_adr,0);
		remoteIO[fence]->wise4060_writeDO(fence_RLED_adr,0);
	}
	else if(display_mode == module_fence_err)
	{	/* if fence door open or totalEMS on */
		remoteIO[fence]->wise4060_writeDO(fence_GLED_adr,static_cast<int>(display_HL_change));
		remoteIO[fence]->wise4060_writeDO(fence_YLED_adr,static_cast<int>(display_HL_change));
		remoteIO[fence]->wise4060_writeDO(fence_RLED_adr,static_cast<int>(display_HL_change));
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

	display_HL_change = (!display_HL_change);
	// std::cout << "display_HL_change reverse : " << display_HL_change << std::endl;

}


/** * @brief cas_lab_safetysystem_classType main function
	* @param none
 	* @return lab_state, cas lab working state
**	**/
lab_state cas_lab_safetysystem_classType::run(void)
{
	display_mode = module_ALL_healthy;
	STO_time_ms = std::chrono::system_clock::now();
	display_time_ms = std::chrono::system_clock::now();
	STO_time_ms_old = STO_time_ms;
	display_time_ms_old = display_time_ms;

	while(1)
	{
		STO_time_ms = std::chrono::system_clock::now();
		STO_time_diff = std::chrono::duration_cast<std::chrono::milliseconds>(STO_time_ms - STO_time_ms_old).count();
		if( STO_time_diff > STO_interval )
		{
			STO_time_ms_old = STO_time_ms;
			std::cout << "STO_time: " << STO_time_diff << std::endl;
			/* verify that totalAP is online before executing the program */
			if( verify_totalAP() == EXIT_SUCCESS )
			{
				/* verify moduleAPs is working and connected. */
				verify_moduleAP();
				/* verify remoteIOs is working and connected. */
				verify_remoteIO();
				
				/* get remoteIO[fence&guide_robot] DI data */
				get_remoteIO_DI(fence);
				// get_remoteIO_DI(camera_robot);
				get_remoteIO_DI(guide_robot);
				/* check cas lab EMS status */
				if( cas_lab_state.network != network_fence_remoteIO_err )
				{	/* check if the fence door is open */
					if( check_fence_door() == fence_close )
					{	/* check cas lab module EMS */
						// check_camera_robot_EMS();
						check_guide_robot_EMS();
						// check_stand_EMS();
						// check_AGV_EMS();
					}
					/* implement actions on the indicator lights and STO of each module */
					CAS_LAB_action();
				}
				// debug_message = debug_message + "display_mode: " + std::to_string(display_mode) + "\n";
				std::cout << "display_mode: " << display_mode << std::endl;
				// delay_1ms(500, true);
				// std::cout << TC_CLOSE << "\n" << debug_message.c_str() << std::endl;
			}
			// else
			// {
			// 	std::cout << TC_ERROR << "CAS Lab network is down, unable to operate" << TC_RESET << std::endl;
			// 	break;
			// }
		}

		display_time_ms = std::chrono::system_clock::now();
		display_time_diff = std::chrono::duration_cast<std::chrono::milliseconds>(display_time_ms - display_time_ms_old).count();
		if( display_time_diff > flash_interval )
		{
			display_time_ms_old = display_time_ms;
			// std::cout << "display_time: " << display_time_diff << "\n";
			action_StackLight();
		}
	}

	return cas_lab_state;
}
/** * @brief cas lab module initialization
	* @param none
 	* @return none
**	**/
void cas_lab_safetysystem_classType::init(void)
{
	debug_message.clear();
	// debug_message = "";

	for(flc1=0; flc1<remoteIO_quantity; flc1++)
	{
		if( remoteIO[flc1]->set_response_timeout(0,100000) == 0 )
			std::cout << flc1 << " : set response timeout Success!\n";
		else
			std::cout << TC_ERROR << flc1 << " : set response timeout Fail!\n";
		// if( remoteIO[flc1]->set_indication_timeout(0,100000) == 0 )
		// 	std::cout << flc1 << " : set indication timeout Success!" << std::endl;
		// else
		// 	std::cout << TC_ERROR << flc1 << " : set indication timeout Fail!" << std::endl;
	}

	STOon_camera_robot();
	STOon_guide_robot();
	// STOon_stand();
	STOon_AGV();
	cas_lab_state_old.guide_robot = guide_robot_EMS_on;
	delay_1ms(1000, true);
	STOoff_camera_robot();
	STOoff_guide_robot();
	// STOoff_stand();
	STOoff_AGV();
	delay_1ms(1000, true);
	// gettimeofday(&tv, NULL);
	
	display_mode=99; display_mode_old=0;
	display_HL_change = false; display_LED_change = true;

	// std::cout << "display_HL_change : " << display_HL_change << std::endl;
	std::cout << debug_message.c_str();
	debug_message.clear();
	debug_message = "";

	std::cout << "    >>> cas_lab_SafetySystem controller initialization completed!" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl << std::endl;
}


void cas_lab_safetysystem_classType::delay_1ms(int delay_time, bool printSW)
{
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	while(true)
	{
		int64_t duration =
			std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();
		if (duration > delay_time)
		{
			if(printSW)
				std::cout << "delay time: " << duration << "ms" << std::endl;
				// debug_message = debug_message + "delay time: " + std::to_string(duration) + "ms" + "\n";
			break;
		}
	}
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF cas_lab_safetysystem_classType.cpp ***** */
