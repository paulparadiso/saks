#include "HotSpot.h"

HotSpot::HotSpot()
{
    //ctor
}

HotSpot::HotSpot(int _x, int _y, int _num)
{
    number = _num;
    spotPos.set(_x, _y);
    outputPos.set(_x, 250);
    outputValue = 0;
    outputDirection = -1;
    outputVelocity = 15.0;
    gui = new ofxUICanvas(_x,250,45,40);
    vector<string> names;
    for(int i = number; i < number + 10; i++){
        names.push_back(ofToString(i));
    }
    ddl = new ofxUIDropDownList("#", names, 30, -10, -10, OFX_UI_FONT_SMALL);
    ddl->setAllowMultiple(false);
    //ddl->
    gui->addWidgetDown(ddl);
    ofAddListener(gui->newGUIEvent, this, &HotSpot::guiEvent);
}

HotSpot::~HotSpot()
{
    delete gui;
}

void HotSpot::setBounds(int _x, int _y)
{
    spotBounds.set(_x, _y);
}

void HotSpot::update(){
    if(bHaveActivity){
        outputDirection = 1;
    } else {
        outputDirection = -1;
    }
    outputValue += outputVelocity * outputDirection;
    if(outputValue < 0){
        outputValue = 0;
    }
    if(outputValue > 255){
        outputValue = 255;
    }
    //cout << "Intensity of " << number << " = " << outputValue << endl;
    attrs.clear();
    //cout << "hotspot name = " << ddl->getSelected()[0] << endl;
    attrs["number"] = ofToString(number);
    attrs["value"] = ofToString(outputValue);
    //cout << "Set intensity attrs to " << attrs["number"] << " and " << attrs["value"] << endl;
    SubObMediator::Instance()->update("intensity-updated", this);

}

void HotSpot::draw(){
    ofEnableAlphaBlending();
    if(!bHaveActivity){
        ofSetColor(0 ,255, 0, 50);
    } else {
        ofSetColor(255, 0, 0,127);
    }
    ofRect(spotPos.x, spotPos.y, spotBounds.x - spotPos.x, spotBounds.y - spotPos.y);
    ofDisableAlphaBlending();
    /*
    ofSetColor(outputValue,outputValue,outputValue);
    ofRect(outputPos.x, outputPos.y, 20, 20);
    ofNoFill();
    ofSetColor(0,0,0);
    ofRect(outputPos.x, outputPos.y, 20, 20);
    ofFill();
    */
    ofSetColor(255,255,255);
}

void HotSpot::checkForActivity(unsigned char * _activityMap, int _width, int _height)
{
    for(int y = 0; y < _height; y++){
        for(int x = 0; x < _width; x++){
            if(_activityMap[(y * _width) + x] == 255){
                if(isInside(x,y)){
                    bHaveActivity = true;
                    return;
                }
            }
        }
    }
    bHaveActivity = false;
}

bool HotSpot::isInside(int _x, int _y)
{
    if((_x > spotPos.x && _x < spotBounds.x) && (_y > spotPos.y && _y < spotBounds.y)){
        return true;
    } else {
        return false;
    }
}

void HotSpot::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();

    vector<ofxUIWidget*> w = ddl->getSelected();
    if(w.size() > 0){
        //cout << "WIDGET NAME: " << ddl->getSelected()[0]->getName() << endl;
        ddl->setName(w[0]->getName());
    }

    if(name == "FULLSCREEN")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        ofSetFullscreen(toggle->getValue());
    }
    else if(name == "DYNAMIC DROP DOWN")
    {
        ofxUIDropDownList *ddlist = (ofxUIDropDownList *) e.widget;
        vector<ofxUIWidget *> &selected = ddlist->getSelected();
        for(int i = 0; i < selected.size(); i++)
        {
            cout << "SELECTED: " << selected[i]->getName() << endl;
        }
    }
}

