#include <iostream>

using namespace std;

#include "cvfilter.cpp"

int main()
{

    gsImage img_in = gsImage("catbone.pgm");

    vector<vector<float>> laplace_8_filter = {{1, 1, 1},
                                              {1, -8, 1},
                                              {1, 1, 1}};

    // vector<vector<float>> laplace_4_filter = {{0, 1, 0},
    //                                           {1, -4, 1},
    //                                           {0, 1, 0}};

    vector<vector<float>> mean_filter = {{1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0},
                                         {1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0},
                                         {1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0}};

    vector<vector<float>> prewit_h_filter = {{-1, 0, 1},
                                             {-1, 0, 1},
                                             {-1, 0, 1}};

    vector<vector<float>> prewit_v_filter = {{-1, -1, -1},
                                             {0, 0, 0},
                                             {1, 1, 1}};

    vector<vector<float>> sobel_h_filter = {{-1, 0, 1},
                                            {-2, 0, 2},
                                            {-1, 0, 1}};

    vector<vector<float>> sobel_v_filter = {{-1, -2, -1},
                                            {0, 0, 0},
                                            {1, 2, 1}};

    vector<vector<float>> gaussian_filter = {{1, 2, 1},
                                             {2, 4, 2},
                                             {1, 2, 1}};

    vector<vector<float>> median_filter = {{1, 1, 1},
                                           {1, 1, 1},
                                           {1, 1, 1}};

    vector<vector<float>> threshold_filter = {{128}};

    vector<vector<float>> multithreshold_filter = {{50, 128, 200}};

    // cout << mean_filter[0][0];

    cout << "h: " << img_in.getHeight() << " w: " << img_in.getWidth();
    gsImage img_out = applyFilter(img_in, multithreshold_filter, &threshFilter);
    // gsImage img_out = img_in;
    scale(img_out);
    img_out.saveAs("catbonemultithresh.pgm");

    return 0;
}
