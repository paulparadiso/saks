#ifndef HOTSPOT_H
#define HOTSPOT_H

#include "ofMain.h"
#include "IntensityDisplay.h"
#include "Subject.h"
#include "SubObMediator.h"

class HotSpot : public Subject
{
    public:
        HotSpot();
        HotSpot(int _x, int _y);
        void setDisplay(IntensityDisplay *_display){mDisplay = _display;}
        void setBounds(int _x, int _y);
        void checkForActivity(unsigned char * _activityMap, int _width, int _height);
        void draw();
        bool isInside(int _x, int _y);
        void update();
        void setNumber(int _num){number = _num;}
        string getAttr(const char * _key){return attrs[_key];}
        virtual ~HotSpot();
    protected:
    private:

        /*
        Vectors containing the position and size of the HotSpot.
        */

        ofVec2f spotPos;
        ofVec2f spotBounds;

        /*
        Vector containing the offset of the HotSpot.  This allows the hotspot interface to
        be moved around the screen while still being able to compare itself against an image.
        */

        ofVec2f spotOffset;

        /*
        The position at which the output square will be drawn.
        */

        ofVec2f outputPos;

        /*
        Whether the is currently activity whithin the HotSpot.
        */

        bool bHaveActivity;

        int outputValue;
        int outputDirection;
        float outputVelocity;

        IntensityDisplay *mDisplay;

        /*
        Name of the camera that the hotspot is connected to.
        */

        string cameraName;
        int number;
        map<string, string> attrs;

};

#endif // HOTSPOT_H
