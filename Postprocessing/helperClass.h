#ifndef SOMETHING_H
#define SOMETHING_H
#include "postprocessing.h"

class HelperClass
{
public:
    HelperClass();
    static int countNeighbors(cv::Mat img, int row, int col);
};

#endif // SOMETHING_H
