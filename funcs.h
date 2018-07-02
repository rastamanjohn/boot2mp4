#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

class BootAnimation {

public:

    struct Animation {

        /*
        struct Frame {
            String8 name;
            FileMap* map;
            int trimX;
            int trimY;
            int trimWidth;
            int trimHeight;
            mutable GLuint tid;
            bool operator < (const Frame& rhs) const {
                return name < rhs.name;
            }
        };*/

        struct Part {

            int count;  // The number of times this part should repeat, 0 for infinite
            int pause;  // The number of frames to pause for at the end of this part
            int clockPosX;  // The x position of the clock, in pixels. Positive values offset from
                            // the left of the screen, negative values offset from the right.
            int clockPosY;  // The y position of the clock, in pixels. Positive values offset from
                            // the bottom of the screen, negative values offset from the top.
                            // If either of the above are INT_MIN the clock is disabled, if INT_MAX
                            // the clock is centred on that axis.
            string path;
            string trimData;
            //SortedVector<Frame> frames;
            bool playUntilComplete;
            float backgroundColor[3];
            //uint8_t* audioData;
            //int audioLength;
            Animation* animation;

        };

        int fps;
        int width;
        int height;
        vector<Part> parts;
        //String8 audioConf;
        //String8 fileName;
        //ZipFileRO* zip;
        //Font clockFont;

    };

private:
    bool parseAnimationDesc(Animation&);

};
