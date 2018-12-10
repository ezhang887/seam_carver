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
    show_gif.addListener(this, &OfApp::popup_gif);
    start_calculation.addListener(this, &OfApp::startCalculation);
    
    panel.setup();
    panel.add(load.setup("load image"));
    panel.add(enable_face_detection.setup("Enable face detection", true));
    panel.add(popup_carved.setup("popup carved image"));
    panel.add(show_gif.setup("popup GIF"));
    panel.add(target_height.setup("Set target height", image.getHeight())); 
    panel.add(target_width.setup("Set target width", image.getWidth()));
    panel.add(image_height.setup("Image height", ""));
    panel.add(image_width.setup("Image width", ""));
    panel.add(start_calculation.setup("Calculate!"));

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
    runImagePopupWindow(carved_image, main_window);
}

void OfApp::popup_gif(){
    if (!image.isAllocated()){
        return;
    }
    int h = max(image.getHeight(), carved_image.getHeight());
    int w = max(image.getWidth(), carved_image.getWidth());
    runGifPopupWindow("test.gif", h, w, main_window);
}

void OfApp::startCalculation(){
    if (!image.isAllocated()){
        return;
    }
    SeamCarver sc(ImageUtils::of_to_raw(image));
    string path = ofToDataPath("test.gif");
    gif_saver.create(path);

    int diff_height = image.getHeight() - target_height;
    int diff_width = image.getWidth() - target_width;
    if (diff_height > 0){
        for(int i=0; i<diff_height; i++){
            vector<int> seam = sc.find_h_seam();
            gif_saver.append(ImageUtils::raw_to_of(sc.getDrawn()).getPixels());
            sc.remove_h_seam(seam);
        }
    }
    else{
        for(int i=0; i<(-diff_height); i++){
            vector<int> seam = sc.find_h_seam();
            gif_saver.append(ImageUtils::raw_to_of(sc.getDrawn()).getPixels());
            sc.add_h_seam(seam);
        }
    }
    if (diff_width > 0){
        for(int i=0; i<diff_width; i++){
            vector<int> seam = sc.find_v_seam();
            gif_saver.append(ImageUtils::raw_to_of(sc.getDrawn()).getPixels());
            sc.remove_v_seam(seam);
        }
    }
    else{
        for(int i=0; i<(-diff_width); i++){
            vector<int> seam = sc.find_v_seam();
            gif_saver.append(ImageUtils::raw_to_of(sc.getDrawn()).getPixels());
            sc.add_v_seam(seam);
        }
    }
    carved_image = ImageUtils::raw_to_of(sc.getCarved());
    gif_saver.save();
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
