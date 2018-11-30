#ifndef OF_APP_H
#define OF_APP_H

#include "ofMain.h"
#include "ofxGui.h"

class OfApp : public ofBaseApp{

    private: 
        ofxPanel gui;
        ofxButton save;
        ofxButton popup;
        ofxButton load;
        ofxInputField<int> target_height;
        ofxInputField<int> target_width;

        ofImage test;

        void saveImage();
        void loadImage();
        void popupImage();

    public:
        void setup();
        void update();
        void draw();
};

#endif
