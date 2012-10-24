#pragma once

#include "ofMain.h"
#include "ofxCLEyeMulticam.h"
#include "HotSpot.h"
#include "IntensityDisplay.h"
#include "MotionCam.h"
#include "SubObMediator.h"
#include "Subject.h"

class testApp : public ofBaseApp, public Subject{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        MotionCam *motionCam;
        MotionCam *motionCam2;
        MotionCam *motionCam3;
        MotionCam *motionCam4;
        MotionCam *motionCam5;
        MotionCam *motionCam6;

        string camera1UUID;
        string camera2UUID;
        string camera3UUID;
        string camera4UUID;
        string camera5UUID;
        string camera6UUID;

        map<string,string> attrs;
        string getAttr(const char * _key){return attrs[_key];}

        void updateMouseState(const char * _state, int _x, int _y, int _button);

        IntensityDisplay *display;

        ofImage window;

		/*

		void makeMovementMap(unsigned char * _currentFrame, unsigned char * _previousFrame, unsigned char * _output, int _width, int _height);
        void makeMovementOverlay(unsigned char * _movementFrame, unsigned char * _movementOverlay, int _width, int _height);

        ofxCLEyeMulticam *multiCam;
        ofTexture cTex;
        ofTexture movementTex;
        ofTexture movementOverlay;
        ofTexture backgroundTex;

        unsigned char * previousFrame;
        unsigned char * currentFrame;
        unsigned char * movementFrame;
        unsigned char * movementOverlayFrame;
        unsigned char * backgroundFrame;

        bool bSelecting;
        vector<HotSpot*> hotSpots;

        bool bBgCompare;


        int cameraThreshold;

        */

};
