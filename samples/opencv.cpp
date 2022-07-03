#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

int main()
{
    const unsigned int width = 640;
    const unsigned int height = 480;
    const cv::Scalar color_bgr(0, 255, 0);

    cv::Mat img(height, width, CV_8UC3, color_bgr);
    imshow("Display window", img);
    cv::waitKey(0); // Wait for a keystroke in the window
    return 0;
}
