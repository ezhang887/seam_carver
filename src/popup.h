#ifndef POPUP_H
#define POPUP_H

#include <string>

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"

using std::string;

class PopupWindow : public ofBaseApp{

    private:
        ofxButton save;
        ofImage image;
        int update_duration;
        bool should_update;
        string path;

        void saveImage();

    public:
        PopupWindow(string path, int update_duration);
        PopupWindow(ofImage image);
        void setup();
        void update();
        void draw();

};

void runPopupWindow(string path, int height, int width, shared_ptr<ofAppBaseWindow>& main_window);
void runPopupWindow(ofImage image, shared_ptr<ofAppBaseWindow>& main_window);

#endif
