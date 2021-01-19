#ifndef SPUR_H
#define SPUR_H
#include "postprocessing.h"


class Spur
{
public:
    Spur();
    void locateSpurs(std::string file);
    bool isEnd(cv::Mat img, int row, int col);
    bool isSpur(cv::Mat img, int row, int col);
    int countSpurLength(cv::Mat img, int row, int col, int prevRow, int prevCol, int* count);
    void removeSpur(cv::Mat img, int row, int col);
};

#endif // SPUR_H
