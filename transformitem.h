#ifndef TRANSFORMITEM_H
#define TRANSFORMITEM_H

#include "eden.h"
#include <iostream>
#include "settings.h"

using namespace std;

class TransformItem
{
public:
    Settings * Settings_;
    TransformItem(Settings *Settings__);
    bool TransEnabled = true;
    int TransType = 0;
    string GetInfo();
    string InfoDbVal(int Val);
    string InfoVal(int Val);
    string InfoWeight(int WR, int WG, int WB);

    int Trans0Type = 0;
    string Trans0File = "";
    bool Trans0Gamma = true;
    int Trans0BriR = 0;
    int Trans0BriG = 0;
    int Trans0BriB = 0;
    int Trans0ConR = 0;
    int Trans0ConG = 0;
    int Trans0ConB = 0;
    int Trans0InvR = 0;
    int Trans0InvG = 0;
    int Trans0InvB = 0;
    int Trans0GammaR = 0;
    int Trans0GammaG = 0;
    int Trans0GammaB = 0;

    int Trans1Type = 0;
    string Trans1File = "";
    bool Trans1Gamma = true;
    int Trans1Sat = 0;
    int Trans1Chan = 0;
    int Trans1YuvType = 0;
    int Trans1YuvWeightR = 299;
    int Trans1YuvWeightG = 587;
    int Trans1YuvWeightB = 114;
    int Trans1YuvLuma = 128;

    int Trans2Offset1R = 0;
    int Trans2Offset1G = 0;
    int Trans2Offset1B = 0;
    int Trans2GainR = 1;
    int Trans2GainG = 1;
    int Trans2GainB = 1;
    int Trans2Offset2R = 0;
    int Trans2Offset2G = 0;
    int Trans2Offset2B = 0;
    int Trans2Common = 0;
    bool Trans2Gamma = true;
    int Trans2MatrixR[29];
    int Trans2MatrixG[29];
    int Trans2MatrixB[29];

    vector<int> Trans3Prop;
    vector<int> Trans3Rot;
    vector<int> Trans3Matrix;
    int Trans3ItemCount = 0;
    int Trans3CurrentItem = 0;
    int Trans3CurrentProp1 = 0;
    int Trans3CurrentProp2 = 0;
    int Trans3CurrentProp3 = 0;
    int Trans3CurrentProp4 = 0;
    int Trans3CurrentRot0 = false;
    int Trans3CurrentRot1 = false;
    int Trans3CurrentRot2 = false;
    int Trans3CurrentRot3 = false;
    int Trans3CurrentMatrix[25];
    void Trans3CurrentSet();
    void Trans3CurrentGet();
    string Trans3CurrentInfo();
    void Trans3ItemAdd();
    void Trans3ItemRem();
    void Trans3ItemMovePrev();
    void Trans3ItemMoveNext();
    void Trans3ItemPrev();
    void Trans3ItemNext();

    int Trans4Type = 0;
    int Trans4Size = 0;
    int Trans4Size1W = 1;
    int Trans4Size1H = 1;
    int Trans4Size2W = 1;
    int Trans4Size2H = 1;
    int Trans4Scale = 0;
    bool Trans4Channels = false;
    int Trans4LcdType = 0;
    int Trans4LcdOp = 0;
    int Trans4LcdWeightR = 1;
    int Trans4LcdWeightG = 1;
    int Trans4LcdWeightB = 1;
    bool Trans4LcdInterpolation = false;

    int Trans5Rotate = 0;

    void FillLUT(uchar *LUT_R, uchar *LUT_G, uchar *LUT_B);
    void SaveLUT(string FileName, int Resolution);
    void FillConv(int *Conv_R, int *Conv_G, int *Conv_B);
    void Convert256To16M(uchar *LUT_R, uchar *LUT_G, uchar *LUT_B, uchar *LUT_R_, uchar *LUT_G_, uchar *LUT_B_);
    void Merge256(uchar *LUT_R, uchar *LUT_G, uchar *LUT_B, uchar *LUT_R_, uchar *LUT_G_, uchar *LUT_B_);
    void Merge16M(uchar *LUT_R, uchar *LUT_G, uchar *LUT_B, uchar *LUT_R_, uchar *LUT_G_, uchar *LUT_B_);

    double ValDecibel(int DB);
    ldouble ValDecibelL(int DB);

    int YUV_R;
    int YUV_G;
    int YUV_B;
    int YUV_L;
    int YUV_C_R;
    int YUV_C_G;
    int YUV_C_B;
    ldouble YUV_R_;
    ldouble YUV_G_;
    ldouble YUV_B_;
    ldouble YUV_L_;
    ldouble YUV_C_R_;
    ldouble YUV_C_G_;
    ldouble YUV_C_B_;

    ldouble YUV_RW, YUV_RW1;
    ldouble YUV_GW, YUV_GW1;
    ldouble YUV_BW, YUV_BW1;
    ldouble YUV_GW_RW;
    ldouble YUV_BW_RW;
    ldouble YUV_RW_GW;
    ldouble YUV_BW_GW;
    ldouble YUV_RW_BW;
    ldouble YUV_GW_BW;

    void RGB2YUV();
    void RGB2YUV_();
    void YUV2RGB();
    void YUV2RGB_R();
    void YUV2RGB_G();
    void YUV2RGB_B();
    void YUV2RGB_();
    void PrepareYUV();
    bool YUV16bit = false;

    static bool ReadVector(fstream &F, vector<string> &Vec, bool Loop);
    static int BinIntRead(uchar * Raw, int Pos);
    static void BinIntWrite(uchar * Raw, int Pos, int Val);


    int GammaLUT_I[256];
    int GammaLUT_O[70001];
    void GammaLUT();
    int GammaLUT_gamma = -1;
};

#endif // TRANSFORMITEM_H
