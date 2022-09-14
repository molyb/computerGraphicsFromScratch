#include "canvas.h"
#include "traceRay.h"

std::shared_ptr<Scene> makeScene() {
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    scene->spheres.emplace_back(
            std::make_shared<Sphere>(1, cv::Vec3d(0, -1, 3), cv::Vec3b(255, 0, 0), 500, 0.2));  // red
    scene->spheres.emplace_back(
            std::make_shared<Sphere>(1., cv::Vec3d(2, 0, 4), cv::Vec3b(0, 0, 255), 500, 0.3));  // blue
    scene->spheres.emplace_back(
            std::make_shared<Sphere>(1., cv::Vec3d(-2, 0, 4), cv::Vec3b(0, 255, 0), 10, 0.4));  // green
    scene->spheres.emplace_back(
            std::make_shared<Sphere>(5000., cv::Vec3d(0, -5001, 0), cv::Vec3b(255, 255, 0), 1000, 0.5));  // yellow

    scene->lights.emplace_back(std::make_shared<Light>(0.2));  // Light::Type::ambient
    scene->lights.emplace_back(std::make_shared<Light>(Light::Type::point, 0.6, cv::Vec3d(2, 1, 0)));
    scene->lights.emplace_back(std::make_shared<Light>(Light::Type::directional, 0.2, cv::Vec3d(1, 4, 4)));

    return scene;
}

// ./computerGraphicsFromScratch (recursive_depth)
int main(int argc, char** argv) {
    const int canvasWidth = 400;
    const int canvasHeight = 400;
    const double viewportWidth = 1.;
    const double viewportHeight = 1.;
    const double viewportDepth = 1.;
    size_t recursive_depth = 5;
    if (1 < argc) {
        recursive_depth = std::strtoul(argv[1], nullptr, 10);
    }

    Canvas canvas(canvasWidth, canvasHeight, viewportWidth, viewportHeight, viewportDepth);
    TraceRay trace(makeScene());
    trace.setBackgroundColor({0, 0, 0});  // black

    for (int x = -canvasWidth / 2; x < canvasWidth / 2; x++) {
        for (int y = -canvasHeight / 2; y < canvasHeight / 2; y++) {
            cv::Vec3d D = canvas.toViewport(x, y);
            cv::Vec3d O(0, 0, 0);
            cv::Vec3b color = trace.compute(O, D, 1, std::numeric_limits<double>::infinity(), recursive_depth);
            canvas.putPixel(x, y, color);
        }
    }
    canvas.show();
    return 0;
}
