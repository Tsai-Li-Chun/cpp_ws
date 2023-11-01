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
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "define.h"
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
    float pose[16]={0};
    for(int i=0; i<16; i++)
        pose[i] = i+0.1;
    
    shmid_ds shm_ds;
    int shm_id,wait_key;
    void *shm_ptr;

    /* create shared memory nattch */
    shm_id = shmget(shm_key, shm_size, shm_flg);
    if( shm_id != (-1) )
    {
        printf("Create shared memory Success. shm_id=: %d\n",shm_id);
        shm_ptr = shmat(shm_id, NULL, 0);
        if( shm_ptr != (void*)(-1) )
            printf("Attach shared memroy Success. shm_ptr=: %p\n",shm_ptr);
        else
        {
            printf("Create shared meeory Failed.\n");
            perror(" -> shmat error code: ");
            return EXIT_FAILURE;
        }
    }
    else
    {
        printf("Create shared meeory Failed.\n");
        perror(" -> shmget error code: ");
        return EXIT_FAILURE;
    }

    /* write data to shared memory. */
    memcpy(shm_ptr, pose, sizeof(pose));

    /* Detach and Remove shared memory */
    std::cin >> wait_key;
    if( shmdt(shm_ptr)!=(-1) )
    {
        printf("Detach shared meeory Success.\n");
        if( shmctl(shm_id, IPC_RMID, NULL) == 0 )
            printf("Remove shared meeory Success.\n");
        else
        {
            printf("Remove shared meeory Failed.\n");
            perror(" -> shmctl error code: ");
            return EXIT_FAILURE;
        }
    }
    else
    {
        printf("Detach shared meeory Failed.\n");
        perror(" -> shmdt error code: ");
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF main.cpp ***** */