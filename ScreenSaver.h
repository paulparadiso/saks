#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#include "ofMain.h"
#include "SubObMediator.h"
#include "Subject.h"
#include "Observer.h"

#define SCREENSAVER_WAIT_TIME 5.0
#define SCREENSAVER_RECORD_STOP 10000
#define SCREENSAVER_WALK_DELAY 0.2
#define SCREENSAVER_PULSE_DELAY 0.05
#define MAX_WALKERS 5

enum{
    SCREENSAVER_STATE_WAITING,
    SCREENSAVER_STATE_RECORDING,
    SCREENSAVER_STATE_PLAYING,
    SCREENSAVER_STATE_ON
};

enum{
    SCREENSAVER_MODE_PULSE,
    SCREENSAVER_MODE_WALK
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

class Faker : public Subject
{
    public:
        Faker(int _num);
        void update();
        void reset();
        void setValue(int _val);
        int getValue(){return val;}
        int setDirection(int _dir){direction = _dir;}
        string getAttr(const char * _key){return attrs[_key];}
        ~Faker(){}
    private:
        string label;
        int velocity;
        int direction;
        int val;
        map<string,string> attrs;
};

class Walker
{
    public:
        Walker(int _min, int _max, int _start);
        void update();
        int getValue(){return val;}
        ~Walker(){}
    private:
        int val;
        int min;
        int max;
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
        void setWalkMode(){mode = SCREENSAVER_MODE_WALK;}
        void setPulseMode(){mode = SCREENSAVER_MODE_PULSE;}
        virtual ~ScreenSaver();
    protected:
    private:
        float timeOfLastEvent;
        float timeOfLastWalk;
        float timeOfLastPulse;
        float recordingStartTime;
        Recording *recording;
        map<string, string>attrs;
        int recordState;
        vector<Pulser*> pulsers;
        vector<Faker*> fakers;
        vector<Walker*> walkers;
        int mode;
        int walker;
};

#endif // SCREENSAVER_H
