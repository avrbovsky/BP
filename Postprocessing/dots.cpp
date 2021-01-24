#include "dots.h"

Dot::Dot(std::string fileName)
{
    this->imgBefore = cv::imread(fileName, cv::IMREAD_GRAYSCALE);
    this->imgAfter = this->imgBefore.clone();
}

Dot::Dot(cv::Mat img)
{
    this->imgBefore = img;
    this->imgAfter = this->imgBefore.clone();
}

void Dot::removeDots()
{
    for(int i = 1; i < this->imgBefore.rows; i++){
        for(int j = 1; j < this->imgBefore.cols; j++){
            if(this->imgAfter.at<uchar>(i,j)==0){
                if(isDot(i, j))
                    this->imgAfter.at<uchar>(i,j) = 255;
            }
        }
    }
    cv::imshow("imgBeforeDots", this->imgBefore);
    cv::imshow("imgAfterDots", this->imgAfter);
}

bool Dot::isDot(int row, int col)
{
    int neighbor = 0;
    for(int i = row - 1; i <= row + 1; i++){
        for(int j = col - 1; j <= col + 1; j++){
            if(this->imgAfter.at<uchar>(i,j) <= 10){
                neighbor++;
            }
        }
    }
    return neighbor==1;
}
