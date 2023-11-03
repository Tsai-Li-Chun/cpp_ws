/** ******************************************************
	* @file		photoneo_controller.hpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __photoneo_controller_HPP__
#define __photoneo_controller_HPP__


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <thread>
#include <atomic>
#include <chrono>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "PhoXi.h"
#include "PhoLocalization.h"
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */

#if defined(_WIN32)
    #define DELIMITER "\\"
#elif defined (__linux__)
    #define DELIMITER "/"
#endif
#define LOCAL_CROSS_SLEEP(Millis) std::this_thread::sleep_for(std::chrono::milliseconds(Millis));

/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */
/* Extern Typedef End */


/* Extern Class -------------------------------------------*/
/* Extern Class Begin */

/* photoneo PhoXiControl and Localization API */
class photoneo_controller
{
/* private members */
private:
    pho::api::PhoXiFactory Factory;
    pho::api::PPhoXi PhoXiDevice;
    pho::api::PFrame SampleFrame;
    std::vector <pho::api::PhoXiDeviceInformation> DeviceList;
    std::string FileCameraFolder = "";
    std::string OutputFolder = "";

    /* get availble devices */
    void GetAvailableDevices(void);
    /* select how to connect */
    void ConnectPhoXiDevice(void);
    /* connect usong device Hardware-Identification */
    void ConnectPhoXiDeviceBySerial(void);
    /* conncet using device number */
    void ConnectPhoXiDeviceByPhoXiDeviceInformationEntry(void);
    /* connect usong device IP */
    void ConnectPhoXiDeviceByIPAddress(void);
    /* connect to the first device in the list */
    void ConnectFirstAttachedPhoXiDevice(void);
    /* connect using device camera-file */
    void ConnectPhoXiFileCamera(void);

    /* display and query about the current device function */
    void BasicDeviceState(void);
    /* display about the current device information */
    void BasicDeviceInfo(void);

    /* capture frame in free-mode, loop 5 times */
    void Freerun_loop5(void);
    /*  capture frame in Software-Trigger, loop 5 times */
    void SoftwareTrigger_loop5(void);
    /* capture frame in Software-Trigger-Async, loop 5 times */
    void SoftwareTriggerAsyncGrab_loop5(void);

    /* change the settings of the device */
    void ChangeSettings(void);
    /*  */
    void DataHandling(void);
    void CorrectDisconnect(void);

    void PrintFrameInfo(const pho::api::PFrame &Frame);
    void PrintFrameData(const pho::api::PFrame &Frame);
    void PrintCapturingSettings(const pho::api::PhoXiCapturingSettings &CapturingSettings);
    void PrintProcessingSettings(const pho::api::PhoXiProcessingSettings &ProcessingSettings);
    void PrintCoordinatesSettings(const pho::api::PhoXiCoordinatesSettings &CoordinatesSettings);
    void PrintCalibrationSettings(const pho::api::PhoXiCalibrationSettings &CalibrationSettings, const std::string &source);
    void PrintAdditionalCalibrationSettings(const pho::api::PhoXiAdditionalCameraCalibration& CalibrationSettings, const std::string& source);
    void PrintResolution(const pho::api::PhoXiSize& Resolution);
    void PrintCoordinateTransformation(const pho::api::PhoXiCoordinateTransformation& transformation);
    void PrintMatrix(const std::string &name, const pho::api::CameraMatrix64f &matrix);
    void PrintVector(const std::string &name, const pho::api::Point3_64f &vector);
    void PrintDistortionCoefficients(const std::string &name, const std::vector<double> & distCoeffs);

    template<class T>
    bool ReadLine(T &Output) const
    {
        std::string Input;
        std::getline(std::cin, Input);
        std::stringstream InputSteam(Input);
        return (InputSteam >> Output) ? true : false;
    }
    bool ReadLine(std::string &Output) const
    {
        std::getline(std::cin, Output);
        return true;
    }

/* public members */
public:
	/* Constructor */
    photoneo_controller() {};
	/* Destructor */
    ~photoneo_controller() {};
};

/* Extern Class End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */
/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */


#endif /*__photoneo_controller_HPP__ */

/* ***** END OF photoneo_controller.HPP ***** */
