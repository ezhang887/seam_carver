#include "ofMain.h"
#include "of_app.h"
#include "constants.h"

int main(int argc, char** argv){
    ofGLFWWindowSettings settings;
    settings.resizable = false;
    settings.setSize(constants::kMainWindowHeight, constants::kMainWindowWidth);
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

    shared_ptr<OfApp> mainApp(new OfApp(mainWindow));
    ofRunApp(mainWindow, mainApp);
    ofSetWindowTitle("Seam Carver");
    ofRunMainLoop();
}
