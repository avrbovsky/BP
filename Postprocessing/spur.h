#ifndef SPUR_H
#define SPUR_H
#include "postprocessing.h"


class Spur
{
private:
    cv::Mat imgBefore;
    cv::Mat imgAfter;
public:
    Spur(std::string);
    Spur(cv::Mat);
    void locateSpurs();
    bool isEnd(int row, int col);
    bool isSpur(int row, int col);
    int countSpurLength(int row, int col, int prevRow, int prevCol, int* count);
    void removeSpur(int row, int col);
};

#endif // SPUR_H
