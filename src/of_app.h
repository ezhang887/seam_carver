#ifndef OF_APP_H
#define OF_APP_H

#include "ofMain.h"
#include "ofxGui.h"

class OfApp : public ofBaseApp{

    private: 
        ofxPanel panel;
        ofxButton save;
        ofxButton popup_carved;
        ofxButton popup_seams;
        ofxButton load;
        ofxInputField<int> target_height;
        ofxInputField<int> target_width;

        ofImage image;

        void saveImage();
        void loadImage();
        void popupCarved();
        void popupSeams();

    public:
        void setup();
        void update();
        void draw();
};

#endif
