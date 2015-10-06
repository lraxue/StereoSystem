#ifndef SCENEANALYSIS
#define SCENEANALYSIS

#include "stereoview.h"

using namespace cv;
using namespace std;

class CStereoAnalysis
{
    CStereoAnalysis();
    ~CStereoAnalysis();


private:

    CStereoView *scene;

    double dbBaseline;
    double dbDolly;
    double dbArch;
    double dbFov;
    double dbTranslation;


public:
    void setScene(CStereoView *);
    void setParameters(double baseline, double dolly,
                       double arch, double fov, double translation);
};

#endif // SCENEANALYSIS

