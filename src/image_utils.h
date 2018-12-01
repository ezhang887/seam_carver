#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

#include <vector>

#include "ofMain.h"
#include "seam_carver.h"

class ImageUtils{

    public:
        static ofImage raw_to_of(vector<vector<Color>> image);
        static vector<vector<Color>> of_to_raw(ofImage image);
        static ofImage draw_seams(vector<vector<Color>> image, vector<vector<int>> h_seams, vector<vector<int>> v_seams);
};

#endif
