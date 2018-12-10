#ifndef BACKGROUND_RUNNER_H
#define BACKGROUND_RUNNER_H

#include <ofMain.h>
#include "seam_carver.h"

class BackgroundRunner : public ofThread{

    private:
        int diff_height;
        int diff_width;
        bool is_finished;
        bool has_started;

        SeamCarver sc;
        ofImage image;
        vector<vector<Color>> processed_image;
        vector<vector<ofPixels>> gif_frames;
        string gif_path;
        
        void threadedFunction();

    public:
        BackgroundRunner();
        vector<vector<Color>> getProcessedImage();
        void start(ofImage image, string gif_path, int diff_height, int diff_width);
        void stop();
        bool finished();
        bool started();

};

#endif
