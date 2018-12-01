#include "of_app.h"
#include "popup.h"


void OfApp::setup(){
    save.addListener(this, &OfApp::saveImage);
    load.addListener(this, &OfApp::loadImage);
    popup_carved.addListener(this, &OfApp::popupCarved);
    popup_seams.addListener(this, &OfApp::popupSeams);
    
    panel.setup();
    panel.add(save.setup("save image"));
    panel.add(load.setup("load image"));
    panel.add(popup_carved.setup("popup carved image"));
    panel.add(popup_seams.setup("popup seams on image"));
    panel.add(target_width.setup("Set target width", image.getWidth()));
    panel.add(target_height.setup("Set target height", image.getHeight()));
}

void OfApp::saveImage(){
    ofFileDialogResult result = ofSystemSaveDialog("saved.jpg", "Save");
    if(result.bSuccess) {
        string path = result.getPath();
        ofImage to_save(image);
        to_save.save(path);
    }
}

void OfApp::loadImage(){
    ofFileDialogResult result = ofSystemLoadDialog("Load file");
    if (result.bSuccess){
        string path = result.getPath();
        image.load(path);
        int max_h = 700;
        int max_w = 700;
        int bigger = max(image.getHeight(), image.getWidth());
        image.resize(max_w * image.getWidth()/bigger,max_h * image.getHeight()/bigger);
    }
}

void OfApp::popupCarved(){
    if (!image.isAllocated()){
        return;
    }
    ofPixels pixels = image.getPixels();
    ofPixels new_pixels;
    new_pixels.allocate(image.getWidth()/2, image.getHeight()/2, OF_IMAGE_COLOR);
    for(int i=0; i<image.getWidth()/2; i++){
        for(int j=0; j<image.getHeight()/2; j++){
            new_pixels.setColor(i,j,image.getColor(i,j));
        }
    }
    
    runPopupWindow(new_pixels);
}

void OfApp::popupSeams(){
    if (!image.isAllocated()){
        return;
    }

    ofPixels pixels = image.getPixels();
    ofPixels new_pixels;
    new_pixels.allocate(image.getWidth(), image.getHeight(), OF_IMAGE_COLOR);
    for(int i=0; i<image.getWidth(); i++){
        for(int j=0; j<image.getHeight(); j++){
            if (i == j){
                new_pixels.setColor(i,j,ofColor(255,0,0));
            }
            else{
                new_pixels.setColor(i,j,image.getColor(i,j));
            }
        }
    }

    runPopupWindow(new_pixels);
}

void OfApp::update(){

}

void OfApp::draw(){
    ofBackgroundGradient(ofColor::white, ofColor::gray);
    panel.draw();
    if (image.isAllocated()){
        image.draw(500, 10);
    }
}
