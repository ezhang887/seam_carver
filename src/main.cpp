#include "ofMain.h"
#include "of_app.h"

int main(){
    ofGLFWWindowSettings settings;
    settings.resizable = false;
    settings.setSize(1280, 720);
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

    shared_ptr<ofApp> mainApp(new ofApp);
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
}
