/** ******************************************************
	* @file		main.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <PhoLocalization.h>
#include <PhoXi.h>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
/* User Includes End */

/* namespace ------------------------------------------------*/
/* namespace Begin */
using namespace pho::sdk;
using namespace pho::api;
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
	PhoXiFactory Factory;
	//Check if the PhoXi Control Software is running
    if (!Factory.isPhoXiControlRunning())
    {
        std::cout << "PhoXi Control Software is not running" << std::endl;
    }
    else
    {
        std::cout << "PhoXi Control Software is running OK!" << std::endl;
    }

	std::unique_ptr<PhoLocalization> localization;
    //Initialize localization object.
    //Note that without proper authentication, this step will fail.
    //See Photoneo Localization SDK manual how to authenticate your installation.
    try 
	{
        localization.reset(new PhoLocalization());
		std::cout << "PhoLocalization reset Success" << std::endl;
    }
	catch (const AuthenticationException & ex)
	{
        std::cout << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    try
	{
        SceneSource scene;
        //Set scene where to look for an object. Possible scene sources are:
        //Photoneo device (Photoneo PhoXi 3D Scanner, Photoneo MotionCam 3D) or file camera (e.g., "InstalledExamples-basic-example"):
        //     scene = SceneSource::PhoXi("Device ID");
        //*.praw or *.ply files created by Photoneo PhoXi Control from 3D scans:
        //     scene = SceneSource::File("path to praw / ply file");
        scene = SceneSource::File("template_api_test1.ply");
        localization->SetSceneSource(scene);
		std::cout << "SetSceneSource Success" << std::endl;
    }
	catch (const PhoLocalizationException & ex)
	{
        std::cout << "SetSceneSource Error: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    try
	{
        //Load PLCF file containing a preprocessed model, localization settings, and stopping criteria.
        localization->LoadLocalizationConfiguration("template_api_test.plcf");
		std::cout << "LoadLocalizationConfiguration Success" << std::endl;
    }
	catch (const IOException & ex)
	{
        std::cout << "Error loading plcf file: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    //See ProgrammaticSettings example for adjusting localization settings and setting stopping criteria.

    AsynchroneResultQueue queue;
    try
	{
        queue = localization->StartAsync();
        //If the scene and model were correctly set, calling StartAsync() starts a localization loop.
        //Localized poses will begin to appear in the queue.
        //The loop will run until any of the stopping criteria stored in the PLCF file is met.
        //If no stopping criteria are set, the loop will run indefinitely or until localization->StopAsync() is called.
    }
	catch (const PhoLocalizationException & ex)
	{
        std::cout << "Error starting localization: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    TransformationMatrix4x4 result;
    std::cout << "Localization results:" << std::endl;
    while (queue.GetNext(result))
	{
        std::cout << result << std::endl;
    }
    std::cout << "Localization finished" << std::endl;

	// /* main loop */
	// while(1)
	// {	}

	/* main quit */
	return EXIT_SUCCESS;
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF main.cpp ***** */