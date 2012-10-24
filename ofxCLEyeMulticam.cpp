#include "ofxCLEyeMulticam.h"
#include <stdio.h>
#include "ofMain.h"

ofxCLEyeMulticam::ofxCLEyeMulticam()
{

    //cout << "Trying to open - " << guid.Data1 << ":" << guid.Data2 << ":" << guid.Data3 << ":" << guid.Data4[0] << endl;;

    //printf("Data4[0] = %02x\n", guid.Data4[0]);

    //createCamera(0, CLEYE_QVGA, CLEYE_MONO_PROCESSED, 30);
    init();
}

ofxCLEyeMulticam::ofxCLEyeMulticam(GUID _guid, int _colorMode, int _resolution, int _framerate)
{
    createCamera(_guid, _colorMode, _resolution, _framerate);
    init();
}

ofxCLEyeMulticam::ofxCLEyeMulticam(int _camera, int _colorMode, int _resolution, int _framerate)
{
    GUID guid = CLEyeGetCameraUUID(_camera);
    printf("Camera %d GUID: [%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x]\n",
						_camera, guid.Data1, guid.Data2, guid.Data3,
						guid.Data4[0], guid.Data4[1], guid.Data4[2],
						guid.Data4[3], guid.Data4[4], guid.Data4[5],
						guid.Data4[6], guid.Data4[7]);
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
