#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    button.addListener(this, &ofApp::buttonPressed);
    string path = "images/test.jpg";
    test.load(path);

    int max_h = 700;
    int max_w = 700;
    double ratio = test.getHeight()/test.getWidth();
    int bigger = max(test.getHeight(), test.getWidth());
    test.resize(max_w * test.getWidth()/bigger,max_h * test.getHeight()/bigger);

    gui.setup();
    gui.add(button.setup("button"));
    gui.add(input.setup("Set target width", 0));
}

void ofApp::buttonPressed(){
    cout << "BUTTON PRESSED" << endl;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor::white, ofColor::gray);
    gui.draw();
    test.draw(500, 10);
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
