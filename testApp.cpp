#include "testApp.h"
#include "ofxSimpleGuiToo.h"
#include "CLEyeMulticam.h"

//--------------------------------------------------------------
void testApp::setup(){

    cout << "Have " << ofxCLEyeMulticam::getCameraCount() << " cameras." << endl;

    motionCam = new MotionCam(0,0,0);
    motionCam->start();

    /*

    motionCam2 = new MotionCam(1,320,0);
    motionCam2->start();

    motionCam3 = new MotionCam(2,640,0);
    motionCam3->start();

    motionCam4 = new MotionCam(3,0,240);
    motionCam4->start();

    motionCam5 = new MotionCam(4,320,240);
    motionCam5->start();

    motionCam6 = new MotionCam(5,640,240);
    motionCam6->start();

    */

    /*
    cout << "Have " << CLEyeGetCameraCount() << " cameras." << endl;
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
    display = new IntensityDisplay(0, 240);
    cameraThreshold = 20;
    */
    display = new IntensityDisplay(0, 240);
    window.loadImage("single_window.png");
}

//--------------------------------------------------------------
void testApp::update(){
    //motionCam->update();
    /*
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
        //movementTex.loadData(movementFrame, 320, 240, GL_LUMINANCE);
        movementOverlay.loadData(movementOverlayFrame, 320, 240, GL_RGBA);
        memcpy(previousFrame, currentFrame, 320 * 240);
        vector<HotSpot*>::iterator hIter;
        for(hIter = hotSpots.begin(); hIter != hotSpots.end(); hIter++){
            (*hIter)->checkForActivity(movementFrame, 320, 240);
            (*hIter)->update();
        }
    }
    */
}

//--------------------------------------------------------------
void testApp::draw(){

    motionCam->draw();

    /*
    motionCam2->draw();
    motionCam3->draw();
    motionCam4->draw();
    motionCam5->draw();
    motionCam6->draw();
    */

    /*
    ofBackground(255,255,255);
    cTex.draw(0, 0);
    ofEnableAlphaBlending();
    movementOverlay.draw(0,0);
    ofDisableAlphaBlending();
    vector<HotSpot*>::iterator hIter;
    for(hIter = hotSpots.begin(); hIter != hotSpots.end(); hIter++){
        (*hIter)->draw();
    }
    */
    //window.draw(0,280);
    //display->draw();

}

/*

void testApp::makeMovementMap(unsigned char * _currentFrame, unsigned char * _previousFrame, unsigned char * _output, int _width, int _height)
{
    for(int y = 0; y < _height; y++){
        for(int x = 0; x < _width; x++){
            if(abs(_previousFrame[(y * _width) + x] - _currentFrame[(y * _width) + x]) > cameraThreshold){
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

*/

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == 'b'){
        //memcpy(backgroundFrame, multiCam->getPixels(), 320 * 240);
        motionCam->captureBackground();
    }
    if(key == 's'){
        //bBgCompare = !bBgCompare;
        motionCam->toggleCompare();
    }
    /*
    if(key == OF_KEY_UP){
        cameraThreshold++;
        if(cameraThreshold > 255){
            cameraThreshold = 255;
        }
        cout << "Threshold set to " << cameraThreshold << endl;
    }
    if(key == OF_KEY_DOWN){
        cameraThreshold--;
        if(cameraThreshold < 0){
            cameraThreshold = 0;
        }
        cout << "Threshold set to " << cameraThreshold << endl;
    }
    */
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    /*
    if(bSelecting){
        hotSpots.back()->setBounds(x, y);
    }
    */
    updateMouseState("drag", x, y, button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    /*
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
    */
    updateMouseState("down", x, y, button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    /*
    if(button == 0){
        if(bSelecting){
            hotSpots.back()->setBounds(x, y);
            bSelecting = false;
        }
    }
    */
    updateMouseState("up", x, y, button);
}

void testApp::updateMouseState(const char * _state, int _x, int _y, int _button)
{
    attrs["mouseX"] = ofToString(_x);
    attrs["mouseY"] = ofToString(_y);
    attrs["mouseButton"] = ofToString(_button);
    attrs["mouseState"] = _state;
    SubObMediator::Instance()->update("mouse-changed", this);
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
