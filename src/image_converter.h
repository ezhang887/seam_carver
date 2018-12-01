#ifndef IMAGE_CONVERTER_H
#define IMAGE_CONVERTER_H

#include <vector>

#include "ofMain.h"
#include "seam_carver.h"

class ImageConverter{

    public:
        static ofImage raw_to_of(vector<vector<Color>> image);
        static vector<vector<Color>> of_to_raw(ofImage image);
};

#endif
