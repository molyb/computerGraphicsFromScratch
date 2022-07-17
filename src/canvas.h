#ifndef COMPUTERGRAPHICSFROMSCRATCH_CANVAS_H
#define COMPUTERGRAPHICSFROMSCRATCH_CANVAS_H

#include <opencv2/highgui.hpp>


class Canvas {
public:
    Canvas(size_t canvasWidth, size_t canvasHeight,
           double viewportWidth = 1., double viewportHeight = 1., double viewportDepth = 1.);

    bool putPixel(int x, int y, const cv::Vec3b& color);

    cv::Vec3d toViewport(int x, int y) const;

    void show(const std::string& title = std::string("image"));

private:
    cv::Mat image_;
    int canvasWidth_;
    int canvasHeight_;
    double viewportWidth_;
    double viewportHeight_;
    double viewportDepth_;
};


#endif //COMPUTERGRAPHICSFROMSCRATCH_CANVAS_H
