#ifndef INTENSITYDISPLAY_H
#define INTENSITYDISPLAY_H

#include "ofMain.h"
#include "Subject.h"
#include "Observer.h"
#include "SubObMediator.h"

class IntensityOutput : public Observer
{
    public:
        IntensityOutput(int _x, int _y, int _number, bool _bDb);
        ~IntensityOutput(){}
        void update(string _subName, Subject *_sub);
        void draw();
        void setValue(int _val){value = _val;}
    private:
        ofVec2f pos;
        ofVec2f size;
        int value;
        int number;
        string label;
        bool bDb;
        bool bUpdating;
};

class IntensityDisplay
{
    public:
        IntensityDisplay(int _x, int _y);
        virtual ~IntensityDisplay();
        void draw();
    protected:
    private:
        vector<IntensityOutput*> outputs;
};

#endif // INTENSITYDISPLAY_H
