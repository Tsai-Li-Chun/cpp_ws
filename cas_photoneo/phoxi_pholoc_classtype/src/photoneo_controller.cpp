/** ******************************************************
	* @file		photoneo_controller.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "photoneo_controller.hpp"
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

/** * @brief get availble devices
	* @param None
 	* @return None
**	**/
void photoneo_controller::GetAvailableDevices(void)
{
    /* Wait for PhoXiControl to start */
    while (!Factory.isPhoXiControlRunning())
    {
		std::cout << "waiting PhoXiControl start ..." << std::endl;
        LOCAL_CROSS_SLEEP(1000);
    }
    std::cout << "PhoXi Control Version: " << Factory.GetPhoXiControlVersion() << std::endl;
    std::cout << "PhoXi API Version: " << Factory.GetAPIVersion() << std::endl;

    DeviceList = Factory.GetDeviceList();
    std::cout << "PhoXi Factory found " << DeviceList.size() << " devices." << std::endl;
    pho::api::PhoXiDeviceInformation *DeviceInfo;
    for (for_count = 0; for_count < DeviceList.size(); ++for_count)
    {
        DeviceInfo = &DeviceList[for_count];
        std::cout << "Device: " << for_count << std::endl;
        std::cout << "  Name:                    " << DeviceInfo->Name << std::endl;
        std::cout << "  Hardware Identification: " << DeviceInfo->HWIdentification << std::endl;
        std::cout << "  Type:                    " << std::string(DeviceInfo->Type) << std::endl;
        std::cout << "  Firmware version:        " << DeviceInfo->FirmwareVersion << std::endl;
        std::cout << "  Variant:                 " << DeviceInfo->Variant << std::endl;
        std::cout << "  IsFileCamera:            " << (DeviceInfo->IsFileCamera ? "Yes" : "No") << std::endl;
        std::cout << "  Feature-Alpha:           " << (DeviceInfo->CheckFeature("Alpha") ? "Yes" : "No") << std::endl;
        std::cout << "  Feature-Color:           " << (DeviceInfo->CheckFeature("Color") ? "Yes" : "No") << std::endl;
        std::cout << "  Status:                  "
            << (DeviceInfo->Status.Attached ? "Attached to PhoXi Control. " : "Not Attached to PhoXi Control. ")
            << (DeviceInfo->Status.Ready    ? "Ready to connect"            : "Occupied")
            << std::endl;
    }
    std::cout << "------------------------------------------------" << std::endl << std::endl;
}

/** * @brief select how to connect
	* @param None
 	* @return None
**	**/
void photoneo_controller::ConnectPhoXiDevice(void)
{
    for (;;)
    {
        std::cout << "Please enter the number of the way to connect to your device from this possibilities:" << std::endl;
        std::cout << "  1. Connect by Hardware Identification Number" << std::endl;
        std::cout << "  2. Connect by Index listed from GetDeviceList call" << std::endl;
        std::cout << "  3. Connect by IP address" << std::endl;
        std::cout << "  4. Connect first device Attached to PhoXi Control - if any" << std::endl;
        std::cout << "  5. Connect to file camera in folder: " << FileCameraFolder << std::endl;
        std::cout << "  6. Refresh GetDeviceList" << std::endl;
        std::cout << "Please enter the choice: ";

        std::size_t Index;
        if (!ReadLine(Index))
        {
            std::cout << "Incorrect input!" << std::endl;
            continue;
        }

        switch (Index)
        {
            case 1:
                ConnectPhoXiDeviceBySerial();
                break;
            case 2:
                ConnectPhoXiDeviceByPhoXiDeviceInformationEntry();
                break;
            case 3:
                ConnectPhoXiDeviceByIPAddress();
                break;
            case 4:
                ConnectFirstAttachedPhoXiDevice();
                break;
            case 5:
                ConnectPhoXiFileCamera();
                break;
            case 6:
                GetAvailableDevices();
                break;
            default:
                continue;
        }
        if (PhoXiDevice && PhoXiDevice->isConnected())
        {
            std::cout << "You are connected to " << std::string(PhoXiDevice->GetType())
                << " with Hardware Identification " << std::string(PhoXiDevice->HardwareIdentification)
                << std::endl;
            std::cout << "------------------------------------------------" << std::endl << std::endl;
            break;
        }
    }
}

/** * @brief connect using device Hardware-Identification
	* @param None
 	* @return None
**	**/
void photoneo_controller::ConnectPhoXiDeviceBySerial(void)
{
    std::cout << "Please enter the Hardware Identification Number: ";
    std::string HardwareIdentification;
    if (!ReadLine(HardwareIdentification))
    {
        std::cout << "Incorrect input!" << std::endl;
        return;
    }

    pho::api::PhoXiTimeout Timeout = pho::api::PhoXiTimeout::ZeroTimeout;
    PhoXiDevice = Factory.CreateAndConnect(HardwareIdentification, Timeout);
    if (PhoXiDevice)
    {
        std::cout << "Connection to the device " << HardwareIdentification << " was Successful!" << std::endl;
    }
    else
    {
        std::cout << "Connection to the device " << HardwareIdentification << " was Unsuccessful!" << std::endl;
    }
}

/** * @brief connect using device number
	* @param None
 	* @return None
**	**/
void photoneo_controller::ConnectPhoXiDeviceByPhoXiDeviceInformationEntry(void)
{
    std::cout << "Please enter the Index listed from GetDeviceList call: ";

    std::size_t Index;
    if (!ReadLine(Index))
    {
        std::cout << "Incorrect input!" << std::endl;
        return;
    }

    if (Index >= DeviceList.size())
    {
        std::cout << "Bad Index, or not number!" << std::endl;
        return;
    }

    PhoXiDevice = Factory.Create(DeviceList[Index]);
    if (!PhoXiDevice)
    {
        std::cout << "Device " << DeviceList[Index].HWIdentification << " was not created" << std::endl;
        return;
    }

    if (PhoXiDevice->Connect())
    {
        std::cout << "Connection to the device " << DeviceList[Index].HWIdentification << " was Successful!" << std::endl;
    }
    else
    {
        std::cout << "Connection to the device " << DeviceList[Index].HWIdentification << " was Unsuccessful!" << std::endl;
    }
}

/** * @brief connect using device IP
	* @param None
 	* @return None
**	**/
void photoneo_controller::ConnectPhoXiDeviceByIPAddress(void)
{
    std::cout << "Please enter device type:" << std::endl;
    std::cout << "  1. PhoXi Scanner" << std::endl;
    std::cout << "  2. PhoXi MotionCam3D" << std::endl;
    std::cout << "Please enter your choice: ";
    int type = 0;
    if (!ReadLine(type))
    {
        std::cout << "Incorrect input!" << std::endl;
        return;
    }

    std::string deviceType;
    using PhoXiDeviceType = pho::api::PhoXiDeviceType;
    switch(type)
    {
        case 1:
            deviceType = static_cast<std::string>(PhoXiDeviceType(PhoXiDeviceType::PhoXiScanner));
            break;
        case 2:
            deviceType = static_cast<std::string>(PhoXiDeviceType(PhoXiDeviceType::MotionCam3D));
            break;
        default:
            std::cout << "Incorrect input!" << std::endl;
            return;
    }

    std::cout << std::endl << "Please enter new device ID: ";
    std::string HWIdentification;
    if (!ReadLine(HWIdentification))
    {
        std::cout << "Incorrect input!" << std::endl;
        return;
    }

    std::cout << std::endl << "Please enter the IP (v4 or v6) address: ";
    std::string Ip;
    if (!ReadLine(Ip))
    {
        std::cout << "Incorrect input!" << std::endl;
        return;
    }

    PhoXiDevice = Factory.CreateAndConnect(HWIdentification, deviceType, Ip);
    if (PhoXiDevice)
    {
        std::cout << "Connection to the device " << HWIdentification << " at " << Ip << " was Successful!" << std::endl;
    }
    else
    {
        std::cout << "Connection to the device " << HWIdentification << " at " << Ip << " was Unsuccessful!" << std::endl;
    }
}

/** * @brief connect to the first device in the list
	* @param None
 	* @return None
**	**/
void photoneo_controller::ConnectFirstAttachedPhoXiDevice(void)
{
    PhoXiDevice = Factory.Create(DeviceList[0]);
    if (!PhoXiDevice)
    {
        std::cout << "Device " << DeviceList[0].HWIdentification << " was not created" << std::endl;
        return;
    }

    if (PhoXiDevice->Connect())
        std::cout << "Connection to the device " << DeviceList[0].HWIdentification << " was Successful!" << std::endl;
    else
        std::cout << "Connection to the device " << DeviceList[0].HWIdentification << " was Unsuccessful!" << std::endl;
}

/** * @brief connect using device camera-file
	* @param None
 	* @return None
**	**/
void photoneo_controller::ConnectPhoXiFileCamera(void)
{
    std::vector<std::string> prawFolder { FileCameraFolder };
    const auto name = "TestFileCamera";
    const auto fileCameraName = Factory.AttachFileCamera(name, prawFolder);

    if (fileCameraName.empty())
    {
        std::cout << "Could not create file camera! Check whether praw files are in the specified folder: " << prawFolder[0] << std::endl;
        return;
    }

    PhoXiDevice = Factory.CreateAndConnect(fileCameraName, pho::api::PhoXiTimeout::Infinity);
    if (PhoXiDevice)
    {
        std::cout << "Connection to the device " << static_cast<std::string>(PhoXiDevice->HardwareIdentification) << " was Successful!" << std::endl;
        // In file camera you can't change settings thus we stop the program flow
        CorrectDisconnect();
    }
    else
    {
        std::cout << "There is no attached device, or the device is not ready!" << std::endl;
    }
}

/** * @brief display and query about the current device function
	* @param None
 	* @return None
**	**/
void photoneo_controller::BasicDeviceState(void)
{
    /* Check if the device is connected */
    if (!PhoXiDevice || !PhoXiDevice->isConnected())
    {
        std::cout << "Device is not created, or not connected!" << std::endl;
        return;
    }

    std::cout << "  Work Status:" << std::endl;
    std::cout << "    "
        << (PhoXiDevice->isAcquiring() ? "Device is in acquisition mode" : "Device is not in acquisition mode")
        << std::endl;

    std::vector <std::string> SupportedFeatures = PhoXiDevice->Features.GetSupportedFeatures();
    std::cout << "  This device have these features supported:";
    for (for_count = 0; for_count < SupportedFeatures.size(); ++for_count)
    {
        std::cout << " " << SupportedFeatures[for_count] << ";";
    }
    std::cout << std::endl << std::endl;

    /* Retrieve  all current Device function */
    if (PhoXiDevice->HardwareIdentification.isEnabled() && PhoXiDevice->HardwareIdentification.CanGet())
    {
        std::string HardwareIdentification = PhoXiDevice->HardwareIdentification;
        if (!PhoXiDevice->HardwareIdentification.isLastOperationSuccessful())
        {
            throw std::runtime_error(PhoXiDevice->HardwareIdentification.GetLastErrorMessage().c_str());
        }
        std::cout << "  HardwareIdentification: " << HardwareIdentification << std::endl;
    }

    /* ask the feature if it is implemented and if it is possible to Get or Set the feature value */
    /* ask PhoXiCapturingMode */
    if (PhoXiDevice->CapturingMode.isEnabled() && PhoXiDevice->CapturingMode.CanGet())
    {
        pho::api::PhoXiCapturingMode CapturingMode = PhoXiDevice->CapturingMode;
        //You can ask the feature, if the last performed operation was successful
        if (!PhoXiDevice->CapturingMode.isLastOperationSuccessful())
        {
            throw std::runtime_error(PhoXiDevice->CapturingMode.GetLastErrorMessage().c_str());
        }
        pho::api::PhoXiSize Resolution = CapturingMode.Resolution;
        //You can also access the resolution by PhoXiDevice->Resolution;
        std::cout << "  CapturingMode: " << std::endl;
        std::cout << "    Resolution:" << std::endl;
        std::cout << "      Width: "   << Resolution.Width << std::endl; /*PhoXiDevice->Resolution->Width*/
        std::cout << "      Height: "  << Resolution.Height << std::endl; /*PhoXiDevice->Resolution->Height*/
    }
    /* ask PhoXiCapturingMode */
    if (PhoXiDevice->SupportedCapturingModes.isEnabled() && PhoXiDevice->SupportedCapturingModes.CanGet())
    {
        std::vector <pho::api::PhoXiCapturingMode> SupportedCapturingModes = PhoXiDevice->SupportedCapturingModes;
        if (!PhoXiDevice->SupportedCapturingModes.isLastOperationSuccessful())
        {
            throw std::runtime_error(PhoXiDevice->SupportedCapturingModes.GetLastErrorMessage().c_str());
        }
        std::cout << "  SupportedCapturingModes: " << std::endl;
        for (for_count = 0; for_count < SupportedCapturingModes.size(); ++for_count)
        {
            std::cout << "    (" 
                << std::to_string(SupportedCapturingModes[for_count].Resolution.Width) << " x "
                << std::to_string(SupportedCapturingModes[for_count].Resolution.Height) << ")"
                << std::endl;
        }
    }
    /* ask PhoXiTriggerMode */
    if (PhoXiDevice->TriggerMode.isEnabled() && PhoXiDevice->TriggerMode.CanGet())
    {
        pho::api::PhoXiTriggerMode TriggerMode = PhoXiDevice->TriggerMode;
        if (!PhoXiDevice->TriggerMode.isLastOperationSuccessful())
        {
            throw std::runtime_error(PhoXiDevice->TriggerMode.GetLastErrorMessage().c_str());
        }
        std::cout << "  TriggerMode: " << std::string(TriggerMode) << std::endl;
    }
    /* ask PhoXiTimeout */
    if (PhoXiDevice->Timeout.isEnabled() && PhoXiDevice->Timeout.CanGet())
    {
        pho::api::PhoXiTimeout Timeout = PhoXiDevice->Timeout;
        if (!PhoXiDevice->Timeout.isLastOperationSuccessful())
        {
            throw std::runtime_error(PhoXiDevice->Timeout.GetLastErrorMessage().c_str());
        }
        std::cout << "  Timeout: " << std::string(Timeout) << std::endl;
    }
    /* ask PhoXiCapturingSettings */
    if (PhoXiDevice->CapturingSettings.isEnabled() && PhoXiDevice->CapturingSettings.CanGet())
    {
        pho::api::PhoXiCapturingSettings CapturingSettings = PhoXiDevice->CapturingSettings;
        if (!PhoXiDevice->CapturingSettings.isLastOperationSuccessful())
        {
            throw std::runtime_error(PhoXiDevice->CapturingSettings.GetLastErrorMessage().c_str());
        }
        PrintCapturingSettings(CapturingSettings);
    }
    /* ask PhoXiProcessingSettings */
    if (PhoXiDevice->ProcessingSettings.isEnabled() && PhoXiDevice->ProcessingSettings.CanGet())
    {
        pho::api::PhoXiProcessingSettings ProcessingSettings = PhoXiDevice->ProcessingSettings;
        if (!PhoXiDevice->ProcessingSettings.isLastOperationSuccessful())
        {
            throw std::runtime_error(PhoXiDevice->ProcessingSettings.GetLastErrorMessage().c_str());
        }
        PrintProcessingSettings(ProcessingSettings);
    }
    /* ask PhoXiCoordinatesSettings */
    if (PhoXiDevice->CoordinatesSettings.isEnabled() && PhoXiDevice->CoordinatesSettings.CanGet())
    {
        pho::api::PhoXiCoordinatesSettings CoordinatesSettings = PhoXiDevice->CoordinatesSettings;
        if (!PhoXiDevice->CoordinatesSettings.isLastOperationSuccessful())
        {
            throw std::runtime_error(PhoXiDevice->CoordinatesSettings.GetLastErrorMessage().c_str());
        }
        PrintCoordinatesSettings(CoordinatesSettings);
    }
    /* ask PhoXiCalibrationSettings */
    if (PhoXiDevice->CalibrationSettings.isEnabled() && PhoXiDevice->CalibrationSettings.CanGet())
    {
        pho::api::PhoXiCalibrationSettings CalibrationSettings = PhoXiDevice->CalibrationSettings;
        if (!PhoXiDevice->CalibrationSettings.isLastOperationSuccessful())
        {
            throw std::runtime_error(PhoXiDevice->CalibrationSettings.GetLastErrorMessage().c_str());
        }
        PrintCalibrationSettings(CalibrationSettings, "Projector");
    }
    /* ask PhoXiCalibrationSettings */
    if (PhoXiDevice->ColorCameraCalibrationSettings.isEnabled() && PhoXiDevice->ColorCameraCalibrationSettings.CanGet())
    {
        pho::api::PhoXiAdditionalCameraCalibration CalibrationSettings = PhoXiDevice->ColorCameraCalibrationSettings;
        if (!PhoXiDevice->ColorCameraCalibrationSettings.isLastOperationSuccessful())
        {
            throw std::runtime_error(PhoXiDevice->ColorCameraCalibrationSettings.GetLastErrorMessage().c_str());
        }
        PrintAdditionalCalibrationSettings(CalibrationSettings, "ColorCamera");
    }
    /* ask FrameOutputSettings */
    if (PhoXiDevice->OutputSettings.isEnabled() && PhoXiDevice->OutputSettings.CanGet())
    {
        pho::api::FrameOutputSettings OutputSettings = PhoXiDevice->OutputSettings;
        if (!PhoXiDevice->OutputSettings.isLastOperationSuccessful())
        {
            throw std::runtime_error(PhoXiDevice->OutputSettings.GetLastErrorMessage().c_str());
        }
        std::cout << "  OutputSettings: " << std::endl;
        std::cout << "    SendConfidenceMap: " << (OutputSettings.SendConfidenceMap ? "Yes" : "No") << std::endl;
        std::cout << "    SendDepthMap: "      << (OutputSettings.SendDepthMap      ? "Yes" : "No") << std::endl;
        std::cout << "    SendNormalMap: "     << (OutputSettings.SendNormalMap     ? "Yes" : "No") << std::endl;
        std::cout << "    SendPointCloud: "    << (OutputSettings.SendPointCloud    ? "Yes" : "No") << std::endl;
        std::cout << "    SendEventMap: "      << (OutputSettings.SendEventMap      ? "Yes" : "No") << std::endl;
        std::cout << "    SendTexture: "       << (OutputSettings.SendTexture       ? "Yes" : "No") << std::endl;
        std::cout << "    SendColorCameraImage: " << (OutputSettings.SendColorCameraImage ? "Yes" : "No") << std::endl;
    }
    /* ask CameraBinning */
    if (PhoXiDevice->CameraBinning.isEnabled() && PhoXiDevice->OutputSettings.CanGet())
    {
        pho::api::PhoXiSize binning = PhoXiDevice->CameraBinning;
        if (!PhoXiDevice->CameraBinning.isLastOperationSuccessful())
        {
            throw std::runtime_error(PhoXiDevice->CameraBinning.GetLastErrorMessage().c_str());
        }
        std::cout << "Camera binning height: " << binning.Height << std::endl;
        std::cout << "Camera binning width: " << binning.Width << std::endl;
    }
}

/** * @brief display about the current device information
	* @param None
 	* @return None
**	**/
void photoneo_controller::BasicDeviceInfo(void)
{
    /* Check if the device is connected */
    if (!PhoXiDevice)
    {
        std::cout << "Device is not created!" << std::endl;
        return;
    }

    std::cout << "  Info:" << std::endl;
    std::cout << "    "
        << (PhoXiDevice->Info().ConnectedToPhoXiControl() ? "Device is connected" : "Device is not connected (Error)")
        << std::endl;

    std::cout << "    "
        << "name: " << PhoXiDevice->Info().Name << std::endl;
    std::cout << "    "
        << "HWIdentification: " << PhoXiDevice->Info().HWIdentification << std::endl;
    std::cout << "    "
        << "FirmwareVersion: " << PhoXiDevice->Info().FirmwareVersion << std::endl;
    std::cout << "    "
        << "Variant: " << PhoXiDevice->Info().Variant << std::endl;
    std::cout << "    "
        << "Features: " << PhoXiDevice->Info().Features << std::endl;
    std::cout << "    "
        << (PhoXiDevice->Info().IsFileCamera ? "Device is filecam" : "Device is not filecamera")
        << std::endl;
    std::cout << "    "
        << "GetTypeHWIdentification: " << PhoXiDevice->Info().GetTypeHWIdentification() << std::endl;
}

/** * @brief capture frame in free-mode, loop 5 times
	* @param None
 	* @return None
**	**/
void photoneo_controller::Freerun_loop5(void)
{
    /* Check if the device is connected */
    if (!PhoXiDevice || !PhoXiDevice->isConnected())
    {
        std::cout << "Device is not created, or not connected!" << std::endl;
        return;
    }
    /* if it is not in Freerun mode, we need to switch the modes */
    if (PhoXiDevice->TriggerMode != pho::api::PhoXiTriggerMode::Freerun)
    {
        std::cout << "Device is not in Freerun mode" << std::endl;
        if (PhoXiDevice->isAcquiring())
        {
            std::cout << "Stopping acquisition" << std::endl;
            /* if the device is in Acquisition mode, we need to stop the acquisition */
            if (!PhoXiDevice->StopAcquisition())
            {
                throw std::runtime_error("Error in StopAcquistion");
            }
        }
        std::cout << "Switching to Freerun mode " << std::endl;
        /* modify the value of PhoXiDevice->TriggerMode to enable the device to operate */
        PhoXiDevice->TriggerMode = pho::api::PhoXiTriggerMode::Freerun;
        /* check if the operation was successful */
        if (!PhoXiDevice->TriggerMode.isLastOperationSuccessful())
        {
            throw std::runtime_error(PhoXiDevice->TriggerMode.GetLastErrorMessage().c_str());
        }
    }

    /* start the device acquisition, if necessary */
    if (!PhoXiDevice->isAcquiring())
    {
        if (!PhoXiDevice->StartAcquisition())
        {
            throw std::runtime_error("Error in StartAcquisition");
        }
    }

    /* clear the current Acquisition buffer */
    int ClearedFrames = PhoXiDevice->ClearBuffer();
    std::cout << ClearedFrames << " were cleared from the cyclic buffer" << std::endl;
    /* check the state of the Acquisition call */
    if (!PhoXiDevice->isAcquiring())
    {
        std::cout << "Device is not acquiring" << std::endl;
        return;
    }

    /* get the frame, loop 5 times */
    for (for_count = 0; for_count < 5; ++for_count)
    {
        std::cout << "Waiting for frame " << for_count << std::endl;
        /* get the frame */
        pho::api::PFrame Frame = PhoXiDevice->GetFrame();
        /* display */
        if (Frame)
        {
            PrintFrameInfo(Frame);
            PrintFrameData(Frame);
        }
        else
        {
            std::cout << "Failed to retrieve the frame!";
        }
    }
}

/** * @brief capture frame in free-mode
	* @param None
 	* @return None
**	**/
void photoneo_controller::Freerun(void)
{
    /* Check if the device is connected */
    if (!PhoXiDevice || !PhoXiDevice->isConnected())
    {
        std::cout << "Device is not created, or not connected!" << std::endl;
        return;
    }
    /* if it is not in Freerun mode, we need to switch the modes */
    if (PhoXiDevice->TriggerMode != pho::api::PhoXiTriggerMode::Freerun)
    {
        std::cout << "Device is not in Freerun mode" << std::endl;
        if (PhoXiDevice->isAcquiring())
        {
            std::cout << "Stopping acquisition" << std::endl;
            /* if the device is in Acquisition mode, we need to stop the acquisition */
            if (!PhoXiDevice->StopAcquisition())
            {
                throw std::runtime_error("Error in StopAcquistion");
            }
        }
        std::cout << "Switching to Freerun mode " << std::endl;
        /* modify the value of PhoXiDevice->TriggerMode to enable the device to operate */
        PhoXiDevice->TriggerMode = pho::api::PhoXiTriggerMode::Freerun;
        /* check if the operation was successful */
        if (!PhoXiDevice->TriggerMode.isLastOperationSuccessful())
        {
            throw std::runtime_error(PhoXiDevice->TriggerMode.GetLastErrorMessage().c_str());
        }
    }

    /* start the device acquisition, if necessary */
    if (!PhoXiDevice->isAcquiring())
        if (!PhoXiDevice->StartAcquisition())
            throw std::runtime_error("Error in StartAcquisition");

    /* clear the current Acquisition buffer */
    int ClearedFrames = PhoXiDevice->ClearBuffer();
    std::cout << ClearedFrames << " were cleared from the cyclic buffer" << std::endl;
    /* check the state of the Acquisition call */
    if (!PhoXiDevice->isAcquiring())
    {
        std::cout << "Device is not acquiring" << std::endl;
        return;
    }

    /* get the frame */
    pho::api::PFrame Frame = PhoXiDevice->GetFrame();
    /* display */
    if (Frame)
    {
        PrintFrameInfo(Frame);
        PrintFrameData(Frame);
    }
    else
        std::cout << "Failed to retrieve the frame!";
}

/** * @brief capture frame in Software-Trigger, loop 5 times
	* @param None
 	* @return None
**	**/
void photoneo_controller::SoftwareTrigger_loop5(void)
{
    /* Check if the device is connected */
    if (!PhoXiDevice || !PhoXiDevice->isConnected())
    {
        std::cout << "Device is not created, or not connected!" << std::endl;
        return;
    }
    /* if it is not in Software trigger mode, we need to switch the modes */
    if (PhoXiDevice->TriggerMode != pho::api::PhoXiTriggerMode::Software)
    {
        std::cout << "Device is not in Software trigger mode" << std::endl;
        if (PhoXiDevice->isAcquiring())
        {
            std::cout << "Stopping acquisition" << std::endl;
            /* if the device is in Acquisition mode, we need to stop the acquisition */
            if (!PhoXiDevice->StopAcquisition())
            {
                throw std::runtime_error("Error in StopAcquistion");
            }
        }
        std::cout << "Switching to Software trigger mode " << std::endl;
        /* modify the value of PhoXiDevice->TriggerMode to enable the device to operate */
        PhoXiDevice->TriggerMode = pho::api::PhoXiTriggerMode::Software;
        /* check if the operation was successful */
        if (!PhoXiDevice->TriggerMode.isLastOperationSuccessful())
        {
            throw std::runtime_error(PhoXiDevice->TriggerMode.GetLastErrorMessage().c_str());
        }
    }

    /* start the device acquisition, if necessary */
    if (!PhoXiDevice->isAcquiring())
    {
        if (!PhoXiDevice->StartAcquisition())
        {
            throw std::runtime_error("Error in StartAcquisition");
        }
    }

    /* clear the current Acquisition buffer */
    int ClearedFrames = PhoXiDevice->ClearBuffer();
    std::cout << ClearedFrames << " frames were cleared from the cyclic buffer" << std::endl;
    /* check the state of the Acquisition call */
    if (!PhoXiDevice->isAcquiring())
    {
        std::cout << "Device is not acquiring" << std::endl;
        return;
    }

    /* get the frame, loop 5 times */
    for (for_count = 0; for_count < 5; ++for_count)
    {
        std::cout << "Triggering the " << for_count << "-th frame" << std::endl;
        int FrameID = PhoXiDevice->TriggerFrame();
        if (FrameID < 0)
        {
            /* if negative number is returned trigger was unsuccessful */
            std::cout << "Trigger was unsuccessful! code=" << FrameID << std::endl;
            continue;
        }
        else
        {
            std::cout << "Frame was triggered, Frame Id: " << FrameID << std::endl;
        }

        /* call for a frame with specific FrameID */
        std::cout << "Waiting for frame " << for_count << std::endl;
        pho::api::PFrame Frame = PhoXiDevice->GetSpecificFrame(FrameID);
        /* display */
        if (Frame)
        {
            PrintFrameInfo(Frame);
            PrintFrameData(Frame); 
        }
        else
        {
            std::cout << "Failed to retrieve the frame!";
        }
    }
}

/** * @brief capture frame in Software-Trigger
	* @param None
 	* @return None
**	**/
void photoneo_controller::SoftwareTrigger(void)
{
    /* Check if the device is connected */
    if (!PhoXiDevice || !PhoXiDevice->isConnected())
    {
        std::cout << "Device is not created, or not connected!" << std::endl;
        return;
    }
    /* if it is not in Software trigger mode, we need to switch the modes */
    if (PhoXiDevice->TriggerMode != pho::api::PhoXiTriggerMode::Software)
    {
        std::cout << "Device is not in Software trigger mode" << std::endl;
        if (PhoXiDevice->isAcquiring())
        {
            std::cout << "Stopping acquisition" << std::endl;
            /* if the device is in Acquisition mode, we need to stop the acquisition */
            if (!PhoXiDevice->StopAcquisition())
            {
                throw std::runtime_error("Error in StopAcquistion");
            }
        }
        std::cout << "Switching to Software trigger mode " << std::endl;
        /* modify the value of PhoXiDevice->TriggerMode to enable the device to operate */
        PhoXiDevice->TriggerMode = pho::api::PhoXiTriggerMode::Software;
        /* check if the operation was successful */
        if (!PhoXiDevice->TriggerMode.isLastOperationSuccessful())
            throw std::runtime_error(PhoXiDevice->TriggerMode.GetLastErrorMessage().c_str());
    }

    /* start the device acquisition, if necessary */
    if (!PhoXiDevice->isAcquiring())
        if (!PhoXiDevice->StartAcquisition())
            throw std::runtime_error("Error in StartAcquisition");

    /* clear the current Acquisition buffer */
    int ClearedFrames = PhoXiDevice->ClearBuffer();
    std::cout << ClearedFrames << " frames were cleared from the cyclic buffer" << std::endl;
    /* check the state of the Acquisition call */
    if (!PhoXiDevice->isAcquiring())
    {
        std::cout << "Device is not acquiring" << std::endl;
        return;
    }

    int FrameID = PhoXiDevice->TriggerFrame();
    if (FrameID < 0)
    {
        /* if negative number is returned trigger was unsuccessful */
        std::cout << "Trigger was unsuccessful! code=" << FrameID << std::endl;
        return;
    }
    else
        std::cout << "Frame was triggered, Frame Id: " << FrameID << std::endl;

    /* call for a frame with specific FrameID */
    std::cout << "Waiting for frame " << FrameID << std::endl;
    pho::api::PFrame Frame = PhoXiDevice->GetSpecificFrame(FrameID);
    /* display */
    if (Frame)
    {
        PrintFrameInfo(Frame);
        PrintFrameData(Frame); 
    }
    else
        std::cout << "Failed to retrieve the frame!";
    std::cout << "------------------------------------------------" << std::endl << std::endl;
}

/** * @brief capture frame in Software-Trigger-Async, loop 5 times
	* @param None
 	* @return None
**	**/
void photoneo_controller::SoftwareTriggerAsyncGrab_loop5(void)
{
    std::atomic<uint64_t> AsyncFrameID;

    /* callback will be called when new frame is arrived */
    auto AsyncGetFrameCallback = [&AsyncFrameID, this](pho::api::PFrame Frame) {
        if (Frame) {
            PrintFrameInfo(Frame);
            PrintFrameData(Frame);
            AsyncFrameID = Frame->Info.FrameIndex;
        }
        else
        {
            std::cout << "Failed to retrieve the frame!" << std::endl;
        }
    };

    /* check if the device is connected */
    if (!PhoXiDevice || !PhoXiDevice->isConnected())
    {
        std::cout << "Device is not created, or not connected!" << std::endl;
        return;
    }
    /* if it is not in Software trigger mode, we need to switch the modes */
    if (PhoXiDevice->TriggerMode != pho::api::PhoXiTriggerMode::Software)
    {
        std::cout << "Device is not in Software trigger mode" << std::endl;
        if (PhoXiDevice->isAcquiring())
        {
            std::cout << "Stopping acquisition" << std::endl;
            /* if the device is in Acquisition mode, we need to stop the acquisition */
            if (!PhoXiDevice->StopAcquisition())
            {
                throw std::runtime_error("Error in StopAcquistion");
            }
        }
        std::cout << "Switching to Software trigger mode " << std::endl;
        /* modify the value of PhoXiDevice->TriggerMode to enable the device to operate */
        PhoXiDevice->TriggerMode = pho::api::PhoXiTriggerMode::Software;
        /* check if the operation was successful */
        if (!PhoXiDevice->TriggerMode.isLastOperationSuccessful())
        {
            throw std::runtime_error(PhoXiDevice->TriggerMode.GetLastErrorMessage().c_str());
        }
    }

    /* start the device acquisition, if necessary */
    if (!PhoXiDevice->isAcquiring())
    {
        if (!PhoXiDevice->StartAcquisition())
        {
            throw std::runtime_error("Error in StartAcquisition");
        }
    }
    /* clear the current Acquisition buffer */
    int ClearedFrames = PhoXiDevice->ClearBuffer();
    /* enable exclusive asynchronous frame grabbing mode with user defined notification callback */
    PhoXiDevice->EnableAsyncGetFrame(std::move(AsyncGetFrameCallback));
    /* check the state of the Acquisition call */
    if (!PhoXiDevice->isAcquiring())
    {
        std::cout << "Device is not acquiring" << std::endl;
        return;
    }

    /* get the frame, loop 5 times */
    int FrameID = -1;
    for (for_count = 0; for_count < 5; ++for_count)
    {
        std::cout << "Triggering the " << for_count << "-th frame" << std::endl;
        FrameID = PhoXiDevice->TriggerFrame();
        if (FrameID < 0)
        {
            /* if negative number is returned trigger was unsuccessful */
            std::cout << "Trigger was unsuccessful! code=" << FrameID << std::endl;
            continue;
        }
        else
        {
            std::cout << "Frame was triggered, Frame Id: " << FrameID << std::endl;
        }
    }

    /* wait for last frame catched in callback */
    while ((uint64_t)FrameID != AsyncFrameID) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    /* disable asynchronous frame grabbing and switch back to synchronous mode */
    PhoXiDevice->DisableAsyncGetFrame();
}

/** * @brief change the settings of the device,
    *        restore to the original settings after completion
    * @param None
 	* @return None
**	**/
void photoneo_controller::ChangeSettings(void)
{
    /* check if the device is connected */
    if (!PhoXiDevice || !PhoXiDevice->isConnected())
    {
        std::cout << "Device is not created, or not connected!" << std::endl;
        return;
    }
    /* Retrieve  all current Device function */
    if (!PhoXiDevice->CapturingSettings.isEnabled() 
        || !PhoXiDevice->CapturingSettings.CanSet() || !PhoXiDevice->CapturingSettings.CanGet())
    {
        std::cout << "Settings used in  are not supported by the Device Hardware, or are Read only on the specific device" << std::endl;
        return;
    }
    std::cout << "Settings change " << std::endl;

    /* change the trigger mode to Software Trigger */
    if (PhoXiDevice->TriggerMode != pho::api::PhoXiTriggerMode::Software)
    {
        if (PhoXiDevice->isAcquiring())
        {
            if (!PhoXiDevice->StopAcquisition())
            {
                throw std::runtime_error("Error in StopAcquistion");
            }
        }
        PhoXiDevice->TriggerMode = pho::api::PhoXiTriggerMode::Software;
        /* check if the operation was successful */
        if (!PhoXiDevice->TriggerMode.isLastOperationSuccessful())
        {
            throw std::runtime_error(PhoXiDevice->TriggerMode.GetLastErrorMessage().c_str());
        }
    }

    /* start the device acquisition, if necessary */
    if (!PhoXiDevice->isAcquiring())
    {
        if (!PhoXiDevice->StartAcquisition())
        {
            throw std::runtime_error("Error in StartAcquisition");
        }
    }

    int CurrentShutterMultiplier = PhoXiDevice->CapturingSettings->ShutterMultiplier;

    /* to change the setting, just assign a new value */
    PhoXiDevice->CapturingSettings->ShutterMultiplier = CurrentShutterMultiplier + 1;

    /* check if the operation succeed */
    if (!PhoXiDevice->CapturingSettings.isLastOperationSuccessful())
    {
        throw std::runtime_error(PhoXiDevice->CapturingSettings.GetLastErrorMessage().c_str());
    }

    /* get the current Output configuration */
    pho::api::FrameOutputSettings CurrentOutputSettings = PhoXiDevice->OutputSettings;
    pho::api::FrameOutputSettings NewOutputSettings = CurrentOutputSettings;
    NewOutputSettings.SendPointCloud = true;
    NewOutputSettings.SendNormalMap = true;
    NewOutputSettings.SendDepthMap = true;
    NewOutputSettings.SendConfidenceMap = true;
    NewOutputSettings.SendTexture = true;
    NewOutputSettings.SendColorCameraImage = true;
    NewOutputSettings.SendEventMap = true;
    /* send all outputs */
    PhoXiDevice->OutputSettings = NewOutputSettings;

    /* trigger the frame */
    int FrameID = PhoXiDevice->TriggerFrame();
    /* check if the frame was successfully triggered */
    if (FrameID < 0)
    {
        throw std::runtime_error("Software trigger failed! code=" + std::to_string(FrameID));
    }

    /* retrieve the frame */
    pho::api::PFrame Frame = PhoXiDevice->GetSpecificFrame(FrameID);
    if (Frame)
    {
        /* save the frame for next  */
        SampleFrame = Frame;
    }

    /* change the setting back */
    PhoXiDevice->OutputSettings = CurrentOutputSettings;
    PhoXiDevice->CapturingSettings->ShutterMultiplier = CurrentShutterMultiplier;

    if (!PhoXiDevice->CapturingSettings.isLastOperationSuccessful())
    {
        throw std::runtime_error(PhoXiDevice->CapturingSettings.GetLastErrorMessage().c_str());
    }

    /* try to change device resolution */
    if (PhoXiDevice->SupportedCapturingModes.isEnabled() && PhoXiDevice->SupportedCapturingModes.CanGet()
        && PhoXiDevice->CapturingMode.isEnabled() 
        && PhoXiDevice->CapturingMode.CanSet() && PhoXiDevice->CapturingMode.CanGet())
    {
        /* retrieve current capturing mode */
        pho::api::PhoXiCapturingMode CurrentCapturingMode = PhoXiDevice->CapturingMode;
        if (!PhoXiDevice->CapturingMode.isLastOperationSuccessful())
        {
            throw std::runtime_error(PhoXiDevice->CapturingMode.GetLastErrorMessage().c_str());
        }

        /* get all supported modes */
        std::vector <pho::api::PhoXiCapturingMode> SupportedCapturingModes = PhoXiDevice->SupportedCapturingModes;
        if (!PhoXiDevice->SupportedCapturingModes.isLastOperationSuccessful())
        {
            throw std::runtime_error(PhoXiDevice->SupportedCapturingModes.GetLastErrorMessage().c_str());
        }

        /* cycle trough all other Supported modes, change the settings and grab a frame */
        for (for_count = 0; for_count < SupportedCapturingModes.size(); ++for_count)
        {
            if (!(SupportedCapturingModes[for_count] == CurrentCapturingMode))
            {
                PhoXiDevice->CapturingMode = SupportedCapturingModes[for_count];
                if (!PhoXiDevice->CapturingMode.isLastOperationSuccessful())
                {
                    throw std::runtime_error(PhoXiDevice->CapturingMode.GetLastErrorMessage().c_str());
                }
                /* trigger Frame */
                int FrameID = PhoXiDevice->TriggerFrame();
                if (FrameID < 0)
                {
                    throw std::runtime_error("Software trigger failed! code=" + std::to_string(FrameID));
                }

                Frame = PhoXiDevice->GetSpecificFrame(FrameID);
                if (Frame)
                {
                    std::cout << "Arrived Frame Resolution: "
                        << Frame->GetResolution().Width << " x "
                        << Frame->GetResolution().Height << std::endl;
                }
            }
        }

        /* change the mode back */
        PhoXiDevice->CapturingMode = CurrentCapturingMode;
        if (!PhoXiDevice->CapturingMode.isLastOperationSuccessful())
        {
            throw std::runtime_error(PhoXiDevice->CapturingMode.GetLastErrorMessage().c_str());
        }

    }
}

/** * @brief get and set Profile
    * @param None
 	* @return None
**	**/
void photoneo_controller::GetAndSetProfile(void)
{
    SetProfile(GetSettingProfiles());
}

/** * @brief get profiles
    * @param None
 	* @return int16_t, number of obtained profiles.
**	**/
int32_t photoneo_controller::GetSettingProfiles(void)
{
    ProfilesList = PhoXiDevice->Profiles;
    if (!PhoXiDevice->Profiles.isLastOperationSuccessful())
    {
        std::cout << "Can not get profile list: " << PhoXiDevice->Profiles.GetLastErrorMessage() << std::endl;
        return (-1);
    }
    std::cout << "Get setting profiles Successully!" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << std::boolalpha;
    for( for_count=0; for_count<ProfilesList.size(); for_count++ )
        printProfilesList(for_count, ProfilesList[for_count]);

    return for_count;
}

/** * @brief set setting profiles
    * @param None
 	* @return bool, operation result
**	**/
bool photoneo_controller::SetProfile(int32_t count)
{
    std::cout << "Please enter the profile number to using:";
    std::size_t Index;
    while( (!ReadLine(Index)) || (Index>=count) )
        std::cout << "Incorrect input! Please re-enter:";

    PhoXiDevice->ActiveProfile = ProfilesList[Index].Name;
    if (PhoXiDevice->ActiveProfile.isLastOperationSuccessful())
        std::cout << "active profile set to : " << ProfilesList[Index].Name << " Soccesully" << std::endl;
    else
    {
        std::cout << "Can not set active profile: " << PhoXiDevice->ActiveProfile.GetLastErrorMessage() << std::endl;
        return false;
    }
    std::cout << "------------------------------------------------" << std::endl << std::endl;
    return true;
}

/** * @brief retrieve PointCloud information + store the Frame as a ply structure
    * @param None
 	* @return None
**	**/
void photoneo_controller::DataHandling(void)
{
    /* check if we have SampleFrame Data */
    int a=0;
    if (!SampleFrame || SampleFrame->Empty())
    {
        std::cout << "Frame does not exist, or has no content!" << std::endl;
    }

    /* we will count the number of measured points */
    if (!SampleFrame->PointCloud.Empty())
    {
        int MeasuredPoints = 0;
        pho::api::Point3_32f ZeroPoint(0.0f, 0.0f, 0.0f);
        for (int y = 0; y < SampleFrame->PointCloud.Size.Height; ++y)
        {
            for (int x = 0; x < SampleFrame->PointCloud.Size.Width; ++x)
            {
                if (SampleFrame->PointCloud[y][x] != ZeroPoint)
                {
                    MeasuredPoints++;
                }
            }
        }
        std::cout << "Your sample PointCloud has " << MeasuredPoints << " measured points." << std::endl;

        float *MyLocalCopy = new float[SampleFrame->PointCloud.GetElementsCount() * 3];

        pho::api::Point3_32f *RawPointer = SampleFrame->PointCloud.GetDataPtr();
        memcpy(MyLocalCopy, RawPointer, SampleFrame->PointCloud.GetDataSize());
        //Data are organized as a matrix of X, Y, Z floats, see the documentation for all other types

        delete[] MyLocalCopy;
        //Data from SampleFrame, or all other frames that are returned by the device are copied from the Cyclic buffer and will remain in the memory until the Frame will go out of scope
        //You can specifically call SampleFrame->PointCloud.Clear() to release some of the data
    }

    //You can store the Frame as a ply structure
    //If you don't specify Output folder, the PLY file will be saved in the same folder where the FullAPI executable is located
    const auto outputFolder = OutputFolder.empty() ? std::string() : OutputFolder + DELIMITER;
    const auto sampleFramePly = outputFolder + "SampleFrame.ply";
    std::cout << "Saving frame as 'SampleFrame.ply'" << std::endl;
    if (SampleFrame->SaveAsPly(sampleFramePly, true, true))
    {
        std::cout << "Saved sample frame as PLY to: " << sampleFramePly << std::endl;
    }
    else
    {
        std::cout << "Could not save sample frame as PLY to " << sampleFramePly << " !" << std::endl;
    }
    //You can save scans to any format, you only need to specify path + file name
    //API will look at extension and save the scan in the correct format
    //You can define which options to save (PointCloud, DepthMap, ...) in PhoXi Control application -> Saving options
    //This method has a an optional 2nd parameter: FrameId
    //Use this option to save other scans than the last one
    //Absolute path is prefered
    //If you don't specify Output folder the file will be saved to %APPDATA%\PhotoneoPhoXiControl\ folder on Windows or ~/.PhotoneoPhoXiControl/ on Linux
    const auto sampleFrameAnyFormat = outputFolder + "OtherSampleFrame.tif";
    if (PhoXiDevice->SaveLastOutput(sampleFrameAnyFormat))
    {
        std::cout << "Saved sample frame to: " << sampleFrameAnyFormat << std::endl;
    }
    else
    {
        std::cout << "Could not save sample frame to: " << sampleFrameAnyFormat << " !" << std::endl;
    }

    //If you want OpenCV support, you need to link appropriate libraries and add OpenCV include directory
    //To add the support, add #define PHOXI_OPENCV_SUPPORT before include of PhoXi include files
#ifdef PHOXI_OPENCV_SUPPORT
    if (!SampleFrame->PointCloud.Empty())
    {
        cv::Mat PointCloudMat;
        if (SampleFrame->PointCloud.ConvertTo(PointCloudMat))
        {
            cv::Point3f MiddlePoint = PointCloudMat.at<cv::Point3f>(PointCloudMat.rows/2, PointCloudMat.cols/2);
            std::cout << "Middle point: " << MiddlePoint.x << "; " << MiddlePoint.y << "; " << MiddlePoint.z;
        }
    }
#endif
    //If you want PCL support, you need to link appropriate libraries and add PCL include directory
    //To add the support, add #define PHOXI_PCL_SUPPORT before include of PhoXi include files
#ifdef PHOXI_PCL_SUPPORT
    //The PCL convert will convert the appropriate data into the pcl PointCloud based on the Point Cloud type
    pcl::PointCloud<pcl::PointXYZRGBNormal> MyPCLCloud;
    SampleFrame->ConvertTo(MyPCLCloud);
#endif
}

/** * @brief disconnect from the current device
    * @param None
 	* @return None
**	**/
void photoneo_controller::CorrectDisconnect(void)
{
    if (!PhoXiDevice->isConnected()) {
        std::cout << "Device is not connected." << std::endl;
        return;
    }

    //The whole API is designed on C++ standards, using smart pointers and constructor/destructor logic
    //All resources will be closed automatically, but the device state will not be affected -> it will remain connected in PhoXi Control and if in freerun, it will remain Scanning
    //To Stop the device, just
    PhoXiDevice->StopAcquisition();
    //If you want to disconnect and logout the device from PhoXi Control, so it will then be available for other devices, call
    std::cout << "Do you want to logout the device? (0 if NO / 1 if YES) ";
    bool Entry;
    if (!ReadLine(Entry))
    {
        return;
    }
    PhoXiDevice->Disconnect(Entry);
    //The call PhoXiDevice without Logout will be called automatically by destructor
}

/** * @brief display setting profile
    * @param PhoXiProfileDescriptor, profile profile descriptor
 	* @return None
**	**/
void photoneo_controller::printProfilesList(size_t count, const pho::api::PhoXiProfileDescriptor &profile)
{
    std::cout << "Profile [" << count << "] :" << std::endl;
    std::cout << "    Name: "<< profile.Name << std::endl;
    std::cout << "    Is factory profile: " << profile.IsFactory << std::endl;
}


void photoneo_controller::PrintFrameInfo(const pho::api::PFrame &Frame)
{
    const pho::api::FrameInfo &FrameInfo = Frame->Info;
    std::cout << "  Frame params: " << std::endl;
    std::cout << "    Frame Index: " << FrameInfo.FrameIndex << std::endl;
    std::cout << "    Frame Timestamp: " << FrameInfo.FrameTimestamp << " ms" << std::endl;
    std::cout << "    Frame Acquisition duration: " << FrameInfo.FrameDuration << " ms" << std::endl;
    std::cout << "    Frame Computation duration: " << FrameInfo.FrameComputationDuration << " ms" << std::endl;
    std::cout << "    Frame Transfer duration: " << FrameInfo.FrameTransferDuration << " ms" << std::endl;
    std::cout << "    Sensor Position: ["
        << FrameInfo.SensorPosition.x << "; "
        << FrameInfo.SensorPosition.y << "; "
        << FrameInfo.SensorPosition.z << "]"
        << std::endl;
    PrintMatrix("Camera calibration matrix", FrameInfo.CameraMatrix);
    PrintDistortionCoefficients("Frame Distortion Coefficients", FrameInfo.DistortionCoefficients);
    std::cout << "    Camera binning height: " << FrameInfo.CameraBinning.Height << std::endl;
    std::cout << "    Camera binning width: " << FrameInfo.CameraBinning.Width << std::endl;
    std::cout << "    Total scan count: " << FrameInfo.TotalScanCount << std::endl;
    std::cout << "    Color Camera Position: ["
        << FrameInfo.ColorCameraPosition.x << "; "
        << FrameInfo.ColorCameraPosition.y << "; "
        << FrameInfo.ColorCameraPosition.z << "]"
        << std::endl;
}

void photoneo_controller::PrintFrameData(const pho::api::PFrame &Frame)
{
    if (Frame->Empty())
    {
        std::cout << "Frame is empty.";
        return;
    }
    std::cout << "  Frame data: " << std::endl;
    if (!Frame->PointCloud.Empty())
    {
        std::cout << "    PointCloud:    ("
            << Frame->PointCloud.Size.Width << " x "
            << Frame->PointCloud.Size.Height << ") Type: "
            << Frame->PointCloud.GetElementName()
            << std::endl;
    }
    if (!Frame->NormalMap.Empty())
    {
        std::cout << "    NormalMap:     ("
            << Frame->NormalMap.Size.Width << " x "
            << Frame->NormalMap.Size.Height << ") Type: "
            << Frame->NormalMap.GetElementName()
            << std::endl;
    }
    if (!Frame->DepthMap.Empty())
    {
        std::cout << "    DepthMap:      ("
            << Frame->DepthMap.Size.Width << " x "
            << Frame->DepthMap.Size.Height << ") Type: "
            << Frame->DepthMap.GetElementName()
            << std::endl;
    }
    if (!Frame->ConfidenceMap.Empty())
    {
        std::cout << "    ConfidenceMap: ("
            << Frame->ConfidenceMap.Size.Width << " x "
            << Frame->ConfidenceMap.Size.Height << ") Type: "
            << Frame->ConfidenceMap.GetElementName()
            << std::endl;
    }
    if (!Frame->Texture.Empty())
    {
        std::cout << "    Texture:       ("
            << Frame->Texture.Size.Width << " x "
            << Frame->Texture.Size.Height << ") Type: "
            << Frame->Texture.GetElementName()
            << std::endl;
    }
    if (!Frame->TextureRGB.Empty())
    {
        std::cout << "    TextureRGB:       ("
            << Frame->TextureRGB.Size.Width << " x "
            << Frame->TextureRGB.Size.Height << ") Type: "
            << Frame->TextureRGB.GetElementName()
            << std::endl;
    }
    if (!Frame->ColorCameraImage.Empty())
    {
        std::cout << "    ColorCameraImage:       ("
            << Frame->ColorCameraImage.Size.Width << " x "
            << Frame->ColorCameraImage.Size.Height << ") Type: "
            << Frame->ColorCameraImage.GetElementName()
            << std::endl;
    }
}

void photoneo_controller::PrintCapturingSettings(const pho::api::PhoXiCapturingSettings &CapturingSettings)
{
    std::cout << "  CapturingSettings: "         << std::endl;
    std::cout << "    ShutterMultiplier: "       << CapturingSettings.ShutterMultiplier << std::endl;
    std::cout << "    ScanMultiplier: "          << CapturingSettings.ScanMultiplier << std::endl;
    std::cout << "    CameraOnlyMode: "          << CapturingSettings.CameraOnlyMode << std::endl;
    std::cout << "    AmbientLightSuppression: " << CapturingSettings.AmbientLightSuppression << std::endl;
    std::cout << "    MaximumFPS: "              << CapturingSettings.MaximumFPS << std::endl;
    std::cout << "    SinglePatternExposure: "   << CapturingSettings.SinglePatternExposure << std::endl;
    std::cout << "    CodingStrategy: "          << std::string(CapturingSettings.CodingStrategy) << std::endl;
    std::cout << "    CodingQuality: "           << std::string(CapturingSettings.CodingQuality) << std::endl;
    std::cout << "    TextureSource: "           << std::string(CapturingSettings.TextureSource) << std::endl;
    std::cout << "    SinglePatternExposure: "   << CapturingSettings.SinglePatternExposure << std::endl;
    std::cout << "    MaximumFPS: "              << CapturingSettings.MaximumFPS << std::endl;
    std::cout << "    LaserPower: "              << CapturingSettings.LaserPower << std::endl;
    std::cout << "    LEDPower: "                << CapturingSettings.LEDPower << std::endl;
    std::cout << "    ProjectionOffsetLeft: "    << CapturingSettings.ProjectionOffsetLeft << std::endl;
    std::cout << "    ProjectionOffsetRight: "   << CapturingSettings.ProjectionOffsetRight << std::endl;
    std::cout << "    HardwareTrigger: "         << CapturingSettings.HardwareTrigger << std::endl;
    std::cout << "    HardwareTriggerSignal: "   << CapturingSettings.HardwareTriggerSignal << std::endl;
}

void photoneo_controller::PrintProcessingSettings(const pho::api::PhoXiProcessingSettings &ProcessingSettings)
{
    std::cout << "  ProcessingSettings: "           << std::endl;
    std::cout << "    Confidence (MaxInaccuracy): " << ProcessingSettings.Confidence << std::endl;
    std::cout << "    CalibrationVolumeOnly: "      << ProcessingSettings.CalibrationVolumeOnly << std::endl;
    PrintVector("MinCameraSpace(in DataCutting)", ProcessingSettings.ROI3D.CameraSpace.min);
    PrintVector("MaxCameraSpace(in DataCutting)", ProcessingSettings.ROI3D.CameraSpace.max);
    PrintVector("MinPointCloudSpace (in DataCutting)", ProcessingSettings.ROI3D.PointCloudSpace.min);
    PrintVector("MaxPointCloudSpace (in DataCutting)", ProcessingSettings.ROI3D.PointCloudSpace.max);
    std::cout << "    MaxCameraAngle: "             << ProcessingSettings.NormalAngle.MaxCameraAngle << std::endl;
    std::cout << "    MaxProjectionAngle: "         << ProcessingSettings.NormalAngle.MaxProjectorAngle << std::endl;
    std::cout << "    MinHalfwayAngle: "            << ProcessingSettings.NormalAngle.MinHalfwayAngle << std::endl;
    std::cout << "    MaxHalfwayAngle: "            << ProcessingSettings.NormalAngle.MaxHalfwayAngle << std::endl;
    std::cout << "    SurfaceSmoothness: "          << std::string(ProcessingSettings.SurfaceSmoothness) << std::endl;
    std::cout << "    NormalsEstimationRadius: "    << ProcessingSettings.NormalsEstimationRadius << std::endl;
    std::cout << "    InterreflectionsFiltering: "  << ProcessingSettings.InterreflectionsFiltering << std::endl;
}

void photoneo_controller::PrintCoordinatesSettings(const pho::api::PhoXiCoordinatesSettings &CoordinatesSettings)
{
    std::cout << "  CoordinatesSettings: " << std::endl;
    PrintMatrix("CustomRotationMatrix", CoordinatesSettings.CustomTransformation.Rotation);
    PrintVector("CustomTranslationVector", CoordinatesSettings.CustomTransformation.Translation);
    PrintVector("RobotTranslationVector", CoordinatesSettings.RobotTransformation.Translation);
    std::cout << "    CoordinateSpace: "   << std::string(CoordinatesSettings.CoordinateSpace) << std::endl;
    std::cout << "    RecognizeMarkers: "  << CoordinatesSettings.RecognizeMarkers << std::endl;
    std::cout << "    SaveTransformations: " << CoordinatesSettings.SaveTransformations << std::endl;
    std::cout << "    MarkerScale: "
        << CoordinatesSettings.MarkersSettings.MarkerScale.Width << " x "
        << CoordinatesSettings.MarkersSettings.MarkerScale.Height
        << std::endl;
}

void photoneo_controller::PrintCalibrationSettings(const pho::api::PhoXiCalibrationSettings &CalibrationSettings, const std::string &source)
{
    std::cout << "Source: " << source << std::endl;
    std::cout << "  CalibrationSettings: " << std::endl;
    std::cout << "    FocusLength: " << CalibrationSettings.FocusLength << std::endl;
    std::cout << "    PixelSize: "
        << CalibrationSettings.PixelSize.Width << " x "
        << CalibrationSettings.PixelSize.Height
        << std::endl;
    PrintMatrix("CameraMatrix", CalibrationSettings.CameraMatrix);
    PrintDistortionCoefficients("DistortionCoefficients", CalibrationSettings.DistortionCoefficients);
}

void photoneo_controller::PrintAdditionalCalibrationSettings(const pho::api::PhoXiAdditionalCameraCalibration& CalibrationSettings, const std::string& source) {
    std::cout << "Additional camera calibration settings: " << source << std::endl;
    PrintCalibrationSettings(CalibrationSettings.CalibrationSettings, source);
    PrintResolution(CalibrationSettings.CameraResolution);
    PrintCoordinateTransformation(CalibrationSettings.CoordinateTransformation);
}

void photoneo_controller::PrintCoordinateTransformation(const pho::api::PhoXiCoordinateTransformation& transformation) {
    PrintMatrix("RotationMatrix", transformation.Rotation);
    PrintVector("TranslationVector", transformation.Translation);
}

void photoneo_controller::PrintResolution(const pho::api::PhoXiSize& Resolution) {
    std::cout << "    Resolution: ("
        << Resolution.Width
        << "x"
        << Resolution.Height
        << ")" << std::endl;
}

void photoneo_controller::PrintVector(const std::string &name, const pho::api::Point3_64f &vector)
{
    std::cout << "    " << name << ": ["
        << vector.x << "; "
        << vector.y << "; "
        << vector.z << "]"
        << std::endl;
}

void photoneo_controller::PrintMatrix(const std::string &name, const pho::api::CameraMatrix64f &matrix)
{
    if (matrix.Empty())
    {
        std::cout << "    " << name << ": [empty]" << std::endl;
    }
    else
    {
        std::cout << "    " << name << ": "
            << std::endl << "      ["
            << matrix[0][0] << ", "
            << matrix[0][1] << ", "
            << matrix[0][2] << "]"

            << std::endl << "      ["
            << matrix[1][0] << ", "
            << matrix[1][1] << ", "
            << matrix[1][2] << "]"

            << std::endl << "      ["
            << matrix[2][0] << ", "
            << matrix[2][1] << ", "
            << matrix[2][2] << "]"
            << std::endl;
    }
}

void photoneo_controller::PrintDistortionCoefficients(const std::string& name, const std::vector<double>& distCoeffs)
{
    std::cout << "    " << name << ": " << std::endl;
    std::cout << "      Format is the following: " << std::endl;
    std::cout << "      (k1, k2, p1, p2[, k3[, k4, k5, k6[, s1, s2, s3, s4[, tx, ty]]]])" << std::endl;

    std::stringstream currentDistCoeffsSS;
    int brackets = 0;
    currentDistCoeffsSS << "(";
    currentDistCoeffsSS << distCoeffs[0];
    for (for_count = 1; for_count < distCoeffs.size(); ++for_count)
    {
        if (for_count == 4 || for_count == 5 || for_count == 8 || for_count == 12 || for_count == 14)
        {
            currentDistCoeffsSS << "[";
            ++brackets;
        }
        currentDistCoeffsSS << ", " << distCoeffs[for_count];
    }
    for (for_count = 0; for_count < brackets; ++for_count)
    {
        currentDistCoeffsSS << "]";
    }
    currentDistCoeffsSS << ")";
    std::cout << "      " << currentDistCoeffsSS.str() << std::endl;
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF photoneo_controller.cpp ***** */
