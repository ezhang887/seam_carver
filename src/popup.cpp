#include "popup.h"

PopupWindow::PopupWindow(ofImage image){
    this->image = image;
}

void PopupWindow::setup(){

}

void PopupWindow::draw(){
    if (image.isAllocated()){
        image.draw(0,0);
    }
}

void runPopupWindow(ofImage image){
    ofGLFWWindowSettings settings;
    settings.resizable = false;
    settings.setSize(image.getWidth(), image.getHeight());

    shared_ptr<ofAppBaseWindow> window = ofCreateWindow(settings);
    shared_ptr<PopupWindow> popup(new PopupWindow(image));
    ofRunApp(window, popup);
}
