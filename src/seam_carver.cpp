#include "seam_carver.h"

#include <cmath>
#include <cassert>
#include <algorithm>
#include <iostream>

#include "constants.h"

using std::cout;
using std::endl;
using std::min;
using std::max;

SeamCarver::SeamCarver(){
    this->transposed = false;
}

SeamCarver::SeamCarver(vector<vector<Color>> image){
    this->image = image;
    this->drawn_image = image;
    this->height = image.size();
    this->width = image[0].size();
    this->transposed = false;
}

Color SeamCarver::average(Color a, Color b){ int r_avg = (a.r + b.r)/2;
    int g_avg = (a.g + b.g)/2;
    int b_avg = (a.b + b.b)/2;
    return Color(r_avg, g_avg, b_avg);
}

double SeamCarver::energy(int row, int col, FaceBounds& face_bounds){
    if (row >= face_bounds.y-constants::kFaceDetectionOffsetHeight && row <= face_bounds.upper_y+constants::kFaceDetectionOffsetHeight && col >= face_bounds.x && col <= face_bounds.upper_x){
        return 1e9;
    }
    Color curr = image[row][col];
    double rv = 0;
    if (row > 0){
        rv += distance(image[row-1][col], curr);
    }
    if (row < height-1){
        rv += distance(image[row+1][col], curr);
    }
    if (col > 0){
        rv += distance(image[row][col-1], curr);
    }
    if (col < width-1){
        rv += distance(image[row][col+1], curr);
    }
    return rv;
}

double SeamCarver::distance(Color a, Color b){
    double del_r = a.r-b.r;
    double del_g = a.g-b.g;
    double del_b = a.b-b.b;
    return sqrt(del_r*del_r + del_g*del_g + del_b*del_b);
}

vector<int> SeamCarver::find_h_seam(FaceBounds& face_bounds){
    //dp[i][j] = the min. cum. energy on a seam up to (i,j)
    //dp[i][0] = energy
    //dp[i][j+1] = min(dp[i][j+1], dp[i][j]+dp[i+k][j+1]) for k = (-1,0,1)
    vector<vector<double>> dp(height, vector<double>(width, 1e9));
    //bt[i][j] = the the relative delta of the horizontal index of the previous point on the min. cum. energy path leading up to (i,j)
    vector<vector<int>> bt(height, vector<int>(width, 0));
    //base case: 1st col is the default energy
    for(int row=0; row<height; row++){
        dp[row][0] = energy(row, 0, face_bounds);
    }

    //update dp table
    for(int col=0; col<width; col++){
        for(int row=0; row<height; row++){
            int next_col = col+1;
            if (next_col >= width){
                continue;
            }
            //compare with each neighbor in the next column
            for(int d_row = -1; d_row<=1; d_row++){
                int next_row = row+d_row;
                if (next_row < 0 || next_row >= height){
                    continue;
                }
                if (dp[row][col] + energy(next_row, next_col, face_bounds) < dp[next_row][next_col]){
                    dp[next_row][next_col] = dp[row][col] + energy(next_row, next_col, face_bounds);
                    bt[next_row][next_col] = d_row;
                }
            }
        }
    }

    //figure out which index to start backtracking from
    //this is the index at the furthest right column with min. cum. energy
    int min_row_idx = 0;
    int min_cum_energy = 1e9;
    for(int row=0; row<height; row++){
        int curr = dp[row][width-1];
        if (curr < min_cum_energy){
            min_cum_energy = curr;
            min_row_idx = row;
        }
    }

    //backtrack the path
    vector<int> rv(width);
    bool above_face_bound = true;
    //we subtract the delta that brought us to this row after each iteration
    //and decrement the column index by one
    for(int col=width-1, row = min_row_idx; col>=0; col--, row-=bt[row][col]){
        if (col >= face_bounds.x && col <= face_bounds.upper_x){
            if (row > face_bounds.y){
                above_face_bound = false;
            }
        }
        rv[col] = row;
    }
    if (above_face_bound){
        if (face_bounds.y > 0){
            face_bounds.y--;
            face_bounds.upper_y--;
        }
    }
    drawn_image = image;
    for(int col=0; col<rv.size(); col++){
        int row = rv[col];
        drawn_image[row][col] = constants::kRed;
    }
    return rv;
}

vector<int> SeamCarver::find_v_seam(FaceBounds& face_bounds){
    if (!transposed){
        transpose();
    }
    //TODO: TRANSPOSE FACE_BOUNDS
    FaceBounds transposed_bounds;
    transposed_bounds.x = face_bounds.y;
    transposed_bounds.y = face_bounds.x;
    transposed_bounds.upper_x = face_bounds.upper_y;
    transposed_bounds.upper_y = face_bounds.upper_x;
    auto rv = find_h_seam(transposed_bounds);
    transpose();
    return rv;
}

void SeamCarver::load_image(vector<vector<Color>> image){
    this->image = image;
    this->drawn_image = image;
    this->height = image.size();
    this->width = image[0].size();
    this->transposed = false;
}

void SeamCarver::remove_h_seam(vector<int> seam){
    //decrement height
    height--;
    //create a new image 2d array without the specified seam
    vector<vector<Color>> new_image(height, vector<Color>(width, Color(0,0,0)));
    for(int col=0; col<width; col++){
        //index of the row in the current col that is part of the given seam
        int curr_row_removed_idx = seam[col];
        for(int row=0; row<height; row++){
            if (row < curr_row_removed_idx){
                new_image[row][col] = image[row][col];
            }
            else{
                new_image[row][col] = image[row+1][col];
            }
        }
    }
    //update member variable with new image
    image = new_image;
    drawn_image = image;
}

void SeamCarver::remove_v_seam(vector<int> seam){
    if (!transposed){
        transpose();
    }
    remove_h_seam(seam);
    transpose();
}

void SeamCarver::add_h_seam(vector<int> seam){
    height++;
    vector<vector<Color>> new_image(height, vector<Color>(width, Color(0,0,0)));
    for(int col=0; col<width; col++){
        int curr_row_min_idx = seam[col];
        for(int row=0; row<height; row++){
            if (row == 0 || row < curr_row_min_idx){
                new_image[row][col] = image[row][col];
            }
            else if (row == curr_row_min_idx || row == curr_row_min_idx+1){
                new_image[row][col] = average(image[row-1][col], image[row+1][col]);
            }
            else{
                new_image[row][col] = image[row-1][col];
            }
        }
    }
    image = new_image;
    drawn_image = image;
}

void SeamCarver::add_v_seam(vector<int> seam){
    if (!transposed){
        transpose();
    }
    add_h_seam(seam);
    transpose();
}

void SeamCarver::transpose(){
    transposed = !transposed;
    //new_image[col][row] = image[row][col]
    vector<vector<Color>> new_image(width, vector<Color>(height, Color(0,0,0)));
    for(int row=0; row<height; row++){
        for(int col=0; col<width; col++){
            new_image[col][row] = image[row][col];
        }
    }
    //update image
    image = new_image;
    vector<vector<Color>> new_drawn_image(width, vector<Color>(height, Color(0,0,0)));
    for(int row=0; row<height; row++){
        for(int col=0; col<width; col++){
            new_drawn_image[col][row] = drawn_image[row][col];
        }
    }
    drawn_image = new_drawn_image;
    //swap width and height member variables
    int temp = height;
    height = width;
    width = temp;
}

vector<vector<Color>> SeamCarver::getCarved(){
    if (transposed){
        transpose();
    }
    return image;
}

vector<vector<Color>> SeamCarver::getDrawn(){
    if (transposed){
        transpose();
    }
    return drawn_image;
}
