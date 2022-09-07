#ifndef COMPUTERGRAPHICSFROMSCRATCH_TRACERAY_H
#define COMPUTERGRAPHICSFROMSCRATCH_TRACERAY_H


#include <opencv2/core.hpp>
#include "object.h"


class TraceRay {
public:
    TraceRay(std::shared_ptr<Scene> scene);
    cv::Vec3b compute(const cv::Vec3d& O, const cv::Vec3d& D, double t_min, double t_max);

private:
    static cv::Vec2d intersectRaySphere(const cv::Vec3d& O, const cv::Vec3d& D, const Sphere& sphere);
    std::pair<std::shared_ptr<Sphere>, double> closestIntersection(const cv::Vec3d& O, const cv::Vec3d& D, double tMin, double tMax);
    double computeLighting(const cv::Vec3d& P, const cv::Vec3d& N, const cv::Vec3d& V, double s);

    cv::Vec3b backGroundColor_;
    std::shared_ptr<Scene> scene_;
};

#endif //COMPUTERGRAPHICSFROMSCRATCH_TRACERAY_H
