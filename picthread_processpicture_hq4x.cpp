#include "picthread.h"

void PicThread::HQ4X_Process1(uchar * BmpBuf_, uchar * BmpBufX_, int MinY, int MaxY, int PicW_, int PicH_, int &P, int L)
{
    int LL = L << 1;
    int LLL = LL + L;
    int X, Y;
    int XW, XE, YN, YS;
    int PicW_1 = PicW_ - 1;
    int PicH_1 = PicH_ - 1;
    int W1R, W1G, W1B, W2R, W2G, W2B, W3R, W3G, W3B;
    int W4R, W4G, W4B, W5R, W5G, W5B, W6R, W6G, W6B;
    int W7R, W7G, W7B, W8R, W8G, W8B, W9R, W9G, W9B;
    int PicP;
    for (Y = MinY; Y < MaxY; Y++)
    {
        YN = Max(Y - 1, 0);
        YS = Min(Y + 1, PicH_1);
        for (X = 0; X < PicW_; X++)
        {
            XW = Max(X - 1, 0);
            XE = Min(X + 1, PicW_1);

            PicP = ((YN * PicW_) + XW) << 2;
            W1R = BmpBuf_[PicP + 2];
            W1G = BmpBuf_[PicP + 1];
            W1B = BmpBuf_[PicP + 0];

            PicP = ((YN * PicW_) + X) << 2;
            W2R = BmpBuf_[PicP + 2];
            W2G = BmpBuf_[PicP + 1];
            W2B = BmpBuf_[PicP + 0];

            PicP = ((YN * PicW_) + XE) << 2;
            W3R = BmpBuf_[PicP + 2];
            W3G = BmpBuf_[PicP + 1];
            W3B = BmpBuf_[PicP + 0];

            PicP = ((Y * PicW_) + XW) << 2;
            W4R = BmpBuf_[PicP + 2];
            W4G = BmpBuf_[PicP + 1];
            W4B = BmpBuf_[PicP + 0];

            PicP = ((Y * PicW_) + X) << 2;
            W5R = BmpBuf_[PicP + 2];
            W5G = BmpBuf_[PicP + 1];
            W5B = BmpBuf_[PicP + 0];

            PicP = ((Y * PicW_) + XE) << 2;
            W6R = BmpBuf_[PicP + 2];
            W6G = BmpBuf_[PicP + 1];
            W6B = BmpBuf_[PicP + 0];

            PicP = ((YS * PicW_) + XW) << 2;
            W7R = BmpBuf_[PicP + 2];
            W7G = BmpBuf_[PicP + 1];
            W7B = BmpBuf_[PicP + 0];

            PicP = ((YS * PicW_) + X) << 2;
            W8R = BmpBuf_[PicP + 2];
            W8G = BmpBuf_[PicP + 1];
            W8B = BmpBuf_[PicP + 0];

            PicP = ((YS * PicW_) + XE) << 2;
            W9R = BmpBuf_[PicP + 2];
            W9G = BmpBuf_[PicP + 1];
            W9B = BmpBuf_[PicP + 0];

            int Pattern = 0;
            int YUV_ = HQX_RGB2YUV(W5R, W5G, W5B);
            if (HQX_Diff_YUV(YUV_, HQX_RGB2YUV(W1R, W1G, W1B))) { Pattern += 1; }
            if (HQX_Diff_YUV(YUV_, HQX_RGB2YUV(W2R, W2G, W2B))) { Pattern += 2; }
            if (HQX_Diff_YUV(YUV_, HQX_RGB2YUV(W3R, W3G, W3B))) { Pattern += 4; }
            if (HQX_Diff_YUV(YUV_, HQX_RGB2YUV(W4R, W4G, W4B))) { Pattern += 8; }
            if (HQX_Diff_YUV(YUV_, HQX_RGB2YUV(W6R, W6G, W6B))) { Pattern += 16; }
            if (HQX_Diff_YUV(YUV_, HQX_RGB2YUV(W7R, W7G, W7B))) { Pattern += 32; }
            if (HQX_Diff_YUV(YUV_, HQX_RGB2YUV(W8R, W8G, W8B))) { Pattern += 64; }
            if (HQX_Diff_YUV(YUV_, HQX_RGB2YUV(W9R, W9G, W9B))) { Pattern += 128; }

            int R00, G00, B00;
            int R01, G01, B01;
            int R02, G02, B02;
            int R03, G03, B03;
            int R10, G10, B10;
            int R11, G11, B11;
            int R12, G12, B12;
            int R13, G13, B13;
            int R20, G20, B20;
            int R21, G21, B21;
            int R22, G22, B22;
            int R23, G23, B23;
            int R30, G30, B30;
            int R31, G31, B31;
            int R32, G32, B32;
            int R33, G33, B33;

            switch (Pattern)
            {
                case 0:
                case 1:
                case 4:
                case 32:
                case 128:
                case 5:
                case 132:
                case 160:
                case 33:
                case 129:
                case 36:
                case 133:
                case 164:
                case 161:
                case 37:
                case 165:
                    {
                        HQ4X_PIXEL00_RGB_20
                        HQ4X_PIXEL01_RGB_60
                        HQ4X_PIXEL02_RGB_60
                        HQ4X_PIXEL03_RGB_20
                        HQ4X_PIXEL10_RGB_60
                        HQ4X_PIXEL11_RGB_70
                        HQ4X_PIXEL12_RGB_70
                        HQ4X_PIXEL13_RGB_60
                        HQ4X_PIXEL20_RGB_60
                        HQ4X_PIXEL21_RGB_70
                        HQ4X_PIXEL22_RGB_70
                        HQ4X_PIXEL23_RGB_60
                        HQ4X_PIXEL30_RGB_20
                        HQ4X_PIXEL31_RGB_60
                        HQ4X_PIXEL32_RGB_60
                        HQ4X_PIXEL33_RGB_20
                        break;
                    }
                case 2:
                case 34:
                case 130:
                case 162:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_61
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_61
                        HQ4X_PIXEL20_RGB_60
                        HQ4X_PIXEL21_RGB_70
                        HQ4X_PIXEL22_RGB_70
                        HQ4X_PIXEL23_RGB_60
                        HQ4X_PIXEL30_RGB_20
                        HQ4X_PIXEL31_RGB_60
                        HQ4X_PIXEL32_RGB_60
                        HQ4X_PIXEL33_RGB_20
                        break;
                    }
                case 16:
                case 17:
                case 48:
                case 49:
                    {
                        HQ4X_PIXEL00_RGB_20
                        HQ4X_PIXEL01_RGB_60
                        HQ4X_PIXEL02_RGB_61
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_60
                        HQ4X_PIXEL11_RGB_70
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL20_RGB_60
                        HQ4X_PIXEL21_RGB_70
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_20
                        HQ4X_PIXEL31_RGB_60
                        HQ4X_PIXEL32_RGB_61
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 64:
                case 65:
                case 68:
                case 69:
                    {
                        HQ4X_PIXEL00_RGB_20
                        HQ4X_PIXEL01_RGB_60
                        HQ4X_PIXEL02_RGB_60
                        HQ4X_PIXEL03_RGB_20
                        HQ4X_PIXEL10_RGB_60
                        HQ4X_PIXEL11_RGB_70
                        HQ4X_PIXEL12_RGB_70
                        HQ4X_PIXEL13_RGB_60
                        HQ4X_PIXEL20_RGB_61
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_61
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 8:
                case 12:
                case 136:
                case 140:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_61
                        HQ4X_PIXEL02_RGB_60
                        HQ4X_PIXEL03_RGB_20
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_70
                        HQ4X_PIXEL13_RGB_60
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_70
                        HQ4X_PIXEL23_RGB_60
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_61
                        HQ4X_PIXEL32_RGB_60
                        HQ4X_PIXEL33_RGB_20
                        break;
                    }
                case 3:
                case 35:
                case 131:
                case 163:
                    {
                        HQ4X_PIXEL00_RGB_81
                        HQ4X_PIXEL01_RGB_31
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_81
                        HQ4X_PIXEL11_RGB_31
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_61
                        HQ4X_PIXEL20_RGB_60
                        HQ4X_PIXEL21_RGB_70
                        HQ4X_PIXEL22_RGB_70
                        HQ4X_PIXEL23_RGB_60
                        HQ4X_PIXEL30_RGB_20
                        HQ4X_PIXEL31_RGB_60
                        HQ4X_PIXEL32_RGB_60
                        HQ4X_PIXEL33_RGB_20
                        break;
                    }
                case 6:
                case 38:
                case 134:
                case 166:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        HQ4X_PIXEL02_RGB_32
                        HQ4X_PIXEL03_RGB_82
                        HQ4X_PIXEL10_RGB_61
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_32
                        HQ4X_PIXEL13_RGB_82
                        HQ4X_PIXEL20_RGB_60
                        HQ4X_PIXEL21_RGB_70
                        HQ4X_PIXEL22_RGB_70
                        HQ4X_PIXEL23_RGB_60
                        HQ4X_PIXEL30_RGB_20
                        HQ4X_PIXEL31_RGB_60
                        HQ4X_PIXEL32_RGB_60
                        HQ4X_PIXEL33_RGB_20
                        break;
                    }
                case 20:
                case 21:
                case 52:
                case 53:
                    {
                        HQ4X_PIXEL00_RGB_20
                        HQ4X_PIXEL01_RGB_60
                        HQ4X_PIXEL02_RGB_81
                        HQ4X_PIXEL03_RGB_81
                        HQ4X_PIXEL10_RGB_60
                        HQ4X_PIXEL11_RGB_70
                        HQ4X_PIXEL12_RGB_31
                        HQ4X_PIXEL13_RGB_31
                        HQ4X_PIXEL20_RGB_60
                        HQ4X_PIXEL21_RGB_70
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_20
                        HQ4X_PIXEL31_RGB_60
                        HQ4X_PIXEL32_RGB_61
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 144:
                case 145:
                case 176:
                case 177:
                    {
                        HQ4X_PIXEL00_RGB_20
                        HQ4X_PIXEL01_RGB_60
                        HQ4X_PIXEL02_RGB_61
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_60
                        HQ4X_PIXEL11_RGB_70
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL20_RGB_60
                        HQ4X_PIXEL21_RGB_70
                        HQ4X_PIXEL22_RGB_32
                        HQ4X_PIXEL23_RGB_32
                        HQ4X_PIXEL30_RGB_20
                        HQ4X_PIXEL31_RGB_60
                        HQ4X_PIXEL32_RGB_82
                        HQ4X_PIXEL33_RGB_82
                        break;
                    }
                case 192:
                case 193:
                case 196:
                case 197:
                    {
                        HQ4X_PIXEL00_RGB_20
                        HQ4X_PIXEL01_RGB_60
                        HQ4X_PIXEL02_RGB_60
                        HQ4X_PIXEL03_RGB_20
                        HQ4X_PIXEL10_RGB_60
                        HQ4X_PIXEL11_RGB_70
                        HQ4X_PIXEL12_RGB_70
                        HQ4X_PIXEL13_RGB_60
                        HQ4X_PIXEL20_RGB_61
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_31
                        HQ4X_PIXEL23_RGB_81
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        HQ4X_PIXEL32_RGB_31
                        HQ4X_PIXEL33_RGB_81
                        break;
                    }
                case 96:
                case 97:
                case 100:
                case 101:
                    {
                        HQ4X_PIXEL00_RGB_20
                        HQ4X_PIXEL01_RGB_60
                        HQ4X_PIXEL02_RGB_60
                        HQ4X_PIXEL03_RGB_20
                        HQ4X_PIXEL10_RGB_60
                        HQ4X_PIXEL11_RGB_70
                        HQ4X_PIXEL12_RGB_70
                        HQ4X_PIXEL13_RGB_60
                        HQ4X_PIXEL20_RGB_82
                        HQ4X_PIXEL21_RGB_32
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_61
                        HQ4X_PIXEL30_RGB_82
                        HQ4X_PIXEL31_RGB_32
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 40:
                case 44:
                case 168:
                case 172:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_61
                        HQ4X_PIXEL02_RGB_60
                        HQ4X_PIXEL03_RGB_20
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_70
                        HQ4X_PIXEL13_RGB_60
                        HQ4X_PIXEL20_RGB_31
                        HQ4X_PIXEL21_RGB_31
                        HQ4X_PIXEL22_RGB_70
                        HQ4X_PIXEL23_RGB_60
                        HQ4X_PIXEL30_RGB_81
                        HQ4X_PIXEL31_RGB_81
                        HQ4X_PIXEL32_RGB_60
                        HQ4X_PIXEL33_RGB_20
                        break;
                    }
                case 9:
                case 13:
                case 137:
                case 141:
                    {
                        HQ4X_PIXEL00_RGB_82
                        HQ4X_PIXEL01_RGB_82
                        HQ4X_PIXEL02_RGB_60
                        HQ4X_PIXEL03_RGB_20
                        HQ4X_PIXEL10_RGB_32
                        HQ4X_PIXEL11_RGB_32
                        HQ4X_PIXEL12_RGB_70
                        HQ4X_PIXEL13_RGB_60
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_70
                        HQ4X_PIXEL23_RGB_60
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_61
                        HQ4X_PIXEL32_RGB_60
                        HQ4X_PIXEL33_RGB_20
                        break;
                    }
                case 18:
                case 50:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_10
                            HQ4X_PIXEL03_RGB_80
                            HQ4X_PIXEL12_RGB_30
                            HQ4X_PIXEL13_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_50
                            HQ4X_PIXEL03_RGB_50
                            HQ4X_PIXEL12_RGB_0
                            HQ4X_PIXEL13_RGB_50
                        }
                        HQ4X_PIXEL10_RGB_61
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL20_RGB_60
                        HQ4X_PIXEL21_RGB_70
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_20
                        HQ4X_PIXEL31_RGB_60
                        HQ4X_PIXEL32_RGB_61
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 80:
                case 81:
                    {
                        HQ4X_PIXEL00_RGB_20
                        HQ4X_PIXEL01_RGB_60
                        HQ4X_PIXEL02_RGB_61
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_60
                        HQ4X_PIXEL11_RGB_70
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL20_RGB_61
                        HQ4X_PIXEL21_RGB_30
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL22_RGB_30
                            HQ4X_PIXEL23_RGB_10
                            HQ4X_PIXEL32_RGB_10
                            HQ4X_PIXEL33_RGB_80
                        }
                        else
                        {
                            HQ4X_PIXEL22_RGB_0
                            HQ4X_PIXEL23_RGB_50
                            HQ4X_PIXEL32_RGB_50
                            HQ4X_PIXEL33_RGB_50
                        }
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        break;
                    }
                case 72:
                case 76:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_61
                        HQ4X_PIXEL02_RGB_60
                        HQ4X_PIXEL03_RGB_20
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_70
                        HQ4X_PIXEL13_RGB_60
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_10
                            HQ4X_PIXEL21_RGB_30
                            HQ4X_PIXEL30_RGB_80
                            HQ4X_PIXEL31_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_50
                            HQ4X_PIXEL21_RGB_0
                            HQ4X_PIXEL30_RGB_50
                            HQ4X_PIXEL31_RGB_50
                        }
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_61
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 10:
                case 138:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_80
                            HQ4X_PIXEL01_RGB_10
                            HQ4X_PIXEL10_RGB_10
                            HQ4X_PIXEL11_RGB_30
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_50
                            HQ4X_PIXEL01_RGB_50
                            HQ4X_PIXEL10_RGB_50
                            HQ4X_PIXEL11_RGB_0
                        }
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_61
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_70
                        HQ4X_PIXEL23_RGB_60
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_61
                        HQ4X_PIXEL32_RGB_60
                        HQ4X_PIXEL33_RGB_20
                        break;
                    }
                case 66:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_61
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_61
                        HQ4X_PIXEL20_RGB_61
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_61
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 24:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_61
                        HQ4X_PIXEL02_RGB_61
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_61
                        HQ4X_PIXEL32_RGB_61
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 7:
                case 39:
                case 135:
                    {
                        HQ4X_PIXEL00_RGB_81
                        HQ4X_PIXEL01_RGB_31
                        HQ4X_PIXEL02_RGB_32
                        HQ4X_PIXEL03_RGB_82
                        HQ4X_PIXEL10_RGB_81
                        HQ4X_PIXEL11_RGB_31
                        HQ4X_PIXEL12_RGB_32
                        HQ4X_PIXEL13_RGB_82
                        HQ4X_PIXEL20_RGB_60
                        HQ4X_PIXEL21_RGB_70
                        HQ4X_PIXEL22_RGB_70
                        HQ4X_PIXEL23_RGB_60
                        HQ4X_PIXEL30_RGB_20
                        HQ4X_PIXEL31_RGB_60
                        HQ4X_PIXEL32_RGB_60
                        HQ4X_PIXEL33_RGB_20
                        break;
                    }
                case 148:
                case 149:
                case 180:
                    {
                        HQ4X_PIXEL00_RGB_20
                        HQ4X_PIXEL01_RGB_60
                        HQ4X_PIXEL02_RGB_81
                        HQ4X_PIXEL03_RGB_81
                        HQ4X_PIXEL10_RGB_60
                        HQ4X_PIXEL11_RGB_70
                        HQ4X_PIXEL12_RGB_31
                        HQ4X_PIXEL13_RGB_31
                        HQ4X_PIXEL20_RGB_60
                        HQ4X_PIXEL21_RGB_70
                        HQ4X_PIXEL22_RGB_32
                        HQ4X_PIXEL23_RGB_32
                        HQ4X_PIXEL30_RGB_20
                        HQ4X_PIXEL31_RGB_60
                        HQ4X_PIXEL32_RGB_82
                        HQ4X_PIXEL33_RGB_82
                        break;
                    }
                case 224:
                case 228:
                case 225:
                    {
                        HQ4X_PIXEL00_RGB_20
                        HQ4X_PIXEL01_RGB_60
                        HQ4X_PIXEL02_RGB_60
                        HQ4X_PIXEL03_RGB_20
                        HQ4X_PIXEL10_RGB_60
                        HQ4X_PIXEL11_RGB_70
                        HQ4X_PIXEL12_RGB_70
                        HQ4X_PIXEL13_RGB_60
                        HQ4X_PIXEL20_RGB_82
                        HQ4X_PIXEL21_RGB_32
                        HQ4X_PIXEL22_RGB_31
                        HQ4X_PIXEL23_RGB_81
                        HQ4X_PIXEL30_RGB_82
                        HQ4X_PIXEL31_RGB_32
                        HQ4X_PIXEL32_RGB_31
                        HQ4X_PIXEL33_RGB_81
                        break;
                    }
                case 41:
                case 169:
                case 45:
                    {
                        HQ4X_PIXEL00_RGB_82
                        HQ4X_PIXEL01_RGB_82
                        HQ4X_PIXEL02_RGB_60
                        HQ4X_PIXEL03_RGB_20
                        HQ4X_PIXEL10_RGB_32
                        HQ4X_PIXEL11_RGB_32
                        HQ4X_PIXEL12_RGB_70
                        HQ4X_PIXEL13_RGB_60
                        HQ4X_PIXEL20_RGB_31
                        HQ4X_PIXEL21_RGB_31
                        HQ4X_PIXEL22_RGB_70
                        HQ4X_PIXEL23_RGB_60
                        HQ4X_PIXEL30_RGB_81
                        HQ4X_PIXEL31_RGB_81
                        HQ4X_PIXEL32_RGB_60
                        HQ4X_PIXEL33_RGB_20
                        break;
                    }
                case 22:
                case 54:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_0
                            HQ4X_PIXEL03_RGB_0
                            HQ4X_PIXEL13_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_50
                            HQ4X_PIXEL03_RGB_50
                            HQ4X_PIXEL13_RGB_50
                        }
                        HQ4X_PIXEL10_RGB_61
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_0
                        HQ4X_PIXEL20_RGB_60
                        HQ4X_PIXEL21_RGB_70
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_20
                        HQ4X_PIXEL31_RGB_60
                        HQ4X_PIXEL32_RGB_61
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 208:
                case 209:
                    {
                        HQ4X_PIXEL00_RGB_20
                        HQ4X_PIXEL01_RGB_60
                        HQ4X_PIXEL02_RGB_61
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_60
                        HQ4X_PIXEL11_RGB_70
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL20_RGB_61
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL23_RGB_0
                            HQ4X_PIXEL32_RGB_0
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL23_RGB_50
                            HQ4X_PIXEL32_RGB_50
                            HQ4X_PIXEL33_RGB_50
                        }
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        break;
                    }
                case 104:
                case 108:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_61
                        HQ4X_PIXEL02_RGB_60
                        HQ4X_PIXEL03_RGB_20
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_70
                        HQ4X_PIXEL13_RGB_60
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_0
                            HQ4X_PIXEL30_RGB_0
                            HQ4X_PIXEL31_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_50
                            HQ4X_PIXEL30_RGB_50
                            HQ4X_PIXEL31_RGB_50
                        }
                        HQ4X_PIXEL21_RGB_0
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_61
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 11:
                case 139:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                            HQ4X_PIXEL01_RGB_0
                            HQ4X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_50
                            HQ4X_PIXEL01_RGB_50
                            HQ4X_PIXEL10_RGB_50
                        }
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL11_RGB_0
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_61
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_70
                        HQ4X_PIXEL23_RGB_60
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_61
                        HQ4X_PIXEL32_RGB_60
                        HQ4X_PIXEL33_RGB_20
                        break;
                    }
                case 19:
                case 51:
                    {
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL00_RGB_81
                            HQ4X_PIXEL01_RGB_31
                            HQ4X_PIXEL02_RGB_10
                            HQ4X_PIXEL03_RGB_80
                            HQ4X_PIXEL12_RGB_30
                            HQ4X_PIXEL13_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_12
                            HQ4X_PIXEL01_RGB_14
                            HQ4X_PIXEL02_RGB_83
                            HQ4X_PIXEL03_RGB_50
                            HQ4X_PIXEL12_RGB_70
                            HQ4X_PIXEL13_RGB_21
                        }
                        HQ4X_PIXEL10_RGB_81
                        HQ4X_PIXEL11_RGB_31
                        HQ4X_PIXEL20_RGB_60
                        HQ4X_PIXEL21_RGB_70
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_20
                        HQ4X_PIXEL31_RGB_60
                        HQ4X_PIXEL32_RGB_61
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 146:
                case 178:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_10
                            HQ4X_PIXEL03_RGB_80
                            HQ4X_PIXEL12_RGB_30
                            HQ4X_PIXEL13_RGB_10
                            HQ4X_PIXEL23_RGB_32
                            HQ4X_PIXEL33_RGB_82
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_21
                            HQ4X_PIXEL03_RGB_50
                            HQ4X_PIXEL12_RGB_70
                            HQ4X_PIXEL13_RGB_83
                            HQ4X_PIXEL23_RGB_13
                            HQ4X_PIXEL33_RGB_11
                        }
                        HQ4X_PIXEL10_RGB_61
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL20_RGB_60
                        HQ4X_PIXEL21_RGB_70
                        HQ4X_PIXEL22_RGB_32
                        HQ4X_PIXEL30_RGB_20
                        HQ4X_PIXEL31_RGB_60
                        HQ4X_PIXEL32_RGB_82
                        break;
                    }
                case 84:
                case 85:
                    {
                        HQ4X_PIXEL00_RGB_20
                        HQ4X_PIXEL01_RGB_60
                        HQ4X_PIXEL02_RGB_81
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL03_RGB_81
                            HQ4X_PIXEL13_RGB_31
                            HQ4X_PIXEL22_RGB_30
                            HQ4X_PIXEL23_RGB_10
                            HQ4X_PIXEL32_RGB_10
                            HQ4X_PIXEL33_RGB_80
                        }
                        else
                        {
                            HQ4X_PIXEL03_RGB_12
                            HQ4X_PIXEL13_RGB_14
                            HQ4X_PIXEL22_RGB_70
                            HQ4X_PIXEL23_RGB_83
                            HQ4X_PIXEL32_RGB_21
                            HQ4X_PIXEL33_RGB_50
                        }
                        HQ4X_PIXEL10_RGB_60
                        HQ4X_PIXEL11_RGB_70
                        HQ4X_PIXEL12_RGB_31
                        HQ4X_PIXEL20_RGB_61
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        break;
                    }
                case 112:
                case 113:
                    {
                        HQ4X_PIXEL00_RGB_20
                        HQ4X_PIXEL01_RGB_60
                        HQ4X_PIXEL02_RGB_61
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_60
                        HQ4X_PIXEL11_RGB_70
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL20_RGB_82
                        HQ4X_PIXEL21_RGB_32
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL22_RGB_30
                            HQ4X_PIXEL23_RGB_10
                            HQ4X_PIXEL30_RGB_82
                            HQ4X_PIXEL31_RGB_32
                            HQ4X_PIXEL32_RGB_10
                            HQ4X_PIXEL33_RGB_80
                        }
                        else
                        {
                            HQ4X_PIXEL22_RGB_70
                            HQ4X_PIXEL23_RGB_21
                            HQ4X_PIXEL30_RGB_11
                            HQ4X_PIXEL31_RGB_13
                            HQ4X_PIXEL32_RGB_83
                            HQ4X_PIXEL33_RGB_50
                        }
                        break;
                    }
                case 200:
                case 204:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_61
                        HQ4X_PIXEL02_RGB_60
                        HQ4X_PIXEL03_RGB_20
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_70
                        HQ4X_PIXEL13_RGB_60
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_10
                            HQ4X_PIXEL21_RGB_30
                            HQ4X_PIXEL30_RGB_80
                            HQ4X_PIXEL31_RGB_10
                            HQ4X_PIXEL32_RGB_31
                            HQ4X_PIXEL33_RGB_81
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_21
                            HQ4X_PIXEL21_RGB_70
                            HQ4X_PIXEL30_RGB_50
                            HQ4X_PIXEL31_RGB_83
                            HQ4X_PIXEL32_RGB_14
                            HQ4X_PIXEL33_RGB_12
                        }
                        HQ4X_PIXEL22_RGB_31
                        HQ4X_PIXEL23_RGB_81
                        break;
                    }
                case 73:
                case 77:
                    {
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL00_RGB_82
                            HQ4X_PIXEL10_RGB_32
                            HQ4X_PIXEL20_RGB_10
                            HQ4X_PIXEL21_RGB_30
                            HQ4X_PIXEL30_RGB_80
                            HQ4X_PIXEL31_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_11
                            HQ4X_PIXEL10_RGB_13
                            HQ4X_PIXEL20_RGB_83
                            HQ4X_PIXEL21_RGB_70
                            HQ4X_PIXEL30_RGB_50
                            HQ4X_PIXEL31_RGB_21
                        }
                        HQ4X_PIXEL01_RGB_82
                        HQ4X_PIXEL02_RGB_60
                        HQ4X_PIXEL03_RGB_20
                        HQ4X_PIXEL11_RGB_32
                        HQ4X_PIXEL12_RGB_70
                        HQ4X_PIXEL13_RGB_60
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_61
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 42:
                case 170:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_80
                            HQ4X_PIXEL01_RGB_10
                            HQ4X_PIXEL10_RGB_10
                            HQ4X_PIXEL11_RGB_30
                            HQ4X_PIXEL20_RGB_31
                            HQ4X_PIXEL30_RGB_81
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_50
                            HQ4X_PIXEL01_RGB_21
                            HQ4X_PIXEL10_RGB_83
                            HQ4X_PIXEL11_RGB_70
                            HQ4X_PIXEL20_RGB_14
                            HQ4X_PIXEL30_RGB_12
                        }
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_61
                        HQ4X_PIXEL21_RGB_31
                        HQ4X_PIXEL22_RGB_70
                        HQ4X_PIXEL23_RGB_60
                        HQ4X_PIXEL31_RGB_81
                        HQ4X_PIXEL32_RGB_60
                        HQ4X_PIXEL33_RGB_20
                        break;
                    }
                case 14:
                case 142:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_80
                            HQ4X_PIXEL01_RGB_10
                            HQ4X_PIXEL02_RGB_32
                            HQ4X_PIXEL03_RGB_82
                            HQ4X_PIXEL10_RGB_10
                            HQ4X_PIXEL11_RGB_30
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_50
                            HQ4X_PIXEL01_RGB_83
                            HQ4X_PIXEL02_RGB_13
                            HQ4X_PIXEL03_RGB_11
                            HQ4X_PIXEL10_RGB_21
                            HQ4X_PIXEL11_RGB_70
                        }
                        HQ4X_PIXEL12_RGB_32
                        HQ4X_PIXEL13_RGB_82
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_70
                        HQ4X_PIXEL23_RGB_60
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_61
                        HQ4X_PIXEL32_RGB_60
                        HQ4X_PIXEL33_RGB_20
                        break;
                    }
                case 67:
                    {
                        HQ4X_PIXEL00_RGB_81
                        HQ4X_PIXEL01_RGB_31
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_81
                        HQ4X_PIXEL11_RGB_31
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_61
                        HQ4X_PIXEL20_RGB_61
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_61
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 70:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        HQ4X_PIXEL02_RGB_32
                        HQ4X_PIXEL03_RGB_82
                        HQ4X_PIXEL10_RGB_61
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_32
                        HQ4X_PIXEL13_RGB_82
                        HQ4X_PIXEL20_RGB_61
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_61
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 28:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_61
                        HQ4X_PIXEL02_RGB_81
                        HQ4X_PIXEL03_RGB_81
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_31
                        HQ4X_PIXEL13_RGB_31
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_61
                        HQ4X_PIXEL32_RGB_61
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 152:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_61
                        HQ4X_PIXEL02_RGB_61
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_32
                        HQ4X_PIXEL23_RGB_32
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_61
                        HQ4X_PIXEL32_RGB_82
                        HQ4X_PIXEL33_RGB_82
                        break;
                    }
                case 194:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_61
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_61
                        HQ4X_PIXEL20_RGB_61
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_31
                        HQ4X_PIXEL23_RGB_81
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        HQ4X_PIXEL32_RGB_31
                        HQ4X_PIXEL33_RGB_81
                        break;
                    }
                case 98:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_61
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_61
                        HQ4X_PIXEL20_RGB_82
                        HQ4X_PIXEL21_RGB_32
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_61
                        HQ4X_PIXEL30_RGB_82
                        HQ4X_PIXEL31_RGB_32
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 56:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_61
                        HQ4X_PIXEL02_RGB_61
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL20_RGB_31
                        HQ4X_PIXEL21_RGB_31
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_81
                        HQ4X_PIXEL31_RGB_81
                        HQ4X_PIXEL32_RGB_61
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 25:
                    {
                        HQ4X_PIXEL00_RGB_82
                        HQ4X_PIXEL01_RGB_82
                        HQ4X_PIXEL02_RGB_61
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_32
                        HQ4X_PIXEL11_RGB_32
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_61
                        HQ4X_PIXEL32_RGB_61
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 26:
                case 31:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                            HQ4X_PIXEL01_RGB_0
                            HQ4X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_50
                            HQ4X_PIXEL01_RGB_50
                            HQ4X_PIXEL10_RGB_50
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_0
                            HQ4X_PIXEL03_RGB_0
                            HQ4X_PIXEL13_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_50
                            HQ4X_PIXEL03_RGB_50
                            HQ4X_PIXEL13_RGB_50
                        }
                        HQ4X_PIXEL11_RGB_0
                        HQ4X_PIXEL12_RGB_0
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_61
                        HQ4X_PIXEL32_RGB_61
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 82:
                case 214:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_0
                            HQ4X_PIXEL03_RGB_0
                            HQ4X_PIXEL13_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_50
                            HQ4X_PIXEL03_RGB_50
                            HQ4X_PIXEL13_RGB_50
                        }
                        HQ4X_PIXEL10_RGB_61
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_0
                        HQ4X_PIXEL20_RGB_61
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL23_RGB_0
                            HQ4X_PIXEL32_RGB_0
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL23_RGB_50
                            HQ4X_PIXEL32_RGB_50
                            HQ4X_PIXEL33_RGB_50
                        }
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        break;
                    }
                case 88:
                case 248:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_61
                        HQ4X_PIXEL02_RGB_61
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_0
                            HQ4X_PIXEL30_RGB_0
                            HQ4X_PIXEL31_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_50
                            HQ4X_PIXEL30_RGB_50
                            HQ4X_PIXEL31_RGB_50
                        }
                        HQ4X_PIXEL21_RGB_0
                        HQ4X_PIXEL22_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL23_RGB_0
                            HQ4X_PIXEL32_RGB_0
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL23_RGB_50
                            HQ4X_PIXEL32_RGB_50
                            HQ4X_PIXEL33_RGB_50
                        }
                        break;
                    }
                case 74:
                case 107:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                            HQ4X_PIXEL01_RGB_0
                            HQ4X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_50
                            HQ4X_PIXEL01_RGB_50
                            HQ4X_PIXEL10_RGB_50
                        }
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL11_RGB_0
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_61
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_0
                            HQ4X_PIXEL30_RGB_0
                            HQ4X_PIXEL31_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_50
                            HQ4X_PIXEL30_RGB_50
                            HQ4X_PIXEL31_RGB_50
                        }
                        HQ4X_PIXEL21_RGB_0
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_61
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 27:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                            HQ4X_PIXEL01_RGB_0
                            HQ4X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_50
                            HQ4X_PIXEL01_RGB_50
                            HQ4X_PIXEL10_RGB_50
                        }
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL11_RGB_0
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_61
                        HQ4X_PIXEL32_RGB_61
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 86:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_0
                            HQ4X_PIXEL03_RGB_0
                            HQ4X_PIXEL13_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_50
                            HQ4X_PIXEL03_RGB_50
                            HQ4X_PIXEL13_RGB_50
                        }
                        HQ4X_PIXEL10_RGB_61
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_0
                        HQ4X_PIXEL20_RGB_61
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 216:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_61
                        HQ4X_PIXEL02_RGB_61
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL23_RGB_0
                            HQ4X_PIXEL32_RGB_0
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL23_RGB_50
                            HQ4X_PIXEL32_RGB_50
                            HQ4X_PIXEL33_RGB_50
                        }
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        break;
                    }
                case 106:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_61
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_0
                            HQ4X_PIXEL30_RGB_0
                            HQ4X_PIXEL31_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_50
                            HQ4X_PIXEL30_RGB_50
                            HQ4X_PIXEL31_RGB_50
                        }
                        HQ4X_PIXEL21_RGB_0
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_61
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 30:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_0
                            HQ4X_PIXEL03_RGB_0
                            HQ4X_PIXEL13_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_50
                            HQ4X_PIXEL03_RGB_50
                            HQ4X_PIXEL13_RGB_50
                        }
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_0
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_61
                        HQ4X_PIXEL32_RGB_61
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 210:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_61
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL20_RGB_61
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL23_RGB_0
                            HQ4X_PIXEL32_RGB_0
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL23_RGB_50
                            HQ4X_PIXEL32_RGB_50
                            HQ4X_PIXEL33_RGB_50
                        }
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        break;
                    }
                case 120:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_61
                        HQ4X_PIXEL02_RGB_61
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_0
                            HQ4X_PIXEL30_RGB_0
                            HQ4X_PIXEL31_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_50
                            HQ4X_PIXEL30_RGB_50
                            HQ4X_PIXEL31_RGB_50
                        }
                        HQ4X_PIXEL21_RGB_0
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 75:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                            HQ4X_PIXEL01_RGB_0
                            HQ4X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_50
                            HQ4X_PIXEL01_RGB_50
                            HQ4X_PIXEL10_RGB_50
                        }
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL11_RGB_0
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_61
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_61
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 29:
                    {
                        HQ4X_PIXEL00_RGB_82
                        HQ4X_PIXEL01_RGB_82
                        HQ4X_PIXEL02_RGB_81
                        HQ4X_PIXEL03_RGB_81
                        HQ4X_PIXEL10_RGB_32
                        HQ4X_PIXEL11_RGB_32
                        HQ4X_PIXEL12_RGB_31
                        HQ4X_PIXEL13_RGB_31
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_61
                        HQ4X_PIXEL32_RGB_61
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 198:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        HQ4X_PIXEL02_RGB_32
                        HQ4X_PIXEL03_RGB_82
                        HQ4X_PIXEL10_RGB_61
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_32
                        HQ4X_PIXEL13_RGB_82
                        HQ4X_PIXEL20_RGB_61
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_31
                        HQ4X_PIXEL23_RGB_81
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        HQ4X_PIXEL32_RGB_31
                        HQ4X_PIXEL33_RGB_81
                        break;
                    }
                case 184:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_61
                        HQ4X_PIXEL02_RGB_61
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL20_RGB_31
                        HQ4X_PIXEL21_RGB_31
                        HQ4X_PIXEL22_RGB_32
                        HQ4X_PIXEL23_RGB_32
                        HQ4X_PIXEL30_RGB_81
                        HQ4X_PIXEL31_RGB_81
                        HQ4X_PIXEL32_RGB_82
                        HQ4X_PIXEL33_RGB_82
                        break;
                    }
                case 99:
                    {
                        HQ4X_PIXEL00_RGB_81
                        HQ4X_PIXEL01_RGB_31
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_81
                        HQ4X_PIXEL11_RGB_31
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_61
                        HQ4X_PIXEL20_RGB_82
                        HQ4X_PIXEL21_RGB_32
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_61
                        HQ4X_PIXEL30_RGB_82
                        HQ4X_PIXEL31_RGB_32
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 57:
                    {
                        HQ4X_PIXEL00_RGB_82
                        HQ4X_PIXEL01_RGB_82
                        HQ4X_PIXEL02_RGB_61
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_32
                        HQ4X_PIXEL11_RGB_32
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL20_RGB_31
                        HQ4X_PIXEL21_RGB_31
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_81
                        HQ4X_PIXEL31_RGB_81
                        HQ4X_PIXEL32_RGB_61
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 71:
                    {
                        HQ4X_PIXEL00_RGB_81
                        HQ4X_PIXEL01_RGB_31
                        HQ4X_PIXEL02_RGB_32
                        HQ4X_PIXEL03_RGB_82
                        HQ4X_PIXEL10_RGB_81
                        HQ4X_PIXEL11_RGB_31
                        HQ4X_PIXEL12_RGB_32
                        HQ4X_PIXEL13_RGB_82
                        HQ4X_PIXEL20_RGB_61
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_61
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 156:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_61
                        HQ4X_PIXEL02_RGB_81
                        HQ4X_PIXEL03_RGB_81
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_31
                        HQ4X_PIXEL13_RGB_31
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_32
                        HQ4X_PIXEL23_RGB_32
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_61
                        HQ4X_PIXEL32_RGB_82
                        HQ4X_PIXEL33_RGB_82
                        break;
                    }
                case 226:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_61
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_61
                        HQ4X_PIXEL20_RGB_82
                        HQ4X_PIXEL21_RGB_32
                        HQ4X_PIXEL22_RGB_31
                        HQ4X_PIXEL23_RGB_81
                        HQ4X_PIXEL30_RGB_82
                        HQ4X_PIXEL31_RGB_32
                        HQ4X_PIXEL32_RGB_31
                        HQ4X_PIXEL33_RGB_81
                        break;
                    }
                case 60:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_61
                        HQ4X_PIXEL02_RGB_81
                        HQ4X_PIXEL03_RGB_81
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_31
                        HQ4X_PIXEL13_RGB_31
                        HQ4X_PIXEL20_RGB_31
                        HQ4X_PIXEL21_RGB_31
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_81
                        HQ4X_PIXEL31_RGB_81
                        HQ4X_PIXEL32_RGB_61
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 195:
                    {
                        HQ4X_PIXEL00_RGB_81
                        HQ4X_PIXEL01_RGB_31
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_81
                        HQ4X_PIXEL11_RGB_31
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_61
                        HQ4X_PIXEL20_RGB_61
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_31
                        HQ4X_PIXEL23_RGB_81
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        HQ4X_PIXEL32_RGB_31
                        HQ4X_PIXEL33_RGB_81
                        break;
                    }
                case 102:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        HQ4X_PIXEL02_RGB_32
                        HQ4X_PIXEL03_RGB_82
                        HQ4X_PIXEL10_RGB_61
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_32
                        HQ4X_PIXEL13_RGB_82
                        HQ4X_PIXEL20_RGB_82
                        HQ4X_PIXEL21_RGB_32
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_61
                        HQ4X_PIXEL30_RGB_82
                        HQ4X_PIXEL31_RGB_32
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 153:
                    {
                        HQ4X_PIXEL00_RGB_82
                        HQ4X_PIXEL01_RGB_82
                        HQ4X_PIXEL02_RGB_61
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_32
                        HQ4X_PIXEL11_RGB_32
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_32
                        HQ4X_PIXEL23_RGB_32
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_61
                        HQ4X_PIXEL32_RGB_82
                        HQ4X_PIXEL33_RGB_82
                        break;
                    }
                case 58:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_80
                            HQ4X_PIXEL01_RGB_10
                            HQ4X_PIXEL10_RGB_10
                            HQ4X_PIXEL11_RGB_30
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_20
                            HQ4X_PIXEL01_RGB_12
                            HQ4X_PIXEL10_RGB_11
                            HQ4X_PIXEL11_RGB_0
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_10
                            HQ4X_PIXEL03_RGB_80
                            HQ4X_PIXEL12_RGB_30
                            HQ4X_PIXEL13_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_11
                            HQ4X_PIXEL03_RGB_20
                            HQ4X_PIXEL12_RGB_0
                            HQ4X_PIXEL13_RGB_12
                        }
                        HQ4X_PIXEL20_RGB_31
                        HQ4X_PIXEL21_RGB_31
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_81
                        HQ4X_PIXEL31_RGB_81
                        HQ4X_PIXEL32_RGB_61
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 83:
                    {
                        HQ4X_PIXEL00_RGB_81
                        HQ4X_PIXEL01_RGB_31
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_10
                            HQ4X_PIXEL03_RGB_80
                            HQ4X_PIXEL12_RGB_30
                            HQ4X_PIXEL13_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_11
                            HQ4X_PIXEL03_RGB_20
                            HQ4X_PIXEL12_RGB_0
                            HQ4X_PIXEL13_RGB_12
                        }
                        HQ4X_PIXEL10_RGB_81
                        HQ4X_PIXEL11_RGB_31
                        HQ4X_PIXEL20_RGB_61
                        HQ4X_PIXEL21_RGB_30
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL22_RGB_30
                            HQ4X_PIXEL23_RGB_10
                            HQ4X_PIXEL32_RGB_10
                            HQ4X_PIXEL33_RGB_80
                        }
                        else
                        {
                            HQ4X_PIXEL22_RGB_0
                            HQ4X_PIXEL23_RGB_11
                            HQ4X_PIXEL32_RGB_12
                            HQ4X_PIXEL33_RGB_20
                        }
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        break;
                    }
                case 92:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_61
                        HQ4X_PIXEL02_RGB_81
                        HQ4X_PIXEL03_RGB_81
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_31
                        HQ4X_PIXEL13_RGB_31
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_10
                            HQ4X_PIXEL21_RGB_30
                            HQ4X_PIXEL30_RGB_80
                            HQ4X_PIXEL31_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_12
                            HQ4X_PIXEL21_RGB_0
                            HQ4X_PIXEL30_RGB_20
                            HQ4X_PIXEL31_RGB_11
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL22_RGB_30
                            HQ4X_PIXEL23_RGB_10
                            HQ4X_PIXEL32_RGB_10
                            HQ4X_PIXEL33_RGB_80
                        }
                        else
                        {
                            HQ4X_PIXEL22_RGB_0
                            HQ4X_PIXEL23_RGB_11
                            HQ4X_PIXEL32_RGB_12
                            HQ4X_PIXEL33_RGB_20
                        }
                        break;
                    }
                case 202:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_80
                            HQ4X_PIXEL01_RGB_10
                            HQ4X_PIXEL10_RGB_10
                            HQ4X_PIXEL11_RGB_30
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_20
                            HQ4X_PIXEL01_RGB_12
                            HQ4X_PIXEL10_RGB_11
                            HQ4X_PIXEL11_RGB_0
                        }
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_61
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_10
                            HQ4X_PIXEL21_RGB_30
                            HQ4X_PIXEL30_RGB_80
                            HQ4X_PIXEL31_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_12
                            HQ4X_PIXEL21_RGB_0
                            HQ4X_PIXEL30_RGB_20
                            HQ4X_PIXEL31_RGB_11
                        }
                        HQ4X_PIXEL22_RGB_31
                        HQ4X_PIXEL23_RGB_81
                        HQ4X_PIXEL32_RGB_31
                        HQ4X_PIXEL33_RGB_81
                        break;
                    }
                case 78:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_80
                            HQ4X_PIXEL01_RGB_10
                            HQ4X_PIXEL10_RGB_10
                            HQ4X_PIXEL11_RGB_30
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_20
                            HQ4X_PIXEL01_RGB_12
                            HQ4X_PIXEL10_RGB_11
                            HQ4X_PIXEL11_RGB_0
                        }
                        HQ4X_PIXEL02_RGB_32
                        HQ4X_PIXEL03_RGB_82
                        HQ4X_PIXEL12_RGB_32
                        HQ4X_PIXEL13_RGB_82
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_10
                            HQ4X_PIXEL21_RGB_30
                            HQ4X_PIXEL30_RGB_80
                            HQ4X_PIXEL31_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_12
                            HQ4X_PIXEL21_RGB_0
                            HQ4X_PIXEL30_RGB_20
                            HQ4X_PIXEL31_RGB_11
                        }
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_61
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 154:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_80
                            HQ4X_PIXEL01_RGB_10
                            HQ4X_PIXEL10_RGB_10
                            HQ4X_PIXEL11_RGB_30
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_20
                            HQ4X_PIXEL01_RGB_12
                            HQ4X_PIXEL10_RGB_11
                            HQ4X_PIXEL11_RGB_0
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_10
                            HQ4X_PIXEL03_RGB_80
                            HQ4X_PIXEL12_RGB_30
                            HQ4X_PIXEL13_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_11
                            HQ4X_PIXEL03_RGB_20
                            HQ4X_PIXEL12_RGB_0
                            HQ4X_PIXEL13_RGB_12
                        }
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_32
                        HQ4X_PIXEL23_RGB_32
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_61
                        HQ4X_PIXEL32_RGB_82
                        HQ4X_PIXEL33_RGB_82
                        break;
                    }
                case 114:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_10
                            HQ4X_PIXEL03_RGB_80
                            HQ4X_PIXEL12_RGB_30
                            HQ4X_PIXEL13_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_11
                            HQ4X_PIXEL03_RGB_20
                            HQ4X_PIXEL12_RGB_0
                            HQ4X_PIXEL13_RGB_12
                        }
                        HQ4X_PIXEL10_RGB_61
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL20_RGB_82
                        HQ4X_PIXEL21_RGB_32
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL22_RGB_30
                            HQ4X_PIXEL23_RGB_10
                            HQ4X_PIXEL32_RGB_10
                            HQ4X_PIXEL33_RGB_80
                        }
                        else
                        {
                            HQ4X_PIXEL22_RGB_0
                            HQ4X_PIXEL23_RGB_11
                            HQ4X_PIXEL32_RGB_12
                            HQ4X_PIXEL33_RGB_20
                        }
                        HQ4X_PIXEL30_RGB_82
                        HQ4X_PIXEL31_RGB_32
                        break;
                    }
                case 89:
                    {
                        HQ4X_PIXEL00_RGB_82
                        HQ4X_PIXEL01_RGB_82
                        HQ4X_PIXEL02_RGB_61
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_32
                        HQ4X_PIXEL11_RGB_32
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_10
                            HQ4X_PIXEL21_RGB_30
                            HQ4X_PIXEL30_RGB_80
                            HQ4X_PIXEL31_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_12
                            HQ4X_PIXEL21_RGB_0
                            HQ4X_PIXEL30_RGB_20
                            HQ4X_PIXEL31_RGB_11
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL22_RGB_30
                            HQ4X_PIXEL23_RGB_10
                            HQ4X_PIXEL32_RGB_10
                            HQ4X_PIXEL33_RGB_80
                        }
                        else
                        {
                            HQ4X_PIXEL22_RGB_0
                            HQ4X_PIXEL23_RGB_11
                            HQ4X_PIXEL32_RGB_12
                            HQ4X_PIXEL33_RGB_20
                        }
                        break;
                    }
                case 90:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_80
                            HQ4X_PIXEL01_RGB_10
                            HQ4X_PIXEL10_RGB_10
                            HQ4X_PIXEL11_RGB_30
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_20
                            HQ4X_PIXEL01_RGB_12
                            HQ4X_PIXEL10_RGB_11
                            HQ4X_PIXEL11_RGB_0
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_10
                            HQ4X_PIXEL03_RGB_80
                            HQ4X_PIXEL12_RGB_30
                            HQ4X_PIXEL13_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_11
                            HQ4X_PIXEL03_RGB_20
                            HQ4X_PIXEL12_RGB_0
                            HQ4X_PIXEL13_RGB_12
                        }
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_10
                            HQ4X_PIXEL21_RGB_30
                            HQ4X_PIXEL30_RGB_80
                            HQ4X_PIXEL31_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_12
                            HQ4X_PIXEL21_RGB_0
                            HQ4X_PIXEL30_RGB_20
                            HQ4X_PIXEL31_RGB_11
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL22_RGB_30
                            HQ4X_PIXEL23_RGB_10
                            HQ4X_PIXEL32_RGB_10
                            HQ4X_PIXEL33_RGB_80
                        }
                        else
                        {
                            HQ4X_PIXEL22_RGB_0
                            HQ4X_PIXEL23_RGB_11
                            HQ4X_PIXEL32_RGB_12
                            HQ4X_PIXEL33_RGB_20
                        }
                        break;
                    }
                case 55:
                case 23:
                    {
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL00_RGB_81
                            HQ4X_PIXEL01_RGB_31
                            HQ4X_PIXEL02_RGB_0
                            HQ4X_PIXEL03_RGB_0
                            HQ4X_PIXEL12_RGB_0
                            HQ4X_PIXEL13_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_12
                            HQ4X_PIXEL01_RGB_14
                            HQ4X_PIXEL02_RGB_83
                            HQ4X_PIXEL03_RGB_50
                            HQ4X_PIXEL12_RGB_70
                            HQ4X_PIXEL13_RGB_21
                        }
                        HQ4X_PIXEL10_RGB_81
                        HQ4X_PIXEL11_RGB_31
                        HQ4X_PIXEL20_RGB_60
                        HQ4X_PIXEL21_RGB_70
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_20
                        HQ4X_PIXEL31_RGB_60
                        HQ4X_PIXEL32_RGB_61
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 182:
                case 150:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_0
                            HQ4X_PIXEL03_RGB_0
                            HQ4X_PIXEL12_RGB_0
                            HQ4X_PIXEL13_RGB_0
                            HQ4X_PIXEL23_RGB_32
                            HQ4X_PIXEL33_RGB_82
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_21
                            HQ4X_PIXEL03_RGB_50
                            HQ4X_PIXEL12_RGB_70
                            HQ4X_PIXEL13_RGB_83
                            HQ4X_PIXEL23_RGB_13
                            HQ4X_PIXEL33_RGB_11
                        }
                        HQ4X_PIXEL10_RGB_61
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL20_RGB_60
                        HQ4X_PIXEL21_RGB_70
                        HQ4X_PIXEL22_RGB_32
                        HQ4X_PIXEL30_RGB_20
                        HQ4X_PIXEL31_RGB_60
                        HQ4X_PIXEL32_RGB_82
                        break;
                    }
                case 213:
                case 212:
                    {
                        HQ4X_PIXEL00_RGB_20
                        HQ4X_PIXEL01_RGB_60
                        HQ4X_PIXEL02_RGB_81
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL03_RGB_81
                            HQ4X_PIXEL13_RGB_31
                            HQ4X_PIXEL22_RGB_0
                            HQ4X_PIXEL23_RGB_0
                            HQ4X_PIXEL32_RGB_0
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL03_RGB_12
                            HQ4X_PIXEL13_RGB_14
                            HQ4X_PIXEL22_RGB_70
                            HQ4X_PIXEL23_RGB_83
                            HQ4X_PIXEL32_RGB_21
                            HQ4X_PIXEL33_RGB_50
                        }
                        HQ4X_PIXEL10_RGB_60
                        HQ4X_PIXEL11_RGB_70
                        HQ4X_PIXEL12_RGB_31
                        HQ4X_PIXEL20_RGB_61
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        break;
                    }
                case 241:
                case 240:
                    {
                        HQ4X_PIXEL00_RGB_20
                        HQ4X_PIXEL01_RGB_60
                        HQ4X_PIXEL02_RGB_61
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_60
                        HQ4X_PIXEL11_RGB_70
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL20_RGB_82
                        HQ4X_PIXEL21_RGB_32
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL22_RGB_0
                            HQ4X_PIXEL23_RGB_0
                            HQ4X_PIXEL30_RGB_82
                            HQ4X_PIXEL31_RGB_32
                            HQ4X_PIXEL32_RGB_0
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL22_RGB_70
                            HQ4X_PIXEL23_RGB_21
                            HQ4X_PIXEL30_RGB_11
                            HQ4X_PIXEL31_RGB_13
                            HQ4X_PIXEL32_RGB_83
                            HQ4X_PIXEL33_RGB_50
                        }
                        break;
                    }
                case 236:
                case 232:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_61
                        HQ4X_PIXEL02_RGB_60
                        HQ4X_PIXEL03_RGB_20
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_70
                        HQ4X_PIXEL13_RGB_60
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_0
                            HQ4X_PIXEL21_RGB_0
                            HQ4X_PIXEL30_RGB_0
                            HQ4X_PIXEL31_RGB_0
                            HQ4X_PIXEL32_RGB_31
                            HQ4X_PIXEL33_RGB_81
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_21
                            HQ4X_PIXEL21_RGB_70
                            HQ4X_PIXEL30_RGB_50
                            HQ4X_PIXEL31_RGB_83
                            HQ4X_PIXEL32_RGB_14
                            HQ4X_PIXEL33_RGB_12
                        }
                        HQ4X_PIXEL22_RGB_31
                        HQ4X_PIXEL23_RGB_81
                        break;
                    }
                case 109:
                case 105:
                    {
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL00_RGB_82
                            HQ4X_PIXEL10_RGB_32
                            HQ4X_PIXEL20_RGB_0
                            HQ4X_PIXEL21_RGB_0
                            HQ4X_PIXEL30_RGB_0
                            HQ4X_PIXEL31_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_11
                            HQ4X_PIXEL10_RGB_13
                            HQ4X_PIXEL20_RGB_83
                            HQ4X_PIXEL21_RGB_70
                            HQ4X_PIXEL30_RGB_50
                            HQ4X_PIXEL31_RGB_21
                        }
                        HQ4X_PIXEL01_RGB_82
                        HQ4X_PIXEL02_RGB_60
                        HQ4X_PIXEL03_RGB_20
                        HQ4X_PIXEL11_RGB_32
                        HQ4X_PIXEL12_RGB_70
                        HQ4X_PIXEL13_RGB_60
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_61
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 171:
                case 43:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                            HQ4X_PIXEL01_RGB_0
                            HQ4X_PIXEL10_RGB_0
                            HQ4X_PIXEL11_RGB_0
                            HQ4X_PIXEL20_RGB_31
                            HQ4X_PIXEL30_RGB_81
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_50
                            HQ4X_PIXEL01_RGB_21
                            HQ4X_PIXEL10_RGB_83
                            HQ4X_PIXEL11_RGB_70
                            HQ4X_PIXEL20_RGB_14
                            HQ4X_PIXEL30_RGB_12
                        }
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_61
                        HQ4X_PIXEL21_RGB_31
                        HQ4X_PIXEL22_RGB_70
                        HQ4X_PIXEL23_RGB_60
                        HQ4X_PIXEL31_RGB_81
                        HQ4X_PIXEL32_RGB_60
                        HQ4X_PIXEL33_RGB_20
                        break;
                    }
                case 143:
                case 15:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                            HQ4X_PIXEL01_RGB_0
                            HQ4X_PIXEL02_RGB_32
                            HQ4X_PIXEL03_RGB_82
                            HQ4X_PIXEL10_RGB_0
                            HQ4X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_50
                            HQ4X_PIXEL01_RGB_83
                            HQ4X_PIXEL02_RGB_13
                            HQ4X_PIXEL03_RGB_11
                            HQ4X_PIXEL10_RGB_21
                            HQ4X_PIXEL11_RGB_70
                        }
                        HQ4X_PIXEL12_RGB_32
                        HQ4X_PIXEL13_RGB_82
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_70
                        HQ4X_PIXEL23_RGB_60
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_61
                        HQ4X_PIXEL32_RGB_60
                        HQ4X_PIXEL33_RGB_20
                        break;
                    }
                case 124:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_61
                        HQ4X_PIXEL02_RGB_81
                        HQ4X_PIXEL03_RGB_81
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_31
                        HQ4X_PIXEL13_RGB_31
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_0
                            HQ4X_PIXEL30_RGB_0
                            HQ4X_PIXEL31_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_50
                            HQ4X_PIXEL30_RGB_50
                            HQ4X_PIXEL31_RGB_50
                        }
                        HQ4X_PIXEL21_RGB_0
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 203:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                            HQ4X_PIXEL01_RGB_0
                            HQ4X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_50
                            HQ4X_PIXEL01_RGB_50
                            HQ4X_PIXEL10_RGB_50
                        }
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL11_RGB_0
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_61
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_31
                        HQ4X_PIXEL23_RGB_81
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        HQ4X_PIXEL32_RGB_31
                        HQ4X_PIXEL33_RGB_81
                        break;
                    }
                case 62:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_0
                            HQ4X_PIXEL03_RGB_0
                            HQ4X_PIXEL13_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_50
                            HQ4X_PIXEL03_RGB_50
                            HQ4X_PIXEL13_RGB_50
                        }
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_0
                        HQ4X_PIXEL20_RGB_31
                        HQ4X_PIXEL21_RGB_31
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_81
                        HQ4X_PIXEL31_RGB_81
                        HQ4X_PIXEL32_RGB_61
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 211:
                    {
                        HQ4X_PIXEL00_RGB_81
                        HQ4X_PIXEL01_RGB_31
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_81
                        HQ4X_PIXEL11_RGB_31
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL20_RGB_61
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL23_RGB_0
                            HQ4X_PIXEL32_RGB_0
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL23_RGB_50
                            HQ4X_PIXEL32_RGB_50
                            HQ4X_PIXEL33_RGB_50
                        }
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        break;
                    }
                case 118:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_0
                            HQ4X_PIXEL03_RGB_0
                            HQ4X_PIXEL13_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_50
                            HQ4X_PIXEL03_RGB_50
                            HQ4X_PIXEL13_RGB_50
                        }
                        HQ4X_PIXEL10_RGB_61
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_0
                        HQ4X_PIXEL20_RGB_82
                        HQ4X_PIXEL21_RGB_32
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_82
                        HQ4X_PIXEL31_RGB_32
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 217:
                    {
                        HQ4X_PIXEL00_RGB_82
                        HQ4X_PIXEL01_RGB_82
                        HQ4X_PIXEL02_RGB_61
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_32
                        HQ4X_PIXEL11_RGB_32
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL23_RGB_0
                            HQ4X_PIXEL32_RGB_0
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL23_RGB_50
                            HQ4X_PIXEL32_RGB_50
                            HQ4X_PIXEL33_RGB_50
                        }
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        break;
                    }
                case 110:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        HQ4X_PIXEL02_RGB_32
                        HQ4X_PIXEL03_RGB_82
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_32
                        HQ4X_PIXEL13_RGB_82
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_0
                            HQ4X_PIXEL30_RGB_0
                            HQ4X_PIXEL31_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_50
                            HQ4X_PIXEL30_RGB_50
                            HQ4X_PIXEL31_RGB_50
                        }
                        HQ4X_PIXEL21_RGB_0
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_61
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 155:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                            HQ4X_PIXEL01_RGB_0
                            HQ4X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_50
                            HQ4X_PIXEL01_RGB_50
                            HQ4X_PIXEL10_RGB_50
                        }
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL11_RGB_0
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_32
                        HQ4X_PIXEL23_RGB_32
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_61
                        HQ4X_PIXEL32_RGB_82
                        HQ4X_PIXEL33_RGB_82
                        break;
                    }
                case 188:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_61
                        HQ4X_PIXEL02_RGB_81
                        HQ4X_PIXEL03_RGB_81
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_31
                        HQ4X_PIXEL13_RGB_31
                        HQ4X_PIXEL20_RGB_31
                        HQ4X_PIXEL21_RGB_31
                        HQ4X_PIXEL22_RGB_32
                        HQ4X_PIXEL23_RGB_32
                        HQ4X_PIXEL30_RGB_81
                        HQ4X_PIXEL31_RGB_81
                        HQ4X_PIXEL32_RGB_82
                        HQ4X_PIXEL33_RGB_82
                        break;
                    }
                case 185:
                    {
                        HQ4X_PIXEL00_RGB_82
                        HQ4X_PIXEL01_RGB_82
                        HQ4X_PIXEL02_RGB_61
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_32
                        HQ4X_PIXEL11_RGB_32
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL20_RGB_31
                        HQ4X_PIXEL21_RGB_31
                        HQ4X_PIXEL22_RGB_32
                        HQ4X_PIXEL23_RGB_32
                        HQ4X_PIXEL30_RGB_81
                        HQ4X_PIXEL31_RGB_81
                        HQ4X_PIXEL32_RGB_82
                        HQ4X_PIXEL33_RGB_82
                        break;
                    }
                case 61:
                    {
                        HQ4X_PIXEL00_RGB_82
                        HQ4X_PIXEL01_RGB_82
                        HQ4X_PIXEL02_RGB_81
                        HQ4X_PIXEL03_RGB_81
                        HQ4X_PIXEL10_RGB_32
                        HQ4X_PIXEL11_RGB_32
                        HQ4X_PIXEL12_RGB_31
                        HQ4X_PIXEL13_RGB_31
                        HQ4X_PIXEL20_RGB_31
                        HQ4X_PIXEL21_RGB_31
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_81
                        HQ4X_PIXEL31_RGB_81
                        HQ4X_PIXEL32_RGB_61
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 157:
                    {
                        HQ4X_PIXEL00_RGB_82
                        HQ4X_PIXEL01_RGB_82
                        HQ4X_PIXEL02_RGB_81
                        HQ4X_PIXEL03_RGB_81
                        HQ4X_PIXEL10_RGB_32
                        HQ4X_PIXEL11_RGB_32
                        HQ4X_PIXEL12_RGB_31
                        HQ4X_PIXEL13_RGB_31
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_32
                        HQ4X_PIXEL23_RGB_32
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_61
                        HQ4X_PIXEL32_RGB_82
                        HQ4X_PIXEL33_RGB_82
                        break;
                    }
                case 103:
                    {
                        HQ4X_PIXEL00_RGB_81
                        HQ4X_PIXEL01_RGB_31
                        HQ4X_PIXEL02_RGB_32
                        HQ4X_PIXEL03_RGB_82
                        HQ4X_PIXEL10_RGB_81
                        HQ4X_PIXEL11_RGB_31
                        HQ4X_PIXEL12_RGB_32
                        HQ4X_PIXEL13_RGB_82
                        HQ4X_PIXEL20_RGB_82
                        HQ4X_PIXEL21_RGB_32
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_61
                        HQ4X_PIXEL30_RGB_82
                        HQ4X_PIXEL31_RGB_32
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 227:
                    {
                        HQ4X_PIXEL00_RGB_81
                        HQ4X_PIXEL01_RGB_31
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_81
                        HQ4X_PIXEL11_RGB_31
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_61
                        HQ4X_PIXEL20_RGB_82
                        HQ4X_PIXEL21_RGB_32
                        HQ4X_PIXEL22_RGB_31
                        HQ4X_PIXEL23_RGB_81
                        HQ4X_PIXEL30_RGB_82
                        HQ4X_PIXEL31_RGB_32
                        HQ4X_PIXEL32_RGB_31
                        HQ4X_PIXEL33_RGB_81
                        break;
                    }
                case 230:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        HQ4X_PIXEL02_RGB_32
                        HQ4X_PIXEL03_RGB_82
                        HQ4X_PIXEL10_RGB_61
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_32
                        HQ4X_PIXEL13_RGB_82
                        HQ4X_PIXEL20_RGB_82
                        HQ4X_PIXEL21_RGB_32
                        HQ4X_PIXEL22_RGB_31
                        HQ4X_PIXEL23_RGB_81
                        HQ4X_PIXEL30_RGB_82
                        HQ4X_PIXEL31_RGB_32
                        HQ4X_PIXEL32_RGB_31
                        HQ4X_PIXEL33_RGB_81
                        break;
                    }
                case 199:
                    {
                        HQ4X_PIXEL00_RGB_81
                        HQ4X_PIXEL01_RGB_31
                        HQ4X_PIXEL02_RGB_32
                        HQ4X_PIXEL03_RGB_82
                        HQ4X_PIXEL10_RGB_81
                        HQ4X_PIXEL11_RGB_31
                        HQ4X_PIXEL12_RGB_32
                        HQ4X_PIXEL13_RGB_82
                        HQ4X_PIXEL20_RGB_61
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_31
                        HQ4X_PIXEL23_RGB_81
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        HQ4X_PIXEL32_RGB_31
                        HQ4X_PIXEL33_RGB_81
                        break;
                    }
                case 220:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_61
                        HQ4X_PIXEL02_RGB_81
                        HQ4X_PIXEL03_RGB_81
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_31
                        HQ4X_PIXEL13_RGB_31
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_10
                            HQ4X_PIXEL21_RGB_30
                            HQ4X_PIXEL30_RGB_80
                            HQ4X_PIXEL31_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_12
                            HQ4X_PIXEL21_RGB_0
                            HQ4X_PIXEL30_RGB_20
                            HQ4X_PIXEL31_RGB_11
                        }
                        HQ4X_PIXEL22_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL23_RGB_0
                            HQ4X_PIXEL32_RGB_0
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL23_RGB_50
                            HQ4X_PIXEL32_RGB_50
                            HQ4X_PIXEL33_RGB_50
                        }
                        break;
                    }
                case 158:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_80
                            HQ4X_PIXEL01_RGB_10
                            HQ4X_PIXEL10_RGB_10
                            HQ4X_PIXEL11_RGB_30
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_20
                            HQ4X_PIXEL01_RGB_12
                            HQ4X_PIXEL10_RGB_11
                            HQ4X_PIXEL11_RGB_0
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_0
                            HQ4X_PIXEL03_RGB_0
                            HQ4X_PIXEL13_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_50
                            HQ4X_PIXEL03_RGB_50
                            HQ4X_PIXEL13_RGB_50
                        }
                        HQ4X_PIXEL12_RGB_0
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_32
                        HQ4X_PIXEL23_RGB_32
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_61
                        HQ4X_PIXEL32_RGB_82
                        HQ4X_PIXEL33_RGB_82
                        break;
                    }
                case 234:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_80
                            HQ4X_PIXEL01_RGB_10
                            HQ4X_PIXEL10_RGB_10
                            HQ4X_PIXEL11_RGB_30
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_20
                            HQ4X_PIXEL01_RGB_12
                            HQ4X_PIXEL10_RGB_11
                            HQ4X_PIXEL11_RGB_0
                        }
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_61
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_0
                            HQ4X_PIXEL30_RGB_0
                            HQ4X_PIXEL31_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_50
                            HQ4X_PIXEL30_RGB_50
                            HQ4X_PIXEL31_RGB_50
                        }
                        HQ4X_PIXEL21_RGB_0
                        HQ4X_PIXEL22_RGB_31
                        HQ4X_PIXEL23_RGB_81
                        HQ4X_PIXEL32_RGB_31
                        HQ4X_PIXEL33_RGB_81
                        break;
                    }
                case 242:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_10
                            HQ4X_PIXEL03_RGB_80
                            HQ4X_PIXEL12_RGB_30
                            HQ4X_PIXEL13_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_11
                            HQ4X_PIXEL03_RGB_20
                            HQ4X_PIXEL12_RGB_0
                            HQ4X_PIXEL13_RGB_12
                        }
                        HQ4X_PIXEL10_RGB_61
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL20_RGB_82
                        HQ4X_PIXEL21_RGB_32
                        HQ4X_PIXEL22_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL23_RGB_0
                            HQ4X_PIXEL32_RGB_0
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL23_RGB_50
                            HQ4X_PIXEL32_RGB_50
                            HQ4X_PIXEL33_RGB_50
                        }
                        HQ4X_PIXEL30_RGB_82
                        HQ4X_PIXEL31_RGB_32
                        break;
                    }
                case 59:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                            HQ4X_PIXEL01_RGB_0
                            HQ4X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_50
                            HQ4X_PIXEL01_RGB_50
                            HQ4X_PIXEL10_RGB_50
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_10
                            HQ4X_PIXEL03_RGB_80
                            HQ4X_PIXEL12_RGB_30
                            HQ4X_PIXEL13_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_11
                            HQ4X_PIXEL03_RGB_20
                            HQ4X_PIXEL12_RGB_0
                            HQ4X_PIXEL13_RGB_12
                        }
                        HQ4X_PIXEL11_RGB_0
                        HQ4X_PIXEL20_RGB_31
                        HQ4X_PIXEL21_RGB_31
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_81
                        HQ4X_PIXEL31_RGB_81
                        HQ4X_PIXEL32_RGB_61
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 121:
                    {
                        HQ4X_PIXEL00_RGB_82
                        HQ4X_PIXEL01_RGB_82
                        HQ4X_PIXEL02_RGB_61
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_32
                        HQ4X_PIXEL11_RGB_32
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_0
                            HQ4X_PIXEL30_RGB_0
                            HQ4X_PIXEL31_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_50
                            HQ4X_PIXEL30_RGB_50
                            HQ4X_PIXEL31_RGB_50
                        }
                        HQ4X_PIXEL21_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL22_RGB_30
                            HQ4X_PIXEL23_RGB_10
                            HQ4X_PIXEL32_RGB_10
                            HQ4X_PIXEL33_RGB_80
                        }
                        else
                        {
                            HQ4X_PIXEL22_RGB_0
                            HQ4X_PIXEL23_RGB_11
                            HQ4X_PIXEL32_RGB_12
                            HQ4X_PIXEL33_RGB_20
                        }
                        break;
                    }
                case 87:
                    {
                        HQ4X_PIXEL00_RGB_81
                        HQ4X_PIXEL01_RGB_31
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_0
                            HQ4X_PIXEL03_RGB_0
                            HQ4X_PIXEL13_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_50
                            HQ4X_PIXEL03_RGB_50
                            HQ4X_PIXEL13_RGB_50
                        }
                        HQ4X_PIXEL10_RGB_81
                        HQ4X_PIXEL11_RGB_31
                        HQ4X_PIXEL12_RGB_0
                        HQ4X_PIXEL20_RGB_61
                        HQ4X_PIXEL21_RGB_30
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL22_RGB_30
                            HQ4X_PIXEL23_RGB_10
                            HQ4X_PIXEL32_RGB_10
                            HQ4X_PIXEL33_RGB_80
                        }
                        else
                        {
                            HQ4X_PIXEL22_RGB_0
                            HQ4X_PIXEL23_RGB_11
                            HQ4X_PIXEL32_RGB_12
                            HQ4X_PIXEL33_RGB_20
                        }
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        break;
                    }
                case 79:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                            HQ4X_PIXEL01_RGB_0
                            HQ4X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_50
                            HQ4X_PIXEL01_RGB_50
                            HQ4X_PIXEL10_RGB_50
                        }
                        HQ4X_PIXEL02_RGB_32
                        HQ4X_PIXEL03_RGB_82
                        HQ4X_PIXEL11_RGB_0
                        HQ4X_PIXEL12_RGB_32
                        HQ4X_PIXEL13_RGB_82
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_10
                            HQ4X_PIXEL21_RGB_30
                            HQ4X_PIXEL30_RGB_80
                            HQ4X_PIXEL31_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_12
                            HQ4X_PIXEL21_RGB_0
                            HQ4X_PIXEL30_RGB_20
                            HQ4X_PIXEL31_RGB_11
                        }
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_61
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 122:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_80
                            HQ4X_PIXEL01_RGB_10
                            HQ4X_PIXEL10_RGB_10
                            HQ4X_PIXEL11_RGB_30
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_20
                            HQ4X_PIXEL01_RGB_12
                            HQ4X_PIXEL10_RGB_11
                            HQ4X_PIXEL11_RGB_0
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_10
                            HQ4X_PIXEL03_RGB_80
                            HQ4X_PIXEL12_RGB_30
                            HQ4X_PIXEL13_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_11
                            HQ4X_PIXEL03_RGB_20
                            HQ4X_PIXEL12_RGB_0
                            HQ4X_PIXEL13_RGB_12
                        }
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_0
                            HQ4X_PIXEL30_RGB_0
                            HQ4X_PIXEL31_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_50
                            HQ4X_PIXEL30_RGB_50
                            HQ4X_PIXEL31_RGB_50
                        }
                        HQ4X_PIXEL21_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL22_RGB_30
                            HQ4X_PIXEL23_RGB_10
                            HQ4X_PIXEL32_RGB_10
                            HQ4X_PIXEL33_RGB_80
                        }
                        else
                        {
                            HQ4X_PIXEL22_RGB_0
                            HQ4X_PIXEL23_RGB_11
                            HQ4X_PIXEL32_RGB_12
                            HQ4X_PIXEL33_RGB_20
                        }
                        break;
                    }
                case 94:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_80
                            HQ4X_PIXEL01_RGB_10
                            HQ4X_PIXEL10_RGB_10
                            HQ4X_PIXEL11_RGB_30
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_20
                            HQ4X_PIXEL01_RGB_12
                            HQ4X_PIXEL10_RGB_11
                            HQ4X_PIXEL11_RGB_0
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_0
                            HQ4X_PIXEL03_RGB_0
                            HQ4X_PIXEL13_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_50
                            HQ4X_PIXEL03_RGB_50
                            HQ4X_PIXEL13_RGB_50
                        }
                        HQ4X_PIXEL12_RGB_0
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_10
                            HQ4X_PIXEL21_RGB_30
                            HQ4X_PIXEL30_RGB_80
                            HQ4X_PIXEL31_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_12
                            HQ4X_PIXEL21_RGB_0
                            HQ4X_PIXEL30_RGB_20
                            HQ4X_PIXEL31_RGB_11
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL22_RGB_30
                            HQ4X_PIXEL23_RGB_10
                            HQ4X_PIXEL32_RGB_10
                            HQ4X_PIXEL33_RGB_80
                        }
                        else
                        {
                            HQ4X_PIXEL22_RGB_0
                            HQ4X_PIXEL23_RGB_11
                            HQ4X_PIXEL32_RGB_12
                            HQ4X_PIXEL33_RGB_20
                        }
                        break;
                    }
                case 218:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_80
                            HQ4X_PIXEL01_RGB_10
                            HQ4X_PIXEL10_RGB_10
                            HQ4X_PIXEL11_RGB_30
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_20
                            HQ4X_PIXEL01_RGB_12
                            HQ4X_PIXEL10_RGB_11
                            HQ4X_PIXEL11_RGB_0
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_10
                            HQ4X_PIXEL03_RGB_80
                            HQ4X_PIXEL12_RGB_30
                            HQ4X_PIXEL13_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_11
                            HQ4X_PIXEL03_RGB_20
                            HQ4X_PIXEL12_RGB_0
                            HQ4X_PIXEL13_RGB_12
                        }
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_10
                            HQ4X_PIXEL21_RGB_30
                            HQ4X_PIXEL30_RGB_80
                            HQ4X_PIXEL31_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_12
                            HQ4X_PIXEL21_RGB_0
                            HQ4X_PIXEL30_RGB_20
                            HQ4X_PIXEL31_RGB_11
                        }
                        HQ4X_PIXEL22_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL23_RGB_0
                            HQ4X_PIXEL32_RGB_0
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL23_RGB_50
                            HQ4X_PIXEL32_RGB_50
                            HQ4X_PIXEL33_RGB_50
                        }
                        break;
                    }
                case 91:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                            HQ4X_PIXEL01_RGB_0
                            HQ4X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_50
                            HQ4X_PIXEL01_RGB_50
                            HQ4X_PIXEL10_RGB_50
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_10
                            HQ4X_PIXEL03_RGB_80
                            HQ4X_PIXEL12_RGB_30
                            HQ4X_PIXEL13_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_11
                            HQ4X_PIXEL03_RGB_20
                            HQ4X_PIXEL12_RGB_0
                            HQ4X_PIXEL13_RGB_12
                        }
                        HQ4X_PIXEL11_RGB_0
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_10
                            HQ4X_PIXEL21_RGB_30
                            HQ4X_PIXEL30_RGB_80
                            HQ4X_PIXEL31_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_12
                            HQ4X_PIXEL21_RGB_0
                            HQ4X_PIXEL30_RGB_20
                            HQ4X_PIXEL31_RGB_11
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL22_RGB_30
                            HQ4X_PIXEL23_RGB_10
                            HQ4X_PIXEL32_RGB_10
                            HQ4X_PIXEL33_RGB_80
                        }
                        else
                        {
                            HQ4X_PIXEL22_RGB_0
                            HQ4X_PIXEL23_RGB_11
                            HQ4X_PIXEL32_RGB_12
                            HQ4X_PIXEL33_RGB_20
                        }
                        break;
                    }
                case 229:
                    {
                        HQ4X_PIXEL00_RGB_20
                        HQ4X_PIXEL01_RGB_60
                        HQ4X_PIXEL02_RGB_60
                        HQ4X_PIXEL03_RGB_20
                        HQ4X_PIXEL10_RGB_60
                        HQ4X_PIXEL11_RGB_70
                        HQ4X_PIXEL12_RGB_70
                        HQ4X_PIXEL13_RGB_60
                        HQ4X_PIXEL20_RGB_82
                        HQ4X_PIXEL21_RGB_32
                        HQ4X_PIXEL22_RGB_31
                        HQ4X_PIXEL23_RGB_81
                        HQ4X_PIXEL30_RGB_82
                        HQ4X_PIXEL31_RGB_32
                        HQ4X_PIXEL32_RGB_31
                        HQ4X_PIXEL33_RGB_81
                        break;
                    }
                case 167:
                    {
                        HQ4X_PIXEL00_RGB_81
                        HQ4X_PIXEL01_RGB_31
                        HQ4X_PIXEL02_RGB_32
                        HQ4X_PIXEL03_RGB_82
                        HQ4X_PIXEL10_RGB_81
                        HQ4X_PIXEL11_RGB_31
                        HQ4X_PIXEL12_RGB_32
                        HQ4X_PIXEL13_RGB_82
                        HQ4X_PIXEL20_RGB_60
                        HQ4X_PIXEL21_RGB_70
                        HQ4X_PIXEL22_RGB_70
                        HQ4X_PIXEL23_RGB_60
                        HQ4X_PIXEL30_RGB_20
                        HQ4X_PIXEL31_RGB_60
                        HQ4X_PIXEL32_RGB_60
                        HQ4X_PIXEL33_RGB_20
                        break;
                    }
                case 173:
                    {
                        HQ4X_PIXEL00_RGB_82
                        HQ4X_PIXEL01_RGB_82
                        HQ4X_PIXEL02_RGB_60
                        HQ4X_PIXEL03_RGB_20
                        HQ4X_PIXEL10_RGB_32
                        HQ4X_PIXEL11_RGB_32
                        HQ4X_PIXEL12_RGB_70
                        HQ4X_PIXEL13_RGB_60
                        HQ4X_PIXEL20_RGB_31
                        HQ4X_PIXEL21_RGB_31
                        HQ4X_PIXEL22_RGB_70
                        HQ4X_PIXEL23_RGB_60
                        HQ4X_PIXEL30_RGB_81
                        HQ4X_PIXEL31_RGB_81
                        HQ4X_PIXEL32_RGB_60
                        HQ4X_PIXEL33_RGB_20
                        break;
                    }
                case 181:
                    {
                        HQ4X_PIXEL00_RGB_20
                        HQ4X_PIXEL01_RGB_60
                        HQ4X_PIXEL02_RGB_81
                        HQ4X_PIXEL03_RGB_81
                        HQ4X_PIXEL10_RGB_60
                        HQ4X_PIXEL11_RGB_70
                        HQ4X_PIXEL12_RGB_31
                        HQ4X_PIXEL13_RGB_31
                        HQ4X_PIXEL20_RGB_60
                        HQ4X_PIXEL21_RGB_70
                        HQ4X_PIXEL22_RGB_32
                        HQ4X_PIXEL23_RGB_32
                        HQ4X_PIXEL30_RGB_20
                        HQ4X_PIXEL31_RGB_60
                        HQ4X_PIXEL32_RGB_82
                        HQ4X_PIXEL33_RGB_82
                        break;
                    }
                case 186:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_80
                            HQ4X_PIXEL01_RGB_10
                            HQ4X_PIXEL10_RGB_10
                            HQ4X_PIXEL11_RGB_30
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_20
                            HQ4X_PIXEL01_RGB_12
                            HQ4X_PIXEL10_RGB_11
                            HQ4X_PIXEL11_RGB_0
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_10
                            HQ4X_PIXEL03_RGB_80
                            HQ4X_PIXEL12_RGB_30
                            HQ4X_PIXEL13_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_11
                            HQ4X_PIXEL03_RGB_20
                            HQ4X_PIXEL12_RGB_0
                            HQ4X_PIXEL13_RGB_12
                        }
                        HQ4X_PIXEL20_RGB_31
                        HQ4X_PIXEL21_RGB_31
                        HQ4X_PIXEL22_RGB_32
                        HQ4X_PIXEL23_RGB_32
                        HQ4X_PIXEL30_RGB_81
                        HQ4X_PIXEL31_RGB_81
                        HQ4X_PIXEL32_RGB_82
                        HQ4X_PIXEL33_RGB_82
                        break;
                    }
                case 115:
                    {
                        HQ4X_PIXEL00_RGB_81
                        HQ4X_PIXEL01_RGB_31
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_10
                            HQ4X_PIXEL03_RGB_80
                            HQ4X_PIXEL12_RGB_30
                            HQ4X_PIXEL13_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_11
                            HQ4X_PIXEL03_RGB_20
                            HQ4X_PIXEL12_RGB_0
                            HQ4X_PIXEL13_RGB_12
                        }
                        HQ4X_PIXEL10_RGB_81
                        HQ4X_PIXEL11_RGB_31
                        HQ4X_PIXEL20_RGB_82
                        HQ4X_PIXEL21_RGB_32
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL22_RGB_30
                            HQ4X_PIXEL23_RGB_10
                            HQ4X_PIXEL32_RGB_10
                            HQ4X_PIXEL33_RGB_80
                        }
                        else
                        {
                            HQ4X_PIXEL22_RGB_0
                            HQ4X_PIXEL23_RGB_11
                            HQ4X_PIXEL32_RGB_12
                            HQ4X_PIXEL33_RGB_20
                        }
                        HQ4X_PIXEL30_RGB_82
                        HQ4X_PIXEL31_RGB_32
                        break;
                    }
                case 93:
                    {
                        HQ4X_PIXEL00_RGB_82
                        HQ4X_PIXEL01_RGB_82
                        HQ4X_PIXEL02_RGB_81
                        HQ4X_PIXEL03_RGB_81
                        HQ4X_PIXEL10_RGB_32
                        HQ4X_PIXEL11_RGB_32
                        HQ4X_PIXEL12_RGB_31
                        HQ4X_PIXEL13_RGB_31
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_10
                            HQ4X_PIXEL21_RGB_30
                            HQ4X_PIXEL30_RGB_80
                            HQ4X_PIXEL31_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_12
                            HQ4X_PIXEL21_RGB_0
                            HQ4X_PIXEL30_RGB_20
                            HQ4X_PIXEL31_RGB_11
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL22_RGB_30
                            HQ4X_PIXEL23_RGB_10
                            HQ4X_PIXEL32_RGB_10
                            HQ4X_PIXEL33_RGB_80
                        }
                        else
                        {
                            HQ4X_PIXEL22_RGB_0
                            HQ4X_PIXEL23_RGB_11
                            HQ4X_PIXEL32_RGB_12
                            HQ4X_PIXEL33_RGB_20
                        }
                        break;
                    }
                case 206:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_80
                            HQ4X_PIXEL01_RGB_10
                            HQ4X_PIXEL10_RGB_10
                            HQ4X_PIXEL11_RGB_30
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_20
                            HQ4X_PIXEL01_RGB_12
                            HQ4X_PIXEL10_RGB_11
                            HQ4X_PIXEL11_RGB_0
                        }
                        HQ4X_PIXEL02_RGB_32
                        HQ4X_PIXEL03_RGB_82
                        HQ4X_PIXEL12_RGB_32
                        HQ4X_PIXEL13_RGB_82
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_10
                            HQ4X_PIXEL21_RGB_30
                            HQ4X_PIXEL30_RGB_80
                            HQ4X_PIXEL31_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_12
                            HQ4X_PIXEL21_RGB_0
                            HQ4X_PIXEL30_RGB_20
                            HQ4X_PIXEL31_RGB_11
                        }
                        HQ4X_PIXEL22_RGB_31
                        HQ4X_PIXEL23_RGB_81
                        HQ4X_PIXEL32_RGB_31
                        HQ4X_PIXEL33_RGB_81
                        break;
                    }
                case 205:
                case 201:
                    {
                        HQ4X_PIXEL00_RGB_82
                        HQ4X_PIXEL01_RGB_82
                        HQ4X_PIXEL02_RGB_60
                        HQ4X_PIXEL03_RGB_20
                        HQ4X_PIXEL10_RGB_32
                        HQ4X_PIXEL11_RGB_32
                        HQ4X_PIXEL12_RGB_70
                        HQ4X_PIXEL13_RGB_60
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_10
                            HQ4X_PIXEL21_RGB_30
                            HQ4X_PIXEL30_RGB_80
                            HQ4X_PIXEL31_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_12
                            HQ4X_PIXEL21_RGB_0
                            HQ4X_PIXEL30_RGB_20
                            HQ4X_PIXEL31_RGB_11
                        }
                        HQ4X_PIXEL22_RGB_31
                        HQ4X_PIXEL23_RGB_81
                        HQ4X_PIXEL32_RGB_31
                        HQ4X_PIXEL33_RGB_81
                        break;
                    }
                case 174:
                case 46:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_80
                            HQ4X_PIXEL01_RGB_10
                            HQ4X_PIXEL10_RGB_10
                            HQ4X_PIXEL11_RGB_30
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_20
                            HQ4X_PIXEL01_RGB_12
                            HQ4X_PIXEL10_RGB_11
                            HQ4X_PIXEL11_RGB_0
                        }
                        HQ4X_PIXEL02_RGB_32
                        HQ4X_PIXEL03_RGB_82
                        HQ4X_PIXEL12_RGB_32
                        HQ4X_PIXEL13_RGB_82
                        HQ4X_PIXEL20_RGB_31
                        HQ4X_PIXEL21_RGB_31
                        HQ4X_PIXEL22_RGB_70
                        HQ4X_PIXEL23_RGB_60
                        HQ4X_PIXEL30_RGB_81
                        HQ4X_PIXEL31_RGB_81
                        HQ4X_PIXEL32_RGB_60
                        HQ4X_PIXEL33_RGB_20
                        break;
                    }
                case 179:
                case 147:
                    {
                        HQ4X_PIXEL00_RGB_81
                        HQ4X_PIXEL01_RGB_31
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_10
                            HQ4X_PIXEL03_RGB_80
                            HQ4X_PIXEL12_RGB_30
                            HQ4X_PIXEL13_RGB_10
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_11
                            HQ4X_PIXEL03_RGB_20
                            HQ4X_PIXEL12_RGB_0
                            HQ4X_PIXEL13_RGB_12
                        }
                        HQ4X_PIXEL10_RGB_81
                        HQ4X_PIXEL11_RGB_31
                        HQ4X_PIXEL20_RGB_60
                        HQ4X_PIXEL21_RGB_70
                        HQ4X_PIXEL22_RGB_32
                        HQ4X_PIXEL23_RGB_32
                        HQ4X_PIXEL30_RGB_20
                        HQ4X_PIXEL31_RGB_60
                        HQ4X_PIXEL32_RGB_82
                        HQ4X_PIXEL33_RGB_82
                        break;
                    }
                case 117:
                case 116:
                    {
                        HQ4X_PIXEL00_RGB_20
                        HQ4X_PIXEL01_RGB_60
                        HQ4X_PIXEL02_RGB_81
                        HQ4X_PIXEL03_RGB_81
                        HQ4X_PIXEL10_RGB_60
                        HQ4X_PIXEL11_RGB_70
                        HQ4X_PIXEL12_RGB_31
                        HQ4X_PIXEL13_RGB_31
                        HQ4X_PIXEL20_RGB_82
                        HQ4X_PIXEL21_RGB_32
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL22_RGB_30
                            HQ4X_PIXEL23_RGB_10
                            HQ4X_PIXEL32_RGB_10
                            HQ4X_PIXEL33_RGB_80
                        }
                        else
                        {
                            HQ4X_PIXEL22_RGB_0
                            HQ4X_PIXEL23_RGB_11
                            HQ4X_PIXEL32_RGB_12
                            HQ4X_PIXEL33_RGB_20
                        }
                        HQ4X_PIXEL30_RGB_82
                        HQ4X_PIXEL31_RGB_32
                        break;
                    }
                case 189:
                    {
                        HQ4X_PIXEL00_RGB_82
                        HQ4X_PIXEL01_RGB_82
                        HQ4X_PIXEL02_RGB_81
                        HQ4X_PIXEL03_RGB_81
                        HQ4X_PIXEL10_RGB_32
                        HQ4X_PIXEL11_RGB_32
                        HQ4X_PIXEL12_RGB_31
                        HQ4X_PIXEL13_RGB_31
                        HQ4X_PIXEL20_RGB_31
                        HQ4X_PIXEL21_RGB_31
                        HQ4X_PIXEL22_RGB_32
                        HQ4X_PIXEL23_RGB_32
                        HQ4X_PIXEL30_RGB_81
                        HQ4X_PIXEL31_RGB_81
                        HQ4X_PIXEL32_RGB_82
                        HQ4X_PIXEL33_RGB_82
                        break;
                    }
                case 231:
                    {
                        HQ4X_PIXEL00_RGB_81
                        HQ4X_PIXEL01_RGB_31
                        HQ4X_PIXEL02_RGB_32
                        HQ4X_PIXEL03_RGB_82
                        HQ4X_PIXEL10_RGB_81
                        HQ4X_PIXEL11_RGB_31
                        HQ4X_PIXEL12_RGB_32
                        HQ4X_PIXEL13_RGB_82
                        HQ4X_PIXEL20_RGB_82
                        HQ4X_PIXEL21_RGB_32
                        HQ4X_PIXEL22_RGB_31
                        HQ4X_PIXEL23_RGB_81
                        HQ4X_PIXEL30_RGB_82
                        HQ4X_PIXEL31_RGB_32
                        HQ4X_PIXEL32_RGB_31
                        HQ4X_PIXEL33_RGB_81
                        break;
                    }
                case 126:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_0
                            HQ4X_PIXEL03_RGB_0
                            HQ4X_PIXEL13_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_50
                            HQ4X_PIXEL03_RGB_50
                            HQ4X_PIXEL13_RGB_50
                        }
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_0
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_0
                            HQ4X_PIXEL30_RGB_0
                            HQ4X_PIXEL31_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_50
                            HQ4X_PIXEL30_RGB_50
                            HQ4X_PIXEL31_RGB_50
                        }
                        HQ4X_PIXEL21_RGB_0
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 219:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                            HQ4X_PIXEL01_RGB_0
                            HQ4X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_50
                            HQ4X_PIXEL01_RGB_50
                            HQ4X_PIXEL10_RGB_50
                        }
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL11_RGB_0
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL23_RGB_0
                            HQ4X_PIXEL32_RGB_0
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL23_RGB_50
                            HQ4X_PIXEL32_RGB_50
                            HQ4X_PIXEL33_RGB_50
                        }
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        break;
                    }
                case 125:
                    {
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL00_RGB_82
                            HQ4X_PIXEL10_RGB_32
                            HQ4X_PIXEL20_RGB_0
                            HQ4X_PIXEL21_RGB_0
                            HQ4X_PIXEL30_RGB_0
                            HQ4X_PIXEL31_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_11
                            HQ4X_PIXEL10_RGB_13
                            HQ4X_PIXEL20_RGB_83
                            HQ4X_PIXEL21_RGB_70
                            HQ4X_PIXEL30_RGB_50
                            HQ4X_PIXEL31_RGB_21
                        }
                        HQ4X_PIXEL01_RGB_82
                        HQ4X_PIXEL02_RGB_81
                        HQ4X_PIXEL03_RGB_81
                        HQ4X_PIXEL11_RGB_32
                        HQ4X_PIXEL12_RGB_31
                        HQ4X_PIXEL13_RGB_31
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 221:
                    {
                        HQ4X_PIXEL00_RGB_82
                        HQ4X_PIXEL01_RGB_82
                        HQ4X_PIXEL02_RGB_81
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL03_RGB_81
                            HQ4X_PIXEL13_RGB_31
                            HQ4X_PIXEL22_RGB_0
                            HQ4X_PIXEL23_RGB_0
                            HQ4X_PIXEL32_RGB_0
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL03_RGB_12
                            HQ4X_PIXEL13_RGB_14
                            HQ4X_PIXEL22_RGB_70
                            HQ4X_PIXEL23_RGB_83
                            HQ4X_PIXEL32_RGB_21
                            HQ4X_PIXEL33_RGB_50
                        }
                        HQ4X_PIXEL10_RGB_32
                        HQ4X_PIXEL11_RGB_32
                        HQ4X_PIXEL12_RGB_31
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        break;
                    }
                case 207:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                            HQ4X_PIXEL01_RGB_0
                            HQ4X_PIXEL02_RGB_32
                            HQ4X_PIXEL03_RGB_82
                            HQ4X_PIXEL10_RGB_0
                            HQ4X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_50
                            HQ4X_PIXEL01_RGB_83
                            HQ4X_PIXEL02_RGB_13
                            HQ4X_PIXEL03_RGB_11
                            HQ4X_PIXEL10_RGB_21
                            HQ4X_PIXEL11_RGB_70
                        }
                        HQ4X_PIXEL12_RGB_32
                        HQ4X_PIXEL13_RGB_82
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_31
                        HQ4X_PIXEL23_RGB_81
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        HQ4X_PIXEL32_RGB_31
                        HQ4X_PIXEL33_RGB_81
                        break;
                    }
                case 238:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        HQ4X_PIXEL02_RGB_32
                        HQ4X_PIXEL03_RGB_82
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_32
                        HQ4X_PIXEL13_RGB_82
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_0
                            HQ4X_PIXEL21_RGB_0
                            HQ4X_PIXEL30_RGB_0
                            HQ4X_PIXEL31_RGB_0
                            HQ4X_PIXEL32_RGB_31
                            HQ4X_PIXEL33_RGB_81
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_21
                            HQ4X_PIXEL21_RGB_70
                            HQ4X_PIXEL30_RGB_50
                            HQ4X_PIXEL31_RGB_83
                            HQ4X_PIXEL32_RGB_14
                            HQ4X_PIXEL33_RGB_12
                        }
                        HQ4X_PIXEL22_RGB_31
                        HQ4X_PIXEL23_RGB_81
                        break;
                    }
                case 190:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_0
                            HQ4X_PIXEL03_RGB_0
                            HQ4X_PIXEL12_RGB_0
                            HQ4X_PIXEL13_RGB_0
                            HQ4X_PIXEL23_RGB_32
                            HQ4X_PIXEL33_RGB_82
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_21
                            HQ4X_PIXEL03_RGB_50
                            HQ4X_PIXEL12_RGB_70
                            HQ4X_PIXEL13_RGB_83
                            HQ4X_PIXEL23_RGB_13
                            HQ4X_PIXEL33_RGB_11
                        }
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL20_RGB_31
                        HQ4X_PIXEL21_RGB_31
                        HQ4X_PIXEL22_RGB_32
                        HQ4X_PIXEL30_RGB_81
                        HQ4X_PIXEL31_RGB_81
                        HQ4X_PIXEL32_RGB_82
                        break;
                    }
                case 187:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                            HQ4X_PIXEL01_RGB_0
                            HQ4X_PIXEL10_RGB_0
                            HQ4X_PIXEL11_RGB_0
                            HQ4X_PIXEL20_RGB_31
                            HQ4X_PIXEL30_RGB_81
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_50
                            HQ4X_PIXEL01_RGB_21
                            HQ4X_PIXEL10_RGB_83
                            HQ4X_PIXEL11_RGB_70
                            HQ4X_PIXEL20_RGB_14
                            HQ4X_PIXEL30_RGB_12
                        }
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL21_RGB_31
                        HQ4X_PIXEL22_RGB_32
                        HQ4X_PIXEL23_RGB_32
                        HQ4X_PIXEL31_RGB_81
                        HQ4X_PIXEL32_RGB_82
                        HQ4X_PIXEL33_RGB_82
                        break;
                    }
                case 243:
                    {
                        HQ4X_PIXEL00_RGB_81
                        HQ4X_PIXEL01_RGB_31
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_81
                        HQ4X_PIXEL11_RGB_31
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL20_RGB_82
                        HQ4X_PIXEL21_RGB_32
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL22_RGB_0
                            HQ4X_PIXEL23_RGB_0
                            HQ4X_PIXEL30_RGB_82
                            HQ4X_PIXEL31_RGB_32
                            HQ4X_PIXEL32_RGB_0
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL22_RGB_70
                            HQ4X_PIXEL23_RGB_21
                            HQ4X_PIXEL30_RGB_11
                            HQ4X_PIXEL31_RGB_13
                            HQ4X_PIXEL32_RGB_83
                            HQ4X_PIXEL33_RGB_50
                        }
                        break;
                    }
                case 119:
                    {
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL00_RGB_81
                            HQ4X_PIXEL01_RGB_31
                            HQ4X_PIXEL02_RGB_0
                            HQ4X_PIXEL03_RGB_0
                            HQ4X_PIXEL12_RGB_0
                            HQ4X_PIXEL13_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_12
                            HQ4X_PIXEL01_RGB_14
                            HQ4X_PIXEL02_RGB_83
                            HQ4X_PIXEL03_RGB_50
                            HQ4X_PIXEL12_RGB_70
                            HQ4X_PIXEL13_RGB_21
                        }
                        HQ4X_PIXEL10_RGB_81
                        HQ4X_PIXEL11_RGB_31
                        HQ4X_PIXEL20_RGB_82
                        HQ4X_PIXEL21_RGB_32
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_82
                        HQ4X_PIXEL31_RGB_32
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 237:
                case 233:
                    {
                        HQ4X_PIXEL00_RGB_82
                        HQ4X_PIXEL01_RGB_82
                        HQ4X_PIXEL02_RGB_60
                        HQ4X_PIXEL03_RGB_20
                        HQ4X_PIXEL10_RGB_32
                        HQ4X_PIXEL11_RGB_32
                        HQ4X_PIXEL12_RGB_70
                        HQ4X_PIXEL13_RGB_60
                        HQ4X_PIXEL20_RGB_0
                        HQ4X_PIXEL21_RGB_0
                        HQ4X_PIXEL22_RGB_31
                        HQ4X_PIXEL23_RGB_81
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL30_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL30_RGB_20
                        }
                        HQ4X_PIXEL31_RGB_0
                        HQ4X_PIXEL32_RGB_31
                        HQ4X_PIXEL33_RGB_81
                        break;
                    }
                case 175:
                case 47:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_20
                        }
                        HQ4X_PIXEL01_RGB_0
                        HQ4X_PIXEL02_RGB_32
                        HQ4X_PIXEL03_RGB_82
                        HQ4X_PIXEL10_RGB_0
                        HQ4X_PIXEL11_RGB_0
                        HQ4X_PIXEL12_RGB_32
                        HQ4X_PIXEL13_RGB_82
                        HQ4X_PIXEL20_RGB_31
                        HQ4X_PIXEL21_RGB_31
                        HQ4X_PIXEL22_RGB_70
                        HQ4X_PIXEL23_RGB_60
                        HQ4X_PIXEL30_RGB_81
                        HQ4X_PIXEL31_RGB_81
                        HQ4X_PIXEL32_RGB_60
                        HQ4X_PIXEL33_RGB_20
                        break;
                    }
                case 183:
                case 151:
                    {
                        HQ4X_PIXEL00_RGB_81
                        HQ4X_PIXEL01_RGB_31
                        HQ4X_PIXEL02_RGB_0
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL03_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL03_RGB_20
                        }
                        HQ4X_PIXEL10_RGB_81
                        HQ4X_PIXEL11_RGB_31
                        HQ4X_PIXEL12_RGB_0
                        HQ4X_PIXEL13_RGB_0
                        HQ4X_PIXEL20_RGB_60
                        HQ4X_PIXEL21_RGB_70
                        HQ4X_PIXEL22_RGB_32
                        HQ4X_PIXEL23_RGB_32
                        HQ4X_PIXEL30_RGB_20
                        HQ4X_PIXEL31_RGB_60
                        HQ4X_PIXEL32_RGB_82
                        HQ4X_PIXEL33_RGB_82
                        break;
                    }
                case 245:
                case 244:
                    {
                        HQ4X_PIXEL00_RGB_20
                        HQ4X_PIXEL01_RGB_60
                        HQ4X_PIXEL02_RGB_81
                        HQ4X_PIXEL03_RGB_81
                        HQ4X_PIXEL10_RGB_60
                        HQ4X_PIXEL11_RGB_70
                        HQ4X_PIXEL12_RGB_31
                        HQ4X_PIXEL13_RGB_31
                        HQ4X_PIXEL20_RGB_82
                        HQ4X_PIXEL21_RGB_32
                        HQ4X_PIXEL22_RGB_0
                        HQ4X_PIXEL23_RGB_0
                        HQ4X_PIXEL30_RGB_82
                        HQ4X_PIXEL31_RGB_32
                        HQ4X_PIXEL32_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL33_RGB_20
                        }
                        break;
                    }
                case 250:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_0
                            HQ4X_PIXEL30_RGB_0
                            HQ4X_PIXEL31_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_50
                            HQ4X_PIXEL30_RGB_50
                            HQ4X_PIXEL31_RGB_50
                        }
                        HQ4X_PIXEL21_RGB_0
                        HQ4X_PIXEL22_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL23_RGB_0
                            HQ4X_PIXEL32_RGB_0
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL23_RGB_50
                            HQ4X_PIXEL32_RGB_50
                            HQ4X_PIXEL33_RGB_50
                        }
                        break;
                    }
                case 123:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                            HQ4X_PIXEL01_RGB_0
                            HQ4X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_50
                            HQ4X_PIXEL01_RGB_50
                            HQ4X_PIXEL10_RGB_50
                        }
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL11_RGB_0
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_0
                            HQ4X_PIXEL30_RGB_0
                            HQ4X_PIXEL31_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_50
                            HQ4X_PIXEL30_RGB_50
                            HQ4X_PIXEL31_RGB_50
                        }
                        HQ4X_PIXEL21_RGB_0
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 95:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                            HQ4X_PIXEL01_RGB_0
                            HQ4X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_50
                            HQ4X_PIXEL01_RGB_50
                            HQ4X_PIXEL10_RGB_50
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_0
                            HQ4X_PIXEL03_RGB_0
                            HQ4X_PIXEL13_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_50
                            HQ4X_PIXEL03_RGB_50
                            HQ4X_PIXEL13_RGB_50
                        }
                        HQ4X_PIXEL11_RGB_0
                        HQ4X_PIXEL12_RGB_0
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 222:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_0
                            HQ4X_PIXEL03_RGB_0
                            HQ4X_PIXEL13_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_50
                            HQ4X_PIXEL03_RGB_50
                            HQ4X_PIXEL13_RGB_50
                        }
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_0
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL23_RGB_0
                            HQ4X_PIXEL32_RGB_0
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL23_RGB_50
                            HQ4X_PIXEL32_RGB_50
                            HQ4X_PIXEL33_RGB_50
                        }
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        break;
                    }
                case 252:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_61
                        HQ4X_PIXEL02_RGB_81
                        HQ4X_PIXEL03_RGB_81
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_31
                        HQ4X_PIXEL13_RGB_31
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_0
                            HQ4X_PIXEL30_RGB_0
                            HQ4X_PIXEL31_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_50
                            HQ4X_PIXEL30_RGB_50
                            HQ4X_PIXEL31_RGB_50
                        }
                        HQ4X_PIXEL21_RGB_0
                        HQ4X_PIXEL22_RGB_0
                        HQ4X_PIXEL23_RGB_0
                        HQ4X_PIXEL32_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL33_RGB_20
                        }
                        break;
                    }
                case 249:
                    {
                        HQ4X_PIXEL00_RGB_82
                        HQ4X_PIXEL01_RGB_82
                        HQ4X_PIXEL02_RGB_61
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL10_RGB_32
                        HQ4X_PIXEL11_RGB_32
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL20_RGB_0
                        HQ4X_PIXEL21_RGB_0
                        HQ4X_PIXEL22_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL23_RGB_0
                            HQ4X_PIXEL32_RGB_0
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL23_RGB_50
                            HQ4X_PIXEL32_RGB_50
                            HQ4X_PIXEL33_RGB_50
                        }
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL30_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL30_RGB_20
                        }
                        HQ4X_PIXEL31_RGB_0
                        break;
                    }
                case 235:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                            HQ4X_PIXEL01_RGB_0
                            HQ4X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_50
                            HQ4X_PIXEL01_RGB_50
                            HQ4X_PIXEL10_RGB_50
                        }
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL11_RGB_0
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_61
                        HQ4X_PIXEL20_RGB_0
                        HQ4X_PIXEL21_RGB_0
                        HQ4X_PIXEL22_RGB_31
                        HQ4X_PIXEL23_RGB_81
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL30_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL30_RGB_20
                        }
                        HQ4X_PIXEL31_RGB_0
                        HQ4X_PIXEL32_RGB_31
                        HQ4X_PIXEL33_RGB_81
                        break;
                    }
                case 111:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_20
                        }
                        HQ4X_PIXEL01_RGB_0
                        HQ4X_PIXEL02_RGB_32
                        HQ4X_PIXEL03_RGB_82
                        HQ4X_PIXEL10_RGB_0
                        HQ4X_PIXEL11_RGB_0
                        HQ4X_PIXEL12_RGB_32
                        HQ4X_PIXEL13_RGB_82
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_0
                            HQ4X_PIXEL30_RGB_0
                            HQ4X_PIXEL31_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_50
                            HQ4X_PIXEL30_RGB_50
                            HQ4X_PIXEL31_RGB_50
                        }
                        HQ4X_PIXEL21_RGB_0
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_61
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 63:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_20
                        }
                        HQ4X_PIXEL01_RGB_0
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_0
                            HQ4X_PIXEL03_RGB_0
                            HQ4X_PIXEL13_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_50
                            HQ4X_PIXEL03_RGB_50
                            HQ4X_PIXEL13_RGB_50
                        }
                        HQ4X_PIXEL10_RGB_0
                        HQ4X_PIXEL11_RGB_0
                        HQ4X_PIXEL12_RGB_0
                        HQ4X_PIXEL20_RGB_31
                        HQ4X_PIXEL21_RGB_31
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL30_RGB_81
                        HQ4X_PIXEL31_RGB_81
                        HQ4X_PIXEL32_RGB_61
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 159:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                            HQ4X_PIXEL01_RGB_0
                            HQ4X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_50
                            HQ4X_PIXEL01_RGB_50
                            HQ4X_PIXEL10_RGB_50
                        }
                        HQ4X_PIXEL02_RGB_0
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL03_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL03_RGB_20
                        }
                        HQ4X_PIXEL11_RGB_0
                        HQ4X_PIXEL12_RGB_0
                        HQ4X_PIXEL13_RGB_0
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_32
                        HQ4X_PIXEL23_RGB_32
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_61
                        HQ4X_PIXEL32_RGB_82
                        HQ4X_PIXEL33_RGB_82
                        break;
                    }
                case 215:
                    {
                        HQ4X_PIXEL00_RGB_81
                        HQ4X_PIXEL01_RGB_31
                        HQ4X_PIXEL02_RGB_0
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL03_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL03_RGB_20
                        }
                        HQ4X_PIXEL10_RGB_81
                        HQ4X_PIXEL11_RGB_31
                        HQ4X_PIXEL12_RGB_0
                        HQ4X_PIXEL13_RGB_0
                        HQ4X_PIXEL20_RGB_61
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL23_RGB_0
                            HQ4X_PIXEL32_RGB_0
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL23_RGB_50
                            HQ4X_PIXEL32_RGB_50
                            HQ4X_PIXEL33_RGB_50
                        }
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        break;
                    }
                case 246:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_0
                            HQ4X_PIXEL03_RGB_0
                            HQ4X_PIXEL13_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_50
                            HQ4X_PIXEL03_RGB_50
                            HQ4X_PIXEL13_RGB_50
                        }
                        HQ4X_PIXEL10_RGB_61
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_0
                        HQ4X_PIXEL20_RGB_82
                        HQ4X_PIXEL21_RGB_32
                        HQ4X_PIXEL22_RGB_0
                        HQ4X_PIXEL23_RGB_0
                        HQ4X_PIXEL30_RGB_82
                        HQ4X_PIXEL31_RGB_32
                        HQ4X_PIXEL32_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL33_RGB_20
                        }
                        break;
                    }
                case 254:
                    {
                        HQ4X_PIXEL00_RGB_80
                        HQ4X_PIXEL01_RGB_10
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_0
                            HQ4X_PIXEL03_RGB_0
                            HQ4X_PIXEL13_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_50
                            HQ4X_PIXEL03_RGB_50
                            HQ4X_PIXEL13_RGB_50
                        }
                        HQ4X_PIXEL10_RGB_10
                        HQ4X_PIXEL11_RGB_30
                        HQ4X_PIXEL12_RGB_0
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_0
                            HQ4X_PIXEL30_RGB_0
                            HQ4X_PIXEL31_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_50
                            HQ4X_PIXEL30_RGB_50
                            HQ4X_PIXEL31_RGB_50
                        }
                        HQ4X_PIXEL21_RGB_0
                        HQ4X_PIXEL22_RGB_0
                        HQ4X_PIXEL23_RGB_0
                        HQ4X_PIXEL32_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL33_RGB_20
                        }
                        break;
                    }
                case 253:
                    {
                        HQ4X_PIXEL00_RGB_82
                        HQ4X_PIXEL01_RGB_82
                        HQ4X_PIXEL02_RGB_81
                        HQ4X_PIXEL03_RGB_81
                        HQ4X_PIXEL10_RGB_32
                        HQ4X_PIXEL11_RGB_32
                        HQ4X_PIXEL12_RGB_31
                        HQ4X_PIXEL13_RGB_31
                        HQ4X_PIXEL20_RGB_0
                        HQ4X_PIXEL21_RGB_0
                        HQ4X_PIXEL22_RGB_0
                        HQ4X_PIXEL23_RGB_0
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL30_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL30_RGB_20
                        }
                        HQ4X_PIXEL31_RGB_0
                        HQ4X_PIXEL32_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL33_RGB_20
                        }
                        break;
                    }
                case 251:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                            HQ4X_PIXEL01_RGB_0
                            HQ4X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_50
                            HQ4X_PIXEL01_RGB_50
                            HQ4X_PIXEL10_RGB_50
                        }
                        HQ4X_PIXEL02_RGB_10
                        HQ4X_PIXEL03_RGB_80
                        HQ4X_PIXEL11_RGB_0
                        HQ4X_PIXEL12_RGB_30
                        HQ4X_PIXEL13_RGB_10
                        HQ4X_PIXEL20_RGB_0
                        HQ4X_PIXEL21_RGB_0
                        HQ4X_PIXEL22_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL23_RGB_0
                            HQ4X_PIXEL32_RGB_0
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL23_RGB_50
                            HQ4X_PIXEL32_RGB_50
                            HQ4X_PIXEL33_RGB_50
                        }
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL30_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL30_RGB_20
                        }
                        HQ4X_PIXEL31_RGB_0
                        break;
                    }
                case 239:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_20
                        }
                        HQ4X_PIXEL01_RGB_0
                        HQ4X_PIXEL02_RGB_32
                        HQ4X_PIXEL03_RGB_82
                        HQ4X_PIXEL10_RGB_0
                        HQ4X_PIXEL11_RGB_0
                        HQ4X_PIXEL12_RGB_32
                        HQ4X_PIXEL13_RGB_82
                        HQ4X_PIXEL20_RGB_0
                        HQ4X_PIXEL21_RGB_0
                        HQ4X_PIXEL22_RGB_31
                        HQ4X_PIXEL23_RGB_81
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL30_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL30_RGB_20
                        }
                        HQ4X_PIXEL31_RGB_0
                        HQ4X_PIXEL32_RGB_31
                        HQ4X_PIXEL33_RGB_81
                        break;
                    }
                case 127:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_20
                        }
                        HQ4X_PIXEL01_RGB_0
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL02_RGB_0
                            HQ4X_PIXEL03_RGB_0
                            HQ4X_PIXEL13_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL02_RGB_50
                            HQ4X_PIXEL03_RGB_50
                            HQ4X_PIXEL13_RGB_50
                        }
                        HQ4X_PIXEL10_RGB_0
                        HQ4X_PIXEL11_RGB_0
                        HQ4X_PIXEL12_RGB_0
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL20_RGB_0
                            HQ4X_PIXEL30_RGB_0
                            HQ4X_PIXEL31_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL20_RGB_50
                            HQ4X_PIXEL30_RGB_50
                            HQ4X_PIXEL31_RGB_50
                        }
                        HQ4X_PIXEL21_RGB_0
                        HQ4X_PIXEL22_RGB_30
                        HQ4X_PIXEL23_RGB_10
                        HQ4X_PIXEL32_RGB_10
                        HQ4X_PIXEL33_RGB_80
                        break;
                    }
                case 191:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_20
                        }
                        HQ4X_PIXEL01_RGB_0
                        HQ4X_PIXEL02_RGB_0
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL03_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL03_RGB_20
                        }
                        HQ4X_PIXEL10_RGB_0
                        HQ4X_PIXEL11_RGB_0
                        HQ4X_PIXEL12_RGB_0
                        HQ4X_PIXEL13_RGB_0
                        HQ4X_PIXEL20_RGB_31
                        HQ4X_PIXEL21_RGB_31
                        HQ4X_PIXEL22_RGB_32
                        HQ4X_PIXEL23_RGB_32
                        HQ4X_PIXEL30_RGB_81
                        HQ4X_PIXEL31_RGB_81
                        HQ4X_PIXEL32_RGB_82
                        HQ4X_PIXEL33_RGB_82
                        break;
                    }
                case 223:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                            HQ4X_PIXEL01_RGB_0
                            HQ4X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_50
                            HQ4X_PIXEL01_RGB_50
                            HQ4X_PIXEL10_RGB_50
                        }
                        HQ4X_PIXEL02_RGB_0
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL03_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL03_RGB_20
                        }
                        HQ4X_PIXEL11_RGB_0
                        HQ4X_PIXEL12_RGB_0
                        HQ4X_PIXEL13_RGB_0
                        HQ4X_PIXEL20_RGB_10
                        HQ4X_PIXEL21_RGB_30
                        HQ4X_PIXEL22_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL23_RGB_0
                            HQ4X_PIXEL32_RGB_0
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL23_RGB_50
                            HQ4X_PIXEL32_RGB_50
                            HQ4X_PIXEL33_RGB_50
                        }
                        HQ4X_PIXEL30_RGB_80
                        HQ4X_PIXEL31_RGB_10
                        break;
                    }
                case 247:
                    {
                        HQ4X_PIXEL00_RGB_81
                        HQ4X_PIXEL01_RGB_31
                        HQ4X_PIXEL02_RGB_0
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL03_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL03_RGB_20
                        }
                        HQ4X_PIXEL10_RGB_81
                        HQ4X_PIXEL11_RGB_31
                        HQ4X_PIXEL12_RGB_0
                        HQ4X_PIXEL13_RGB_0
                        HQ4X_PIXEL20_RGB_82
                        HQ4X_PIXEL21_RGB_32
                        HQ4X_PIXEL22_RGB_0
                        HQ4X_PIXEL23_RGB_0
                        HQ4X_PIXEL30_RGB_82
                        HQ4X_PIXEL31_RGB_32
                        HQ4X_PIXEL32_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL33_RGB_20
                        }
                        break;
                    }
                case 255:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ4X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL00_RGB_20
                        }
                        HQ4X_PIXEL01_RGB_0
                        HQ4X_PIXEL02_RGB_0
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ4X_PIXEL03_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL03_RGB_20
                        }
                        HQ4X_PIXEL10_RGB_0
                        HQ4X_PIXEL11_RGB_0
                        HQ4X_PIXEL12_RGB_0
                        HQ4X_PIXEL13_RGB_0
                        HQ4X_PIXEL20_RGB_0
                        HQ4X_PIXEL21_RGB_0
                        HQ4X_PIXEL22_RGB_0
                        HQ4X_PIXEL23_RGB_0
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ4X_PIXEL30_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL30_RGB_20
                        }
                        HQ4X_PIXEL31_RGB_0
                        HQ4X_PIXEL32_RGB_0
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ4X_PIXEL33_RGB_0
                        }
                        else
                        {
                            HQ4X_PIXEL33_RGB_20
                        }
                        break;
                    }
            }

            BmpBufX_[P + 2] = R00;
            BmpBufX_[P + 1] = G00;
            BmpBufX_[P + 0] = B00;
            BmpBufX_[L + P + 2] = R10;
            BmpBufX_[L + P + 1] = G10;
            BmpBufX_[L + P + 0] = B10;
            BmpBufX_[LL + P + 2] = R20;
            BmpBufX_[LL + P + 1] = G20;
            BmpBufX_[LL + P + 0] = B20;
            BmpBufX_[LLL + P + 2] = R30;
            BmpBufX_[LLL + P + 1] = G30;
            BmpBufX_[LLL + P + 0] = B30;

            BmpBufX_[P + 4 + 2] = R01;
            BmpBufX_[P + 4 + 1] = G01;
            BmpBufX_[P + 4 + 0] = B01;
            BmpBufX_[L + 4 + P + 2] = R11;
            BmpBufX_[L + 4 + P + 1] = G11;
            BmpBufX_[L + 4 + P + 0] = B11;
            BmpBufX_[LL + 4 + P + 2] = R21;
            BmpBufX_[LL + 4 + P + 1] = G21;
            BmpBufX_[LL + 4 + P + 0] = B21;
            BmpBufX_[LLL + 4 + P + 2] = R31;
            BmpBufX_[LLL + 4 + P + 1] = G31;
            BmpBufX_[LLL + 4 + P + 0] = B31;

            BmpBufX_[P + 8 + 2] = R02;
            BmpBufX_[P + 8 + 1] = G02;
            BmpBufX_[P + 8 + 0] = B02;
            BmpBufX_[L + 8 + P + 2] = R12;
            BmpBufX_[L + 8 + P + 1] = G12;
            BmpBufX_[L + 8 + P + 0] = B12;
            BmpBufX_[LL + 8 + P + 2] = R22;
            BmpBufX_[LL + 8 + P + 1] = G22;
            BmpBufX_[LL + 8 + P + 0] = B22;
            BmpBufX_[LLL + 8 + P + 2] = R32;
            BmpBufX_[LLL + 8 + P + 1] = G32;
            BmpBufX_[LLL + 8 + P + 0] = B32;

            BmpBufX_[P + 12 + 2] = R03;
            BmpBufX_[P + 12 + 1] = G03;
            BmpBufX_[P + 12 + 0] = B03;
            BmpBufX_[L + 12 + P + 2] = R13;
            BmpBufX_[L + 12 + P + 1] = G13;
            BmpBufX_[L + 12 + P + 0] = B13;
            BmpBufX_[LL + 12 + P + 2] = R23;
            BmpBufX_[LL + 12 + P + 1] = G23;
            BmpBufX_[LL + 12 + P + 0] = B23;
            BmpBufX_[LLL + 12 + P + 2] = R33;
            BmpBufX_[LLL + 12 + P + 1] = G33;
            BmpBufX_[LLL + 12 + P + 0] = B33;
            P += 16;
        }
        P += LLL;
    }
}

void PicThread::HQ4X_Process2(uchar * BmpBuf_, uchar * BmpBufX_, int MinY, int MaxY, int PicW_, int PicH_, int &P, int L)
{
    int LL = L << 1;
    int LLL = LL + L;
    int X, Y;
    int XW, XE, YN, YS;
    int PicW_1 = PicW_ - 1;
    int PicH_1 = PicH_ - 1;
    int W1R, W1G, W1B, W2R, W2G, W2B, W3R, W3G, W3B;
    int W4R, W4G, W4B, W5R, W5G, W5B, W6R, W6G, W6B;
    int W7R, W7G, W7B, W8R, W8G, W8B, W9R, W9G, W9B;
    int W1, W2, W3, W4, W5, W6, W7, W8, W9;
    int C00, C01, C02, C03, C10, C11, C12, C13, C20, C21, C22, C23, C30, C31, C32, C33;
    int C;
    int PicP;
    for (Y = MinY; Y < MaxY; Y++)
    {
        YN = Max(Y - 1, 0);
        YS = Min(Y + 1, PicH_1);
        for (X = 0; X < PicW_; X++)
        {
            XW = Max(X - 1, 0);
            XE = Min(X + 1, PicW_1);

            PicP = ((YN * PicW_) + XW) << 2;
            W1R = BmpBuf_[PicP + 2];
            W1G = BmpBuf_[PicP + 1];
            W1B = BmpBuf_[PicP + 0];

            PicP = ((YN * PicW_) + X) << 2;
            W2R = BmpBuf_[PicP + 2];
            W2G = BmpBuf_[PicP + 1];
            W2B = BmpBuf_[PicP + 0];

            PicP = ((YN * PicW_) + XE) << 2;
            W3R = BmpBuf_[PicP + 2];
            W3G = BmpBuf_[PicP + 1];
            W3B = BmpBuf_[PicP + 0];

            PicP = ((Y * PicW_) + XW) << 2;
            W4R = BmpBuf_[PicP + 2];
            W4G = BmpBuf_[PicP + 1];
            W4B = BmpBuf_[PicP + 0];

            PicP = ((Y * PicW_) + X) << 2;
            W5R = BmpBuf_[PicP + 2];
            W5G = BmpBuf_[PicP + 1];
            W5B = BmpBuf_[PicP + 0];

            PicP = ((Y * PicW_) + XE) << 2;
            W6R = BmpBuf_[PicP + 2];
            W6G = BmpBuf_[PicP + 1];
            W6B = BmpBuf_[PicP + 0];

            PicP = ((YS * PicW_) + XW) << 2;
            W7R = BmpBuf_[PicP + 2];
            W7G = BmpBuf_[PicP + 1];
            W7B = BmpBuf_[PicP + 0];

            PicP = ((YS * PicW_) + X) << 2;
            W8R = BmpBuf_[PicP + 2];
            W8G = BmpBuf_[PicP + 1];
            W8B = BmpBuf_[PicP + 0];

            PicP = ((YS * PicW_) + XE) << 2;
            W9R = BmpBuf_[PicP + 2];
            W9G = BmpBuf_[PicP + 1];
            W9B = BmpBuf_[PicP + 0];

            for (C = 0; C < 3; C++)
            {
                switch (C)
                {
                    case 0:
                        W1 = W1R;
                        W2 = W2R;
                        W3 = W3R;
                        W4 = W4R;
                        W5 = W5R;
                        W6 = W6R;
                        W7 = W7R;
                        W8 = W8R;
                        W9 = W9R;
                        break;
                    case 1:
                        W1 = W1G;
                        W2 = W2G;
                        W3 = W3G;
                        W4 = W4G;
                        W5 = W5G;
                        W6 = W6G;
                        W7 = W7G;
                        W8 = W8G;
                        W9 = W9G;
                        break;
                    case 2:
                        W1 = W1B;
                        W2 = W2B;
                        W3 = W3B;
                        W4 = W4B;
                        W5 = W5B;
                        W6 = W6B;
                        W7 = W7B;
                        W8 = W8B;
                        W9 = W9B;
                        break;
                }


                int Threshold = 10;
                int Pattern = 0;
                if (abs(W5 - W1) > Threshold) { Pattern += 1; }
                if (abs(W5 - W2) > Threshold) { Pattern += 2; }
                if (abs(W5 - W3) > Threshold) { Pattern += 4; }
                if (abs(W5 - W4) > Threshold) { Pattern += 8; }
                if (abs(W5 - W6) > Threshold) { Pattern += 16; }
                if (abs(W5 - W7) > Threshold) { Pattern += 32; }
                if (abs(W5 - W8) > Threshold) { Pattern += 64; }
                if (abs(W5 - W9) > Threshold) { Pattern += 128; }

                switch (Pattern)
                {
                    case 0:
                    case 1:
                    case 4:
                    case 32:
                    case 128:
                    case 5:
                    case 132:
                    case 160:
                    case 33:
                    case 129:
                    case 36:
                    case 133:
                    case 164:
                    case 161:
                    case 37:
                    case 165:
                        {
                            HQ4X_PIXEL00_20
                            HQ4X_PIXEL01_60
                            HQ4X_PIXEL02_60
                            HQ4X_PIXEL03_20
                            HQ4X_PIXEL10_60
                            HQ4X_PIXEL11_70
                            HQ4X_PIXEL12_70
                            HQ4X_PIXEL13_60
                            HQ4X_PIXEL20_60
                            HQ4X_PIXEL21_70
                            HQ4X_PIXEL22_70
                            HQ4X_PIXEL23_60
                            HQ4X_PIXEL30_20
                            HQ4X_PIXEL31_60
                            HQ4X_PIXEL32_60
                            HQ4X_PIXEL33_20
                            break;
                        }
                    case 2:
                    case 34:
                    case 130:
                    case 162:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_61
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_61
                            HQ4X_PIXEL20_60
                            HQ4X_PIXEL21_70
                            HQ4X_PIXEL22_70
                            HQ4X_PIXEL23_60
                            HQ4X_PIXEL30_20
                            HQ4X_PIXEL31_60
                            HQ4X_PIXEL32_60
                            HQ4X_PIXEL33_20
                            break;
                        }
                    case 16:
                    case 17:
                    case 48:
                    case 49:
                        {
                            HQ4X_PIXEL00_20
                            HQ4X_PIXEL01_60
                            HQ4X_PIXEL02_61
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_60
                            HQ4X_PIXEL11_70
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL20_60
                            HQ4X_PIXEL21_70
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_20
                            HQ4X_PIXEL31_60
                            HQ4X_PIXEL32_61
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 64:
                    case 65:
                    case 68:
                    case 69:
                        {
                            HQ4X_PIXEL00_20
                            HQ4X_PIXEL01_60
                            HQ4X_PIXEL02_60
                            HQ4X_PIXEL03_20
                            HQ4X_PIXEL10_60
                            HQ4X_PIXEL11_70
                            HQ4X_PIXEL12_70
                            HQ4X_PIXEL13_60
                            HQ4X_PIXEL20_61
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_61
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 8:
                    case 12:
                    case 136:
                    case 140:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_61
                            HQ4X_PIXEL02_60
                            HQ4X_PIXEL03_20
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_70
                            HQ4X_PIXEL13_60
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_70
                            HQ4X_PIXEL23_60
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_61
                            HQ4X_PIXEL32_60
                            HQ4X_PIXEL33_20
                            break;
                        }
                    case 3:
                    case 35:
                    case 131:
                    case 163:
                        {
                            HQ4X_PIXEL00_81
                            HQ4X_PIXEL01_31
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_81
                            HQ4X_PIXEL11_31
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_61
                            HQ4X_PIXEL20_60
                            HQ4X_PIXEL21_70
                            HQ4X_PIXEL22_70
                            HQ4X_PIXEL23_60
                            HQ4X_PIXEL30_20
                            HQ4X_PIXEL31_60
                            HQ4X_PIXEL32_60
                            HQ4X_PIXEL33_20
                            break;
                        }
                    case 6:
                    case 38:
                    case 134:
                    case 166:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            HQ4X_PIXEL02_32
                            HQ4X_PIXEL03_82
                            HQ4X_PIXEL10_61
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_32
                            HQ4X_PIXEL13_82
                            HQ4X_PIXEL20_60
                            HQ4X_PIXEL21_70
                            HQ4X_PIXEL22_70
                            HQ4X_PIXEL23_60
                            HQ4X_PIXEL30_20
                            HQ4X_PIXEL31_60
                            HQ4X_PIXEL32_60
                            HQ4X_PIXEL33_20
                            break;
                        }
                    case 20:
                    case 21:
                    case 52:
                    case 53:
                        {
                            HQ4X_PIXEL00_20
                            HQ4X_PIXEL01_60
                            HQ4X_PIXEL02_81
                            HQ4X_PIXEL03_81
                            HQ4X_PIXEL10_60
                            HQ4X_PIXEL11_70
                            HQ4X_PIXEL12_31
                            HQ4X_PIXEL13_31
                            HQ4X_PIXEL20_60
                            HQ4X_PIXEL21_70
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_20
                            HQ4X_PIXEL31_60
                            HQ4X_PIXEL32_61
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 144:
                    case 145:
                    case 176:
                    case 177:
                        {
                            HQ4X_PIXEL00_20
                            HQ4X_PIXEL01_60
                            HQ4X_PIXEL02_61
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_60
                            HQ4X_PIXEL11_70
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL20_60
                            HQ4X_PIXEL21_70
                            HQ4X_PIXEL22_32
                            HQ4X_PIXEL23_32
                            HQ4X_PIXEL30_20
                            HQ4X_PIXEL31_60
                            HQ4X_PIXEL32_82
                            HQ4X_PIXEL33_82
                            break;
                        }
                    case 192:
                    case 193:
                    case 196:
                    case 197:
                        {
                            HQ4X_PIXEL00_20
                            HQ4X_PIXEL01_60
                            HQ4X_PIXEL02_60
                            HQ4X_PIXEL03_20
                            HQ4X_PIXEL10_60
                            HQ4X_PIXEL11_70
                            HQ4X_PIXEL12_70
                            HQ4X_PIXEL13_60
                            HQ4X_PIXEL20_61
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_31
                            HQ4X_PIXEL23_81
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            HQ4X_PIXEL32_31
                            HQ4X_PIXEL33_81
                            break;
                        }
                    case 96:
                    case 97:
                    case 100:
                    case 101:
                        {
                            HQ4X_PIXEL00_20
                            HQ4X_PIXEL01_60
                            HQ4X_PIXEL02_60
                            HQ4X_PIXEL03_20
                            HQ4X_PIXEL10_60
                            HQ4X_PIXEL11_70
                            HQ4X_PIXEL12_70
                            HQ4X_PIXEL13_60
                            HQ4X_PIXEL20_82
                            HQ4X_PIXEL21_32
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_61
                            HQ4X_PIXEL30_82
                            HQ4X_PIXEL31_32
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 40:
                    case 44:
                    case 168:
                    case 172:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_61
                            HQ4X_PIXEL02_60
                            HQ4X_PIXEL03_20
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_70
                            HQ4X_PIXEL13_60
                            HQ4X_PIXEL20_31
                            HQ4X_PIXEL21_31
                            HQ4X_PIXEL22_70
                            HQ4X_PIXEL23_60
                            HQ4X_PIXEL30_81
                            HQ4X_PIXEL31_81
                            HQ4X_PIXEL32_60
                            HQ4X_PIXEL33_20
                            break;
                        }
                    case 9:
                    case 13:
                    case 137:
                    case 141:
                        {
                            HQ4X_PIXEL00_82
                            HQ4X_PIXEL01_82
                            HQ4X_PIXEL02_60
                            HQ4X_PIXEL03_20
                            HQ4X_PIXEL10_32
                            HQ4X_PIXEL11_32
                            HQ4X_PIXEL12_70
                            HQ4X_PIXEL13_60
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_70
                            HQ4X_PIXEL23_60
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_61
                            HQ4X_PIXEL32_60
                            HQ4X_PIXEL33_20
                            break;
                        }
                    case 18:
                    case 50:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_10
                                HQ4X_PIXEL03_80
                                HQ4X_PIXEL12_30
                                HQ4X_PIXEL13_10
                            }
                            else
                            {
                                HQ4X_PIXEL02_50
                                HQ4X_PIXEL03_50
                                HQ4X_PIXEL12_0
                                HQ4X_PIXEL13_50
                            }
                            HQ4X_PIXEL10_61
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL20_60
                            HQ4X_PIXEL21_70
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_20
                            HQ4X_PIXEL31_60
                            HQ4X_PIXEL32_61
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 80:
                    case 81:
                        {
                            HQ4X_PIXEL00_20
                            HQ4X_PIXEL01_60
                            HQ4X_PIXEL02_61
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_60
                            HQ4X_PIXEL11_70
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL20_61
                            HQ4X_PIXEL21_30
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL22_30
                                HQ4X_PIXEL23_10
                                HQ4X_PIXEL32_10
                                HQ4X_PIXEL33_80
                            }
                            else
                            {
                                HQ4X_PIXEL22_0
                                HQ4X_PIXEL23_50
                                HQ4X_PIXEL32_50
                                HQ4X_PIXEL33_50
                            }
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            break;
                        }
                    case 72:
                    case 76:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_61
                            HQ4X_PIXEL02_60
                            HQ4X_PIXEL03_20
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_70
                            HQ4X_PIXEL13_60
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_10
                                HQ4X_PIXEL21_30
                                HQ4X_PIXEL30_80
                                HQ4X_PIXEL31_10
                            }
                            else
                            {
                                HQ4X_PIXEL20_50
                                HQ4X_PIXEL21_0
                                HQ4X_PIXEL30_50
                                HQ4X_PIXEL31_50
                            }
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_61
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 10:
                    case 138:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_80
                                HQ4X_PIXEL01_10
                                HQ4X_PIXEL10_10
                                HQ4X_PIXEL11_30
                            }
                            else
                            {
                                HQ4X_PIXEL00_50
                                HQ4X_PIXEL01_50
                                HQ4X_PIXEL10_50
                                HQ4X_PIXEL11_0
                            }
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_61
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_70
                            HQ4X_PIXEL23_60
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_61
                            HQ4X_PIXEL32_60
                            HQ4X_PIXEL33_20
                            break;
                        }
                    case 66:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_61
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_61
                            HQ4X_PIXEL20_61
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_61
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 24:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_61
                            HQ4X_PIXEL02_61
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_61
                            HQ4X_PIXEL32_61
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 7:
                    case 39:
                    case 135:
                        {
                            HQ4X_PIXEL00_81
                            HQ4X_PIXEL01_31
                            HQ4X_PIXEL02_32
                            HQ4X_PIXEL03_82
                            HQ4X_PIXEL10_81
                            HQ4X_PIXEL11_31
                            HQ4X_PIXEL12_32
                            HQ4X_PIXEL13_82
                            HQ4X_PIXEL20_60
                            HQ4X_PIXEL21_70
                            HQ4X_PIXEL22_70
                            HQ4X_PIXEL23_60
                            HQ4X_PIXEL30_20
                            HQ4X_PIXEL31_60
                            HQ4X_PIXEL32_60
                            HQ4X_PIXEL33_20
                            break;
                        }
                    case 148:
                    case 149:
                    case 180:
                        {
                            HQ4X_PIXEL00_20
                            HQ4X_PIXEL01_60
                            HQ4X_PIXEL02_81
                            HQ4X_PIXEL03_81
                            HQ4X_PIXEL10_60
                            HQ4X_PIXEL11_70
                            HQ4X_PIXEL12_31
                            HQ4X_PIXEL13_31
                            HQ4X_PIXEL20_60
                            HQ4X_PIXEL21_70
                            HQ4X_PIXEL22_32
                            HQ4X_PIXEL23_32
                            HQ4X_PIXEL30_20
                            HQ4X_PIXEL31_60
                            HQ4X_PIXEL32_82
                            HQ4X_PIXEL33_82
                            break;
                        }
                    case 224:
                    case 228:
                    case 225:
                        {
                            HQ4X_PIXEL00_20
                            HQ4X_PIXEL01_60
                            HQ4X_PIXEL02_60
                            HQ4X_PIXEL03_20
                            HQ4X_PIXEL10_60
                            HQ4X_PIXEL11_70
                            HQ4X_PIXEL12_70
                            HQ4X_PIXEL13_60
                            HQ4X_PIXEL20_82
                            HQ4X_PIXEL21_32
                            HQ4X_PIXEL22_31
                            HQ4X_PIXEL23_81
                            HQ4X_PIXEL30_82
                            HQ4X_PIXEL31_32
                            HQ4X_PIXEL32_31
                            HQ4X_PIXEL33_81
                            break;
                        }
                    case 41:
                    case 169:
                    case 45:
                        {
                            HQ4X_PIXEL00_82
                            HQ4X_PIXEL01_82
                            HQ4X_PIXEL02_60
                            HQ4X_PIXEL03_20
                            HQ4X_PIXEL10_32
                            HQ4X_PIXEL11_32
                            HQ4X_PIXEL12_70
                            HQ4X_PIXEL13_60
                            HQ4X_PIXEL20_31
                            HQ4X_PIXEL21_31
                            HQ4X_PIXEL22_70
                            HQ4X_PIXEL23_60
                            HQ4X_PIXEL30_81
                            HQ4X_PIXEL31_81
                            HQ4X_PIXEL32_60
                            HQ4X_PIXEL33_20
                            break;
                        }
                    case 22:
                    case 54:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_0
                                HQ4X_PIXEL03_0
                                HQ4X_PIXEL13_0
                            }
                            else
                            {
                                HQ4X_PIXEL02_50
                                HQ4X_PIXEL03_50
                                HQ4X_PIXEL13_50
                            }
                            HQ4X_PIXEL10_61
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_0
                            HQ4X_PIXEL20_60
                            HQ4X_PIXEL21_70
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_20
                            HQ4X_PIXEL31_60
                            HQ4X_PIXEL32_61
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 208:
                    case 209:
                        {
                            HQ4X_PIXEL00_20
                            HQ4X_PIXEL01_60
                            HQ4X_PIXEL02_61
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_60
                            HQ4X_PIXEL11_70
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL20_61
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL23_0
                                HQ4X_PIXEL32_0
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL23_50
                                HQ4X_PIXEL32_50
                                HQ4X_PIXEL33_50
                            }
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            break;
                        }
                    case 104:
                    case 108:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_61
                            HQ4X_PIXEL02_60
                            HQ4X_PIXEL03_20
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_70
                            HQ4X_PIXEL13_60
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_0
                                HQ4X_PIXEL30_0
                                HQ4X_PIXEL31_0
                            }
                            else
                            {
                                HQ4X_PIXEL20_50
                                HQ4X_PIXEL30_50
                                HQ4X_PIXEL31_50
                            }
                            HQ4X_PIXEL21_0
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_61
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 11:
                    case 139:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                                HQ4X_PIXEL01_0
                                HQ4X_PIXEL10_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_50
                                HQ4X_PIXEL01_50
                                HQ4X_PIXEL10_50
                            }
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL11_0
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_61
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_70
                            HQ4X_PIXEL23_60
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_61
                            HQ4X_PIXEL32_60
                            HQ4X_PIXEL33_20
                            break;
                        }
                    case 19:
                    case 51:
                        {
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL00_81
                                HQ4X_PIXEL01_31
                                HQ4X_PIXEL02_10
                                HQ4X_PIXEL03_80
                                HQ4X_PIXEL12_30
                                HQ4X_PIXEL13_10
                            }
                            else
                            {
                                HQ4X_PIXEL00_12
                                HQ4X_PIXEL01_14
                                HQ4X_PIXEL02_83
                                HQ4X_PIXEL03_50
                                HQ4X_PIXEL12_70
                                HQ4X_PIXEL13_21
                            }
                            HQ4X_PIXEL10_81
                            HQ4X_PIXEL11_31
                            HQ4X_PIXEL20_60
                            HQ4X_PIXEL21_70
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_20
                            HQ4X_PIXEL31_60
                            HQ4X_PIXEL32_61
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 146:
                    case 178:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_10
                                HQ4X_PIXEL03_80
                                HQ4X_PIXEL12_30
                                HQ4X_PIXEL13_10
                                HQ4X_PIXEL23_32
                                HQ4X_PIXEL33_82
                            }
                            else
                            {
                                HQ4X_PIXEL02_21
                                HQ4X_PIXEL03_50
                                HQ4X_PIXEL12_70
                                HQ4X_PIXEL13_83
                                HQ4X_PIXEL23_13
                                HQ4X_PIXEL33_11
                            }
                            HQ4X_PIXEL10_61
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL20_60
                            HQ4X_PIXEL21_70
                            HQ4X_PIXEL22_32
                            HQ4X_PIXEL30_20
                            HQ4X_PIXEL31_60
                            HQ4X_PIXEL32_82
                            break;
                        }
                    case 84:
                    case 85:
                        {
                            HQ4X_PIXEL00_20
                            HQ4X_PIXEL01_60
                            HQ4X_PIXEL02_81
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL03_81
                                HQ4X_PIXEL13_31
                                HQ4X_PIXEL22_30
                                HQ4X_PIXEL23_10
                                HQ4X_PIXEL32_10
                                HQ4X_PIXEL33_80
                            }
                            else
                            {
                                HQ4X_PIXEL03_12
                                HQ4X_PIXEL13_14
                                HQ4X_PIXEL22_70
                                HQ4X_PIXEL23_83
                                HQ4X_PIXEL32_21
                                HQ4X_PIXEL33_50
                            }
                            HQ4X_PIXEL10_60
                            HQ4X_PIXEL11_70
                            HQ4X_PIXEL12_31
                            HQ4X_PIXEL20_61
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            break;
                        }
                    case 112:
                    case 113:
                        {
                            HQ4X_PIXEL00_20
                            HQ4X_PIXEL01_60
                            HQ4X_PIXEL02_61
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_60
                            HQ4X_PIXEL11_70
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL20_82
                            HQ4X_PIXEL21_32
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL22_30
                                HQ4X_PIXEL23_10
                                HQ4X_PIXEL30_82
                                HQ4X_PIXEL31_32
                                HQ4X_PIXEL32_10
                                HQ4X_PIXEL33_80
                            }
                            else
                            {
                                HQ4X_PIXEL22_70
                                HQ4X_PIXEL23_21
                                HQ4X_PIXEL30_11
                                HQ4X_PIXEL31_13
                                HQ4X_PIXEL32_83
                                HQ4X_PIXEL33_50
                            }
                            break;
                        }
                    case 200:
                    case 204:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_61
                            HQ4X_PIXEL02_60
                            HQ4X_PIXEL03_20
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_70
                            HQ4X_PIXEL13_60
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_10
                                HQ4X_PIXEL21_30
                                HQ4X_PIXEL30_80
                                HQ4X_PIXEL31_10
                                HQ4X_PIXEL32_31
                                HQ4X_PIXEL33_81
                            }
                            else
                            {
                                HQ4X_PIXEL20_21
                                HQ4X_PIXEL21_70
                                HQ4X_PIXEL30_50
                                HQ4X_PIXEL31_83
                                HQ4X_PIXEL32_14
                                HQ4X_PIXEL33_12
                            }
                            HQ4X_PIXEL22_31
                            HQ4X_PIXEL23_81
                            break;
                        }
                    case 73:
                    case 77:
                        {
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL00_82
                                HQ4X_PIXEL10_32
                                HQ4X_PIXEL20_10
                                HQ4X_PIXEL21_30
                                HQ4X_PIXEL30_80
                                HQ4X_PIXEL31_10
                            }
                            else
                            {
                                HQ4X_PIXEL00_11
                                HQ4X_PIXEL10_13
                                HQ4X_PIXEL20_83
                                HQ4X_PIXEL21_70
                                HQ4X_PIXEL30_50
                                HQ4X_PIXEL31_21
                            }
                            HQ4X_PIXEL01_82
                            HQ4X_PIXEL02_60
                            HQ4X_PIXEL03_20
                            HQ4X_PIXEL11_32
                            HQ4X_PIXEL12_70
                            HQ4X_PIXEL13_60
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_61
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 42:
                    case 170:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_80
                                HQ4X_PIXEL01_10
                                HQ4X_PIXEL10_10
                                HQ4X_PIXEL11_30
                                HQ4X_PIXEL20_31
                                HQ4X_PIXEL30_81
                            }
                            else
                            {
                                HQ4X_PIXEL00_50
                                HQ4X_PIXEL01_21
                                HQ4X_PIXEL10_83
                                HQ4X_PIXEL11_70
                                HQ4X_PIXEL20_14
                                HQ4X_PIXEL30_12
                            }
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_61
                            HQ4X_PIXEL21_31
                            HQ4X_PIXEL22_70
                            HQ4X_PIXEL23_60
                            HQ4X_PIXEL31_81
                            HQ4X_PIXEL32_60
                            HQ4X_PIXEL33_20
                            break;
                        }
                    case 14:
                    case 142:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_80
                                HQ4X_PIXEL01_10
                                HQ4X_PIXEL02_32
                                HQ4X_PIXEL03_82
                                HQ4X_PIXEL10_10
                                HQ4X_PIXEL11_30
                            }
                            else
                            {
                                HQ4X_PIXEL00_50
                                HQ4X_PIXEL01_83
                                HQ4X_PIXEL02_13
                                HQ4X_PIXEL03_11
                                HQ4X_PIXEL10_21
                                HQ4X_PIXEL11_70
                            }
                            HQ4X_PIXEL12_32
                            HQ4X_PIXEL13_82
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_70
                            HQ4X_PIXEL23_60
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_61
                            HQ4X_PIXEL32_60
                            HQ4X_PIXEL33_20
                            break;
                        }
                    case 67:
                        {
                            HQ4X_PIXEL00_81
                            HQ4X_PIXEL01_31
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_81
                            HQ4X_PIXEL11_31
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_61
                            HQ4X_PIXEL20_61
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_61
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 70:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            HQ4X_PIXEL02_32
                            HQ4X_PIXEL03_82
                            HQ4X_PIXEL10_61
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_32
                            HQ4X_PIXEL13_82
                            HQ4X_PIXEL20_61
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_61
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 28:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_61
                            HQ4X_PIXEL02_81
                            HQ4X_PIXEL03_81
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_31
                            HQ4X_PIXEL13_31
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_61
                            HQ4X_PIXEL32_61
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 152:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_61
                            HQ4X_PIXEL02_61
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_32
                            HQ4X_PIXEL23_32
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_61
                            HQ4X_PIXEL32_82
                            HQ4X_PIXEL33_82
                            break;
                        }
                    case 194:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_61
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_61
                            HQ4X_PIXEL20_61
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_31
                            HQ4X_PIXEL23_81
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            HQ4X_PIXEL32_31
                            HQ4X_PIXEL33_81
                            break;
                        }
                    case 98:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_61
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_61
                            HQ4X_PIXEL20_82
                            HQ4X_PIXEL21_32
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_61
                            HQ4X_PIXEL30_82
                            HQ4X_PIXEL31_32
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 56:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_61
                            HQ4X_PIXEL02_61
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL20_31
                            HQ4X_PIXEL21_31
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_81
                            HQ4X_PIXEL31_81
                            HQ4X_PIXEL32_61
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 25:
                        {
                            HQ4X_PIXEL00_82
                            HQ4X_PIXEL01_82
                            HQ4X_PIXEL02_61
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_32
                            HQ4X_PIXEL11_32
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_61
                            HQ4X_PIXEL32_61
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 26:
                    case 31:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                                HQ4X_PIXEL01_0
                                HQ4X_PIXEL10_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_50
                                HQ4X_PIXEL01_50
                                HQ4X_PIXEL10_50
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_0
                                HQ4X_PIXEL03_0
                                HQ4X_PIXEL13_0
                            }
                            else
                            {
                                HQ4X_PIXEL02_50
                                HQ4X_PIXEL03_50
                                HQ4X_PIXEL13_50
                            }
                            HQ4X_PIXEL11_0
                            HQ4X_PIXEL12_0
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_61
                            HQ4X_PIXEL32_61
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 82:
                    case 214:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_0
                                HQ4X_PIXEL03_0
                                HQ4X_PIXEL13_0
                            }
                            else
                            {
                                HQ4X_PIXEL02_50
                                HQ4X_PIXEL03_50
                                HQ4X_PIXEL13_50
                            }
                            HQ4X_PIXEL10_61
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_0
                            HQ4X_PIXEL20_61
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL23_0
                                HQ4X_PIXEL32_0
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL23_50
                                HQ4X_PIXEL32_50
                                HQ4X_PIXEL33_50
                            }
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            break;
                        }
                    case 88:
                    case 248:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_61
                            HQ4X_PIXEL02_61
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_0
                                HQ4X_PIXEL30_0
                                HQ4X_PIXEL31_0
                            }
                            else
                            {
                                HQ4X_PIXEL20_50
                                HQ4X_PIXEL30_50
                                HQ4X_PIXEL31_50
                            }
                            HQ4X_PIXEL21_0
                            HQ4X_PIXEL22_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL23_0
                                HQ4X_PIXEL32_0
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL23_50
                                HQ4X_PIXEL32_50
                                HQ4X_PIXEL33_50
                            }
                            break;
                        }
                    case 74:
                    case 107:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                                HQ4X_PIXEL01_0
                                HQ4X_PIXEL10_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_50
                                HQ4X_PIXEL01_50
                                HQ4X_PIXEL10_50
                            }
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL11_0
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_61
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_0
                                HQ4X_PIXEL30_0
                                HQ4X_PIXEL31_0
                            }
                            else
                            {
                                HQ4X_PIXEL20_50
                                HQ4X_PIXEL30_50
                                HQ4X_PIXEL31_50
                            }
                            HQ4X_PIXEL21_0
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_61
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 27:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                                HQ4X_PIXEL01_0
                                HQ4X_PIXEL10_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_50
                                HQ4X_PIXEL01_50
                                HQ4X_PIXEL10_50
                            }
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL11_0
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_61
                            HQ4X_PIXEL32_61
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 86:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_0
                                HQ4X_PIXEL03_0
                                HQ4X_PIXEL13_0
                            }
                            else
                            {
                                HQ4X_PIXEL02_50
                                HQ4X_PIXEL03_50
                                HQ4X_PIXEL13_50
                            }
                            HQ4X_PIXEL10_61
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_0
                            HQ4X_PIXEL20_61
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 216:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_61
                            HQ4X_PIXEL02_61
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL23_0
                                HQ4X_PIXEL32_0
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL23_50
                                HQ4X_PIXEL32_50
                                HQ4X_PIXEL33_50
                            }
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            break;
                        }
                    case 106:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_61
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_0
                                HQ4X_PIXEL30_0
                                HQ4X_PIXEL31_0
                            }
                            else
                            {
                                HQ4X_PIXEL20_50
                                HQ4X_PIXEL30_50
                                HQ4X_PIXEL31_50
                            }
                            HQ4X_PIXEL21_0
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_61
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 30:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_0
                                HQ4X_PIXEL03_0
                                HQ4X_PIXEL13_0
                            }
                            else
                            {
                                HQ4X_PIXEL02_50
                                HQ4X_PIXEL03_50
                                HQ4X_PIXEL13_50
                            }
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_0
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_61
                            HQ4X_PIXEL32_61
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 210:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_61
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL20_61
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL23_0
                                HQ4X_PIXEL32_0
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL23_50
                                HQ4X_PIXEL32_50
                                HQ4X_PIXEL33_50
                            }
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            break;
                        }
                    case 120:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_61
                            HQ4X_PIXEL02_61
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_0
                                HQ4X_PIXEL30_0
                                HQ4X_PIXEL31_0
                            }
                            else
                            {
                                HQ4X_PIXEL20_50
                                HQ4X_PIXEL30_50
                                HQ4X_PIXEL31_50
                            }
                            HQ4X_PIXEL21_0
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 75:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                                HQ4X_PIXEL01_0
                                HQ4X_PIXEL10_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_50
                                HQ4X_PIXEL01_50
                                HQ4X_PIXEL10_50
                            }
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL11_0
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_61
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_61
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 29:
                        {
                            HQ4X_PIXEL00_82
                            HQ4X_PIXEL01_82
                            HQ4X_PIXEL02_81
                            HQ4X_PIXEL03_81
                            HQ4X_PIXEL10_32
                            HQ4X_PIXEL11_32
                            HQ4X_PIXEL12_31
                            HQ4X_PIXEL13_31
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_61
                            HQ4X_PIXEL32_61
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 198:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            HQ4X_PIXEL02_32
                            HQ4X_PIXEL03_82
                            HQ4X_PIXEL10_61
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_32
                            HQ4X_PIXEL13_82
                            HQ4X_PIXEL20_61
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_31
                            HQ4X_PIXEL23_81
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            HQ4X_PIXEL32_31
                            HQ4X_PIXEL33_81
                            break;
                        }
                    case 184:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_61
                            HQ4X_PIXEL02_61
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL20_31
                            HQ4X_PIXEL21_31
                            HQ4X_PIXEL22_32
                            HQ4X_PIXEL23_32
                            HQ4X_PIXEL30_81
                            HQ4X_PIXEL31_81
                            HQ4X_PIXEL32_82
                            HQ4X_PIXEL33_82
                            break;
                        }
                    case 99:
                        {
                            HQ4X_PIXEL00_81
                            HQ4X_PIXEL01_31
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_81
                            HQ4X_PIXEL11_31
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_61
                            HQ4X_PIXEL20_82
                            HQ4X_PIXEL21_32
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_61
                            HQ4X_PIXEL30_82
                            HQ4X_PIXEL31_32
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 57:
                        {
                            HQ4X_PIXEL00_82
                            HQ4X_PIXEL01_82
                            HQ4X_PIXEL02_61
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_32
                            HQ4X_PIXEL11_32
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL20_31
                            HQ4X_PIXEL21_31
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_81
                            HQ4X_PIXEL31_81
                            HQ4X_PIXEL32_61
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 71:
                        {
                            HQ4X_PIXEL00_81
                            HQ4X_PIXEL01_31
                            HQ4X_PIXEL02_32
                            HQ4X_PIXEL03_82
                            HQ4X_PIXEL10_81
                            HQ4X_PIXEL11_31
                            HQ4X_PIXEL12_32
                            HQ4X_PIXEL13_82
                            HQ4X_PIXEL20_61
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_61
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 156:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_61
                            HQ4X_PIXEL02_81
                            HQ4X_PIXEL03_81
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_31
                            HQ4X_PIXEL13_31
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_32
                            HQ4X_PIXEL23_32
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_61
                            HQ4X_PIXEL32_82
                            HQ4X_PIXEL33_82
                            break;
                        }
                    case 226:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_61
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_61
                            HQ4X_PIXEL20_82
                            HQ4X_PIXEL21_32
                            HQ4X_PIXEL22_31
                            HQ4X_PIXEL23_81
                            HQ4X_PIXEL30_82
                            HQ4X_PIXEL31_32
                            HQ4X_PIXEL32_31
                            HQ4X_PIXEL33_81
                            break;
                        }
                    case 60:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_61
                            HQ4X_PIXEL02_81
                            HQ4X_PIXEL03_81
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_31
                            HQ4X_PIXEL13_31
                            HQ4X_PIXEL20_31
                            HQ4X_PIXEL21_31
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_81
                            HQ4X_PIXEL31_81
                            HQ4X_PIXEL32_61
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 195:
                        {
                            HQ4X_PIXEL00_81
                            HQ4X_PIXEL01_31
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_81
                            HQ4X_PIXEL11_31
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_61
                            HQ4X_PIXEL20_61
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_31
                            HQ4X_PIXEL23_81
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            HQ4X_PIXEL32_31
                            HQ4X_PIXEL33_81
                            break;
                        }
                    case 102:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            HQ4X_PIXEL02_32
                            HQ4X_PIXEL03_82
                            HQ4X_PIXEL10_61
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_32
                            HQ4X_PIXEL13_82
                            HQ4X_PIXEL20_82
                            HQ4X_PIXEL21_32
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_61
                            HQ4X_PIXEL30_82
                            HQ4X_PIXEL31_32
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 153:
                        {
                            HQ4X_PIXEL00_82
                            HQ4X_PIXEL01_82
                            HQ4X_PIXEL02_61
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_32
                            HQ4X_PIXEL11_32
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_32
                            HQ4X_PIXEL23_32
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_61
                            HQ4X_PIXEL32_82
                            HQ4X_PIXEL33_82
                            break;
                        }
                    case 58:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_80
                                HQ4X_PIXEL01_10
                                HQ4X_PIXEL10_10
                                HQ4X_PIXEL11_30
                            }
                            else
                            {
                                HQ4X_PIXEL00_20
                                HQ4X_PIXEL01_12
                                HQ4X_PIXEL10_11
                                HQ4X_PIXEL11_0
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_10
                                HQ4X_PIXEL03_80
                                HQ4X_PIXEL12_30
                                HQ4X_PIXEL13_10
                            }
                            else
                            {
                                HQ4X_PIXEL02_11
                                HQ4X_PIXEL03_20
                                HQ4X_PIXEL12_0
                                HQ4X_PIXEL13_12
                            }
                            HQ4X_PIXEL20_31
                            HQ4X_PIXEL21_31
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_81
                            HQ4X_PIXEL31_81
                            HQ4X_PIXEL32_61
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 83:
                        {
                            HQ4X_PIXEL00_81
                            HQ4X_PIXEL01_31
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_10
                                HQ4X_PIXEL03_80
                                HQ4X_PIXEL12_30
                                HQ4X_PIXEL13_10
                            }
                            else
                            {
                                HQ4X_PIXEL02_11
                                HQ4X_PIXEL03_20
                                HQ4X_PIXEL12_0
                                HQ4X_PIXEL13_12
                            }
                            HQ4X_PIXEL10_81
                            HQ4X_PIXEL11_31
                            HQ4X_PIXEL20_61
                            HQ4X_PIXEL21_30
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL22_30
                                HQ4X_PIXEL23_10
                                HQ4X_PIXEL32_10
                                HQ4X_PIXEL33_80
                            }
                            else
                            {
                                HQ4X_PIXEL22_0
                                HQ4X_PIXEL23_11
                                HQ4X_PIXEL32_12
                                HQ4X_PIXEL33_20
                            }
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            break;
                        }
                    case 92:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_61
                            HQ4X_PIXEL02_81
                            HQ4X_PIXEL03_81
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_31
                            HQ4X_PIXEL13_31
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_10
                                HQ4X_PIXEL21_30
                                HQ4X_PIXEL30_80
                                HQ4X_PIXEL31_10
                            }
                            else
                            {
                                HQ4X_PIXEL20_12
                                HQ4X_PIXEL21_0
                                HQ4X_PIXEL30_20
                                HQ4X_PIXEL31_11
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL22_30
                                HQ4X_PIXEL23_10
                                HQ4X_PIXEL32_10
                                HQ4X_PIXEL33_80
                            }
                            else
                            {
                                HQ4X_PIXEL22_0
                                HQ4X_PIXEL23_11
                                HQ4X_PIXEL32_12
                                HQ4X_PIXEL33_20
                            }
                            break;
                        }
                    case 202:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_80
                                HQ4X_PIXEL01_10
                                HQ4X_PIXEL10_10
                                HQ4X_PIXEL11_30
                            }
                            else
                            {
                                HQ4X_PIXEL00_20
                                HQ4X_PIXEL01_12
                                HQ4X_PIXEL10_11
                                HQ4X_PIXEL11_0
                            }
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_61
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_10
                                HQ4X_PIXEL21_30
                                HQ4X_PIXEL30_80
                                HQ4X_PIXEL31_10
                            }
                            else
                            {
                                HQ4X_PIXEL20_12
                                HQ4X_PIXEL21_0
                                HQ4X_PIXEL30_20
                                HQ4X_PIXEL31_11
                            }
                            HQ4X_PIXEL22_31
                            HQ4X_PIXEL23_81
                            HQ4X_PIXEL32_31
                            HQ4X_PIXEL33_81
                            break;
                        }
                    case 78:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_80
                                HQ4X_PIXEL01_10
                                HQ4X_PIXEL10_10
                                HQ4X_PIXEL11_30
                            }
                            else
                            {
                                HQ4X_PIXEL00_20
                                HQ4X_PIXEL01_12
                                HQ4X_PIXEL10_11
                                HQ4X_PIXEL11_0
                            }
                            HQ4X_PIXEL02_32
                            HQ4X_PIXEL03_82
                            HQ4X_PIXEL12_32
                            HQ4X_PIXEL13_82
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_10
                                HQ4X_PIXEL21_30
                                HQ4X_PIXEL30_80
                                HQ4X_PIXEL31_10
                            }
                            else
                            {
                                HQ4X_PIXEL20_12
                                HQ4X_PIXEL21_0
                                HQ4X_PIXEL30_20
                                HQ4X_PIXEL31_11
                            }
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_61
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 154:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_80
                                HQ4X_PIXEL01_10
                                HQ4X_PIXEL10_10
                                HQ4X_PIXEL11_30
                            }
                            else
                            {
                                HQ4X_PIXEL00_20
                                HQ4X_PIXEL01_12
                                HQ4X_PIXEL10_11
                                HQ4X_PIXEL11_0
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_10
                                HQ4X_PIXEL03_80
                                HQ4X_PIXEL12_30
                                HQ4X_PIXEL13_10
                            }
                            else
                            {
                                HQ4X_PIXEL02_11
                                HQ4X_PIXEL03_20
                                HQ4X_PIXEL12_0
                                HQ4X_PIXEL13_12
                            }
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_32
                            HQ4X_PIXEL23_32
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_61
                            HQ4X_PIXEL32_82
                            HQ4X_PIXEL33_82
                            break;
                        }
                    case 114:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_10
                                HQ4X_PIXEL03_80
                                HQ4X_PIXEL12_30
                                HQ4X_PIXEL13_10
                            }
                            else
                            {
                                HQ4X_PIXEL02_11
                                HQ4X_PIXEL03_20
                                HQ4X_PIXEL12_0
                                HQ4X_PIXEL13_12
                            }
                            HQ4X_PIXEL10_61
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL20_82
                            HQ4X_PIXEL21_32
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL22_30
                                HQ4X_PIXEL23_10
                                HQ4X_PIXEL32_10
                                HQ4X_PIXEL33_80
                            }
                            else
                            {
                                HQ4X_PIXEL22_0
                                HQ4X_PIXEL23_11
                                HQ4X_PIXEL32_12
                                HQ4X_PIXEL33_20
                            }
                            HQ4X_PIXEL30_82
                            HQ4X_PIXEL31_32
                            break;
                        }
                    case 89:
                        {
                            HQ4X_PIXEL00_82
                            HQ4X_PIXEL01_82
                            HQ4X_PIXEL02_61
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_32
                            HQ4X_PIXEL11_32
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_10
                                HQ4X_PIXEL21_30
                                HQ4X_PIXEL30_80
                                HQ4X_PIXEL31_10
                            }
                            else
                            {
                                HQ4X_PIXEL20_12
                                HQ4X_PIXEL21_0
                                HQ4X_PIXEL30_20
                                HQ4X_PIXEL31_11
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL22_30
                                HQ4X_PIXEL23_10
                                HQ4X_PIXEL32_10
                                HQ4X_PIXEL33_80
                            }
                            else
                            {
                                HQ4X_PIXEL22_0
                                HQ4X_PIXEL23_11
                                HQ4X_PIXEL32_12
                                HQ4X_PIXEL33_20
                            }
                            break;
                        }
                    case 90:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_80
                                HQ4X_PIXEL01_10
                                HQ4X_PIXEL10_10
                                HQ4X_PIXEL11_30
                            }
                            else
                            {
                                HQ4X_PIXEL00_20
                                HQ4X_PIXEL01_12
                                HQ4X_PIXEL10_11
                                HQ4X_PIXEL11_0
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_10
                                HQ4X_PIXEL03_80
                                HQ4X_PIXEL12_30
                                HQ4X_PIXEL13_10
                            }
                            else
                            {
                                HQ4X_PIXEL02_11
                                HQ4X_PIXEL03_20
                                HQ4X_PIXEL12_0
                                HQ4X_PIXEL13_12
                            }
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_10
                                HQ4X_PIXEL21_30
                                HQ4X_PIXEL30_80
                                HQ4X_PIXEL31_10
                            }
                            else
                            {
                                HQ4X_PIXEL20_12
                                HQ4X_PIXEL21_0
                                HQ4X_PIXEL30_20
                                HQ4X_PIXEL31_11
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL22_30
                                HQ4X_PIXEL23_10
                                HQ4X_PIXEL32_10
                                HQ4X_PIXEL33_80
                            }
                            else
                            {
                                HQ4X_PIXEL22_0
                                HQ4X_PIXEL23_11
                                HQ4X_PIXEL32_12
                                HQ4X_PIXEL33_20
                            }
                            break;
                        }
                    case 55:
                    case 23:
                        {
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL00_81
                                HQ4X_PIXEL01_31
                                HQ4X_PIXEL02_0
                                HQ4X_PIXEL03_0
                                HQ4X_PIXEL12_0
                                HQ4X_PIXEL13_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_12
                                HQ4X_PIXEL01_14
                                HQ4X_PIXEL02_83
                                HQ4X_PIXEL03_50
                                HQ4X_PIXEL12_70
                                HQ4X_PIXEL13_21
                            }
                            HQ4X_PIXEL10_81
                            HQ4X_PIXEL11_31
                            HQ4X_PIXEL20_60
                            HQ4X_PIXEL21_70
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_20
                            HQ4X_PIXEL31_60
                            HQ4X_PIXEL32_61
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 182:
                    case 150:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_0
                                HQ4X_PIXEL03_0
                                HQ4X_PIXEL12_0
                                HQ4X_PIXEL13_0
                                HQ4X_PIXEL23_32
                                HQ4X_PIXEL33_82
                            }
                            else
                            {
                                HQ4X_PIXEL02_21
                                HQ4X_PIXEL03_50
                                HQ4X_PIXEL12_70
                                HQ4X_PIXEL13_83
                                HQ4X_PIXEL23_13
                                HQ4X_PIXEL33_11
                            }
                            HQ4X_PIXEL10_61
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL20_60
                            HQ4X_PIXEL21_70
                            HQ4X_PIXEL22_32
                            HQ4X_PIXEL30_20
                            HQ4X_PIXEL31_60
                            HQ4X_PIXEL32_82
                            break;
                        }
                    case 213:
                    case 212:
                        {
                            HQ4X_PIXEL00_20
                            HQ4X_PIXEL01_60
                            HQ4X_PIXEL02_81
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL03_81
                                HQ4X_PIXEL13_31
                                HQ4X_PIXEL22_0
                                HQ4X_PIXEL23_0
                                HQ4X_PIXEL32_0
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL03_12
                                HQ4X_PIXEL13_14
                                HQ4X_PIXEL22_70
                                HQ4X_PIXEL23_83
                                HQ4X_PIXEL32_21
                                HQ4X_PIXEL33_50
                            }
                            HQ4X_PIXEL10_60
                            HQ4X_PIXEL11_70
                            HQ4X_PIXEL12_31
                            HQ4X_PIXEL20_61
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            break;
                        }
                    case 241:
                    case 240:
                        {
                            HQ4X_PIXEL00_20
                            HQ4X_PIXEL01_60
                            HQ4X_PIXEL02_61
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_60
                            HQ4X_PIXEL11_70
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL20_82
                            HQ4X_PIXEL21_32
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL22_0
                                HQ4X_PIXEL23_0
                                HQ4X_PIXEL30_82
                                HQ4X_PIXEL31_32
                                HQ4X_PIXEL32_0
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL22_70
                                HQ4X_PIXEL23_21
                                HQ4X_PIXEL30_11
                                HQ4X_PIXEL31_13
                                HQ4X_PIXEL32_83
                                HQ4X_PIXEL33_50
                            }
                            break;
                        }
                    case 236:
                    case 232:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_61
                            HQ4X_PIXEL02_60
                            HQ4X_PIXEL03_20
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_70
                            HQ4X_PIXEL13_60
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_0
                                HQ4X_PIXEL21_0
                                HQ4X_PIXEL30_0
                                HQ4X_PIXEL31_0
                                HQ4X_PIXEL32_31
                                HQ4X_PIXEL33_81
                            }
                            else
                            {
                                HQ4X_PIXEL20_21
                                HQ4X_PIXEL21_70
                                HQ4X_PIXEL30_50
                                HQ4X_PIXEL31_83
                                HQ4X_PIXEL32_14
                                HQ4X_PIXEL33_12
                            }
                            HQ4X_PIXEL22_31
                            HQ4X_PIXEL23_81
                            break;
                        }
                    case 109:
                    case 105:
                        {
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL00_82
                                HQ4X_PIXEL10_32
                                HQ4X_PIXEL20_0
                                HQ4X_PIXEL21_0
                                HQ4X_PIXEL30_0
                                HQ4X_PIXEL31_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_11
                                HQ4X_PIXEL10_13
                                HQ4X_PIXEL20_83
                                HQ4X_PIXEL21_70
                                HQ4X_PIXEL30_50
                                HQ4X_PIXEL31_21
                            }
                            HQ4X_PIXEL01_82
                            HQ4X_PIXEL02_60
                            HQ4X_PIXEL03_20
                            HQ4X_PIXEL11_32
                            HQ4X_PIXEL12_70
                            HQ4X_PIXEL13_60
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_61
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 171:
                    case 43:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                                HQ4X_PIXEL01_0
                                HQ4X_PIXEL10_0
                                HQ4X_PIXEL11_0
                                HQ4X_PIXEL20_31
                                HQ4X_PIXEL30_81
                            }
                            else
                            {
                                HQ4X_PIXEL00_50
                                HQ4X_PIXEL01_21
                                HQ4X_PIXEL10_83
                                HQ4X_PIXEL11_70
                                HQ4X_PIXEL20_14
                                HQ4X_PIXEL30_12
                            }
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_61
                            HQ4X_PIXEL21_31
                            HQ4X_PIXEL22_70
                            HQ4X_PIXEL23_60
                            HQ4X_PIXEL31_81
                            HQ4X_PIXEL32_60
                            HQ4X_PIXEL33_20
                            break;
                        }
                    case 143:
                    case 15:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                                HQ4X_PIXEL01_0
                                HQ4X_PIXEL02_32
                                HQ4X_PIXEL03_82
                                HQ4X_PIXEL10_0
                                HQ4X_PIXEL11_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_50
                                HQ4X_PIXEL01_83
                                HQ4X_PIXEL02_13
                                HQ4X_PIXEL03_11
                                HQ4X_PIXEL10_21
                                HQ4X_PIXEL11_70
                            }
                            HQ4X_PIXEL12_32
                            HQ4X_PIXEL13_82
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_70
                            HQ4X_PIXEL23_60
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_61
                            HQ4X_PIXEL32_60
                            HQ4X_PIXEL33_20
                            break;
                        }
                    case 124:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_61
                            HQ4X_PIXEL02_81
                            HQ4X_PIXEL03_81
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_31
                            HQ4X_PIXEL13_31
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_0
                                HQ4X_PIXEL30_0
                                HQ4X_PIXEL31_0
                            }
                            else
                            {
                                HQ4X_PIXEL20_50
                                HQ4X_PIXEL30_50
                                HQ4X_PIXEL31_50
                            }
                            HQ4X_PIXEL21_0
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 203:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                                HQ4X_PIXEL01_0
                                HQ4X_PIXEL10_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_50
                                HQ4X_PIXEL01_50
                                HQ4X_PIXEL10_50
                            }
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL11_0
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_61
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_31
                            HQ4X_PIXEL23_81
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            HQ4X_PIXEL32_31
                            HQ4X_PIXEL33_81
                            break;
                        }
                    case 62:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_0
                                HQ4X_PIXEL03_0
                                HQ4X_PIXEL13_0
                            }
                            else
                            {
                                HQ4X_PIXEL02_50
                                HQ4X_PIXEL03_50
                                HQ4X_PIXEL13_50
                            }
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_0
                            HQ4X_PIXEL20_31
                            HQ4X_PIXEL21_31
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_81
                            HQ4X_PIXEL31_81
                            HQ4X_PIXEL32_61
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 211:
                        {
                            HQ4X_PIXEL00_81
                            HQ4X_PIXEL01_31
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_81
                            HQ4X_PIXEL11_31
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL20_61
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL23_0
                                HQ4X_PIXEL32_0
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL23_50
                                HQ4X_PIXEL32_50
                                HQ4X_PIXEL33_50
                            }
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            break;
                        }
                    case 118:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_0
                                HQ4X_PIXEL03_0
                                HQ4X_PIXEL13_0
                            }
                            else
                            {
                                HQ4X_PIXEL02_50
                                HQ4X_PIXEL03_50
                                HQ4X_PIXEL13_50
                            }
                            HQ4X_PIXEL10_61
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_0
                            HQ4X_PIXEL20_82
                            HQ4X_PIXEL21_32
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_82
                            HQ4X_PIXEL31_32
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 217:
                        {
                            HQ4X_PIXEL00_82
                            HQ4X_PIXEL01_82
                            HQ4X_PIXEL02_61
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_32
                            HQ4X_PIXEL11_32
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL23_0
                                HQ4X_PIXEL32_0
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL23_50
                                HQ4X_PIXEL32_50
                                HQ4X_PIXEL33_50
                            }
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            break;
                        }
                    case 110:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            HQ4X_PIXEL02_32
                            HQ4X_PIXEL03_82
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_32
                            HQ4X_PIXEL13_82
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_0
                                HQ4X_PIXEL30_0
                                HQ4X_PIXEL31_0
                            }
                            else
                            {
                                HQ4X_PIXEL20_50
                                HQ4X_PIXEL30_50
                                HQ4X_PIXEL31_50
                            }
                            HQ4X_PIXEL21_0
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_61
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 155:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                                HQ4X_PIXEL01_0
                                HQ4X_PIXEL10_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_50
                                HQ4X_PIXEL01_50
                                HQ4X_PIXEL10_50
                            }
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL11_0
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_32
                            HQ4X_PIXEL23_32
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_61
                            HQ4X_PIXEL32_82
                            HQ4X_PIXEL33_82
                            break;
                        }
                    case 188:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_61
                            HQ4X_PIXEL02_81
                            HQ4X_PIXEL03_81
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_31
                            HQ4X_PIXEL13_31
                            HQ4X_PIXEL20_31
                            HQ4X_PIXEL21_31
                            HQ4X_PIXEL22_32
                            HQ4X_PIXEL23_32
                            HQ4X_PIXEL30_81
                            HQ4X_PIXEL31_81
                            HQ4X_PIXEL32_82
                            HQ4X_PIXEL33_82
                            break;
                        }
                    case 185:
                        {
                            HQ4X_PIXEL00_82
                            HQ4X_PIXEL01_82
                            HQ4X_PIXEL02_61
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_32
                            HQ4X_PIXEL11_32
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL20_31
                            HQ4X_PIXEL21_31
                            HQ4X_PIXEL22_32
                            HQ4X_PIXEL23_32
                            HQ4X_PIXEL30_81
                            HQ4X_PIXEL31_81
                            HQ4X_PIXEL32_82
                            HQ4X_PIXEL33_82
                            break;
                        }
                    case 61:
                        {
                            HQ4X_PIXEL00_82
                            HQ4X_PIXEL01_82
                            HQ4X_PIXEL02_81
                            HQ4X_PIXEL03_81
                            HQ4X_PIXEL10_32
                            HQ4X_PIXEL11_32
                            HQ4X_PIXEL12_31
                            HQ4X_PIXEL13_31
                            HQ4X_PIXEL20_31
                            HQ4X_PIXEL21_31
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_81
                            HQ4X_PIXEL31_81
                            HQ4X_PIXEL32_61
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 157:
                        {
                            HQ4X_PIXEL00_82
                            HQ4X_PIXEL01_82
                            HQ4X_PIXEL02_81
                            HQ4X_PIXEL03_81
                            HQ4X_PIXEL10_32
                            HQ4X_PIXEL11_32
                            HQ4X_PIXEL12_31
                            HQ4X_PIXEL13_31
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_32
                            HQ4X_PIXEL23_32
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_61
                            HQ4X_PIXEL32_82
                            HQ4X_PIXEL33_82
                            break;
                        }
                    case 103:
                        {
                            HQ4X_PIXEL00_81
                            HQ4X_PIXEL01_31
                            HQ4X_PIXEL02_32
                            HQ4X_PIXEL03_82
                            HQ4X_PIXEL10_81
                            HQ4X_PIXEL11_31
                            HQ4X_PIXEL12_32
                            HQ4X_PIXEL13_82
                            HQ4X_PIXEL20_82
                            HQ4X_PIXEL21_32
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_61
                            HQ4X_PIXEL30_82
                            HQ4X_PIXEL31_32
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 227:
                        {
                            HQ4X_PIXEL00_81
                            HQ4X_PIXEL01_31
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_81
                            HQ4X_PIXEL11_31
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_61
                            HQ4X_PIXEL20_82
                            HQ4X_PIXEL21_32
                            HQ4X_PIXEL22_31
                            HQ4X_PIXEL23_81
                            HQ4X_PIXEL30_82
                            HQ4X_PIXEL31_32
                            HQ4X_PIXEL32_31
                            HQ4X_PIXEL33_81
                            break;
                        }
                    case 230:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            HQ4X_PIXEL02_32
                            HQ4X_PIXEL03_82
                            HQ4X_PIXEL10_61
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_32
                            HQ4X_PIXEL13_82
                            HQ4X_PIXEL20_82
                            HQ4X_PIXEL21_32
                            HQ4X_PIXEL22_31
                            HQ4X_PIXEL23_81
                            HQ4X_PIXEL30_82
                            HQ4X_PIXEL31_32
                            HQ4X_PIXEL32_31
                            HQ4X_PIXEL33_81
                            break;
                        }
                    case 199:
                        {
                            HQ4X_PIXEL00_81
                            HQ4X_PIXEL01_31
                            HQ4X_PIXEL02_32
                            HQ4X_PIXEL03_82
                            HQ4X_PIXEL10_81
                            HQ4X_PIXEL11_31
                            HQ4X_PIXEL12_32
                            HQ4X_PIXEL13_82
                            HQ4X_PIXEL20_61
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_31
                            HQ4X_PIXEL23_81
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            HQ4X_PIXEL32_31
                            HQ4X_PIXEL33_81
                            break;
                        }
                    case 220:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_61
                            HQ4X_PIXEL02_81
                            HQ4X_PIXEL03_81
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_31
                            HQ4X_PIXEL13_31
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_10
                                HQ4X_PIXEL21_30
                                HQ4X_PIXEL30_80
                                HQ4X_PIXEL31_10
                            }
                            else
                            {
                                HQ4X_PIXEL20_12
                                HQ4X_PIXEL21_0
                                HQ4X_PIXEL30_20
                                HQ4X_PIXEL31_11
                            }
                            HQ4X_PIXEL22_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL23_0
                                HQ4X_PIXEL32_0
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL23_50
                                HQ4X_PIXEL32_50
                                HQ4X_PIXEL33_50
                            }
                            break;
                        }
                    case 158:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_80
                                HQ4X_PIXEL01_10
                                HQ4X_PIXEL10_10
                                HQ4X_PIXEL11_30
                            }
                            else
                            {
                                HQ4X_PIXEL00_20
                                HQ4X_PIXEL01_12
                                HQ4X_PIXEL10_11
                                HQ4X_PIXEL11_0
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_0
                                HQ4X_PIXEL03_0
                                HQ4X_PIXEL13_0
                            }
                            else
                            {
                                HQ4X_PIXEL02_50
                                HQ4X_PIXEL03_50
                                HQ4X_PIXEL13_50
                            }
                            HQ4X_PIXEL12_0
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_32
                            HQ4X_PIXEL23_32
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_61
                            HQ4X_PIXEL32_82
                            HQ4X_PIXEL33_82
                            break;
                        }
                    case 234:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_80
                                HQ4X_PIXEL01_10
                                HQ4X_PIXEL10_10
                                HQ4X_PIXEL11_30
                            }
                            else
                            {
                                HQ4X_PIXEL00_20
                                HQ4X_PIXEL01_12
                                HQ4X_PIXEL10_11
                                HQ4X_PIXEL11_0
                            }
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_61
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_0
                                HQ4X_PIXEL30_0
                                HQ4X_PIXEL31_0
                            }
                            else
                            {
                                HQ4X_PIXEL20_50
                                HQ4X_PIXEL30_50
                                HQ4X_PIXEL31_50
                            }
                            HQ4X_PIXEL21_0
                            HQ4X_PIXEL22_31
                            HQ4X_PIXEL23_81
                            HQ4X_PIXEL32_31
                            HQ4X_PIXEL33_81
                            break;
                        }
                    case 242:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_10
                                HQ4X_PIXEL03_80
                                HQ4X_PIXEL12_30
                                HQ4X_PIXEL13_10
                            }
                            else
                            {
                                HQ4X_PIXEL02_11
                                HQ4X_PIXEL03_20
                                HQ4X_PIXEL12_0
                                HQ4X_PIXEL13_12
                            }
                            HQ4X_PIXEL10_61
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL20_82
                            HQ4X_PIXEL21_32
                            HQ4X_PIXEL22_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL23_0
                                HQ4X_PIXEL32_0
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL23_50
                                HQ4X_PIXEL32_50
                                HQ4X_PIXEL33_50
                            }
                            HQ4X_PIXEL30_82
                            HQ4X_PIXEL31_32
                            break;
                        }
                    case 59:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                                HQ4X_PIXEL01_0
                                HQ4X_PIXEL10_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_50
                                HQ4X_PIXEL01_50
                                HQ4X_PIXEL10_50
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_10
                                HQ4X_PIXEL03_80
                                HQ4X_PIXEL12_30
                                HQ4X_PIXEL13_10
                            }
                            else
                            {
                                HQ4X_PIXEL02_11
                                HQ4X_PIXEL03_20
                                HQ4X_PIXEL12_0
                                HQ4X_PIXEL13_12
                            }
                            HQ4X_PIXEL11_0
                            HQ4X_PIXEL20_31
                            HQ4X_PIXEL21_31
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_81
                            HQ4X_PIXEL31_81
                            HQ4X_PIXEL32_61
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 121:
                        {
                            HQ4X_PIXEL00_82
                            HQ4X_PIXEL01_82
                            HQ4X_PIXEL02_61
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_32
                            HQ4X_PIXEL11_32
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_0
                                HQ4X_PIXEL30_0
                                HQ4X_PIXEL31_0
                            }
                            else
                            {
                                HQ4X_PIXEL20_50
                                HQ4X_PIXEL30_50
                                HQ4X_PIXEL31_50
                            }
                            HQ4X_PIXEL21_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL22_30
                                HQ4X_PIXEL23_10
                                HQ4X_PIXEL32_10
                                HQ4X_PIXEL33_80
                            }
                            else
                            {
                                HQ4X_PIXEL22_0
                                HQ4X_PIXEL23_11
                                HQ4X_PIXEL32_12
                                HQ4X_PIXEL33_20
                            }
                            break;
                        }
                    case 87:
                        {
                            HQ4X_PIXEL00_81
                            HQ4X_PIXEL01_31
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_0
                                HQ4X_PIXEL03_0
                                HQ4X_PIXEL13_0
                            }
                            else
                            {
                                HQ4X_PIXEL02_50
                                HQ4X_PIXEL03_50
                                HQ4X_PIXEL13_50
                            }
                            HQ4X_PIXEL10_81
                            HQ4X_PIXEL11_31
                            HQ4X_PIXEL12_0
                            HQ4X_PIXEL20_61
                            HQ4X_PIXEL21_30
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL22_30
                                HQ4X_PIXEL23_10
                                HQ4X_PIXEL32_10
                                HQ4X_PIXEL33_80
                            }
                            else
                            {
                                HQ4X_PIXEL22_0
                                HQ4X_PIXEL23_11
                                HQ4X_PIXEL32_12
                                HQ4X_PIXEL33_20
                            }
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            break;
                        }
                    case 79:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                                HQ4X_PIXEL01_0
                                HQ4X_PIXEL10_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_50
                                HQ4X_PIXEL01_50
                                HQ4X_PIXEL10_50
                            }
                            HQ4X_PIXEL02_32
                            HQ4X_PIXEL03_82
                            HQ4X_PIXEL11_0
                            HQ4X_PIXEL12_32
                            HQ4X_PIXEL13_82
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_10
                                HQ4X_PIXEL21_30
                                HQ4X_PIXEL30_80
                                HQ4X_PIXEL31_10
                            }
                            else
                            {
                                HQ4X_PIXEL20_12
                                HQ4X_PIXEL21_0
                                HQ4X_PIXEL30_20
                                HQ4X_PIXEL31_11
                            }
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_61
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 122:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_80
                                HQ4X_PIXEL01_10
                                HQ4X_PIXEL10_10
                                HQ4X_PIXEL11_30
                            }
                            else
                            {
                                HQ4X_PIXEL00_20
                                HQ4X_PIXEL01_12
                                HQ4X_PIXEL10_11
                                HQ4X_PIXEL11_0
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_10
                                HQ4X_PIXEL03_80
                                HQ4X_PIXEL12_30
                                HQ4X_PIXEL13_10
                            }
                            else
                            {
                                HQ4X_PIXEL02_11
                                HQ4X_PIXEL03_20
                                HQ4X_PIXEL12_0
                                HQ4X_PIXEL13_12
                            }
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_0
                                HQ4X_PIXEL30_0
                                HQ4X_PIXEL31_0
                            }
                            else
                            {
                                HQ4X_PIXEL20_50
                                HQ4X_PIXEL30_50
                                HQ4X_PIXEL31_50
                            }
                            HQ4X_PIXEL21_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL22_30
                                HQ4X_PIXEL23_10
                                HQ4X_PIXEL32_10
                                HQ4X_PIXEL33_80
                            }
                            else
                            {
                                HQ4X_PIXEL22_0
                                HQ4X_PIXEL23_11
                                HQ4X_PIXEL32_12
                                HQ4X_PIXEL33_20
                            }
                            break;
                        }
                    case 94:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_80
                                HQ4X_PIXEL01_10
                                HQ4X_PIXEL10_10
                                HQ4X_PIXEL11_30
                            }
                            else
                            {
                                HQ4X_PIXEL00_20
                                HQ4X_PIXEL01_12
                                HQ4X_PIXEL10_11
                                HQ4X_PIXEL11_0
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_0
                                HQ4X_PIXEL03_0
                                HQ4X_PIXEL13_0
                            }
                            else
                            {
                                HQ4X_PIXEL02_50
                                HQ4X_PIXEL03_50
                                HQ4X_PIXEL13_50
                            }
                            HQ4X_PIXEL12_0
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_10
                                HQ4X_PIXEL21_30
                                HQ4X_PIXEL30_80
                                HQ4X_PIXEL31_10
                            }
                            else
                            {
                                HQ4X_PIXEL20_12
                                HQ4X_PIXEL21_0
                                HQ4X_PIXEL30_20
                                HQ4X_PIXEL31_11
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL22_30
                                HQ4X_PIXEL23_10
                                HQ4X_PIXEL32_10
                                HQ4X_PIXEL33_80
                            }
                            else
                            {
                                HQ4X_PIXEL22_0
                                HQ4X_PIXEL23_11
                                HQ4X_PIXEL32_12
                                HQ4X_PIXEL33_20
                            }
                            break;
                        }
                    case 218:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_80
                                HQ4X_PIXEL01_10
                                HQ4X_PIXEL10_10
                                HQ4X_PIXEL11_30
                            }
                            else
                            {
                                HQ4X_PIXEL00_20
                                HQ4X_PIXEL01_12
                                HQ4X_PIXEL10_11
                                HQ4X_PIXEL11_0
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_10
                                HQ4X_PIXEL03_80
                                HQ4X_PIXEL12_30
                                HQ4X_PIXEL13_10
                            }
                            else
                            {
                                HQ4X_PIXEL02_11
                                HQ4X_PIXEL03_20
                                HQ4X_PIXEL12_0
                                HQ4X_PIXEL13_12
                            }
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_10
                                HQ4X_PIXEL21_30
                                HQ4X_PIXEL30_80
                                HQ4X_PIXEL31_10
                            }
                            else
                            {
                                HQ4X_PIXEL20_12
                                HQ4X_PIXEL21_0
                                HQ4X_PIXEL30_20
                                HQ4X_PIXEL31_11
                            }
                            HQ4X_PIXEL22_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL23_0
                                HQ4X_PIXEL32_0
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL23_50
                                HQ4X_PIXEL32_50
                                HQ4X_PIXEL33_50
                            }
                            break;
                        }
                    case 91:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                                HQ4X_PIXEL01_0
                                HQ4X_PIXEL10_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_50
                                HQ4X_PIXEL01_50
                                HQ4X_PIXEL10_50
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_10
                                HQ4X_PIXEL03_80
                                HQ4X_PIXEL12_30
                                HQ4X_PIXEL13_10
                            }
                            else
                            {
                                HQ4X_PIXEL02_11
                                HQ4X_PIXEL03_20
                                HQ4X_PIXEL12_0
                                HQ4X_PIXEL13_12
                            }
                            HQ4X_PIXEL11_0
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_10
                                HQ4X_PIXEL21_30
                                HQ4X_PIXEL30_80
                                HQ4X_PIXEL31_10
                            }
                            else
                            {
                                HQ4X_PIXEL20_12
                                HQ4X_PIXEL21_0
                                HQ4X_PIXEL30_20
                                HQ4X_PIXEL31_11
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL22_30
                                HQ4X_PIXEL23_10
                                HQ4X_PIXEL32_10
                                HQ4X_PIXEL33_80
                            }
                            else
                            {
                                HQ4X_PIXEL22_0
                                HQ4X_PIXEL23_11
                                HQ4X_PIXEL32_12
                                HQ4X_PIXEL33_20
                            }
                            break;
                        }
                    case 229:
                        {
                            HQ4X_PIXEL00_20
                            HQ4X_PIXEL01_60
                            HQ4X_PIXEL02_60
                            HQ4X_PIXEL03_20
                            HQ4X_PIXEL10_60
                            HQ4X_PIXEL11_70
                            HQ4X_PIXEL12_70
                            HQ4X_PIXEL13_60
                            HQ4X_PIXEL20_82
                            HQ4X_PIXEL21_32
                            HQ4X_PIXEL22_31
                            HQ4X_PIXEL23_81
                            HQ4X_PIXEL30_82
                            HQ4X_PIXEL31_32
                            HQ4X_PIXEL32_31
                            HQ4X_PIXEL33_81
                            break;
                        }
                    case 167:
                        {
                            HQ4X_PIXEL00_81
                            HQ4X_PIXEL01_31
                            HQ4X_PIXEL02_32
                            HQ4X_PIXEL03_82
                            HQ4X_PIXEL10_81
                            HQ4X_PIXEL11_31
                            HQ4X_PIXEL12_32
                            HQ4X_PIXEL13_82
                            HQ4X_PIXEL20_60
                            HQ4X_PIXEL21_70
                            HQ4X_PIXEL22_70
                            HQ4X_PIXEL23_60
                            HQ4X_PIXEL30_20
                            HQ4X_PIXEL31_60
                            HQ4X_PIXEL32_60
                            HQ4X_PIXEL33_20
                            break;
                        }
                    case 173:
                        {
                            HQ4X_PIXEL00_82
                            HQ4X_PIXEL01_82
                            HQ4X_PIXEL02_60
                            HQ4X_PIXEL03_20
                            HQ4X_PIXEL10_32
                            HQ4X_PIXEL11_32
                            HQ4X_PIXEL12_70
                            HQ4X_PIXEL13_60
                            HQ4X_PIXEL20_31
                            HQ4X_PIXEL21_31
                            HQ4X_PIXEL22_70
                            HQ4X_PIXEL23_60
                            HQ4X_PIXEL30_81
                            HQ4X_PIXEL31_81
                            HQ4X_PIXEL32_60
                            HQ4X_PIXEL33_20
                            break;
                        }
                    case 181:
                        {
                            HQ4X_PIXEL00_20
                            HQ4X_PIXEL01_60
                            HQ4X_PIXEL02_81
                            HQ4X_PIXEL03_81
                            HQ4X_PIXEL10_60
                            HQ4X_PIXEL11_70
                            HQ4X_PIXEL12_31
                            HQ4X_PIXEL13_31
                            HQ4X_PIXEL20_60
                            HQ4X_PIXEL21_70
                            HQ4X_PIXEL22_32
                            HQ4X_PIXEL23_32
                            HQ4X_PIXEL30_20
                            HQ4X_PIXEL31_60
                            HQ4X_PIXEL32_82
                            HQ4X_PIXEL33_82
                            break;
                        }
                    case 186:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_80
                                HQ4X_PIXEL01_10
                                HQ4X_PIXEL10_10
                                HQ4X_PIXEL11_30
                            }
                            else
                            {
                                HQ4X_PIXEL00_20
                                HQ4X_PIXEL01_12
                                HQ4X_PIXEL10_11
                                HQ4X_PIXEL11_0
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_10
                                HQ4X_PIXEL03_80
                                HQ4X_PIXEL12_30
                                HQ4X_PIXEL13_10
                            }
                            else
                            {
                                HQ4X_PIXEL02_11
                                HQ4X_PIXEL03_20
                                HQ4X_PIXEL12_0
                                HQ4X_PIXEL13_12
                            }
                            HQ4X_PIXEL20_31
                            HQ4X_PIXEL21_31
                            HQ4X_PIXEL22_32
                            HQ4X_PIXEL23_32
                            HQ4X_PIXEL30_81
                            HQ4X_PIXEL31_81
                            HQ4X_PIXEL32_82
                            HQ4X_PIXEL33_82
                            break;
                        }
                    case 115:
                        {
                            HQ4X_PIXEL00_81
                            HQ4X_PIXEL01_31
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_10
                                HQ4X_PIXEL03_80
                                HQ4X_PIXEL12_30
                                HQ4X_PIXEL13_10
                            }
                            else
                            {
                                HQ4X_PIXEL02_11
                                HQ4X_PIXEL03_20
                                HQ4X_PIXEL12_0
                                HQ4X_PIXEL13_12
                            }
                            HQ4X_PIXEL10_81
                            HQ4X_PIXEL11_31
                            HQ4X_PIXEL20_82
                            HQ4X_PIXEL21_32
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL22_30
                                HQ4X_PIXEL23_10
                                HQ4X_PIXEL32_10
                                HQ4X_PIXEL33_80
                            }
                            else
                            {
                                HQ4X_PIXEL22_0
                                HQ4X_PIXEL23_11
                                HQ4X_PIXEL32_12
                                HQ4X_PIXEL33_20
                            }
                            HQ4X_PIXEL30_82
                            HQ4X_PIXEL31_32
                            break;
                        }
                    case 93:
                        {
                            HQ4X_PIXEL00_82
                            HQ4X_PIXEL01_82
                            HQ4X_PIXEL02_81
                            HQ4X_PIXEL03_81
                            HQ4X_PIXEL10_32
                            HQ4X_PIXEL11_32
                            HQ4X_PIXEL12_31
                            HQ4X_PIXEL13_31
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_10
                                HQ4X_PIXEL21_30
                                HQ4X_PIXEL30_80
                                HQ4X_PIXEL31_10
                            }
                            else
                            {
                                HQ4X_PIXEL20_12
                                HQ4X_PIXEL21_0
                                HQ4X_PIXEL30_20
                                HQ4X_PIXEL31_11
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL22_30
                                HQ4X_PIXEL23_10
                                HQ4X_PIXEL32_10
                                HQ4X_PIXEL33_80
                            }
                            else
                            {
                                HQ4X_PIXEL22_0
                                HQ4X_PIXEL23_11
                                HQ4X_PIXEL32_12
                                HQ4X_PIXEL33_20
                            }
                            break;
                        }
                    case 206:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_80
                                HQ4X_PIXEL01_10
                                HQ4X_PIXEL10_10
                                HQ4X_PIXEL11_30
                            }
                            else
                            {
                                HQ4X_PIXEL00_20
                                HQ4X_PIXEL01_12
                                HQ4X_PIXEL10_11
                                HQ4X_PIXEL11_0
                            }
                            HQ4X_PIXEL02_32
                            HQ4X_PIXEL03_82
                            HQ4X_PIXEL12_32
                            HQ4X_PIXEL13_82
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_10
                                HQ4X_PIXEL21_30
                                HQ4X_PIXEL30_80
                                HQ4X_PIXEL31_10
                            }
                            else
                            {
                                HQ4X_PIXEL20_12
                                HQ4X_PIXEL21_0
                                HQ4X_PIXEL30_20
                                HQ4X_PIXEL31_11
                            }
                            HQ4X_PIXEL22_31
                            HQ4X_PIXEL23_81
                            HQ4X_PIXEL32_31
                            HQ4X_PIXEL33_81
                            break;
                        }
                    case 205:
                    case 201:
                        {
                            HQ4X_PIXEL00_82
                            HQ4X_PIXEL01_82
                            HQ4X_PIXEL02_60
                            HQ4X_PIXEL03_20
                            HQ4X_PIXEL10_32
                            HQ4X_PIXEL11_32
                            HQ4X_PIXEL12_70
                            HQ4X_PIXEL13_60
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_10
                                HQ4X_PIXEL21_30
                                HQ4X_PIXEL30_80
                                HQ4X_PIXEL31_10
                            }
                            else
                            {
                                HQ4X_PIXEL20_12
                                HQ4X_PIXEL21_0
                                HQ4X_PIXEL30_20
                                HQ4X_PIXEL31_11
                            }
                            HQ4X_PIXEL22_31
                            HQ4X_PIXEL23_81
                            HQ4X_PIXEL32_31
                            HQ4X_PIXEL33_81
                            break;
                        }
                    case 174:
                    case 46:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_80
                                HQ4X_PIXEL01_10
                                HQ4X_PIXEL10_10
                                HQ4X_PIXEL11_30
                            }
                            else
                            {
                                HQ4X_PIXEL00_20
                                HQ4X_PIXEL01_12
                                HQ4X_PIXEL10_11
                                HQ4X_PIXEL11_0
                            }
                            HQ4X_PIXEL02_32
                            HQ4X_PIXEL03_82
                            HQ4X_PIXEL12_32
                            HQ4X_PIXEL13_82
                            HQ4X_PIXEL20_31
                            HQ4X_PIXEL21_31
                            HQ4X_PIXEL22_70
                            HQ4X_PIXEL23_60
                            HQ4X_PIXEL30_81
                            HQ4X_PIXEL31_81
                            HQ4X_PIXEL32_60
                            HQ4X_PIXEL33_20
                            break;
                        }
                    case 179:
                    case 147:
                        {
                            HQ4X_PIXEL00_81
                            HQ4X_PIXEL01_31
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_10
                                HQ4X_PIXEL03_80
                                HQ4X_PIXEL12_30
                                HQ4X_PIXEL13_10
                            }
                            else
                            {
                                HQ4X_PIXEL02_11
                                HQ4X_PIXEL03_20
                                HQ4X_PIXEL12_0
                                HQ4X_PIXEL13_12
                            }
                            HQ4X_PIXEL10_81
                            HQ4X_PIXEL11_31
                            HQ4X_PIXEL20_60
                            HQ4X_PIXEL21_70
                            HQ4X_PIXEL22_32
                            HQ4X_PIXEL23_32
                            HQ4X_PIXEL30_20
                            HQ4X_PIXEL31_60
                            HQ4X_PIXEL32_82
                            HQ4X_PIXEL33_82
                            break;
                        }
                    case 117:
                    case 116:
                        {
                            HQ4X_PIXEL00_20
                            HQ4X_PIXEL01_60
                            HQ4X_PIXEL02_81
                            HQ4X_PIXEL03_81
                            HQ4X_PIXEL10_60
                            HQ4X_PIXEL11_70
                            HQ4X_PIXEL12_31
                            HQ4X_PIXEL13_31
                            HQ4X_PIXEL20_82
                            HQ4X_PIXEL21_32
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL22_30
                                HQ4X_PIXEL23_10
                                HQ4X_PIXEL32_10
                                HQ4X_PIXEL33_80
                            }
                            else
                            {
                                HQ4X_PIXEL22_0
                                HQ4X_PIXEL23_11
                                HQ4X_PIXEL32_12
                                HQ4X_PIXEL33_20
                            }
                            HQ4X_PIXEL30_82
                            HQ4X_PIXEL31_32
                            break;
                        }
                    case 189:
                        {
                            HQ4X_PIXEL00_82
                            HQ4X_PIXEL01_82
                            HQ4X_PIXEL02_81
                            HQ4X_PIXEL03_81
                            HQ4X_PIXEL10_32
                            HQ4X_PIXEL11_32
                            HQ4X_PIXEL12_31
                            HQ4X_PIXEL13_31
                            HQ4X_PIXEL20_31
                            HQ4X_PIXEL21_31
                            HQ4X_PIXEL22_32
                            HQ4X_PIXEL23_32
                            HQ4X_PIXEL30_81
                            HQ4X_PIXEL31_81
                            HQ4X_PIXEL32_82
                            HQ4X_PIXEL33_82
                            break;
                        }
                    case 231:
                        {
                            HQ4X_PIXEL00_81
                            HQ4X_PIXEL01_31
                            HQ4X_PIXEL02_32
                            HQ4X_PIXEL03_82
                            HQ4X_PIXEL10_81
                            HQ4X_PIXEL11_31
                            HQ4X_PIXEL12_32
                            HQ4X_PIXEL13_82
                            HQ4X_PIXEL20_82
                            HQ4X_PIXEL21_32
                            HQ4X_PIXEL22_31
                            HQ4X_PIXEL23_81
                            HQ4X_PIXEL30_82
                            HQ4X_PIXEL31_32
                            HQ4X_PIXEL32_31
                            HQ4X_PIXEL33_81
                            break;
                        }
                    case 126:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_0
                                HQ4X_PIXEL03_0
                                HQ4X_PIXEL13_0
                            }
                            else
                            {
                                HQ4X_PIXEL02_50
                                HQ4X_PIXEL03_50
                                HQ4X_PIXEL13_50
                            }
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_0
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_0
                                HQ4X_PIXEL30_0
                                HQ4X_PIXEL31_0
                            }
                            else
                            {
                                HQ4X_PIXEL20_50
                                HQ4X_PIXEL30_50
                                HQ4X_PIXEL31_50
                            }
                            HQ4X_PIXEL21_0
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 219:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                                HQ4X_PIXEL01_0
                                HQ4X_PIXEL10_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_50
                                HQ4X_PIXEL01_50
                                HQ4X_PIXEL10_50
                            }
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL11_0
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL23_0
                                HQ4X_PIXEL32_0
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL23_50
                                HQ4X_PIXEL32_50
                                HQ4X_PIXEL33_50
                            }
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            break;
                        }
                    case 125:
                        {
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL00_82
                                HQ4X_PIXEL10_32
                                HQ4X_PIXEL20_0
                                HQ4X_PIXEL21_0
                                HQ4X_PIXEL30_0
                                HQ4X_PIXEL31_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_11
                                HQ4X_PIXEL10_13
                                HQ4X_PIXEL20_83
                                HQ4X_PIXEL21_70
                                HQ4X_PIXEL30_50
                                HQ4X_PIXEL31_21
                            }
                            HQ4X_PIXEL01_82
                            HQ4X_PIXEL02_81
                            HQ4X_PIXEL03_81
                            HQ4X_PIXEL11_32
                            HQ4X_PIXEL12_31
                            HQ4X_PIXEL13_31
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 221:
                        {
                            HQ4X_PIXEL00_82
                            HQ4X_PIXEL01_82
                            HQ4X_PIXEL02_81
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL03_81
                                HQ4X_PIXEL13_31
                                HQ4X_PIXEL22_0
                                HQ4X_PIXEL23_0
                                HQ4X_PIXEL32_0
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL03_12
                                HQ4X_PIXEL13_14
                                HQ4X_PIXEL22_70
                                HQ4X_PIXEL23_83
                                HQ4X_PIXEL32_21
                                HQ4X_PIXEL33_50
                            }
                            HQ4X_PIXEL10_32
                            HQ4X_PIXEL11_32
                            HQ4X_PIXEL12_31
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            break;
                        }
                    case 207:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                                HQ4X_PIXEL01_0
                                HQ4X_PIXEL02_32
                                HQ4X_PIXEL03_82
                                HQ4X_PIXEL10_0
                                HQ4X_PIXEL11_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_50
                                HQ4X_PIXEL01_83
                                HQ4X_PIXEL02_13
                                HQ4X_PIXEL03_11
                                HQ4X_PIXEL10_21
                                HQ4X_PIXEL11_70
                            }
                            HQ4X_PIXEL12_32
                            HQ4X_PIXEL13_82
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_31
                            HQ4X_PIXEL23_81
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            HQ4X_PIXEL32_31
                            HQ4X_PIXEL33_81
                            break;
                        }
                    case 238:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            HQ4X_PIXEL02_32
                            HQ4X_PIXEL03_82
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_32
                            HQ4X_PIXEL13_82
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_0
                                HQ4X_PIXEL21_0
                                HQ4X_PIXEL30_0
                                HQ4X_PIXEL31_0
                                HQ4X_PIXEL32_31
                                HQ4X_PIXEL33_81
                            }
                            else
                            {
                                HQ4X_PIXEL20_21
                                HQ4X_PIXEL21_70
                                HQ4X_PIXEL30_50
                                HQ4X_PIXEL31_83
                                HQ4X_PIXEL32_14
                                HQ4X_PIXEL33_12
                            }
                            HQ4X_PIXEL22_31
                            HQ4X_PIXEL23_81
                            break;
                        }
                    case 190:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_0
                                HQ4X_PIXEL03_0
                                HQ4X_PIXEL12_0
                                HQ4X_PIXEL13_0
                                HQ4X_PIXEL23_32
                                HQ4X_PIXEL33_82
                            }
                            else
                            {
                                HQ4X_PIXEL02_21
                                HQ4X_PIXEL03_50
                                HQ4X_PIXEL12_70
                                HQ4X_PIXEL13_83
                                HQ4X_PIXEL23_13
                                HQ4X_PIXEL33_11
                            }
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL20_31
                            HQ4X_PIXEL21_31
                            HQ4X_PIXEL22_32
                            HQ4X_PIXEL30_81
                            HQ4X_PIXEL31_81
                            HQ4X_PIXEL32_82
                            break;
                        }
                    case 187:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                                HQ4X_PIXEL01_0
                                HQ4X_PIXEL10_0
                                HQ4X_PIXEL11_0
                                HQ4X_PIXEL20_31
                                HQ4X_PIXEL30_81
                            }
                            else
                            {
                                HQ4X_PIXEL00_50
                                HQ4X_PIXEL01_21
                                HQ4X_PIXEL10_83
                                HQ4X_PIXEL11_70
                                HQ4X_PIXEL20_14
                                HQ4X_PIXEL30_12
                            }
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL21_31
                            HQ4X_PIXEL22_32
                            HQ4X_PIXEL23_32
                            HQ4X_PIXEL31_81
                            HQ4X_PIXEL32_82
                            HQ4X_PIXEL33_82
                            break;
                        }
                    case 243:
                        {
                            HQ4X_PIXEL00_81
                            HQ4X_PIXEL01_31
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_81
                            HQ4X_PIXEL11_31
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL20_82
                            HQ4X_PIXEL21_32
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL22_0
                                HQ4X_PIXEL23_0
                                HQ4X_PIXEL30_82
                                HQ4X_PIXEL31_32
                                HQ4X_PIXEL32_0
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL22_70
                                HQ4X_PIXEL23_21
                                HQ4X_PIXEL30_11
                                HQ4X_PIXEL31_13
                                HQ4X_PIXEL32_83
                                HQ4X_PIXEL33_50
                            }
                            break;
                        }
                    case 119:
                        {
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL00_81
                                HQ4X_PIXEL01_31
                                HQ4X_PIXEL02_0
                                HQ4X_PIXEL03_0
                                HQ4X_PIXEL12_0
                                HQ4X_PIXEL13_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_12
                                HQ4X_PIXEL01_14
                                HQ4X_PIXEL02_83
                                HQ4X_PIXEL03_50
                                HQ4X_PIXEL12_70
                                HQ4X_PIXEL13_21
                            }
                            HQ4X_PIXEL10_81
                            HQ4X_PIXEL11_31
                            HQ4X_PIXEL20_82
                            HQ4X_PIXEL21_32
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_82
                            HQ4X_PIXEL31_32
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 237:
                    case 233:
                        {
                            HQ4X_PIXEL00_82
                            HQ4X_PIXEL01_82
                            HQ4X_PIXEL02_60
                            HQ4X_PIXEL03_20
                            HQ4X_PIXEL10_32
                            HQ4X_PIXEL11_32
                            HQ4X_PIXEL12_70
                            HQ4X_PIXEL13_60
                            HQ4X_PIXEL20_0
                            HQ4X_PIXEL21_0
                            HQ4X_PIXEL22_31
                            HQ4X_PIXEL23_81
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL30_0
                            }
                            else
                            {
                                HQ4X_PIXEL30_20
                            }
                            HQ4X_PIXEL31_0
                            HQ4X_PIXEL32_31
                            HQ4X_PIXEL33_81
                            break;
                        }
                    case 175:
                    case 47:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_20
                            }
                            HQ4X_PIXEL01_0
                            HQ4X_PIXEL02_32
                            HQ4X_PIXEL03_82
                            HQ4X_PIXEL10_0
                            HQ4X_PIXEL11_0
                            HQ4X_PIXEL12_32
                            HQ4X_PIXEL13_82
                            HQ4X_PIXEL20_31
                            HQ4X_PIXEL21_31
                            HQ4X_PIXEL22_70
                            HQ4X_PIXEL23_60
                            HQ4X_PIXEL30_81
                            HQ4X_PIXEL31_81
                            HQ4X_PIXEL32_60
                            HQ4X_PIXEL33_20
                            break;
                        }
                    case 183:
                    case 151:
                        {
                            HQ4X_PIXEL00_81
                            HQ4X_PIXEL01_31
                            HQ4X_PIXEL02_0
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL03_0
                            }
                            else
                            {
                                HQ4X_PIXEL03_20
                            }
                            HQ4X_PIXEL10_81
                            HQ4X_PIXEL11_31
                            HQ4X_PIXEL12_0
                            HQ4X_PIXEL13_0
                            HQ4X_PIXEL20_60
                            HQ4X_PIXEL21_70
                            HQ4X_PIXEL22_32
                            HQ4X_PIXEL23_32
                            HQ4X_PIXEL30_20
                            HQ4X_PIXEL31_60
                            HQ4X_PIXEL32_82
                            HQ4X_PIXEL33_82
                            break;
                        }
                    case 245:
                    case 244:
                        {
                            HQ4X_PIXEL00_20
                            HQ4X_PIXEL01_60
                            HQ4X_PIXEL02_81
                            HQ4X_PIXEL03_81
                            HQ4X_PIXEL10_60
                            HQ4X_PIXEL11_70
                            HQ4X_PIXEL12_31
                            HQ4X_PIXEL13_31
                            HQ4X_PIXEL20_82
                            HQ4X_PIXEL21_32
                            HQ4X_PIXEL22_0
                            HQ4X_PIXEL23_0
                            HQ4X_PIXEL30_82
                            HQ4X_PIXEL31_32
                            HQ4X_PIXEL32_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL33_20
                            }
                            break;
                        }
                    case 250:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_0
                                HQ4X_PIXEL30_0
                                HQ4X_PIXEL31_0
                            }
                            else
                            {
                                HQ4X_PIXEL20_50
                                HQ4X_PIXEL30_50
                                HQ4X_PIXEL31_50
                            }
                            HQ4X_PIXEL21_0
                            HQ4X_PIXEL22_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL23_0
                                HQ4X_PIXEL32_0
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL23_50
                                HQ4X_PIXEL32_50
                                HQ4X_PIXEL33_50
                            }
                            break;
                        }
                    case 123:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                                HQ4X_PIXEL01_0
                                HQ4X_PIXEL10_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_50
                                HQ4X_PIXEL01_50
                                HQ4X_PIXEL10_50
                            }
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL11_0
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_0
                                HQ4X_PIXEL30_0
                                HQ4X_PIXEL31_0
                            }
                            else
                            {
                                HQ4X_PIXEL20_50
                                HQ4X_PIXEL30_50
                                HQ4X_PIXEL31_50
                            }
                            HQ4X_PIXEL21_0
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 95:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                                HQ4X_PIXEL01_0
                                HQ4X_PIXEL10_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_50
                                HQ4X_PIXEL01_50
                                HQ4X_PIXEL10_50
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_0
                                HQ4X_PIXEL03_0
                                HQ4X_PIXEL13_0
                            }
                            else
                            {
                                HQ4X_PIXEL02_50
                                HQ4X_PIXEL03_50
                                HQ4X_PIXEL13_50
                            }
                            HQ4X_PIXEL11_0
                            HQ4X_PIXEL12_0
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 222:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_0
                                HQ4X_PIXEL03_0
                                HQ4X_PIXEL13_0
                            }
                            else
                            {
                                HQ4X_PIXEL02_50
                                HQ4X_PIXEL03_50
                                HQ4X_PIXEL13_50
                            }
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_0
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL23_0
                                HQ4X_PIXEL32_0
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL23_50
                                HQ4X_PIXEL32_50
                                HQ4X_PIXEL33_50
                            }
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            break;
                        }
                    case 252:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_61
                            HQ4X_PIXEL02_81
                            HQ4X_PIXEL03_81
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_31
                            HQ4X_PIXEL13_31
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_0
                                HQ4X_PIXEL30_0
                                HQ4X_PIXEL31_0
                            }
                            else
                            {
                                HQ4X_PIXEL20_50
                                HQ4X_PIXEL30_50
                                HQ4X_PIXEL31_50
                            }
                            HQ4X_PIXEL21_0
                            HQ4X_PIXEL22_0
                            HQ4X_PIXEL23_0
                            HQ4X_PIXEL32_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL33_20
                            }
                            break;
                        }
                    case 249:
                        {
                            HQ4X_PIXEL00_82
                            HQ4X_PIXEL01_82
                            HQ4X_PIXEL02_61
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL10_32
                            HQ4X_PIXEL11_32
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL20_0
                            HQ4X_PIXEL21_0
                            HQ4X_PIXEL22_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL23_0
                                HQ4X_PIXEL32_0
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL23_50
                                HQ4X_PIXEL32_50
                                HQ4X_PIXEL33_50
                            }
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL30_0
                            }
                            else
                            {
                                HQ4X_PIXEL30_20
                            }
                            HQ4X_PIXEL31_0
                            break;
                        }
                    case 235:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                                HQ4X_PIXEL01_0
                                HQ4X_PIXEL10_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_50
                                HQ4X_PIXEL01_50
                                HQ4X_PIXEL10_50
                            }
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL11_0
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_61
                            HQ4X_PIXEL20_0
                            HQ4X_PIXEL21_0
                            HQ4X_PIXEL22_31
                            HQ4X_PIXEL23_81
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL30_0
                            }
                            else
                            {
                                HQ4X_PIXEL30_20
                            }
                            HQ4X_PIXEL31_0
                            HQ4X_PIXEL32_31
                            HQ4X_PIXEL33_81
                            break;
                        }
                    case 111:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_20
                            }
                            HQ4X_PIXEL01_0
                            HQ4X_PIXEL02_32
                            HQ4X_PIXEL03_82
                            HQ4X_PIXEL10_0
                            HQ4X_PIXEL11_0
                            HQ4X_PIXEL12_32
                            HQ4X_PIXEL13_82
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_0
                                HQ4X_PIXEL30_0
                                HQ4X_PIXEL31_0
                            }
                            else
                            {
                                HQ4X_PIXEL20_50
                                HQ4X_PIXEL30_50
                                HQ4X_PIXEL31_50
                            }
                            HQ4X_PIXEL21_0
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_61
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 63:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_20
                            }
                            HQ4X_PIXEL01_0
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_0
                                HQ4X_PIXEL03_0
                                HQ4X_PIXEL13_0
                            }
                            else
                            {
                                HQ4X_PIXEL02_50
                                HQ4X_PIXEL03_50
                                HQ4X_PIXEL13_50
                            }
                            HQ4X_PIXEL10_0
                            HQ4X_PIXEL11_0
                            HQ4X_PIXEL12_0
                            HQ4X_PIXEL20_31
                            HQ4X_PIXEL21_31
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL30_81
                            HQ4X_PIXEL31_81
                            HQ4X_PIXEL32_61
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 159:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                                HQ4X_PIXEL01_0
                                HQ4X_PIXEL10_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_50
                                HQ4X_PIXEL01_50
                                HQ4X_PIXEL10_50
                            }
                            HQ4X_PIXEL02_0
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL03_0
                            }
                            else
                            {
                                HQ4X_PIXEL03_20
                            }
                            HQ4X_PIXEL11_0
                            HQ4X_PIXEL12_0
                            HQ4X_PIXEL13_0
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_32
                            HQ4X_PIXEL23_32
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_61
                            HQ4X_PIXEL32_82
                            HQ4X_PIXEL33_82
                            break;
                        }
                    case 215:
                        {
                            HQ4X_PIXEL00_81
                            HQ4X_PIXEL01_31
                            HQ4X_PIXEL02_0
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL03_0
                            }
                            else
                            {
                                HQ4X_PIXEL03_20
                            }
                            HQ4X_PIXEL10_81
                            HQ4X_PIXEL11_31
                            HQ4X_PIXEL12_0
                            HQ4X_PIXEL13_0
                            HQ4X_PIXEL20_61
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL23_0
                                HQ4X_PIXEL32_0
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL23_50
                                HQ4X_PIXEL32_50
                                HQ4X_PIXEL33_50
                            }
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            break;
                        }
                    case 246:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_0
                                HQ4X_PIXEL03_0
                                HQ4X_PIXEL13_0
                            }
                            else
                            {
                                HQ4X_PIXEL02_50
                                HQ4X_PIXEL03_50
                                HQ4X_PIXEL13_50
                            }
                            HQ4X_PIXEL10_61
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_0
                            HQ4X_PIXEL20_82
                            HQ4X_PIXEL21_32
                            HQ4X_PIXEL22_0
                            HQ4X_PIXEL23_0
                            HQ4X_PIXEL30_82
                            HQ4X_PIXEL31_32
                            HQ4X_PIXEL32_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL33_20
                            }
                            break;
                        }
                    case 254:
                        {
                            HQ4X_PIXEL00_80
                            HQ4X_PIXEL01_10
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_0
                                HQ4X_PIXEL03_0
                                HQ4X_PIXEL13_0
                            }
                            else
                            {
                                HQ4X_PIXEL02_50
                                HQ4X_PIXEL03_50
                                HQ4X_PIXEL13_50
                            }
                            HQ4X_PIXEL10_10
                            HQ4X_PIXEL11_30
                            HQ4X_PIXEL12_0
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_0
                                HQ4X_PIXEL30_0
                                HQ4X_PIXEL31_0
                            }
                            else
                            {
                                HQ4X_PIXEL20_50
                                HQ4X_PIXEL30_50
                                HQ4X_PIXEL31_50
                            }
                            HQ4X_PIXEL21_0
                            HQ4X_PIXEL22_0
                            HQ4X_PIXEL23_0
                            HQ4X_PIXEL32_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL33_20
                            }
                            break;
                        }
                    case 253:
                        {
                            HQ4X_PIXEL00_82
                            HQ4X_PIXEL01_82
                            HQ4X_PIXEL02_81
                            HQ4X_PIXEL03_81
                            HQ4X_PIXEL10_32
                            HQ4X_PIXEL11_32
                            HQ4X_PIXEL12_31
                            HQ4X_PIXEL13_31
                            HQ4X_PIXEL20_0
                            HQ4X_PIXEL21_0
                            HQ4X_PIXEL22_0
                            HQ4X_PIXEL23_0
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL30_0
                            }
                            else
                            {
                                HQ4X_PIXEL30_20
                            }
                            HQ4X_PIXEL31_0
                            HQ4X_PIXEL32_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL33_20
                            }
                            break;
                        }
                    case 251:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                                HQ4X_PIXEL01_0
                                HQ4X_PIXEL10_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_50
                                HQ4X_PIXEL01_50
                                HQ4X_PIXEL10_50
                            }
                            HQ4X_PIXEL02_10
                            HQ4X_PIXEL03_80
                            HQ4X_PIXEL11_0
                            HQ4X_PIXEL12_30
                            HQ4X_PIXEL13_10
                            HQ4X_PIXEL20_0
                            HQ4X_PIXEL21_0
                            HQ4X_PIXEL22_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL23_0
                                HQ4X_PIXEL32_0
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL23_50
                                HQ4X_PIXEL32_50
                                HQ4X_PIXEL33_50
                            }
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL30_0
                            }
                            else
                            {
                                HQ4X_PIXEL30_20
                            }
                            HQ4X_PIXEL31_0
                            break;
                        }
                    case 239:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_20
                            }
                            HQ4X_PIXEL01_0
                            HQ4X_PIXEL02_32
                            HQ4X_PIXEL03_82
                            HQ4X_PIXEL10_0
                            HQ4X_PIXEL11_0
                            HQ4X_PIXEL12_32
                            HQ4X_PIXEL13_82
                            HQ4X_PIXEL20_0
                            HQ4X_PIXEL21_0
                            HQ4X_PIXEL22_31
                            HQ4X_PIXEL23_81
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL30_0
                            }
                            else
                            {
                                HQ4X_PIXEL30_20
                            }
                            HQ4X_PIXEL31_0
                            HQ4X_PIXEL32_31
                            HQ4X_PIXEL33_81
                            break;
                        }
                    case 127:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_20
                            }
                            HQ4X_PIXEL01_0
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL02_0
                                HQ4X_PIXEL03_0
                                HQ4X_PIXEL13_0
                            }
                            else
                            {
                                HQ4X_PIXEL02_50
                                HQ4X_PIXEL03_50
                                HQ4X_PIXEL13_50
                            }
                            HQ4X_PIXEL10_0
                            HQ4X_PIXEL11_0
                            HQ4X_PIXEL12_0
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL20_0
                                HQ4X_PIXEL30_0
                                HQ4X_PIXEL31_0
                            }
                            else
                            {
                                HQ4X_PIXEL20_50
                                HQ4X_PIXEL30_50
                                HQ4X_PIXEL31_50
                            }
                            HQ4X_PIXEL21_0
                            HQ4X_PIXEL22_30
                            HQ4X_PIXEL23_10
                            HQ4X_PIXEL32_10
                            HQ4X_PIXEL33_80
                            break;
                        }
                    case 191:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_20
                            }
                            HQ4X_PIXEL01_0
                            HQ4X_PIXEL02_0
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL03_0
                            }
                            else
                            {
                                HQ4X_PIXEL03_20
                            }
                            HQ4X_PIXEL10_0
                            HQ4X_PIXEL11_0
                            HQ4X_PIXEL12_0
                            HQ4X_PIXEL13_0
                            HQ4X_PIXEL20_31
                            HQ4X_PIXEL21_31
                            HQ4X_PIXEL22_32
                            HQ4X_PIXEL23_32
                            HQ4X_PIXEL30_81
                            HQ4X_PIXEL31_81
                            HQ4X_PIXEL32_82
                            HQ4X_PIXEL33_82
                            break;
                        }
                    case 223:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                                HQ4X_PIXEL01_0
                                HQ4X_PIXEL10_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_50
                                HQ4X_PIXEL01_50
                                HQ4X_PIXEL10_50
                            }
                            HQ4X_PIXEL02_0
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL03_0
                            }
                            else
                            {
                                HQ4X_PIXEL03_20
                            }
                            HQ4X_PIXEL11_0
                            HQ4X_PIXEL12_0
                            HQ4X_PIXEL13_0
                            HQ4X_PIXEL20_10
                            HQ4X_PIXEL21_30
                            HQ4X_PIXEL22_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL23_0
                                HQ4X_PIXEL32_0
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL23_50
                                HQ4X_PIXEL32_50
                                HQ4X_PIXEL33_50
                            }
                            HQ4X_PIXEL30_80
                            HQ4X_PIXEL31_10
                            break;
                        }
                    case 247:
                        {
                            HQ4X_PIXEL00_81
                            HQ4X_PIXEL01_31
                            HQ4X_PIXEL02_0
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL03_0
                            }
                            else
                            {
                                HQ4X_PIXEL03_20
                            }
                            HQ4X_PIXEL10_81
                            HQ4X_PIXEL11_31
                            HQ4X_PIXEL12_0
                            HQ4X_PIXEL13_0
                            HQ4X_PIXEL20_82
                            HQ4X_PIXEL21_32
                            HQ4X_PIXEL22_0
                            HQ4X_PIXEL23_0
                            HQ4X_PIXEL30_82
                            HQ4X_PIXEL31_32
                            HQ4X_PIXEL32_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL33_20
                            }
                            break;
                        }
                    case 255:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ4X_PIXEL00_0
                            }
                            else
                            {
                                HQ4X_PIXEL00_20
                            }
                            HQ4X_PIXEL01_0
                            HQ4X_PIXEL02_0
                            if (HQX_Diff(W2, W6))
                            {
                                HQ4X_PIXEL03_0
                            }
                            else
                            {
                                HQ4X_PIXEL03_20
                            }
                            HQ4X_PIXEL10_0
                            HQ4X_PIXEL11_0
                            HQ4X_PIXEL12_0
                            HQ4X_PIXEL13_0
                            HQ4X_PIXEL20_0
                            HQ4X_PIXEL21_0
                            HQ4X_PIXEL22_0
                            HQ4X_PIXEL23_0
                            if (HQX_Diff(W8, W4))
                            {
                                HQ4X_PIXEL30_0
                            }
                            else
                            {
                                HQ4X_PIXEL30_20
                            }
                            HQ4X_PIXEL31_0
                            HQ4X_PIXEL32_0
                            if (HQX_Diff(W6, W8))
                            {
                                HQ4X_PIXEL33_0
                            }
                            else
                            {
                                HQ4X_PIXEL33_20
                            }
                            break;
                        }
                }

                switch (C)
                {
                    case 0:
                        BmpBufX_[P + 2] = C00;
                        BmpBufX_[L + P + 2] = C10;
                        BmpBufX_[LL + P + 2] = C20;
                        BmpBufX_[LLL + P + 2] = C30;
                        BmpBufX_[P + 4 + 2] = C01;
                        BmpBufX_[L + 4 + P + 2] = C11;
                        BmpBufX_[LL + 4 + P + 2] = C21;
                        BmpBufX_[LLL + 4 + P + 2] = C31;
                        BmpBufX_[P + 8 + 2] = C02;
                        BmpBufX_[L + 8 + P + 2] = C12;
                        BmpBufX_[LL + 8 + P + 2] = C22;
                        BmpBufX_[LLL + 8 + P + 2] = C32;
                        BmpBufX_[P + 12 + 2] = C03;
                        BmpBufX_[L + 12 + P + 2] = C13;
                        BmpBufX_[LL + 12 + P + 2] = C23;
                        BmpBufX_[LLL + 12 + P + 2] = C33;
                        break;
                    case 1:
                        BmpBufX_[P + 1] = C00;
                        BmpBufX_[L + P + 1] = C10;
                        BmpBufX_[LL + P + 1] = C20;
                        BmpBufX_[LLL + P + 1] = C30;
                        BmpBufX_[P + 4 + 1] = C01;
                        BmpBufX_[L + 4 + P + 1] = C11;
                        BmpBufX_[LL + 4 + P + 1] = C21;
                        BmpBufX_[LLL + 4 + P + 1] = C31;
                        BmpBufX_[P + 8 + 1] = C02;
                        BmpBufX_[L + 8 + P + 1] = C12;
                        BmpBufX_[LL + 8 + P + 1] = C22;
                        BmpBufX_[LLL + 8 + P + 1] = C32;
                        BmpBufX_[P + 12 + 1] = C03;
                        BmpBufX_[L + 12 + P + 1] = C13;
                        BmpBufX_[LL + 12 + P + 1] = C23;
                        BmpBufX_[LLL + 12 + P + 1] = C33;
                        break;
                    case 2:
                        BmpBufX_[P + 0] = C00;
                        BmpBufX_[L + P + 0] = C10;
                        BmpBufX_[LL + P + 0] = C20;
                        BmpBufX_[LLL + P + 0] = C30;
                        BmpBufX_[P + 4 + 0] = C01;
                        BmpBufX_[L + 4 + P + 0] = C11;
                        BmpBufX_[LL + 4 + P + 0] = C21;
                        BmpBufX_[LLL + 4 + P + 0] = C31;
                        BmpBufX_[P + 8 + 0] = C02;
                        BmpBufX_[L + 8 + P + 0] = C12;
                        BmpBufX_[LL + 8 + P + 0] = C22;
                        BmpBufX_[LLL + 8 + P + 0] = C32;
                        BmpBufX_[P + 12 + 0] = C03;
                        BmpBufX_[L + 12 + P + 0] = C13;
                        BmpBufX_[LL + 12 + P + 0] = C23;
                        BmpBufX_[LLL + 12 + P + 0] = C33;
                        break;
                }
            }

            P += 16;
        }
        P += LLL;
    }
}
