#include "traceRay.h"


TraceRay::TraceRay(std::shared_ptr<Scene> scene) : scene_(std::move(scene)) {
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


std::pair<std::shared_ptr<Sphere>, double>
TraceRay::closestIntersection(const cv::Vec3d &O, const cv::Vec3d &D, double t_min, double t_max) {
    double closest_t = std::numeric_limits<double>::infinity();
    std::shared_ptr<Sphere> closest_sphere = nullptr;
    for (const std::shared_ptr<Sphere>& sphere : scene_->spheres) {
        cv::Vec2d t = intersectRaySphere(O, D, *sphere);
        double t1 = t[0];
        if (t_min <= t1 && t1 <= t_max && t1 < closest_t) {
            closest_t = t1;
            closest_sphere = sphere;
        }
        double t2 = t[1];
        if (t_min <= t2 && t2 <= t_max && t2 < closest_t) {
            closest_t = t2;
            closest_sphere = sphere;
        }
    }
    return {closest_sphere, closest_t};
}


cv::Vec3d TraceRay::compute(
        const cv::Vec3d& O, const cv::Vec3d& D, double t_min, double t_max, size_t recursion_depth) {
    std::pair<std::shared_ptr<Sphere>, double> intersection = closestIntersection(O, D, t_min, t_max);
    std::shared_ptr<Sphere> closest_sphere = intersection.first;
    double closest_t = intersection.second;

    if (closest_sphere == nullptr) {
        return backGroundColor_;
    }

    cv::Vec3d P = O + closest_t * D;
    cv::Vec3d N = P - closest_sphere->center;
    N = N / cv::norm(N);
    cv::Vec3d local_color = closest_sphere->color * computeLighting(P, N, -D, closest_sphere->specular);

    double r = closest_sphere->reflective;
    if (recursion_depth <= 0 || r <= 0) {
        return local_color;
    }
    cv::Vec3d R = reflectRay(-D, N);
    cv::Vec3d reflected_color = compute(P, R, 0.001, std::numeric_limits<double>::infinity(), recursion_depth - 1);
    return local_color * (1 - r) + reflected_color * r;
}


double TraceRay::computeLighting(const cv::Vec3d& P, const cv::Vec3d& N, const cv::Vec3d& V, double s) {
    double i = 0.0;

    for (const std::shared_ptr<Light>& light : scene_->lights) {
        if (light->type == Light::Type::ambient) {
            i += light->intensity;
        } else {
            double t_max = std::numeric_limits<double>::infinity();
            cv::Vec3d L = 0.;
            if (light->type == Light::Type::point) {
                L = light->position - P;
                t_max = 1.;
            } else {
                L = light->direction;
                t_max = std::numeric_limits<double>::infinity();
            }

            // shadow check
            std::pair<std::shared_ptr<Sphere>, double> shadow = closestIntersection(P, L, 0.01, t_max);
            std::shared_ptr<Sphere> shadow_sphere = shadow.first;
            if (shadow_sphere != nullptr) {
                continue;
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

cv::Vec3d TraceRay::reflectRay(const cv::Vec3d &R, const cv::Vec3d &N) {
    return 2 * N * N.dot(R) - R;
}

void TraceRay::setBackgroundColor(const cv::Vec3b& color) {
    backGroundColor_ = color;
}
