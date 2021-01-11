#ifndef CAMERA_UTILS_H
#define CAMERA_UTILS_H
#include <iostream>
#include "PhoXi.h"

pho::api::PPhoXi initialize_camera();
void initialize_acquiring(pho::api::PPhoXi &device);

#endif // CAMERA_UTILS_H
