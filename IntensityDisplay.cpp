#include "IntensityDisplay.h"

IntensityOutput::IntensityOutput(int _x, int _y, int _number, bool _bDb)
{
    pos.set(_x, _y);
    value = 255;
    size.set(10,10);
    number = _number;
    SubObMediator::Instance()->addObserver("intensity-updated", this);
    bDb = _bDb;
}

void IntensityOutput::draw(){
    ofSetColor(value,value,value);
    ofFill();
    ofRect(pos.x + 10, pos.y + 10, size.x, size.y);
    ofSetColor(0,0,0);
    ofNoFill();
    ofRect(pos.x + 10, pos.y + 10, size.x, size.y);
    //ofRect(pos.x, pos.y, 40,40);
    ofFill();
    ofSetColor(255,255,255);
    ofDrawBitmapString(ofToString(number), pos.x + 11, pos.y + 33);
}

void IntensityOutput::update(string _subName, Subject *_sub)
{
    if(_subName == "intensity-updated"){
        int inNum = ofToInt(_sub->getAttr("number"));
        if(inNum == number){
            value = ofToInt(_sub->getAttr("value"));
            //cout << "Recieved intensity input - " << inNum << ", " << inValue << endl;
        }
    }
}

IntensityDisplay::IntensityDisplay(int _x, int _y)
{
    int i;
    for(i = 0; i < 30; i++){
        outputs.push_back(new IntensityOutput(_x + 30 * i, _y, i, false));
    }
    for(i = 0; i < 30; i++){
        outputs.push_back(new IntensityOutput(_x + 30 * i, _y + 30, i + 30, false));
    }
    /*
    outputs.push_back(new IntensityOutput(1, 358, 0, false));
    outputs.push_back(new IntensityOutput(39, 358, 1, false));
    outputs.push_back(new IntensityOutput(53, 358, 2, false));
    outputs.push_back(new IntensityOutput(65, 358, 3, false));
    outputs.push_back(new IntensityOutput(78, 358, 3, false));
    outputs.push_back(new IntensityOutput(91, 358, 4, false));
    outputs.push_back(new IntensityOutput(104, 358, 4, false));
    outputs.push_back(new IntensityOutput(190, 358, 5, false));
    outputs.push_back(new IntensityOutput(204, 358, 6, false));
    outputs.push_back(new IntensityOutput(295, 358, 7, false));
    */
}

IntensityDisplay::~IntensityDisplay()
{
    //dtor
}

void IntensityDisplay::draw()
{
    vector<IntensityOutput*>::iterator iIter;
    for(iIter = outputs.begin(); iIter != outputs.end(); iIter++){
        (*iIter)->draw();
    }
}
