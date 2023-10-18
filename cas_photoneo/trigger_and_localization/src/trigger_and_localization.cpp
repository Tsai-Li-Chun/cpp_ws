#include <vector>
#include <string>
#include <iostream>

#include "PhoXi.h"

/* print Devices Information function */
void printDeviceInfoList(const pho::api::PhoXiDeviceInformation);
/* software trigger single scan function */
bool SoftwareTrigger_SingleScan(const pho::api::PPhoXi);

/** * @brief  Program entry point.
 	* @param argc(int) Number of input parameters
 	* @param argv(int) input parameters
 	* @return (int) Program Error.
**	**/
int main(int argc, char *argv[])
{
    /* create PhoXiControl software top class object */
    pho::api::PhoXiFactory Factory;
    /* to determine whether the PhoXiControl is running or not  */
    if( !(Factory.isPhoXiControlRunning()) )
    {   /* if PhoXiXontrol not run, exit the program */
        std::cout << "PhoXiControl is not running" << std::endl;
        return 0;
    }
    else
        std::cout << "PhoxiControl is running!" << std::endl;

    /* get list of available devices on the network */
    std::vector<pho::api::PhoXiDeviceInformation> DeviceList = Factory.GetDeviceList();
    if(DeviceList.empty())
    {   /* if not devices on the network... */
        std::cout << "PhoXi Factory has found 0 devices" << std::endl;
        return 0;
    }
    /* print Devices Information */
    std::size_t i;
    for( i=0; i<DeviceList.size(); i++ )
    {
        std::cout << "Device: " << i << std::endl;
        printDeviceInfoList(DeviceList[i]);
    }

    int device_number;
    /* create PhoXiControl device control class object */
    /* try to connect device opened in PhoXiControl, if any */
    pho::api::PPhoXi PhoXiDevice = Factory.CreateAndConnectFirstAttached();
    if(PhoXiDevice)
    {   /* if connection already exist */
        std::cout << "You have already Device opened in PhoXicontrol, connected to Device: "
            << (std::string)PhoXiDevice->HardwareIdentification << std::endl;
    }
    else
    {   /* if the connection does not exist, connect according to the input number */
        std::cout << "You have no Device opened in PhoXiControl, Please select the Device number to connect: ";
        std::cin >> device_number;
        PhoXiDevice = Factory.CreateAndConnect(DeviceList[device_number].HWIdentification);
    }

    /* check if device was created */
    if(PhoXiDevice) /* if device create success */
        std::cout << "Device create Successfully" << std::endl;
    else    
    {   /* if device create failed, exit the program */
        std::cout << "Device create Failed" << std::endl;
        return 0;
    }

    /* check if device is connected */
    if( PhoXiDevice->isConnected() )    /* if device connect success */
        std::cout << "Your device have connected, device is: "
            << (std::string)PhoXiDevice->HardwareIdentification << std::endl;
    else
    {   /* if device connect failed, exit the program */
        std::cout << "Failed, Your device is not connected." << std::endl;
        return 0;
    }

    /* software single scan trigger */
    if(SoftwareTrigger_SingleScan(PhoXiDevice))
        std::cout << "Scan Success" << std::endl;
    else
        std::cout << "Scan Failed" << std::endl;

    std::cin >> device_number; std::cout<<std::endl;
    /* Disconnect PhoXiControl device */
    PhoXiDevice->Disconnect(true,true);
    /* if disconnection fails */
    if(PhoXiDevice->isConnected())
    {   /* if disconnection fails, exit program */
        std::cout << "The device failed to disconnect" << std::endl;
        return 0;
    }


    return 0;
}

/** * @brief print Devices Information function.
 	* @param PhoXiDeviceInformation Devices Information.
 	* @return None.
**	**/
void printDeviceInfoList(const pho::api::PhoXiDeviceInformation devicelist)
{
    std::cout << "  Name:                    " << devicelist.Name << std::endl;
    std::cout << "  Hardware Identification: " << devicelist.HWIdentification << std::endl;
    std::cout << "  Type:                    " << std::string(devicelist.Type) << std::endl;
    std::cout << "  Firmware Version:        " << devicelist.FirmwareVersion << std::endl;
    std::cout << "  Variant:                 " << devicelist.Variant << std::endl;
    std::cout << "  File Camera:             " << (devicelist.IsFileCamera? "Yes" : "No") << std::endl;
    std::cout << "  Feature:                 " << devicelist.Features << std::endl;
    std::cout << "  Status:                  "
        << (devicelist.Status.Attached? "Attached to PhoXi Control. " : "Not Attached to PhoXi Control. ")
        << (devicelist.Status.Ready? "Ready" : "Occupied")
        << std::endl << std::endl;
}

/** * @brief software trigger single scan function.
 	* @param device pho::api::PPhoXi.
 	* @return bool program error code.
**	**/
bool SoftwareTrigger_SingleScan(const pho::api::PPhoXi device)
{
    int FrameID = 0;
    /* if the device is in acquisition mode, stop acquisition */
    /* status checked to pause */
    if(device->isAcquiring())
        device->StopAcquisition();

    /* clear acqisition frames buffer */
    std::cout << "Clear Acqisition Buffer, Clear frames: ";
    std::cout << device->ClearBuffer() << std::endl;

    /* set trigger mode  */
    device->TriggerMode = pho::api::PhoXiTriggerMode::Software;
    /* start acquisition mode */
    device->StartAcquisition();
    /* if checked success, status checked to running */
    if(device->isAcquiring())
        std::cout << "PhoXiControl device setup Acqisition Successfully" << std::endl << std::endl;
    else
    {   /* if setup acqisition mode failed, exit function */
        std::cout << "PhoXiControl device setup Acqisition Failed" << std::endl << std::endl;
        return false;
    }

    /* trigger device to scan the frame */
    FrameID = device->TriggerFrame();
    std::cout << "-----------------------------------------------------------------------------" << std::endl;
    /* if FrameID=0, it means that the frame cannot be scan */
    if(FrameID < 0)
        std::cout << "Trigger was Frame Failed, code=" << FrameID << std::endl;
    else
        std::cout << "Frame was Triggered, FrameID: " << FrameID << std::endl;
    
    /* retrieve the specified frame */
    pho::api::PFrame frame = device->GetSpecificFrame(FrameID, pho::api::PhoXiTimeout::Infinity);
    if(frame)
    {   /* if retrieve success */
        std::cout << "  Frame params: " << std::endl;
        std::cout << "    Frame Index: "                << frame->Info.FrameIndex << std::endl;
        std::cout << "    Frame Acquisition duration: " << frame->Info.FrameDuration << " ms" << std::endl;
        std::cout << "    Frame Computation duration: " << frame->Info.FrameComputationDuration << " ms" << std::endl;
        std::cout << "    Frame Transfer duration: "    << frame->Info.FrameTransferDuration << " ms" << std::endl;
        std::cout << "    Sensor Position: ["
            << frame->Info.SensorPosition.x << "; "
            << frame->Info.SensorPosition.y << "; "
            << frame->Info.SensorPosition.z << "]"
            << std::endl;
        std::cout << "    Color Camera Position: ["
            << frame->Info.ColorCameraPosition.x << "; "
            << frame->Info.ColorCameraPosition.y << "; "
            << frame->Info.ColorCameraPosition.z << "]"
            << std::endl;
        std::cout << "    Total scan count: "           << frame->Info.TotalScanCount << std::endl;
        if (frame->Empty())
        {
            std::cout << "Frame is empty." << std::endl << std::endl;
            return false;
        }
        std::cout << "  Frame data: " << std::endl;
        if (!frame->PointCloud.Empty())
        {
            std::cout << "    PointCloud:    ("
                << frame->PointCloud.Size.Width << " x "
                << frame->PointCloud.Size.Height << ") Type: "
                << frame->PointCloud.GetElementName()
                << std::endl;
        }
        if (!frame->NormalMap.Empty())
        {
            std::cout << "    NormalMap:     ("
                << frame->NormalMap.Size.Width << " x "
                << frame->NormalMap.Size.Height << ") Type: "
                << frame->NormalMap.GetElementName()
                << std::endl;
        }
        if (!frame->DepthMap.Empty())
        {
            std::cout << "    DepthMap:      ("
                << frame->DepthMap.Size.Width << " x "
                << frame->DepthMap.Size.Height << ") Type: "
                << frame->DepthMap.GetElementName()
                << std::endl;
        }
        if (!frame->ConfidenceMap.Empty())
        {
            std::cout << "    ConfidenceMap: ("
                << frame->ConfidenceMap.Size.Width << " x "
                << frame->ConfidenceMap.Size.Height << ") Type: "
                << frame->ConfidenceMap.GetElementName()
                << std::endl;
        }
        if (!frame->Texture.Empty())
        {
            std::cout << "    Texture:       ("
                << frame->Texture.Size.Width << " x "
                << frame->Texture.Size.Height << ") Type: "
                << frame->Texture.GetElementName()
                << std::endl;
        }
        if (!frame->TextureRGB.Empty())
        {
            std::cout << "    TextureRGB:       ("
                << frame->TextureRGB.Size.Width << " x "
                << frame->TextureRGB.Size.Height << ") Type: "
                << frame->TextureRGB.GetElementName()
                << std::endl;
        }
        if (!frame->ColorCameraImage.Empty())
        {
            std::cout << "    ColorCameraImage:       ("
                << frame->ColorCameraImage.Size.Width << " x "
                << frame->ColorCameraImage.Size.Height << ") Type: "
                << frame->ColorCameraImage.GetElementName()
                << std::endl;
        }
        std::cout << "-----------------------------------------------------------------------------" << std::endl << std::endl;
    }
    else
    {   /* if retrieve fail */
        std::cout << "Failed to retrieve the frame" << std::endl;
        return false;
    }
    
    
    return true;
}