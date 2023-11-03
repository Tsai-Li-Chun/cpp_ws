/** ******************************************************
	* @file		main.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <iostream>
#include <cstdlib>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "define.h"
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

int main(int argc, char** argv)
{
    int i;
    float pose[17]={0};  

    /* Create shared memory control object */
    shared_memory_controller shm_ctl;
    /* create and get shared memory segment */
    int id = shm_ctl.get_shm(shm_key, shm_size, shm_flg);
    if( id == (-1) )
        return EXIT_FAILURE;
    /* attach to the shared memory segment */
    void *ptr = shm_ctl.attach_shm(id, nullptr, shm_rw_twoway);
    if( ptr == (void*)(-1) )
        return EXIT_FAILURE;
	/* display information of the shm */
    shm_ctl.shmds_information(); 

    /* write data to shared memory. */
    do
    {
        printf("Waiting for data request command ...\n");
        shm_ctl.read_shm(pose, sizeof(pose));
        if( pose[0] == 1.0f )
        {
            printf("Received data request command.\n");
            pose[0] = 2.0f;
            for(i=1; i<17; i++) pose[i] = i+0.1;
            shm_ctl.write_shm(pose, sizeof(pose));
            printf("Finished writing to shared memory.\n");
        }
        sleep(1);
    }while( pose[0] != 4.0f );

    /* detach and Remove shared memory segment */
    if( shm_ctl.detach_shm(ptr) == (-1) )
        return EXIT_FAILURE;
    /* remove and Remove shared memory segment */
    if( shm_ctl.remove_shm(id) == (-1) )
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF main.cpp ***** */