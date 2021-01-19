    #include "hilditch.h"

Hilditch::Hilditch(cv::Mat imgOriginal)
{
    this->imgOriginal = imgOriginal;
    this->imgAfter = imgOriginal.clone();
}

void Hilditch::skeletonization()
{
    int i = 0;
    bool changed = true;
    while(changed){
        changed = removePixel(&i);
    }
    std::cout << i << std::endl;
}

bool Hilditch::removePixel(int* count)
{
    bool removed = false;
    for(int i = 1; i < imgAfter.rows; i++){
        for(int j = 1; j < imgAfter.cols; j++){
            if(imgAfter.at<uchar>(i,j) == 0){
                int b = countNeighbours(i,j);
                if(b >= 2 && b <= 6){
                    int a = connectivity(i,j);
                    if(a == 1){
                        int p2 = imgAfter.at<uchar>(i-1, j);
                        int p4 = imgAfter.at<uchar>(i, j+1);
                        int p6 = imgAfter.at<uchar>(i+1, j);
                        int p8 = imgAfter.at<uchar>(i, j-1);
                        if((p2 > 10 || p4 > 10 || p8 > 10) || connectivity(i+1, j) != 1)
                            if((p2 > 10 || p4 > 10 || p6 > 10) || connectivity(i, j+1) != 1){
                                imgAfter.at<uchar>(i,j) = 255;
                                *count += 1;
                                removed = true;
                            }
                    }
                }
            }
        }
    }
    return removed;
}

int Hilditch::countNeighbours(int row, int col)
{
    int neighbours = 0;
    for(int i = row - 1; i <= row + 1; i++){
        for(int j = col - 1; j <= col + 1; j++){
            if(imgAfter.at<uchar>(i,j) == 0)
                neighbours++;
        }
    }
    return --neighbours;
}

int Hilditch::connectivity(int row, int col)
{
    int p[8];
    p[0] = imgAfter.at<uchar>(row-1, col);
    p[1] = imgAfter.at<uchar>(row-1, col+1);
    p[2] = imgAfter.at<uchar>(row, col+1);
    p[3] = imgAfter.at<uchar>(row+1, col+1);
    p[4] = imgAfter.at<uchar>(row+1, col);
    p[5] = imgAfter.at<uchar>(row+1, col-1);
    p[6] = imgAfter.at<uchar>(row, col-1);
    p[7] = imgAfter.at<uchar>(row-1, col-1);
    bool space = true;
    int a = 0;
    for(int i = 0; i < 8; i++){
        if(space && p[i] == 0){
            a++;
            space = false;
        }else if(p[i] == 255){
            space = true;
        }
    }
    if(a > 1 && p[0] == 0 && p[7] == 0)
        a--;
    return a;
}
