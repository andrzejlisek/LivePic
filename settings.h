#ifndef SETTINGS_H
#define SETTINGS_H

#include <mutex>
#include <configfile.h>
#include <eden.h>

class Settings
{
public:
    EdenClass::ConfigFile CF;

    Settings();
    ~Settings();
    void Save();

    int PicX = 0;
    int PicY = 0;
    int PicW = 320;
    int PicH = 240;
    int ViewX = 0;
    int ViewY = 0;
    int ViewW = 640;
    int ViewH = 480;
    int ViewMarginLeft = 0;
    int ViewMarginTop = 0;
    int ViewMarginRight = 0;
    int ViewMarginBottom = 0;
    int ViewOffsetX = 0;
    int ViewOffsetY = 0;
    int ViewStretched = 3;
    int PicThreads = 1;
    int MouseSize = 0;
    int MouseThickness = 0;
    int MousePointerType = 0;
    bool FollowMouse = true;
    int Gamma = 2200;
    string TransformFile = "";
    int BackColorR = 0;
    int BackColorG = 0;
    int BackColorB = 0;
    int PipeCount = 0;
    int MouseMargin = 20;
    int DelayLineCount = 0;
    string DelayLineFileName = "";
    std::mutex MTX;
    bool NeedRecalc = true;
};

#endif // SETTINGS_H
