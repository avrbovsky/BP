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
                    if(canConnect(i,j)){
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
    if(angle >= 0 && angle < 90-10){//doprava
        for(int i = 1; i <= LENGTH; i++){
            double height = tan(angle * M_PI / 180.0) * i;
                if(imgAfter.at<uchar>(row - floor(height), col + i) == 0){
                    if(isBreak(row - floor(height), col + i)){
                        double angle2 = getAngle(row - floor(height), col + i);
                        if(angle>angle2)
                            angle-=180;
                        else
                            angle+=180;
                        if(angle-0.5 <= angle2 && angle+0.5 >= angle2){
                            connectPoints(col,row,col+i,row - floor(height));
                            return true;
                        }
                        else return false;
                    }
                    else return false;
            }
            if(imgAfter.at<uchar>(row - ceil(height), col + i) == 0){
                if(isBreak(row - ceil(height), col + i)){
                    double angle2 = getAngle(row - ceil(height), col + i);
                    if(angle>angle2)
                        angle-=180;
                    else
                        angle+=180;
                    if(angle-0.5 <= angle2 && angle+0.5 >= angle2){
                        connectPoints(col,row,col+i,row - ceil(height));
                        return true;
                    }
                    else return false;
                }
                else return false;
            }
        }
    }else if(angle > 90 + 10 && angle < 270-10){//dolava
        for(int i = 1; i <= LENGTH; i++){
            double height = tan(angle * M_PI / 180.0) * i;
            if(imgAfter.at<uchar>(row - floor(height), col - i) == 0){
                if(isBreak(row - floor(height), col - i)){
                    double angle2 = getAngle(row - floor(height), col - i);
                    if(angle>angle2)
                        angle-=180;
                    else
                        angle+=180;
                    if(angle-0.5 <= angle2 && angle+0.5 >= angle2){
                        connectPoints(col,row,col-i,row - floor(height));
                        return true;
                    }
                    else return false;
                }
                else return false;
            }
            if(imgAfter.at<uchar>(row - ceil(height), col - i) == 0){
                if(isBreak(row - ceil(height), col - i)){
                    double angle2 = getAngle(row - ceil(height), col - i);
                    if(angle>angle2)
                        angle-=180;
                    else
                        angle+=180;
                    if(angle-0.5 <= angle2 && angle+0.5 >= angle2){
                        connectPoints(col,row,col-i,row - ceil(height));
                        return true;
                    }
                    else return false;
                }
                else return false;
            }
        }
    }else if(angle > 270 + 10 && angle <= 360){//doprava
        for(int i = 1; i <= LENGTH; i++){
            double height = tan(angle * M_PI / 180.0) * i;
            if(imgAfter.at<uchar>(row - floor(height), col + i) == 0){
                if(isBreak(row - floor(height), col + i)){
                    double angle2 = getAngle(row - floor(height), col + i);
                    if(angle>angle2)
                        angle-=180;
                    else
                        angle+=180;
                    if(angle-0.5 <= angle2 && angle+0.5 >= angle2){
                        connectPoints(col,row,col+i,row - floor(height));
                        return true;
                    }
                    else return false;
                }
                else return false;
            }
            if(imgAfter.at<uchar>(row - ceil(height), col + i) == 0){
                if(isBreak(row - ceil(height), col + i)){
                    double angle2 = getAngle(row - ceil(height), col + i);
                    if(angle>angle2)
                        angle-=180;
                    else
                        angle+=180;
                    if(angle-0.5 <= angle2 && angle+0.5 >= angle2){
                        connectPoints(col,row,col+i,row - ceil(height));
                        return true;
                    }
                    else return false;
                }
                else return false;
            }
        }
    }else if(angle >= 90 - 10 && angle <= 90 + 10){//hore
        for(int i = 0; i <= LENGTH; i++){
            if(imgAfter.at<uchar>(row-i,col)==0){
                if(isBreak(row - i, col)){
                    double angle2 = getAngle(row - i, col);
                    if(angle>angle2)
                        angle-=180;
                    else
                        angle+=180;
                    if(angle-0.5 <= angle2 && angle+0.5 >= angle2){
                        connectPoints(col,row,col,row - i);
                        return true;
                    }
                    else return false;
                }
                else return false;
            }
        }
    }else{//dole
        for(int i = 0; i <= LENGTH; i++){
            if(imgAfter.at<uchar>(row+i,col)==0){
                if(isBreak(row + i, col)){
                    double angle2 = getAngle(row + i, col);
                    if(angle>angle2)
                        angle-=180;
                    else
                        angle+=180;
                    if(angle-0.5 <= angle2 && angle+0.5 >= angle2){
                        connectPoints(col,row,col,row + i);
                        return true;
                    }
                    else return false;
                }
                else return false;
            }
        }
    }
    return false;
}

double Breaks::getAngle(int row, int col)
{
    double rad = orientationMap.at<double>(row,col);
    rad = rad * 180 / M_PI;
    int dir = getDirection(row,col);
    switch(dir) {
        case 1: return 90 + rad;
        case 2: return 45 + rad;
        case 3: return rad >= 0 ? rad : 360 + rad;
        case 4: return 315 + rad;
        case 5: return 270 + rad;
        case 6: return 225 + rad;
        case 7: return 180 + rad;
        case 8: return 135 + rad;
    }
}

void Breaks::connectPoints(int row1, int col1, int row2, int col2)
{
    cv::line(imgAfter, cv::Point(row1, col1), cv::Point(row2, col2), 0, 1);
}

int Breaks::getDirection(int row, int col)
{
    if(imgAfter.at<uchar>(row-1,col)==0)
        return 5;
    if(imgAfter.at<uchar>(row-1,col+1)==0)
        return 6;
    if(imgAfter.at<uchar>(row,col+1)==0)
        return 7;
    if(imgAfter.at<uchar>(row+1,col+1)==0)
        return 8;
    if(imgAfter.at<uchar>(row+1,col)==0)
        return 1;
    if(imgAfter.at<uchar>(row+1,col-1)==0)
        return 2;
    if(imgAfter.at<uchar>(row,col-1)==0)
        return 3;
    if(imgAfter.at<uchar>(row-1,col-1)==0)
        return 4;
}
