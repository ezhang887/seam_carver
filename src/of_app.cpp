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
    
    panel.setup();
    panel.add(load.setup("load image"));
    panel.add(popup_carved.setup("popup carved image"));
    panel.add(popup_seams.setup("popup seams on image"));
    panel.add(target_width.setup("Set target width", image.getWidth()));
    panel.add(target_height.setup("Set target height", image.getHeight()));

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
    face_detector.update(image);
}

void OfApp::popupCarved(){
    if (!image.isAllocated()){
        return;
    }
    SeamCarver sc(ImageUtils::of_to_raw(image));
    int diff_height = image.getHeight()-target_height;
    int diff_width = image.getWidth()-target_width;
    if (diff_height > 0){
        sc.carve_h_seams(diff_height);
    }
    else{
        sc.add_h_seams(-diff_height);
    }
    if (diff_width > 0){
        sc.carve_v_seams(diff_width);
    }
    else{
        sc.add_v_seams(-diff_width);
    }
    ofImage new_image = ImageUtils::raw_to_of(sc.getImage());

    runPopupWindow(new_image, main_window);
}

void OfApp::popupSeams(){
    if (!image.isAllocated()){
        return;
    }
    SeamCarver sc(ImageUtils::of_to_raw(image));
    vector<vector<int>> h_seams = sc.carve_h_seams(image.getHeight()-target_height);
    vector<vector<int>> v_seams = sc.carve_v_seams(image.getWidth()-target_width);
    ofImage new_image = ImageUtils::draw_seams(ImageUtils::of_to_raw(image), h_seams, v_seams);

    runPopupWindow(new_image, main_window);
}

void OfApp::update(){

}

void OfApp::draw(){
    ofBackgroundGradient(ofColor::white, ofColor::gray);
    panel.draw();
    if (image.isAllocated()){
        image.draw(500, 10);
	for(int i = 0; i < face_detector.size(); i++){
            ofNoFill();
            ofRectangle object = face_detector.getObject(i);
            object.setX(500 + object.getX());
            object.setY(10 + object.getY());
            ofDrawRectangle(object);
	}
    }
}
