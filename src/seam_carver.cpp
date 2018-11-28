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
    return distance(image[row-1][col], curr) + distance(image[row+1][col], curr)
        + distance(image[row][col-1], curr) + distance(image[row][col+1], curr);
}

double SeamCarver::distance(Color a, Color b){
    double del_r = a.r-b.r;
    double del_g = a.g-b.g;
    double del_b = a.b-b.b;
    return sqrt(del_r*del_r + del_g*del_g + del_b*del_b);
}

vector<int> SeamCarver::find_h_seam(){
    //check to make sure we are not transposed
    if (transposed){
        transpose();
    }

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
            //compare with each neighbor in the next column
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
            min_row_idx = row;
        }
    }

    //backtrack the path
    vector<int> rv(width);
    //we subtract the delta that brought us to this row after each iteration
    //and decrement the column index by one
    for(int col=width-1, row = min_row_idx; col>=0; col--, row-=bt[row][col]){
        rv[col] = row;
    }
    return rv;
}

vector<int> SeamCarver::find_v_seam(){
    if (!transposed){
        transpose();
    }
    return find_h_seam();
}

void SeamCarver::remove_h_seam(vector<int> seam){
    //check to make sure we are not transposed
    if (transposed){
        transpose();
    }

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
    //re-calculate energy array
    energy = calculate_energy();
}

void SeamCarver::remove_v_seam(vector<int> seam){
    if (!transposed){
        transpose();
    }
    remove_h_seam(seam);
}

void SeamCarver::transpose(){
    transposed = !transposed;
    //new_image[col][row] = image[row][col]
    vector<vector<Color>> new_image(width, vector<Color>(height, Color(0,0,0)));
    //new_energy[col][row] = energy[row][col]
    vector<vector<double>> new_energy(width, vector<double>(height, 0));
    for(int row=0; row<height; row++){
        for(int col=0; col<width; col++){
            new_image[col][row] = image[row][col];
            new_energy[col][row] = energy[row][col];
        }
    }
    //update image + energy
    image = new_image;
    energy = new_energy;
    //swap width and height member variables
    int temp = height;
    height = width;
    width = temp;
}

vector<vector<Color>> SeamCarver::getCarved(int v_seams, int h_seams){
    for(int i=0; i<v_seams; i++){
        vector<int> v_seam = find_v_seam();
        remove_v_seam(v_seam);
    }
    for(int i=0; i<h_seams; i++){
        vector<int> h_seam = find_h_seam();
        remove_h_seam(h_seam);
    }
}
