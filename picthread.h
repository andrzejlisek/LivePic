#ifndef PICTHREAD_H
#define PICTHREAD_H

#include <QObject>
#include <QThread>
#include <iostream>
#include <QDebug>
#include <QScreen>
#include <QPixmap>
#include <QGuiApplication>
#include <QLabel>
#include <thread>
#include "settings.h"
#include <vector>
#include <fstream>
#include <string>
#include "eden.h"
#include "qmouselabel.h"
#include "stopwatch.h"
#include "transformcore.h"
#include "picnetwork.h"
#include <queue>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextCodec>

#include "googleconvert.h"
#include "recorder.h"
#include "textcapture.h"

using namespace std;

class PicThread : public QThread
{
// #define DebugThreadSeq
#define PicBufIMargin 2
#define NullColor 16777216

// YUV -> RGB
#define YUV_C_R(L, C) Range((L) + (C), 0, 70000)
#define YUV_C_G(L, C) Range((L) + (C), 0, 70000)
#define YUV_C_B(L, C) Range((L) + (C), 0, 70000)

// RGB -> YUV
#define YUV_RGB_L(R, G, B) ((RWeight * (R) + GWeight * (G) + BWeight * (B)) / TWeight)
#define YUV_RGB_R(L, C) ((C) - (L))
#define YUV_RGB_G(L, C) ((C) - (L))
#define YUV_RGB_B(L, C) ((C) - (L))

    Q_OBJECT
public:
    Recorder * Recorder_;
    PicNetwork * PicNetwork_;
    int PicThreads = 1;
    uchar ColorDiv3[65536 * 3];
    TransformCore * TransformCore_;
    EdenClass::StopWatch SW;
    struct DitherMatrixElement
    {
        int T[5][5];
        int Colors;
        uint Color1;
        uint Color2;
        uint Color3;
        uint Color4;
    };

    explicit PicThread(QObject *parent = 0);
    ~PicThread();
    void WorkLoopSleep(int WorkLoopSleepTime);
    void WorkLoop();
    void run();
    void Stop();
    Settings * Settings_;
    TextCapture * TextCapture_;
    int FPS = 0;
    void OpLoad();
    string DebugInfo = "";

    uint GammaLUT_I[256];
    uint GammaLUT_O[70001];
    void ReInit();
    bool NeedReInit;
    QMouseLabel * PictureScreen;
    int HQX_YUV_Y[16777216];
    int HQX_YUV_U[16777216];
    int HQX_YUV_V[16777216];

    int HQX_DiffY = 0x30;
    int HQX_DiffU = 0x07;
    int HQX_DiffV = 0x06;

    #define HQX_RGB2YUV(R, G, B) (((R) << 16) + ((G) << 8) + (B))
    bool HQX_Diff_YUV(int YUV1, int YUV2);
    bool HQX_Diff_RGB(int R1, int G1, int B1, int R2, int G2, int B2);
    #define HQX_Diff(C1, C2) (abs(C1 - C2) > Threshold)
    #define HQX_Interpolate_2(C1, W1, C2, W2, S) ((C1 != C2) ? (C1 * W1 + C2 * W2) >> S : C1)
    #define HQX_Interpolate_3(C1, W1, C2, W2, C3, W3, S) ((C1 * W1 + C2 * W2 + C3 * W3) >> S)

    #define HQX_Interp1(C1, C2) HQX_Interpolate_2(C1, 3, C2, 1, 2)
    #define HQX_Interp2(C1, C2, C3) HQX_Interpolate_3(C1, 2, C2, 1, C3, 1, 2)
    #define HQX_Interp3(C1, C2) HQX_Interpolate_2(C1, 7, C2, 1, 3)
    #define HQX_Interp4(C1, C2, C3) HQX_Interpolate_3(C1, 2, C2, 7, C3, 7, 4)
    #define HQX_Interp5(C1, C2) HQX_Interpolate_2(C1, 1, C2, 1, 1)
    #define HQX_Interp6(C1, C2, C3) HQX_Interpolate_3(C1, 5, C2, 2, C3, 1, 3)
    #define HQX_Interp7(C1, C2, C3) HQX_Interpolate_3(C1, 6, C2, 1, C3, 1, 3)
    #define HQX_Interp8(C1, C2) HQX_Interpolate_2(C1, 5, C2, 3, 3)
    #define HQX_Interp9(C1, C2, C3) HQX_Interpolate_3(C1, 2, C2, 3, C3, 3, 3)
    #define HQX_Interp10(C1, C2, C3) HQX_Interpolate_3(C1, 14, C2, 1, C3, 1, 4)

    #define HQX_Interp1_RGB(R1, G1, B1, R2, G2, B2, _R, _G, _B) _R = HQX_Interp1(R1, R2); _G = HQX_Interp1(G1, G2); _B = HQX_Interp1(B1, B2);
    #define HQX_Interp2_RGB(R1, G1, B1, R2, G2, B2, R3, G3, B3, _R, _G, _B) _R = HQX_Interp2(R1, R2, R3); _G = HQX_Interp2(G1, G2, G3); _B = HQX_Interp2(B1, B2, B3);
    #define HQX_Interp3_RGB(R1, G1, B1, R2, G2, B2, _R, _G, _B) _R = HQX_Interp3(R1, R2); _G = HQX_Interp3(G1, G2); _B = HQX_Interp3(B1, B2);
    #define HQX_Interp4_RGB(R1, G1, B1, R2, G2, B2, R3, G3, B3, _R, _G, _B) _R = HQX_Interp4(R1, R2, R3); _G = HQX_Interp4(G1, G2, G3); _B = HQX_Interp4(B1, B2, B3);
    #define HQX_Interp5_RGB(R1, G1, B1, R2, G2, B2, _R, _G, _B) _R = HQX_Interp5(R1, R2); _G = HQX_Interp5(G1, G2); _B = HQX_Interp5(B1, B2);
    #define HQX_Interp6_RGB(R1, G1, B1, R2, G2, B2, R3, G3, B3, _R, _G, _B) _R = HQX_Interp6(R1, R2, R3); _G = HQX_Interp6(G1, G2, G3); _B = HQX_Interp6(B1, B2, B3);
    #define HQX_Interp7_RGB(R1, G1, B1, R2, G2, B2, R3, G3, B3, _R, _G, _B) _R = HQX_Interp7(R1, R2, R3); _G = HQX_Interp7(G1, G2, G3); _B = HQX_Interp7(B1, B2, B3);
    #define HQX_Interp8_RGB(R1, G1, B1, R2, G2, B2, _R, _G, _B) _R = HQX_Interp8(R1, R2); _G = HQX_Interp8(G1, G2); _B = HQX_Interp8(B1, B2);
    #define HQX_Interp9_RGB(R1, G1, B1, R2, G2, B2, R3, G3, B3, _R, _G, _B) _R = HQX_Interp9(R1, R2, R3); _G = HQX_Interp9(G1, G2, G3); _B = HQX_Interp9(B1, B2, B3);
    #define HQX_Interp10_RGB(R1, G1, B1, R2, G2, B2, R3, G3, B3, _R, _G, _B) _R = HQX_Interp10(R1, R2, R3); _G = HQX_Interp10(G1, G2, G3); _B = HQX_Interp10(B1, B2, B3);

    #define HQ2X_PIXEL00_RGB_0     R00 = W5R; G00 = W5G; B00 = W5B;
    #define HQ2X_PIXEL00_RGB_10    HQX_Interp1_RGB(W5R, W5G, W5B, W1R, W1G, W1B, R00, G00, B00);
    #define HQ2X_PIXEL00_RGB_11    HQX_Interp1_RGB(W5R, W5G, W5B, W4R, W4G, W4B, R00, G00, B00);
    #define HQ2X_PIXEL00_RGB_12    HQX_Interp1_RGB(W5R, W5G, W5B, W2R, W2G, W2B, R00, G00, B00);
    #define HQ2X_PIXEL00_RGB_20    HQX_Interp2_RGB(W5R, W5G, W5B, W4R, W4G, W4B, W2R, W2G, W2B, R00, G00, B00);
    #define HQ2X_PIXEL00_RGB_21    HQX_Interp2_RGB(W5R, W5G, W5B, W1R, W1G, W1B, W2R, W2G, W2B, R00, G00, B00);
    #define HQ2X_PIXEL00_RGB_22    HQX_Interp2_RGB(W5R, W5G, W5B, W1R, W1G, W1B, W4R, W4G, W4B, R00, G00, B00);
    #define HQ2X_PIXEL00_RGB_60    HQX_Interp6_RGB(W5R, W5G, W5B, W2R, W2G, W2B, W4R, W4G, W4B, R00, G00, B00);
    #define HQ2X_PIXEL00_RGB_61    HQX_Interp6_RGB(W5R, W5G, W5B, W4R, W4G, W4B, W2R, W2G, W2B, R00, G00, B00);
    #define HQ2X_PIXEL00_RGB_70    HQX_Interp7_RGB(W5R, W5G, W5B, W4R, W4G, W4B, W2R, W2G, W2B, R00, G00, B00);
    #define HQ2X_PIXEL00_RGB_90    HQX_Interp9_RGB(W5R, W5G, W5B, W4R, W4G, W4B, W2R, W2G, W2B, R00, G00, B00);
    #define HQ2X_PIXEL00_RGB_100   HQX_Interp10_RGB(W5R, W5G, W5B, W4R, W4G, W4B, W2R, W2G, W2B, R00, G00, B00);
    #define HQ2X_PIXEL01_RGB_0     R01 = W5R; G01 = W5G; B01 = W5B;
    #define HQ2X_PIXEL01_RGB_10    HQX_Interp1_RGB(W5R, W5G, W5B, W3R, W3G, W3B, R01, G01, B01);
    #define HQ2X_PIXEL01_RGB_11    HQX_Interp1_RGB(W5R, W5G, W5B, W2R, W2G, W2B, R01, G01, B01);
    #define HQ2X_PIXEL01_RGB_12    HQX_Interp1_RGB(W5R, W5G, W5B, W6R, W6G, W6B, R01, G01, B01);
    #define HQ2X_PIXEL01_RGB_20    HQX_Interp2_RGB(W5R, W5G, W5B, W2R, W2G, W2B, W6R, W6G, W6B, R01, G01, B01);
    #define HQ2X_PIXEL01_RGB_21    HQX_Interp2_RGB(W5R, W5G, W5B, W3R, W3G, W3B, W6R, W6G, W6B, R01, G01, B01);
    #define HQ2X_PIXEL01_RGB_22    HQX_Interp2_RGB(W5R, W5G, W5B, W3R, W3G, W3B, W2R, W2G, W2B, R01, G01, B01);
    #define HQ2X_PIXEL01_RGB_60    HQX_Interp6_RGB(W5R, W5G, W5B, W6R, W6G, W6B, W2R, W2G, W2B, R01, G01, B01);
    #define HQ2X_PIXEL01_RGB_61    HQX_Interp6_RGB(W5R, W5G, W5B, W2R, W2G, W2B, W6R, W6G, W6B, R01, G01, B01);
    #define HQ2X_PIXEL01_RGB_70    HQX_Interp7_RGB(W5R, W5G, W5B, W2R, W2G, W2B, W6R, W6G, W6B, R01, G01, B01);
    #define HQ2X_PIXEL01_RGB_90    HQX_Interp9_RGB(W5R, W5G, W5B, W2R, W2G, W2B, W6R, W6G, W6B, R01, G01, B01);
    #define HQ2X_PIXEL01_RGB_100   HQX_Interp10_RGB(W5R, W5G, W5B, W2R, W2G, W2B, W6R, W6G, W6B, R01, G01, B01);
    #define HQ2X_PIXEL10_RGB_0     R10 = W5R; G10 = W5G; B10 = W5B;
    #define HQ2X_PIXEL10_RGB_10    HQX_Interp1_RGB(W5R, W5G, W5B, W7R, W7G, W7B, R10, G10, B10);
    #define HQ2X_PIXEL10_RGB_11    HQX_Interp1_RGB(W5R, W5G, W5B, W8R, W8G, W8B, R10, G10, B10);
    #define HQ2X_PIXEL10_RGB_12    HQX_Interp1_RGB(W5R, W5G, W5B, W4R, W4G, W4B, R10, G10, B10);
    #define HQ2X_PIXEL10_RGB_20    HQX_Interp2_RGB(W5R, W5G, W5B, W8R, W8G, W8B, W4R, W4G, W4B, R10, G10, B10);
    #define HQ2X_PIXEL10_RGB_21    HQX_Interp2_RGB(W5R, W5G, W5B, W7R, W7G, W7B, W4R, W4G, W4B, R10, G10, B10);
    #define HQ2X_PIXEL10_RGB_22    HQX_Interp2_RGB(W5R, W5G, W5B, W7R, W7G, W7B, W8R, W8G, W8B, R10, G10, B10);
    #define HQ2X_PIXEL10_RGB_60    HQX_Interp6_RGB(W5R, W5G, W5B, W4R, W4G, W4B, W8R, W8G, W8B, R10, G10, B10);
    #define HQ2X_PIXEL10_RGB_61    HQX_Interp6_RGB(W5R, W5G, W5B, W8R, W8G, W8B, W4R, W4G, W4B, R10, G10, B10);
    #define HQ2X_PIXEL10_RGB_70    HQX_Interp7_RGB(W5R, W5G, W5B, W8R, W8G, W8B, W4R, W4G, W4B, R10, G10, B10);
    #define HQ2X_PIXEL10_RGB_90    HQX_Interp9_RGB(W5R, W5G, W5B, W8R, W8G, W8B, W4R, W4G, W4B, R10, G10, B10);
    #define HQ2X_PIXEL10_RGB_100   HQX_Interp10_RGB(W5R, W5G, W5B, W8R, W8G, W8B, W4R, W4G, W4B, R10, G10, B10);
    #define HQ2X_PIXEL11_RGB_0     R11 = W5R; G11 = W5G; B11 = W5B;
    #define HQ2X_PIXEL11_RGB_10    HQX_Interp1_RGB(W5R, W5G, W5B, W9R, W9G, W9B, R11, G11, B11);
    #define HQ2X_PIXEL11_RGB_11    HQX_Interp1_RGB(W5R, W5G, W5B, W6R, W6G, W6B, R11, G11, B11);
    #define HQ2X_PIXEL11_RGB_12    HQX_Interp1_RGB(W5R, W5G, W5B, W8R, W8G, W8B, R11, G11, B11);
    #define HQ2X_PIXEL11_RGB_20    HQX_Interp2_RGB(W5R, W5G, W5B, W6R, W6G, W6B, W8R, W8G, W8B, R11, G11, B11);
    #define HQ2X_PIXEL11_RGB_21    HQX_Interp2_RGB(W5R, W5G, W5B, W9R, W9G, W9B, W8R, W8G, W8B, R11, G11, B11);
    #define HQ2X_PIXEL11_RGB_22    HQX_Interp2_RGB(W5R, W5G, W5B, W9R, W9G, W9B, W6R, W6G, W6B, R11, G11, B11);
    #define HQ2X_PIXEL11_RGB_60    HQX_Interp6_RGB(W5R, W5G, W5B, W8R, W8G, W8B, W6R, W6G, W6B, R11, G11, B11);
    #define HQ2X_PIXEL11_RGB_61    HQX_Interp6_RGB(W5R, W5G, W5B, W6R, W6G, W6B, W8R, W8G, W8B, R11, G11, B11);
    #define HQ2X_PIXEL11_RGB_70    HQX_Interp7_RGB(W5R, W5G, W5B, W6R, W6G, W6B, W8R, W8G, W8B, R11, G11, B11);
    #define HQ2X_PIXEL11_RGB_90    HQX_Interp9_RGB(W5R, W5G, W5B, W6R, W6G, W6B, W8R, W8G, W8B, R11, G11, B11);
    #define HQ2X_PIXEL11_RGB_100   HQX_Interp10_RGB(W5R, W5G, W5B, W6R, W6G, W6B, W8R, W8G, W8B, R11, G11, B11);

    #define HQ3X_PIXEL00_RGB_1M    HQX_Interp1_RGB(W5R, W5G, W5B, W1R, W1G, W1B, R00, G00, B00);
    #define HQ3X_PIXEL00_RGB_1U    HQX_Interp1_RGB(W5R, W5G, W5B, W2R, W2G, W2B, R00, G00, B00);
    #define HQ3X_PIXEL00_RGB_1L    HQX_Interp1_RGB(W5R, W5G, W5B, W4R, W4G, W4B, R00, G00, B00);
    #define HQ3X_PIXEL00_RGB_2     HQX_Interp2_RGB(W5R, W5G, W5B, W4R, W4G, W4B, W2R, W2G, W2B, R00, G00, B00);
    #define HQ3X_PIXEL00_RGB_4     HQX_Interp4_RGB(W5R, W5G, W5B, W4R, W4G, W4B, W2R, W2G, W2B, R00, G00, B00);
    #define HQ3X_PIXEL00_RGB_5     HQX_Interp5_RGB(W4R, W4G, W4B, W2R, W2G, W2B, R00, G00, B00);
    #define HQ3X_PIXEL00_RGB_C     R00 = W5R; G00 = W5G; B00 = W5B;
    #define HQ3X_PIXEL01_RGB_1     HQX_Interp1_RGB(W5R, W5G, W5B, W2R, W2G, W2B, R01, G01, B01);
    #define HQ3X_PIXEL01_RGB_3     HQX_Interp3_RGB(W5R, W5G, W5B, W2R, W2G, W2B, R01, G01, B01);
    #define HQ3X_PIXEL01_RGB_6     HQX_Interp1_RGB(W2R, W2G, W2B, W5R, W5G, W5B, R01, G01, B01);
    #define HQ3X_PIXEL01_RGB_C     R01 = W5R; G01 = W5G; B01 = W5B;
    #define HQ3X_PIXEL02_RGB_1M    HQX_Interp1_RGB(W5R, W5G, W5B, W3R, W3G, W3B, R02, G02, B02);
    #define HQ3X_PIXEL02_RGB_1U    HQX_Interp1_RGB(W5R, W5G, W5B, W2R, W2G, W2B, R02, G02, B02);
    #define HQ3X_PIXEL02_RGB_1R    HQX_Interp1_RGB(W5R, W5G, W5B, W6R, W6G, W6B, R02, G02, B02);
    #define HQ3X_PIXEL02_RGB_2     HQX_Interp2_RGB(W5R, W5G, W5B, W2R, W2G, W2B, W6R, W6G, W6B, R02, G02, B02);
    #define HQ3X_PIXEL02_RGB_4     HQX_Interp4_RGB(W5R, W5G, W5B, W2R, W2G, W2B, W6R, W6G, W6B, R02, G02, B02);
    #define HQ3X_PIXEL02_RGB_5     HQX_Interp5_RGB(W2R, W2G, W2B, W6R, W6G, W6B, R02, G02, B02);
    #define HQ3X_PIXEL02_RGB_C     R02 = W5R; G02 = W5G; B02 = W5B;
    #define HQ3X_PIXEL10_RGB_1     HQX_Interp1_RGB(W5R, W5G, W5B, W4R, W4G, W4B, R10, G10, B10);
    #define HQ3X_PIXEL10_RGB_3     HQX_Interp3_RGB(W5R, W5G, W5B, W4R, W4G, W4B, R10, G10, B10);
    #define HQ3X_PIXEL10_RGB_6     HQX_Interp1_RGB(W4R, W4G, W4B, W5R, W5G, W5B, R10, G10, B10);
    #define HQ3X_PIXEL10_RGB_C     R10 = W5R; G10 = W5G; B10 = W5B;
    #define HQ3X_PIXEL11_RGB       R11 = W5R; G11 = W5G; B11 = W5B;
    #define HQ3X_PIXEL12_RGB_1     HQX_Interp1_RGB(W5R, W5G, W5B, W6R, W6G, W6B, R12, G12, B12);
    #define HQ3X_PIXEL12_RGB_3     HQX_Interp3_RGB(W5R, W5G, W5B, W6R, W6G, W6B, R12, G12, B12);
    #define HQ3X_PIXEL12_RGB_6     HQX_Interp1_RGB(W6R, W6G, W6B, W5R, W5G, W5B, R12, G12, B12);
    #define HQ3X_PIXEL12_RGB_C     R12 = W5R; G12 = W5G; B12 = W5B;
    #define HQ3X_PIXEL20_RGB_1M    HQX_Interp1_RGB(W5R, W5G, W5B, W7R, W7G, W7B, R20, G20, B20);
    #define HQ3X_PIXEL20_RGB_1D    HQX_Interp1_RGB(W5R, W5G, W5B, W8R, W8G, W8B, R20, G20, B20);
    #define HQ3X_PIXEL20_RGB_1L    HQX_Interp1_RGB(W5R, W5G, W5B, W4R, W4G, W4B, R20, G20, B20);
    #define HQ3X_PIXEL20_RGB_2     HQX_Interp2_RGB(W5R, W5G, W5B, W8R, W8G, W8B, W4R, W4G, W4B, R20, G20, B20);
    #define HQ3X_PIXEL20_RGB_4     HQX_Interp4_RGB(W5R, W5G, W5B, W8R, W8G, W8B, W4R, W4G, W4B, R20, G20, B20);
    #define HQ3X_PIXEL20_RGB_5     HQX_Interp5_RGB(W8R, W8G, W8B, W4R, W4G, W4B, R20, G20, B20);
    #define HQ3X_PIXEL20_RGB_C     R20 = W5R; G20 = W5G; B20 = W5B;
    #define HQ3X_PIXEL21_RGB_1     HQX_Interp1_RGB(W5R, W5G, W5B, W8R, W8G, W8B, R21, G21, B21);
    #define HQ3X_PIXEL21_RGB_3     HQX_Interp3_RGB(W5R, W5G, W5B, W8R, W8G, W8B, R21, G21, B21);
    #define HQ3X_PIXEL21_RGB_6     HQX_Interp1_RGB(W8R, W8G, W8B, W5R, W5G, W5B, R21, G21, B21);
    #define HQ3X_PIXEL21_RGB_C     R21 = W5R; G21 = W5G; B21 = W5B;
    #define HQ3X_PIXEL22_RGB_1M    HQX_Interp1_RGB(W5R, W5G, W5B, W9R, W9G, W9B, R22, G22, B22);
    #define HQ3X_PIXEL22_RGB_1D    HQX_Interp1_RGB(W5R, W5G, W5B, W8R, W8G, W8B, R22, G22, B22);
    #define HQ3X_PIXEL22_RGB_1R    HQX_Interp1_RGB(W5R, W5G, W5B, W6R, W6G, W6B, R22, G22, B22);
    #define HQ3X_PIXEL22_RGB_2     HQX_Interp2_RGB(W5R, W5G, W5B, W6R, W6G, W6B, W8R, W8G, W8B, R22, G22, B22);
    #define HQ3X_PIXEL22_RGB_4     HQX_Interp4_RGB(W5R, W5G, W5B, W6R, W6G, W6B, W8R, W8G, W8B, R22, G22, B22);
    #define HQ3X_PIXEL22_RGB_5     HQX_Interp5_RGB(W6R, W6G, W6B, W8R, W8G, W8B, R22, G22, B22);
    #define HQ3X_PIXEL22_RGB_C     R22 = W5R; G22 = W5G; B22 = W5B;

    #define HQ4X_PIXEL00_RGB_0     R00 = W5R; G00 = W5G; B00 = W5B;
    #define HQ4X_PIXEL00_RGB_11    HQX_Interp1_RGB(W5R, W5G, W5B, W4R, W4G, W4B, R00, G00, B00);
    #define HQ4X_PIXEL00_RGB_12    HQX_Interp1_RGB(W5R, W5G, W5B, W2R, W2G, W2B, R00, G00, B00);
    #define HQ4X_PIXEL00_RGB_20    HQX_Interp2_RGB(W5R, W5G, W5B, W2R, W2G, W2B, W4R, W4G, W4B, R00, G00, B00);
    #define HQ4X_PIXEL00_RGB_50    HQX_Interp5_RGB(W2R, W2G, W2B, W4R, W4G, W4B, R00, G00, B00);
    #define HQ4X_PIXEL00_RGB_80    HQX_Interp8_RGB(W5R, W5G, W5B, W1R, W1G, W1B, R00, G00, B00);
    #define HQ4X_PIXEL00_RGB_81    HQX_Interp8_RGB(W5R, W5G, W5B, W4R, W4G, W4B, R00, G00, B00);
    #define HQ4X_PIXEL00_RGB_82    HQX_Interp8_RGB(W5R, W5G, W5B, W2R, W2G, W2B, R00, G00, B00);
    #define HQ4X_PIXEL01_RGB_0     R01 = W5R; G01 = W5G; B01 = W5B;
    #define HQ4X_PIXEL01_RGB_10    HQX_Interp1_RGB(W5R, W5G, W5B, W1R, W1G, W1B, R01, G01, B01);
    #define HQ4X_PIXEL01_RGB_12    HQX_Interp1_RGB(W5R, W5G, W5B, W2R, W2G, W2B, R01, G01, B01);
    #define HQ4X_PIXEL01_RGB_14    HQX_Interp1_RGB(W2R, W2G, W2B, W5R, W5G, W5B, R01, G01, B01);
    #define HQ4X_PIXEL01_RGB_21    HQX_Interp2_RGB(W2R, W2G, W2B, W5R, W5G, W5B, W4R, W4G, W4B, R01, G01, B01);
    #define HQ4X_PIXEL01_RGB_31    HQX_Interp3_RGB(W5R, W5G, W5B, W4R, W4G, W4B, R01, G01, B01);
    #define HQ4X_PIXEL01_RGB_50    HQX_Interp5_RGB(W2R, W2G, W2B, W5R, W5G, W5B, R01, G01, B01);
    #define HQ4X_PIXEL01_RGB_60    HQX_Interp6_RGB(W5R, W5G, W5B, W2R, W2G, W2B, W4R, W4G, W4B, R01, G01, B01);
    #define HQ4X_PIXEL01_RGB_61    HQX_Interp6_RGB(W5R, W5G, W5B, W2R, W2G, W2B, W1R, W1G, W1B, R01, G01, B01);
    #define HQ4X_PIXEL01_RGB_82    HQX_Interp8_RGB(W5R, W5G, W5B, W2R, W2G, W2B, R01, G01, B01);
    #define HQ4X_PIXEL01_RGB_83    HQX_Interp8_RGB(W2R, W2G, W2B, W4R, W4G, W4B, R01, G01, B01);
    #define HQ4X_PIXEL02_RGB_0     R02 = W5R; G02 = W5G; B02 = W5B;
    #define HQ4X_PIXEL02_RGB_10    HQX_Interp1_RGB(W5R, W5G, W5B, W3R, W3G, W3B, R02, G02, B02);
    #define HQ4X_PIXEL02_RGB_11    HQX_Interp1_RGB(W5R, W5G, W5B, W2R, W2G, W2B, R02, G02, B02);
    #define HQ4X_PIXEL02_RGB_13    HQX_Interp1_RGB(W2R, W2G, W2B, W5R, W5G, W5B, R02, G02, B02);
    #define HQ4X_PIXEL02_RGB_21    HQX_Interp2_RGB(W2R, W2G, W2B, W5R, W5G, W5B, W6R, W6G, W6B, R02, G02, B02);
    #define HQ4X_PIXEL02_RGB_32    HQX_Interp3_RGB(W5R, W5G, W5B, W6R, W6G, W6B, R02, G02, B02);
    #define HQ4X_PIXEL02_RGB_50    HQX_Interp5_RGB(W2R, W2G, W2B, W5R, W5G, W5B, R02, G02, B02);
    #define HQ4X_PIXEL02_RGB_60    HQX_Interp6_RGB(W5R, W5G, W5B, W2R, W2G, W2B, W6R, W6G, W6B, R02, G02, B02);
    #define HQ4X_PIXEL02_RGB_61    HQX_Interp6_RGB(W5R, W5G, W5B, W2R, W2G, W2B, W3R, W3G, W3B, R02, G02, B02);
    #define HQ4X_PIXEL02_RGB_81    HQX_Interp8_RGB(W5R, W5G, W5B, W2R, W2G, W2B, R02, G02, B02);
    #define HQ4X_PIXEL02_RGB_83    HQX_Interp8_RGB(W2R, W2G, W2B, W6R, W6G, W6B, R02, G02, B02);
    #define HQ4X_PIXEL03_RGB_0     R03 = W5R; G03 = W5G; B03 = W5B;
    #define HQ4X_PIXEL03_RGB_11    HQX_Interp1_RGB(W5R, W5G, W5B, W2R, W2G, W2B, R03, G03, B03);
    #define HQ4X_PIXEL03_RGB_12    HQX_Interp1_RGB(W5R, W5G, W5B, W6R, W6G, W6B, R03, G03, B03);
    #define HQ4X_PIXEL03_RGB_20    HQX_Interp2_RGB(W5R, W5G, W5B, W2R, W2G, W2B, W6R, W6G, W6B, R03, G03, B03);
    #define HQ4X_PIXEL03_RGB_50    HQX_Interp5_RGB(W2R, W2G, W2B, W6R, W6G, W6B, R03, G03, B03);
    #define HQ4X_PIXEL03_RGB_80    HQX_Interp8_RGB(W5R, W5G, W5B, W3R, W3G, W3B, R03, G03, B03);
    #define HQ4X_PIXEL03_RGB_81    HQX_Interp8_RGB(W5R, W5G, W5B, W2R, W2G, W2B, R03, G03, B03);
    #define HQ4X_PIXEL03_RGB_82    HQX_Interp8_RGB(W5R, W5G, W5B, W6R, W6G, W6B, R03, G03, B03);
    #define HQ4X_PIXEL10_RGB_0     R10 = W5R; G10 = W5G; B10 = W5B;
    #define HQ4X_PIXEL10_RGB_10    HQX_Interp1_RGB(W5R, W5G, W5B, W1R, W1G, W1B, R10, G10, B10);
    #define HQ4X_PIXEL10_RGB_11    HQX_Interp1_RGB(W5R, W5G, W5B, W4R, W4G, W4B, R10, G10, B10);
    #define HQ4X_PIXEL10_RGB_13    HQX_Interp1_RGB(W4R, W4G, W4B, W5R, W5G, W5B, R10, G10, B10);
    #define HQ4X_PIXEL10_RGB_21    HQX_Interp2_RGB(W4R, W4G, W4B, W5R, W5G, W5B, W2R, W2G, W2B, R10, G10, B10);
    #define HQ4X_PIXEL10_RGB_32    HQX_Interp3_RGB(W5R, W5G, W5B, W2R, W2G, W2B, R10, G10, B10);
    #define HQ4X_PIXEL10_RGB_50    HQX_Interp5_RGB(W4R, W4G, W4B, W5R, W5G, W5B, R10, G10, B10);
    #define HQ4X_PIXEL10_RGB_60    HQX_Interp6_RGB(W5R, W5G, W5B, W4R, W4G, W4B, W2R, W2G, W2B, R10, G10, B10);
    #define HQ4X_PIXEL10_RGB_61    HQX_Interp6_RGB(W5R, W5G, W5B, W4R, W4G, W4B, W1R, W1G, W1B, R10, G10, B10);
    #define HQ4X_PIXEL10_RGB_81    HQX_Interp8_RGB(W5R, W5G, W5B, W4R, W4G, W4B, R10, G10, B10);
    #define HQ4X_PIXEL10_RGB_83    HQX_Interp8_RGB(W4R, W4G, W4B, W2R, W2G, W2B, R10, G10, B10);
    #define HQ4X_PIXEL11_RGB_0     R11 = W5R; G11 = W5G; B11 = W5B;
    #define HQ4X_PIXEL11_RGB_30    HQX_Interp3_RGB(W5R, W5G, W5B, W1R, W1G, W1B, R11, G11, B11);
    #define HQ4X_PIXEL11_RGB_31    HQX_Interp3_RGB(W5R, W5G, W5B, W4R, W4G, W4B, R11, G11, B11);
    #define HQ4X_PIXEL11_RGB_32    HQX_Interp3_RGB(W5R, W5G, W5B, W2R, W2G, W2B, R11, G11, B11);
    #define HQ4X_PIXEL11_RGB_70    HQX_Interp7_RGB(W5R, W5G, W5B, W4R, W4G, W4B, W2R, W2G, W2B, R11, G11, B11);
    #define HQ4X_PIXEL12_RGB_0     R12 = W5R; G12 = W5G; B12 = W5B;
    #define HQ4X_PIXEL12_RGB_30    HQX_Interp3_RGB(W5R, W5G, W5B, W3R, W3G, W3B, R12, G12, B12);
    #define HQ4X_PIXEL12_RGB_31    HQX_Interp3_RGB(W5R, W5G, W5B, W2R, W2G, W2B, R12, G12, B12);
    #define HQ4X_PIXEL12_RGB_32    HQX_Interp3_RGB(W5R, W5G, W5B, W6R, W6G, W6B, R12, G12, B12);
    #define HQ4X_PIXEL12_RGB_70    HQX_Interp7_RGB(W5R, W5G, W5B, W6R, W6G, W6B, W2R, W2G, W2B, R12, G12, B12);
    #define HQ4X_PIXEL13_RGB_0     R13 = W5R; G13 = W5G; B13 = W5B;
    #define HQ4X_PIXEL13_RGB_10    HQX_Interp1_RGB(W5R, W5G, W5B, W3R, W3G, W3B, R13, G13, B13);
    #define HQ4X_PIXEL13_RGB_12    HQX_Interp1_RGB(W5R, W5G, W5B, W6R, W6G, W6B, R13, G13, B13);
    #define HQ4X_PIXEL13_RGB_14    HQX_Interp1_RGB(W6R, W6G, W6B, W5R, W5G, W5B, R13, G13, B13);
    #define HQ4X_PIXEL13_RGB_21    HQX_Interp2_RGB(W6R, W6G, W6B, W5R, W5G, W5B, W2R, W2G, W2B, R13, G13, B13);
    #define HQ4X_PIXEL13_RGB_31    HQX_Interp3_RGB(W5R, W5G, W5B, W2R, W2G, W2B, R13, G13, B13);
    #define HQ4X_PIXEL13_RGB_50    HQX_Interp5_RGB(W6R, W6G, W6B, W5R, W5G, W5B, R13, G13, B13);
    #define HQ4X_PIXEL13_RGB_60    HQX_Interp6_RGB(W5R, W5G, W5B, W6R, W6G, W6B, W2R, W2G, W2B, R13, G13, B13);
    #define HQ4X_PIXEL13_RGB_61    HQX_Interp6_RGB(W5R, W5G, W5B, W6R, W6G, W6B, W3R, W3G, W3B, R13, G13, B13);
    #define HQ4X_PIXEL13_RGB_82    HQX_Interp8_RGB(W5R, W5G, W5B, W6R, W6G, W6B, R13, G13, B13);
    #define HQ4X_PIXEL13_RGB_83    HQX_Interp8_RGB(W6R, W6G, W6B, W2R, W2G, W2B, R13, G13, B13);
    #define HQ4X_PIXEL20_RGB_0     R20 = W5R; G20 = W5G; B20 = W5B;
    #define HQ4X_PIXEL20_RGB_10    HQX_Interp1_RGB(W5R, W5G, W5B, W7R, W7G, W7B, R20, G20, B20);
    #define HQ4X_PIXEL20_RGB_12    HQX_Interp1_RGB(W5R, W5G, W5B, W4R, W4G, W4B, R20, G20, B20);
    #define HQ4X_PIXEL20_RGB_14    HQX_Interp1_RGB(W4R, W4G, W4B, W5R, W5G, W5B, R20, G20, B20);
    #define HQ4X_PIXEL20_RGB_21    HQX_Interp2_RGB(W4R, W4G, W4B, W5R, W5G, W5B, W8R, W8G, W8B, R20, G20, B20);
    #define HQ4X_PIXEL20_RGB_31    HQX_Interp3_RGB(W5R, W5G, W5B, W8R, W8G, W8B, R20, G20, B20);
    #define HQ4X_PIXEL20_RGB_50    HQX_Interp5_RGB(W4R, W4G, W4B, W5R, W5G, W5B, R20, G20, B20);
    #define HQ4X_PIXEL20_RGB_60    HQX_Interp6_RGB(W5R, W5G, W5B, W4R, W4G, W4B, W8R, W8G, W8B, R20, G20, B20);
    #define HQ4X_PIXEL20_RGB_61    HQX_Interp6_RGB(W5R, W5G, W5B, W4R, W4G, W4B, W7R, W7G, W7B, R20, G20, B20);
    #define HQ4X_PIXEL20_RGB_82    HQX_Interp8_RGB(W5R, W5G, W5B, W4R, W4G, W4B, R20, G20, B20);
    #define HQ4X_PIXEL20_RGB_83    HQX_Interp8_RGB(W4R, W4G, W4B, W8R, W8G, W8B, R20, G20, B20);
    #define HQ4X_PIXEL21_RGB_0     R21 = W5R; G21 = W5G; B21 = W5B;
    #define HQ4X_PIXEL21_RGB_30    HQX_Interp3_RGB(W5R, W5G, W5B, W7R, W7G, W7B, R21, G21, B21);
    #define HQ4X_PIXEL21_RGB_31    HQX_Interp3_RGB(W5R, W5G, W5B, W8R, W8G, W8B, R21, G21, B21);
    #define HQ4X_PIXEL21_RGB_32    HQX_Interp3_RGB(W5R, W5G, W5B, W4R, W4G, W4B, R21, G21, B21);
    #define HQ4X_PIXEL21_RGB_70    HQX_Interp7_RGB(W5R, W5G, W5B, W4R, W4G, W4B, W8R, W8G, W8B, R21, G21, B21);
    #define HQ4X_PIXEL22_RGB_0     R22 = W5R; G22 = W5G; B22 = W5B;
    #define HQ4X_PIXEL22_RGB_30    HQX_Interp3_RGB(W5R, W5G, W5B, W9R, W9G, W9B, R22, G22, B22);
    #define HQ4X_PIXEL22_RGB_31    HQX_Interp3_RGB(W5R, W5G, W5B, W6R, W6G, W6B, R22, G22, B22);
    #define HQ4X_PIXEL22_RGB_32    HQX_Interp3_RGB(W5R, W5G, W5B, W8R, W8G, W8B, R22, G22, B22);
    #define HQ4X_PIXEL22_RGB_70    HQX_Interp7_RGB(W5R, W5G, W5B, W6R, W6G, W6B, W8R, W8G, W8B, R22, G22, B22);
    #define HQ4X_PIXEL23_RGB_0     R23 = W5R; G23 = W5G; B23 = W5B;
    #define HQ4X_PIXEL23_RGB_10    HQX_Interp1_RGB(W5R, W5G, W5B, W9R, W9G, W9B, R23, G23, B23);
    #define HQ4X_PIXEL23_RGB_11    HQX_Interp1_RGB(W5R, W5G, W5B, W6R, W6G, W6B, R23, G23, B23);
    #define HQ4X_PIXEL23_RGB_13    HQX_Interp1_RGB(W6R, W6G, W6B, W5R, W5G, W5B, R23, G23, B23);
    #define HQ4X_PIXEL23_RGB_21    HQX_Interp2_RGB(W6R, W6G, W6B, W5R, W5G, W5B, W8R, W8G, W8B, R23, G23, B23);
    #define HQ4X_PIXEL23_RGB_32    HQX_Interp3_RGB(W5R, W5G, W5B, W8R, W8G, W8B, R23, G23, B23);
    #define HQ4X_PIXEL23_RGB_50    HQX_Interp5_RGB(W6R, W6G, W6B, W5R, W5G, W5B, R23, G23, B23);
    #define HQ4X_PIXEL23_RGB_60    HQX_Interp6_RGB(W5R, W5G, W5B, W6R, W6G, W6B, W8R, W8G, W8B, R23, G23, B23);
    #define HQ4X_PIXEL23_RGB_61    HQX_Interp6_RGB(W5R, W5G, W5B, W6R, W6G, W6B, W9R, W9G, W9B, R23, G23, B23);
    #define HQ4X_PIXEL23_RGB_81    HQX_Interp8_RGB(W5R, W5G, W5B, W6R, W6G, W6B, R23, G23, B23);
    #define HQ4X_PIXEL23_RGB_83    HQX_Interp8_RGB(W6R, W6G, W6B, W8R, W8G, W8B, R23, G23, B23);
    #define HQ4X_PIXEL30_RGB_0     R30 = W5R; G30 = W5G; B30 = W5B;
    #define HQ4X_PIXEL30_RGB_11    HQX_Interp1_RGB(W5R, W5G, W5B, W8R, W8G, W8B, R30, G30, B30);
    #define HQ4X_PIXEL30_RGB_12    HQX_Interp1_RGB(W5R, W5G, W5B, W4R, W4G, W4B, R30, G30, B30);
    #define HQ4X_PIXEL30_RGB_20    HQX_Interp2_RGB(W5R, W5G, W5B, W8R, W8G, W8B, W4R, W4G, W4B, R30, G30, B30);
    #define HQ4X_PIXEL30_RGB_50    HQX_Interp5_RGB(W8R, W8G, W8B, W4R, W4G, W4B, R30, G30, B30);
    #define HQ4X_PIXEL30_RGB_80    HQX_Interp8_RGB(W5R, W5G, W5B, W7R, W7G, W7B, R30, G30, B30);
    #define HQ4X_PIXEL30_RGB_81    HQX_Interp8_RGB(W5R, W5G, W5B, W8R, W8G, W8B, R30, G30, B30);
    #define HQ4X_PIXEL30_RGB_82    HQX_Interp8_RGB(W5R, W5G, W5B, W4R, W4G, W4B, R30, G30, B30);
    #define HQ4X_PIXEL31_RGB_0     R31 = W5R; G31 = W5G; B31 = W5B;
    #define HQ4X_PIXEL31_RGB_10    HQX_Interp1_RGB(W5R, W5G, W5B, W7R, W7G, W7B, R31, G31, B31);
    #define HQ4X_PIXEL31_RGB_11    HQX_Interp1_RGB(W5R, W5G, W5B, W8R, W8G, W8B, R31, G31, B31);
    #define HQ4X_PIXEL31_RGB_13    HQX_Interp1_RGB(W8R, W8G, W8B, W5R, W5G, W5B, R31, G31, B31);
    #define HQ4X_PIXEL31_RGB_21    HQX_Interp2_RGB(W8R, W8G, W8B, W5R, W5G, W5B, W4R, W4G, W4B, R31, G31, B31);
    #define HQ4X_PIXEL31_RGB_32    HQX_Interp3_RGB(W5R, W5G, W5B, W4R, W4G, W4B, R31, G31, B31);
    #define HQ4X_PIXEL31_RGB_50    HQX_Interp5_RGB(W8R, W8G, W8B, W5R, W5G, W5B, R31, G31, B31);
    #define HQ4X_PIXEL31_RGB_60    HQX_Interp6_RGB(W5R, W5G, W5B, W8R, W8G, W8B, W4R, W4G, W4B, R31, G31, B31);
    #define HQ4X_PIXEL31_RGB_61    HQX_Interp6_RGB(W5R, W5G, W5B, W8R, W8G, W8B, W7R, W7G, W7B, R31, G31, B31);
    #define HQ4X_PIXEL31_RGB_81    HQX_Interp8_RGB(W5R, W5G, W5B, W8R, W8G, W8B, R31, G31, B31);
    #define HQ4X_PIXEL31_RGB_83    HQX_Interp8_RGB(W8R, W8G, W8B, W4R, W4G, W4B, R31, G31, B31);
    #define HQ4X_PIXEL32_RGB_0     R32 = W5R; G32 = W5G; B32 = W5B;
    #define HQ4X_PIXEL32_RGB_10    HQX_Interp1_RGB(W5R, W5G, W5B, W9R, W9G, W9B, R32, G32, B32);
    #define HQ4X_PIXEL32_RGB_12    HQX_Interp1_RGB(W5R, W5G, W5B, W8R, W8G, W8B, R32, G32, B32);
    #define HQ4X_PIXEL32_RGB_14    HQX_Interp1_RGB(W8R, W8G, W8B, W5R, W5G, W5B, R32, G32, B32);
    #define HQ4X_PIXEL32_RGB_21    HQX_Interp2_RGB(W8R, W8G, W8B, W5R, W5G, W5B, W6R, W6G, W6B, R32, G32, B32);
    #define HQ4X_PIXEL32_RGB_31    HQX_Interp3_RGB(W5R, W5G, W5B, W6R, W6G, W6B, R32, G32, B32);
    #define HQ4X_PIXEL32_RGB_50    HQX_Interp5_RGB(W8R, W8G, W8B, W5R, W5G, W5B, R32, G32, B32);
    #define HQ4X_PIXEL32_RGB_60    HQX_Interp6_RGB(W5R, W5G, W5B, W8R, W8G, W8B, W6R, W6G, W6B, R32, G32, B32);
    #define HQ4X_PIXEL32_RGB_61    HQX_Interp6_RGB(W5R, W5G, W5B, W8R, W8G, W8B, W9R, W9G, W9B, R32, G32, B32);
    #define HQ4X_PIXEL32_RGB_82    HQX_Interp8_RGB(W5R, W5G, W5B, W8R, W8G, W8B, R32, G32, B32);
    #define HQ4X_PIXEL32_RGB_83    HQX_Interp8_RGB(W8R, W8G, W8B, W6R, W6G, W6B, R32, G32, B32);
    #define HQ4X_PIXEL33_RGB_0     R33 = W5R; G33 = W5G; B33 = W5B;
    #define HQ4X_PIXEL33_RGB_11    HQX_Interp1_RGB(W5R, W5G, W5B, W6R, W6G, W6B, R33, G33, B33);
    #define HQ4X_PIXEL33_RGB_12    HQX_Interp1_RGB(W5R, W5G, W5B, W8R, W8G, W8B, R33, G33, B33);
    #define HQ4X_PIXEL33_RGB_20    HQX_Interp2_RGB(W5R, W5G, W5B, W8R, W8G, W8B, W6R, W6G, W6B, R33, G33, B33);
    #define HQ4X_PIXEL33_RGB_50    HQX_Interp5_RGB(W8R, W8G, W8B, W6R, W6G, W6B, R33, G33, B33);
    #define HQ4X_PIXEL33_RGB_80    HQX_Interp8_RGB(W5R, W5G, W5B, W9R, W9G, W9B, R33, G33, B33);
    #define HQ4X_PIXEL33_RGB_81    HQX_Interp8_RGB(W5R, W5G, W5B, W6R, W6G, W6B, R33, G33, B33);
    #define HQ4X_PIXEL33_RGB_82    HQX_Interp8_RGB(W5R, W5G, W5B, W8R, W8G, W8B, R33, G33, B33);

    #define HQ2X_PIXEL00_0     C00 = W5;
    #define HQ2X_PIXEL00_10    C00 = HQX_Interp1(W5, W1);
    #define HQ2X_PIXEL00_11    C00 = HQX_Interp1(W5, W4);
    #define HQ2X_PIXEL00_12    C00 = HQX_Interp1(W5, W2);
    #define HQ2X_PIXEL00_20    C00 = HQX_Interp2(W5, W4, W2);
    #define HQ2X_PIXEL00_21    C00 = HQX_Interp2(W5, W1, W2);
    #define HQ2X_PIXEL00_22    C00 = HQX_Interp2(W5, W1, W4);
    #define HQ2X_PIXEL00_60    C00 = HQX_Interp6(W5, W2, W4);
    #define HQ2X_PIXEL00_61    C00 = HQX_Interp6(W5, W4, W2);
    #define HQ2X_PIXEL00_70    C00 = HQX_Interp7(W5, W4, W2);
    #define HQ2X_PIXEL00_90    C00 = HQX_Interp9(W5, W4, W2);
    #define HQ2X_PIXEL00_100   C00 = HQX_Interp10(W5, W4, W2);
    #define HQ2X_PIXEL01_0     C01 = W5;
    #define HQ2X_PIXEL01_10    C01 = HQX_Interp1(W5, W3);
    #define HQ2X_PIXEL01_11    C01 = HQX_Interp1(W5, W2);
    #define HQ2X_PIXEL01_12    C01 = HQX_Interp1(W5, W6);
    #define HQ2X_PIXEL01_20    C01 = HQX_Interp2(W5, W2, W6);
    #define HQ2X_PIXEL01_21    C01 = HQX_Interp2(W5, W3, W6);
    #define HQ2X_PIXEL01_22    C01 = HQX_Interp2(W5, W3, W2);
    #define HQ2X_PIXEL01_60    C01 = HQX_Interp6(W5, W6, W2);
    #define HQ2X_PIXEL01_61    C01 = HQX_Interp6(W5, W2, W6);
    #define HQ2X_PIXEL01_70    C01 = HQX_Interp7(W5, W2, W6);
    #define HQ2X_PIXEL01_90    C01 = HQX_Interp9(W5, W2, W6);
    #define HQ2X_PIXEL01_100   C01 = HQX_Interp10(W5, W2, W6);
    #define HQ2X_PIXEL10_0     C10 = W5;
    #define HQ2X_PIXEL10_10    C10 = HQX_Interp1(W5, W7);
    #define HQ2X_PIXEL10_11    C10 = HQX_Interp1(W5, W8);
    #define HQ2X_PIXEL10_12    C10 = HQX_Interp1(W5, W4);
    #define HQ2X_PIXEL10_20    C10 = HQX_Interp2(W5, W8, W4);
    #define HQ2X_PIXEL10_21    C10 = HQX_Interp2(W5, W7, W4);
    #define HQ2X_PIXEL10_22    C10 = HQX_Interp2(W5, W7, W8);
    #define HQ2X_PIXEL10_60    C10 = HQX_Interp6(W5, W4, W8);
    #define HQ2X_PIXEL10_61    C10 = HQX_Interp6(W5, W8, W4);
    #define HQ2X_PIXEL10_70    C10 = HQX_Interp7(W5, W8, W4);
    #define HQ2X_PIXEL10_90    C10 = HQX_Interp9(W5, W8, W4);
    #define HQ2X_PIXEL10_100   C10 = HQX_Interp10(W5, W8, W4);
    #define HQ2X_PIXEL11_0     C11 = W5;
    #define HQ2X_PIXEL11_10    C11 = HQX_Interp1(W5, W9);
    #define HQ2X_PIXEL11_11    C11 = HQX_Interp1(W5, W6);
    #define HQ2X_PIXEL11_12    C11 = HQX_Interp1(W5, W8);
    #define HQ2X_PIXEL11_20    C11 = HQX_Interp2(W5, W6, W8);
    #define HQ2X_PIXEL11_21    C11 = HQX_Interp2(W5, W9, W8);
    #define HQ2X_PIXEL11_22    C11 = HQX_Interp2(W5, W9, W6);
    #define HQ2X_PIXEL11_60    C11 = HQX_Interp6(W5, W8, W6);
    #define HQ2X_PIXEL11_61    C11 = HQX_Interp6(W5, W6, W8);
    #define HQ2X_PIXEL11_70    C11 = HQX_Interp7(W5, W6, W8);
    #define HQ2X_PIXEL11_90    C11 = HQX_Interp9(W5, W6, W8);
    #define HQ2X_PIXEL11_100   C11 = HQX_Interp10(W5, W6, W8);

    #define HQ3X_PIXEL00_1M    C00 = HQX_Interp1(W5, W1);
    #define HQ3X_PIXEL00_1U    C00 = HQX_Interp1(W5, W2);
    #define HQ3X_PIXEL00_1L    C00 = HQX_Interp1(W5, W4);
    #define HQ3X_PIXEL00_2     C00 = HQX_Interp2(W5, W4, W2);
    #define HQ3X_PIXEL00_4     C00 = HQX_Interp4(W5, W4, W2);
    #define HQ3X_PIXEL00_5     C00 = HQX_Interp5(W4, W2);
    #define HQ3X_PIXEL00_C     C00 = W5;
    #define HQ3X_PIXEL01_1     C01 = HQX_Interp1(W5, W2);
    #define HQ3X_PIXEL01_3     C01 = HQX_Interp3(W5, W2);
    #define HQ3X_PIXEL01_6     C01 = HQX_Interp1(W2, W5);
    #define HQ3X_PIXEL01_C     C01 = W5;
    #define HQ3X_PIXEL02_1M    C02 = HQX_Interp1(W5, W3);
    #define HQ3X_PIXEL02_1U    C02 = HQX_Interp1(W5, W2);
    #define HQ3X_PIXEL02_1R    C02 = HQX_Interp1(W5, W6);
    #define HQ3X_PIXEL02_2     C02 = HQX_Interp2(W5, W2, W6);
    #define HQ3X_PIXEL02_4     C02 = HQX_Interp4(W5, W2, W6);
    #define HQ3X_PIXEL02_5     C02 = HQX_Interp5(W2, W6);
    #define HQ3X_PIXEL02_C     C02 = W5;
    #define HQ3X_PIXEL10_1     C10 = HQX_Interp1(W5, W4);
    #define HQ3X_PIXEL10_3     C10 = HQX_Interp3(W5, W4);
    #define HQ3X_PIXEL10_6     C10 = HQX_Interp1(W4, W5);
    #define HQ3X_PIXEL10_C     C10 = W5;
    #define HQ3X_PIXEL11       C11 = W5;
    #define HQ3X_PIXEL12_1     C12 = HQX_Interp1(W5, W6);
    #define HQ3X_PIXEL12_3     C12 = HQX_Interp3(W5, W6);
    #define HQ3X_PIXEL12_6     C12 = HQX_Interp1(W6, W5);
    #define HQ3X_PIXEL12_C     C12 = W5;
    #define HQ3X_PIXEL20_1M    C20 = HQX_Interp1(W5, W7);
    #define HQ3X_PIXEL20_1D    C20 = HQX_Interp1(W5, W8);
    #define HQ3X_PIXEL20_1L    C20 = HQX_Interp1(W5, W4);
    #define HQ3X_PIXEL20_2     C20 = HQX_Interp2(W5, W8, W4);
    #define HQ3X_PIXEL20_4     C20 = HQX_Interp4(W5, W8, W4);
    #define HQ3X_PIXEL20_5     C20 = HQX_Interp5(W8, W4);
    #define HQ3X_PIXEL20_C     C20 = W5;
    #define HQ3X_PIXEL21_1     C21 = HQX_Interp1(W5, W8);
    #define HQ3X_PIXEL21_3     C21 = HQX_Interp3(W5, W8);
    #define HQ3X_PIXEL21_6     C21 = HQX_Interp1(W8, W5);
    #define HQ3X_PIXEL21_C     C21 = W5;
    #define HQ3X_PIXEL22_1M    C22 = HQX_Interp1(W5, W9);
    #define HQ3X_PIXEL22_1D    C22 = HQX_Interp1(W5, W8);
    #define HQ3X_PIXEL22_1R    C22 = HQX_Interp1(W5, W6);
    #define HQ3X_PIXEL22_2     C22 = HQX_Interp2(W5, W6, W8);
    #define HQ3X_PIXEL22_4     C22 = HQX_Interp4(W5, W6, W8);
    #define HQ3X_PIXEL22_5     C22 = HQX_Interp5(W6, W8);
    #define HQ3X_PIXEL22_C     C22 = W5;

    #define HQ4X_PIXEL00_0     C00 = W5;
    #define HQ4X_PIXEL00_11    C00 = HQX_Interp1(W5, W4);
    #define HQ4X_PIXEL00_12    C00 = HQX_Interp1(W5, W2);
    #define HQ4X_PIXEL00_20    C00 = HQX_Interp2(W5, W2, W4);
    #define HQ4X_PIXEL00_50    C00 = HQX_Interp5(W2, W4);
    #define HQ4X_PIXEL00_80    C00 = HQX_Interp8(W5, W1);
    #define HQ4X_PIXEL00_81    C00 = HQX_Interp8(W5, W4);
    #define HQ4X_PIXEL00_82    C00 = HQX_Interp8(W5, W2);
    #define HQ4X_PIXEL01_0     C01 = W5;
    #define HQ4X_PIXEL01_10    C01 = HQX_Interp1(W5, W1);
    #define HQ4X_PIXEL01_12    C01 = HQX_Interp1(W5, W2);
    #define HQ4X_PIXEL01_14    C01 = HQX_Interp1(W2, W5);
    #define HQ4X_PIXEL01_21    C01 = HQX_Interp2(W2, W5, W4);
    #define HQ4X_PIXEL01_31    C01 = HQX_Interp3(W5, W4);
    #define HQ4X_PIXEL01_50    C01 = HQX_Interp5(W2, W5);
    #define HQ4X_PIXEL01_60    C01 = HQX_Interp6(W5, W2, W4);
    #define HQ4X_PIXEL01_61    C01 = HQX_Interp6(W5, W2, W1);
    #define HQ4X_PIXEL01_82    C01 = HQX_Interp8(W5, W2);
    #define HQ4X_PIXEL01_83    C01 = HQX_Interp8(W2, W4);
    #define HQ4X_PIXEL02_0     C02 = W5;
    #define HQ4X_PIXEL02_10    C02 = HQX_Interp1(W5, W3);
    #define HQ4X_PIXEL02_11    C02 = HQX_Interp1(W5, W2);
    #define HQ4X_PIXEL02_13    C02 = HQX_Interp1(W2, W5);
    #define HQ4X_PIXEL02_21    C02 = HQX_Interp2(W2, W5, W6);
    #define HQ4X_PIXEL02_32    C02 = HQX_Interp3(W5, W6);
    #define HQ4X_PIXEL02_50    C02 = HQX_Interp5(W2, W5);
    #define HQ4X_PIXEL02_60    C02 = HQX_Interp6(W5, W2, W6);
    #define HQ4X_PIXEL02_61    C02 = HQX_Interp6(W5, W2, W3);
    #define HQ4X_PIXEL02_81    C02 = HQX_Interp8(W5, W2);
    #define HQ4X_PIXEL02_83    C02 = HQX_Interp8(W2, W6);
    #define HQ4X_PIXEL03_0     C03 = W5;
    #define HQ4X_PIXEL03_11    C03 = HQX_Interp1(W5, W2);
    #define HQ4X_PIXEL03_12    C03 = HQX_Interp1(W5, W6);
    #define HQ4X_PIXEL03_20    C03 = HQX_Interp2(W5, W2, W6);
    #define HQ4X_PIXEL03_50    C03 = HQX_Interp5(W2, W6);
    #define HQ4X_PIXEL03_80    C03 = HQX_Interp8(W5, W3);
    #define HQ4X_PIXEL03_81    C03 = HQX_Interp8(W5, W2);
    #define HQ4X_PIXEL03_82    C03 = HQX_Interp8(W5, W6);
    #define HQ4X_PIXEL10_0     C10 = W5;
    #define HQ4X_PIXEL10_10    C10 = HQX_Interp1(W5, W1);
    #define HQ4X_PIXEL10_11    C10 = HQX_Interp1(W5, W4);
    #define HQ4X_PIXEL10_13    C10 = HQX_Interp1(W4, W5);
    #define HQ4X_PIXEL10_21    C10 = HQX_Interp2(W4, W5, W2);
    #define HQ4X_PIXEL10_32    C10 = HQX_Interp3(W5, W2);
    #define HQ4X_PIXEL10_50    C10 = HQX_Interp5(W4, W5);
    #define HQ4X_PIXEL10_60    C10 = HQX_Interp6(W5, W4, W2);
    #define HQ4X_PIXEL10_61    C10 = HQX_Interp6(W5, W4, W1);
    #define HQ4X_PIXEL10_81    C10 = HQX_Interp8(W5, W4);
    #define HQ4X_PIXEL10_83    C10 = HQX_Interp8(W4, W2);
    #define HQ4X_PIXEL11_0     C11 = W5;
    #define HQ4X_PIXEL11_30    C11 = HQX_Interp3(W5, W1);
    #define HQ4X_PIXEL11_31    C11 = HQX_Interp3(W5, W4);
    #define HQ4X_PIXEL11_32    C11 = HQX_Interp3(W5, W2);
    #define HQ4X_PIXEL11_70    C11 = HQX_Interp7(W5, W4, W2);
    #define HQ4X_PIXEL12_0     C12 = W5;
    #define HQ4X_PIXEL12_30    C12 = HQX_Interp3(W5, W3);
    #define HQ4X_PIXEL12_31    C12 = HQX_Interp3(W5, W2);
    #define HQ4X_PIXEL12_32    C12 = HQX_Interp3(W5, W6);
    #define HQ4X_PIXEL12_70    C12 = HQX_Interp7(W5, W6, W2);
    #define HQ4X_PIXEL13_0     C13 = W5;
    #define HQ4X_PIXEL13_10    C13 = HQX_Interp1(W5, W3);
    #define HQ4X_PIXEL13_12    C13 = HQX_Interp1(W5, W6);
    #define HQ4X_PIXEL13_14    C13 = HQX_Interp1(W6, W5);
    #define HQ4X_PIXEL13_21    C13 = HQX_Interp2(W6, W5, W2);
    #define HQ4X_PIXEL13_31    C13 = HQX_Interp3(W5, W2);
    #define HQ4X_PIXEL13_50    C13 = HQX_Interp5(W6, W5);
    #define HQ4X_PIXEL13_60    C13 = HQX_Interp6(W5, W6, W2);
    #define HQ4X_PIXEL13_61    C13 = HQX_Interp6(W5, W6, W3);
    #define HQ4X_PIXEL13_82    C13 = HQX_Interp8(W5, W6);
    #define HQ4X_PIXEL13_83    C13 = HQX_Interp8(W6, W2);
    #define HQ4X_PIXEL20_0     C20 = W5;
    #define HQ4X_PIXEL20_10    C20 = HQX_Interp1(W5, W7);
    #define HQ4X_PIXEL20_12    C20 = HQX_Interp1(W5, W4);
    #define HQ4X_PIXEL20_14    C20 = HQX_Interp1(W4, W5);
    #define HQ4X_PIXEL20_21    C20 = HQX_Interp2(W4, W5, W8);
    #define HQ4X_PIXEL20_31    C20 = HQX_Interp3(W5, W8);
    #define HQ4X_PIXEL20_50    C20 = HQX_Interp5(W4, W5);
    #define HQ4X_PIXEL20_60    C20 = HQX_Interp6(W5, W4, W8);
    #define HQ4X_PIXEL20_61    C20 = HQX_Interp6(W5, W4, W7);
    #define HQ4X_PIXEL20_82    C20 = HQX_Interp8(W5, W4);
    #define HQ4X_PIXEL20_83    C20 = HQX_Interp8(W4, W8);
    #define HQ4X_PIXEL21_0     C21 = W5;
    #define HQ4X_PIXEL21_30    C21 = HQX_Interp3(W5, W7);
    #define HQ4X_PIXEL21_31    C21 = HQX_Interp3(W5, W8);
    #define HQ4X_PIXEL21_32    C21 = HQX_Interp3(W5, W4);
    #define HQ4X_PIXEL21_70    C21 = HQX_Interp7(W5, W4, W8);
    #define HQ4X_PIXEL22_0     C22 = W5;
    #define HQ4X_PIXEL22_30    C22 = HQX_Interp3(W5, W9);
    #define HQ4X_PIXEL22_31    C22 = HQX_Interp3(W5, W6);
    #define HQ4X_PIXEL22_32    C22 = HQX_Interp3(W5, W8);
    #define HQ4X_PIXEL22_70    C22 = HQX_Interp7(W5, W6, W8);
    #define HQ4X_PIXEL23_0     C23 = W5;
    #define HQ4X_PIXEL23_10    C23 = HQX_Interp1(W5, W9);
    #define HQ4X_PIXEL23_11    C23 = HQX_Interp1(W5, W6);
    #define HQ4X_PIXEL23_13    C23 = HQX_Interp1(W6, W5);
    #define HQ4X_PIXEL23_21    C23 = HQX_Interp2(W6, W5, W8);
    #define HQ4X_PIXEL23_32    C23 = HQX_Interp3(W5, W8);
    #define HQ4X_PIXEL23_50    C23 = HQX_Interp5(W6, W5);
    #define HQ4X_PIXEL23_60    C23 = HQX_Interp6(W5, W6, W8);
    #define HQ4X_PIXEL23_61    C23 = HQX_Interp6(W5, W6, W9);
    #define HQ4X_PIXEL23_81    C23 = HQX_Interp8(W5, W6);
    #define HQ4X_PIXEL23_83    C23 = HQX_Interp8(W6, W8);
    #define HQ4X_PIXEL30_0     C30 = W5;
    #define HQ4X_PIXEL30_11    C30 = HQX_Interp1(W5, W8);
    #define HQ4X_PIXEL30_12    C30 = HQX_Interp1(W5, W4);
    #define HQ4X_PIXEL30_20    C30 = HQX_Interp2(W5, W8, W4);
    #define HQ4X_PIXEL30_50    C30 = HQX_Interp5(W8, W4);
    #define HQ4X_PIXEL30_80    C30 = HQX_Interp8(W5, W7);
    #define HQ4X_PIXEL30_81    C30 = HQX_Interp8(W5, W8);
    #define HQ4X_PIXEL30_82    C30 = HQX_Interp8(W5, W4);
    #define HQ4X_PIXEL31_0     C31 = W5;
    #define HQ4X_PIXEL31_10    C31 = HQX_Interp1(W5, W7);
    #define HQ4X_PIXEL31_11    C31 = HQX_Interp1(W5, W8);
    #define HQ4X_PIXEL31_13    C31 = HQX_Interp1(W8, W5);
    #define HQ4X_PIXEL31_21    C31 = HQX_Interp2(W8, W5, W4);
    #define HQ4X_PIXEL31_32    C31 = HQX_Interp3(W5, W4);
    #define HQ4X_PIXEL31_50    C31 = HQX_Interp5(W8, W5);
    #define HQ4X_PIXEL31_60    C31 = HQX_Interp6(W5, W8, W4);
    #define HQ4X_PIXEL31_61    C31 = HQX_Interp6(W5, W8, W7);
    #define HQ4X_PIXEL31_81    C31 = HQX_Interp8(W5, W8);
    #define HQ4X_PIXEL31_83    C31 = HQX_Interp8(W8, W4);
    #define HQ4X_PIXEL32_0     C32 = W5;
    #define HQ4X_PIXEL32_10    C32 = HQX_Interp1(W5, W9);
    #define HQ4X_PIXEL32_12    C32 = HQX_Interp1(W5, W8);
    #define HQ4X_PIXEL32_14    C32 = HQX_Interp1(W8, W5);
    #define HQ4X_PIXEL32_21    C32 = HQX_Interp2(W8, W5, W6);
    #define HQ4X_PIXEL32_31    C32 = HQX_Interp3(W5, W6);
    #define HQ4X_PIXEL32_50    C32 = HQX_Interp5(W8, W5);
    #define HQ4X_PIXEL32_60    C32 = HQX_Interp6(W5, W8, W6);
    #define HQ4X_PIXEL32_61    C32 = HQX_Interp6(W5, W8, W9);
    #define HQ4X_PIXEL32_82    C32 = HQX_Interp8(W5, W8);
    #define HQ4X_PIXEL32_83    C32 = HQX_Interp8(W8, W6);
    #define HQ4X_PIXEL33_0     C33 = W5;
    #define HQ4X_PIXEL33_11    C33 = HQX_Interp1(W5, W6);
    #define HQ4X_PIXEL33_12    C33 = HQX_Interp1(W5, W8);
    #define HQ4X_PIXEL33_20    C33 = HQX_Interp2(W5, W8, W6);
    #define HQ4X_PIXEL33_50    C33 = HQX_Interp5(W8, W6);
    #define HQ4X_PIXEL33_80    C33 = HQX_Interp8(W5, W9);
    #define HQ4X_PIXEL33_81    C33 = HQX_Interp8(W5, W6);
    #define HQ4X_PIXEL33_82    C33 = HQX_Interp8(W5, W8);

    struct DelayLineAsyncThreadData
    {
    public:
        int Type;
        int Id;
        int Pos;
        QByteArray Data;
        QString Url;
    };

    queue<DelayLineAsyncThreadData> DelayLineAsyncThreadRequest;

    queue<DelayLineAsyncThreadData> DelayLineAsyncThreadResult;



private:
    int PicWMax, PicHMax, OpC, OpC1;

    QImage * BmpDisp;
    uchar * BmpDispRaw;
    int BmpDispW;
    int BmpDispH;

    vector<uint> PropCol1;
    vector<uint> PropCol2;
    vector<uint> PropVal1;
    vector<uint> PropVal2;
    vector<uint> PropResult;
    uint ColorProp(uint Col1, uint Col2, uint Val1, uint Val2);
    uint ColorProp(uint Col1, uint Col2, uint Col3, uint Val1, uint Val2, uint Val3);
    uint ColorProp(uint Col1, uint Col2, uint Col3, uint Col4, uint Val1, uint Val2, uint Val3, uint Val4);
    volatile bool Working;
    void ProcessPicture(int MinY, int MaxY, int P, int OpNr, int PipeI_);
    uchar ** BmpBuf = NULL;
    uint ** BmpBufIX_ = NULL;
    int BmpBufN = 0;
    int * BmpBufW = NULL;
    int * BmpBufH = NULL;
    int BmpBufIN = 0;
    int BmpBufIUnit = 0;
    int PicW;
    int PicH;
    int PicWDisp;
    int PicHDisp;
    int PicRawSizeDisp = 0;
    uchar * PicRawDummyDisp = NULL;
    //int PicWPtr;
    //int PicWPtrI;
    vector<int> OpType;
    vector<uchar*> OpMatrix;
    vector<uchar*> OpMatrixR;
    vector<uchar*> OpMatrixG;
    vector<uchar*> OpMatrixB;
    vector<vector<DitherMatrixElement>> OpMatrixDither;
    vector<int*> OpMatrixIR;
    vector<int*> OpMatrixIG;
    vector<int*> OpMatrixIB;
    void HQ2X_Process1(uchar * BmpBuf_, uchar * BmpBufX_, int MinY, int MaxY, int PicW_, int PicH_, int &P, int L);
    void HQ2X_Process2(uchar * BmpBuf_, uchar * BmpBufX_, int MinY, int MaxY, int PicW_, int PicH_, int &P, int L);
    void HQ3X_Process1(uchar * BmpBuf_, uchar * BmpBufX_, int MinY, int MaxY, int PicW_, int PicH_, int &P, int L);
    void HQ3X_Process2(uchar * BmpBuf_, uchar * BmpBufX_, int MinY, int MaxY, int PicW_, int PicH_, int &P, int L);
    void HQ4X_Process1(uchar * BmpBuf_, uchar * BmpBufX_, int MinY, int MaxY, int PicW_, int PicH_, int &P, int L);
    void HQ4X_Process2(uchar * BmpBuf_, uchar * BmpBufX_, int MinY, int MaxY, int PicW_, int PicH_, int &P, int L);

    void Convolution_Process(uchar * BmpBuf_, uchar * BmpBufX_, int MinY, int MaxY, int PicW_, int PicH_, int &P, int * OpMatrixIR_, int * OpMatrixIG_, int * OpMatrixIB_);
    void Convolution_Process_Gamma(uchar * BmpBuf_, uchar * BmpBufX_, int MinY, int MaxY, int PicW_, int PicH_, int &P, int * OpMatrixIR_, int * OpMatrixIG_, int * OpMatrixIB_);

    void GetColor(uchar * Bmp, int PicW__, int PicH__, int X, int Y, int TX, int TY, int &R, int &G, int &B, int &T);

    // Accuracy = 64
    // V = Accuracy / 2
    // 1 << B = Accuracy
    // M = Accuracy - 1
    #define InterpolationAccuracyV 32
    #define InterpolationAccuracyB 6
    #define InterpolationAccuracyM 63


    #define MaxThreadCount 16
    #define MaxThreadCountBit 4

    int * ThrMinY;
    int * ThrMaxY;
    int * ThrPicLines;
    int * ThrStartPtr;
    int * ThrLineDiv;
    uchar * ThrMultiThread;
    void DrawMousePointer(int PipeI, int PipeI_);
    void ProcessThread(int PipeI, int PipeI_);
    void ProcessThreadDummy();
    int MouseX_[MaxThreadCount];
    int MouseY_[MaxThreadCount];
    int PicX_[MaxThreadCount];
    int PicY_[MaxThreadCount];
    int PipeCount = 1;

    int DelayLineCount = 0;
    int DelayLinePos = 0;
    int DelayLinePointer = 0;
    int DelayLineChunkSize = 0;
    string DelayLineFileName = "";
    bool RecorderI1 = false;
    bool RecorderI2 = false;
    bool RecorderO1 = false;
    bool RecorderO2 = false;
    bool DelayLineI = false;
    bool DelayLineO = false;
    bool DelayLineFile = false;
    uchar * DelayLineBuf = NULL;
    fstream * DelayLineFileObj = NULL;
    int * DelayLineId = NULL;
    void DelayLinePrepare();
    void DelayLineProcess(uchar *Data);
    void DelayLineCleanUp();
    int DelayLineIdCounter = 0;

    int DelayLineAsyncDecimateI;
    int DelayLineAsyncDecimateC;

    struct DelayLineAsyncDef
    {
    public:
        int Id;
        int Pos;
        QImage RawImg;
        uchar * Raw;

    };
    vector<DelayLineAsyncDef> DelayLineAsyncList;
    void DelayLineAsyncBegin(int Pos, int Id);
    void DelayLineAsyncEnd();
    void DelayLineAsyncPaint(uchar *Raw);
    QTimer * Timeout;

    struct DelayLinePaintCmdDef
    {
        int Cmd;
        vector<int> Id;
        char Needed;
        QString PaintText;
        int PaintX1;
        int PaintY1;
        int PaintX2;
        int PaintY2;
        int * PointX1;
        int * PointX2;
        int * PointY1;
        int * PointY2;
        int PaintRot;
        int CmdId;
    };
    vector<DelayLinePaintCmdDef> DelayLinePaintCmdList;

    int DelayLinePaintCmdTextId;

    int DelayLinePaintCmdAdd(vector<int> Id, int Cmd, int X1, int Y1, int X2, int Y2, QString Text, int Rot, int *PointX1, int *PointX2, int *PointY1, int *PointY2);

    int DelayLineAsyncBitmapIdx(int Pos);
    void DelayLineAsyncBitmapFlush(int Idx);

    int * DelayLineAsyncBitmapMaskMinX = NULL;
    int * DelayLineAsyncBitmapMaskMinX_R = NULL;
    int * DelayLineAsyncBitmapMaskMinX_G = NULL;
    int * DelayLineAsyncBitmapMaskMinX_B = NULL;

    int * DelayLineAsyncBitmapMaskMinY = NULL;
    int * DelayLineAsyncBitmapMaskMinY_R = NULL;
    int * DelayLineAsyncBitmapMaskMinY_G = NULL;
    int * DelayLineAsyncBitmapMaskMinY_B = NULL;

    int * DelayLineAsyncBitmapMaskMaxX = NULL;
    int * DelayLineAsyncBitmapMaskMaxX_R = NULL;
    int * DelayLineAsyncBitmapMaskMaxX_G = NULL;
    int * DelayLineAsyncBitmapMaskMaxX_B = NULL;

    int * DelayLineAsyncBitmapMaskMaxY = NULL;
    int * DelayLineAsyncBitmapMaskMaxY_R = NULL;
    int * DelayLineAsyncBitmapMaskMaxY_G = NULL;
    int * DelayLineAsyncBitmapMaskMaxY_B = NULL;

    struct DelayLineAsyncTextObjDef
    {
    public:
        int ObjType;
        int X1;
        int Y1;
        int X2;
        int Y2;
        int X3;
        int Y3;
        int X4;
        int Y4;
        int MidX;
        int MidY;
        int MinX;
        int MaxX;
        int MinY;
        int MaxY;
        string ObjText;
        int BreakType;
        int TextState;
        int TextColor;
        int TextRotate;
    };

signals:
    void UpdatePixmap(QImage *Img);
    void PicSetRefresh();
    void RecorderInit();
    void TextCaptureFinish();

public slots:
};

#endif // PICTHREAD_H
