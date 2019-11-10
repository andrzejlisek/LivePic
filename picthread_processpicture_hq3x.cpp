#include "picthread.h"

void PicThread::HQ3X_Process1(uchar * BmpBuf_, uchar * BmpBufX_, int MinY, int MaxY, int PicW_, int PicH_, int &P, int L)
{
    int LL = L << 1;
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
            int R10, G10, B10;
            int R11, G11, B11;
            int R12, G12, B12;
            int R20, G20, B20;
            int R21, G21, B21;
            int R22, G22, B22;

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
                        HQ3X_PIXEL00_RGB_2
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_2
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_2
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_2
                        break;
                    }
                case 2:
                case 34:
                case 130:
                case 162:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_2
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_2
                        break;
                    }
                case 16:
                case 17:
                case 48:
                case 49:
                    {
                        HQ3X_PIXEL00_RGB_2
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_2
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 64:
                case 65:
                case 68:
                case 69:
                    {
                        HQ3X_PIXEL00_RGB_2
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_2
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 8:
                case 12:
                case 136:
                case 140:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_2
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_2
                        break;
                    }
                case 3:
                case 35:
                case 131:
                case 163:
                    {
                        HQ3X_PIXEL00_RGB_1L
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_2
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_2
                        break;
                    }
                case 6:
                case 38:
                case 134:
                case 166:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1R
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_2
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_2
                        break;
                    }
                case 20:
                case 21:
                case 52:
                case 53:
                    {
                        HQ3X_PIXEL00_RGB_2
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1U
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_2
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 144:
                case 145:
                case 176:
                case 177:
                    {
                        HQ3X_PIXEL00_RGB_2
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_2
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1D
                        break;
                    }
                case 192:
                case 193:
                case 196:
                case 197:
                    {
                        HQ3X_PIXEL00_RGB_2
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_2
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1R
                        break;
                    }
                case 96:
                case 97:
                case 100:
                case 101:
                    {
                        HQ3X_PIXEL00_RGB_2
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_2
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1L
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 40:
                case 44:
                case 168:
                case 172:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_2
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1D
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_2
                        break;
                    }
                case 9:
                case 13:
                case 137:
                case 141:
                    {
                        HQ3X_PIXEL00_RGB_1U
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_2
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_2
                        break;
                    }
                case 18:
                case 50:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL02_RGB_1M
                            HQ3X_PIXEL12_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL02_RGB_4
                            HQ3X_PIXEL12_RGB_3
                        }
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_2
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 80:
                case 81:
                    {
                        HQ3X_PIXEL00_RGB_2
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_1M
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL12_RGB_C
                            HQ3X_PIXEL21_RGB_C
                            HQ3X_PIXEL22_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL12_RGB_3
                            HQ3X_PIXEL21_RGB_3
                            HQ3X_PIXEL22_RGB_4
                        }
                        break;
                    }
                case 72:
                case 76:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_2
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL10_RGB_C
                            HQ3X_PIXEL20_RGB_1M
                            HQ3X_PIXEL21_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL10_RGB_3
                            HQ3X_PIXEL20_RGB_4
                            HQ3X_PIXEL21_RGB_3
                        }
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 10:
                case 138:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_1M
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL10_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_4
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL10_RGB_3
                        }
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_2
                        break;
                    }
                case 66:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 24:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 7:
                case 39:
                case 135:
                    {
                        HQ3X_PIXEL00_RGB_1L
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1R
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_2
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_2
                        break;
                    }
                case 148:
                case 149:
                case 180:
                    {
                        HQ3X_PIXEL00_RGB_2
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1U
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_2
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1D
                        break;
                    }
                case 224:
                case 228:
                case 225:
                    {
                        HQ3X_PIXEL00_RGB_2
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_2
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1L
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1R
                        break;
                    }
                case 41:
                case 169:
                case 45:
                    {
                        HQ3X_PIXEL00_RGB_1U
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_2
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1D
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_2
                        break;
                    }
                case 22:
                case 54:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL02_RGB_C
                            HQ3X_PIXEL12_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL02_RGB_4
                            HQ3X_PIXEL12_RGB_3
                        }
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_2
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 208:
                case 209:
                    {
                        HQ3X_PIXEL00_RGB_2
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_1M
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL12_RGB_C
                            HQ3X_PIXEL21_RGB_C
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL12_RGB_3
                            HQ3X_PIXEL21_RGB_3
                            HQ3X_PIXEL22_RGB_4
                        }
                        break;
                    }
                case 104:
                case 108:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_2
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL10_RGB_C
                            HQ3X_PIXEL20_RGB_C
                            HQ3X_PIXEL21_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL10_RGB_3
                            HQ3X_PIXEL20_RGB_4
                            HQ3X_PIXEL21_RGB_3
                        }
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 11:
                case 139:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL10_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_4
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL10_RGB_3
                        }
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_2
                        break;
                    }
                case 19:
                case 51:
                    {
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL00_RGB_1L
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL02_RGB_1M
                            HQ3X_PIXEL12_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                            HQ3X_PIXEL01_RGB_6
                            HQ3X_PIXEL02_RGB_5
                            HQ3X_PIXEL12_RGB_1
                        }
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_2
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 146:
                case 178:
                    {
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL02_RGB_1M
                            HQ3X_PIXEL12_RGB_C
                            HQ3X_PIXEL22_RGB_1D
                        }
                        else
                        {
                            HQ3X_PIXEL01_RGB_1
                            HQ3X_PIXEL02_RGB_5
                            HQ3X_PIXEL12_RGB_6
                            HQ3X_PIXEL22_RGB_2
                        }
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_2
                        HQ3X_PIXEL21_RGB_1
                        break;
                    }
                case 84:
                case 85:
                    {
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL02_RGB_1U
                            HQ3X_PIXEL12_RGB_C
                            HQ3X_PIXEL21_RGB_C
                            HQ3X_PIXEL22_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_2
                            HQ3X_PIXEL12_RGB_6
                            HQ3X_PIXEL21_RGB_1
                            HQ3X_PIXEL22_RGB_5
                        }
                        HQ3X_PIXEL00_RGB_2
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_1M
                        break;
                    }
                case 112:
                case 113:
                    {
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL12_RGB_C
                            HQ3X_PIXEL20_RGB_1L
                            HQ3X_PIXEL21_RGB_C
                            HQ3X_PIXEL22_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL12_RGB_1
                            HQ3X_PIXEL20_RGB_2
                            HQ3X_PIXEL21_RGB_6
                            HQ3X_PIXEL22_RGB_5
                        }
                        HQ3X_PIXEL00_RGB_2
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        break;
                    }
                case 200:
                case 204:
                    {
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL10_RGB_C
                            HQ3X_PIXEL20_RGB_1M
                            HQ3X_PIXEL21_RGB_C
                            HQ3X_PIXEL22_RGB_1R
                        }
                        else
                        {
                            HQ3X_PIXEL10_RGB_1
                            HQ3X_PIXEL20_RGB_5
                            HQ3X_PIXEL21_RGB_6
                            HQ3X_PIXEL22_RGB_2
                        }
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_2
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        break;
                    }
                case 73:
                case 77:
                    {
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL00_RGB_1U
                            HQ3X_PIXEL10_RGB_C
                            HQ3X_PIXEL20_RGB_1M
                            HQ3X_PIXEL21_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                            HQ3X_PIXEL10_RGB_6
                            HQ3X_PIXEL20_RGB_5
                            HQ3X_PIXEL21_RGB_1
                        }
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_2
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 42:
                case 170:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_1M
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL10_RGB_C
                            HQ3X_PIXEL20_RGB_1D
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_5
                            HQ3X_PIXEL01_RGB_1
                            HQ3X_PIXEL10_RGB_6
                            HQ3X_PIXEL20_RGB_2
                        }
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_2
                        break;
                    }
                case 14:
                case 142:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_1M
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL02_RGB_1R
                            HQ3X_PIXEL10_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_5
                            HQ3X_PIXEL01_RGB_6
                            HQ3X_PIXEL02_RGB_2
                            HQ3X_PIXEL10_RGB_1
                        }
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_2
                        break;
                    }
                case 67:
                    {
                        HQ3X_PIXEL00_RGB_1L
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 70:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1R
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 28:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1U
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 152:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1D
                        break;
                    }
                case 194:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1R
                        break;
                    }
                case 98:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1L
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 56:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1D
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 25:
                    {
                        HQ3X_PIXEL00_RGB_1U
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 26:
                case 31:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                            HQ3X_PIXEL10_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_4
                            HQ3X_PIXEL10_RGB_3
                        }
                        HQ3X_PIXEL01_RGB_C
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL02_RGB_C
                            HQ3X_PIXEL12_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_4
                            HQ3X_PIXEL12_RGB_3
                        }
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 82:
                case 214:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL02_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL02_RGB_4
                        }
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1M
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL21_RGB_C
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL21_RGB_3
                            HQ3X_PIXEL22_RGB_4
                        }
                        break;
                    }
                case 88:
                case 248:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL11_RGB
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL10_RGB_C
                            HQ3X_PIXEL20_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL10_RGB_3
                            HQ3X_PIXEL20_RGB_4
                        }
                        HQ3X_PIXEL21_RGB_C
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL12_RGB_C
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL12_RGB_3
                            HQ3X_PIXEL22_RGB_4
                        }
                        break;
                    }
                case 74:
                case 107:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                            HQ3X_PIXEL01_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_4
                            HQ3X_PIXEL01_RGB_3
                        }
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL20_RGB_C
                            HQ3X_PIXEL21_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL20_RGB_4
                            HQ3X_PIXEL21_RGB_3
                        }
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 27:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL10_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_4
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL10_RGB_3
                        }
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 86:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL02_RGB_C
                            HQ3X_PIXEL12_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL02_RGB_4
                            HQ3X_PIXEL12_RGB_3
                        }
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 216:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_1M
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL12_RGB_C
                            HQ3X_PIXEL21_RGB_C
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL12_RGB_3
                            HQ3X_PIXEL21_RGB_3
                            HQ3X_PIXEL22_RGB_4
                        }
                        break;
                    }
                case 106:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL10_RGB_C
                            HQ3X_PIXEL20_RGB_C
                            HQ3X_PIXEL21_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL10_RGB_3
                            HQ3X_PIXEL20_RGB_4
                            HQ3X_PIXEL21_RGB_3
                        }
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 30:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL02_RGB_C
                            HQ3X_PIXEL12_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL02_RGB_4
                            HQ3X_PIXEL12_RGB_3
                        }
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 210:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_1M
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL12_RGB_C
                            HQ3X_PIXEL21_RGB_C
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL12_RGB_3
                            HQ3X_PIXEL21_RGB_3
                            HQ3X_PIXEL22_RGB_4
                        }
                        break;
                    }
                case 120:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL10_RGB_C
                            HQ3X_PIXEL20_RGB_C
                            HQ3X_PIXEL21_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL10_RGB_3
                            HQ3X_PIXEL20_RGB_4
                            HQ3X_PIXEL21_RGB_3
                        }
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 75:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL10_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_4
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL10_RGB_3
                        }
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 29:
                    {
                        HQ3X_PIXEL00_RGB_1U
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1U
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 198:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1R
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1R
                        break;
                    }
                case 184:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1D
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1D
                        break;
                    }
                case 99:
                    {
                        HQ3X_PIXEL00_RGB_1L
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1L
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 57:
                    {
                        HQ3X_PIXEL00_RGB_1U
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1D
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 71:
                    {
                        HQ3X_PIXEL00_RGB_1L
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1R
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 156:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1U
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1D
                        break;
                    }
                case 226:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1L
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1R
                        break;
                    }
                case 60:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1U
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1D
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 195:
                    {
                        HQ3X_PIXEL00_RGB_1L
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1R
                        break;
                    }
                case 102:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1R
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1L
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 153:
                    {
                        HQ3X_PIXEL00_RGB_1U
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1D
                        break;
                    }
                case 58:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                        }
                        HQ3X_PIXEL01_RGB_C
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL02_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_2
                        }
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1D
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 83:
                    {
                        HQ3X_PIXEL00_RGB_1L
                        HQ3X_PIXEL01_RGB_C
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL02_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_2
                        }
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_C
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL22_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL22_RGB_2
                        }
                        break;
                    }
                case 92:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1U
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL20_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL20_RGB_2
                        }
                        HQ3X_PIXEL21_RGB_C
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL22_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL22_RGB_2
                        }
                        break;
                    }
                case 202:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                        }
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL20_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL20_RGB_2
                        }
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1R
                        break;
                    }
                case 78:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                        }
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1R
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL20_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL20_RGB_2
                        }
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 154:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                        }
                        HQ3X_PIXEL01_RGB_C
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL02_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_2
                        }
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1D
                        break;
                    }
                case 114:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_C
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL02_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_2
                        }
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1L
                        HQ3X_PIXEL21_RGB_C
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL22_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL22_RGB_2
                        }
                        break;
                    }
                case 89:
                    {
                        HQ3X_PIXEL00_RGB_1U
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL20_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL20_RGB_2
                        }
                        HQ3X_PIXEL21_RGB_C
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL22_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL22_RGB_2
                        }
                        break;
                    }
                case 90:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                        }
                        HQ3X_PIXEL01_RGB_C
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL02_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_2
                        }
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL20_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL20_RGB_2
                        }
                        HQ3X_PIXEL21_RGB_C
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL22_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL22_RGB_2
                        }
                        break;
                    }
                case 55:
                case 23:
                    {
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL00_RGB_1L
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL02_RGB_C
                            HQ3X_PIXEL12_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                            HQ3X_PIXEL01_RGB_6
                            HQ3X_PIXEL02_RGB_5
                            HQ3X_PIXEL12_RGB_1
                        }
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_2
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 182:
                case 150:
                    {
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL02_RGB_C
                            HQ3X_PIXEL12_RGB_C
                            HQ3X_PIXEL22_RGB_1D
                        }
                        else
                        {
                            HQ3X_PIXEL01_RGB_1
                            HQ3X_PIXEL02_RGB_5
                            HQ3X_PIXEL12_RGB_6
                            HQ3X_PIXEL22_RGB_2
                        }
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_2
                        HQ3X_PIXEL21_RGB_1
                        break;
                    }
                case 213:
                case 212:
                    {
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL02_RGB_1U
                            HQ3X_PIXEL12_RGB_C
                            HQ3X_PIXEL21_RGB_C
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_2
                            HQ3X_PIXEL12_RGB_6
                            HQ3X_PIXEL21_RGB_1
                            HQ3X_PIXEL22_RGB_5
                        }
                        HQ3X_PIXEL00_RGB_2
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_1M
                        break;
                    }
                case 241:
                case 240:
                    {
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL12_RGB_C
                            HQ3X_PIXEL20_RGB_1L
                            HQ3X_PIXEL21_RGB_C
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL12_RGB_1
                            HQ3X_PIXEL20_RGB_2
                            HQ3X_PIXEL21_RGB_6
                            HQ3X_PIXEL22_RGB_5
                        }
                        HQ3X_PIXEL00_RGB_2
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        break;
                    }
                case 236:
                case 232:
                    {
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL10_RGB_C
                            HQ3X_PIXEL20_RGB_C
                            HQ3X_PIXEL21_RGB_C
                            HQ3X_PIXEL22_RGB_1R
                        }
                        else
                        {
                            HQ3X_PIXEL10_RGB_1
                            HQ3X_PIXEL20_RGB_5
                            HQ3X_PIXEL21_RGB_6
                            HQ3X_PIXEL22_RGB_2
                        }
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_2
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        break;
                    }
                case 109:
                case 105:
                    {
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL00_RGB_1U
                            HQ3X_PIXEL10_RGB_C
                            HQ3X_PIXEL20_RGB_C
                            HQ3X_PIXEL21_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                            HQ3X_PIXEL10_RGB_6
                            HQ3X_PIXEL20_RGB_5
                            HQ3X_PIXEL21_RGB_1
                        }
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_2
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 171:
                case 43:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL10_RGB_C
                            HQ3X_PIXEL20_RGB_1D
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_5
                            HQ3X_PIXEL01_RGB_1
                            HQ3X_PIXEL10_RGB_6
                            HQ3X_PIXEL20_RGB_2
                        }
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_2
                        break;
                    }
                case 143:
                case 15:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL02_RGB_1R
                            HQ3X_PIXEL10_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_5
                            HQ3X_PIXEL01_RGB_6
                            HQ3X_PIXEL02_RGB_2
                            HQ3X_PIXEL10_RGB_1
                        }
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_2
                        break;
                    }
                case 124:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1U
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL10_RGB_C
                            HQ3X_PIXEL20_RGB_C
                            HQ3X_PIXEL21_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL10_RGB_3
                            HQ3X_PIXEL20_RGB_4
                            HQ3X_PIXEL21_RGB_3
                        }
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 203:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL10_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_4
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL10_RGB_3
                        }
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1R
                        break;
                    }
                case 62:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL02_RGB_C
                            HQ3X_PIXEL12_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL02_RGB_4
                            HQ3X_PIXEL12_RGB_3
                        }
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_1D
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 211:
                    {
                        HQ3X_PIXEL00_RGB_1L
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_1M
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL12_RGB_C
                            HQ3X_PIXEL21_RGB_C
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL12_RGB_3
                            HQ3X_PIXEL21_RGB_3
                            HQ3X_PIXEL22_RGB_4
                        }
                        break;
                    }
                case 118:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL02_RGB_C
                            HQ3X_PIXEL12_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL02_RGB_4
                            HQ3X_PIXEL12_RGB_3
                        }
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_1L
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 217:
                    {
                        HQ3X_PIXEL00_RGB_1U
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_1M
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL12_RGB_C
                            HQ3X_PIXEL21_RGB_C
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL12_RGB_3
                            HQ3X_PIXEL21_RGB_3
                            HQ3X_PIXEL22_RGB_4
                        }
                        break;
                    }
                case 110:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1R
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL10_RGB_C
                            HQ3X_PIXEL20_RGB_C
                            HQ3X_PIXEL21_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL10_RGB_3
                            HQ3X_PIXEL20_RGB_4
                            HQ3X_PIXEL21_RGB_3
                        }
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 155:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL10_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_4
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL10_RGB_3
                        }
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1D
                        break;
                    }
                case 188:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1U
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1D
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1D
                        break;
                    }
                case 185:
                    {
                        HQ3X_PIXEL00_RGB_1U
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1D
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1D
                        break;
                    }
                case 61:
                    {
                        HQ3X_PIXEL00_RGB_1U
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1U
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1D
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 157:
                    {
                        HQ3X_PIXEL00_RGB_1U
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1U
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1D
                        break;
                    }
                case 103:
                    {
                        HQ3X_PIXEL00_RGB_1L
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1R
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1L
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 227:
                    {
                        HQ3X_PIXEL00_RGB_1L
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1L
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1R
                        break;
                    }
                case 230:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1R
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1L
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1R
                        break;
                    }
                case 199:
                    {
                        HQ3X_PIXEL00_RGB_1L
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1R
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1R
                        break;
                    }
                case 220:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1U
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL20_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL20_RGB_2
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL12_RGB_C
                            HQ3X_PIXEL21_RGB_C
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL12_RGB_3
                            HQ3X_PIXEL21_RGB_3
                            HQ3X_PIXEL22_RGB_4
                        }
                        break;
                    }
                case 158:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL02_RGB_C
                            HQ3X_PIXEL12_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL02_RGB_4
                            HQ3X_PIXEL12_RGB_3
                        }
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1D
                        break;
                    }
                case 234:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                        }
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL10_RGB_C
                            HQ3X_PIXEL20_RGB_C
                            HQ3X_PIXEL21_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL10_RGB_3
                            HQ3X_PIXEL20_RGB_4
                            HQ3X_PIXEL21_RGB_3
                        }
                        HQ3X_PIXEL22_RGB_1R
                        break;
                    }
                case 242:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_C
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL02_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_2
                        }
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_1L
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL12_RGB_C
                            HQ3X_PIXEL21_RGB_C
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL12_RGB_3
                            HQ3X_PIXEL21_RGB_3
                            HQ3X_PIXEL22_RGB_4
                        }
                        break;
                    }
                case 59:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL10_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_4
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL10_RGB_3
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL02_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_2
                        }
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1D
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 121:
                    {
                        HQ3X_PIXEL00_RGB_1U
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL10_RGB_C
                            HQ3X_PIXEL20_RGB_C
                            HQ3X_PIXEL21_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL10_RGB_3
                            HQ3X_PIXEL20_RGB_4
                            HQ3X_PIXEL21_RGB_3
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL22_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL22_RGB_2
                        }
                        break;
                    }
                case 87:
                    {
                        HQ3X_PIXEL00_RGB_1L
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL02_RGB_C
                            HQ3X_PIXEL12_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL02_RGB_4
                            HQ3X_PIXEL12_RGB_3
                        }
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_C
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL22_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL22_RGB_2
                        }
                        break;
                    }
                case 79:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL10_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_4
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL10_RGB_3
                        }
                        HQ3X_PIXEL02_RGB_1R
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL20_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL20_RGB_2
                        }
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 122:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                        }
                        HQ3X_PIXEL01_RGB_C
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL02_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_2
                        }
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL10_RGB_C
                            HQ3X_PIXEL20_RGB_C
                            HQ3X_PIXEL21_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL10_RGB_3
                            HQ3X_PIXEL20_RGB_4
                            HQ3X_PIXEL21_RGB_3
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL22_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL22_RGB_2
                        }
                        break;
                    }
                case 94:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL02_RGB_C
                            HQ3X_PIXEL12_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL02_RGB_4
                            HQ3X_PIXEL12_RGB_3
                        }
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL20_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL20_RGB_2
                        }
                        HQ3X_PIXEL21_RGB_C
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL22_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL22_RGB_2
                        }
                        break;
                    }
                case 218:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                        }
                        HQ3X_PIXEL01_RGB_C
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL02_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_2
                        }
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL20_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL20_RGB_2
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL12_RGB_C
                            HQ3X_PIXEL21_RGB_C
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL12_RGB_3
                            HQ3X_PIXEL21_RGB_3
                            HQ3X_PIXEL22_RGB_4
                        }
                        break;
                    }
                case 91:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL10_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_4
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL10_RGB_3
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL02_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_2
                        }
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL20_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL20_RGB_2
                        }
                        HQ3X_PIXEL21_RGB_C
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL22_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL22_RGB_2
                        }
                        break;
                    }
                case 229:
                    {
                        HQ3X_PIXEL00_RGB_2
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_2
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1L
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1R
                        break;
                    }
                case 167:
                    {
                        HQ3X_PIXEL00_RGB_1L
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1R
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_2
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_2
                        break;
                    }
                case 173:
                    {
                        HQ3X_PIXEL00_RGB_1U
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_2
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1D
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_2
                        break;
                    }
                case 181:
                    {
                        HQ3X_PIXEL00_RGB_2
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1U
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_2
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1D
                        break;
                    }
                case 186:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                        }
                        HQ3X_PIXEL01_RGB_C
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL02_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_2
                        }
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1D
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1D
                        break;
                    }
                case 115:
                    {
                        HQ3X_PIXEL00_RGB_1L
                        HQ3X_PIXEL01_RGB_C
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL02_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_2
                        }
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1L
                        HQ3X_PIXEL21_RGB_C
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL22_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL22_RGB_2
                        }
                        break;
                    }
                case 93:
                    {
                        HQ3X_PIXEL00_RGB_1U
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1U
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL20_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL20_RGB_2
                        }
                        HQ3X_PIXEL21_RGB_C
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL22_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL22_RGB_2
                        }
                        break;
                    }
                case 206:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                        }
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1R
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL20_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL20_RGB_2
                        }
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1R
                        break;
                    }
                case 205:
                case 201:
                    {
                        HQ3X_PIXEL00_RGB_1U
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_2
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL20_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL20_RGB_2
                        }
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1R
                        break;
                    }
                case 174:
                case 46:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                        }
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1R
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1D
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_2
                        break;
                    }
                case 179:
                case 147:
                    {
                        HQ3X_PIXEL00_RGB_1L
                        HQ3X_PIXEL01_RGB_C
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL02_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_2
                        }
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_2
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1D
                        break;
                    }
                case 117:
                case 116:
                    {
                        HQ3X_PIXEL00_RGB_2
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1U
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1L
                        HQ3X_PIXEL21_RGB_C
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL22_RGB_1M
                        }
                        else
                        {
                            HQ3X_PIXEL22_RGB_2
                        }
                        break;
                    }
                case 189:
                    {
                        HQ3X_PIXEL00_RGB_1U
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1U
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1D
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1D
                        break;
                    }
                case 231:
                    {
                        HQ3X_PIXEL00_RGB_1L
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1R
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1L
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1R
                        break;
                    }
                case 126:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL02_RGB_C
                            HQ3X_PIXEL12_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL02_RGB_4
                            HQ3X_PIXEL12_RGB_3
                        }
                        HQ3X_PIXEL11_RGB
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL10_RGB_C
                            HQ3X_PIXEL20_RGB_C
                            HQ3X_PIXEL21_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL10_RGB_3
                            HQ3X_PIXEL20_RGB_4
                            HQ3X_PIXEL21_RGB_3
                        }
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 219:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL10_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_4
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL10_RGB_3
                        }
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_1M
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL12_RGB_C
                            HQ3X_PIXEL21_RGB_C
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL12_RGB_3
                            HQ3X_PIXEL21_RGB_3
                            HQ3X_PIXEL22_RGB_4
                        }
                        break;
                    }
                case 125:
                    {
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL00_RGB_1U
                            HQ3X_PIXEL10_RGB_C
                            HQ3X_PIXEL20_RGB_C
                            HQ3X_PIXEL21_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                            HQ3X_PIXEL10_RGB_6
                            HQ3X_PIXEL20_RGB_5
                            HQ3X_PIXEL21_RGB_1
                        }
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1U
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 221:
                    {
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL02_RGB_1U
                            HQ3X_PIXEL12_RGB_C
                            HQ3X_PIXEL21_RGB_C
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_2
                            HQ3X_PIXEL12_RGB_6
                            HQ3X_PIXEL21_RGB_1
                            HQ3X_PIXEL22_RGB_5
                        }
                        HQ3X_PIXEL00_RGB_1U
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_1M
                        break;
                    }
                case 207:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL02_RGB_1R
                            HQ3X_PIXEL10_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_5
                            HQ3X_PIXEL01_RGB_6
                            HQ3X_PIXEL02_RGB_2
                            HQ3X_PIXEL10_RGB_1
                        }
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1R
                        break;
                    }
                case 238:
                    {
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL10_RGB_C
                            HQ3X_PIXEL20_RGB_C
                            HQ3X_PIXEL21_RGB_C
                            HQ3X_PIXEL22_RGB_1R
                        }
                        else
                        {
                            HQ3X_PIXEL10_RGB_1
                            HQ3X_PIXEL20_RGB_5
                            HQ3X_PIXEL21_RGB_6
                            HQ3X_PIXEL22_RGB_2
                        }
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1R
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        break;
                    }
                case 190:
                    {
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL02_RGB_C
                            HQ3X_PIXEL12_RGB_C
                            HQ3X_PIXEL22_RGB_1D
                        }
                        else
                        {
                            HQ3X_PIXEL01_RGB_1
                            HQ3X_PIXEL02_RGB_5
                            HQ3X_PIXEL12_RGB_6
                            HQ3X_PIXEL22_RGB_2
                        }
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_1D
                        HQ3X_PIXEL21_RGB_1
                        break;
                    }
                case 187:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL10_RGB_C
                            HQ3X_PIXEL20_RGB_1D
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_5
                            HQ3X_PIXEL01_RGB_1
                            HQ3X_PIXEL10_RGB_6
                            HQ3X_PIXEL20_RGB_2
                        }
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1D
                        break;
                    }
                case 243:
                    {
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL12_RGB_C
                            HQ3X_PIXEL20_RGB_1L
                            HQ3X_PIXEL21_RGB_C
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL12_RGB_1
                            HQ3X_PIXEL20_RGB_2
                            HQ3X_PIXEL21_RGB_6
                            HQ3X_PIXEL22_RGB_5
                        }
                        HQ3X_PIXEL00_RGB_1L
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        break;
                    }
                case 119:
                    {
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL00_RGB_1L
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL02_RGB_C
                            HQ3X_PIXEL12_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                            HQ3X_PIXEL01_RGB_6
                            HQ3X_PIXEL02_RGB_5
                            HQ3X_PIXEL12_RGB_1
                        }
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_1L
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 237:
                case 233:
                    {
                        HQ3X_PIXEL00_RGB_1U
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_2
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL20_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL20_RGB_2
                        }
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1R
                        break;
                    }
                case 175:
                case 47:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                        }
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1R
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        HQ3X_PIXEL20_RGB_1D
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_2
                        break;
                    }
                case 183:
                case 151:
                    {
                        HQ3X_PIXEL00_RGB_1L
                        HQ3X_PIXEL01_RGB_C
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL02_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_2
                        }
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_2
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1D
                        break;
                    }
                case 245:
                case 244:
                    {
                        HQ3X_PIXEL00_RGB_2
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1U
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1L
                        HQ3X_PIXEL21_RGB_C
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL22_RGB_2
                        }
                        break;
                    }
                case 250:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL11_RGB
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL10_RGB_C
                            HQ3X_PIXEL20_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL10_RGB_3
                            HQ3X_PIXEL20_RGB_4
                        }
                        HQ3X_PIXEL21_RGB_C
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL12_RGB_C
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL12_RGB_3
                            HQ3X_PIXEL22_RGB_4
                        }
                        break;
                    }
                case 123:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                            HQ3X_PIXEL01_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_4
                            HQ3X_PIXEL01_RGB_3
                        }
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL20_RGB_C
                            HQ3X_PIXEL21_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL20_RGB_4
                            HQ3X_PIXEL21_RGB_3
                        }
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 95:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                            HQ3X_PIXEL10_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_4
                            HQ3X_PIXEL10_RGB_3
                        }
                        HQ3X_PIXEL01_RGB_C
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL02_RGB_C
                            HQ3X_PIXEL12_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_4
                            HQ3X_PIXEL12_RGB_3
                        }
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 222:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL02_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL02_RGB_4
                        }
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1M
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL21_RGB_C
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL21_RGB_3
                            HQ3X_PIXEL22_RGB_4
                        }
                        break;
                    }
                case 252:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1U
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL10_RGB_C
                            HQ3X_PIXEL20_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL10_RGB_3
                            HQ3X_PIXEL20_RGB_4
                        }
                        HQ3X_PIXEL21_RGB_C
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL22_RGB_2
                        }
                        break;
                    }
                case 249:
                    {
                        HQ3X_PIXEL00_RGB_1U
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL20_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL20_RGB_2
                        }
                        HQ3X_PIXEL21_RGB_C
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL12_RGB_C
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL12_RGB_3
                            HQ3X_PIXEL22_RGB_4
                        }
                        break;
                    }
                case 235:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                            HQ3X_PIXEL01_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_4
                            HQ3X_PIXEL01_RGB_3
                        }
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL20_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL20_RGB_2
                        }
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1R
                        break;
                    }
                case 111:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                        }
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1R
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL20_RGB_C
                            HQ3X_PIXEL21_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL20_RGB_4
                            HQ3X_PIXEL21_RGB_3
                        }
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 63:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                        }
                        HQ3X_PIXEL01_RGB_C
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL02_RGB_C
                            HQ3X_PIXEL12_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_4
                            HQ3X_PIXEL12_RGB_3
                        }
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_1D
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 159:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                            HQ3X_PIXEL10_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_4
                            HQ3X_PIXEL10_RGB_3
                        }
                        HQ3X_PIXEL01_RGB_C
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL02_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_2
                        }
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1M
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1D
                        break;
                    }
                case 215:
                    {
                        HQ3X_PIXEL00_RGB_1L
                        HQ3X_PIXEL01_RGB_C
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL02_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_2
                        }
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1M
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL21_RGB_C
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL21_RGB_3
                            HQ3X_PIXEL22_RGB_4
                        }
                        break;
                    }
                case 246:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL02_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL02_RGB_4
                        }
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1L
                        HQ3X_PIXEL21_RGB_C
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL22_RGB_2
                        }
                        break;
                    }
                case 254:
                    {
                        HQ3X_PIXEL00_RGB_1M
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL02_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL02_RGB_4
                        }
                        HQ3X_PIXEL11_RGB
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL10_RGB_C
                            HQ3X_PIXEL20_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL10_RGB_3
                            HQ3X_PIXEL20_RGB_4
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL12_RGB_C
                            HQ3X_PIXEL21_RGB_C
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL12_RGB_3
                            HQ3X_PIXEL21_RGB_3
                            HQ3X_PIXEL22_RGB_2
                        }
                        break;
                    }
                case 253:
                    {
                        HQ3X_PIXEL00_RGB_1U
                        HQ3X_PIXEL01_RGB_1
                        HQ3X_PIXEL02_RGB_1U
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL20_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL20_RGB_2
                        }
                        HQ3X_PIXEL21_RGB_C
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL22_RGB_2
                        }
                        break;
                    }
                case 251:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                            HQ3X_PIXEL01_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_4
                            HQ3X_PIXEL01_RGB_3
                        }
                        HQ3X_PIXEL02_RGB_1M
                        HQ3X_PIXEL11_RGB
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL10_RGB_C
                            HQ3X_PIXEL20_RGB_C
                            HQ3X_PIXEL21_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL10_RGB_3
                            HQ3X_PIXEL20_RGB_2
                            HQ3X_PIXEL21_RGB_3
                        }
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL12_RGB_C
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL12_RGB_3
                            HQ3X_PIXEL22_RGB_4
                        }
                        break;
                    }
                case 239:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                        }
                        HQ3X_PIXEL01_RGB_C
                        HQ3X_PIXEL02_RGB_1R
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_1
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL20_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL20_RGB_2
                        }
                        HQ3X_PIXEL21_RGB_C
                        HQ3X_PIXEL22_RGB_1R
                        break;
                    }
                case 127:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL10_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL10_RGB_3
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL02_RGB_C
                            HQ3X_PIXEL12_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_4
                            HQ3X_PIXEL12_RGB_3
                        }
                        HQ3X_PIXEL11_RGB
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL20_RGB_C
                            HQ3X_PIXEL21_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL20_RGB_4
                            HQ3X_PIXEL21_RGB_3
                        }
                        HQ3X_PIXEL22_RGB_1M
                        break;
                    }
                case 191:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                        }
                        HQ3X_PIXEL01_RGB_C
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL02_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_2
                        }
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1D
                        HQ3X_PIXEL21_RGB_1
                        HQ3X_PIXEL22_RGB_1D
                        break;
                    }
                case 223:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                            HQ3X_PIXEL10_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_4
                            HQ3X_PIXEL10_RGB_3
                        }
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL01_RGB_C
                            HQ3X_PIXEL02_RGB_C
                            HQ3X_PIXEL12_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL01_RGB_3
                            HQ3X_PIXEL02_RGB_2
                            HQ3X_PIXEL12_RGB_3
                        }
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL20_RGB_1M
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL21_RGB_C
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL21_RGB_3
                            HQ3X_PIXEL22_RGB_4
                        }
                        break;
                    }
                case 247:
                    {
                        HQ3X_PIXEL00_RGB_1L
                        HQ3X_PIXEL01_RGB_C
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL02_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_2
                        }
                        HQ3X_PIXEL10_RGB_1
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        HQ3X_PIXEL20_RGB_1L
                        HQ3X_PIXEL21_RGB_C
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL22_RGB_2
                        }
                        break;
                    }
                case 255:
                    {
                        if (HQX_Diff_RGB(W4R, W4G, W4B, W2R, W2G, W2B))
                        {
                            HQ3X_PIXEL00_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL00_RGB_2
                        }
                        HQ3X_PIXEL01_RGB_C
                        if (HQX_Diff_RGB(W2R, W2G, W2B, W6R, W6G, W6B))
                        {
                            HQ3X_PIXEL02_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL02_RGB_2
                        }
                        HQ3X_PIXEL10_RGB_C
                        HQ3X_PIXEL11_RGB
                        HQ3X_PIXEL12_RGB_C
                        if (HQX_Diff_RGB(W8R, W8G, W8B, W4R, W4G, W4B))
                        {
                            HQ3X_PIXEL20_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL20_RGB_2
                        }
                        HQ3X_PIXEL21_RGB_C
                        if (HQX_Diff_RGB(W6R, W6G, W6B, W8R, W8G, W8B))
                        {
                            HQ3X_PIXEL22_RGB_C
                        }
                        else
                        {
                            HQ3X_PIXEL22_RGB_2
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

            BmpBufX_[P + 4 + 2] = R01;
            BmpBufX_[P + 4 + 1] = G01;
            BmpBufX_[P + 4 + 0] = B01;
            BmpBufX_[L + 4 + P + 2] = R11;
            BmpBufX_[L + 4 + P + 1] = G11;
            BmpBufX_[L + 4 + P + 0] = B11;
            BmpBufX_[LL + 4 + P + 2] = R21;
            BmpBufX_[LL + 4 + P + 1] = G21;
            BmpBufX_[LL + 4 + P + 0] = B21;

            BmpBufX_[P + 8 + 2] = R02;
            BmpBufX_[P + 8 + 1] = G02;
            BmpBufX_[P + 8 + 0] = B02;
            BmpBufX_[L + 8 + P + 2] = R12;
            BmpBufX_[L + 8 + P + 1] = G12;
            BmpBufX_[L + 8 + P + 0] = B12;
            BmpBufX_[LL + 8 + P + 2] = R22;
            BmpBufX_[LL + 8 + P + 1] = G22;
            BmpBufX_[LL + 8 + P + 0] = B22;
            P += 12;
        }
        P += LL;
    }
}

void PicThread::HQ3X_Process2(uchar * BmpBuf_, uchar * BmpBufX_, int MinY, int MaxY, int PicW_, int PicH_, int &P, int L)
{
    int LL = L << 1;
    int X, Y;
    int XW, XE, YN, YS;
    int PicW_1 = PicW_ - 1;
    int PicH_1 = PicH_ - 1;
    int W1R, W1G, W1B, W2R, W2G, W2B, W3R, W3G, W3B;
    int W4R, W4G, W4B, W5R, W5G, W5B, W6R, W6G, W6B;
    int W7R, W7G, W7B, W8R, W8G, W8B, W9R, W9G, W9B;
    int W1, W2, W3, W4, W5, W6, W7, W8, W9;
    int C00, C01, C02, C10, C11, C12, C20, C21, C22;
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
                            HQ3X_PIXEL00_2
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_2
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_2
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_2
                            break;
                        }
                    case 2:
                    case 34:
                    case 130:
                    case 162:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_2
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_2
                            break;
                        }
                    case 16:
                    case 17:
                    case 48:
                    case 49:
                        {
                            HQ3X_PIXEL00_2
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_2
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 64:
                    case 65:
                    case 68:
                    case 69:
                        {
                            HQ3X_PIXEL00_2
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_2
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 8:
                    case 12:
                    case 136:
                    case 140:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_2
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_2
                            break;
                        }
                    case 3:
                    case 35:
                    case 131:
                    case 163:
                        {
                            HQ3X_PIXEL00_1L
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_2
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_2
                            break;
                        }
                    case 6:
                    case 38:
                    case 134:
                    case 166:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1R
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_2
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_2
                            break;
                        }
                    case 20:
                    case 21:
                    case 52:
                    case 53:
                        {
                            HQ3X_PIXEL00_2
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1U
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_2
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 144:
                    case 145:
                    case 176:
                    case 177:
                        {
                            HQ3X_PIXEL00_2
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_2
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1D
                            break;
                        }
                    case 192:
                    case 193:
                    case 196:
                    case 197:
                        {
                            HQ3X_PIXEL00_2
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_2
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1R
                            break;
                        }
                    case 96:
                    case 97:
                    case 100:
                    case 101:
                        {
                            HQ3X_PIXEL00_2
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_2
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1L
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 40:
                    case 44:
                    case 168:
                    case 172:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_2
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1D
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_2
                            break;
                        }
                    case 9:
                    case 13:
                    case 137:
                    case 141:
                        {
                            HQ3X_PIXEL00_1U
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_2
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_2
                            break;
                        }
                    case 18:
                    case 50:
                        {
                            HQ3X_PIXEL00_1M
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL02_1M
                                HQ3X_PIXEL12_C
                            }
                            else
                            {
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL02_4
                                HQ3X_PIXEL12_3
                            }
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_2
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 80:
                    case 81:
                        {
                            HQ3X_PIXEL00_2
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_1M
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL12_C
                                HQ3X_PIXEL21_C
                                HQ3X_PIXEL22_1M
                            }
                            else
                            {
                                HQ3X_PIXEL12_3
                                HQ3X_PIXEL21_3
                                HQ3X_PIXEL22_4
                            }
                            break;
                        }
                    case 72:
                    case 76:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_2
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL10_C
                                HQ3X_PIXEL20_1M
                                HQ3X_PIXEL21_C
                            }
                            else
                            {
                                HQ3X_PIXEL10_3
                                HQ3X_PIXEL20_4
                                HQ3X_PIXEL21_3
                            }
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 10:
                    case 138:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_1M
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL10_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_4
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL10_3
                            }
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_2
                            break;
                        }
                    case 66:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 24:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 7:
                    case 39:
                    case 135:
                        {
                            HQ3X_PIXEL00_1L
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1R
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_2
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_2
                            break;
                        }
                    case 148:
                    case 149:
                    case 180:
                        {
                            HQ3X_PIXEL00_2
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1U
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_2
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1D
                            break;
                        }
                    case 224:
                    case 228:
                    case 225:
                        {
                            HQ3X_PIXEL00_2
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_2
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1L
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1R
                            break;
                        }
                    case 41:
                    case 169:
                    case 45:
                        {
                            HQ3X_PIXEL00_1U
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_2
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1D
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_2
                            break;
                        }
                    case 22:
                    case 54:
                        {
                            HQ3X_PIXEL00_1M
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL02_C
                                HQ3X_PIXEL12_C
                            }
                            else
                            {
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL02_4
                                HQ3X_PIXEL12_3
                            }
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_2
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 208:
                    case 209:
                        {
                            HQ3X_PIXEL00_2
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_1M
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL12_C
                                HQ3X_PIXEL21_C
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL12_3
                                HQ3X_PIXEL21_3
                                HQ3X_PIXEL22_4
                            }
                            break;
                        }
                    case 104:
                    case 108:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_2
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL10_C
                                HQ3X_PIXEL20_C
                                HQ3X_PIXEL21_C
                            }
                            else
                            {
                                HQ3X_PIXEL10_3
                                HQ3X_PIXEL20_4
                                HQ3X_PIXEL21_3
                            }
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 11:
                    case 139:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL10_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_4
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL10_3
                            }
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_2
                            break;
                        }
                    case 19:
                    case 51:
                        {
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL00_1L
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL02_1M
                                HQ3X_PIXEL12_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                                HQ3X_PIXEL01_6
                                HQ3X_PIXEL02_5
                                HQ3X_PIXEL12_1
                            }
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_2
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 146:
                    case 178:
                        {
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL02_1M
                                HQ3X_PIXEL12_C
                                HQ3X_PIXEL22_1D
                            }
                            else
                            {
                                HQ3X_PIXEL01_1
                                HQ3X_PIXEL02_5
                                HQ3X_PIXEL12_6
                                HQ3X_PIXEL22_2
                            }
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_2
                            HQ3X_PIXEL21_1
                            break;
                        }
                    case 84:
                    case 85:
                        {
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL02_1U
                                HQ3X_PIXEL12_C
                                HQ3X_PIXEL21_C
                                HQ3X_PIXEL22_1M
                            }
                            else
                            {
                                HQ3X_PIXEL02_2
                                HQ3X_PIXEL12_6
                                HQ3X_PIXEL21_1
                                HQ3X_PIXEL22_5
                            }
                            HQ3X_PIXEL00_2
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_1M
                            break;
                        }
                    case 112:
                    case 113:
                        {
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL12_C
                                HQ3X_PIXEL20_1L
                                HQ3X_PIXEL21_C
                                HQ3X_PIXEL22_1M
                            }
                            else
                            {
                                HQ3X_PIXEL12_1
                                HQ3X_PIXEL20_2
                                HQ3X_PIXEL21_6
                                HQ3X_PIXEL22_5
                            }
                            HQ3X_PIXEL00_2
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            break;
                        }
                    case 200:
                    case 204:
                        {
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL10_C
                                HQ3X_PIXEL20_1M
                                HQ3X_PIXEL21_C
                                HQ3X_PIXEL22_1R
                            }
                            else
                            {
                                HQ3X_PIXEL10_1
                                HQ3X_PIXEL20_5
                                HQ3X_PIXEL21_6
                                HQ3X_PIXEL22_2
                            }
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_2
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            break;
                        }
                    case 73:
                    case 77:
                        {
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL00_1U
                                HQ3X_PIXEL10_C
                                HQ3X_PIXEL20_1M
                                HQ3X_PIXEL21_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                                HQ3X_PIXEL10_6
                                HQ3X_PIXEL20_5
                                HQ3X_PIXEL21_1
                            }
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_2
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 42:
                    case 170:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_1M
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL10_C
                                HQ3X_PIXEL20_1D
                            }
                            else
                            {
                                HQ3X_PIXEL00_5
                                HQ3X_PIXEL01_1
                                HQ3X_PIXEL10_6
                                HQ3X_PIXEL20_2
                            }
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_2
                            break;
                        }
                    case 14:
                    case 142:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_1M
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL02_1R
                                HQ3X_PIXEL10_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_5
                                HQ3X_PIXEL01_6
                                HQ3X_PIXEL02_2
                                HQ3X_PIXEL10_1
                            }
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_2
                            break;
                        }
                    case 67:
                        {
                            HQ3X_PIXEL00_1L
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 70:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1R
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 28:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1U
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 152:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1D
                            break;
                        }
                    case 194:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1R
                            break;
                        }
                    case 98:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1L
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 56:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1D
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 25:
                        {
                            HQ3X_PIXEL00_1U
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 26:
                    case 31:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                                HQ3X_PIXEL10_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_4
                                HQ3X_PIXEL10_3
                            }
                            HQ3X_PIXEL01_C
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL02_C
                                HQ3X_PIXEL12_C
                            }
                            else
                            {
                                HQ3X_PIXEL02_4
                                HQ3X_PIXEL12_3
                            }
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 82:
                    case 214:
                        {
                            HQ3X_PIXEL00_1M
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL02_C
                            }
                            else
                            {
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL02_4
                            }
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1M
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL21_C
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL21_3
                                HQ3X_PIXEL22_4
                            }
                            break;
                        }
                    case 88:
                    case 248:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL11
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL10_C
                                HQ3X_PIXEL20_C
                            }
                            else
                            {
                                HQ3X_PIXEL10_3
                                HQ3X_PIXEL20_4
                            }
                            HQ3X_PIXEL21_C
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL12_C
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL12_3
                                HQ3X_PIXEL22_4
                            }
                            break;
                        }
                    case 74:
                    case 107:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                                HQ3X_PIXEL01_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_4
                                HQ3X_PIXEL01_3
                            }
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL20_C
                                HQ3X_PIXEL21_C
                            }
                            else
                            {
                                HQ3X_PIXEL20_4
                                HQ3X_PIXEL21_3
                            }
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 27:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL10_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_4
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL10_3
                            }
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 86:
                        {
                            HQ3X_PIXEL00_1M
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL02_C
                                HQ3X_PIXEL12_C
                            }
                            else
                            {
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL02_4
                                HQ3X_PIXEL12_3
                            }
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 216:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_1M
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL12_C
                                HQ3X_PIXEL21_C
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL12_3
                                HQ3X_PIXEL21_3
                                HQ3X_PIXEL22_4
                            }
                            break;
                        }
                    case 106:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL10_C
                                HQ3X_PIXEL20_C
                                HQ3X_PIXEL21_C
                            }
                            else
                            {
                                HQ3X_PIXEL10_3
                                HQ3X_PIXEL20_4
                                HQ3X_PIXEL21_3
                            }
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 30:
                        {
                            HQ3X_PIXEL00_1M
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL02_C
                                HQ3X_PIXEL12_C
                            }
                            else
                            {
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL02_4
                                HQ3X_PIXEL12_3
                            }
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 210:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_1M
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL12_C
                                HQ3X_PIXEL21_C
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL12_3
                                HQ3X_PIXEL21_3
                                HQ3X_PIXEL22_4
                            }
                            break;
                        }
                    case 120:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL10_C
                                HQ3X_PIXEL20_C
                                HQ3X_PIXEL21_C
                            }
                            else
                            {
                                HQ3X_PIXEL10_3
                                HQ3X_PIXEL20_4
                                HQ3X_PIXEL21_3
                            }
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 75:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL10_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_4
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL10_3
                            }
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 29:
                        {
                            HQ3X_PIXEL00_1U
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1U
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 198:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1R
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1R
                            break;
                        }
                    case 184:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1D
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1D
                            break;
                        }
                    case 99:
                        {
                            HQ3X_PIXEL00_1L
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1L
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 57:
                        {
                            HQ3X_PIXEL00_1U
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1D
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 71:
                        {
                            HQ3X_PIXEL00_1L
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1R
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 156:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1U
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1D
                            break;
                        }
                    case 226:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1L
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1R
                            break;
                        }
                    case 60:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1U
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1D
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 195:
                        {
                            HQ3X_PIXEL00_1L
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1R
                            break;
                        }
                    case 102:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1R
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1L
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 153:
                        {
                            HQ3X_PIXEL00_1U
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1D
                            break;
                        }
                    case 58:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_1M
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                            }
                            HQ3X_PIXEL01_C
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL02_1M
                            }
                            else
                            {
                                HQ3X_PIXEL02_2
                            }
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1D
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 83:
                        {
                            HQ3X_PIXEL00_1L
                            HQ3X_PIXEL01_C
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL02_1M
                            }
                            else
                            {
                                HQ3X_PIXEL02_2
                            }
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_C
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL22_1M
                            }
                            else
                            {
                                HQ3X_PIXEL22_2
                            }
                            break;
                        }
                    case 92:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1U
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL20_1M
                            }
                            else
                            {
                                HQ3X_PIXEL20_2
                            }
                            HQ3X_PIXEL21_C
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL22_1M
                            }
                            else
                            {
                                HQ3X_PIXEL22_2
                            }
                            break;
                        }
                    case 202:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_1M
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                            }
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL20_1M
                            }
                            else
                            {
                                HQ3X_PIXEL20_2
                            }
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1R
                            break;
                        }
                    case 78:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_1M
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                            }
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1R
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL20_1M
                            }
                            else
                            {
                                HQ3X_PIXEL20_2
                            }
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 154:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_1M
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                            }
                            HQ3X_PIXEL01_C
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL02_1M
                            }
                            else
                            {
                                HQ3X_PIXEL02_2
                            }
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1D
                            break;
                        }
                    case 114:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_C
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL02_1M
                            }
                            else
                            {
                                HQ3X_PIXEL02_2
                            }
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1L
                            HQ3X_PIXEL21_C
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL22_1M
                            }
                            else
                            {
                                HQ3X_PIXEL22_2
                            }
                            break;
                        }
                    case 89:
                        {
                            HQ3X_PIXEL00_1U
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL20_1M
                            }
                            else
                            {
                                HQ3X_PIXEL20_2
                            }
                            HQ3X_PIXEL21_C
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL22_1M
                            }
                            else
                            {
                                HQ3X_PIXEL22_2
                            }
                            break;
                        }
                    case 90:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_1M
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                            }
                            HQ3X_PIXEL01_C
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL02_1M
                            }
                            else
                            {
                                HQ3X_PIXEL02_2
                            }
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL20_1M
                            }
                            else
                            {
                                HQ3X_PIXEL20_2
                            }
                            HQ3X_PIXEL21_C
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL22_1M
                            }
                            else
                            {
                                HQ3X_PIXEL22_2
                            }
                            break;
                        }
                    case 55:
                    case 23:
                        {
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL00_1L
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL02_C
                                HQ3X_PIXEL12_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                                HQ3X_PIXEL01_6
                                HQ3X_PIXEL02_5
                                HQ3X_PIXEL12_1
                            }
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_2
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 182:
                    case 150:
                        {
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL02_C
                                HQ3X_PIXEL12_C
                                HQ3X_PIXEL22_1D
                            }
                            else
                            {
                                HQ3X_PIXEL01_1
                                HQ3X_PIXEL02_5
                                HQ3X_PIXEL12_6
                                HQ3X_PIXEL22_2
                            }
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_2
                            HQ3X_PIXEL21_1
                            break;
                        }
                    case 213:
                    case 212:
                        {
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL02_1U
                                HQ3X_PIXEL12_C
                                HQ3X_PIXEL21_C
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL02_2
                                HQ3X_PIXEL12_6
                                HQ3X_PIXEL21_1
                                HQ3X_PIXEL22_5
                            }
                            HQ3X_PIXEL00_2
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_1M
                            break;
                        }
                    case 241:
                    case 240:
                        {
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL12_C
                                HQ3X_PIXEL20_1L
                                HQ3X_PIXEL21_C
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL12_1
                                HQ3X_PIXEL20_2
                                HQ3X_PIXEL21_6
                                HQ3X_PIXEL22_5
                            }
                            HQ3X_PIXEL00_2
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            break;
                        }
                    case 236:
                    case 232:
                        {
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL10_C
                                HQ3X_PIXEL20_C
                                HQ3X_PIXEL21_C
                                HQ3X_PIXEL22_1R
                            }
                            else
                            {
                                HQ3X_PIXEL10_1
                                HQ3X_PIXEL20_5
                                HQ3X_PIXEL21_6
                                HQ3X_PIXEL22_2
                            }
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_2
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            break;
                        }
                    case 109:
                    case 105:
                        {
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL00_1U
                                HQ3X_PIXEL10_C
                                HQ3X_PIXEL20_C
                                HQ3X_PIXEL21_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                                HQ3X_PIXEL10_6
                                HQ3X_PIXEL20_5
                                HQ3X_PIXEL21_1
                            }
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_2
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 171:
                    case 43:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL10_C
                                HQ3X_PIXEL20_1D
                            }
                            else
                            {
                                HQ3X_PIXEL00_5
                                HQ3X_PIXEL01_1
                                HQ3X_PIXEL10_6
                                HQ3X_PIXEL20_2
                            }
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_2
                            break;
                        }
                    case 143:
                    case 15:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL02_1R
                                HQ3X_PIXEL10_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_5
                                HQ3X_PIXEL01_6
                                HQ3X_PIXEL02_2
                                HQ3X_PIXEL10_1
                            }
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_2
                            break;
                        }
                    case 124:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1U
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL10_C
                                HQ3X_PIXEL20_C
                                HQ3X_PIXEL21_C
                            }
                            else
                            {
                                HQ3X_PIXEL10_3
                                HQ3X_PIXEL20_4
                                HQ3X_PIXEL21_3
                            }
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 203:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL10_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_4
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL10_3
                            }
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1R
                            break;
                        }
                    case 62:
                        {
                            HQ3X_PIXEL00_1M
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL02_C
                                HQ3X_PIXEL12_C
                            }
                            else
                            {
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL02_4
                                HQ3X_PIXEL12_3
                            }
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_1D
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 211:
                        {
                            HQ3X_PIXEL00_1L
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_1M
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL12_C
                                HQ3X_PIXEL21_C
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL12_3
                                HQ3X_PIXEL21_3
                                HQ3X_PIXEL22_4
                            }
                            break;
                        }
                    case 118:
                        {
                            HQ3X_PIXEL00_1M
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL02_C
                                HQ3X_PIXEL12_C
                            }
                            else
                            {
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL02_4
                                HQ3X_PIXEL12_3
                            }
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_1L
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 217:
                        {
                            HQ3X_PIXEL00_1U
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_1M
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL12_C
                                HQ3X_PIXEL21_C
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL12_3
                                HQ3X_PIXEL21_3
                                HQ3X_PIXEL22_4
                            }
                            break;
                        }
                    case 110:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1R
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL10_C
                                HQ3X_PIXEL20_C
                                HQ3X_PIXEL21_C
                            }
                            else
                            {
                                HQ3X_PIXEL10_3
                                HQ3X_PIXEL20_4
                                HQ3X_PIXEL21_3
                            }
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 155:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL10_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_4
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL10_3
                            }
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1D
                            break;
                        }
                    case 188:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1U
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1D
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1D
                            break;
                        }
                    case 185:
                        {
                            HQ3X_PIXEL00_1U
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1D
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1D
                            break;
                        }
                    case 61:
                        {
                            HQ3X_PIXEL00_1U
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1U
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1D
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 157:
                        {
                            HQ3X_PIXEL00_1U
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1U
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1D
                            break;
                        }
                    case 103:
                        {
                            HQ3X_PIXEL00_1L
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1R
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1L
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 227:
                        {
                            HQ3X_PIXEL00_1L
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1L
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1R
                            break;
                        }
                    case 230:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1R
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1L
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1R
                            break;
                        }
                    case 199:
                        {
                            HQ3X_PIXEL00_1L
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1R
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1R
                            break;
                        }
                    case 220:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1U
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL20_1M
                            }
                            else
                            {
                                HQ3X_PIXEL20_2
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL12_C
                                HQ3X_PIXEL21_C
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL12_3
                                HQ3X_PIXEL21_3
                                HQ3X_PIXEL22_4
                            }
                            break;
                        }
                    case 158:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_1M
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL02_C
                                HQ3X_PIXEL12_C
                            }
                            else
                            {
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL02_4
                                HQ3X_PIXEL12_3
                            }
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1D
                            break;
                        }
                    case 234:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_1M
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                            }
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL10_C
                                HQ3X_PIXEL20_C
                                HQ3X_PIXEL21_C
                            }
                            else
                            {
                                HQ3X_PIXEL10_3
                                HQ3X_PIXEL20_4
                                HQ3X_PIXEL21_3
                            }
                            HQ3X_PIXEL22_1R
                            break;
                        }
                    case 242:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_C
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL02_1M
                            }
                            else
                            {
                                HQ3X_PIXEL02_2
                            }
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_1L
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL12_C
                                HQ3X_PIXEL21_C
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL12_3
                                HQ3X_PIXEL21_3
                                HQ3X_PIXEL22_4
                            }
                            break;
                        }
                    case 59:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL10_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_4
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL10_3
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL02_1M
                            }
                            else
                            {
                                HQ3X_PIXEL02_2
                            }
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1D
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 121:
                        {
                            HQ3X_PIXEL00_1U
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL10_C
                                HQ3X_PIXEL20_C
                                HQ3X_PIXEL21_C
                            }
                            else
                            {
                                HQ3X_PIXEL10_3
                                HQ3X_PIXEL20_4
                                HQ3X_PIXEL21_3
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL22_1M
                            }
                            else
                            {
                                HQ3X_PIXEL22_2
                            }
                            break;
                        }
                    case 87:
                        {
                            HQ3X_PIXEL00_1L
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL02_C
                                HQ3X_PIXEL12_C
                            }
                            else
                            {
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL02_4
                                HQ3X_PIXEL12_3
                            }
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_C
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL22_1M
                            }
                            else
                            {
                                HQ3X_PIXEL22_2
                            }
                            break;
                        }
                    case 79:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL10_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_4
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL10_3
                            }
                            HQ3X_PIXEL02_1R
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL20_1M
                            }
                            else
                            {
                                HQ3X_PIXEL20_2
                            }
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 122:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_1M
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                            }
                            HQ3X_PIXEL01_C
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL02_1M
                            }
                            else
                            {
                                HQ3X_PIXEL02_2
                            }
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL10_C
                                HQ3X_PIXEL20_C
                                HQ3X_PIXEL21_C
                            }
                            else
                            {
                                HQ3X_PIXEL10_3
                                HQ3X_PIXEL20_4
                                HQ3X_PIXEL21_3
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL22_1M
                            }
                            else
                            {
                                HQ3X_PIXEL22_2
                            }
                            break;
                        }
                    case 94:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_1M
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL02_C
                                HQ3X_PIXEL12_C
                            }
                            else
                            {
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL02_4
                                HQ3X_PIXEL12_3
                            }
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL20_1M
                            }
                            else
                            {
                                HQ3X_PIXEL20_2
                            }
                            HQ3X_PIXEL21_C
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL22_1M
                            }
                            else
                            {
                                HQ3X_PIXEL22_2
                            }
                            break;
                        }
                    case 218:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_1M
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                            }
                            HQ3X_PIXEL01_C
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL02_1M
                            }
                            else
                            {
                                HQ3X_PIXEL02_2
                            }
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL20_1M
                            }
                            else
                            {
                                HQ3X_PIXEL20_2
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL12_C
                                HQ3X_PIXEL21_C
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL12_3
                                HQ3X_PIXEL21_3
                                HQ3X_PIXEL22_4
                            }
                            break;
                        }
                    case 91:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL10_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_4
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL10_3
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL02_1M
                            }
                            else
                            {
                                HQ3X_PIXEL02_2
                            }
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL20_1M
                            }
                            else
                            {
                                HQ3X_PIXEL20_2
                            }
                            HQ3X_PIXEL21_C
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL22_1M
                            }
                            else
                            {
                                HQ3X_PIXEL22_2
                            }
                            break;
                        }
                    case 229:
                        {
                            HQ3X_PIXEL00_2
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_2
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1L
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1R
                            break;
                        }
                    case 167:
                        {
                            HQ3X_PIXEL00_1L
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1R
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_2
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_2
                            break;
                        }
                    case 173:
                        {
                            HQ3X_PIXEL00_1U
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_2
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1D
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_2
                            break;
                        }
                    case 181:
                        {
                            HQ3X_PIXEL00_2
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1U
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_2
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1D
                            break;
                        }
                    case 186:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_1M
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                            }
                            HQ3X_PIXEL01_C
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL02_1M
                            }
                            else
                            {
                                HQ3X_PIXEL02_2
                            }
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1D
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1D
                            break;
                        }
                    case 115:
                        {
                            HQ3X_PIXEL00_1L
                            HQ3X_PIXEL01_C
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL02_1M
                            }
                            else
                            {
                                HQ3X_PIXEL02_2
                            }
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1L
                            HQ3X_PIXEL21_C
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL22_1M
                            }
                            else
                            {
                                HQ3X_PIXEL22_2
                            }
                            break;
                        }
                    case 93:
                        {
                            HQ3X_PIXEL00_1U
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1U
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL20_1M
                            }
                            else
                            {
                                HQ3X_PIXEL20_2
                            }
                            HQ3X_PIXEL21_C
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL22_1M
                            }
                            else
                            {
                                HQ3X_PIXEL22_2
                            }
                            break;
                        }
                    case 206:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_1M
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                            }
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1R
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL20_1M
                            }
                            else
                            {
                                HQ3X_PIXEL20_2
                            }
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1R
                            break;
                        }
                    case 205:
                    case 201:
                        {
                            HQ3X_PIXEL00_1U
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_2
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL20_1M
                            }
                            else
                            {
                                HQ3X_PIXEL20_2
                            }
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1R
                            break;
                        }
                    case 174:
                    case 46:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_1M
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                            }
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1R
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1D
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_2
                            break;
                        }
                    case 179:
                    case 147:
                        {
                            HQ3X_PIXEL00_1L
                            HQ3X_PIXEL01_C
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL02_1M
                            }
                            else
                            {
                                HQ3X_PIXEL02_2
                            }
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_2
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1D
                            break;
                        }
                    case 117:
                    case 116:
                        {
                            HQ3X_PIXEL00_2
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1U
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1L
                            HQ3X_PIXEL21_C
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL22_1M
                            }
                            else
                            {
                                HQ3X_PIXEL22_2
                            }
                            break;
                        }
                    case 189:
                        {
                            HQ3X_PIXEL00_1U
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1U
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1D
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1D
                            break;
                        }
                    case 231:
                        {
                            HQ3X_PIXEL00_1L
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1R
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1L
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1R
                            break;
                        }
                    case 126:
                        {
                            HQ3X_PIXEL00_1M
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL02_C
                                HQ3X_PIXEL12_C
                            }
                            else
                            {
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL02_4
                                HQ3X_PIXEL12_3
                            }
                            HQ3X_PIXEL11
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL10_C
                                HQ3X_PIXEL20_C
                                HQ3X_PIXEL21_C
                            }
                            else
                            {
                                HQ3X_PIXEL10_3
                                HQ3X_PIXEL20_4
                                HQ3X_PIXEL21_3
                            }
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 219:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL10_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_4
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL10_3
                            }
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_1M
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL12_C
                                HQ3X_PIXEL21_C
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL12_3
                                HQ3X_PIXEL21_3
                                HQ3X_PIXEL22_4
                            }
                            break;
                        }
                    case 125:
                        {
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL00_1U
                                HQ3X_PIXEL10_C
                                HQ3X_PIXEL20_C
                                HQ3X_PIXEL21_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                                HQ3X_PIXEL10_6
                                HQ3X_PIXEL20_5
                                HQ3X_PIXEL21_1
                            }
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1U
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 221:
                        {
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL02_1U
                                HQ3X_PIXEL12_C
                                HQ3X_PIXEL21_C
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL02_2
                                HQ3X_PIXEL12_6
                                HQ3X_PIXEL21_1
                                HQ3X_PIXEL22_5
                            }
                            HQ3X_PIXEL00_1U
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_1M
                            break;
                        }
                    case 207:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL02_1R
                                HQ3X_PIXEL10_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_5
                                HQ3X_PIXEL01_6
                                HQ3X_PIXEL02_2
                                HQ3X_PIXEL10_1
                            }
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1R
                            break;
                        }
                    case 238:
                        {
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL10_C
                                HQ3X_PIXEL20_C
                                HQ3X_PIXEL21_C
                                HQ3X_PIXEL22_1R
                            }
                            else
                            {
                                HQ3X_PIXEL10_1
                                HQ3X_PIXEL20_5
                                HQ3X_PIXEL21_6
                                HQ3X_PIXEL22_2
                            }
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1R
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            break;
                        }
                    case 190:
                        {
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL02_C
                                HQ3X_PIXEL12_C
                                HQ3X_PIXEL22_1D
                            }
                            else
                            {
                                HQ3X_PIXEL01_1
                                HQ3X_PIXEL02_5
                                HQ3X_PIXEL12_6
                                HQ3X_PIXEL22_2
                            }
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_1D
                            HQ3X_PIXEL21_1
                            break;
                        }
                    case 187:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL10_C
                                HQ3X_PIXEL20_1D
                            }
                            else
                            {
                                HQ3X_PIXEL00_5
                                HQ3X_PIXEL01_1
                                HQ3X_PIXEL10_6
                                HQ3X_PIXEL20_2
                            }
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1D
                            break;
                        }
                    case 243:
                        {
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL12_C
                                HQ3X_PIXEL20_1L
                                HQ3X_PIXEL21_C
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL12_1
                                HQ3X_PIXEL20_2
                                HQ3X_PIXEL21_6
                                HQ3X_PIXEL22_5
                            }
                            HQ3X_PIXEL00_1L
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            break;
                        }
                    case 119:
                        {
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL00_1L
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL02_C
                                HQ3X_PIXEL12_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                                HQ3X_PIXEL01_6
                                HQ3X_PIXEL02_5
                                HQ3X_PIXEL12_1
                            }
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_1L
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 237:
                    case 233:
                        {
                            HQ3X_PIXEL00_1U
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_2
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL20_C
                            }
                            else
                            {
                                HQ3X_PIXEL20_2
                            }
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1R
                            break;
                        }
                    case 175:
                    case 47:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                            }
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1R
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            HQ3X_PIXEL20_1D
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_2
                            break;
                        }
                    case 183:
                    case 151:
                        {
                            HQ3X_PIXEL00_1L
                            HQ3X_PIXEL01_C
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL02_C
                            }
                            else
                            {
                                HQ3X_PIXEL02_2
                            }
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_2
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1D
                            break;
                        }
                    case 245:
                    case 244:
                        {
                            HQ3X_PIXEL00_2
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1U
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1L
                            HQ3X_PIXEL21_C
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL22_2
                            }
                            break;
                        }
                    case 250:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL11
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL10_C
                                HQ3X_PIXEL20_C
                            }
                            else
                            {
                                HQ3X_PIXEL10_3
                                HQ3X_PIXEL20_4
                            }
                            HQ3X_PIXEL21_C
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL12_C
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL12_3
                                HQ3X_PIXEL22_4
                            }
                            break;
                        }
                    case 123:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                                HQ3X_PIXEL01_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_4
                                HQ3X_PIXEL01_3
                            }
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL20_C
                                HQ3X_PIXEL21_C
                            }
                            else
                            {
                                HQ3X_PIXEL20_4
                                HQ3X_PIXEL21_3
                            }
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 95:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                                HQ3X_PIXEL10_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_4
                                HQ3X_PIXEL10_3
                            }
                            HQ3X_PIXEL01_C
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL02_C
                                HQ3X_PIXEL12_C
                            }
                            else
                            {
                                HQ3X_PIXEL02_4
                                HQ3X_PIXEL12_3
                            }
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 222:
                        {
                            HQ3X_PIXEL00_1M
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL02_C
                            }
                            else
                            {
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL02_4
                            }
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1M
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL21_C
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL21_3
                                HQ3X_PIXEL22_4
                            }
                            break;
                        }
                    case 252:
                        {
                            HQ3X_PIXEL00_1M
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1U
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL10_C
                                HQ3X_PIXEL20_C
                            }
                            else
                            {
                                HQ3X_PIXEL10_3
                                HQ3X_PIXEL20_4
                            }
                            HQ3X_PIXEL21_C
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL22_2
                            }
                            break;
                        }
                    case 249:
                        {
                            HQ3X_PIXEL00_1U
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL20_C
                            }
                            else
                            {
                                HQ3X_PIXEL20_2
                            }
                            HQ3X_PIXEL21_C
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL12_C
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL12_3
                                HQ3X_PIXEL22_4
                            }
                            break;
                        }
                    case 235:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                                HQ3X_PIXEL01_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_4
                                HQ3X_PIXEL01_3
                            }
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL20_C
                            }
                            else
                            {
                                HQ3X_PIXEL20_2
                            }
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1R
                            break;
                        }
                    case 111:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                            }
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1R
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL20_C
                                HQ3X_PIXEL21_C
                            }
                            else
                            {
                                HQ3X_PIXEL20_4
                                HQ3X_PIXEL21_3
                            }
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 63:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                            }
                            HQ3X_PIXEL01_C
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL02_C
                                HQ3X_PIXEL12_C
                            }
                            else
                            {
                                HQ3X_PIXEL02_4
                                HQ3X_PIXEL12_3
                            }
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_1D
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 159:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                                HQ3X_PIXEL10_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_4
                                HQ3X_PIXEL10_3
                            }
                            HQ3X_PIXEL01_C
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL02_C
                            }
                            else
                            {
                                HQ3X_PIXEL02_2
                            }
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1M
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1D
                            break;
                        }
                    case 215:
                        {
                            HQ3X_PIXEL00_1L
                            HQ3X_PIXEL01_C
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL02_C
                            }
                            else
                            {
                                HQ3X_PIXEL02_2
                            }
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1M
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL21_C
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL21_3
                                HQ3X_PIXEL22_4
                            }
                            break;
                        }
                    case 246:
                        {
                            HQ3X_PIXEL00_1M
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL02_C
                            }
                            else
                            {
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL02_4
                            }
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1L
                            HQ3X_PIXEL21_C
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL22_2
                            }
                            break;
                        }
                    case 254:
                        {
                            HQ3X_PIXEL00_1M
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL02_C
                            }
                            else
                            {
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL02_4
                            }
                            HQ3X_PIXEL11
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL10_C
                                HQ3X_PIXEL20_C
                            }
                            else
                            {
                                HQ3X_PIXEL10_3
                                HQ3X_PIXEL20_4
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL12_C
                                HQ3X_PIXEL21_C
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL12_3
                                HQ3X_PIXEL21_3
                                HQ3X_PIXEL22_2
                            }
                            break;
                        }
                    case 253:
                        {
                            HQ3X_PIXEL00_1U
                            HQ3X_PIXEL01_1
                            HQ3X_PIXEL02_1U
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL20_C
                            }
                            else
                            {
                                HQ3X_PIXEL20_2
                            }
                            HQ3X_PIXEL21_C
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL22_2
                            }
                            break;
                        }
                    case 251:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                                HQ3X_PIXEL01_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_4
                                HQ3X_PIXEL01_3
                            }
                            HQ3X_PIXEL02_1M
                            HQ3X_PIXEL11
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL10_C
                                HQ3X_PIXEL20_C
                                HQ3X_PIXEL21_C
                            }
                            else
                            {
                                HQ3X_PIXEL10_3
                                HQ3X_PIXEL20_2
                                HQ3X_PIXEL21_3
                            }
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL12_C
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL12_3
                                HQ3X_PIXEL22_4
                            }
                            break;
                        }
                    case 239:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                            }
                            HQ3X_PIXEL01_C
                            HQ3X_PIXEL02_1R
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_1
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL20_C
                            }
                            else
                            {
                                HQ3X_PIXEL20_2
                            }
                            HQ3X_PIXEL21_C
                            HQ3X_PIXEL22_1R
                            break;
                        }
                    case 127:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL10_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL10_3
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL02_C
                                HQ3X_PIXEL12_C
                            }
                            else
                            {
                                HQ3X_PIXEL02_4
                                HQ3X_PIXEL12_3
                            }
                            HQ3X_PIXEL11
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL20_C
                                HQ3X_PIXEL21_C
                            }
                            else
                            {
                                HQ3X_PIXEL20_4
                                HQ3X_PIXEL21_3
                            }
                            HQ3X_PIXEL22_1M
                            break;
                        }
                    case 191:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                            }
                            HQ3X_PIXEL01_C
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL02_C
                            }
                            else
                            {
                                HQ3X_PIXEL02_2
                            }
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1D
                            HQ3X_PIXEL21_1
                            HQ3X_PIXEL22_1D
                            break;
                        }
                    case 223:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                                HQ3X_PIXEL10_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_4
                                HQ3X_PIXEL10_3
                            }
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL01_C
                                HQ3X_PIXEL02_C
                                HQ3X_PIXEL12_C
                            }
                            else
                            {
                                HQ3X_PIXEL01_3
                                HQ3X_PIXEL02_2
                                HQ3X_PIXEL12_3
                            }
                            HQ3X_PIXEL11
                            HQ3X_PIXEL20_1M
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL21_C
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL21_3
                                HQ3X_PIXEL22_4
                            }
                            break;
                        }
                    case 247:
                        {
                            HQ3X_PIXEL00_1L
                            HQ3X_PIXEL01_C
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL02_C
                            }
                            else
                            {
                                HQ3X_PIXEL02_2
                            }
                            HQ3X_PIXEL10_1
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            HQ3X_PIXEL20_1L
                            HQ3X_PIXEL21_C
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL22_2
                            }
                            break;
                        }
                    case 255:
                        {
                            if (HQX_Diff(W4, W2))
                            {
                                HQ3X_PIXEL00_C
                            }
                            else
                            {
                                HQ3X_PIXEL00_2
                            }
                            HQ3X_PIXEL01_C
                            if (HQX_Diff(W2, W6))
                            {
                                HQ3X_PIXEL02_C
                            }
                            else
                            {
                                HQ3X_PIXEL02_2
                            }
                            HQ3X_PIXEL10_C
                            HQ3X_PIXEL11
                            HQ3X_PIXEL12_C
                            if (HQX_Diff(W8, W4))
                            {
                                HQ3X_PIXEL20_C
                            }
                            else
                            {
                                HQ3X_PIXEL20_2
                            }
                            HQ3X_PIXEL21_C
                            if (HQX_Diff(W6, W8))
                            {
                                HQ3X_PIXEL22_C
                            }
                            else
                            {
                                HQ3X_PIXEL22_2
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
                        BmpBufX_[P + 4 + 2] = C01;
                        BmpBufX_[L + 4 + P + 2] = C11;
                        BmpBufX_[LL + 4 + P + 2] = C21;
                        BmpBufX_[P + 8 + 2] = C02;
                        BmpBufX_[L + 8 + P + 2] = C12;
                        BmpBufX_[LL + 8 + P + 2] = C22;
                        break;
                    case 1:
                        BmpBufX_[P + 1] = C00;
                        BmpBufX_[L + P + 1] = C10;
                        BmpBufX_[LL + P + 1] = C20;
                        BmpBufX_[P + 4 + 1] = C01;
                        BmpBufX_[L + 4 + P + 1] = C11;
                        BmpBufX_[LL + 4 + P + 1] = C21;
                        BmpBufX_[P + 8 + 1] = C02;
                        BmpBufX_[L + 8 + P + 1] = C12;
                        BmpBufX_[LL + 8 + P + 1] = C22;
                        break;
                    case 2:
                        BmpBufX_[P + 0] = C00;
                        BmpBufX_[L + P + 0] = C10;
                        BmpBufX_[LL + P + 0] = C20;
                        BmpBufX_[P + 4 + 0] = C01;
                        BmpBufX_[L + 4 + P + 0] = C11;
                        BmpBufX_[LL + 4 + P + 0] = C21;
                        BmpBufX_[P + 8 + 0] = C02;
                        BmpBufX_[L + 8 + P + 0] = C12;
                        BmpBufX_[LL + 8 + P + 0] = C22;
                        break;
                }
            }

            P += 12;
        }
        P += LL;
    }
}
