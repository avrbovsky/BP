#ifndef POSTPROCESSING_H
#define POSTPROCESSING_H

#include "Postprocessing_global.h"
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "helperClass.h"

#include "breaks.h"
#include "dots.h"
#include "islands.h"
#include "spur.h"

#define LENGTH 5

class POSTPROCESSING_EXPORT Postprocessing
{
public:
    Postprocessing();
};

#endif // POSTPROCESSING_H
