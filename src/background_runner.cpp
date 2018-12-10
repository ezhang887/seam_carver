#include "background_runner.h"
#include "image_utils.h"

BackgroundRunner::BackgroundRunner(ofImage image, string gif_path){
    this->image = image;
    this->gif_path = gif_path;
    this->sc.load_image(ImageUtils::of_to_raw(image));
}

BackgroundRunner::~BackgroundRunner(){

}

ofImage BackgroundRunner::getProcessedImage(){

}

void BackgroundRunner::update(){
    int horizontal_iteration = 0;
    while(ofThread::isThreadRunning() && horizontal_iteration < abs(diff_height)){
        vector<int> seam = sc.find_h_seam();
        gif_saver.append(ImageUtils::raw_to_of(sc.getDrawn()).getPixels());
        if (diff_height > 0){
            sc.remove_h_seam(seam);
        }
        else{
            sc.add_h_seam(seam);
        }
        horizontal_iteration++;
    }

    int vertical_iteration = 0;
    while(ofThread::isThreadRunning() && vertical_iteration < abs(diff_width)){
        vector<int> seam = sc.find_v_seam(); 
        gif_saver.append(ImageUtils::raw_to_of(sc.getDrawn()).getPixels());
        if (diff_width > 0){
            sc.remove_v_seam(seam);
        }
        else{
            sc.add_h_seam(seam);
        }
        vertical_iteration++;
    }
}

void BackgroundRunner::start(int diff_height, int diff_width){
    ofThread::startThread();
    gif_saver.create(gif_path);
    this->diff_height = diff_height;
    this->diff_width = diff_width;
}

void BackgroundRunner::stop(){
    ofThread::stopThread();
    gif_saver.save();
}
