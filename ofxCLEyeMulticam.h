#ifndef OFXCLEYEMULTICAM_H
#define OFXCLEYEMULTICAM_H

#include "CLEyeMulticam.h"

class ofxCLEyeMulticam
{
    public:
        ofxCLEyeMulticam();

        /*
        Create an instance of ofxCLEyeMulticam with a specified
        camera, color mode and resolution.  Or alternately by
        camera number.
        */

        ofxCLEyeMulticam(GUID _guid, int _colorMode, int _resolution, int _framerate);
        ofxCLEyeMulticam(int _camera, int _colorMode, int _resolution, int _framerate);
        virtual ~ofxCLEyeMulticam();

        /*
        Static method to get the number of connected cameras.
        */

        static int getCameraCount();

        /*
        Static method to get the UUID of a particular camera.
        */

        static GUID getCameraUUID(int _camera);

        /*
        Check for a new frame.
        */

        void grabFrame();

        /*
        Check if there is a new frame.
        */

        bool isFrameNew();

        /*
        Get the pointer to the pixel data.
        */

        unsigned char * getPixels();

    protected:
    private:

        void createCamera(GUID _id, int _colorMode, int _resolution, int _framerate);
        void init();

        CLEyeCameraInstance mCam;
        unsigned char * vBuf;
        int mColorMode;
        int mResolution;
        int mCameraNumber;
        GUID mGuid;

        int mCameraWidth;
        int mCameraHeight;
        int mCameraColorDepth;

        bool bNewFrame;
};

#endif // OFXCLEYEMULTICAM_H
