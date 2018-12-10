#ifndef OF_APP_H
#define OF_APP_H

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "ofxProgressBar.h"
#include "background_runner.h"

class OfApp : public ofBaseApp{

    private: 
        ofxPanel panel;
        ofxButton popup_carved;
        ofxButton show_gif;
        ofxButton load;
        ofxInputField<int> target_height;
        ofxInputField<int> target_width;
        ofxLabel image_height;
        ofxLabel image_width;
        ofxButton start_calculation;

        ofImage image;
        ofImage carved_image;
        ofxToggle enable_face_detection;
        ofxToggle enable_gif_generation;

        ofxProgressBar progress_bar;

        shared_ptr<ofAppBaseWindow> main_window;

        ofxCv::ObjectFinder face_detector;

        BackgroundRunner background_runner;

        bool gif_generated;
        int progress;

        void loadImage();
        void popup_gif();
        void popupCarved();
        void startCalculation();

    public:
        OfApp(shared_ptr<ofAppBaseWindow>& main_window);
        void setup();
        void update();
        void draw();
        void exit();
};

#endif
