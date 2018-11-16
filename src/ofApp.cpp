#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    save.addListener(this, &ofApp::buttonPressed);
    load.addListener(this, &ofApp::loadImage);
    
    gui.setup();
    gui.add(save.setup("save image"));
    gui.add(load.setup("load image"));
    gui.add(target_width.setup("Set target width", 0));
    gui.add(target_height.setup("Set target height", 0));
}

void ofApp::buttonPressed(){
    cout << "BUTTON PRESSED" << endl;
}

void ofApp::loadImage(){
    ofFileDialogResult result = ofSystemLoadDialog("Load file");
    if (result.bSuccess){
        string path = result.getPath();
        test.load(path);
        int max_h = 700;
        int max_w = 700;
        double ratio = test.getHeight()/test.getWidth();
        int bigger = max(test.getHeight(), test.getWidth());
        test.resize(max_w * test.getWidth()/bigger,max_h * test.getHeight()/bigger);
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor::white, ofColor::gray);
    gui.draw();
    if (test.isAllocated()){
        test.draw(500, 10);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
