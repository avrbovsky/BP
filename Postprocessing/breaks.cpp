#include "breaks.h"


Breaks::Breaks(std::string fileName, cv::Mat orientationMap)
{
    this->imgBefore = cv::imread(fileName, cv::IMREAD_GRAYSCALE);
    this->imgAfter = this->imgBefore.clone();
    this->orientationMap = orientationMap;
}

Breaks::Breaks(cv::Mat img, cv::Mat orientationMap)
{
    this->imgBefore = img;
    this->imgAfter = this->imgBefore.clone();
    this->orientationMap = orientationMap;
}

void Breaks::removeBreaks()
{
    int connected = 0;
    for(int i = 1; i < imgAfter.rows; i++){
        for(int j = 1; j < imgAfter.cols; j++){
            if(imgAfter.at<uchar>(i,j) == 0)
                if(isBreak(i,j)){
                    if(canConnect(j,i)){
                        connected++;
                    }
                }
        }
    }
    std::cout << connected << std::endl;
}

bool Breaks::isBreak(int row, int col)
{
    int n = 0;
    for(int i = row - 1; i <= row + 1; i++){
        for(int j = col - 1; j <= col + 1; j++){
            if(imgAfter.at<uchar>(i,j) == 0)
                n++;
        }
    }
    return n==2;
}

bool Breaks::canConnect(int row, int col)
{
    double angle = getAngle(row,col);
    if(angle >= 0 && angle < 90){//doprava
        for(int i = 1; i <= LENGTH; i++){
            double height = tan(angle) * i;
                if(imgAfter.at<uchar>(col - floor(height), row + i) == 0){
                connectPoints(row,col,row+i,col - floor(height));
                return true;
            }
            if(imgAfter.at<uchar>(col - ceil(height), row + i) == 0){
                connectPoints(row,col,row + i, col - ceil(height));
                return true;
            }
        }
    }else if(angle > 90 && angle < 270){//dolava
        for(int i = 1; i <= LENGTH; i++){
            double height = tan(angle) * i;
            if(imgAfter.at<uchar>(col - i, row - floor(height)) == 0){
                connectPoints(row,col,row - floor(height),col - i);
                return true;
            }
            if(imgAfter.at<uchar>(col - i, row - ceil(height)) == 0){
                connectPoints(row,col,row - ceil(height),col - i);
                return true;
            }
        }
    }else if(angle > 270 && angle <= 360){//doprava
        for(int i = 1; i <= LENGTH; i++){
            double height = tan(angle) * i;
            if(imgAfter.at<uchar>(col + i, row - floor(height)) == 0){
                connectPoints(row,col,row-floor(height),col+1);
                return true;
            }
            if(imgAfter.at<uchar>(col + i, row - ceil(height)) == 0){
                connectPoints(row,col,row-ceil(height),col+1);
                return true;
            }
        }
    }else if(angle == 90){//hore
        for(int i = 0; i <= LENGTH; i++){
            if(imgAfter.at<uchar>(col,row-i)==0){
                connectPoints(row,col,row-1,col);
                return true;
            }
        }
    }else{//dole
        for(int i = 0; i <= LENGTH; i++){
            if(imgAfter.at<uchar>(col,row+i)==0){
                connectPoints(row,col,row+i,col);
                return true;
            }
        }
    }
    return false;
}


double Breaks::getAngle(int row, int col)
{
    double rad = orientationMap.at<double>(row,col);
    while(rad <= 0){
        rad++;
    }
    return rad * 180 / M_PI;
}

void Breaks::connectPoints(int row1, int col1, int row2, int col2)
{
    cv::line(imgAfter, cv::Point(row1, col1), cv::Point(row2, col2), 0, 1);
}
