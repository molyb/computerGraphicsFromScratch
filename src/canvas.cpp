#include "canvas.h"


Canvas::Canvas(size_t canvasWidth, size_t canvasHeight,
               double viewportWidth, double viewportHeight, double viewportDepth):
                canvasWidth_((int)canvasWidth), canvasHeight_((int)canvasHeight),
                viewportWidth_(viewportWidth), viewportHeight_(viewportHeight), viewportDepth_(viewportDepth) {
    if (INT_MAX < canvasWidth || INT_MAX < canvasHeight ||
        viewportWidth < 0 || viewportHeight < 0 || viewportDepth < 0) {
        return;
    }
    image_ = cv::Mat_<cv::Vec3b>(canvasHeight_, canvasWidth_, cv::Vec3b(0, 0, 0));  // black
}


bool Canvas::putPixel(int x, int y, const cv::Vec3b& colorRGB) {
    if (image_.empty()) {
        return false;
    }
    int u = x + canvasWidth_ / 2;
    int v = canvasHeight_ / 2 - y;
    if (u < 0 || v < 0 || canvasWidth_ <= u || canvasHeight_ <= v) {
        return false;
    }
    image_.at<cv::Vec3b>(v, u) = cv::Vec3b(colorRGB(2), colorRGB(1), colorRGB(0));  // RGB -> BGR(OpenCV)
    return true;
}


cv::Vec3d Canvas::toViewport(int x, int y) const {
    return {(double)x * viewportWidth_/(double)canvasWidth_,
            (double)y * viewportHeight_/(double)canvasHeight_,
            viewportDepth_};
}


void Canvas::show(const std::string& title) {
    cv::imshow(title, image_);
    cv::waitKey(0);
}
