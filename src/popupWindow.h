#ifndef POPUP_WINDOW_H
#define POPUP_WINDOW_H

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"

class PopupWindow : public ofBaseApp{

    private:
        ofImage image;

    public:
        PopupWindow(ofImage image);
        void setup();
        void update();
        void draw();

};

#endif
