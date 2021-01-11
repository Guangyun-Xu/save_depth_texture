#include "camera_utils.h"

pho::api::PPhoXi initialize_camera()
{
    pho::api::PhoXiFactory Factory;

    // Check if the PhoXi Control Software is running
    if (!Factory.isPhoXiControlRunning()) {
        std::cout << "PhoXi Control Software is not running" << std::endl;
    }

    // Get List of available devices on the network
    std::vector<pho::api::PhoXiDeviceInformation> DeviceList =
            Factory.GetDeviceList();
    if (DeviceList.empty()) {
        std::cout << "PhoXi Factory has found 0 devices" << std::endl;
    }

    // Try to connect device opened in PhoXi Control, if any
    pho::api::PPhoXi PhoXiDevice = Factory.CreateAndConnectFirstAttached();
    if (PhoXiDevice) {
        std::cout << "You have already PhoXi device opened in PhoXi Control, "
                     "the API Example is connected to device: "
                  << (std::string)PhoXiDevice->HardwareIdentification
                  << std::endl;
        return PhoXiDevice;
    } else {
        std::cout
                << "You have no PhoXi device opened in PhoXi Control, the API ";

        for (size_t i = 0; i < DeviceList.size(); i++) {
            std::cout << "Example will try to connect to ..."
                      << DeviceList.at(i).HWIdentification << std::endl;
            // wait 5 second for scanner became ready
            PhoXiDevice = Factory.CreateAndConnect(
                    DeviceList.at(i).HWIdentification, 5000);
            if (PhoXiDevice) {
                std::cout << "succesfully connected" << std::endl;
                return PhoXiDevice;
            }
            if (i == DeviceList.size() - 1) {
                std::cout << "Can not connect to any device" << std::endl;
                return PhoXiDevice;
            }
        }
    }
}

void initialize_acquiring(pho::api::PPhoXi &PhoXiDevice)
{
    if (PhoXiDevice->isAcquiring()) {
        // Stop acquisition to change trigger mode
        PhoXiDevice->StopAcquisition();
    }

    PhoXiDevice->TriggerMode = pho::api::PhoXiTriggerMode::Software;
    std::cout << "Software trigger mode was set" << std::endl;
    PhoXiDevice->ClearBuffer();
    PhoXiDevice->StartAcquisition();
    if (!PhoXiDevice->isAcquiring()) {
        std::cout << "Your device could not start acquisition!" << std::endl;
        return;
    }
}
