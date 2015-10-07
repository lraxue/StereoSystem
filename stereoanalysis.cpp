#include "stereoanalysis.h"

using namespace cv;

CStereoAnalysis::CStereoAnalysis()
{

}

CStereoAnalysis::~CStereoAnalysis()
{
   /* if (scene != nullptr)
        delete scene;
        */

}

void CStereoAnalysis::setScene(CStereoView *_scene)
{
    /*if (scene == nullptr)
        delete scene;

    scene = _scene;
*/
}

void CStereoAnalysis::setParameters(double baseline, double dolly,
                               double arch, double fov, double translation)
{
    dbBaseline = baseline;
    dbDolly = dolly;
    dbArch = arch;
    dbFov = fov;
    dbTranslation = translation;
}
