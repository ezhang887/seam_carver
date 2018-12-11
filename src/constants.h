#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "seam_carver.h"

namespace constants{
    const int kMainWindowHeight = 1280;
    const int kMainWindowWidth = 720;

    const int kLoadedImageX = 500;
    const int kLoadedImageY = 10;
    const int kMaxLoadedImageDimension = 700;

    const int kPopupImageX = 0;
    const int kPopupImageY = 20;

    const int kPopupGifX = 0;
    const int kPopupGifY = 20;

    const int kProgressBarX = 15;
    const int kProgressBarY = 275;
    const int kProgressBarWidth = 175;
    const int kProgressBarHeight = 20;
    const int kProgressBarFontSize = 11;

    const double kGifSleepTimeMicros = 0.1 * 1000000;

    const FaceBounds kNoFaceBounds = FaceBounds(0,0,0,0);
};

#endif
