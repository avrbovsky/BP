#include "spur.h"

Spur::Spur(std::string fileName)
{
    this->imgBefore = cv::imread(fileName, cv::IMREAD_GRAYSCALE);
    this->imgAfter = this->imgBefore.clone();
}

Spur::Spur(cv::Mat img)
{
    this->imgBefore = img;
    this->imgAfter = this->imgBefore.clone();
}

void Spur::locateSpurs()
{
    for(int i = 1; i < this->imgAfter.rows; i++){
        for(int j = 1; j < this->imgAfter.cols; j++){
            if(this->imgAfter.at<uchar>(i,j) <= 10)
            {
                if(isEnd(i, j)){
                    if(isSpur(i,j)){
                        removeSpur(i , j);
                    }
                }
            }
        }
    }
    cv::imshow("imgAfter", this->imgAfter);
    cv::imshow("imgBefore", this->imgBefore);
}

bool Spur::isEnd(int row, int col)
{
    int neighbor = 0;
    for(int i = row - 1; i <= row + 1; i++){
        for(int j = col - 1; j <= col + 1; j++){
            if(this->imgAfter.at<uchar>(i,j) <= 10)
                neighbor++;
        }
    }
    return neighbor==2;
}

bool Spur::isSpur(int row, int col)
{
    int count = 0;
    int length = countSpurLength(row, col, -1, -1, &count);
    return length <= LENGTH && length > 0;
}

int Spur::countSpurLength(int row, int col, int prevRow, int prevCol, int *count)
{
    if(*count >= LENGTH){
        return -1000;
    }
    int neighbor = 0;
    int nextRow = prevRow;
    int nextCol = prevCol;
    for(int i = row - 1; i <= row + 1; i ++){
        for(int j = col - 1; j <= col + 1; j++){
            if(!(i == row && j == col)){
                if(this->imgAfter.at<uchar>(i,j) <= 10){
                    if(!(i == prevRow && j == prevCol)) {
                        neighbor++;
                        nextRow = i;
                        nextCol = j;
                    }
                }
            }
        }
    }
    if(neighbor > 1){
        return 0;
    }else if(neighbor == 1){
        if(prevRow == nextRow && prevCol == nextCol){
            *count += 1;
            return 1;
        }
        else{
            *count += 1;
            return 1 + countSpurLength(nextRow, nextCol, row, col, count);
        }
    }else
        return -10000;
}

void Spur::removeSpur(int row, int col)
{
    int nextRow = -1;
    int nextCol = -1;
    if(!isEnd(row, col)){
        this->imgAfter.at<uchar>(row, col) = 255;
        return;
    }
    this->imgAfter.at<uchar>(row, col) = 255;
    for(int i = row - 1; i <= row + 1; i++){
        for(int j = col - 1; j <= col + 1; j++){
            if(this->imgAfter.at<uchar>(i, j) <= 10){
                nextRow = i;
                nextCol = j;
            }
        }
    }
    if(nextRow == -1 || nextCol == -1)
        return;
    removeSpur(nextRow, nextCol);
}

