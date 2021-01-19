#ifndef HILDITCH_H
#define HILDITCH_H

#include "Hilditch_global.h"
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

class HILDITCH_EXPORT Hilditch
{
public:
    cv::Mat imgOriginal;
    cv::Mat imgAfter;
    Hilditch(cv::Mat imgOriginal);
    void skeletonization();
    bool removePixel(int* count);
    int countNeighbours(int row, int col);
    int connectivity(int row, int col);
};

#endif // HILDITCH_H
