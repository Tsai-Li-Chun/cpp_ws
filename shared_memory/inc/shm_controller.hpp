/** ******************************************************
	* @file		shm_controller.hpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __shm_controller_HPP__
#define __shm_controller_HPP__


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <iostream>
#include <sys/shm.h>
#include <string.h>
#include <cstdlib>
#include <unistd.h>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */
/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */
/* Extern Typedef End */


/* Extern Class -------------------------------------------*/
/* Extern Class Begin */

/* shared memory control object */
class shared_memory_controller
{
/* private members */
private:
	shmid_ds shm_ds;
    int8_t shm_id;
	int8_t error_code;
    void *shm_ptr_void;
    void *ptr_error_code;

/* public members */
public:
	/* Constructor */
	shared_memory_controller(void);
	/* Destructor */
	~shared_memory_controller();

	/* create and get shared memory */
	int8_t get_shm(key_t key, size_t size, int flg);
	/* attach to the shared memory */
	void* attach_shm(int id, void* ptr, int flg);
	/* detach from shared memory */
	int8_t detach_shm(void* ptr);
	/* remove from shared memory */
	int8_t remove_shm(int id);
	/* display information of the shm */
	void shmds_information(void);

	/* write data to shared memory. */
	void* write_shm(void);
	/* read data from shared memory. */
	void* read_shm(void);
};

/* Extern Class End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */
/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */


#endif /*__shm_controller_HPP__ */

/* ***** END OF shm_controller.HPP ***** */
