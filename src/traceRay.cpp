#include "traceRay.h"


TraceRay::TraceRay() {
    std::shared_ptr<Sphere> red = std::make_shared<Sphere>();
    red->radius = 1.;
    red->center = cv::Vec3d(0, -1, 3);
    red->color = cv::Vec3b(0, 0, 255);

    std::shared_ptr<Sphere> blue = std::make_shared<Sphere>();;
    blue->radius = 1.;
    blue->center = cv::Vec3d(2, 0, 4);
    blue->color = cv::Vec3b(255, 0, 0);

    std::shared_ptr<Sphere> green = std::make_shared<Sphere>();;
    green->radius = 1.;
    green->center = cv::Vec3d(-2, 0, 4);
    green->color = cv::Vec3b(0, 255, 0);

    spheres_.push_back(red);
    spheres_.push_back(blue);
    spheres_.push_back(green);

    backGroundColor_ = cv::Vec3b(255, 255, 255); // white
}


cv::Vec2d TraceRay::intersectRaySphere(const cv::Vec3d& O, const cv::Vec3d& D, const Sphere& sphere) {
    double r = sphere.radius;
    cv::Vec3d CO = O - sphere.center;

    double a = D.dot(D);
    double b = 2*CO.dot(D);
    double c = CO.dot(CO) - r*r;

    double discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
        return {std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()};
    }

    double t1 = (-b + sqrt(discriminant)) / (2*a);
    double t2 = (-b - sqrt(discriminant)) / (2*a);
    return {t1, t2};
}


cv::Vec3b TraceRay::compute(const cv::Vec3d& O, const cv::Vec3d& D, double t_min, double t_max) {
    double closest_t = std::numeric_limits<double>::infinity();
    std::shared_ptr<Sphere> closest_sphere = nullptr;

    for (const std::shared_ptr<Sphere>& sphere : spheres_) {
        cv::Vec2d t = intersectRaySphere(O, D, *sphere);
        double t1 = t(0);
        double t2 = t(1);
        if (t_min <= t1 && t1 <= t_max && t1 < closest_t) {
            closest_t = t1;
            closest_sphere = sphere;
        }
        if (t_min <= t2 && t2 <= t_max && t2 < closest_t) {
            closest_t = t2;
            closest_sphere = sphere;
        }
    }
    if (closest_sphere == nullptr) {
        return backGroundColor_;
    }
    return closest_sphere->color;
}
