#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

#include <vector>

#include "ofMain.h"
#include "seam_carver.h"

namespace image_utils{

    //raw image to ofImage
    ofImage raw_to_of(vector<vector<Color>> image);
    //raw image to ofPixels
    ofPixels raw_to_ofpix(vector<vector<Color>> image);
    //ofImage to raw image
    vector<vector<Color>> of_to_raw(ofImage image);
};

#endif
