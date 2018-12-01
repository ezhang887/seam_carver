#include "popup.h"

PopupWindow::PopupWindow(ofImage image){
    this->image = image;
}

void PopupWindow::setup(){
    save.addListener(this, &PopupWindow::saveImage);
    save.setup("Save Image");
}

void PopupWindow::draw(){
    save.draw();
    if (image.isAllocated()){
        image.draw(0,20);
    }
}

void PopupWindow::update(){
}

void PopupWindow::saveImage(){
    ofFileDialogResult result = ofSystemSaveDialog("saved.jpg", "Save");
    if(result.bSuccess) {
        string path = result.getPath();
        ofImage to_save(image);
        to_save.save(path);
    }
}

void runPopupWindow(ofImage image){
    ofGLFWWindowSettings settings;
    settings.resizable = false;
    settings.setSize(image.getWidth(), image.getHeight() + 20);

    shared_ptr<ofAppBaseWindow> window = ofCreateWindow(settings);
    shared_ptr<PopupWindow> popup(new PopupWindow(image));
    ofRunApp(window, popup);
}
