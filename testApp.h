#pragma once

#include "ofMain.h"
#include "ofxCLEyeMulticam.h"
#include "HotSpot.h"

class testApp : public ofBaseApp{

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

};
