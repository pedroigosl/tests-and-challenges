#include "cvfilter.h"
#include <cmath>
#include <algorithm>
#include <iostream>

gsImage::gsImage(char *fileName)
{
    FILE *fp;
    int pixel;

    fp = fopen(fileName, "r");

    fscanf(fp, "P%d", &this->p);
    fscanf(fp, "%d", &this->width);
    fscanf(fp, "%d", &this->height);
    fscanf(fp, "%d", &this->max);

    int h = this->height;
    int w = this->width;
    int m = this->max;
    if (h > 0 && w > 0 && m > 0)
    {
        this->image.resize(w, vector<int>(h, 0));
        // for (int x = 0; x < w; x++)
        //     this->img[x] = new int[h];
        for (int y = 0; y < h; y++)
            for (int x = 0; x < w; x++)
            {
                fscanf(fp, "%d", &pixel);
                this->image[x][y] = pixel;
            }
    }
    fclose(fp);
}

void gsImage::saveAs(char *fileName)
{
    FILE *fp;

    fp = fopen(fileName, "w");

    fprintf(fp, "P2\n");
    fprintf(fp, "%d ", this->width);
    fprintf(fp, "%d\n", this->height);
    fprintf(fp, "%d\n", this->max);

    int h = this->height;
    int w = this->width;
    int m = this->max;

    if (h > 0 && w > 0 && m > 0)
    {
        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                fprintf(fp, "%d ", image[x][y]);
            }
            fprintf(fp, "\n");
        }
    }
    fclose(fp);
}

int gsImage::getHeight()
{
    return this->height;
}
int gsImage::getWidth()
{
    return this->width;
}

void gsImage::setPixel(int x, int y, float val)
{
    this->image[x][y] = val;
}

int gsImage::getPixel(int x, int y)
{
    return image[x][y];
}

void scale(gsImage &img)
{
    int absval = 0;

    vector<vector<int>> v = img.image;
    int h = img.getHeight();
    int w = img.getWidth();
    // auto max = *max_element(v.begin(), v.end());
    // auto min = *min_element(v.begin(), v.end());
    // auto minmax = std::minmax_element(v.begin(), v.end());
    // std::cout << "max: " << minmax.second << "min: " << minmax.first;
    int max = -255;
    int min = 255;
    int val = 0;
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            val = img.getPixel(x, y);
            if (absval == 1 && val < 0)
            {
                val *= -1;
                img.setPixel(x, y, val);
            }
            if (val > max)
            {
                max = val;
            }
            if (val < min)
            {
                min = val;
            }
        }
    }

    std::cout << "max: " << max << "min: " << min;

    int new_val = 0;

    for (int x = 0; x < w - 1; x++)
    {
        for (int y = 0; y < h - 1; y++)
        {
            val = img.getPixel(x, y);
            new_val = 255 * float(float(val - min) / float(max - min));
            img.setPixel(x, y, new_val);
        }
    }
}

int sumFilter(int x, int y, gsImage img, vector<vector<float>> filter)
{
    int order = filter.size();
    float sum = 0.0;
    for (int xx = -int(order / 2); xx <= int(order / 2); xx++)
    {
        sum += filter[int(order / 2) + xx][int(order / 2)] * float(img.getPixel(x + xx, y));
        for (int yy = 1; yy <= int(order / 2); yy++)
        {
            sum += filter[int(order / 2) + xx][int(order / 2) + yy] * float(img.getPixel(x + xx, y + yy)) + filter[int(order / 2) + xx][int(order / 2) - yy] * float(img.getPixel(x + xx, y - yy));
        }
    }
    return int(sum);
}

int medianFilter(int x, int y, gsImage img, vector<vector<float>> filter)
{
    int order = filter.size();
    vector<int> values;
    for (int xx = -int(order / 2); xx <= int(order / 2); xx++)
    {
        values.push_back(img.getPixel(x + xx, y));
        for (int yy = 1; yy <= int(order / 2); yy++)
        {
            values.push_back(img.getPixel(x + xx, y + yy));
            values.push_back(img.getPixel(x + xx, y - yy));
        }
    }
    sort(values.begin(), values.end());
    return values.at(int(values.size() / 2));
}

int threshFilter(int x, int y, gsImage img, vector<vector<float>> filter)
{
    int thrCount = filter[0].size();
    int step = 255 / thrCount;
    for (int i = 0; i < thrCount; i++)
    {
        if (img.getPixel(x, y) < filter[0][i])
        {
            return 255 - i * step;
        }
    }
    return 0;
}

gsImage applyFilter(gsImage img, vector<vector<float>> filter, int (*func)(int, int, gsImage, vector<vector<float>>))
{
    int order = filter.size();

    int h = img.getHeight();
    int w = img.getWidth();

    gsImage output = img;

    for (int x = 1; x < w - 1; x++)
    {

        for (int y = 1; y < h - 1; y++)
        {
            int result = func(x, y, img, filter);
            output.setPixel(x, y, result);
        }
    }

    return output;
}
