#include <unistd.h>
#include "popup.h"
#include "constants.h"

ImagePopupWindow::ImagePopupWindow(ofImage image){
    this->image = image;
}

void ImagePopupWindow::setup(){
    save.addListener(this, &ImagePopupWindow::saveImage);
    save.setup("Save Image");
}

void ImagePopupWindow::draw(){
    save.draw();
    if (image.isAllocated()){
        image.draw(constants::kPopupImageX, constants::kPopupImageY);
    }
}

void ImagePopupWindow::update(){
}

void ImagePopupWindow::saveImage(){
    ofFileDialogResult result = ofSystemSaveDialog("saved.jpg", "Save");
    if(result.bSuccess) {
        string path = result.getPath();
        ofImage to_save(image);
        to_save.save(path);
    }
}

GifPopupWindow::GifPopupWindow(string path){
    this->path = path;
    this->index = 0;
}

void GifPopupWindow::setup(){
    gif_loader.load(path);
    pause.setup("Pause GIF", false);
}

void GifPopupWindow::update(){
    if (!pause){
        index++;
        if (index > gif_loader.pages.size()-1){
            index = 0;
        }
        usleep(constants::kGifSleepTimeMicros);
    }
}

void GifPopupWindow::draw(){
    pause.draw();

    //for whatever reason, the gif library returns the image with a blue tint, probably in BGR format instead of RGB
    //the following code from the OF forums somehow fixes this...even though it looks like it's not doing anything....
    //https://forum.openframeworks.cc/t/ofimage-from-gif-displays-with-blue-tint/22989/4
    ofImage image = gif_loader.pages[index];
    ofPixels pixels = image.getPixels();
    image.setFromPixels(pixels);
    image.draw(constants::kPopupImageX, constants::kPopupImageY);
}

void runImagePopupWindow(ofImage image, shared_ptr<ofAppBaseWindow>& main_window){
    ofGLFWWindowSettings settings;
    settings.resizable = false;
    settings.setSize(image.getWidth() + constants::kPopupImageX, image.getHeight() + constants::kPopupImageY);
    settings.shareContextWith = main_window;

    shared_ptr<ofAppBaseWindow> window = ofCreateWindow(settings);
    shared_ptr<ImagePopupWindow> popup(new ImagePopupWindow(image));
    ofSetWindowTitle("Carved Image");
    ofRunApp(window, popup);
}

void runGifPopupWindow(string path, int height, int width, shared_ptr<ofAppBaseWindow>& main_window){
    ofGLFWWindowSettings settings;
    settings.resizable = false;
    settings.setSize(width + constants::kPopupGifX, height + constants::kPopupGifY);
    settings.shareContextWith = main_window;

    shared_ptr<ofAppBaseWindow> window = ofCreateWindow(settings);
    shared_ptr<GifPopupWindow> popup(new GifPopupWindow(path));
    ofSetWindowTitle("Carving Process");
    ofRunApp(window, popup);

}
