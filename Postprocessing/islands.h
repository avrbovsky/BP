#ifndef ISLANDS_H
#define ISLANDS_H
#include "postprocessing.h"

class Island
{
private:
    cv::Mat imgBefore;
    cv::Mat imgAfter;
public:
    Island(std::string fileName);
    Island(cv::Mat img);
    void removeIslands();
    bool isIsland(int row, int col);
    int countIslandLength(int row, int col, int prevRow, int prevCol, int *count);
    void removeIsland(int row, int col);
};

#endif // ISLANDS_H
