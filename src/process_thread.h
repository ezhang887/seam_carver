#ifndef BACKGROUND_RUNNER_H
#define BACKGROUND_RUNNER_H

#include <ofMain.h>

class BackgroundRunner : public ofThread{

    public:
        BackgroundThread(ofImage image);
        ~BackgroundThread();
        ofImage getImage();

};

#endif
