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
	bool display_HL_change=false;

	/* 建立modbus通訊物件 */
	cas_lab_safetysystem_classType cas_lab_safetysystem;
	cas_lab_safetysystem.init();
	cas_lab_state = cas_lab_safetysystem.run();

	// // std::cout << "display_HL_change : " << display_HL_change << std::endl;
	// /* main loop */
	// while(1)
	// {
	// 	// display_HL_change = (!display_HL_change);
	// 	// std::cout << "display_HL_change : " << display_HL_change << std::endl;
	// 	// cas_lab_safetysystem.delay_1ms(1000);
	// }

	/* main quit */
	return 0;
}





/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF cas_lab_safetysystem.cpp ***** */
