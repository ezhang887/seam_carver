#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

#include <vector>

#include "ofMain.h"
#include "seam_carver.h"

class ImageUtils{

    public:
        //raw image to ofImage
        static ofImage raw_to_of(vector<vector<Color>> image);
        static ofPixels raw_to_ofpix(vector<vector<Color>> image);
        //ofImage to raw image
        static vector<vector<Color>> of_to_raw(ofImage image);
};

#endif
