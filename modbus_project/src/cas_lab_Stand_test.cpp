/** ******************************************************
	* @file		cas_lab_Stand_test.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <iostream>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "cas_lab_StandController.hpp"
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

/** * @brief  Program entry point.
	* @param argc(int) Number of input parameters
 	* @param argv(int) input parameters
 	* @return (int) Program Error.
**	**/
int main(int argc, char **argv)
{
	int rc;
	cas_lab_StandController clst;

	clst.init();
	while(1)
	{
		clst.run();
		// rc = clst.set_deltaDRV_cmd(robot_adr::action_cmd, static_cast<uint16_t>(robot_action_invalid));
		// std::cout << "rc= " << rc << " ,robot command address clean." << std::endl;
		// clst.delay_1ms(500);
		// rc = clst.set_deltaDRV_cmd(robot_adr::action_cmd, static_cast<uint16_t>(robot_action_valid));
		// std::cout << "rc= " << rc << " ,robot command address set." << std::endl;
		// clst.delay_1ms(500);
	}
	/* main quit */
	return 0;
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF cas_lab_Stand_test.cpp ***** */
