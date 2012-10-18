#include "IntensityDisplay.h"

IntensityOutput::IntensityOutput(int _x, int _y)
{
    pos.set(_x, _y);
    value = 255;
    size.set(20,20);
}

void IntensityOutput::draw(){
    ofSetColor(value,value,value);
    ofFill();
    ofRect(pos.x + 10, pos.y + 10, 20, 20);
    ofSetColor(0,0,0);
    ofNoFill();
    ofRect(pos.x + 10, pos.y + 10, 20, 20);
    ofRect(pos.x, pos.y, 40,40);
    ofFill();
    ofSetColor(255,255,255);
}

IntensityDisplay::IntensityDisplay(int _x, int _y)
{
    for(int i = 0; i < 8; i++){
        outputs.push_back(new IntensityOutput(_x + 40 * i, _y));
    }
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
