#include "of_app.h"
#include "popup.h"
#include "image_utils.h"
#include "constants.h"

OfApp::OfApp(shared_ptr<ofAppBaseWindow>& main_window){
    this->main_window = main_window;
    gif_generated = false;
}

void OfApp::setup(){
    load.addListener(this, &OfApp::loadImage);
    popup_carved.addListener(this, &OfApp::popupCarved);
    show_gif.addListener(this, &OfApp::popup_gif);
    start_calculation.addListener(this, &OfApp::startCalculation);
    
    panel.setup();
    panel.add(load.setup("load image"));
    panel.add(enable_face_detection.setup("Enable face detection?", true));
    panel.add(enable_gif_generation.setup("Enable gif calculation?", true));
    panel.add(popup_carved.setup("popup carved image"));
    panel.add(show_gif.setup("popup GIF"));
    panel.add(target_height.setup("Set target height", image.getHeight())); 
    panel.add(target_width.setup("Set target width", image.getWidth()));
    panel.add(image_height.setup("Image height", ""));
    panel.add(image_width.setup("Image width", ""));
    panel.add(start_calculation.setup("Calculate!"));

    progress = 0;
    progress_bar = ofxProgressBar(constants::kProgressBarX, constants::kProgressBarY, constants::kProgressBarWidth, constants::kProgressBarHeight, &progress, 100);
    ofTrueTypeFont font;
    font.load("verdana.ttf", constants::kProgressBarFontSize, true, true);
    progress_bar.setFont(font);
    progress_bar.setBarColor(ofColor::white);
    progress_bar.setBackgroundColor(ofColor::black);
    progress_bar.setLabel("Seam Carving Progress...");

    face_detector.setup("haarcascade_frontalface_default.xml");
}

void OfApp::loadImage(){
    ofFileDialogResult result = ofSystemLoadDialog("Load file");
    if (result.bSuccess){
        string path = result.getPath();
        image.load(path);
        const int max_size = constants::kMaxLoadedImageDimension;
        int bigger = max(image.getHeight(), image.getWidth());
        image.resize(max_size*image.getWidth()/bigger, max_size*image.getHeight()/bigger);
        image_height = ofToString(image.getHeight());
        image_width = ofToString(image.getWidth());
    }
    if (result.bSuccess && enable_face_detection){
        face_detector.update(image);
    }

    //reset the processed images to the new image
    carved_image = image;
}

void OfApp::popupCarved(){
    if (!image.isAllocated()){
        return;
    }
    runImagePopupWindow(carved_image, main_window);
}

void OfApp::popup_gif(){
    if (!image.isAllocated() || !gif_generated){
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
    if (background_runner.started() && !background_runner.finished()){
        return;
    }
    int diff_height = image.getHeight() - target_height;
    int diff_width = image.getWidth() - target_width;
    string path = ofToDataPath("test.gif");
    gif_generated = enable_gif_generation;
    background_runner.start(image, path, diff_height, diff_width, enable_gif_generation);
}

void OfApp::update(){
    if (background_runner.started() && !background_runner.finished()){
        progress = background_runner.get_progress();
    }
    if (background_runner.started() && background_runner.finished()){
        progress = 0;
        background_runner.stop();
        carved_image = ImageUtils::raw_to_of(background_runner.getProcessedImage());
    }
}

void OfApp::draw(){
    ofBackgroundGradient(ofColor::aliceBlue, ofColor::lightBlue);
    panel.draw();
    progress_bar.draw();
    if (image.isAllocated()){
        image.draw(constants::kLoadedImageX, constants::kLoadedImageY);
        if (enable_face_detection){
            for(int i = 0; i < face_detector.size(); i++){
                ofNoFill();
                ofRectangle object = face_detector.getObject(i);
                object.setX(constants::kLoadedImageX + object.getX());
                object.setY(constants::kLoadedImageY + object.getY());
                ofDrawRectangle(object);
            }
        }
    }
}

void OfApp::exit(){
    background_runner.stop();
}
