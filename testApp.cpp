#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    multiCam = new ofxCLEyeMulticam(0, CLEYE_MONO_PROCESSED, CLEYE_QVGA, 30);
    cTex.allocate(320,240,GL_LUMINANCE);
    movementTex.allocate(320, 240, GL_LUMINANCE);
    backgroundTex.allocate(320, 240, GL_LUMINANCE);
    movementOverlay.allocate(320, 240, GL_RGBA);
    currentFrame = (unsigned char *)malloc(320 * 240);
    previousFrame = (unsigned char *)malloc(320 * 240);
    movementFrame = (unsigned char *)malloc(320 * 240);
    backgroundFrame = (unsigned char *)malloc(320 * 240);
    movementOverlayFrame = (unsigned char *)malloc(320 * 240 * 4);
    bSelecting = false;
    bBgCompare = false;
}

//--------------------------------------------------------------
void testApp::update(){
    multiCam->grabFrame();
    if(multiCam->isFrameNew())
    {
        cTex.loadData(multiCam->getPixels(), 320, 240, GL_LUMINANCE);
        memcpy(currentFrame, multiCam->getPixels(), 320 * 240);
        if(!bBgCompare){
            makeMovementMap(currentFrame, previousFrame, movementFrame, 320, 240);
        } else {
            makeMovementMap(currentFrame, backgroundFrame, movementFrame, 320, 240);
        }
        makeMovementOverlay(movementFrame, movementOverlayFrame, 320, 240);
        movementTex.loadData(movementFrame, 320, 240, GL_LUMINANCE);
        movementOverlay.loadData(movementOverlayFrame, 320, 240, GL_RGBA);
        memcpy(previousFrame, currentFrame, 320 * 240);
        vector<HotSpot*>::iterator hIter;
        for(hIter = hotSpots.begin(); hIter != hotSpots.end(); hIter++){
            (*hIter)->checkForActivity(movementFrame, 320, 240);
            (*hIter)->update();
        }
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0,0,255);
    cTex.draw(0, 0);
    ofEnableAlphaBlending();
    movementOverlay.draw(0,0);
    ofDisableAlphaBlending();
    vector<HotSpot*>::iterator hIter;
    for(hIter = hotSpots.begin(); hIter != hotSpots.end(); hIter++){
        (*hIter)->draw();
    }
}

void testApp::makeMovementMap(unsigned char * _currentFrame, unsigned char * _previousFrame, unsigned char * _output, int _width, int _height)
{
    for(int y = 0; y < _height; y++){
        for(int x = 0; x < _width; x++){
            if(abs(_previousFrame[(y * _width) + x] - _currentFrame[(y * _width) + x]) > 20){
                _output[(y * _width) + x] = 255;
            } else {
                _output[(y * _width) + x] = 0;
            }
        }
    }
}

void testApp::makeMovementOverlay(unsigned char * _movementFrame, unsigned char * _movementOverlay, int _width, int _height)
{
    for(int y = 0; y < _height; y++){
        for(int x = 0; x < _width; x++){
            int movementPixel = (y * _width) + x;
            int overlayPixel = (y * _width * 4) + (x * 4);
            if(_movementFrame[movementPixel] == 255){
                _movementOverlay[overlayPixel] = 255;
                _movementOverlay[overlayPixel + 1] = 0;
                _movementOverlay[overlayPixel + 2] = 0;
                _movementOverlay[overlayPixel + 3] = 255;
            } else {
                _movementOverlay[overlayPixel] = 0;
                _movementOverlay[overlayPixel + 1] = 0;
                _movementOverlay[overlayPixel + 2] = 0;
                _movementOverlay[overlayPixel + 3] = 0;
            }
        }
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == 'b'){
        memcpy(backgroundFrame, multiCam->getPixels(), 320 * 240);
    }
    if(key == 's'){
        bBgCompare = !bBgCompare;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    if(bSelecting){
        hotSpots.back()->setBounds(x, y);
    }
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if(button == 0){
        if(!bSelecting){
            bSelecting = true;
            hotSpots.push_back(new HotSpot(x, y));
            hotSpots.back()->setBounds(x, y);
        }
    }
    if(button == 2){
        vector<HotSpot*>::iterator hIter;
        for(hIter = hotSpots.begin(); hIter != hotSpots.end();){
            if((*hIter)->isInside(x, y)){
                hIter = hotSpots.erase(hIter);
            } else {
                ++hIter;
            }
        }
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    if(button == 0){
        if(bSelecting){
            hotSpots.back()->setBounds(x, y);
            bSelecting = false;
        }
    }
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
