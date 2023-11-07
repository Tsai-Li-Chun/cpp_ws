/** ******************************************************
	* @file		main.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


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
    char wait_key;
    float pose[shm_float_size]={0};

    /* Create shared memory control object */
    shared_memory_controller shm_ctl;
    /* create and get shared memory segment */
    int id = shm_ctl.get_shm(shm_key, shm_size, shm_flg);
    if( id == (-1) ) return EXIT_FAILURE;
    /* attach to the shared memory segment */
    void *ptr = shm_ctl.attach_shm(id, nullptr, shm_rw_twoway);
    if( ptr == (void*)(-1) ) return EXIT_FAILURE;
	/* display information of the shm */
    shm_ctl.shmds_information(); 

    /* read data from shared memory. */
    do
    {
        printf("Press Q to exit the program, press R to read from shared memory: ");
        std::cin >> wait_key;
        if( wait_key == 'r' )
        {
            /* send request */
            printf("Send request, pose[0]=1.0\n");
            pose[0] = 1.0f;
            // for(i=1; i<17; i++) pose[i] = 0.0f;
            shm_ctl.write_shm(pose, 1*sizeof(float));
            /* wait for response */
            while( pose[0] != 2.0f )
            {
                shm_ctl.read_shm(pose, 2*sizeof(float));
                printf("Waiting for data to return ...\n");
                printf("pose[0]=%10.4f , pose[1]=%10.4f\n",pose[0],pose[1]);
                sleep(1);
            }
            shm_ctl.read_shm(pose, (size_t)pose[1]*sizeof(float));
            for(i=0; i<(int)pose[1]; i++) printf("(%10.4f) ",pose[i]);
            printf("\n");
            /* send reset signal */
            printf("Response received. Send reset signal ... ");
            for(i=0; i<shm_float_size; i++) pose[i] = 0.0f;
            shm_ctl.write_shm(pose, sizeof(pose));
            printf("Finish\n");
        }
    }while( wait_key!='q' );

    /* send remove shared memory signal */
    printf("send remove shared memory signal.\n");
    pose[0] = 4.0f;
    shm_ctl.write_shm(pose, 1*sizeof(float));

    /* detach and Remove shared memory segment */
    if( shm_ctl.detach_shm(ptr) == (-1) )
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF main.cpp ***** */