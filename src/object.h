#ifndef COMPUTERGRAPHICSFROMSCRATCH_OBJECT_H
#define COMPUTERGRAPHICSFROMSCRATCH_OBJECT_H

#include <opencv2/core.hpp>

struct Sphere {
    double radius;
    cv::Vec3d center;
    cv::Vec3b color;
};

#endif //COMPUTERGRAPHICSFROMSCRATCH_OBJECT_H
