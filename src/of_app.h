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

        shared_ptr<ofAppBaseWindow> main_window;

        void saveImage();
        void loadImage();
        void popupCarved();
        void popupSeams();

    public:
        OfApp(shared_ptr<ofAppBaseWindow>& main_window);
        void setup();
        void update();
        void draw();
};

#endif
