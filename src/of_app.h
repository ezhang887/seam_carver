#ifndef OF_APP_H
#define OF_APP_H

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"

class OfApp : public ofBaseApp{

    private: 
        ofxPanel panel;
        ofxButton popup_carved;
        ofxButton popup_seams;
        ofxButton load;
        ofxInputField<int> target_height;
        ofxInputField<int> target_width;
        ofxLabel image_height;
        ofxLabel image_width;

        ofImage image;

        shared_ptr<ofAppBaseWindow> main_window;

        ofxCv::ObjectFinder face_detector;

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
