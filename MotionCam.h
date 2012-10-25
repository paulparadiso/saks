#ifndef MOTIONCAM_H
#define MOTIONCAM_H

#include "ofMain.h"
#include "ofxCLEyeMulticam.h"
#include "HotSpot.h"
#include "Observer.h"
#include "SubObMediator.h"
#include "ofxXmlSettings.h"

class MotionCam : public Observer, public ofThread
{
    public:
        MotionCam();
        MotionCam(int _camera);
        MotionCam(int _camera, int _x, int _y);
        MotionCam(string _UUID, int _x, int _y);
        virtual ~MotionCam();
        void update();
        void update(string _subName, Subject *_sub);
        void draw();

        bool hasFocus();

        /*
        Thread related functions.
        */

        void start();
        void stop();
        void threadedFunction();

        void captureBackground();
        void toggleCompare(){bBgCompare = !bBgCompare;}
        void setBgCompare(bool _bBg){bBgCompare = _bBg;}
        void setDrawCamera(bool _bDraw){bDrawCamera = _bDraw;}
        void setRunning(bool _b){bRunning = _b;}
        void toggleRunning(){bRunning = !bRunning;}

        /*
        Save hotspot data.
        */

        void loadSettings();
        void saveSettings();

    protected:
    private:

        /*
        The multicam.
        */

        ofxCLEyeMulticam *multiCam;

        /*
        Setup the camera and initialize various components.
        */

        void init();

        /*
        Make GUID from string.
        */

        void setGUIDFromString(string _uuidString);
        GUID cGUID;

        /*
        Analyze a frame for movement.
        */

        void makeMovementMap(unsigned char * _currentFrame, unsigned char * _previousFrame, unsigned char * _output, int _width, int _height);

        /*
        Make the movement overlay.
        */

        void makeMovementOverlay(unsigned char * _movementFrame, unsigned char * _movementOverlay, int _width, int _height);

        /*
        Process mouse input.
        */

        void processMouse(string _state, int _x, int _y, int _button);

        /*
        Is inside.
        */

        bool isInside(int _x, int _y);

        /*
        Textures necessary for drawing the camera and motion.
        */

        ofTexture cTex;
        ofTexture movementOverlay;

        /*
        For storing motion detection and frame comparison images.
        */

        unsigned char * previousFrame;
        unsigned char * currentFrame;
        unsigned char * movementFrame;
        unsigned char * movementOverlayFrame;
        unsigned char * backgroundFrame;

        /*
        Camera name.
        */

        string name;
        int number;

        /*
        The threshold used by the camera for motion detection.
        */

        int cameraThreshold;

        /*
        Coordinates for drawing the output.
        */

        ofVec2f pos;

        /*
        Use motion detection when false.  Otherwise object detection.
        */

        bool bBgCompare;

        /*
        Whether the initial background has been captured.
        */

        bool bBgCaptured;

        /*
        Draw the camera output when true.
        */

        bool bDrawCamera;

        /*
        Pixel to change after background compare.  Slowly updates the
        background image.
        */

        int changePixelX;
        int changePixelY;

        /*
        Hotspot gear.
        */

        bool bSelecting;
        vector<HotSpot*> hotSpots;

        /*
        XML settings file for camera and hotspots.
        */

        ofxXmlSettings settingsFile;
        string settingsFileName;

        /*
        Utilities.
        */

        ofVec2f stringToVec2f(string _vec);

        bool bRunning;


};

#endif // MOTIONCAM_H
