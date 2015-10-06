
#include "stereoview.h"

extern Point2f point;
extern vector<Point2f> points[2];

using namespace cv;
using namespace std;

CStereoView::CStereoView(Mat &_mLeftImg, Mat &_mRightImg)
{
    mLeftImg = _mLeftImg;
    mRightImg = _mRightImg;

    if (mLeftImg.channels() == 3)
        mLeftImg.convertTo(mLeftGrayImg, CV_RGB2GRAY);
    if (mRightImg.channels() == 3)
        mRightImg.convertTo( mRightGrayImg, CV_RGB2GRAY);
}


CStereoView::getRBImg()
{
    Mat mRedChannel;
    Mat mBlueChannel;

    vector<Mat> channels;

    split(mLeftImg, channels);
    mRedChannel = channels.at(2);       // split red channel of left image

    split(mRightImg, channels);
    mBlueChannel = channels.at(0);      // split blue channel of right image

    channels.clear();
    channels.push_back(mBlueChannel);
    channels.push_back(mRedChannel);

    merge(channels, mRBImg);            // merge new red and blue image
}


// tracking objects with optical flow methods
// completed by Xiaohan Jin on 2015-9-22
CStereoView::trackflow(Mat gray, Mat prevGray)
{
    TermCriteria termcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
    Size subPixWinSize(5, 5), winSize(10, 10);
    const int MAX_COUNT = 500;
    bool needToInit = false;
    bool nightMode = false;

    if (nightMode)
        gray = Scalar::all(0);

    if (needToInit)
    {
        // automatic initialization
        goodFeaturesToTrack(gray, points[1], MAX_COUNT, 0.01, 10, Mat(), 3, 0, 0.04);
        cornerSubPix(gray, points[1], subPixWinSize, Size(-1, -1), termcrit);
        addRemovePt = false;
    }
    else if (!points[0].empty())
    {
        vector<uchar> status;
        vector<float> err;
        if (prevGray.empty()){
            gray.copyTo(prevGray);
        }
        //imshow("prevG",prevGray);
        //imshow("newG",gray);

        calcOpticalFlowPyrLK(prevGray, gray, points[0], points[1], status, err, winSize,
                3, termcrit, 0, 0.001);
        size_t i, k;
        for (i = k = 0; i < points[1].size(); i++)
        {
            if (addRemovePt)
            {
                if (norm(point - points[1][i]) <= 5)
                {
                    addRemovePt = false;
                    continue;
                }
            }

            if (!status[i])
                continue;

            points[1][k++] = points[1][i];
            //circle(image, points[1][i], 3, Scalar(0, 255, 0), -1, 8);

            cout << "Track[" << i << "]: (" << points[1][i].x << "," << points[1][i].y << ")" << endl;
        }
        points[1].resize(k);
    }
    if (addRemovePt && points[1].size() < (size_t)MAX_COUNT)
    {
        vector<Point2f> tmp;
        tmp.push_back(point);
        cornerSubPix(gray, tmp, winSize, cvSize(-1, -1), termcrit);
        points[1].push_back(tmp[0]);
        addRemovePt = false;
    }
    needToInit = false;

    std::swap(points[1], points[0]);
    cout<<"p; size : " << points[0].size()<<"  ";

}
