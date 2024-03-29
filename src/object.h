#ifndef COMPUTERGRAPHICSFROMSCRATCH_OBJECT_H
#define COMPUTERGRAPHICSFROMSCRATCH_OBJECT_H

#include <opencv2/core.hpp>

struct Light {
    enum Type {
        ambient,
        point,
        directional
    };
    Type type;
    double intensity;
    cv::Vec3d position;
    cv::Vec3d direction;

    Light() : type(Type::ambient), intensity(0.) {
    };

    // config Light as ambient
    explicit Light(double intensity) : type(Type::ambient), intensity(intensity) {
    };

    Light(Type type, double intensity, const cv::Vec3d& vec) : type(type), intensity(intensity) {
        if (type == Type::point) {
            position = vec;
        } else if (type == Type::directional) {
            direction = vec;
        } else {
            // ambient
        }
    };
};

struct Sphere {
    double radius;
    cv::Vec3d center;
    cv::Vec3b color;
    double specular;
    double reflective;

    Sphere(double radius, const cv::Vec3d& center, const cv::Vec3b& colorRGB, double specular, double reflective) :
        radius(radius), center(center), color(colorRGB), specular(specular), reflective(reflective) {
    };
};

struct Scene {
    std::vector<std::shared_ptr<Light>> lights;
    std::vector<std::shared_ptr<Sphere>> spheres;
};

#endif //COMPUTERGRAPHICSFROMSCRATCH_OBJECT_H
