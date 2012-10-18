#ifndef HOTSPOT_H
#define HOTSPOT_H

#include "ofMain.h"
#include "IntensityDisplay.h"

class HotSpot
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

};

#endif // HOTSPOT_H
