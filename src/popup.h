#ifndef POPUP_H
#define POPUP_H

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "ofxGif.h"

class ImagePopupWindow : public ofBaseApp{

    private:
        ofxButton save;
        ofImage image;

        void saveImage();

    public:
        ImagePopupWindow(ofImage image);
        void setup();
        void update();
        void draw();

};

class GifPopupWindow : public ofBaseApp{

    private:
        ofxToggle pause;
        ofxGIF::fiGifLoader gif_loader;
        string path;
        int index;

    public:
        GifPopupWindow(string path);
        void setup();
        void update();
        void draw();


};

void runImagePopupWindow(ofImage image, shared_ptr<ofAppBaseWindow>& main_window);

void runGifPopupWindow(string path, int height, int width, shared_ptr<ofAppBaseWindow>& main_window);

#endif
