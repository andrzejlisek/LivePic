#include "settings.h"

Settings::Settings()
{
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
    CF.FileSave(Eden::ApplicationDirectory() + "Config.txt");
}
