#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

class gsImage
{
public:
    gsImage(char *fileName);
    int getWidth();
    int getHeight();
    void setPixel(int x, int y, float val);
    int getPixel(int x, int y);
    void saveAs(char *fileName);
    vector<vector<int>> image;

private:
    // vector<vector<int>> image;
    int width = 0;
    int height = 0;
    int max = 0;
    int p = 5;
};

void scale(gsImage &img);

int sumFilter(int x, int y, gsImage img, vector<vector<float>> filter);

int medianFilter(int x, int y, gsImage img, vector<vector<float>> filter);

int threshFilter(int x, int y, gsImage img, vector<vector<float>> filter);

gsImage applyFilter(gsImage img, vector<vector<float>> filter, int (*func)(int, int, gsImage, vector<vector<float>>));