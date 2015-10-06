#include "stereoanalysis.h"

using namespace cv;

CStereoAnalysis::CStereoAnalysis()
{

}

CStereoAnalysis::~CStereoAnalysis()
{
    if (scene != nullptr)
        delete scene;

}

CStereoAnalysis::setScene(CStereoView *_scene)
{
    if (scene == nullptr)
        delete scene;

    scene = _scene;
}

CStereoAnalysis::setParameters(double baseline, double dolly,
                               double arch, double fov, double translation)
{
    dbBaseline = baseline;
    dbDolly = dolly;
    dbArch = arch;
    dbFov = fov;
    dbTranslation = translation;
}
