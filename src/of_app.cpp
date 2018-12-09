#include "of_app.h"
#include "popup.h"
#include "seam_carver.h"
#include "image_utils.h"

OfApp::OfApp(shared_ptr<ofAppBaseWindow>& main_window){
    this->main_window = main_window;
}

void OfApp::setup(){
    load.addListener(this, &OfApp::loadImage);
    popup_carved.addListener(this, &OfApp::popupCarved);
    popup_seams.addListener(this, &OfApp::popupSeams);
    start_calculation.addListener(this, &OfApp::startCalculation);
    
    panel.setup();
    panel.add(load.setup("load image"));
    panel.add(enable_face_detection.setup("Enable face detection", true));
    panel.add(popup_carved.setup("popup carved image"));
    panel.add(popup_seams.setup("popup seams on image"));
    panel.add(target_height.setup("Set target height", image.getHeight())); panel.add(target_width.setup("Set target width", image.getWidth()));
    panel.add(image_height.setup("Image height", ""));
    panel.add(image_width.setup("Image width", ""));
    panel.add(start_calculation.setup("Start seam carver calculation"));

    face_detector.setup("haarcascade_frontalface_default.xml");
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
    if (enable_face_detection){
        face_detector.update(image);
    }
    image_height = ofToString(image.getHeight());
    image_width = ofToString(image.getWidth());

    //reset the processed images to the new image
    carved_image = image;
    seams_image = image;
}

void OfApp::popupCarved(){
    if (!image.isAllocated()){
        return;
    }
    runPopupWindow(carved_image, main_window);
}

void OfApp::popupSeams(){
    if (!image.isAllocated()){
        return;
    }
    runPopupWindow(seams_image, main_window);
}

void OfApp::startCalculation(){
    if (!image.isAllocated()){
        return;
    }
    SeamCarver sc(ImageUtils::of_to_raw(image));
    int diff_height = image.getHeight() - target_height;
    int diff_width = image.getWidth() - target_width;
    vector<vector<int>> h_seams;
    vector<vector<int>> v_seams;
    if (diff_height > 0){
        h_seams = sc.carve_h_seams(diff_height);
    }
    else{
        h_seams = sc.add_h_seams(-diff_height);
    }
    if (diff_width > 0){
        v_seams = sc.carve_v_seams(diff_width);
    }
    else{
        v_seams = sc.add_v_seams(-diff_width);
    }
    carved_image = ImageUtils::raw_to_of(sc.getCarved());
    seams_image = ImageUtils::draw_seams(ImageUtils::of_to_raw(image), h_seams, v_seams);
}

void OfApp::update(){

}

void OfApp::draw(){
    ofBackgroundGradient(ofColor::white, ofColor::gray);
    panel.draw();
    if (image.isAllocated()){
        image.draw(500, 10);
        if (enable_face_detection){
            for(int i = 0; i < face_detector.size(); i++){
                ofNoFill();
                ofRectangle object = face_detector.getObject(i);
                object.setX(500 + object.getX());
                object.setY(10 + object.getY());
                ofDrawRectangle(object);
            }
        }
    }
}
