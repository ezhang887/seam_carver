#ifndef BACKGROUND_RUNNER_H
#define BACKGROUND_RUNNER_H

#include <ofMain.h>
#include <ofxGif.h>
#include "seam_carver.h"

class BackgroundRunner : public ofThread{

    private:
        int diff_height;
        int diff_width;

        SeamCarver sc;
        ofxGIF::fiGifSaver gif_saver;
        ofImage image;
        string gif_path;
        
        virtual void update();

    public:
        BackgroundRunner(ofImage image, string gif_path);
        ~BackgroundRunner();
        ofImage getProcessedImage();
        void start(int diff_height, int diff_width);
        void stop();

};

#endif
