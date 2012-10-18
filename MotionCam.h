#ifndef MOTIONCAM_H
#define MOTIONCAM_H

#include "ofxCLEyeMulticam.h"

class MotionCam
{
    public:
        MotionCam();
        MotionCam(int _camera);
        virtual ~MotionCam();
    protected:
    private:

        /*
        Setup the camera and initialize various components.
        */

        void init();

        /*
        For storing motion detection and frame comparison images.
        */

        unsigned char * previousFrame;
        unsigned char * currentFrame;
        unsigned char * movementFrame;
        unsigned char * movementOverlayFrame;
        unsigned char * backgroundFrame;
};

#endif // MOTIONCAM_H
