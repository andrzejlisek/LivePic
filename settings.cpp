#include "settings.h"

Settings::Settings()
{
    QList<QScreen *> screens = QGuiApplication::screens();
    if (screens.length() > 0)
    {
        BoundX1 = screens[0]->geometry().x();
        BoundY1 = screens[0]->geometry().y();
        BoundX2 = screens[0]->geometry().x() + screens[0]->geometry().width();
        BoundY2 = screens[0]->geometry().y() + screens[0]->geometry().height();
    }
    for (int I = 0; I < screens.length(); I++)
    {
        if (BoundX1 > screens[I]->geometry().x())
        {
            BoundX1 = screens[I]->geometry().x();
        }
        if (BoundY1 > screens[I]->geometry().y())
        {
            BoundY1 = screens[I]->geometry().y();
        }
        if (BoundX2 < screens[I]->geometry().x() + screens[I]->geometry().width())
        {
            BoundX2 = screens[I]->geometry().x() + screens[I]->geometry().width();
        }
        if (BoundY2 < screens[I]->geometry().y() + screens[I]->geometry().height())
        {
            BoundY2 = screens[I]->geometry().y() + screens[I]->geometry().height();
        }
    }

    _BoundX1.push_back(BoundX1);
    _BoundY1.push_back(BoundY1);
    _BoundX2.push_back(BoundX2);
    _BoundY2.push_back(BoundY2);
    if (screens.length() > 1)
    {
        for (int I = 0; I < screens.length(); I++)
        {
            _BoundX1.push_back(screens[I]->geometry().x());
            _BoundY1.push_back(screens[I]->geometry().y());
            _BoundX2.push_back(screens[I]->geometry().x() + screens[I]->geometry().width());
            _BoundY2.push_back(screens[I]->geometry().y() + screens[I]->geometry().height());
        }
    }
    _BoundX1.push_back(-999999);
    _BoundY1.push_back(-999999);
    _BoundX2.push_back(999999);
    _BoundY2.push_back(999999);

    CF.FileLoad(Eden::ApplicationDirectory() + "Config.txt");
    CF.ParamGet("PicX", PicX);
    CF.ParamGet("PicY", PicY);
    CF.ParamGet("PicW", PicW);
    CF.ParamGet("PicH", PicH);
    CF.ParamGet("ViewX", ViewX);
    CF.ParamGet("ViewY", ViewY);
    CF.ParamGet("ViewW", ViewW);
    CF.ParamGet("ViewH", ViewH);
    CF.ParamGet("ViewMarginLeft", ViewMarginLeft);
    CF.ParamGet("ViewMarginTop", ViewMarginTop);
    CF.ParamGet("ViewMarginRight", ViewMarginRight);
    CF.ParamGet("ViewMarginBottom", ViewMarginBottom);
    CF.ParamGet("ViewOffsetX", ViewOffsetX);
    CF.ParamGet("ViewOffsetY", ViewOffsetY);
    CF.ParamGet("ViewStretched", ViewStretched);
    CF.ParamGet("PipeCount", PipeCount);
    CF.ParamGet("PicThreads", PicThreads);
    CF.ParamGet("MousePointerType", MousePointerType);
    CF.ParamGet("MouseSize", MouseSize);
    CF.ParamGet("MouseThickness", MouseThickness);
    CF.ParamGet("FollowMouse", FollowMouse);
    CF.ParamGet("Gamma", Gamma);
    CF.ParamGet("TransformFile", TransformFile);
    CF.ParamGet("BackColorR", BackColorR);
    CF.ParamGet("BackColorG", BackColorG);
    CF.ParamGet("BackColorB", BackColorB);
    CF.ParamGet("DelayLineCount", DelayLineCount);
    CF.ParamGet("DelayLineFileName", DelayLineFileName);
    CF.ParamGet("MouseMargin", MouseMargin);
    CF.ParamGet("StayOnTopPic", StayOnTopPic);
    CF.ParamGet("StayOnTopSet", StayOnTopSet);
    CF.ParamGet("SetCloseApp", SetCloseApp);
    CF.ParamGet("Throttle", Throttle);
    CF.ParamGet("NetAddr", NetAddr);
    CF.ParamGet("NetPort", NetPort);
    CF.ParamGet("PicSrcDst", PicSrcDst);
    CF.ParamGet("NetQuality1", NetQuality1);
    CF.ParamGet("NetQuality2", NetQuality2);
    CF.ParamGet("BoundX1", BoundX1);
    CF.ParamGet("BoundY1", BoundY1);
    CF.ParamGet("BoundX2", BoundX2);
    CF.ParamGet("BoundY2", BoundY2);
    CF.ParamGet("ViewFullscreen", ViewFullscreen);

    RefreshWorkingSettings();
}

Settings::~Settings()
{
}

void Settings::Save()
{
    CF.ParamSet("PicX", PicX);
    CF.ParamSet("PicY", PicY);
    CF.ParamSet("PicW", PicW);
    CF.ParamSet("PicH", PicH);
    CF.ParamSet("ViewX", ViewX);
    CF.ParamSet("ViewY", ViewY);
    CF.ParamSet("ViewW", ViewW);
    CF.ParamSet("ViewH", ViewH);
    CF.ParamSet("ViewMarginLeft", ViewMarginLeft);
    CF.ParamSet("ViewMarginTop", ViewMarginTop);
    CF.ParamSet("ViewMarginRight", ViewMarginRight);
    CF.ParamSet("ViewMarginBottom", ViewMarginBottom);
    CF.ParamSet("ViewOffsetX", ViewOffsetX);
    CF.ParamSet("ViewOffsetY", ViewOffsetY);
    CF.ParamSet("ViewStretched", ViewStretched);
    CF.ParamSet("PipeCount", PipeCount);
    CF.ParamSet("PicThreads", PicThreads);
    CF.ParamSet("MousePointerType", MousePointerType);
    CF.ParamSet("MouseSize", MouseSize);
    CF.ParamSet("MouseThickness", MouseThickness);
    CF.ParamSet("FollowMouse", FollowMouse);
    CF.ParamSet("Gamma", Gamma);
    CF.ParamSet("TransformFile", TransformFile);
    CF.ParamSet("BackColorR", BackColorR);
    CF.ParamSet("BackColorG", BackColorG);
    CF.ParamSet("BackColorB", BackColorB);
    CF.ParamSet("DelayLineCount", DelayLineCount);
    CF.ParamSet("DelayLineFileName", DelayLineFileName);
    CF.ParamSet("MouseMargin", MouseMargin);
    CF.ParamSet("StayOnTopPic", StayOnTopPic);
    CF.ParamSet("StayOnTopSet", StayOnTopSet);
    CF.ParamSet("SetCloseApp", SetCloseApp);
    CF.ParamSet("Throttle", Throttle);
    CF.ParamSet("NetAddr", NetAddr);
    CF.ParamSet("NetPort", NetPort);
    CF.ParamSet("PicSrcDst", PicSrcDst);
    CF.ParamSet("NetQuality1", NetQuality1);
    CF.ParamSet("NetQuality2", NetQuality2);
    CF.ParamSet("BoundX1", BoundX1);
    CF.ParamSet("BoundY1", BoundY1);
    CF.ParamSet("BoundX2", BoundX2);
    CF.ParamSet("BoundY2", BoundY2);
    CF.ParamSet("ViewFullscreen", ViewFullscreen);

    CF.FileSave(Eden::ApplicationDirectory() + "Config.txt");
}

void Settings::RefreshWorkingSettings()
{
    switch (PicSrcDst)
    {
        case 0: _PicSrcNet = false; _PicDstNet = false; break;
        case 1: _PicSrcNet = false; _PicDstNet = true; break;
        case 2: _PicSrcNet = false; _PicDstNet = true; break;
        case 3: _PicSrcNet = true; _PicDstNet = false; break;
    }
}
