#include "testApp.h"
#include "CLEyeMulticam.h"

CLEyeCameraInstance _cam;

/*
CLEyeCameraInstance _cam2;
CLEyeCameraInstance _cam3;
CLEyeCameraInstance _cam4;
*/

CLEyeCameraColorMode _mode;
CLEyeCameraResolution _resolution;

ofTexture cTex;
unsigned char buf[320 * 240 * 4];

/*
ofTexture cTex2;
unsigned char buf2[320 * 240 * 4];

ofTexture cTex3;
unsigned char buf3[320 * 240 * 4];

ofTexture cTex4;
unsigned char buf4[320 * 240 * 4];
*/

//--------------------------------------------------------------
void testApp::setup(){
    //printf("CLEyeGetCameraParameter %d\n", CLEyeGetCameraParameter(_cam, (CLEyeCameraParameter)0));
    int numCams = CLEyeGetCameraCount();
    printf("Found %d cameras.\n", numCams);
    for(int i = 0; i < numCams; i++){
        GUID guid = CLEyeGetCameraUUID(i);
		printf("Camera %d GUID: [%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x]\n",
						i+1, guid.Data1, guid.Data2, guid.Data3,
						guid.Data4[0], guid.Data4[1], guid.Data4[2],
						guid.Data4[3], guid.Data4[4], guid.Data4[5],
						guid.Data4[6], guid.Data4[7]);
    }
    _cam = CLEyeCreateCamera(CLEyeGetCameraUUID(0), CLEYE_COLOR_RAW, CLEYE_QVGA, 30);
    /*
    _cam2 = CLEyeCreateCamera(CLEyeGetCameraUUID(1), CLEYE_COLOR_RAW, CLEYE_QVGA, 30);
    _cam3 = CLEyeCreateCamera(CLEyeGetCameraUUID(2), CLEYE_COLOR_RAW, CLEYE_QVGA, 30);
    _cam4 = CLEyeCreateCamera(CLEyeGetCameraUUID(3), CLEYE_COLOR_RAW, CLEYE_QVGA, 30);
    */
    if(CLEyeCameraStart(_cam)){
        printf("Camera 1 started properly.\n");
    }
    /*
    if(CLEyeCameraStart(_cam2)){
        printf("Camera 2 started properly.\n");
    }
    if(CLEyeCameraStart(_cam3)){
        printf("Camera 3 started properly.\n");
    }
    if(CLEyeCameraStart(_cam4)){
        printf("Camera 4 started properly.\n");
    }
    */
    cTex.allocate(320, 240, GL_RGBA);
    /*
    cTex2.allocate(320, 240, GL_RGBA);
    cTex3.allocate(320, 240, GL_RGBA);
    cTex4.allocate(320, 240, GL_RGBA);
    */
}

//--------------------------------------------------------------
void testApp::update(){
    if(CLEyeCameraGetFrame(_cam, (PBYTE)&buf)){
        cTex.loadData((unsigned char *)&buf, 320, 240, GL_RGBA);
    }
    /*
    if(CLEyeCameraGetFrame(_cam2, (PBYTE)&buf2)){
        cTex2.loadData((unsigned char *)&buf2, 320, 240, GL_RGBA);
    }
    if(CLEyeCameraGetFrame(_cam3, (PBYTE)&buf3)){
        cTex3.loadData((unsigned char *)&buf3, 320, 240, GL_RGBA);
    }
    if(CLEyeCameraGetFrame(_cam4, (PBYTE)&buf4)){
        cTex4.loadData((unsigned char *)&buf4, 320, 240, GL_RGBA);
    }
    */
}

//--------------------------------------------------------------
void testApp::draw(){
    cTex.draw(0, 0);
    /*
    cTex2.draw(320, 0);
    cTex3.draw(0, 240);
    cTex4.draw(320, 240);
    */
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

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
