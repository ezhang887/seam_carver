#include "image_utils.h"
#include "assert.h"
#include <algorithm>

using std::min;

ofImage ImageUtils::raw_to_of(vector<vector<Color>> image){
    const int height = image.size();
    const int width = image[0].size();
    ofPixels pixels;
    pixels.allocate(width, height, OF_IMAGE_COLOR);
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            ofColor color(image[i][j].r, image[i][j].g, image[i][j].b);
            pixels.setColor(j,i,color);
        }
    }
    return ofImage(pixels);
}

ofPixels ImageUtils::raw_to_ofpix(vector<vector<Color>> image){
    const int height = image.size();
    const int width = image[0].size();
    ofPixels pixels;
    pixels.allocate(width, height, OF_IMAGE_COLOR);
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            ofColor color(image[i][j].r, image[i][j].g, image[i][j].b);
            pixels.setColor(j,i,color);
        }
    }
    return pixels;
}

vector<vector<Color>> ImageUtils::of_to_raw(ofImage image){
    const int height = image.getHeight();
    const int width = image.getWidth();
    vector<vector<Color>> rv;
    ofPixels pixels = image.getPixels();
    for(int i=0; i<height; i++){
        vector<Color> temp;
        for(int j=0; j<width; j++){
            ofColor of_c = pixels.getColor(j,i);
            Color c(of_c.r, of_c.g, of_c.b);
            temp.push_back(c);
        }
        rv.push_back(temp);
    }
    return rv;
}

ofImage ImageUtils::draw_seams(vector<vector<Color>> image, vector<vector<int>> h_seams, vector<vector<int>> v_seams){
    int height = image.size();
    int width = image[0].size();
    for(auto seam : h_seams){
        assert(seam.size() == width);
    }
    for(auto seam : v_seams){
        assert(seam.size() == height);
    }
    for(int i=0; i<h_seams.size(); i++){
        auto seam = h_seams[i];
        for(int col=0; col<seam.size(); col++){
            int row = seam[col];
            image[min(row+i,height-1)][col] = Color(255, 0, 0);
        }
    }
    for(int i=0; i<v_seams.size(); i++){
        auto seam = v_seams[i];
        for(int row=0; row<seam.size(); row++){
            if (row >= height){
                continue;
            }
            int col = seam[row];
            image[row][min(col+i,width-1)] = Color(0, 0, 255);
        }
    }
    return raw_to_of(image);
}
