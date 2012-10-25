#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#include "ofMain.h"
#include "SubObMediator.h"
#include "Subject.h"
#include "Observer.h"

#define SCREENSAVER_WAIT_TIME 5.0
#define SCREENSAVER_RECORD_STOP 10000

enum{
    SCREENSAVER_STATE_WAITING,
    SCREENSAVER_STATE_RECORDING,
    SCREENSAVER_STATE_PLAYING,
    SCREENSAVER_STATE_ON
};

class CapturedEvent
{
    public:
        CapturedEvent();
        CapturedEvent(string _label, string _value, float _time);
        virtual ~CapturedEvent();
    private:
        string label;
        string value;
        float time;
};

class Pulser : public Subject
{
    public:
        Pulser(int _num);
        void update();
        void reset();
        string getAttr(const char * _key){return attrs[_key];}
        ~Pulser(){}
    private:
        string label;
        int velocity;
        int direction;
        int val;
        map<string,string> attrs;
};

class Recording
{
    public:
        Recording();
        void reset();
        void advance();
        CapturedEvent* nextEvent();
        CapturedEvent* previousEvent();
        float getStartTime(){return startTime;}
        ~Recording();
    private:
        vector<CapturedEvent*>events;
        float startTime;
};

class ScreenSaver : public Observer, public Subject
{
    public:
        ScreenSaver();
        void update();
        void update(string _subName, Subject *_sub);
        string getAttr(const char *_key){return attrs[_key];}
        virtual ~ScreenSaver();
    protected:
    private:
        float timeOfLastEvent;
        float recordingStartTime;
        Recording *recording;
        map<string, string>attrs;
        int recordState;
        vector<Pulser*> pulsers;
};

#endif // SCREENSAVER_H
