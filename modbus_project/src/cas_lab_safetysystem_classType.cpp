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
	remoteIO_IP.resize(remoteIO_quantity);
	remoteIO_IP[remoteIO_number_fence] = remoteIO_IP_fence;
	remoteIO_IP[remoteIO_number_camera_robot] = remoteIO_IP_camera_root;
	remoteIO_IP[remoteIO_number_guide_robot] = remoteIO_IP_guide_root;
	remoteIO_IP[remoteIO_number_stand] = remoteIO_IP_stand;

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
	static int online_remoteIO_quantity = 0;
	online_remoteIO_quantity = 0;
	/* sequentially evaluate the status of all remoteIO */
	for(flc1=0; flc1<remoteIO_quantity; flc1++)
	{
		std::cout << flc1  << " : ";
		/* check the remoteIO is online */
		rc = remoteIO[flc1]->isConnect();
		if(rc != 1)
		{	/* if disconnected, attempt to reconnect */
			std::cout << TC_ERROR << "remoteIO IP:" << remoteIO_IP[flc1].c_str() << " connection lost!" << std::endl;
			rc = remoteIO[flc1]->reConnect();
			if(rc != 0)
			{	/* connection failed */
				cas_lab_state.network = (static_cast<uint8_t>(flc1)+static_cast<uint8_t>(5));
				std::cout << "    >> remoteIO IP:" << remoteIO_IP[flc1].c_str() << " reconnection failed!" << TC_RESET << std::endl;
			}
			else
			{	/* connection successfully */
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
	std::cout << "-------------------------------------------------" << std::endl << std::endl;

	return online_remoteIO_quantity;
}

/** * @brief check if the fence door is open.
	* @param none
 	* @return int, check result, 0:close, 1:open
**	**/
int cas_lab_safetysystem_classType::check_fence_door(void)
{
	
}


/** * @brief cas_lab_safetysystem_classType main function
	* @param none
 	* @return lab_state, cas lab working state
**	**/
lab_state cas_lab_safetysystem_classType::run(void)
{
	/* verify that totalAP is online before executing the program */
	while( verify_totalAP() == EXIT_SUCCESS )
	{
		/* verify moduleAPs is working and connected. */
		verify_moduleAP();
		/* verify remoteIOs is working and connected. */
		verify_remoteIO();


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
