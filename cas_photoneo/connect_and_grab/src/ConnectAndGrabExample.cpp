/*
* Photoneo's API Example - ConnectAndGrab.cpp
* Defines the entry point for the console application.
* Demonstrates the basic functionality of PhoXi device. This Example shows the preferred way how to use API function calls. 
* Contains the usage of PhoXiFactory which is used to retrieve all connected scanners and establish a connection.
* Emphasizes the need to stop acquisition in order to change trigger mode.
* Describes both SoftwareTrigger and FreeRun modes. Different ways of getting frames and frame specific data.
*/

#include <vector>
#include <string>
#include <iostream>

#include "PhoXi.h"

/* print Devices Information function */
void printDeviceInfoList(const pho::api::PhoXiDeviceInformation);

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
 	* @param vector<PhoXiDeviceInformation> Devices Information.
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