#ifndef BACKGROUND_RUNNER_H
#define BACKGROUND_RUNNER_H

#include <ofMain.h>
#include <ofxGif.h>
#include "seam_carver.h"

class BackgroundRunner : public ofThread{

    private:
        int diff_height;
        int diff_width;
        int progress;
        bool is_finished;
        bool has_started;
        bool enable_gif;

        SeamCarver sc;
        FaceBounds face_bounds;
        ofImage image;
        vector<vector<Color>> processed_image;
        string gif_path;

        ofxGIF::fiGifSaver gif_saver;
        
        void threadedFunction();

    public:
        BackgroundRunner();
        vector<vector<Color>> getProcessedImage();
        void start(ofImage image, FaceBounds face_bounds, string gif_path, int diff_height, int diff_width, bool enable_gif);
        void stop();
        bool finished();
        bool started();
        int get_progress();
};

#endif
