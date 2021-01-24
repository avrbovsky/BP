#ifndef BREAKS_H
#define BREAKS_H

#include "postprocessing.h"

class Breaks
{
private:
    cv::Mat imgBefore;
    cv::Mat orientationMap;
public:
    cv::Mat imgAfter;
    Breaks(std::string, cv::Mat);
    Breaks(cv::Mat, cv::Mat);
    void removeBreaks();
    bool isBreak(int row, int col);
    bool canConnect(int row, int col);
    double getAngle(int row, int col);
    void connectPoints(int row1,int col1, int row2, int col2);
    int getDirection(int row, int col);
};

#endif // BREAKS_H
