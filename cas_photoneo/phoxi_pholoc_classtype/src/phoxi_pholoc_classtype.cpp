/** ******************************************************
	* @file		phoxi_pholoc_classtype.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "define.h"
#include "photoneo_controller.hpp"
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

int64_t result_vector2array(std::vector<pho::sdk::LocalizationPose> *vector, float *array);

/* Function End */



/* ---------------------------------------------------------*/
/* ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩ Program ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩ ---------------------------*/
/* ---------------------------------------------------------*/
/* Program Begin */

/** * @brief Program entry point.
	* @param argc(int) Number of input parameters
 	* @param argv(int) input parameters
 	* @return (int) Program Error.
**	**/
int main(int argc, char **argv)
{
    char key=0;
    float ResultList_array[shm_float_size]={0};
    int64_t data_size;
    photoneo_controller pho_ctl;
    std::vector<pho::sdk::LocalizationPose> ResultList_vector;
    shared_memory_controller shm_ctl;

    /* create and get shared memory segment */
    int id = shm_ctl.get_shm(shm_key, shm_size, shm_flg);
    if( id == (-1) ) return EXIT_FAILURE;
    /* attach to the shared memory segment */
    void *ptr = shm_ctl.attach_shm(id, nullptr, shm_rw_twoway);
    if( ptr == (void*)(-1) ) return EXIT_FAILURE;
	/* display information of the shm */
    shm_ctl.shmds_information();
    shm_ctl.write_shm(ResultList_array, shm_size);

    ResultList_vector.reserve(results_MAXsize);
    pho_ctl.GetAvailableDevices();
    pho_ctl.ConnectPhoXiDevice();
    pho_ctl.GetAndSetProfile();
    pho_ctl.SoftwareTrigger();
    pho_ctl.Localization_StartUp();
    
    do
    {
        printf("Waiting for data request command ...\n");
        shm_ctl.read_shm(ResultList_array, 1*sizeof(float));
        if( ResultList_array[0] == 1.0f )
        {
            printf("Received data request command.\n");
            pho_ctl.calculate_localization();
            pho_ctl.GetLocResults(&ResultList_vector);
            data_size = result_vector2array(&ResultList_vector, ResultList_array);
            ResultList_array[0] = 2.0f;     ResultList_array[1] = (float)data_size;
            shm_ctl.write_shm(ResultList_array, data_size*sizeof(float));
            printf("Finished writing to shared memory.\n");
        }
        sleep(1);
    }while( ResultList_array[0] != 4.0f );

    pho_ctl.CorrectDisconnect();
    /* detach and Remove shared memory segment */
    if( shm_ctl.detach_shm(ptr) == (-1) ) return EXIT_FAILURE;
    /* remove and Remove shared memory segment */
    if( shm_ctl.remove_shm(id) == (-1) ) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int64_t result_vector2array(std::vector<pho::sdk::LocalizationPose> *vector, float *array)
{
    static size_t vector_size,array_size,i;
    vector_size = vector->size();
    array_size = 2;
    for( i=0; i<vector_size; i++ )
    {
        std::cout << i << " / " << array_size << std::endl;
        array[array_size] = (float)vector->at(i).ID; array_size++;
        std::cout << i << " / " << array_size << std::endl;
        array[array_size] = (float)vector->at(i).Occluded; array_size++;
        std::cout << i << " / " << array_size << std::endl;
        array[array_size] = (float)vector->at(i).VisibleOverlap; array_size++;
        std::cout << i << " / " << array_size << std::endl;
        array[array_size] = vector->at(i).Transformation.at(0).at(0); array_size++;
        std::cout << i << " / " << array_size << std::endl;
        array[array_size] = vector->at(i).Transformation.at(0).at(1); array_size++;
        array[array_size] = vector->at(i).Transformation.at(0).at(2); array_size++;
        array[array_size] = vector->at(i).Transformation.at(0).at(3); array_size++;
        array[array_size] = vector->at(i).Transformation.at(1).at(0); array_size++;
        array[array_size] = vector->at(i).Transformation.at(1).at(1); array_size++;
        array[array_size] = vector->at(i).Transformation.at(1).at(2); array_size++;
        array[array_size] = vector->at(i).Transformation.at(1).at(3); array_size++;
        array[array_size] = vector->at(i).Transformation.at(2).at(0); array_size++;
        array[array_size] = vector->at(i).Transformation.at(2).at(1); array_size++;
        array[array_size] = vector->at(i).Transformation.at(2).at(2); array_size++;
        array[array_size] = vector->at(i).Transformation.at(2).at(3); array_size++;
        array[array_size] = vector->at(i).Transformation.at(3).at(0); array_size++;
        array[array_size] = vector->at(i).Transformation.at(3).at(1); array_size++;
        array[array_size] = vector->at(i).Transformation.at(3).at(2); array_size++;
        array[array_size] = vector->at(i).Transformation.at(3).at(3); array_size++;
        std::cout << i << " / " << array_size << std::endl;
    }
    return array_size;
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF phoxi_pholoc_classtype.cpp ***** */
