#include "HotSpot.h"

HotSpot::HotSpot()
{
    //ctor
}

HotSpot::HotSpot(int _x, int _y, int _num)
{
    number = _num;
    numberString = "0";
    spotPos.set(_x, _y);
    spotBounds.set(_x, _y);
    outputPos.set(_x, 250);
    outputValue = 0;
    outputDirection = -1;
    outputVelocity = 15.0;
    previousValue = 0;

    //vector<string> names;
    /*
    for(int i = number; i < number + 10; i++){
        names.push_back(ofToString(i));
    }
    */
    //ddl = new ofxUIDropDownList("#", names, 30, -10, -10, OFX_UI_FONT_SMALL);
    //ddl->setAllowMultiple(false);
    //ti = new ofxUITextInput("TEXT INPUT", "#", 30, -10, -10, OFX_UI_FONT_SMALL);
    //ddl->
    //gui->addWidgetDown(ddl);
    //gui->addWidgetDown(ti);
    gui = NULL;
    bHaveActivity = false;
    //makeGui();
}

HotSpot::HotSpot(int _x, int _y, int _bX, int _bY, string _label){
    numberString = _label;
    spotPos.set(_x, _y);
    spotBounds.set(_bX, _bY);
    outputValue = 0;
    outputDirection = -1;
    outputVelocity = 15.0;
    previousValue = 0;
    gui = NULL;
    bHaveActivity = false;
}

HotSpot::~HotSpot()
{
    if(gui != NULL){
        delete gui;
    }
}

void HotSpot::setBounds(int _x, int _y)
{
    spotBounds.set(_x, _y);
    //gui->set
}

void HotSpot::makeGui(int _y)
{
    gui = new ofxUICanvas(spotPos.x - 5, 240 + _y,55,45);
    gui->setDrawBack(false);
    tiName = "0:10:0";
    gui->addTextInput(tiName, numberString, 40)->setAutoClear(false);
    gui->setWidgetFontSize(OFX_UI_FONT_SMALL);
    ofAddListener(gui->newGUIEvent, this, &HotSpot::guiEvent);
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
    if(outputValue != previousValue){
        //attrs.clear();
        //cout << "hotspot name = " << ddl->getSelected()[0] << endl;
        attrs["type"] = "real";
        attrs["number"] = numberString;
        attrs["value"] = ofToString(outputValue);
        //cout << "Set intensity attrs to " << attrs["number"] << " and " << attrs["value"] << endl;
        SubObMediator::Instance()->update("intensity-updated", this);
        previousValue = outputValue;
    }
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

void HotSpot::checkForActivity(unsigned char * _activityMap, int _width, int _height, int _offsetX, int _offsetY)
{
    for(int y = 0; y < _height; y++){
        for(int x = 0; x < _width; x++){
            if(_activityMap[(y * _width) + x] == 255){
                if(isInside(x + _offsetX ,y + _offsetY)){
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
    if(name == tiName){
        ti = (ofxUITextInput*) e.widget;
        if(ti->getTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER){
            cout << "Text input = " << ti->getTextString() << endl;
            numberString = ti->getTextString();
            ti->unClick();
        }
    }

    /*
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
    */
}

