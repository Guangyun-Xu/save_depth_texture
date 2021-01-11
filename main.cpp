#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
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


pho::api::PFrame get_frame(const pho::api::PPhoXi &phoXi_device);
int coustm_save(const pho::api::PPhoXi &phoXi_device,
                const std::string &save_dir);


int main()
{
    // settings
    enum save_method {custom=1, sequence=2};
    save_method method = custom;
    std::string custom_save_dir = "../data";
    std::string sequence_save_dir = "../data";

    pho::api::PPhoXi device = initialize_camera();
    if(!device){
        return 0;
    }else{
        std::cout<<"begin save image!"<< std::endl;
    }

    initialize_acquiring(device);


    switch (method) {
    case 1:
        std::cout << "custom " << std::endl;
        coustm_save(device, custom_save_dir);
        break;
    case 2:
        std::cout << "sequence " << std::endl;
    default:
        std::cout << "please set right save method! " <<std::endl;
        break;
    }


    return 0;
}

pho::api::PFrame get_frame(const pho::api::PPhoXi &phoXi_device)
{
    int frame_ID = phoXi_device->TriggerFrame();
    if (frame_ID < 0) {
        // If negative number is returned trigger was unsuccessful
        std::cout << "Trigger was unsuccessful!" << std::endl;
    } else {
        std::cout << "Frame was triggered, Frame Id: " << frame_ID
                  << std::endl;
    }

    std::cout << "Waiting for frame .... " << std::endl;
    pho::api::PFrame frame = phoXi_device->GetSpecificFrame(
            frame_ID, pho::api::PhoXiTimeout::Infinity);

    if (frame){
        return frame;
    }else{
        std::cout << "Failed to retrieve the frame!" <<std::endl;
    }

}


int coustm_save(const pho::api::PPhoXi &phoXi_device,
                const std::string &save_dir)
{
   pho::api::PFrame frame = get_frame(phoXi_device);

   if (access(save_dir.c_str(), 0) == -1)
       mkdir(save_dir.c_str(), S_IRWXU);

   float *texture_data = new float[frame->Texture.Size.Area()];
   float *depth_data = new float[frame->DepthMap.Size.Area()];

   int height = frame->DepthMap.Size.Height;
   int width = frame->DepthMap.Size.Width;

   frame->Texture.ConvertTo2DArray(texture_data, height, width);
   frame->DepthMap.ConvertTo2DArray(depth_data, height, width);

   cv::Mat depth_mat(cv::Size(width, height), CV_32FC1, depth_data);
   depth_mat = depth_mat * 10.0f;  // conver the unit of depth to 0.1mm
   depth_mat.convertTo(depth_mat, CV_16UC1);
   cv::Mat texture_mat(cv::Size(width, height), CV_32FC1, texture_data);

   float crop_rate = (1.0f - (671.0f/1032.0f))/2.0f;
   int width_top = int(width*crop_rate);
   int height_down = int(height*crop_rate);
   cv::Rect crop_roi(width_top, height_down, 671, 502);

   cv::Mat cropped_depth = depth_mat(crop_roi);
   cv::Mat cropped_texture = texture_mat(crop_roi);

   // normalize texture image
   cv::normalize(cropped_texture, cropped_texture, 0, 450, cv::NORM_MINMAX);

   std::string depth_path = save_dir + "/depth.png";
   std::string texture_path = save_dir + "/texture.png";

   cv::imwrite(depth_path, cropped_depth);
   cv::imwrite(texture_path, cropped_texture);

   std::cout << "depth saved in: " << depth_path <<std::endl;
   std::cout << "texture saved in:" << texture_path << std::endl;

   return 0;
}
