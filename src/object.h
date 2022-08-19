#ifndef COMPUTERGRAPHICSFROMSCRATCH_OBJECT_H
#define COMPUTERGRAPHICSFROMSCRATCH_OBJECT_H

#include <opencv2/core.hpp>

struct Sphere {
    double radius;
    cv::Vec3d center;
    cv::Vec3b color;

    Sphere(double radius, const cv::Vec3d& center, const cv::Vec3b& colorRGB) :
        radius(radius), center(center), color(colorRGB) {
    }
};

#endif //COMPUTERGRAPHICSFROMSCRATCH_OBJECT_H
