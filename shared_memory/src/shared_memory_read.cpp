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
	float pose[17]={0};
    shmid_ds shm_ds;
    int shm_id,i;
    char wait_key;
    void *shm_ptr;
    float *shm_ptrf;

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
    if( shmctl(shm_id, IPC_STAT, &shm_ds ) == 0 )
    {
        printf("shm_ds.shm_perm.uid = %d\n",shm_ds.shm_perm.uid);
        printf("shm_ds.shm_perm.mode= %d\n",shm_ds.shm_perm.mode);
        printf("shm_ds.shm_perm.gid = %d\n",shm_ds.shm_perm.gid);
        printf("shm_ds.shm_perm.cuid= %d\n",shm_ds.shm_perm.cuid);
        printf("shm_ds.shm_perm.cgid= %d\n",shm_ds.shm_perm.cgid);
        printf("shm_ds.shm_segsz    = %ld\n",shm_ds.shm_segsz);
        printf("shm_ds.shm_nattch   = %ld\n",shm_ds.shm_nattch);
        printf("shm_ds.shm_lpid     = %d\n",shm_ds.shm_lpid);
        printf("shm_ds.shm_cpid     = %d\n",shm_ds.shm_cpid);
        printf("shm_ds.shm_ctime    = %ld\n",shm_ds.shm_ctime);
        printf("shm_ds.shm_atime    = %ld\n",shm_ds.shm_atime);
        printf("shm_ds.shm_dtime    = %ld\n",shm_ds.shm_dtime);
    }
    else
        perror(" -> shmctl error code: ");

    /* read data from shared memory. */
    shm_ptrf = (float*)shm_ptr;
    do
    {
        printf("Press Q to exit the program, press R to read from shared memory: ");
        std::cin >> wait_key;
        if( wait_key == 'r' )
        {
            /* send request */
            printf("Send request, pose[0]=1.0\n");
            pose[0] = 1.0f;
            for(i=1; i<17; i++) pose[i] = 0.0f;
            memcpy(shm_ptrf, pose, sizeof(pose));
            /* wait for response */
            while( pose[0] != 2.0f ) 
            {
                printf("Waiting for data to return ...\n");
                memcpy(pose, shm_ptrf, sizeof(pose));
                for(i=0; i<17; i++) printf("(%10.4f) ",pose[i]);
                printf("\n");
                sleep(1);
            }
            /* send reset signal */
            printf("Response received. Send reset signal.\n");
            for(i=0; i<17; i++) pose[i] = 0.0f;
            memcpy(shm_ptrf, pose, sizeof(pose));
        }
    }while( wait_key!='q' );

    /* send remove shared memory signal */
    printf("send remove shared memory signal.\n");
    for(i=0; i<17; i++) pose[i] = 0.0f;
    pose[0] = 4.0f;
    memcpy(shm_ptrf, pose, sizeof(pose));

    /* Detach and Remove shared memory */
    if( shmdt(shm_ptr)!=(-1) )
        printf("Detach shared meeory Success.\n");
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