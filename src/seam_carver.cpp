#include "seam_carver.h"

#include <cmath>

SeamCarver::SeamCarver(vector<vector<Color>> image){
    this->image = image;
    this->height = image.size();
    this->width = image[0].size();
    this->energy = calculate_energy();
}

vector<vector<int>> SeamCarver::calculate_energy(){
    vector<vector<int>> rv;
    for(int row=0; row<height; row++){
        vector<int> temp;
        for(int col=0; col<height; col++){
            temp.push_back(pixel_energy(row, col));
        }
        rv.push_back(temp);
    }
    return rv;
}

int SeamCarver::pixel_energy(int row, int col){
    if (row == 0 || col == 0 || row == height-1 || col == width-1){
        return 1000;
    }
    Color curr = image[row][col];
    return distance(image[row-1][col], curr) + distance(image[row+1][col], curr)
        + distance(image[row][col-1], curr) + distance(image[row][col+1], curr);
}

int SeamCarver::distance(Color a, Color b){
    int del_r = a.r-b.r;
    int del_g = a.g-b.g;
    int del_b = a.b-b.b;
    return del_r*del_r + del_g*del_g + del_b*del_b;
}
