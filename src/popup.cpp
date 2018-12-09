#include "popup.h"
#include <unistd.h>

PopupWindow::PopupWindow(string path, int update_duration){
    this->should_update = true;
    this->path = path;
    this->image.load(path);
    this->update_duration = update_duration;
}

PopupWindow::PopupWindow(ofImage image){
    this->should_update = false;
    this->image = image;
    this->update_duration = 0;
    this->path = "";
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
    if (should_update){
        image.load(path);
        usleep(update_duration * 1000000);
    }
}

void PopupWindow::saveImage(){
    ofFileDialogResult result = ofSystemSaveDialog("saved.jpg", "Save");
    if(result.bSuccess) {
        string path = result.getPath();
        ofImage to_save(image);
        to_save.save(path);
    }
}

void runPopupWindow(string path, int height, int width, shared_ptr<ofAppBaseWindow>& main_window){
    ofGLFWWindowSettings settings;
    settings.resizable = false;
    settings.setSize(width, height+20);
    settings.shareContextWith = main_window;

    shared_ptr<ofAppBaseWindow> window = ofCreateWindow(settings);
    shared_ptr<PopupWindow> popup(new PopupWindow(path, 0.5));
    ofRunApp(window, popup);
}

void runPopupWindow(ofImage image, shared_ptr<ofAppBaseWindow>& main_window){
    ofGLFWWindowSettings settings;
    settings.resizable = false;
    settings.setSize(image.getWidth(), image.getHeight()+20);
    settings.shareContextWith = main_window;

    shared_ptr<ofAppBaseWindow> window = ofCreateWindow(settings);
    shared_ptr<PopupWindow> popup(new PopupWindow(image));
    ofRunApp(window, popup);
}
