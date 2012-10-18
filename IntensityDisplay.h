#ifndef INTENSITYDISPLAY_H
#define INTENSITYDISPLAY_H

#include "ofMain.h"

class IntensityOutput
{
    public:
        IntensityOutput(int _x, int _y);
        ~IntensityOutput();
        void draw();
        void setValue(int _val){value = _val;}
    private:
        ofVec2f pos;
        ofVec2f size;
        int value;
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
