#include "spur.h"

Spur::Spur()
{

}

void Spur::locateSpurs(std::string file)
{
    cv::Mat image = cv::imread(file, cv::IMREAD_GRAYSCALE);
    cv::imshow("imgBeforeSpurs", image);

    for(int i = 1; i < image.rows; i++){
        for(int j = 1; j < image.cols; j++){
            if(image.at<uchar>(i,j) <= 10)
            {
                if(isEnd(image, i, j)){
                    if(isSpur(image,i,j)){
                        removeSpur(image, i , j);
                    }
                }
            }
        }
    }
    cv::imshow("imgAfterSpurs", image);
}

bool Spur::isEnd(cv::Mat img, int row, int col)
{
    int neighbor = 0;
    for(int i = row - 1; i <= row + 1; i++){
        for(int j = col - 1; j <= col + 1; j++){
            if(img.at<uchar>(i,j) <= 10)
                neighbor++;
        }
    }
    return neighbor==2;
}

bool Spur::isSpur(cv::Mat img, int row, int col)
{
    int count = 0;
    int length = countSpurLength(img, row, col, -1, -1, &count);
    return length <= LENGTH && length > 0;
}

int Spur::countSpurLength(cv::Mat img, int row, int col, int prevRow, int prevCol, int *count)
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
                if(img.at<uchar>(i,j) <= 10){
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
            return 1 + countSpurLength(img, nextRow, nextCol, row, col, count);
        }
    }else
        return -10000;
}

void Spur::removeSpur(cv::Mat img, int row, int col)
{
    int nextRow = -1;
    int nextCol = -1;
    if(!isEnd(img, row, col)){
        img.at<uchar>(row, col) = 255;
        return;
    }
    img.at<uchar>(row, col) = 255;
    for(int i = row - 1; i <= row + 1; i++){
        for(int j = col - 1; j <= col + 1; j++){
            if(img.at<uchar>(i, j) <= 10){
                nextRow = i;
                nextCol = j;
            }
        }
    }
    if(nextRow == -1 || nextCol == -1)
        return;
    removeSpur(img, nextRow, nextCol);
}

