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

Faker::Faker(int _num)
{
    label = ofToString(_num);
    val = 0;
    direction = 1;
    velocity = ofRandom(1, 10);
    //velocity = 7;
    //cout << "creating new pulser with vel - " << velocity << endl;
}

void Faker::reset()
{
    val = 0;
    direction = -1;
    velocity = 10;
}

void Faker::setValue(int _val){
    val = _val;
    //cout << "set value to " << val << endl;
}

void Faker::update()
{
    val += velocity * direction;
    if(val > 255){
        val = 255;
    }
    if(val < 0){
        val = 0;
    }
    attrs["type"] = "fake";
    attrs["number"] = label;
    attrs["value"] = ofToString(val);
    SubObMediator::Instance()->update("intensity-updated", this);
}

Walker::Walker(int _min, int _max, int _start)
{
    val = _start;
    min = _min;
    max = _max;
}

void Walker::update()
{
    val += ofRandom(min,max);
}

ScreenSaver::ScreenSaver()
{
    SubObMediator::Instance()->addObserver("intensity-updated", this);
    recordState = SCREENSAVER_STATE_WAITING;
    recording = NULL;
    for(int i = 0; i < 60; i++){
        pulsers.push_back(new Pulser(i));
        fakers.push_back(new Faker(i));
    }
    timeOfLastEvent = timeOfLastWalk = timeOfLastPulse = ofGetElapsedTimef();
    mode = SCREENSAVER_MODE_WALK;
    walker = 0;
}

ScreenSaver::~ScreenSaver()
{
    //dtor
}

void ScreenSaver::update()
{
    if(recordState == SCREENSAVER_STATE_ON){
        if(mode == SCREENSAVER_MODE_PULSE){
            if(ofGetElapsedTimef() - timeOfLastPulse > SCREENSAVER_PULSE_DELAY){
                vector<Pulser*>::iterator pIter;
                for(pIter = pulsers.begin(); pIter != pulsers.end(); pIter ++){
                    (*pIter)->update();
                }
                timeOfLastPulse = ofGetElapsedTimef();
            }
        }
        if(mode == SCREENSAVER_MODE_WALK){
            vector<Faker*>::iterator fIter;
            if(ofGetElapsedTimef() - timeOfLastWalk > SCREENSAVER_WALK_DELAY){
                int c = 0;
                int nVal;
                /*
                vector<Faker*>::iterator fIter;
                for(fIter = fakers.begin(); fIter != fakers.end(); fIter ++){
                    nVal = sin(255.0 * ((float)c++ / 60.0));
                    cout << "setting to " << nVal << endl;
                    (*fIter)->setValue(nVal);
                    (*fIter)->update();
                }
                */
                if(walkers.size() < MAX_WALKERS){
                    walkers.push_back(new Walker(-2, 2, 60 * ofRandom(0,1)));
                }
                for(fIter = fakers.begin(); fIter != fakers.end(); fIter ++){
                    //(*fIter)->setValue(0);
                    (*fIter)->setDirection(-1);
                }
                //fakers[walker]->setValue(255);
                //walker += ofRandom(-2,2);
                vector<Walker*>::iterator wIter;
                //cout << "start.  have " << walkers.size() << " walkers." << endl;
                for(wIter = walkers.begin(); wIter != walkers.end();){
                    (*wIter)->update();
                    int t = (*wIter)->getValue();
                    if(t <= 0 || t >= 59){
                        delete (*wIter);
                        wIter = walkers.erase(wIter);
                    } else {
                        //cout << "turning on " << t << endl;
                        //fakers[t]->setValue(255);
                        //(*fIter)->setDirection(1);
                        fakers[t]->setDirection(1);
                        wIter++;
                    }
                }
                //cout << "stop" << endl;
                /*
                if(walker >= 59){
                    walker = 59;
                }
                if(walker <= 0){
                    walker = 0;
                }
                */
                timeOfLastWalk = ofGetElapsedTimef();
            }
            for(fIter = fakers.begin(); fIter != fakers.end(); fIter ++){
                (*fIter)->update();
            }
        }
    }
    if(recordState == SCREENSAVER_STATE_WAITING){
        if(ofGetElapsedTimef() - timeOfLastEvent > SCREENSAVER_WAIT_TIME){
            //cout << "Screensaver on." << endl;
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
                //cout << "Screensaver off." << endl;
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
