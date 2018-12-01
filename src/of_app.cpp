#include "of_app.h"
#include "popup.h"
#include "seam_carver.h"
#include "image_utils.h"


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
    SeamCarver sc(ImageUtils::of_to_raw(image));
    sc.carve_h_seams(150);
    ofImage new_image = ImageUtils::raw_to_of(sc.getImage());

    runPopupWindow(new_image);
}

void OfApp::popupSeams(){
    if (!image.isAllocated()){
        return;
    }

    SeamCarver sc(ImageUtils::of_to_raw(image));
    vector<vector<int>> h_seams = sc.carve_h_seams(50);
    vector<vector<int>> v_seams = sc.carve_v_seams(50);
    ofImage new_image = ImageUtils::draw_seams(ImageUtils::of_to_raw(image), h_seams, v_seams);

    runPopupWindow(new_image);
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
