#include "ofxCLEyeMulticam.h"
#include <stdio.h>

ofxCLEyeMulticam::ofxCLEyeMulticam()
{
    createCamera(CLEyeGetCameraUUID(0), CLEYE_QVGA, CLEYE_COLOR_PROCESSED, 30);
    init();
}

ofxCLEyeMulticam::ofxCLEyeMulticam(GUID _guid, int _colorMode, int _resolution, int _framerate)
{
    createCamera(_guid, _colorMode, _resolution, _framerate);
    init();
}

ofxCLEyeMulticam::ofxCLEyeMulticam(int _camera, int _colorMode, int _resolution, int _framerate)
{
    createCamera(CLEyeGetCameraUUID(_camera), _colorMode, _resolution, _framerate);
    init();
}

ofxCLEyeMulticam::~ofxCLEyeMulticam()
{
    //dtor
}

int ofxCLEyeMulticam::getCameraCount()
{
    int camCount =  CLEyeGetCameraCount();
    return camCount;
}

GUID ofxCLEyeMulticam::getCameraUUID(int _camera)
{
    return CLEyeGetCameraUUID(_camera);
}

void ofxCLEyeMulticam::createCamera(GUID _guid, int _colorMode, int _resolution, int _framerate)
{
    mGuid = _guid;
    mColorMode = _colorMode;
    mResolution = _resolution;
    mCam = CLEyeCreateCamera(_guid, (CLEyeCameraColorMode)_colorMode, (CLEyeCameraResolution)_resolution, _framerate);
    switch(mResolution)
    {
        case(CLEYE_QVGA):
            mCameraWidth = 320;
            mCameraHeight = 240;
            break;
        case(CLEYE_VGA):
            mCameraWidth = 640;
            mCameraHeight = 480;
            break;
        default:
            mCameraWidth = 0;
            mCameraHeight = 0;
            break;
    }
    if(mColorMode == CLEYE_MONO_PROCESSED || mColorMode == CLEYE_MONO_RAW){
        mCameraColorDepth = 1;
    } else {
        mCameraColorDepth = 4;
    }
    vBuf = (unsigned char *)malloc(mCameraWidth * mCameraHeight * mCameraColorDepth);
    if(CLEyeCameraStart(mCam))
    {
        printf("Started Camera - Width = %d, Height = %d, Color Depth = %d\n", mCameraWidth, mCameraHeight, mCameraColorDepth);
    } else
    {
        printf("Failed to Start Camera\n");
    }
}

void ofxCLEyeMulticam::init()
{
    bNewFrame = false;
}

void ofxCLEyeMulticam::grabFrame()
{
    if(CLEyeCameraGetFrame(mCam, (PBYTE)vBuf))
    {
        bNewFrame = true;
    } else {
        bNewFrame = false;
    }
}

bool ofxCLEyeMulticam::isFrameNew()
{
    return bNewFrame;
}

unsigned char * ofxCLEyeMulticam::getPixels()
{
    return vBuf;
}
