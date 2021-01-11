#include <iostream>
#include <string>
#include <vector>
#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#endif

#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#define PHOXI_OPENCV_SUPPORT

#include "PhoXi.h"
#include "camera_utils.h"


int main()
{
    pho::api::PPhoXi device = initialize_camera();
    if(!device){
        return 0;
    }else{
        std::cout<<"begin save image!"<< std::endl;
    }

    initialize_acquiring(device);

    return 0;
}


