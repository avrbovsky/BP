#include "islands.h"

Island::Island(std::string fileName)
{
    this->imgBefore = cv::imread(fileName, cv::IMREAD_GRAYSCALE);
    this->imgAfter = this->imgBefore.clone();
}

Island::Island(cv::Mat img){
    this->imgBefore = img;
    this->imgAfter = this->imgBefore.clone();
}

void Island::removeIslands()
{
    for(int i = 1; i < this->imgBefore.rows; i++){
        for(int j = 1; j < this->imgBefore.cols; j++){
            if(this->imgAfter.at<uchar>(i,j) <= 10){
                int neighbors = HelperClass().countNeighbors(this->imgAfter, i , j);
                if(neighbors == 1){
                    if(isIsland(i,j)){
                        removeIsland(i,j);
                    }
                }
            }
        }
    }
    cv::imshow("imgBeforeIslands", this->imgBefore);
    cv::imshow("imgAfterIslands", this->imgAfter);
}

bool Island::isIsland(int row, int col)
{
    int count = 0;
    int length = countIslandLength(row, col, -1, -1, &count);
    return length <= LENGTH && length > 0;
}

int Island::countIslandLength(int row, int col, int prevRow, int prevCol, int *count)
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
        return -1000;
    }else if(neighbor == 1){
        if(prevRow == nextRow && prevCol == nextCol){
            *count += 1;
            return 1;
        }
        else{
            *count += 1;
            return 1 + countIslandLength(nextRow, nextCol, row, col, count);
        }
    }else
        return 0;
}

void Island::removeIsland(int row, int col)
{
    int nextRow = -1;
    int nextCol = -1;
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
    removeIsland(nextRow, nextCol);
}
