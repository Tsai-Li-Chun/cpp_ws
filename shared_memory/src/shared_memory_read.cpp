/** ******************************************************
	* @file		main.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
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
	printf("%ld\n",sizeof(pose));
    // 1. 获取 SHM
    int shm_id = shmget(15, 1024, IPC_CREAT | 0666);
    printf("shm_id= %d\n",shm_id);
    if (shm_id != -1)
	{
        // 2. 映射 SHM
        void* shm = shmat(shm_id, NULL, 0);
		printf("&shm= %p\n",&shm);
        printf("shm= %p\n",shm);
        if (shm != (void*)-1)
		{
            // 3. 读取 SHM
            memcpy(pose, shm, sizeof(pose));
			for(int k=0; k<16; k++)
			{
				printf("%f\t",pose[k]);
			}
			printf("\n");
            // 4. 关闭 SHM
            shmdt(shm);
        } else {
            perror("shmat:");
        }
    } else {
        perror("shmget:");
    }
    if (0 == shmctl(shm_id, IPC_RMID, NULL))
        printf("delete shm success.\n");
    return 0;
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF main.cpp ***** */