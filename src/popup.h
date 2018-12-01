#ifndef POPUP_H
#define POPUP_H

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"

class PopupWindow : public ofBaseApp{

    private:
        ofImage image;

    public:
        PopupWindow(ofImage image);
        void setup();
        void draw();

};

void runPopupWindow(ofImage image);

#endif
