#include "canvas.h"
#include "traceRay.h"


int main(int argc, char** argv) {
    const int canvasWidth = 400;
    const int canvasHeight = 400;
    const double viewportWidth = 1.;
    const double viewportHeight = 1.;
    const double viewportDepth = 1.;

    Canvas canvas(canvasWidth, canvasHeight, viewportWidth, viewportHeight, viewportDepth);
    TraceRay trace;
    for (int x = -canvasWidth / 2; x < canvasWidth / 2; x++) {
        for (int y = -canvasHeight / 2; y < canvasHeight / 2; y++) {
            cv::Vec3d D = canvas.toViewport(x, y);
            cv::Vec3d O(0, 0, 0);
            cv::Vec3b color = trace.compute(O, D, 1, std::numeric_limits<double>::infinity());
            canvas.putPixel(x, y, color);
        }
    }
    canvas.show();
    return 0;
}
