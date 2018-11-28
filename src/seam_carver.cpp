#include "seam_carver.h"

#include <cmath>

SeamCarver::SeamCarver(vector<vector<Color>> image){
    this->image = image;
    this->height = image.size();
    this->width = image[0].size();
    this->energy = calculate_energy();
}

vector<vector<double>> SeamCarver::calculate_energy(){
    vector<vector<double>> rv;
    for(int row=0; row<height; row++){
        vector<double> temp;
        for(int col=0; col<height; col++){
            temp.push_back(pixel_energy(row, col));
        }
        rv.push_back(temp);
    }
    return rv;
}

double SeamCarver::pixel_energy(int row, int col){
    if (row == 0 || col == 0 || row == height-1 || col == width-1){
        return 100000;
    }
    Color curr = image[row][col];
    return sqrt(distance(image[row-1][col], curr) + distance(image[row+1][col], curr)
        + distance(image[row][col-1], curr) + distance(image[row][col+1], curr));
}

int SeamCarver::distance(Color a, Color b){
    int del_r = a.r-b.r;
    int del_g = a.g-b.g;
    int del_b = a.b-b.b;
    return del_r*del_r + del_g*del_g + del_b*del_b;
}

vector<int> SeamCarver::find_h_seam(){
    //dp[i][j] = the min. cum. energy up to (i,j)
    vector<vector<double>> dp(height, vector<double>(width, 1e9));
    //bt[i][j] = the the relative delta of the horizontal index of the previous point on the min. cum. energy path leading up to (i,j)
    vector<vector<int>> bt(height, vector<int>(width, 0));

    //base case: 1st col is the default energy
    for(int row=0; row<height; row++){
        dp[row][0] = energy[row][0];
    }

    //update dp table
    for(int col=0; col<width; col++){
        for(int row=0; row<height; row++){
            int next_col = col+1;
            if (next_col >= width){
                continue;
            }
            for(int d_row = -1; d_row<=1; d_row++){
                int next_row = row+d_row;
                if (next_row < 0 || next_row >= height){
                    continue;
                }
                if (dp[row][col] + energy[next_row][next_col] < dp[next_row][next_col]){
                    dp[next_row][next_col] = dp[row][col] + energy[next_row][next_col];
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
            min_row_idx = i;
        }
    }

    //backtrack the path
    vector<int> rv;
    for(int col=width-1, row = min_row_idx; col>=0; col--){
        rv[i] = row;
        row -= bt[row][col];
    }
    return rv;
}

vector<int> SeamCarver::find_v_seam(){
    vector<int> rv;
    return rv;
}
