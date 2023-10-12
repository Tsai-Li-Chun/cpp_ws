/** ******************************************************
	* @file		main.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <PhoLocalization.h>
#include <PhoXi.h>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
/* User Includes End */

/* namespace ------------------------------------------------*/
/* namespace Begin */
using namespace pho::sdk;
using namespace pho::api;
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

/** * @brief  Program entry point.
 	* @param argc(int) Number of input parameters
 	* @param argv(int) input parameters
 	* @return (int) Program Error.
**	**/
int main(int argc, char **argv)
{
	PhoXiFactory Factory;
	//Check if the PhoXi Control Software is running
    if (!Factory.isPhoXiControlRunning())
    {
        std::cout << "PhoXi Control Software is not running" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "PhoXi Control Software is running OK!" << std::endl;
    }

	

	// /* main loop */
	// while(1)
	// {	}

	/* main quit */
	return EXIT_SUCCESS;
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF main.cpp ***** */