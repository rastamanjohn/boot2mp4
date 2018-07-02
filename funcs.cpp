#include "funcs.h"

static const int ANIM_ENTRY_NAME_MAX = 256;
static constexpr size_t TEXT_POS_LEN_MAX = 16;

static bool parseColor(const char str[7], float color[3]) {
    float tmpColor[3];
    for (int i = 0; i < 3; i++) {
        int val = 0;
        for (int j = 0; j < 2; j++) {
            val *= 16;
            char c = str[2*i + j];
            if      (c >= '0' && c <= '9') val += c - '0';
            else if (c >= 'A' && c <= 'F') val += (c - 'A') + 10;
            else if (c >= 'a' && c <= 'f') val += (c - 'a') + 10;
            else                           return false;
        }
        tmpColor[i] = static_cast<float>(val) / 255.0f;
    }
    memcpy(color, tmpColor, sizeof(tmpColor));
    return true;
}


bool BootAnimation::parseAnimationDesc(Animation& animation){

    ifstream infile("desc.txt");
    string line;
    while(getline(infile, line)) {

        int fps = 0;
        int width = 0;
        int height = 0;
        int count = 0;
        int pause = 0;
        char path[ANIM_ENTRY_NAME_MAX];
        char color[7] = "000000"; // default to black if unspecified
        char clockPos1[TEXT_POS_LEN_MAX + 1] = "";
        char clockPos2[TEXT_POS_LEN_MAX + 1] = "";
        char pathType;

        cout << line << "\n";
        const char* l = line.c_str();
        if (sscanf(l, "%d %d %d", &width, &height, &fps)) {
            animation.width = width;
            animation.height = height;
            animation.fps = fps;
        }

        else if (sscanf(l, " %c %d %d %s #%6s %16s %16s", &pathType, &count, &pause, path, color, clockPos1, clockPos2)) {
            Animation::Part part;
            part.playUntilComplete = pathType == 'c';
            part.count = count;
            part.pause = pause;
            part.path = path;
            //part.audioData = NULL;
            part.animation = NULL;
            //cout << part.path << "\n";
            if (!parseColor(color, part.backgroundColor)) {
                part.backgroundColor[0] = 0.0f;
                part.backgroundColor[1] = 0.0f;
                part.backgroundColor[2] = 0.0f;
            }
            animation.parts.push_back(part);
        }
    }
    return true;
}
