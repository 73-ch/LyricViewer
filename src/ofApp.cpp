#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableDepthTest();
    ofEnableLighting();
    ofSetBackgroundColor(20);
    
    ofTrueTypeFontSettings font_settings("NotoSansCJKjp-Medium.otf", 50);
    font_settings.addRanges(ofAlphabet::Japanese);
    font_settings.addRange(ofUnicode::Latin);
    font_settings.addRange(ofUnicode::Latin1Supplement);
    font_settings.addRange(ofUnicode::Space);
    font_settings.addRange(ofUnicode::NumberForms);
    font_settings.addRange(ofUnicode::Hiragana);
    font_settings.addRange(ofUnicode::Katakana);
    font_settings.contours = true;
    font_settings.antialiased = true;
    font.load(font_settings);
    
    main_text = "Hello world";
    
    text_mesh = new TextMesh(font);
    
    text_mesh->setText(main_text, 5);
    
    ofxSubscribeOsc(2323, "/set_text", [&](const string &text) {
        text_mesh->setText(text, 5);
        kakkuri_mesh->setText(text, 30);
        
        main_text = text;
    });
    
    ofxSubscribeOsc(2323, "/set_scene", scene);
    ofxSubscribeOsc(2323, "/set_index_mode", [=](const int index){
        ofLogNotice() << index;
        kakkuri_mesh->setIndexMode(static_cast<KakkuriIndexMode>(index));
    });
    
    ofxSubscribeOsc(2323, "/set_primitive_mode", [=](const int i, const bool auto_index = false){
        ofLogNotice() << i;
        kakkuri_mesh->setPrimitiveMode(static_cast<ofPrimitiveMode>(i), auto_index);
    });
    
    ofxSubscribeOsc(2323, "/set_roughness", roughness);

    kakkuri_mesh = new KakkuriText(font);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    float time = ofGetElapsedTimef();
    cam.setPosition(sin(time) * 500, 200 * ofNoise(time * 0.1), cos(time) * 500);
    cam.lookAt(vec3(0));
    light.setPosition(0, 300, sin(time)* 500);
}

//--------------------------------------------------------------
void ofApp::draw(){
    float time = ofGetElapsedTimef();
    
    cam.begin();
    ofSetColor(200, 200, 200);
    light.enable();
    
    if (scene) {
        text_mesh->draw();
    } else {
        kakkuri_mesh->setText(main_text, roughness);
        kakkuri_mesh->draw();
    }

    cam.end();
    ofSetColor(255);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 10);
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
