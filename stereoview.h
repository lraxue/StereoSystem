#ifndef STEREOVIEW
#define STEREOVIEW

#include <opencv2/opencv.hpp>
#include <opencv2/flann/flann.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/core/core.hpp>
#include <opencv/highgui.h>
#include <opencv2/nonfree/nonfree.hpp>

using namespace cv;
using namespace std;
class CStereoView
{
    CStereoView(Mat &, Mat &);
    ~CStereoView();

private:
    Mat mLeftImg;           // left image
    Mat mRightImg;          // right image

    Mat mLeftGrayImg;       // gray left image
    Mat mRightGrayImg;      // gray right image

    Mat mDispImg;           // disparity image
    Mat mDepthImg;          // depth image

    Mat mRBImg;             // red and blue image


private:
    void getRBImg();
    void trackflow(Mat gray, Mat prevGray);


};

#endif // STEREOVIEW

