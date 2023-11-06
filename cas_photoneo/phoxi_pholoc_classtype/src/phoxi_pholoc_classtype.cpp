/** ******************************************************
	* @file		phoxi_pholoc_classtype.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "photoneo_controller.hpp"
#include "shm_controller.hpp"
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

/** * @brief Program entry point.
	* @param argc(int) Number of input parameters
 	* @param argv(int) input parameters
 	* @return (int) Program Error.
**	**/
int main(int argc, char **argv)
{
    char key=0;

    pho::sdk::AsynchroneResultQueue queue;
    pho::sdk::LocalizationPose result;
    photoneo_controller pho_ctl;
    pho_ctl.GetAvailableDevices();
    pho_ctl.ConnectPhoXiDevice();
    pho_ctl.GetAndSetProfile();
    pho_ctl.SoftwareTrigger();
    pho_ctl.Localization_StartUp();

    do
    {
        std::cout << "press 's' calculate localization, press 'q' exit the loop: ";
        std::cin >> key;
        if(key=='s') pho_ctl.calculate_localization();
    }while( key!='q');

    pho_ctl.CorrectDisconnect();
    return 0;
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF phoxi_pholoc_classtype.cpp ***** */
