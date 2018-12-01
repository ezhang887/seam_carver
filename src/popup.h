#ifndef POPUP_H
#define POPUP_H

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"

class PopupWindow : public ofBaseApp{

    private:
        ofxButton save;
        ofImage image;

        void saveImage();

    public:
        PopupWindow(ofImage image);
        void setup();
        void update();
        void draw();

};

void runPopupWindow(ofImage image);

#endif
