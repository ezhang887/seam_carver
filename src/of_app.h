#ifndef OF_APP_H
#define OF_APP_H

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

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

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
		
};

#endif
