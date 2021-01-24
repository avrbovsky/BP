#ifndef DOTS_H
#define DOTS_H

#include "postprocessing.h"

class Dot
{
private:
    cv::Mat imgBefore;
    cv::Mat imgAfter;
public:
    Dot(std::string);
    Dot(cv::Mat);
    void removeDots();
    bool isDot(int row, int col);
};

#endif // DOTS_H
