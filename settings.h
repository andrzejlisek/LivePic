#ifndef SETTINGS_H
#define SETTINGS_H

#include <mutex>
#include <configfile.h>
#include <eden.h>
#include <QScreen>
#include <QGuiApplication>
#include <vector>

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
    int PicW_disp = 320;
    int PicH_disp = 240;
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
    int MouseSize = 10;
    int MouseThickness = 0;
    int MousePointerType = 1;
    bool FollowMouse = true;
    int Gamma = 2200;
    string TransformFile = "";
    int BackColorR = 0;
    int BackColorG = 0;
    int BackColorB = 0;
    int PipeCount = 0;
    int MouseMargin = 20;
    int DelayLineCount = 0;
    int DelayLineMode = 0;
    string DelayLineFileName = "";
    std::mutex MTX;
    bool NeedRecalc = true;

    bool StayOnTopPic = false;
    bool StayOnTopSet = false;
    bool SetCloseApp = false;
    int Throttle = 100;

    string NetAddr = "0.0.0.0";
    int NetPort = 8000;
    int PicSrcDst = 0;
    int NetQuality1 = 20;
    int NetQuality2 = 20;

    bool _PicSrcNet = false;
    bool _PicDstNet = false;
    void RefreshWorkingSettings();

    int BoundX1 = -999999;
    int BoundY1 = -999999;
    int BoundX2 = 999999;
    int BoundY2 = 999999;

    vector<int> _BoundX1;
    vector<int> _BoundY1;
    vector<int> _BoundX2;
    vector<int> _BoundY2;

    bool ViewFullscreen = false;

    bool GoogleCloudEnabled = false;
    string GoogleCloudKey = "";
    int GoogleCloudMaskOverlay = 3;
    int GoogleCloudDecimate = 10;
    string GoogleCloudLangSrc = "";
    string GoogleCloudLangDst = "";
    string GoogleCloudFontName = "Arial";
    bool GoogleCloudFontAutoSize = true;
    int GoogleCloudImageQuality = 80;
    int GoogleCloudFontSize = 6;
    bool GoogleCloudTextRotate = true;
    bool GoogleCloudTranslateLines = true;
    int GoogleCloudTranslateAlignH = 1;
    int GoogleCloudTranslateAlignV = 1;
    int GoogleCloudSlotCount = 1000;

    int RecorderMode = 0;
    bool RecorderWindowOnTop = false;
    string RecorderDirectory = "";
    bool RecorderMemory = true;
    int RecorderFactor1 = 5;
    int RecorderFactor2 = 5;
    int RecorderFormat = 0;
    int RecorderQuality = 70;
    int RecorderTextTimeout = 1;
    int RecorderTextSize = 90;
};

#endif // SETTINGS_H
