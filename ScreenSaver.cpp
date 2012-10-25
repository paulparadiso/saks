#include "ScreenSaver.h"

Recording::Recording()
{
    startTime = ofGetElapsedTimef();
}

Recording::~Recording()
{

}

Pulser::Pulser(int _num)
{
    label = ofToString(_num);
    val = 0;
    direction = 1;
    velocity = ofRandom(1, 10);
    //velocity = 7;
    //cout << "creating new pulser with vel - " << velocity << endl;
}

void Pulser::reset()
{
    val = 0;
    direction = 1;
    //velocity = ofRandom(15, 15);
}

void Pulser::update()
{
    val += (velocity * direction);
    if(val >= 255){
        direction = -1;
    }
    if(val <= 0){
        direction = 1;
    }
    attrs.clear();
    attrs["type"] = "fake";
    attrs["number"] = label;
    attrs["value"] = ofToString(val);
    SubObMediator::Instance()->update("intensity-updated", this);
}

ScreenSaver::ScreenSaver()
{
    SubObMediator::Instance()->addObserver("intensity-updated", this);
    recordState = SCREENSAVER_STATE_WAITING;
    recording = NULL;
    for(int i = 0; i < 60; i++){
        pulsers.push_back(new Pulser(i));
    }
    timeOfLastEvent = ofGetElapsedTimef();
}

ScreenSaver::~ScreenSaver()
{
    //dtor
}

void ScreenSaver::update()
{
    if(recordState == SCREENSAVER_STATE_ON){
        vector<Pulser*>::iterator pIter;
        for(pIter = pulsers.begin(); pIter != pulsers.end(); pIter ++){
            (*pIter)->update();
        }
    }
    if(recordState == SCREENSAVER_STATE_WAITING){
        if(ofGetElapsedTimef() - timeOfLastEvent > SCREENSAVER_WAIT_TIME){
            cout << "Screensaver on." << endl;
            vector<Pulser*>::iterator pIter;
            for(pIter = pulsers.begin(); pIter != pulsers.end(); pIter ++){
                (*pIter)->reset();
            }
            recordState = SCREENSAVER_STATE_ON;
        }
    }
}

void ScreenSaver::update(string _subName, Subject *_sub)
{
    if(_subName == "intensity-updated"){
        if(_sub->getAttr("type") == "real"){
            timeOfLastEvent = ofGetElapsedTimef();
            if(recordState == SCREENSAVER_STATE_ON){
                cout << "Screensaver off." << endl;
                vector<Pulser*>::iterator pIter;
                for(pIter = pulsers.begin(); pIter != pulsers.end(); pIter ++){
                    (*pIter)->reset();
                    (*pIter)->update();
                }
                recordState = SCREENSAVER_STATE_WAITING;
            }
        }
        /*
        string label = _sub->getAttr("number");
        string value = _sub->getAttr("value");
        float now = ofGetElapsedTimef();
        if(recordState = SCREENSAVER_STATE_WAITING){
            if(recording != NULL){
                delete recording;
            }
            recording = new Recording();
        }
        */
        //cout << "ScreenSaver recieved new events - " << label << " - " << value << " - " << now << endl;
    }
}
