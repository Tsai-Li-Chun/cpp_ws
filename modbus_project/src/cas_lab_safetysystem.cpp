/** ******************************************************
	* @file		cas_lab_safetysystem.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
// #include <string>
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
// int rc;

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
	/* 隨便顯示些東西證明程式運作 */
	std::cout << "CAS Lab Safety System program setup..." << std::endl;
	std::cout << "----------------------------------------------" << std::endl << std::endl;

	/* create data structure for the work status of cas lab */
	lab_state cas_lab_state;

	/* 建立modbus通訊物件 */
	cas_lab_safetysystem_classType cas_lab_safetysystem;

	// /* main loop */
	// while(1)
	// {
		/* work once loop */
		cas_lab_state = cas_lab_safetysystem.run();
	// 	/* delay 100ms */
	// 	usleep(1000*100);
	// }

	/* main quit */
	return 0;
}





/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF cas_lab_safetysystem.cpp ***** */
