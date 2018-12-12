#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "structs.h"

namespace constants{
    const int kMainWindowWidth = 1280;
    const int kMainWindowHeight = 720;

    const int kPanelWidth = 400;
    const int kPanelHeight = 10;

    const int kLoadedImageX = 500;
    const int kLoadedImageY = 10;
    const int kMaxLoadedImageDimension = 700;

    const int kPopupImageX = 0;
    const int kPopupImageY = 20;

    const int kPopupGifX = 0;
    const int kPopupGifY = 20;

    const int kProgressBarX = 10;
    const int kProgressBarY = 275;
    const int kProgressBarWidth = 400;
    const int kProgressBarHeight = 20;
    const int kProgressBarFontSize = 11;

    const double kGifSleepTimeMicros = 0.1 * 1000000;

    const int kFaceDetectionOffsetHeight = 5;

    const FaceBounds kNoFaceBounds = FaceBounds(-1,-1,-1,-1);
    const Color kRed = Color(255,0,0);
};

#endif
