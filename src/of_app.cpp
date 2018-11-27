#include "of_app.h"
#include "popup.h"


void OfApp::setup(){
    save.addListener(this, &OfApp::saveImage);
    load.addListener(this, &OfApp::loadImage);
    popup.addListener(this, &OfApp::popupImage);
    
    gui.setup();
    gui.add(save.setup("save image"));
    gui.add(load.setup("load image"));
    gui.add(popup.setup("popup image"));
    gui.add(target_width.setup("Set target width", 0));
    gui.add(target_height.setup("Set target height", 0));
}

void OfApp::saveImage(){
    ofFileDialogResult result = ofSystemSaveDialog("saved.jpg", "Save");
    if(result.bSuccess) {
        string path = result.getPath();
        ofImage to_save(test);
        to_save.save(path);
    }
    
}

void OfApp::loadImage(){
    ofFileDialogResult result = ofSystemLoadDialog("Load file");
    if (result.bSuccess){
        string path = result.getPath();
        test.load(path);
        int max_h = 700;
        int max_w = 700;
        double ratio = test.getHeight()/test.getWidth();
        int bigger = max(test.getHeight(), test.getWidth());
        test.resize(max_w * test.getWidth()/bigger,max_h * test.getHeight()/bigger);
    }
}

void OfApp::popupImage(){
    ofGLFWWindowSettings settings;
    settings.resizable = false;
    settings.setSize(700, 700);
    shared_ptr<ofAppBaseWindow> window = ofCreateWindow(settings);

    shared_ptr<PopupWindow> popup(new PopupWindow(test));

    ofRunApp(window, popup);
}

void OfApp::update(){

}

void OfApp::draw(){
    ofBackgroundGradient(ofColor::white, ofColor::gray);
    gui.draw();
    if (test.isAllocated()){
        test.draw(500, 10);
    }
}
