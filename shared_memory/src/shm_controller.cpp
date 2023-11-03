/** ******************************************************
	* @file		shm_controller.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
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

/** * @brief Constructor
 	* @param None
 	* @return None
**	**/
shared_memory_controller::shared_memory_controller()
{
	shm_id = 0;
	error_code = 0;
	shm_ptr_void = nullptr;
}
/** * @brief Destructor
 	* @param None
 	* @return None
**	**/
shared_memory_controller::~shared_memory_controller()
{
}

/** * @brief create and get shared memory
 	* @param key_t key, identification key
 	* @param size_t size, shared memory size
 	* @param int flg, control flag value
 	* @return int8_t, unique identification ID number
**	**/
int8_t shared_memory_controller::get_shm(key_t key, size_t size, int flg)
{

	return shm_id;
}

/** * @brief attach to the shared memory
 	* @param int id, unique identification ID number
 	* @param void* ptr, specify address to this program
 	* @param int flg, control flag value(R/W)
 	* @return void*, address linked to this program
**	**/
void* shared_memory_controller::attach_shm(int id, void* ptr, int flg)
{

	return shm_ptr_void;
}

/** * @brief detach from shared memory
 	* @param void* ptr, specify address to this program
 	* @return void*, error code
**	**/
int8_t shared_memory_controller::detach_shm(void* ptr)
{

	return error_code;
}

/** * @brief remove from shared memory
 	* @param void* ptr, specify address to this program
 	* @return void*, error code
**	**/
int8_t shared_memory_controller::remove_shm(int id)
{

	return error_code;
}

/** * @brief display information of the shm
 	* @param None
 	* @return None
**	**/
void shared_memory_controller::shmds_information(void)
{

}

/** * @brief write data to shared memory
 	* @param None
 	* @return None
**	**/
void* shared_memory_controller::write_shm(void)
{


	return ptr_error_code;
}

/** * @brief read data from shared memory
 	* @param None
 	* @return None
**	**/
void* shared_memory_controller::read_shm(void)
{

	return ptr_error_code;
}


/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF shm_controller.cpp ***** */
