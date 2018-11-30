#include "popup.h"

PopupWindow::PopupWindow(ofImage image){
    this->image = image;
}

void PopupWindow::setup(){

}

void PopupWindow::update(){

}

void PopupWindow::draw(){
    if (image.isAllocated()){
        image.draw(0,0);
    }
}
