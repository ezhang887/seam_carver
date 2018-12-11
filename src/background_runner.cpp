#include "background_runner.h"
#include "image_utils.h"
#include "constants.h"

BackgroundRunner::BackgroundRunner(){
    this->has_started = false;
    this->face_bounds = constants::kNoFaceBounds;
}

vector<vector<Color>> BackgroundRunner::getProcessedImage(){
    return processed_image;
}

void BackgroundRunner::threadedFunction(){
    ofThread::lock();

    if (enable_gif){
        gif_saver.create(gif_path);
    }

    int horizontal_iteration = 0;
    while(ofThread::isThreadRunning() && horizontal_iteration < abs(diff_height)){
        vector<int> seam = sc.find_h_seam(face_bounds);
        if (enable_gif){
            ofPixels drawn_pixels = ImageUtils::raw_to_ofpix(sc.getDrawn());
            gif_saver.append(drawn_pixels);
        }
        if (diff_height > 0){
            sc.remove_h_seam(seam);
        }
        else{
            sc.add_h_seam(seam);
        }
        horizontal_iteration++;
        progress++;
    }

    int vertical_iteration = 0;
    while(ofThread::isThreadRunning() && vertical_iteration < abs(diff_width)){
        vector<int> seam = sc.find_v_seam(face_bounds); 
        if (enable_gif){
            ofPixels drawn_pixels = ImageUtils::raw_to_ofpix(sc.getDrawn());
            gif_saver.append(drawn_pixels);
        }
        if (diff_width > 0){
            sc.remove_v_seam(seam);
        }
        else{
            sc.add_h_seam(seam);
        }
        vertical_iteration++;
        progress++;
    }
    this->processed_image = sc.getCarved();
    if (enable_gif){
        gif_saver.save();
    }

    cout << "DONE!" << endl;

    this->is_finished = true;

    ofThread::unlock();
}

void BackgroundRunner::start(ofImage image, FaceBounds face_bounds, string gif_path, int diff_height, int diff_width, bool enable_gif){
    this->image = image;
    this->gif_path = gif_path;
    this->sc.load_image(ImageUtils::of_to_raw(image));
    this->diff_height = diff_height;
    this->diff_width = diff_width;
    this->is_finished = false;
    this->has_started = true;
    this->enable_gif = enable_gif;
    this->face_bounds = face_bounds;
    this->progress = 0;

    ofThread::startThread();
}

void BackgroundRunner::stop(){
    ofThread::stopThread();
    this->has_started = false;
}

bool BackgroundRunner::finished(){
    return is_finished;
}

bool BackgroundRunner::started(){
    return has_started;
}

int BackgroundRunner::get_progress(){
    double total = abs(diff_height) + abs(diff_width);
    double rv = (double)progress/total;
    return (int)(rv*100);
}
