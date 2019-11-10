#include "picthread.h"

void PicThread::HQ2X_Process1(uchar * BmpBuf_, uchar * BmpBufX_, int MinY, int MaxY, int PicW_, int PicH_, int &P, int L)
{
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
            int R10, G10, B10;
            int R11, G11, B11;

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
                        HQ2X_PIXEL00_RGB_20
                        HQ2X_PIXEL01_RGB_20
                        HQ2X_PIXEL10_RGB_20
                        HQ2X_PIXEL11_RGB_20
                        break;
                    }
                case 2:
                case 34:
                case 130:
                case 162:
                    {
                        HQ2X_PIXEL00_RGB_22
                        HQ2X_PIXEL01_RGB_21
                        HQ2X_PIXEL10_RGB_20
                        HQ2X_PIXEL11_RGB_20
                        break;
                    }
                case 16:
                case 17:
                case 48:
                case 49:
                    {
                        HQ2X_PIXEL00_RGB_20
                        HQ2X_PIXEL01_RGB_22
                        HQ2X_PIXEL10_RGB_20
                        HQ2X_PIXEL11_RGB_21
                        break;
                    }
                case 64:
                case 65:
                case 68:
                case 69:
                    {
                        HQ2X_PIXEL00_RGB_20
                        HQ2X_PIXEL01_RGB_20
                        HQ2X_PIXEL10_RGB_21
                        HQ2X_PIXEL11_RGB_22
                        break;
                    }
                case 8:
                case 12:
                case 136:
                case 140:
                    {
                        HQ2X_PIXEL00_RGB_21
                        HQ2X_PIXEL01_RGB_20
                        HQ2X_PIXEL10_RGB_22
                        HQ2X_PIXEL11_RGB_20
                        break;
                    }
                case 3:
                case 35:
                case 131:
                case 163:
                    {
                        HQ2X_PIXEL00_RGB_11
                        HQ2X_PIXEL01_RGB_21
                        HQ2X_PIXEL10_RGB_20
                        HQ2X_PIXEL11_RGB_20
                        break;
                    }
                case 6:
                case 38:
                case 134:
                case 166:
                    {
                        HQ2X_PIXEL00_RGB_22
                        HQ2X_PIXEL01_RGB_12
                        HQ2X_PIXEL10_RGB_20
                        HQ2X_PIXEL11_RGB_20
                        break;
                    }
                case 20:
                case 21:
                case 52:
                case 53:
                    {
                        HQ2X_PIXEL00_RGB_20
                        HQ2X_PIXEL01_RGB_11
                        HQ2X_PIXEL10_RGB_20
                        HQ2X_PIXEL11_RGB_21
                        break;
                    }
                case 144:
                case 145:
                case 176:
                case 177:
                    {
                        HQ2X_PIXEL00_RGB_20
                        HQ2X_PIXEL01_RGB_22
                        HQ2X_PIXEL10_RGB_20
                        HQ2X_PIXEL11_RGB_12
                        break;
                    }
                case 192:
                case 193:
                case 196:
                case 197:
                    {
                        HQ2X_PIXEL00_RGB_20
                        HQ2X_PIXEL01_RGB_20
                        HQ2X_PIXEL10_RGB_21
                        HQ2X_PIXEL11_RGB_11
                        break;
                    }
                case 96:
                case 97:
                case 100:
                case 101:
                    {
                        HQ2X_PIXEL00_RGB_20
                        HQ2X_PIXEL01_RGB_20
                        HQ2X_PIXEL10_RGB_12
                        HQ2X_PIXEL11_RGB_22
                        break;
                    }
                case 40:
                case 44:
                case 168:
                case 172:
                    {
                        HQ2X_PIXEL00_RGB_21
                        HQ2X_PIXEL01_RGB_20
                        HQ2X_PIXEL10_RGB_11
                        HQ2X_PIXEL11_RGB_20
                        break;
                    }
                case 9:
                case 13:
                case 137:
                case 141:
                    {
                        HQ2X_PIXEL00_RGB_12
                        HQ2X_PIXEL01_RGB_20
                        HQ2X_PIXEL10_RGB_22
                        HQ2X_PIXEL11_RGB_20
                        break;
                    }
                case 18:
                case 50:
                    {
                        HQ2X_PIXEL00_RGB_22
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_20
                        }
                        HQ2X_PIXEL10_RGB_20
                        HQ2X_PIXEL11_RGB_21
                        break;
                    }
                case 80:
                case 81:
                    {
                        HQ2X_PIXEL00_RGB_20
                        HQ2X_PIXEL01_RGB_22
                        HQ2X_PIXEL10_RGB_21
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_20
                        }
                        break;
                    }
                case 72:
                case 76:
                    {
                        HQ2X_PIXEL00_RGB_21
                        HQ2X_PIXEL01_RGB_20
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_20
                        }
                        HQ2X_PIXEL11_RGB_22
                        break;
                    }
                case 10:
                case 138:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_20
                        }
                        HQ2X_PIXEL01_RGB_21
                        HQ2X_PIXEL10_RGB_22
                        HQ2X_PIXEL11_RGB_20
                        break;
                    }
                case 66:
                    {
                        HQ2X_PIXEL00_RGB_22
                        HQ2X_PIXEL01_RGB_21
                        HQ2X_PIXEL10_RGB_21
                        HQ2X_PIXEL11_RGB_22
                        break;
                    }
                case 24:
                    {
                        HQ2X_PIXEL00_RGB_21
                        HQ2X_PIXEL01_RGB_22
                        HQ2X_PIXEL10_RGB_22
                        HQ2X_PIXEL11_RGB_21
                        break;
                    }
                case 7:
                case 39:
                case 135:
                    {
                        HQ2X_PIXEL00_RGB_11
                        HQ2X_PIXEL01_RGB_12
                        HQ2X_PIXEL10_RGB_20
                        HQ2X_PIXEL11_RGB_20
                        break;
                    }
                case 148:
                case 149:
                case 180:
                    {
                        HQ2X_PIXEL00_RGB_20
                        HQ2X_PIXEL01_RGB_11
                        HQ2X_PIXEL10_RGB_20
                        HQ2X_PIXEL11_RGB_12
                        break;
                    }
                case 224:
                case 228:
                case 225:
                    {
                        HQ2X_PIXEL00_RGB_20
                        HQ2X_PIXEL01_RGB_20
                        HQ2X_PIXEL10_RGB_12
                        HQ2X_PIXEL11_RGB_11
                        break;
                    }
                case 41:
                case 169:
                case 45:
                    {
                        HQ2X_PIXEL00_RGB_12
                        HQ2X_PIXEL01_RGB_20
                        HQ2X_PIXEL10_RGB_11
                        HQ2X_PIXEL11_RGB_20
                        break;
                    }
                case 22:
                case 54:
                    {
                        HQ2X_PIXEL00_RGB_22
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_20
                        }
                        HQ2X_PIXEL10_RGB_20
                        HQ2X_PIXEL11_RGB_21
                        break;
                    }
                case 208:
                case 209:
                    {
                        HQ2X_PIXEL00_RGB_20
                        HQ2X_PIXEL01_RGB_22
                        HQ2X_PIXEL10_RGB_21
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_20
                        }
                        break;
                    }
                case 104:
                case 108:
                    {
                        HQ2X_PIXEL00_RGB_21
                        HQ2X_PIXEL01_RGB_20
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_20
                        }
                        HQ2X_PIXEL11_RGB_22
                        break;
                    }
                case 11:
                case 139:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_20
                        }
                        HQ2X_PIXEL01_RGB_21
                        HQ2X_PIXEL10_RGB_22
                        HQ2X_PIXEL11_RGB_20
                        break;
                    }
                case 19:
                case 51:
                    {
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL00_RGB_11
                            HQ2X_PIXEL01_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_60
                            HQ2X_PIXEL01_RGB_90
                        }
                        HQ2X_PIXEL10_RGB_20
                        HQ2X_PIXEL11_RGB_21
                        break;
                    }
                case 146:
                case 178:
                    {
                        HQ2X_PIXEL00_RGB_22
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_10
                            HQ2X_PIXEL11_RGB_12
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_90
                            HQ2X_PIXEL11_RGB_61
                        }
                        HQ2X_PIXEL10_RGB_20
                        break;
                    }
                case 84:
                case 85:
                    {
                        HQ2X_PIXEL00_RGB_20
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL01_RGB_11
                            HQ2X_PIXEL11_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_60
                            HQ2X_PIXEL11_RGB_90
                        }
                        HQ2X_PIXEL10_RGB_21
                        break;
                    }
                case 112:
                case 113:
                    {
                        HQ2X_PIXEL00_RGB_20
                        HQ2X_PIXEL01_RGB_22
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL10_RGB_12
                            HQ2X_PIXEL11_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_61
                            HQ2X_PIXEL11_RGB_90
                        }
                        break;
                    }
                case 200:
                case 204:
                    {
                        HQ2X_PIXEL00_RGB_21
                        HQ2X_PIXEL01_RGB_20
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_10
                            HQ2X_PIXEL11_RGB_11
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_90
                            HQ2X_PIXEL11_RGB_60
                        }
                        break;
                    }
                case 73:
                case 77:
                    {
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL00_RGB_12
                            HQ2X_PIXEL10_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_61
                            HQ2X_PIXEL10_RGB_90
                        }
                        HQ2X_PIXEL01_RGB_20
                        HQ2X_PIXEL11_RGB_22
                        break;
                    }
                case 42:
                case 170:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_10
                            HQ2X_PIXEL10_RGB_11
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_90
                            HQ2X_PIXEL10_RGB_60
                        }
                        HQ2X_PIXEL01_RGB_21
                        HQ2X_PIXEL11_RGB_20
                        break;
                    }
                case 14:
                case 142:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_10
                            HQ2X_PIXEL01_RGB_12
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_90
                            HQ2X_PIXEL01_RGB_61
                        }
                        HQ2X_PIXEL10_RGB_22
                        HQ2X_PIXEL11_RGB_20
                        break;
                    }
                case 67:
                    {
                        HQ2X_PIXEL00_RGB_11
                        HQ2X_PIXEL01_RGB_21
                        HQ2X_PIXEL10_RGB_21
                        HQ2X_PIXEL11_RGB_22
                        break;
                    }
                case 70:
                    {
                        HQ2X_PIXEL00_RGB_22
                        HQ2X_PIXEL01_RGB_12
                        HQ2X_PIXEL10_RGB_21
                        HQ2X_PIXEL11_RGB_22
                        break;
                    }
                case 28:
                    {
                        HQ2X_PIXEL00_RGB_21
                        HQ2X_PIXEL01_RGB_11
                        HQ2X_PIXEL10_RGB_22
                        HQ2X_PIXEL11_RGB_21
                        break;
                    }
                case 152:
                    {
                        HQ2X_PIXEL00_RGB_21
                        HQ2X_PIXEL01_RGB_22
                        HQ2X_PIXEL10_RGB_22
                        HQ2X_PIXEL11_RGB_12
                        break;
                    }
                case 194:
                    {
                        HQ2X_PIXEL00_RGB_22
                        HQ2X_PIXEL01_RGB_21
                        HQ2X_PIXEL10_RGB_21
                        HQ2X_PIXEL11_RGB_11
                        break;
                    }
                case 98:
                    {
                        HQ2X_PIXEL00_RGB_22
                        HQ2X_PIXEL01_RGB_21
                        HQ2X_PIXEL10_RGB_12
                        HQ2X_PIXEL11_RGB_22
                        break;
                    }
                case 56:
                    {
                        HQ2X_PIXEL00_RGB_21
                        HQ2X_PIXEL01_RGB_22
                        HQ2X_PIXEL10_RGB_11
                        HQ2X_PIXEL11_RGB_21
                        break;
                    }
                case 25:
                    {
                        HQ2X_PIXEL00_RGB_12
                        HQ2X_PIXEL01_RGB_22
                        HQ2X_PIXEL10_RGB_22
                        HQ2X_PIXEL11_RGB_21
                        break;
                    }
                case 26:
                case 31:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_20
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_20
                        }
                        HQ2X_PIXEL10_RGB_22
                        HQ2X_PIXEL11_RGB_21
                        break;
                    }
                case 82:
                case 214:
                    {
                        HQ2X_PIXEL00_RGB_22
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_20
                        }
                        HQ2X_PIXEL10_RGB_21
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_20
                        }
                        break;
                    }
                case 88:
                case 248:
                    {
                        HQ2X_PIXEL00_RGB_21
                        HQ2X_PIXEL01_RGB_22
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_20
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_20
                        }
                        break;
                    }
                case 74:
                case 107:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_20
                        }
                        HQ2X_PIXEL01_RGB_21
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_20
                        }
                        HQ2X_PIXEL11_RGB_22
                        break;
                    }
                case 27:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_20
                        }
                        HQ2X_PIXEL01_RGB_10
                        HQ2X_PIXEL10_RGB_22
                        HQ2X_PIXEL11_RGB_21
                        break;
                    }
                case 86:
                    {
                        HQ2X_PIXEL00_RGB_22
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_20
                        }
                        HQ2X_PIXEL10_RGB_21
                        HQ2X_PIXEL11_RGB_10
                        break;
                    }
                case 216:
                    {
                        HQ2X_PIXEL00_RGB_21
                        HQ2X_PIXEL01_RGB_22
                        HQ2X_PIXEL10_RGB_10
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_20
                        }
                        break;
                    }
                case 106:
                    {
                        HQ2X_PIXEL00_RGB_10
                        HQ2X_PIXEL01_RGB_21
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_20
                        }
                        HQ2X_PIXEL11_RGB_22
                        break;
                    }
                case 30:
                    {
                        HQ2X_PIXEL00_RGB_10
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_20
                        }
                        HQ2X_PIXEL10_RGB_22
                        HQ2X_PIXEL11_RGB_21
                        break;
                    }
                case 210:
                    {
                        HQ2X_PIXEL00_RGB_22
                        HQ2X_PIXEL01_RGB_10
                        HQ2X_PIXEL10_RGB_21
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_20
                        }
                        break;
                    }
                case 120:
                    {
                        HQ2X_PIXEL00_RGB_21
                        HQ2X_PIXEL01_RGB_22
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_20
                        }
                        HQ2X_PIXEL11_RGB_10
                        break;
                    }
                case 75:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_20
                        }
                        HQ2X_PIXEL01_RGB_21
                        HQ2X_PIXEL10_RGB_10
                        HQ2X_PIXEL11_RGB_22
                        break;
                    }
                case 29:
                    {
                        HQ2X_PIXEL00_RGB_12
                        HQ2X_PIXEL01_RGB_11
                        HQ2X_PIXEL10_RGB_22
                        HQ2X_PIXEL11_RGB_21
                        break;
                    }
                case 198:
                    {
                        HQ2X_PIXEL00_RGB_22
                        HQ2X_PIXEL01_RGB_12
                        HQ2X_PIXEL10_RGB_21
                        HQ2X_PIXEL11_RGB_11
                        break;
                    }
                case 184:
                    {
                        HQ2X_PIXEL00_RGB_21
                        HQ2X_PIXEL01_RGB_22
                        HQ2X_PIXEL10_RGB_11
                        HQ2X_PIXEL11_RGB_12
                        break;
                    }
                case 99:
                    {
                        HQ2X_PIXEL00_RGB_11
                        HQ2X_PIXEL01_RGB_21
                        HQ2X_PIXEL10_RGB_12
                        HQ2X_PIXEL11_RGB_22
                        break;
                    }
                case 57:
                    {
                        HQ2X_PIXEL00_RGB_12
                        HQ2X_PIXEL01_RGB_22
                        HQ2X_PIXEL10_RGB_11
                        HQ2X_PIXEL11_RGB_21
                        break;
                    }
                case 71:
                    {
                        HQ2X_PIXEL00_RGB_11
                        HQ2X_PIXEL01_RGB_12
                        HQ2X_PIXEL10_RGB_21
                        HQ2X_PIXEL11_RGB_22
                        break;
                    }
                case 156:
                    {
                        HQ2X_PIXEL00_RGB_21
                        HQ2X_PIXEL01_RGB_11
                        HQ2X_PIXEL10_RGB_22
                        HQ2X_PIXEL11_RGB_12
                        break;
                    }
                case 226:
                    {
                        HQ2X_PIXEL00_RGB_22
                        HQ2X_PIXEL01_RGB_21
                        HQ2X_PIXEL10_RGB_12
                        HQ2X_PIXEL11_RGB_11
                        break;
                    }
                case 60:
                    {
                        HQ2X_PIXEL00_RGB_21
                        HQ2X_PIXEL01_RGB_11
                        HQ2X_PIXEL10_RGB_11
                        HQ2X_PIXEL11_RGB_21
                        break;
                    }
                case 195:
                    {
                        HQ2X_PIXEL00_RGB_11
                        HQ2X_PIXEL01_RGB_21
                        HQ2X_PIXEL10_RGB_21
                        HQ2X_PIXEL11_RGB_11
                        break;
                    }
                case 102:
                    {
                        HQ2X_PIXEL00_RGB_22
                        HQ2X_PIXEL01_RGB_12
                        HQ2X_PIXEL10_RGB_12
                        HQ2X_PIXEL11_RGB_22
                        break;
                    }
                case 153:
                    {
                        HQ2X_PIXEL00_RGB_12
                        HQ2X_PIXEL01_RGB_22
                        HQ2X_PIXEL10_RGB_22
                        HQ2X_PIXEL11_RGB_12
                        break;
                    }
                case 58:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_70
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_70
                        }
                        HQ2X_PIXEL10_RGB_11
                        HQ2X_PIXEL11_RGB_21
                        break;
                    }
                case 83:
                    {
                        HQ2X_PIXEL00_RGB_11
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_70
                        }
                        HQ2X_PIXEL10_RGB_21
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_70
                        }
                        break;
                    }
                case 92:
                    {
                        HQ2X_PIXEL00_RGB_21
                        HQ2X_PIXEL01_RGB_11
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_70
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_70
                        }
                        break;
                    }
                case 202:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_70
                        }
                        HQ2X_PIXEL01_RGB_21
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_70
                        }
                        HQ2X_PIXEL11_RGB_11
                        break;
                    }
                case 78:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_70
                        }
                        HQ2X_PIXEL01_RGB_12
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_70
                        }
                        HQ2X_PIXEL11_RGB_22
                        break;
                    }
                case 154:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_70
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_70
                        }
                        HQ2X_PIXEL10_RGB_22
                        HQ2X_PIXEL11_RGB_12
                        break;
                    }
                case 114:
                    {
                        HQ2X_PIXEL00_RGB_22
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_70
                        }
                        HQ2X_PIXEL10_RGB_12
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_70
                        }
                        break;
                    }
                case 89:
                    {
                        HQ2X_PIXEL00_RGB_12
                        HQ2X_PIXEL01_RGB_22
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_70
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_70
                        }
                        break;
                    }
                case 90:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_70
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_70
                        }
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_70
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_70
                        }
                        break;
                    }
                case 55:
                case 23:
                    {
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL00_RGB_11
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_60
                            HQ2X_PIXEL01_RGB_90
                        }
                        HQ2X_PIXEL10_RGB_20
                        HQ2X_PIXEL11_RGB_21
                        break;
                    }
                case 182:
                case 150:
                    {
                        HQ2X_PIXEL00_RGB_22
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                            HQ2X_PIXEL11_RGB_12
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_90
                            HQ2X_PIXEL11_RGB_61
                        }
                        HQ2X_PIXEL10_RGB_20
                        break;
                    }
                case 213:
                case 212:
                    {
                        HQ2X_PIXEL00_RGB_20
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL01_RGB_11
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_60
                            HQ2X_PIXEL11_RGB_90
                        }
                        HQ2X_PIXEL10_RGB_21
                        break;
                    }
                case 241:
                case 240:
                    {
                        HQ2X_PIXEL00_RGB_20
                        HQ2X_PIXEL01_RGB_22
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL10_RGB_12
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_61
                            HQ2X_PIXEL11_RGB_90
                        }
                        break;
                    }
                case 236:
                case 232:
                    {
                        HQ2X_PIXEL00_RGB_21
                        HQ2X_PIXEL01_RGB_20
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                            HQ2X_PIXEL11_RGB_11
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_90
                            HQ2X_PIXEL11_RGB_60
                        }
                        break;
                    }
                case 109:
                case 105:
                    {
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL00_RGB_12
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_61
                            HQ2X_PIXEL10_RGB_90
                        }
                        HQ2X_PIXEL01_RGB_20
                        HQ2X_PIXEL11_RGB_22
                        break;
                    }
                case 171:
                case 43:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                            HQ2X_PIXEL10_RGB_11
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_90
                            HQ2X_PIXEL10_RGB_60
                        }
                        HQ2X_PIXEL01_RGB_21
                        HQ2X_PIXEL11_RGB_20
                        break;
                    }
                case 143:
                case 15:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                            HQ2X_PIXEL01_RGB_12
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_90
                            HQ2X_PIXEL01_RGB_61
                        }
                        HQ2X_PIXEL10_RGB_22
                        HQ2X_PIXEL11_RGB_20
                        break;
                    }
                case 124:
                    {
                        HQ2X_PIXEL00_RGB_21
                        HQ2X_PIXEL01_RGB_11
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_20
                        }
                        HQ2X_PIXEL11_RGB_10
                        break;
                    }
                case 203:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_20
                        }
                        HQ2X_PIXEL01_RGB_21
                        HQ2X_PIXEL10_RGB_10
                        HQ2X_PIXEL11_RGB_11
                        break;
                    }
                case 62:
                    {
                        HQ2X_PIXEL00_RGB_10
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_20
                        }
                        HQ2X_PIXEL10_RGB_11
                        HQ2X_PIXEL11_RGB_21
                        break;
                    }
                case 211:
                    {
                        HQ2X_PIXEL00_RGB_11
                        HQ2X_PIXEL01_RGB_10
                        HQ2X_PIXEL10_RGB_21
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_20
                        }
                        break;
                    }
                case 118:
                    {
                        HQ2X_PIXEL00_RGB_22
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_20
                        }
                        HQ2X_PIXEL10_RGB_12
                        HQ2X_PIXEL11_RGB_10
                        break;
                    }
                case 217:
                    {
                        HQ2X_PIXEL00_RGB_12
                        HQ2X_PIXEL01_RGB_22
                        HQ2X_PIXEL10_RGB_10
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_20
                        }
                        break;
                    }
                case 110:
                    {
                        HQ2X_PIXEL00_RGB_10
                        HQ2X_PIXEL01_RGB_12
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_20
                        }
                        HQ2X_PIXEL11_RGB_22
                        break;
                    }
                case 155:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_20
                        }
                        HQ2X_PIXEL01_RGB_10
                        HQ2X_PIXEL10_RGB_22
                        HQ2X_PIXEL11_RGB_12
                        break;
                    }
                case 188:
                    {
                        HQ2X_PIXEL00_RGB_21
                        HQ2X_PIXEL01_RGB_11
                        HQ2X_PIXEL10_RGB_11
                        HQ2X_PIXEL11_RGB_12
                        break;
                    }
                case 185:
                    {
                        HQ2X_PIXEL00_RGB_12
                        HQ2X_PIXEL01_RGB_22
                        HQ2X_PIXEL10_RGB_11
                        HQ2X_PIXEL11_RGB_12
                        break;
                    }
                case 61:
                    {
                        HQ2X_PIXEL00_RGB_12
                        HQ2X_PIXEL01_RGB_11
                        HQ2X_PIXEL10_RGB_11
                        HQ2X_PIXEL11_RGB_21
                        break;
                    }
                case 157:
                    {
                        HQ2X_PIXEL00_RGB_12
                        HQ2X_PIXEL01_RGB_11
                        HQ2X_PIXEL10_RGB_22
                        HQ2X_PIXEL11_RGB_12
                        break;
                    }
                case 103:
                    {
                        HQ2X_PIXEL00_RGB_11
                        HQ2X_PIXEL01_RGB_12
                        HQ2X_PIXEL10_RGB_12
                        HQ2X_PIXEL11_RGB_22
                        break;
                    }
                case 227:
                    {
                        HQ2X_PIXEL00_RGB_11
                        HQ2X_PIXEL01_RGB_21
                        HQ2X_PIXEL10_RGB_12
                        HQ2X_PIXEL11_RGB_11
                        break;
                    }
                case 230:
                    {
                        HQ2X_PIXEL00_RGB_22
                        HQ2X_PIXEL01_RGB_12
                        HQ2X_PIXEL10_RGB_12
                        HQ2X_PIXEL11_RGB_11
                        break;
                    }
                case 199:
                    {
                        HQ2X_PIXEL00_RGB_11
                        HQ2X_PIXEL01_RGB_12
                        HQ2X_PIXEL10_RGB_21
                        HQ2X_PIXEL11_RGB_11
                        break;
                    }
                case 220:
                    {
                        HQ2X_PIXEL00_RGB_21
                        HQ2X_PIXEL01_RGB_11
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_70
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_20
                        }
                        break;
                    }
                case 158:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_70
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_20
                        }
                        HQ2X_PIXEL10_RGB_22
                        HQ2X_PIXEL11_RGB_12
                        break;
                    }
                case 234:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_70
                        }
                        HQ2X_PIXEL01_RGB_21
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_20
                        }
                        HQ2X_PIXEL11_RGB_11
                        break;
                    }
                case 242:
                    {
                        HQ2X_PIXEL00_RGB_22
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_70
                        }
                        HQ2X_PIXEL10_RGB_12
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_20
                        }
                        break;
                    }
                case 59:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_20
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_70
                        }
                        HQ2X_PIXEL10_RGB_11
                        HQ2X_PIXEL11_RGB_21
                        break;
                    }
                case 121:
                    {
                        HQ2X_PIXEL00_RGB_12
                        HQ2X_PIXEL01_RGB_22
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_20
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_70
                        }
                        break;
                    }
                case 87:
                    {
                        HQ2X_PIXEL00_RGB_11
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_20
                        }
                        HQ2X_PIXEL10_RGB_21
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_70
                        }
                        break;
                    }
                case 79:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_20
                        }
                        HQ2X_PIXEL01_RGB_12
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_70
                        }
                        HQ2X_PIXEL11_RGB_22
                        break;
                    }
                case 122:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_70
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_70
                        }
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_20
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_70
                        }
                        break;
                    }
                case 94:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_70
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_20
                        }
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_70
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_70
                        }
                        break;
                    }
                case 218:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_70
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_70
                        }
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_70
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_20
                        }
                        break;
                    }
                case 91:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_20
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_70
                        }
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_70
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_70
                        }
                        break;
                    }
                case 229:
                    {
                        HQ2X_PIXEL00_RGB_20
                        HQ2X_PIXEL01_RGB_20
                        HQ2X_PIXEL10_RGB_12
                        HQ2X_PIXEL11_RGB_11
                        break;
                    }
                case 167:
                    {
                        HQ2X_PIXEL00_RGB_11
                        HQ2X_PIXEL01_RGB_12
                        HQ2X_PIXEL10_RGB_20
                        HQ2X_PIXEL11_RGB_20
                        break;
                    }
                case 173:
                    {
                        HQ2X_PIXEL00_RGB_12
                        HQ2X_PIXEL01_RGB_20
                        HQ2X_PIXEL10_RGB_11
                        HQ2X_PIXEL11_RGB_20
                        break;
                    }
                case 181:
                    {
                        HQ2X_PIXEL00_RGB_20
                        HQ2X_PIXEL01_RGB_11
                        HQ2X_PIXEL10_RGB_20
                        HQ2X_PIXEL11_RGB_12
                        break;
                    }
                case 186:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_70
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_70
                        }
                        HQ2X_PIXEL10_RGB_11
                        HQ2X_PIXEL11_RGB_12
                        break;
                    }
                case 115:
                    {
                        HQ2X_PIXEL00_RGB_11
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_70
                        }
                        HQ2X_PIXEL10_RGB_12
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_70
                        }
                        break;
                    }
                case 93:
                    {
                        HQ2X_PIXEL00_RGB_12
                        HQ2X_PIXEL01_RGB_11
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_70
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_70
                        }
                        break;
                    }
                case 206:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_70
                        }
                        HQ2X_PIXEL01_RGB_12
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_70
                        }
                        HQ2X_PIXEL11_RGB_11
                        break;
                    }
                case 205:
                case 201:
                    {
                        HQ2X_PIXEL00_RGB_12
                        HQ2X_PIXEL01_RGB_20
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_70
                        }
                        HQ2X_PIXEL11_RGB_11
                        break;
                    }
                case 174:
                case 46:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_70
                        }
                        HQ2X_PIXEL01_RGB_12
                        HQ2X_PIXEL10_RGB_11
                        HQ2X_PIXEL11_RGB_20
                        break;
                    }
                case 179:
                case 147:
                    {
                        HQ2X_PIXEL00_RGB_11
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_70
                        }
                        HQ2X_PIXEL10_RGB_20
                        HQ2X_PIXEL11_RGB_12
                        break;
                    }
                case 117:
                case 116:
                    {
                        HQ2X_PIXEL00_RGB_20
                        HQ2X_PIXEL01_RGB_11
                        HQ2X_PIXEL10_RGB_12
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_10
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_70
                        }
                        break;
                    }
                case 189:
                    {
                        HQ2X_PIXEL00_RGB_12
                        HQ2X_PIXEL01_RGB_11
                        HQ2X_PIXEL10_RGB_11
                        HQ2X_PIXEL11_RGB_12
                        break;
                    }
                case 231:
                    {
                        HQ2X_PIXEL00_RGB_11
                        HQ2X_PIXEL01_RGB_12
                        HQ2X_PIXEL10_RGB_12
                        HQ2X_PIXEL11_RGB_11
                        break;
                    }
                case 126:
                    {
                        HQ2X_PIXEL00_RGB_10
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_20
                        }
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_20
                        }
                        HQ2X_PIXEL11_RGB_10
                        break;
                    }
                case 219:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_20
                        }
                        HQ2X_PIXEL01_RGB_10
                        HQ2X_PIXEL10_RGB_10
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_20
                        }
                        break;
                    }
                case 125:
                    {
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL00_RGB_12
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_61
                            HQ2X_PIXEL10_RGB_90
                        }
                        HQ2X_PIXEL01_RGB_11
                        HQ2X_PIXEL11_RGB_10
                        break;
                    }
                case 221:
                    {
                        HQ2X_PIXEL00_RGB_12
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL01_RGB_11
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_60
                            HQ2X_PIXEL11_RGB_90
                        }
                        HQ2X_PIXEL10_RGB_10
                        break;
                    }
                case 207:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                            HQ2X_PIXEL01_RGB_12
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_90
                            HQ2X_PIXEL01_RGB_61
                        }
                        HQ2X_PIXEL10_RGB_10
                        HQ2X_PIXEL11_RGB_11
                        break;
                    }
                case 238:
                    {
                        HQ2X_PIXEL00_RGB_10
                        HQ2X_PIXEL01_RGB_12
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                            HQ2X_PIXEL11_RGB_11
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_90
                            HQ2X_PIXEL11_RGB_60
                        }
                        break;
                    }
                case 190:
                    {
                        HQ2X_PIXEL00_RGB_10
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                            HQ2X_PIXEL11_RGB_12
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_90
                            HQ2X_PIXEL11_RGB_61
                        }
                        HQ2X_PIXEL10_RGB_11
                        break;
                    }
                case 187:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                            HQ2X_PIXEL10_RGB_11
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_90
                            HQ2X_PIXEL10_RGB_60
                        }
                        HQ2X_PIXEL01_RGB_10
                        HQ2X_PIXEL11_RGB_12
                        break;
                    }
                case 243:
                    {
                        HQ2X_PIXEL00_RGB_11
                        HQ2X_PIXEL01_RGB_10
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL10_RGB_12
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_61
                            HQ2X_PIXEL11_RGB_90
                        }
                        break;
                    }
                case 119:
                    {
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL00_RGB_11
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_60
                            HQ2X_PIXEL01_RGB_90
                        }
                        HQ2X_PIXEL10_RGB_12
                        HQ2X_PIXEL11_RGB_10
                        break;
                    }
                case 237:
                case 233:
                    {
                        HQ2X_PIXEL00_RGB_12
                        HQ2X_PIXEL01_RGB_20
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_100
                        }
                        HQ2X_PIXEL11_RGB_11
                        break;
                    }
                case 175:
                case 47:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_100
                        }
                        HQ2X_PIXEL01_RGB_12
                        HQ2X_PIXEL10_RGB_11
                        HQ2X_PIXEL11_RGB_20
                        break;
                    }
                case 183:
                case 151:
                    {
                        HQ2X_PIXEL00_RGB_11
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_100
                        }
                        HQ2X_PIXEL10_RGB_20
                        HQ2X_PIXEL11_RGB_12
                        break;
                    }
                case 245:
                case 244:
                    {
                        HQ2X_PIXEL00_RGB_20
                        HQ2X_PIXEL01_RGB_11
                        HQ2X_PIXEL10_RGB_12
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_100
                        }
                        break;
                    }
                case 250:
                    {
                        HQ2X_PIXEL00_RGB_10
                        HQ2X_PIXEL01_RGB_10
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_20
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_20
                        }
                        break;
                    }
                case 123:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_20
                        }
                        HQ2X_PIXEL01_RGB_10
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_20
                        }
                        HQ2X_PIXEL11_RGB_10
                        break;
                    }
                case 95:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_20
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_20
                        }
                        HQ2X_PIXEL10_RGB_10
                        HQ2X_PIXEL11_RGB_10
                        break;
                    }
                case 222:
                    {
                        HQ2X_PIXEL00_RGB_10
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_20
                        }
                        HQ2X_PIXEL10_RGB_10
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_20
                        }
                        break;
                    }
                case 252:
                    {
                        HQ2X_PIXEL00_RGB_21
                        HQ2X_PIXEL01_RGB_11
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_20
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_100
                        }
                        break;
                    }
                case 249:
                    {
                        HQ2X_PIXEL00_RGB_12
                        HQ2X_PIXEL01_RGB_22
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_100
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_20
                        }
                        break;
                    }
                case 235:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_20
                        }
                        HQ2X_PIXEL01_RGB_21
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_100
                        }
                        HQ2X_PIXEL11_RGB_11
                        break;
                    }
                case 111:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_100
                        }
                        HQ2X_PIXEL01_RGB_12
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_20
                        }
                        HQ2X_PIXEL11_RGB_22
                        break;
                    }
                case 63:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_100
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_20
                        }
                        HQ2X_PIXEL10_RGB_11
                        HQ2X_PIXEL11_RGB_21
                        break;
                    }
                case 159:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_20
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_100
                        }
                        HQ2X_PIXEL10_RGB_22
                        HQ2X_PIXEL11_RGB_12
                        break;
                    }
                case 215:
                    {
                        HQ2X_PIXEL00_RGB_11
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_100
                        }
                        HQ2X_PIXEL10_RGB_21
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_20
                        }
                        break;
                    }
                case 246:
                    {
                        HQ2X_PIXEL00_RGB_22
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_20
                        }
                        HQ2X_PIXEL10_RGB_12
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_100
                        }
                        break;
                    }
                case 254:
                    {
                        HQ2X_PIXEL00_RGB_10
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_20
                        }
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_20
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_100
                        }
                        break;
                    }
                case 253:
                    {
                        HQ2X_PIXEL00_RGB_12
                        HQ2X_PIXEL01_RGB_11
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_100
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_100
                        }
                        break;
                    }
                case 251:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_20
                        }
                        HQ2X_PIXEL01_RGB_10
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_100
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_20
                        }
                        break;
                    }
                case 239:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_100
                        }
                        HQ2X_PIXEL01_RGB_12
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_100
                        }
                        HQ2X_PIXEL11_RGB_11
                        break;
                    }
                case 127:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_100
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_20
                        }
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_20
                        }
                        HQ2X_PIXEL11_RGB_10
                        break;
                    }
                case 191:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_100
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_100
                        }
                        HQ2X_PIXEL10_RGB_11
                        HQ2X_PIXEL11_RGB_12
                        break;
                    }
                case 223:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_20
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_100
                        }
                        HQ2X_PIXEL10_RGB_10
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_20
                        }
                        break;
                    }
                case 247:
                    {
                        HQ2X_PIXEL00_RGB_11
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_100
                        }
                        HQ2X_PIXEL10_RGB_12
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_100
                        }
                        break;
                    }
                case 255:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ2X_PIXEL00_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL00_RGB_100
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ2X_PIXEL01_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL01_RGB_100
                        }
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ2X_PIXEL10_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL10_RGB_100
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ2X_PIXEL11_RGB_0
                        }
                        else
                        {
                            HQ2X_PIXEL11_RGB_100
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
            BmpBufX_[P + 4 + 2] = R01;
            BmpBufX_[P + 4 + 1] = G01;
            BmpBufX_[P + 4 + 0] = B01;
            BmpBufX_[L + 4 + P + 2] = R11;
            BmpBufX_[L + 4 + P + 1] = G11;
            BmpBufX_[L + 4 + P + 0] = B11;
            P += 8;
        }
        P += L;
    }
}

void PicThread::HQ2X_Process2(uchar * BmpBuf_, uchar * BmpBufX_, int MinY, int MaxY, int PicW_, int PicH_, int &P, int L)
{
    int X, Y;
    int XW, XE, YN, YS;
    int PicW_1 = PicW_ - 1;
    int PicH_1 = PicH_ - 1;
    int W1R, W1G, W1B, W2R, W2G, W2B, W3R, W3G, W3B;
    int W4R, W4G, W4B, W5R, W5G, W5B, W6R, W6G, W6B;
    int W7R, W7G, W7B, W8R, W8G, W8B, W9R, W9G, W9B;
    int W1, W2, W3, W4, W5, W6, W7, W8, W9, C00, C01, C10, C11;
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
                            HQ2X_PIXEL00_20
                            HQ2X_PIXEL01_20
                            HQ2X_PIXEL10_20
                            HQ2X_PIXEL11_20
                            break;
                        }
                    case 2:
                    case 34:
                    case 130:
                    case 162:
                        {
                            HQ2X_PIXEL00_22
                            HQ2X_PIXEL01_21
                            HQ2X_PIXEL10_20
                            HQ2X_PIXEL11_20
                            break;
                        }
                    case 16:
                    case 17:
                    case 48:
                    case 49:
                        {
                            HQ2X_PIXEL00_20
                            HQ2X_PIXEL01_22
                            HQ2X_PIXEL10_20
                            HQ2X_PIXEL11_21
                            break;
                        }
                    case 64:
                    case 65:
                    case 68:
                    case 69:
                        {
                            HQ2X_PIXEL00_20
                            HQ2X_PIXEL01_20
                            HQ2X_PIXEL10_21
                            HQ2X_PIXEL11_22
                            break;
                        }
                    case 8:
                    case 12:
                    case 136:
                    case 140:
                        {
                            HQ2X_PIXEL00_21
                            HQ2X_PIXEL01_20
                            HQ2X_PIXEL10_22
                            HQ2X_PIXEL11_20
                            break;
                        }
                    case 3:
                    case 35:
                    case 131:
                    case 163:
                        {
                            HQ2X_PIXEL00_11
                            HQ2X_PIXEL01_21
                            HQ2X_PIXEL10_20
                            HQ2X_PIXEL11_20
                            break;
                        }
                    case 6:
                    case 38:
                    case 134:
                    case 166:
                        {
                            HQ2X_PIXEL00_22
                            HQ2X_PIXEL01_12
                            HQ2X_PIXEL10_20
                            HQ2X_PIXEL11_20
                            break;
                        }
                    case 20:
                    case 21:
                    case 52:
                    case 53:
                        {
                            HQ2X_PIXEL00_20
                            HQ2X_PIXEL01_11
                            HQ2X_PIXEL10_20
                            HQ2X_PIXEL11_21
                            break;
                        }
                    case 144:
                    case 145:
                    case 176:
                    case 177:
                        {
                            HQ2X_PIXEL00_20
                            HQ2X_PIXEL01_22
                            HQ2X_PIXEL10_20
                            HQ2X_PIXEL11_12
                            break;
                        }
                    case 192:
                    case 193:
                    case 196:
                    case 197:
                        {
                            HQ2X_PIXEL00_20
                            HQ2X_PIXEL01_20
                            HQ2X_PIXEL10_21
                            HQ2X_PIXEL11_11
                            break;
                        }
                    case 96:
                    case 97:
                    case 100:
                    case 101:
                        {
                            HQ2X_PIXEL00_20
                            HQ2X_PIXEL01_20
                            HQ2X_PIXEL10_12
                            HQ2X_PIXEL11_22
                            break;
                        }
                    case 40:
                    case 44:
                    case 168:
                    case 172:
                        {
                            HQ2X_PIXEL00_21
                            HQ2X_PIXEL01_20
                            HQ2X_PIXEL10_11
                            HQ2X_PIXEL11_20
                            break;
                        }
                    case 9:
                    case 13:
                    case 137:
                    case 141:
                        {
                            HQ2X_PIXEL00_12
                            HQ2X_PIXEL01_20
                            HQ2X_PIXEL10_22
                            HQ2X_PIXEL11_20
                            break;
                        }
                    case 18:
                    case 50:
                        {
                            HQ2X_PIXEL00_22
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_10
                            }
                            else
                            {
                                HQ2X_PIXEL01_20
                            }
                            HQ2X_PIXEL10_20
                            HQ2X_PIXEL11_21
                            break;
                        }
                    case 80:
                    case 81:
                        {
                            HQ2X_PIXEL00_20
                            HQ2X_PIXEL01_22
                            HQ2X_PIXEL10_21
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_10
                            }
                            else
                            {
                                HQ2X_PIXEL11_20
                            }
                            break;
                        }
                    case 72:
                    case 76:
                        {
                            HQ2X_PIXEL00_21
                            HQ2X_PIXEL01_20
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_10
                            }
                            else
                            {
                                HQ2X_PIXEL10_20
                            }
                            HQ2X_PIXEL11_22
                            break;
                        }
                    case 10:
                    case 138:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_10
                            }
                            else
                            {
                                HQ2X_PIXEL00_20
                            }
                            HQ2X_PIXEL01_21
                            HQ2X_PIXEL10_22
                            HQ2X_PIXEL11_20
                            break;
                        }
                    case 66:
                        {
                            HQ2X_PIXEL00_22
                            HQ2X_PIXEL01_21
                            HQ2X_PIXEL10_21
                            HQ2X_PIXEL11_22
                            break;
                        }
                    case 24:
                        {
                            HQ2X_PIXEL00_21
                            HQ2X_PIXEL01_22
                            HQ2X_PIXEL10_22
                            HQ2X_PIXEL11_21
                            break;
                        }
                    case 7:
                    case 39:
                    case 135:
                        {
                            HQ2X_PIXEL00_11
                            HQ2X_PIXEL01_12
                            HQ2X_PIXEL10_20
                            HQ2X_PIXEL11_20
                            break;
                        }
                    case 148:
                    case 149:
                    case 180:
                        {
                            HQ2X_PIXEL00_20
                            HQ2X_PIXEL01_11
                            HQ2X_PIXEL10_20
                            HQ2X_PIXEL11_12
                            break;
                        }
                    case 224:
                    case 228:
                    case 225:
                        {
                            HQ2X_PIXEL00_20
                            HQ2X_PIXEL01_20
                            HQ2X_PIXEL10_12
                            HQ2X_PIXEL11_11
                            break;
                        }
                    case 41:
                    case 169:
                    case 45:
                        {
                            HQ2X_PIXEL00_12
                            HQ2X_PIXEL01_20
                            HQ2X_PIXEL10_11
                            HQ2X_PIXEL11_20
                            break;
                        }
                    case 22:
                    case 54:
                        {
                            HQ2X_PIXEL00_22
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_20
                            }
                            HQ2X_PIXEL10_20
                            HQ2X_PIXEL11_21
                            break;
                        }
                    case 208:
                    case 209:
                        {
                            HQ2X_PIXEL00_20
                            HQ2X_PIXEL01_22
                            HQ2X_PIXEL10_21
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL11_20
                            }
                            break;
                        }
                    case 104:
                    case 108:
                        {
                            HQ2X_PIXEL00_21
                            HQ2X_PIXEL01_20
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_20
                            }
                            HQ2X_PIXEL11_22
                            break;
                        }
                    case 11:
                    case 139:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_20
                            }
                            HQ2X_PIXEL01_21
                            HQ2X_PIXEL10_22
                            HQ2X_PIXEL11_20
                            break;
                        }
                    case 19:
                    case 51:
                        {
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL00_11
                                HQ2X_PIXEL01_10
                            }
                            else
                            {
                                HQ2X_PIXEL00_60
                                HQ2X_PIXEL01_90
                            }
                            HQ2X_PIXEL10_20
                            HQ2X_PIXEL11_21
                            break;
                        }
                    case 146:
                    case 178:
                        {
                            HQ2X_PIXEL00_22
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_10
                                HQ2X_PIXEL11_12
                            }
                            else
                            {
                                HQ2X_PIXEL01_90
                                HQ2X_PIXEL11_61
                            }
                            HQ2X_PIXEL10_20
                            break;
                        }
                    case 84:
                    case 85:
                        {
                            HQ2X_PIXEL00_20
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL01_11
                                HQ2X_PIXEL11_10
                            }
                            else
                            {
                                HQ2X_PIXEL01_60
                                HQ2X_PIXEL11_90
                            }
                            HQ2X_PIXEL10_21
                            break;
                        }
                    case 112:
                    case 113:
                        {
                            HQ2X_PIXEL00_20
                            HQ2X_PIXEL01_22
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL10_12
                                HQ2X_PIXEL11_10
                            }
                            else
                            {
                                HQ2X_PIXEL10_61
                                HQ2X_PIXEL11_90
                            }
                            break;
                        }
                    case 200:
                    case 204:
                        {
                            HQ2X_PIXEL00_21
                            HQ2X_PIXEL01_20
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_10
                                HQ2X_PIXEL11_11
                            }
                            else
                            {
                                HQ2X_PIXEL10_90
                                HQ2X_PIXEL11_60
                            }
                            break;
                        }
                    case 73:
                    case 77:
                        {
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL00_12
                                HQ2X_PIXEL10_10
                            }
                            else
                            {
                                HQ2X_PIXEL00_61
                                HQ2X_PIXEL10_90
                            }
                            HQ2X_PIXEL01_20
                            HQ2X_PIXEL11_22
                            break;
                        }
                    case 42:
                    case 170:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_10
                                HQ2X_PIXEL10_11
                            }
                            else
                            {
                                HQ2X_PIXEL00_90
                                HQ2X_PIXEL10_60
                            }
                            HQ2X_PIXEL01_21
                            HQ2X_PIXEL11_20
                            break;
                        }
                    case 14:
                    case 142:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_10
                                HQ2X_PIXEL01_12
                            }
                            else
                            {
                                HQ2X_PIXEL00_90
                                HQ2X_PIXEL01_61
                            }
                            HQ2X_PIXEL10_22
                            HQ2X_PIXEL11_20
                            break;
                        }
                    case 67:
                        {
                            HQ2X_PIXEL00_11
                            HQ2X_PIXEL01_21
                            HQ2X_PIXEL10_21
                            HQ2X_PIXEL11_22
                            break;
                        }
                    case 70:
                        {
                            HQ2X_PIXEL00_22
                            HQ2X_PIXEL01_12
                            HQ2X_PIXEL10_21
                            HQ2X_PIXEL11_22
                            break;
                        }
                    case 28:
                        {
                            HQ2X_PIXEL00_21
                            HQ2X_PIXEL01_11
                            HQ2X_PIXEL10_22
                            HQ2X_PIXEL11_21
                            break;
                        }
                    case 152:
                        {
                            HQ2X_PIXEL00_21
                            HQ2X_PIXEL01_22
                            HQ2X_PIXEL10_22
                            HQ2X_PIXEL11_12
                            break;
                        }
                    case 194:
                        {
                            HQ2X_PIXEL00_22
                            HQ2X_PIXEL01_21
                            HQ2X_PIXEL10_21
                            HQ2X_PIXEL11_11
                            break;
                        }
                    case 98:
                        {
                            HQ2X_PIXEL00_22
                            HQ2X_PIXEL01_21
                            HQ2X_PIXEL10_12
                            HQ2X_PIXEL11_22
                            break;
                        }
                    case 56:
                        {
                            HQ2X_PIXEL00_21
                            HQ2X_PIXEL01_22
                            HQ2X_PIXEL10_11
                            HQ2X_PIXEL11_21
                            break;
                        }
                    case 25:
                        {
                            HQ2X_PIXEL00_12
                            HQ2X_PIXEL01_22
                            HQ2X_PIXEL10_22
                            HQ2X_PIXEL11_21
                            break;
                        }
                    case 26:
                    case 31:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_20
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_20
                            }
                            HQ2X_PIXEL10_22
                            HQ2X_PIXEL11_21
                            break;
                        }
                    case 82:
                    case 214:
                        {
                            HQ2X_PIXEL00_22
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_20
                            }
                            HQ2X_PIXEL10_21
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL11_20
                            }
                            break;
                        }
                    case 88:
                    case 248:
                        {
                            HQ2X_PIXEL00_21
                            HQ2X_PIXEL01_22
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_20
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL11_20
                            }
                            break;
                        }
                    case 74:
                    case 107:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_20
                            }
                            HQ2X_PIXEL01_21
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_20
                            }
                            HQ2X_PIXEL11_22
                            break;
                        }
                    case 27:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_20
                            }
                            HQ2X_PIXEL01_10
                            HQ2X_PIXEL10_22
                            HQ2X_PIXEL11_21
                            break;
                        }
                    case 86:
                        {
                            HQ2X_PIXEL00_22
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_20
                            }
                            HQ2X_PIXEL10_21
                            HQ2X_PIXEL11_10
                            break;
                        }
                    case 216:
                        {
                            HQ2X_PIXEL00_21
                            HQ2X_PIXEL01_22
                            HQ2X_PIXEL10_10
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL11_20
                            }
                            break;
                        }
                    case 106:
                        {
                            HQ2X_PIXEL00_10
                            HQ2X_PIXEL01_21
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_20
                            }
                            HQ2X_PIXEL11_22
                            break;
                        }
                    case 30:
                        {
                            HQ2X_PIXEL00_10
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_20
                            }
                            HQ2X_PIXEL10_22
                            HQ2X_PIXEL11_21
                            break;
                        }
                    case 210:
                        {
                            HQ2X_PIXEL00_22
                            HQ2X_PIXEL01_10
                            HQ2X_PIXEL10_21
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL11_20
                            }
                            break;
                        }
                    case 120:
                        {
                            HQ2X_PIXEL00_21
                            HQ2X_PIXEL01_22
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_20
                            }
                            HQ2X_PIXEL11_10
                            break;
                        }
                    case 75:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_20
                            }
                            HQ2X_PIXEL01_21
                            HQ2X_PIXEL10_10
                            HQ2X_PIXEL11_22
                            break;
                        }
                    case 29:
                        {
                            HQ2X_PIXEL00_12
                            HQ2X_PIXEL01_11
                            HQ2X_PIXEL10_22
                            HQ2X_PIXEL11_21
                            break;
                        }
                    case 198:
                        {
                            HQ2X_PIXEL00_22
                            HQ2X_PIXEL01_12
                            HQ2X_PIXEL10_21
                            HQ2X_PIXEL11_11
                            break;
                        }
                    case 184:
                        {
                            HQ2X_PIXEL00_21
                            HQ2X_PIXEL01_22
                            HQ2X_PIXEL10_11
                            HQ2X_PIXEL11_12
                            break;
                        }
                    case 99:
                        {
                            HQ2X_PIXEL00_11
                            HQ2X_PIXEL01_21
                            HQ2X_PIXEL10_12
                            HQ2X_PIXEL11_22
                            break;
                        }
                    case 57:
                        {
                            HQ2X_PIXEL00_12
                            HQ2X_PIXEL01_22
                            HQ2X_PIXEL10_11
                            HQ2X_PIXEL11_21
                            break;
                        }
                    case 71:
                        {
                            HQ2X_PIXEL00_11
                            HQ2X_PIXEL01_12
                            HQ2X_PIXEL10_21
                            HQ2X_PIXEL11_22
                            break;
                        }
                    case 156:
                        {
                            HQ2X_PIXEL00_21
                            HQ2X_PIXEL01_11
                            HQ2X_PIXEL10_22
                            HQ2X_PIXEL11_12
                            break;
                        }
                    case 226:
                        {
                            HQ2X_PIXEL00_22
                            HQ2X_PIXEL01_21
                            HQ2X_PIXEL10_12
                            HQ2X_PIXEL11_11
                            break;
                        }
                    case 60:
                        {
                            HQ2X_PIXEL00_21
                            HQ2X_PIXEL01_11
                            HQ2X_PIXEL10_11
                            HQ2X_PIXEL11_21
                            break;
                        }
                    case 195:
                        {
                            HQ2X_PIXEL00_11
                            HQ2X_PIXEL01_21
                            HQ2X_PIXEL10_21
                            HQ2X_PIXEL11_11
                            break;
                        }
                    case 102:
                        {
                            HQ2X_PIXEL00_22
                            HQ2X_PIXEL01_12
                            HQ2X_PIXEL10_12
                            HQ2X_PIXEL11_22
                            break;
                        }
                    case 153:
                        {
                            HQ2X_PIXEL00_12
                            HQ2X_PIXEL01_22
                            HQ2X_PIXEL10_22
                            HQ2X_PIXEL11_12
                            break;
                        }
                    case 58:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_10
                            }
                            else
                            {
                                HQ2X_PIXEL00_70
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_10
                            }
                            else
                            {
                                HQ2X_PIXEL01_70
                            }
                            HQ2X_PIXEL10_11
                            HQ2X_PIXEL11_21
                            break;
                        }
                    case 83:
                        {
                            HQ2X_PIXEL00_11
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_10
                            }
                            else
                            {
                                HQ2X_PIXEL01_70
                            }
                            HQ2X_PIXEL10_21
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_10
                            }
                            else
                            {
                                HQ2X_PIXEL11_70
                            }
                            break;
                        }
                    case 92:
                        {
                            HQ2X_PIXEL00_21
                            HQ2X_PIXEL01_11
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_10
                            }
                            else
                            {
                                HQ2X_PIXEL10_70
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_10
                            }
                            else
                            {
                                HQ2X_PIXEL11_70
                            }
                            break;
                        }
                    case 202:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_10
                            }
                            else
                            {
                                HQ2X_PIXEL00_70
                            }
                            HQ2X_PIXEL01_21
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_10
                            }
                            else
                            {
                                HQ2X_PIXEL10_70
                            }
                            HQ2X_PIXEL11_11
                            break;
                        }
                    case 78:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_10
                            }
                            else
                            {
                                HQ2X_PIXEL00_70
                            }
                            HQ2X_PIXEL01_12
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_10
                            }
                            else
                            {
                                HQ2X_PIXEL10_70
                            }
                            HQ2X_PIXEL11_22
                            break;
                        }
                    case 154:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_10
                            }
                            else
                            {
                                HQ2X_PIXEL00_70
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_10
                            }
                            else
                            {
                                HQ2X_PIXEL01_70
                            }
                            HQ2X_PIXEL10_22
                            HQ2X_PIXEL11_12
                            break;
                        }
                    case 114:
                        {
                            HQ2X_PIXEL00_22
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_10
                            }
                            else
                            {
                                HQ2X_PIXEL01_70
                            }
                            HQ2X_PIXEL10_12
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_10
                            }
                            else
                            {
                                HQ2X_PIXEL11_70
                            }
                            break;
                        }
                    case 89:
                        {
                            HQ2X_PIXEL00_12
                            HQ2X_PIXEL01_22
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_10
                            }
                            else
                            {
                                HQ2X_PIXEL10_70
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_10
                            }
                            else
                            {
                                HQ2X_PIXEL11_70
                            }
                            break;
                        }
                    case 90:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_10
                            }
                            else
                            {
                                HQ2X_PIXEL00_70
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_10
                            }
                            else
                            {
                                HQ2X_PIXEL01_70
                            }
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_10
                            }
                            else
                            {
                                HQ2X_PIXEL10_70
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_10
                            }
                            else
                            {
                                HQ2X_PIXEL11_70
                            }
                            break;
                        }
                    case 55:
                    case 23:
                        {
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL00_11
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_60
                                HQ2X_PIXEL01_90
                            }
                            HQ2X_PIXEL10_20
                            HQ2X_PIXEL11_21
                            break;
                        }
                    case 182:
                    case 150:
                        {
                            HQ2X_PIXEL00_22
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                                HQ2X_PIXEL11_12
                            }
                            else
                            {
                                HQ2X_PIXEL01_90
                                HQ2X_PIXEL11_61
                            }
                            HQ2X_PIXEL10_20
                            break;
                        }
                    case 213:
                    case 212:
                        {
                            HQ2X_PIXEL00_20
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL01_11
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_60
                                HQ2X_PIXEL11_90
                            }
                            HQ2X_PIXEL10_21
                            break;
                        }
                    case 241:
                    case 240:
                        {
                            HQ2X_PIXEL00_20
                            HQ2X_PIXEL01_22
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL10_12
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_61
                                HQ2X_PIXEL11_90
                            }
                            break;
                        }
                    case 236:
                    case 232:
                        {
                            HQ2X_PIXEL00_21
                            HQ2X_PIXEL01_20
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                                HQ2X_PIXEL11_11
                            }
                            else
                            {
                                HQ2X_PIXEL10_90
                                HQ2X_PIXEL11_60
                            }
                            break;
                        }
                    case 109:
                    case 105:
                        {
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL00_12
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_61
                                HQ2X_PIXEL10_90
                            }
                            HQ2X_PIXEL01_20
                            HQ2X_PIXEL11_22
                            break;
                        }
                    case 171:
                    case 43:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                                HQ2X_PIXEL10_11
                            }
                            else
                            {
                                HQ2X_PIXEL00_90
                                HQ2X_PIXEL10_60
                            }
                            HQ2X_PIXEL01_21
                            HQ2X_PIXEL11_20
                            break;
                        }
                    case 143:
                    case 15:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                                HQ2X_PIXEL01_12
                            }
                            else
                            {
                                HQ2X_PIXEL00_90
                                HQ2X_PIXEL01_61
                            }
                            HQ2X_PIXEL10_22
                            HQ2X_PIXEL11_20
                            break;
                        }
                    case 124:
                        {
                            HQ2X_PIXEL00_21
                            HQ2X_PIXEL01_11
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_20
                            }
                            HQ2X_PIXEL11_10
                            break;
                        }
                    case 203:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_20
                            }
                            HQ2X_PIXEL01_21
                            HQ2X_PIXEL10_10
                            HQ2X_PIXEL11_11
                            break;
                        }
                    case 62:
                        {
                            HQ2X_PIXEL00_10
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_20
                            }
                            HQ2X_PIXEL10_11
                            HQ2X_PIXEL11_21
                            break;
                        }
                    case 211:
                        {
                            HQ2X_PIXEL00_11
                            HQ2X_PIXEL01_10
                            HQ2X_PIXEL10_21
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL11_20
                            }
                            break;
                        }
                    case 118:
                        {
                            HQ2X_PIXEL00_22
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_20
                            }
                            HQ2X_PIXEL10_12
                            HQ2X_PIXEL11_10
                            break;
                        }
                    case 217:
                        {
                            HQ2X_PIXEL00_12
                            HQ2X_PIXEL01_22
                            HQ2X_PIXEL10_10
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL11_20
                            }
                            break;
                        }
                    case 110:
                        {
                            HQ2X_PIXEL00_10
                            HQ2X_PIXEL01_12
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_20
                            }
                            HQ2X_PIXEL11_22
                            break;
                        }
                    case 155:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_20
                            }
                            HQ2X_PIXEL01_10
                            HQ2X_PIXEL10_22
                            HQ2X_PIXEL11_12
                            break;
                        }
                    case 188:
                        {
                            HQ2X_PIXEL00_21
                            HQ2X_PIXEL01_11
                            HQ2X_PIXEL10_11
                            HQ2X_PIXEL11_12
                            break;
                        }
                    case 185:
                        {
                            HQ2X_PIXEL00_12
                            HQ2X_PIXEL01_22
                            HQ2X_PIXEL10_11
                            HQ2X_PIXEL11_12
                            break;
                        }
                    case 61:
                        {
                            HQ2X_PIXEL00_12
                            HQ2X_PIXEL01_11
                            HQ2X_PIXEL10_11
                            HQ2X_PIXEL11_21
                            break;
                        }
                    case 157:
                        {
                            HQ2X_PIXEL00_12
                            HQ2X_PIXEL01_11
                            HQ2X_PIXEL10_22
                            HQ2X_PIXEL11_12
                            break;
                        }
                    case 103:
                        {
                            HQ2X_PIXEL00_11
                            HQ2X_PIXEL01_12
                            HQ2X_PIXEL10_12
                            HQ2X_PIXEL11_22
                            break;
                        }
                    case 227:
                        {
                            HQ2X_PIXEL00_11
                            HQ2X_PIXEL01_21
                            HQ2X_PIXEL10_12
                            HQ2X_PIXEL11_11
                            break;
                        }
                    case 230:
                        {
                            HQ2X_PIXEL00_22
                            HQ2X_PIXEL01_12
                            HQ2X_PIXEL10_12
                            HQ2X_PIXEL11_11
                            break;
                        }
                    case 199:
                        {
                            HQ2X_PIXEL00_11
                            HQ2X_PIXEL01_12
                            HQ2X_PIXEL10_21
                            HQ2X_PIXEL11_11
                            break;
                        }
                    case 220:
                        {
                            HQ2X_PIXEL00_21
                            HQ2X_PIXEL01_11
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_10
                            }
                            else
                            {
                                HQ2X_PIXEL10_70
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL11_20
                            }
                            break;
                        }
                    case 158:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_10
                            }
                            else
                            {
                                HQ2X_PIXEL00_70
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_20
                            }
                            HQ2X_PIXEL10_22
                            HQ2X_PIXEL11_12
                            break;
                        }
                    case 234:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_10
                            }
                            else
                            {
                                HQ2X_PIXEL00_70
                            }
                            HQ2X_PIXEL01_21
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_20
                            }
                            HQ2X_PIXEL11_11
                            break;
                        }
                    case 242:
                        {
                            HQ2X_PIXEL00_22
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_10
                            }
                            else
                            {
                                HQ2X_PIXEL01_70
                            }
                            HQ2X_PIXEL10_12
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL11_20
                            }
                            break;
                        }
                    case 59:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_20
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_10
                            }
                            else
                            {
                                HQ2X_PIXEL01_70
                            }
                            HQ2X_PIXEL10_11
                            HQ2X_PIXEL11_21
                            break;
                        }
                    case 121:
                        {
                            HQ2X_PIXEL00_12
                            HQ2X_PIXEL01_22
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_20
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_10
                            }
                            else
                            {
                                HQ2X_PIXEL11_70
                            }
                            break;
                        }
                    case 87:
                        {
                            HQ2X_PIXEL00_11
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_20
                            }
                            HQ2X_PIXEL10_21
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_10
                            }
                            else
                            {
                                HQ2X_PIXEL11_70
                            }
                            break;
                        }
                    case 79:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_20
                            }
                            HQ2X_PIXEL01_12
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_10
                            }
                            else
                            {
                                HQ2X_PIXEL10_70
                            }
                            HQ2X_PIXEL11_22
                            break;
                        }
                    case 122:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_10
                            }
                            else
                            {
                                HQ2X_PIXEL00_70
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_10
                            }
                            else
                            {
                                HQ2X_PIXEL01_70
                            }
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_20
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_10
                            }
                            else
                            {
                                HQ2X_PIXEL11_70
                            }
                            break;
                        }
                    case 94:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_10
                            }
                            else
                            {
                                HQ2X_PIXEL00_70
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_20
                            }
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_10
                            }
                            else
                            {
                                HQ2X_PIXEL10_70
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_10
                            }
                            else
                            {
                                HQ2X_PIXEL11_70
                            }
                            break;
                        }
                    case 218:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_10
                            }
                            else
                            {
                                HQ2X_PIXEL00_70
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_10
                            }
                            else
                            {
                                HQ2X_PIXEL01_70
                            }
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_10
                            }
                            else
                            {
                                HQ2X_PIXEL10_70
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL11_20
                            }
                            break;
                        }
                    case 91:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_20
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_10
                            }
                            else
                            {
                                HQ2X_PIXEL01_70
                            }
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_10
                            }
                            else
                            {
                                HQ2X_PIXEL10_70
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_10
                            }
                            else
                            {
                                HQ2X_PIXEL11_70
                            }
                            break;
                        }
                    case 229:
                        {
                            HQ2X_PIXEL00_20
                            HQ2X_PIXEL01_20
                            HQ2X_PIXEL10_12
                            HQ2X_PIXEL11_11
                            break;
                        }
                    case 167:
                        {
                            HQ2X_PIXEL00_11
                            HQ2X_PIXEL01_12
                            HQ2X_PIXEL10_20
                            HQ2X_PIXEL11_20
                            break;
                        }
                    case 173:
                        {
                            HQ2X_PIXEL00_12
                            HQ2X_PIXEL01_20
                            HQ2X_PIXEL10_11
                            HQ2X_PIXEL11_20
                            break;
                        }
                    case 181:
                        {
                            HQ2X_PIXEL00_20
                            HQ2X_PIXEL01_11
                            HQ2X_PIXEL10_20
                            HQ2X_PIXEL11_12
                            break;
                        }
                    case 186:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_10
                            }
                            else
                            {
                                HQ2X_PIXEL00_70
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_10
                            }
                            else
                            {
                                HQ2X_PIXEL01_70
                            }
                            HQ2X_PIXEL10_11
                            HQ2X_PIXEL11_12
                            break;
                        }
                    case 115:
                        {
                            HQ2X_PIXEL00_11
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_10
                            }
                            else
                            {
                                HQ2X_PIXEL01_70
                            }
                            HQ2X_PIXEL10_12
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_10
                            }
                            else
                            {
                                HQ2X_PIXEL11_70
                            }
                            break;
                        }
                    case 93:
                        {
                            HQ2X_PIXEL00_12
                            HQ2X_PIXEL01_11
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_10
                            }
                            else
                            {
                                HQ2X_PIXEL10_70
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_10
                            }
                            else
                            {
                                HQ2X_PIXEL11_70
                            }
                            break;
                        }
                    case 206:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_10
                            }
                            else
                            {
                                HQ2X_PIXEL00_70
                            }
                            HQ2X_PIXEL01_12
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_10
                            }
                            else
                            {
                                HQ2X_PIXEL10_70
                            }
                            HQ2X_PIXEL11_11
                            break;
                        }
                    case 205:
                    case 201:
                        {
                            HQ2X_PIXEL00_12
                            HQ2X_PIXEL01_20
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_10
                            }
                            else
                            {
                                HQ2X_PIXEL10_70
                            }
                            HQ2X_PIXEL11_11
                            break;
                        }
                    case 174:
                    case 46:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_10
                            }
                            else
                            {
                                HQ2X_PIXEL00_70
                            }
                            HQ2X_PIXEL01_12
                            HQ2X_PIXEL10_11
                            HQ2X_PIXEL11_20
                            break;
                        }
                    case 179:
                    case 147:
                        {
                            HQ2X_PIXEL00_11
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_10
                            }
                            else
                            {
                                HQ2X_PIXEL01_70
                            }
                            HQ2X_PIXEL10_20
                            HQ2X_PIXEL11_12
                            break;
                        }
                    case 117:
                    case 116:
                        {
                            HQ2X_PIXEL00_20
                            HQ2X_PIXEL01_11
                            HQ2X_PIXEL10_12
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_10
                            }
                            else
                            {
                                HQ2X_PIXEL11_70
                            }
                            break;
                        }
                    case 189:
                        {
                            HQ2X_PIXEL00_12
                            HQ2X_PIXEL01_11
                            HQ2X_PIXEL10_11
                            HQ2X_PIXEL11_12
                            break;
                        }
                    case 231:
                        {
                            HQ2X_PIXEL00_11
                            HQ2X_PIXEL01_12
                            HQ2X_PIXEL10_12
                            HQ2X_PIXEL11_11
                            break;
                        }
                    case 126:
                        {
                            HQ2X_PIXEL00_10
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_20
                            }
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_20
                            }
                            HQ2X_PIXEL11_10
                            break;
                        }
                    case 219:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_20
                            }
                            HQ2X_PIXEL01_10
                            HQ2X_PIXEL10_10
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL11_20
                            }
                            break;
                        }
                    case 125:
                        {
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL00_12
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_61
                                HQ2X_PIXEL10_90
                            }
                            HQ2X_PIXEL01_11
                            HQ2X_PIXEL11_10
                            break;
                        }
                    case 221:
                        {
                            HQ2X_PIXEL00_12
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL01_11
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_60
                                HQ2X_PIXEL11_90
                            }
                            HQ2X_PIXEL10_10
                            break;
                        }
                    case 207:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                                HQ2X_PIXEL01_12
                            }
                            else
                            {
                                HQ2X_PIXEL00_90
                                HQ2X_PIXEL01_61
                            }
                            HQ2X_PIXEL10_10
                            HQ2X_PIXEL11_11
                            break;
                        }
                    case 238:
                        {
                            HQ2X_PIXEL00_10
                            HQ2X_PIXEL01_12
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                                HQ2X_PIXEL11_11
                            }
                            else
                            {
                                HQ2X_PIXEL10_90
                                HQ2X_PIXEL11_60
                            }
                            break;
                        }
                    case 190:
                        {
                            HQ2X_PIXEL00_10
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                                HQ2X_PIXEL11_12
                            }
                            else
                            {
                                HQ2X_PIXEL01_90
                                HQ2X_PIXEL11_61
                            }
                            HQ2X_PIXEL10_11
                            break;
                        }
                    case 187:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                                HQ2X_PIXEL10_11
                            }
                            else
                            {
                                HQ2X_PIXEL00_90
                                HQ2X_PIXEL10_60
                            }
                            HQ2X_PIXEL01_10
                            HQ2X_PIXEL11_12
                            break;
                        }
                    case 243:
                        {
                            HQ2X_PIXEL00_11
                            HQ2X_PIXEL01_10
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL10_12
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_61
                                HQ2X_PIXEL11_90
                            }
                            break;
                        }
                    case 119:
                        {
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL00_11
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_60
                                HQ2X_PIXEL01_90
                            }
                            HQ2X_PIXEL10_12
                            HQ2X_PIXEL11_10
                            break;
                        }
                    case 237:
                    case 233:
                        {
                            HQ2X_PIXEL00_12
                            HQ2X_PIXEL01_20
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_100
                            }
                            HQ2X_PIXEL11_11
                            break;
                        }
                    case 175:
                    case 47:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_100
                            }
                            HQ2X_PIXEL01_12
                            HQ2X_PIXEL10_11
                            HQ2X_PIXEL11_20
                            break;
                        }
                    case 183:
                    case 151:
                        {
                            HQ2X_PIXEL00_11
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_100
                            }
                            HQ2X_PIXEL10_20
                            HQ2X_PIXEL11_12
                            break;
                        }
                    case 245:
                    case 244:
                        {
                            HQ2X_PIXEL00_20
                            HQ2X_PIXEL01_11
                            HQ2X_PIXEL10_12
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL11_100
                            }
                            break;
                        }
                    case 250:
                        {
                            HQ2X_PIXEL00_10
                            HQ2X_PIXEL01_10
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_20
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL11_20
                            }
                            break;
                        }
                    case 123:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_20
                            }
                            HQ2X_PIXEL01_10
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_20
                            }
                            HQ2X_PIXEL11_10
                            break;
                        }
                    case 95:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_20
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_20
                            }
                            HQ2X_PIXEL10_10
                            HQ2X_PIXEL11_10
                            break;
                        }
                    case 222:
                        {
                            HQ2X_PIXEL00_10
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_20
                            }
                            HQ2X_PIXEL10_10
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL11_20
                            }
                            break;
                        }
                    case 252:
                        {
                            HQ2X_PIXEL00_21
                            HQ2X_PIXEL01_11
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_20
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL11_100
                            }
                            break;
                        }
                    case 249:
                        {
                            HQ2X_PIXEL00_12
                            HQ2X_PIXEL01_22
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_100
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL11_20
                            }
                            break;
                        }
                    case 235:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_20
                            }
                            HQ2X_PIXEL01_21
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_100
                            }
                            HQ2X_PIXEL11_11
                            break;
                        }
                    case 111:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_100
                            }
                            HQ2X_PIXEL01_12
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_20
                            }
                            HQ2X_PIXEL11_22
                            break;
                        }
                    case 63:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_100
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_20
                            }
                            HQ2X_PIXEL10_11
                            HQ2X_PIXEL11_21
                            break;
                        }
                    case 159:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_20
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_100
                            }
                            HQ2X_PIXEL10_22
                            HQ2X_PIXEL11_12
                            break;
                        }
                    case 215:
                        {
                            HQ2X_PIXEL00_11
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_100
                            }
                            HQ2X_PIXEL10_21
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL11_20
                            }
                            break;
                        }
                    case 246:
                        {
                            HQ2X_PIXEL00_22
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_20
                            }
                            HQ2X_PIXEL10_12
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL11_100
                            }
                            break;
                        }
                    case 254:
                        {
                            HQ2X_PIXEL00_10
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_20
                            }
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_20
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL11_100
                            }
                            break;
                        }
                    case 253:
                        {
                            HQ2X_PIXEL00_12
                            HQ2X_PIXEL01_11
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_100
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL11_100
                            }
                            break;
                        }
                    case 251:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_20
                            }
                            HQ2X_PIXEL01_10
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_100
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL11_20
                            }
                            break;
                        }
                    case 239:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_100
                            }
                            HQ2X_PIXEL01_12
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_100
                            }
                            HQ2X_PIXEL11_11
                            break;
                        }
                    case 127:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_100
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_20
                            }
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_20
                            }
                            HQ2X_PIXEL11_10
                            break;
                        }
                    case 191:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_100
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_100
                            }
                            HQ2X_PIXEL10_11
                            HQ2X_PIXEL11_12
                            break;
                        }
                    case 223:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_20
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_100
                            }
                            HQ2X_PIXEL10_10
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL11_20
                            }
                            break;
                        }
                    case 247:
                        {
                            HQ2X_PIXEL00_11
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_100
                            }
                            HQ2X_PIXEL10_12
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL11_100
                            }
                            break;
                        }
                    case 255:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ2X_PIXEL00_0
                            }
                            else
                            {
                                HQ2X_PIXEL00_100
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ2X_PIXEL01_0
                            }
                            else
                            {
                                HQ2X_PIXEL01_100
                            }
                            if (HQX_Diff(W8, W4))
                            {
                                HQ2X_PIXEL10_0
                            }
                            else
                            {
                                HQ2X_PIXEL10_100
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ2X_PIXEL11_0
                            }
                            else
                            {
                                HQ2X_PIXEL11_100
                            }
                            break;
                        }
                }

                switch (C)
                {
                    case 0:
                        BmpBufX_[P + 2] = C00;
                        BmpBufX_[L + P + 2] = C10;
                        BmpBufX_[P + 4 + 2] = C01;
                        BmpBufX_[L + 4 + P + 2] = C11;
                        break;
                    case 1:
                        BmpBufX_[P + 1] = C00;
                        BmpBufX_[L + P + 1] = C10;
                        BmpBufX_[P + 4 + 1] = C01;
                        BmpBufX_[L + 4 + P + 1] = C11;
                        break;
                    case 2:
                        BmpBufX_[P + 0] = C00;
                        BmpBufX_[L + P + 0] = C10;
                        BmpBufX_[P + 4 + 0] = C01;
                        BmpBufX_[L + 4 + P + 0] = C11;
                        break;
                }
            }

            P += 8;
        }
        P += L;
    }
}
