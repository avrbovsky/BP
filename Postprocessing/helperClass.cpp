#include "helperClass.h"

HelperClass::HelperClass()
{

}

int HelperClass::countNeighbors(cv::Mat img, int row, int col)
{
    int neighbor = 0;
    for(int i = row - 1; i <= row + 1; i++){
        for(int j = col - 1; j <= col + 1; j++){
            if(!(i == row && j == col)){
                if(img.at<uchar>(i,j) <= 10)
                    neighbor++;
            }
        }
    }
    return neighbor;
}
