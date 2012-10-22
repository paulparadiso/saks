#include "MotionCam.h"

MotionCam::MotionCam()
{
    multiCam = new ofxCLEyeMulticam(0, CLEYE_MONO_PROCESSED, CLEYE_QVGA, 30);
    pos.set(0,0);
    init();
}

MotionCam::MotionCam(int _camera)
{
    multiCam = new ofxCLEyeMulticam(_camera, CLEYE_MONO_PROCESSED, CLEYE_QVGA, 30);
    pos.set(0,0);
    init();
}

MotionCam::MotionCam(int _camera, int _x, int _y)
{
    multiCam = new ofxCLEyeMulticam(_camera, CLEYE_MONO_PROCESSED, CLEYE_QVGA, 30);
    pos.set(_x, _y);
    init();
}

MotionCam::~MotionCam()
{
    //dtor
}

void MotionCam::init()
{
    cTex.allocate(320,240,GL_LUMINANCE);
    movementOverlay.allocate(320, 240, GL_RGBA);
    currentFrame = (unsigned char *)malloc(320 * 240);
    previousFrame = (unsigned char *)malloc(320 * 240);
    movementFrame = (unsigned char *)malloc(320 * 240);
    backgroundFrame = (unsigned char *)malloc(320 * 240);
    movementOverlayFrame = (unsigned char *)malloc(320 * 240 * 4);
    bBgCompare = false;
    bDrawCamera = true;
    cameraThreshold = 20;
    SubObMediator::Instance()->addObserver("mouse-changed", this);
}

void MotionCam::start()
{
    startThread(true, false);
}

void MotionCam::stop()
{
    stopThread();
}

void MotionCam::threadedFunction()
{
    while(isThreadRunning() != 0){
        if(lock()){
            update();
            unlock();
        }
    }
}

void MotionCam::update()
{
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
        if(bDrawCamera) {
            makeMovementOverlay(movementFrame, movementOverlayFrame, 320, 240);
        }
        memcpy(previousFrame, currentFrame, 320 * 240);
        vector<HotSpot*>::iterator hIter;
        for(hIter = hotSpots.begin(); hIter != hotSpots.end(); hIter++){
            (*hIter)->checkForActivity(movementFrame, 320, 240);
            (*hIter)->update();
        }
    }
}

void MotionCam::update(string _subName, Subject *_sub)
{
    if(_subName == "mouse-changed"){
        //cout << "Got mouse change." << endl;
        string state = _sub->getAttr("mouseState");
        int x = ofToInt(_sub->getAttr("mouseX"));
        int y = ofToInt(_sub->getAttr("mouseY"));
        int button = ofToInt(_sub->getAttr("mouseButton"));
        processMouse(state, x, y, button);
    }
}

void MotionCam::processMouse(string _state, int _x, int _y, int _button)
{
    if(isInside(_x, _y)){
        if(_state == "down"){
            if(_button == 0){
                if(!bSelecting){
                    bSelecting = true;
                    hotSpots.push_back(new HotSpot(_x, _y));
                    hotSpots.back()->setBounds(_x, _y);
                    }
                }
            if(_button == 2){
                    vector<HotSpot*>::iterator hIter;
                    for(hIter = hotSpots.begin(); hIter != hotSpots.end();){
                        if((*hIter)->isInside(_x, _y)){
                            hIter = hotSpots.erase(hIter);
                        } else {
                            ++hIter;
                        }
                    }
                }
        }
        if(_state == "drag"){
            if(bSelecting){
                hotSpots.back()->setBounds(_x, _y);
            }
        }
        if(_state == "up"){
            if(_button == 0){
                if(bSelecting){
                    hotSpots.back()->setBounds(_x, _y);
                    bSelecting = false;
                    int count = 0;
                    vector<HotSpot*>::iterator hIter;
                    for(hIter = hotSpots.begin(); hIter != hotSpots.end(); hIter++){
                        (*hIter)->setNumber(count++);
                    }
                }
            }
        }
    }
}

bool MotionCam::isInside(int _x, int _y)
{
    if((_x > pos.x && _x < pos.x + 320) && (_y > pos.y && _y < pos.y + 240)){
        return true;
    } else {
        return false;
    }
}

void MotionCam::draw()
{
    if(bDrawCamera){
        cTex.draw(pos.x, pos.y);
        ofEnableAlphaBlending();
        movementOverlay.loadData(movementOverlayFrame, 320, 240, GL_RGBA);
        movementOverlay.draw(pos.x, pos.y);
        ofDisableAlphaBlending();
        vector<HotSpot*>::iterator hIter;
        for(hIter = hotSpots.begin(); hIter != hotSpots.end(); hIter++){
            (*hIter)->draw();
        }
    }
}

void MotionCam::captureBackground()
{
    memcpy(backgroundFrame, multiCam->getPixels(), 320 * 240);
}

void MotionCam::makeMovementMap(unsigned char * _currentFrame, unsigned char * _previousFrame, unsigned char * _output, int _width, int _height)
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

void MotionCam::makeMovementOverlay(unsigned char * _movementFrame, unsigned char * _movementOverlay, int _width, int _height)
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
