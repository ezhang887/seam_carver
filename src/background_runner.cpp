#include "background_runner.h"
#include "image_utils.h"

BackgroundRunner::BackgroundRunner(){
    this->has_started = false;
}

vector<vector<Color>> BackgroundRunner::getProcessedImage(){
    return processed_image;
}

void BackgroundRunner::threadedFunction(){
    ofThread::lock();

    int horizontal_iteration = 0;
    while(ofThread::isThreadRunning() && horizontal_iteration < abs(diff_height)){
        vector<int> seam = sc.find_h_seam();
        if (diff_height > 0){
            sc.remove_h_seam(seam);
        }
        else{
            sc.add_h_seam(seam);
        }
        horizontal_iteration++;
        cout << "First loop!" << " " << horizontal_iteration << endl;
    }

    int vertical_iteration = 0;
    while(ofThread::isThreadRunning() && vertical_iteration < abs(diff_width)){
        vector<int> seam = sc.find_v_seam(); 
        if (diff_width > 0){
            sc.remove_v_seam(seam);
        }
        else{
            sc.add_h_seam(seam);
        }
        vertical_iteration++;
        cout << "Second loop!" << " " << vertical_iteration << endl;
    }
    this->processed_image = sc.getCarved();
    cout << processed_image.size() << endl;
    cout << "DONE!" << endl;

    this->is_finished = true;
    ofThread::unlock();
}

void BackgroundRunner::start(ofImage image, string gif_path, int diff_height, int diff_width){
    this->image = image;
    this->gif_path = gif_path;
    this->sc.load_image(ImageUtils::of_to_raw(image));
    this->diff_height = diff_height;
    this->diff_width = diff_width;
    this->is_finished = false;
    this->has_started = true;
    this->gif_frames.clear();

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
