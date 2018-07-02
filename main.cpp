#include "funcs.cpp"

typedef BootAnimation::Animation Animation;

int main()
{
    cout << "Hello\n";
    Animation *animation =  new Animation;
    BootAnimation::parseAnimationDesc(*animation);
    return 0;
}
