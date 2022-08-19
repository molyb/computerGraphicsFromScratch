#include "traceRay.h"


TraceRay::TraceRay() {
    spheres_.push_back(std::make_shared<Sphere>(1, cv::Vec3d(0, -1, 3), cv::Vec3b(255, 0, 0), 500));  // red
    spheres_.push_back(std::make_shared<Sphere>(1., cv::Vec3d(2, 0, 4), cv::Vec3b(0, 0, 255), 500));  // blue
    spheres_.push_back(std::make_shared<Sphere>(1., cv::Vec3d(-2, 0, 4), cv::Vec3b(0, 255, 0), 10));  // green
    spheres_.push_back(std::make_shared<Sphere>(5000., cv::Vec3d(0, -5001, 0), cv::Vec3b(255, 255, 0), 1000));  // yellow

    lights_.push_back(std::make_shared<Light>(0.2));  // Light::Type::ambient
    lights_.push_back(std::make_shared<Light>(Light::Type::point, 0.6, cv::Vec3d(2, 1, 0)));
    lights_.push_back(std::make_shared<Light>(Light::Type::directional, 0.2, cv::Vec3d(1, 4, 4)));

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

    cv::Vec3d P = O + closest_t * D;
    cv::Vec3d N = P - closest_sphere->center;
    N = N / cv::norm(N);
    return closest_sphere->color * computeLighting(P, N, -D, closest_sphere->specular);
}


double TraceRay::computeLighting(const cv::Vec3d& P, const cv::Vec3d& N, const cv::Vec3d& V, double s) {
    double i = 0.0;

    for (const std::shared_ptr<Light>& light : lights_) {
        if (light->type == Light::Type::ambient) {
            i += light->intensity;
        } else {
            cv::Vec3d L = 0.;
            if (light->type == Light::Type::point) {
                L = light->position - P;
            } else {
                L = light->direction;
            }
            // Diffuse
            double nDotI = N.dot(L);
            if (nDotI > 0) {
                i += light->intensity * nDotI/(cv::norm(N) * cv::norm(L));
            }

            // Specular
            if (s != -1) {
                cv::Vec3d R = 2 * N * N.dot(L) - L;
                double rDotV = R.dot(V);
                if (rDotV > 0) {
                    i += light->intensity * pow(rDotV / (cv::norm(R) * cv::norm(V)), s);
                }
            }
        }
    }
    return i;
}
