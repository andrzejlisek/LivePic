#include "transformitem.h"

TransformItem::TransformItem(Settings *Settings__)
{
    Settings_ = Settings__;

    for (int I = 0; I < 25; I++)
    {
        Trans2MatrixR[I] = 0;
        Trans2MatrixG[I] = 0;
        Trans2MatrixB[I] = 0;
    }
    Trans2MatrixR[12] = 1;
    Trans2MatrixG[12] = 1;
    Trans2MatrixB[12] = 1;



}

///
/// \brief TransformItem::GammaLUT - Fill in gamma look-up table - the same as in PicThread::OpLoad
///
void TransformItem::GammaLUT()
{
    if ((GammaLUT_gamma < 0) || (GammaLUT_gamma != Settings_->Gamma))
    {
        GammaLUT_gamma = Settings_->Gamma;
        long double GammaX = Settings_->Gamma;
        GammaX = GammaX / 1000.0L;

        for (int I = 0; I < 256; I++)
        {
            long double I_ = I;
            I_ = I_ / 256.0L;
            I_ = powl(I_, GammaX);
            I_ = I_ * 65536.0L;
            GammaLUT_I[I] = roundl(I_);
        }

        GammaX = 1.0 / GammaX;

        for (int I = 0; I <= 70000; I++)
        {
            long double I_ = I;
            I_ = I_ / 65536.0L;
            I_ = powl(I_, GammaX);
            I_ = I_ * 256.0L;
            GammaLUT_O[I] = roundl(I_);
            if (GammaLUT_O[I] > 255)
            {
                GammaLUT_O[I] = 255;
            }
        }
    }
}

///
/// \brief TransformItem::GetInfo - Item text info insplayed on transform list
/// \return
///
string TransformItem::GetInfo()
{
    string StrX = "";
    if (TransEnabled)
    {
        StrX = StrX + "[enabled] ";
    }
    else
    {
        StrX = StrX + "[disabled] ";
    }
    switch (TransType)
    {
        case 0:
            {
                StrX = StrX + "Triple 256-item LUT: ";
                switch (Trans0Type)
                {
                    case 0: StrX = StrX + " From file " + Trans0File; break;
                    case 1: StrX = StrX + " Brightness " + InfoVal(Trans0BriR) + "/" + InfoVal(Trans0BriG) + "/" + InfoVal(Trans0BriB); break;
                    case 2: StrX = StrX + " Contrast " + InfoDbVal(Trans0ConR) + "/" + InfoDbVal(Trans0ConG) + "/" + InfoDbVal(Trans0ConB) + " - bias " + InfoVal(Trans0ConBiasR) + "/" + InfoVal(Trans0ConBiasG) + "/" + InfoVal(Trans0ConBiasB); break;
                    case 3: StrX = StrX + " Invert " + InfoVal(Trans0InvR) + "/" + InfoVal(Trans0InvG) + "/" + InfoVal(Trans0InvB); break;
                    case 4: StrX = StrX + " Gamma " + InfoDbVal(Trans0GammaR) + "/" + InfoDbVal(Trans0GammaG) + "/" + InfoDbVal(Trans0GammaB); break;
                }
                if ((Trans0Type == 1) || (Trans0Type == 2) || (Trans0Type == 3) || (Trans0Type == 4))
                {
                    if (Trans0Gamma)
                    {
                        StrX += " - gamma correction";
                    }
                    else
                    {
                        StrX += " - no gamma correction";
                    }
                }
            }
            break;
        case 1:
            {
                StrX = StrX + "Single 16M-item LUT: ";
                switch (Trans1Type)
                {
                    case 0: StrX = StrX + " From file " + Trans1File; break;
                    case 1: StrX = StrX + " Saturation " + InfoDbVal(Trans1Sat) + InfoWeight(Trans1YuvWeightR, Trans1YuvWeightG, Trans1YuvWeightB); break;
                    case 2:
                    case 3:
                        {
                            if (Trans1Type == 2)
                            {
                                StrX = StrX + " RGB -> Y/C: ";
                            }
                            if (Trans1Type == 3)
                            {
                                StrX = StrX + " Y/C -> RGB: ";
                            }

                            switch (Trans1YuvType)
                            {
                                case 0: { StrX = StrX + "Red-Luma-Blue"; } break;
                                case 1: { StrX = StrX + "Red-Green-Luma"; } break;
                                case 2: { StrX = StrX + "Luma-Green-Blue"; } break;
                                case 3: { StrX = StrX + "Chroma"; } break;
                            }

                            if ((Trans1Type == 3) && (Trans1YuvType == 3))
                            {
                                StrX = StrX + " with luma = " + Eden::ToStr(Trans1YuvLuma);
                            }

                            StrX = StrX + InfoWeight(Trans1YuvWeightR, Trans1YuvWeightG, Trans1YuvWeightB);
                        }
                        break;
                    case 4: StrX = StrX + " Channels: ";
                        {
                            switch (Trans1Chan)
                            {
                                case 0: StrX = StrX + "Swap R <-> G"; break;
                                case 1: StrX = StrX + "Swap G <-> B"; break;
                                case 2: StrX = StrX + "Swap B <-> R"; break;
                                case 3: StrX = StrX + "Rotate RGB -> GBR"; break;
                                case 4: StrX = StrX + "Rotate RGB -> BRG"; break;
                                case 5: StrX = StrX + "Copy R to GB"; break;
                                case 6: StrX = StrX + "Copy G to BR"; break;
                                case 7: StrX = StrX + "Copy B to RG"; break;
                                case 8: StrX = StrX + "Copy R to G"; break;
                                case 9: StrX = StrX + "Copy G to B"; break;
                                case 10: StrX = StrX + "Copy B to R"; break;
                                case 11: StrX = StrX + "Copy B to G"; break;
                                case 12: StrX = StrX + "Copy G to R"; break;
                                case 13: StrX = StrX + "Copy R to B"; break;
                            }
                        }
                        break;
                }
                if ((Trans1Type == 1) || (Trans1Type == 2) || (Trans1Type == 3))
                {
                    if (Trans1Gamma)
                    {
                        StrX += " - gamma correction";
                    }
                    else
                    {
                        StrX += " - no gamma correction";
                    }
                }
            }
            break;
        case 2:
            {
                StrX = StrX + "Convolution: ";
                switch (Trans2Common)
                {
                    case 0: StrX = StrX + " Separated"; break;
                    case 1: StrX = StrX + " Common from R"; break;
                    case 2: StrX = StrX + " Common from G"; break;
                    case 3: StrX = StrX + " Common from B"; break;
                    case 4: StrX = StrX + " R => G"; break;
                    case 5: StrX = StrX + " G => B"; break;
                    case 6: StrX = StrX + " B => R"; break;
                    case 7: StrX = StrX + " R => B"; break;
                    case 8: StrX = StrX + " G => R"; break;
                    case 9: StrX = StrX + " B => G"; break;
                }
                if (Trans2Gamma)
                {
                    StrX += " - gamma correction";
                }
                else
                {
                    StrX += " - no gamma correction";
                }
            }
            break;
        case 3:
            {
                int SS = Trans3Matrix.size() / 25;
                int S = 0;
                for (int I = 0; I < Trans3Rot.size(); I++)
                {
                    if (Trans3Rot[I] > 0)
                    {
                        S++;
                    }
                }
                StrX = StrX + "Dedithering: " + Eden::ToStr(SS) + (SS == 1 ? " template, " : " templates, ") + Eden::ToStr(S) + (S == 1 ? " pattern" : " patterns");
            }
            break;
        case 4:
            {
                switch (Trans4Type)
                {
                    case 0:
                        {
                            StrX = StrX + "Resize " + Eden::ToStr(Trans4Size1W) + "/" + Eden::ToStr(Trans4Size2W) + " x " + Eden::ToStr(Trans4Size1H) + "/" + Eden::ToStr(Trans4Size2H);
                            switch (Trans4Size)
                            {
                                case 0: StrX = StrX + " without smoothing"; break;
                                case 1: StrX = StrX + " with fast smoothing"; break;
                                case 2: StrX = StrX + " with high quality smoothing"; break;
                            }
                        }
                        break;
                    case 1:
                        {
                            switch (Trans4Scale)
                            {
                                case 0: StrX = StrX + "Scale2x"; break;
                                case 1: StrX = StrX + "Scale3x"; break;
                                case 2: StrX = StrX + "Scale4x"; break;
                                case 3: StrX = StrX + "HQ2x"; break;
                                case 4: StrX = StrX + "HQ3x"; break;
                                case 5: StrX = StrX + "HQ4x"; break;
                            }
                            if (Trans4Channels)
                            {
                                StrX = StrX + " - channels separately";
                            }
                            else
                            {
                                StrX = StrX + " - channels together";
                            }
                        }
                        break;
                    case 2:
                        {
                            switch (Trans4LcdType)
                            {
                                case 0: StrX = StrX + "Subpixels H-RGB: "; break;
                                case 1: StrX = StrX + "Subpixels H-BGR: "; break;
                                case 2: StrX = StrX + "Subpixels V-RGB: "; break;
                                case 3: StrX = StrX + "Subpixels V-BGR: "; break;
                            }
                            switch (Trans4LcdOp)
                            {
                                case 0: StrX = StrX + "Composite color"; break;
                                case 1: StrX = StrX + "Composite luminance"; break;
                                case 2: StrX = StrX + "Decomposite - color subpixels"; break;
                                case 3: StrX = StrX + "Decomposite - gray subpixels"; break;
                                case 4: {

                                        if ((Trans4LcdChromaB == 0) && (Trans4LcdChromaV == 0) && (Trans4LcdChromaX == 0))
                                        {
                                            StrX = StrX + "Decomposite - luminance";
                                        }
                                        else
                                        {
                                            int ChB = (Trans4LcdChromaB > 0) ? (Trans4LcdChromaB * 2 - 1) : 0;
                                            int ChV = (Trans4LcdChromaV > 0) ? (Trans4LcdChromaV * 2 - 1) : 0;
                                            int ChX = (Trans4LcdChromaX > 0) ? (Trans4LcdChromaX * 2 - 1) : 0;
                                            StrX = StrX + "Decomposite - luma and chroma (" + Eden::ToStr(ChB) + "/" + Eden::ToStr(ChV) + "/" + Eden::ToStr(ChX) + ")";
                                        }
                                    }
                                    break;
                            }
                            if ((Trans4LcdOp >= 4) || (Trans4LcdOp == 1))
                            {
                                StrX = StrX + InfoWeight(Trans4LcdWeightR, Trans4LcdWeightG, Trans4LcdWeightB);
                            }
                            if (Trans4LcdInterpolation)
                            {
                                StrX = StrX + " - smoothing";
                            }
                            else
                            {
                                StrX = StrX + " - no smoothing";
                            }
                        }
                        break;
                }
            }
            break;
        case 5:
            {
                switch (Trans5Rotate)
                {
                    case 0: StrX = StrX + "No flip / rotate"; break;
                    case 1: StrX = StrX + "Upside down"; break;
                    case 2: StrX = StrX + "Flip horizontal"; break;
                    case 3: StrX = StrX + "Flip vertical"; break;
                    case 4: StrX = StrX + "Flip by main diagonal"; break;
                    case 5: StrX = StrX + "Flip by other diagonal"; break;
                    case 6: StrX = StrX + "Rotate clockwise"; break;
                    case 7: StrX = StrX + "Rotate counter clockwise"; break;
                }
            }
    }
    return StrX;
}

///
/// \brief TransformItem::InfoDbVal - Displaying dB value with sign
/// \param Val
/// \return
///
string TransformItem::InfoDbVal(int Val)
{
    if (Val == 201)
    {
        return "+inf";
    }
    if (Val == -201)
    {
        return "-inf";
    }
    string ValSX = "";
    if (Val > 0)
    {
        ValSX = "+";
    }
    if (Val < 0)
    {
        ValSX = "-";
        Val = 0 - Val;
    }
    string ValS = Eden::ToStr(Val);
    while (ValS.length() < 3)
    {
        ValS = "0" + ValS;
    }
    if (ValS[0] != '0')
    {
        ValSX.push_back(ValS[0]);
    }
    ValSX.push_back(ValS[1]);
    ValSX.push_back('.');
    ValSX.push_back(ValS[2]);
    ValSX.push_back(' ');
    ValSX.push_back('d');
    ValSX.push_back('B');
    return ValSX;
}

///
/// \brief TransformItem::InfoVal - Displaying value with sign
/// \param Val
/// \return
///
string TransformItem::InfoVal(int Val)
{
    if (Val > 0)
    {
        return "+" + Eden::ToStr(Val);
    }
    else
    {
        return Eden::ToStr(Val);
    }
}

///
/// \brief TransformItem::InfoWeight - Displaying RGB weight
/// \param WR
/// \param WG
/// \param WB
/// \return
///
string TransformItem::InfoWeight(int WR, int WG, int WB)
{
    string X = " - weight: " + Eden::ToStr(WR);
    X = X + "/" + Eden::ToStr(WG);
    X = X + "/" + Eden::ToStr(WB);
    return X;
}

///
/// \brief TransformItem::PrepareYUV - Preparing variables needen in RGB/YUV conversion
///
void TransformItem::PrepareYUV()
{
    int WR = Trans1YuvWeightR;
    int WG = Trans1YuvWeightG;
    int WB = Trans1YuvWeightB;

    if ((WR < 0) || (WG < 0) || (WB < 0) || ((WR + WG + WB) == 0))
    {
        WR = 299;
        WG = 587;
        WB = 114;
    }

    if ((WR == 0) || (WG == 0) || (WB == 0))
    {
        int Thr = 1000000;
        while ((WR < Thr) && (WG < Thr) && (WB < Thr))
        {
            WR = WR << 1;
            WG = WG << 1;
            WB = WB << 1;
        }
        if (WR == 0) { WR = 1; }
        if (WG == 0) { WG = 1; }
        if (WB == 0) { WB = 1; }
    }

    ldouble Wt = WR + WG + WB;
    YUV_RW = WR;
    YUV_GW = WG;
    YUV_BW = WB;
    YUV_RW = YUV_RW / Wt;
    YUV_GW = YUV_GW / Wt;
    YUV_BW = YUV_BW / Wt;

    YUV_RW1 = ((1.0L - YUV_RW) / 0.5);
    YUV_GW1 = ((1.0L - YUV_GW) / 0.5);
    YUV_BW1 = ((1.0L - YUV_BW) / 0.5);

    YUV_GW_RW = (YUV_RW > 0) ? ((YUV_GW * (1.0L - YUV_GW)) / (0.5 * YUV_RW)) : 0;
    YUV_BW_RW = (YUV_RW > 0) ? ((YUV_BW * (1.0L - YUV_BW)) / (0.5 * YUV_RW)) : 0;
    YUV_RW_GW = (YUV_GW > 0) ? ((YUV_RW * (1.0L - YUV_RW)) / (0.5 * YUV_GW)) : 0;
    YUV_BW_GW = (YUV_GW > 0) ? ((YUV_BW * (1.0L - YUV_BW)) / (0.5 * YUV_GW)) : 0;
    YUV_RW_BW = (YUV_BW > 0) ? ((YUV_RW * (1.0L - YUV_RW)) / (0.5 * YUV_BW)) : 0;
    YUV_GW_BW = (YUV_BW > 0) ? ((YUV_GW * (1.0L - YUV_GW)) / (0.5 * YUV_BW)) : 0;
}

///
/// \brief TransformItem::FillLUT - Filling LUT table for 3x256 and 16M LUT transforming
/// \param LUT_R - Pointer to R LUT
/// \param LUT_G - Pointer to G LUT
/// \param LUT_B - Pointer to B LUT
///
void TransformItem::FillLUT(uchar *LUT_R, uchar *LUT_G, uchar *LUT_B)
{
    GammaLUT();
    switch (TransType)
    {
        case 0:
            {
                switch (Trans0Type)
                {
                    case 0: // From file
                        {
                            string FileTypeSignature = Eden::ToLower(Trans0File.substr(Trans0File.size() - 4));
                            if (FileTypeSignature == ".txt")
                            {
                                fstream TransFileX(Eden::File(Trans0File), ios::in);
                                if (TransFileX.is_open())
                                {
                                    vector<string> Buf;
                                    ReadVector(TransFileX, Buf, false);
                                    int Resolution = Eden::ToInt(Buf[0]);
                                    int I_L = 0;
                                    int II_L = 0;

                                    switch (Resolution)
                                    {
                                        case 1: { I_L =   2; II_L = 128; } break;
                                        case 2: { I_L =   4; II_L =  64; } break;
                                        case 3: { I_L =   8; II_L =  32; } break;
                                        case 4: { I_L =  16; II_L =  16; } break;
                                        case 5: { I_L =  32; II_L =   8; } break;
                                        case 6: { I_L =  64; II_L =   4; } break;
                                        case 7: { I_L = 128; II_L =   2; } break;
                                        case 8: { I_L = 256; II_L =   1; } break;
                                    }

                                    int P = 0;
                                    for (int I = 0; I < I_L; I++)
                                    {
                                        ReadVector(TransFileX, Buf, false);
                                        for (int II = 0; II < II_L; II++)
                                        {
                                            LUT_R[P] = Eden::ToInt(Buf[0]);
                                            LUT_G[P] = Eden::ToInt(Buf[1]);
                                            LUT_B[P] = Eden::ToInt(Buf[2]);
                                            P++;
                                        }
                                    }

                                    TransFileX.close();
                                }
                            }
                            if (FileTypeSignature == ".bin")
                            {
                                fstream TransFileX(Eden::File(Trans0File), ios::in | ios::binary);
                                if (TransFileX.is_open())
                                {
                                    uchar * FileRaw = new uchar[768];
                                    TransFileX.read((char*)FileRaw, 1);

                                    int Resolution = FileRaw[0];
                                    int I_L = 0;
                                    int II_L = 0;
                                    switch (Resolution)
                                    {
                                        case 1: { I_L =   2; II_L = 128; } break;
                                        case 2: { I_L =   4; II_L =  64; } break;
                                        case 3: { I_L =   8; II_L =  32; } break;
                                        case 4: { I_L =  16; II_L =  16; } break;
                                        case 5: { I_L =  32; II_L =   8; } break;
                                        case 6: { I_L =  64; II_L =   4; } break;
                                        case 7: { I_L = 128; II_L =   2; } break;
                                        case 8: { I_L = 256; II_L =   1; } break;
                                    }

                                    int P = 0;
                                    TransFileX.read((char*)FileRaw, I_L * 3);
                                    for (int I = 0; I < I_L; I++)
                                    {
                                        for (int II = 0; II < II_L; II++)
                                        {
                                            LUT_R[P] = FileRaw[I * 3 + 0];
                                            LUT_G[P] = FileRaw[I * 3 + 1];
                                            LUT_B[P] = FileRaw[I * 3 + 2];
                                            P++;
                                        }
                                    }

                                    delete[] FileRaw;
                                    TransFileX.close();
                                }
                            }
                        }
                        break;
                    case 1: // Brightness
                        {
                            if (Trans0Gamma)
                            {
                                for (int I = 0; I < 256; I++)
                                {
                                    LUT_R[I] = GammaLUT_O[Range(GammaLUT_I[I] + (Trans0BriR * 256), 0, 70000)];
                                    LUT_G[I] = GammaLUT_O[Range(GammaLUT_I[I] + (Trans0BriG * 256), 0, 70000)];
                                    LUT_B[I] = GammaLUT_O[Range(GammaLUT_I[I] + (Trans0BriB * 256), 0, 70000)];
                                }
                            }
                            else
                            {
                                for (int I = 0; I < 256; I++)
                                {
                                    LUT_R[I] = Range(I + Trans0BriR, 0, 255);
                                    LUT_G[I] = Range(I + Trans0BriG, 0, 255);
                                    LUT_B[I] = Range(I + Trans0BriB, 0, 255);
                                }
                            }
                        }
                        break;
                    case 2: // Contrast
                        {
                            int T, BiasR, BiasG, BiasB;
                            double I_, BiasR_, BiasG_, BiasB_;
                            double ValR = ValDecibel(Trans0ConR);
                            double ValG = ValDecibel(Trans0ConG);
                            double ValB = ValDecibel(Trans0ConB);
                            double OffsetR;
                            if (Trans0Gamma)
                            {
                                BiasR = 65535 + (Trans0ConBiasR * 256);
                                BiasG = 65535 + (Trans0ConBiasG * 256);
                                BiasB = 65535 + (Trans0ConBiasB * 256);
                                BiasR_ = BiasR;
                                BiasG_ = BiasG;
                                BiasB_ = BiasB;
                                for (int I = 0; I < 256; I++)
                                {
                                    I_ = (GammaLUT_I[I] * 2) - BiasR;
                                    T = Range(round(((I_ * ValR) + BiasR_) / 2.0), 0, 70000);
                                    LUT_R[I] = GammaLUT_O[T];

                                    I_ = (GammaLUT_I[I] * 2) - BiasG;
                                    T = Range(round(((I_ * ValG) + BiasG_) / 2.0), 0, 70000);
                                    LUT_G[I] = GammaLUT_O[T];

                                    I_ = (GammaLUT_I[I] * 2) - BiasB;
                                    T = Range(round(((I_ * ValB) + BiasB_) / 2.0), 0, 70000);
                                    LUT_B[I] = GammaLUT_O[T];
                                }
                            }
                            else
                            {
                                BiasR = 255 + Trans0ConBiasR;
                                BiasG = 255 + Trans0ConBiasG;
                                BiasB = 255 + Trans0ConBiasB;
                                BiasR_ = BiasR;
                                BiasG_ = BiasG;
                                BiasB_ = BiasB;
                                for (int I = 0; I < 256; I++)
                                {
                                    I_ = (I << 1) - BiasR;
                                    LUT_R[I] = Range(round(((I_ * ValR) + BiasR_) / 2.0), 0, 255);

                                    I_ = (I << 1) - BiasG;
                                    LUT_G[I] = Range(round(((I_ * ValG) + BiasG_) / 2.0), 0, 255);

                                    I_ = (I << 1) - BiasB;
                                    LUT_B[I] = Range(round(((I_ * ValB) + BiasB_) / 2.0), 0, 255);
                                }
                            }
                        }
                        break;
                    case 3: // Invert
                        {
                            for (int I = 0; I < 256; I++)
                            {
                                LUT_R[I] = I;
                                LUT_G[I] = I;
                                LUT_B[I] = I;
                            }
                            if (Trans0InvR < 0)
                            {
                                for (int I = 0; I < (0 - Trans0InvR); I++)
                                {
                                    if (Trans0Gamma)
                                    {
                                        LUT_R[I] = GammaLUT_O[Range(65535 - GammaLUT_I[I], 0, 70000)];
                                    }
                                    else
                                    {
                                        LUT_R[I] = 255 - I;
                                    }
                                }
                            }
                            if (Trans0InvR > 0)
                            {
                                for (int I = (256 - Trans0InvR); I < 256; I++)
                                {
                                    if (Trans0Gamma)
                                    {
                                        LUT_R[I] = GammaLUT_O[Range(65535 - GammaLUT_I[I], 0, 70000)];
                                    }
                                    else
                                    {
                                        LUT_R[I] = 255 - I;
                                    }
                                }
                            }
                            if (Trans0InvG < 0)
                            {
                                for (int I = 0; I < (0 - Trans0InvG); I++)
                                {
                                    if (Trans0Gamma)
                                    {
                                        LUT_G[I] = GammaLUT_O[Range(65535 - GammaLUT_I[I], 0, 70000)];
                                    }
                                    else
                                    {
                                        LUT_G[I] = 255 - I;
                                    }
                                }
                            }
                            if (Trans0InvG > 0)
                            {
                                for (int I = (256 - Trans0InvG); I < 256; I++)
                                {
                                    if (Trans0Gamma)
                                    {
                                        LUT_G[I] = GammaLUT_O[Range(65535 - GammaLUT_I[I], 0, 70000)];
                                    }
                                    else
                                    {
                                        LUT_G[I] = 255 - I;
                                    }
                                }
                            }
                            if (Trans0InvB < 0)
                            {
                                for (int I = 0; I < (0 - Trans0InvB); I++)
                                {
                                    if (Trans0Gamma)
                                    {
                                        LUT_B[I] = GammaLUT_O[Range(65535 - GammaLUT_I[I], 0, 70000)];
                                    }
                                    else
                                    {
                                        LUT_B[I] = 255 - I;
                                    }
                                }
                            }
                            if (Trans0InvB > 0)
                            {
                                for (int I = (256 - Trans0InvB); I < 256; I++)
                                {
                                    if (Trans0Gamma)
                                    {
                                        LUT_B[I] = GammaLUT_O[Range(65535 - GammaLUT_I[I], 0, 70000)];
                                    }
                                    else
                                    {
                                        LUT_B[I] = 255 - I;
                                    }
                                }
                            }
                        }
                        break;
                    case 4: // Gamma
                        {
                            double I_;
                            double ValR = ValDecibel(0 - Trans0GammaR);
                            double ValG = ValDecibel(0 - Trans0GammaG);
                            double ValB = ValDecibel(0 - Trans0GammaB);
                            int T;
                            if (Trans0Gamma)
                            {
                                for (int I = 0; I < 256; I++)
                                {
                                    I_ = GammaLUT_I[I];
                                    I_ = I_ / 65536.0;
                                    I_ = pow(I_, ValR);
                                    I_ = I_ * 65536.0;
                                    T = Range(round(I_), 0, 70000);
                                    LUT_R[I] = GammaLUT_O[T];
                                    I_ = GammaLUT_I[I];
                                    I_ = I_ / 65536.0;
                                    I_ = pow(I_, ValG);
                                    I_ = I_ * 65536.0;
                                    T = Range(round(I_), 0, 70000);
                                    LUT_G[I] = GammaLUT_O[T];
                                    I_ = GammaLUT_I[I];
                                    I_ = I_ / 65536.0;
                                    I_ = pow(I_, ValB);
                                    I_ = I_ * 65536.0;
                                    T = Range(round(I_), 0, 70000);
                                    LUT_B[I] = GammaLUT_O[T];
                                }
                            }
                            else
                            {
                                for (int I = 0; I < 256; I++)
                                {
                                    I_ = I;
                                    I_ = I_ / 256.0;
                                    I_ = pow(I_, ValR);
                                    I_ = I_ * 256.0;
                                    LUT_R[I] = Range(round(I_), 0, 255);
                                    I_ = I;
                                    I_ = I_ / 256.0;
                                    I_ = pow(I_, ValG);
                                    I_ = I_ * 256.0;
                                    LUT_G[I] = Range(round(I_), 0, 255);
                                    I_ = I;
                                    I_ = I_ / 256.0;
                                    I_ = pow(I_, ValB);
                                    I_ = I_ * 256.0;
                                    LUT_B[I] = Range(round(I_), 0, 255);
                                }
                            }
                        }
                        break;
                }
            }
            break;
        case 1:
            {
                int R, G, B, I;
                switch (Trans1Type)
                {
                    case 0: // From file
                        {
                            int RR, GG, BB;
                            string FileTypeSignature = Eden::ToLower(Trans1File.substr(Trans1File.size() - 4));
                            if (FileTypeSignature == ".txt")
                            {
                                fstream TransFileX(Eden::File(Trans1File), ios::in);
                                if (TransFileX.is_open())
                                {
                                    vector<string> Buf;
                                    ReadVector(TransFileX, Buf, false);
                                    int Resolution = Eden::ToInt(Buf[0]);
                                    int ColumnCount = Eden::ToInt(Buf[1]);
                                    int I_L = 0;
                                    int II_L = 0;

                                    switch (Resolution)
                                    {
                                        case 1: { I_L =   2; II_L = 128; } break;
                                        case 2: { I_L =   4; II_L =  64; } break;
                                        case 3: { I_L =   8; II_L =  32; } break;
                                        case 4: { I_L =  16; II_L =  16; } break;
                                        case 5: { I_L =  32; II_L =   8; } break;
                                        case 6: { I_L =  64; II_L =   4; } break;
                                        case 7: { I_L = 128; II_L =   2; } break;
                                        case 8: { I_L = 256; II_L =   1; } break;
                                    }

                                    int P = 0;
                                    int PP;
                                    I = 0;
                                    ReadVector(TransFileX, Buf, false);

                                    for (B = 0; B < I_L; B++)
                                    {
                                        for (G = 0; G < I_L; G++)
                                        {
                                            for (R = 0; R < I_L; R++)
                                            {
                                                PP = P;
                                                for (BB = 0; BB < II_L; BB++)
                                                {
                                                    for (GG = 0; GG < II_L; GG++)
                                                    {
                                                        for (RR = 0; RR < II_L; RR++)
                                                        {
                                                            LUT_R[PP] = Eden::ToInt(Buf[I * 3 + 0]);
                                                            LUT_G[PP] = Eden::ToInt(Buf[I * 3 + 1]);
                                                            LUT_B[PP] = Eden::ToInt(Buf[I * 3 + 2]);
                                                            PP++;
                                                        }
                                                        PP -= II_L;
                                                        PP += (1 << 8);
                                                    }
                                                    PP -= (II_L << 8);
                                                    PP += (1 << 16);
                                                }

                                                I++;
                                                if (I == ColumnCount)
                                                {
                                                    ReadVector(TransFileX, Buf, false);
                                                    I = 0;
                                                }

                                                P += II_L;
                                            }
                                            P -= 256;
                                            P += (II_L << 8);
                                        }
                                        P -= 65536;
                                        P += (II_L << 16);
                                    }

                                    TransFileX.close();
                                }
                            }
                            if (FileTypeSignature == ".bin")
                            {
                                fstream TransFileX(Eden::File(Trans1File), ios::in | ios::binary);
                                if (TransFileX.is_open())
                                {
                                    uchar * FileRaw = new uchar[1];
                                    TransFileX.read((char*)FileRaw, 1);

                                    int Resolution = FileRaw[0];
                                    delete[] FileRaw;

                                    int I_L = 0;
                                    int II_L = 0;
                                    switch (Resolution)
                                    {
                                        case 1: { I_L =   2; II_L = 128; } break;
                                        case 2: { I_L =   4; II_L =  64; } break;
                                        case 3: { I_L =   8; II_L =  32; } break;
                                        case 4: { I_L =  16; II_L =  16; } break;
                                        case 5: { I_L =  32; II_L =   8; } break;
                                        case 6: { I_L =  64; II_L =   4; } break;
                                        case 7: { I_L = 128; II_L =   2; } break;
                                        case 8: { I_L = 256; II_L =   1; } break;
                                    }
                                    FileRaw = new uchar[3 * I_L * I_L * I_L];
                                    TransFileX.read((char*)FileRaw, 3 * I_L * I_L * I_L);

                                    int P = 0;
                                    int PP;
                                    I = 0;
                                    for (B = 0; B < I_L; B++)
                                    {
                                        for (G = 0; G < I_L; G++)
                                        {
                                            for (R = 0; R < I_L; R++)
                                            {
                                                PP = P;
                                                for (BB = 0; BB < II_L; BB++)
                                                {
                                                    for (GG = 0; GG < II_L; GG++)
                                                    {
                                                        for (RR = 0; RR < II_L; RR++)
                                                        {
                                                            LUT_R[PP] = FileRaw[I * 3 + 0];
                                                            LUT_G[PP] = FileRaw[I * 3 + 1];
                                                            LUT_B[PP] = FileRaw[I * 3 + 2];
                                                            PP++;
                                                        }
                                                        PP -= II_L;
                                                        PP += (1 << 8);
                                                    }
                                                    PP -= (II_L << 8);
                                                    PP += (1 << 16);
                                                }

                                                I++;

                                                P += II_L;
                                            }
                                            P -= 256;
                                            P += (II_L << 8);
                                        }
                                        P -= 65536;
                                        P += (II_L << 16);
                                    }

                                    delete[] FileRaw;
                                    TransFileX.close();
                                }
                            }
                        }
                        break;
                    case 1: // Saturation
                        {
                            PrepareYUV();
                            I = 0;
                            ldouble SatFactor = ValDecibelL(Trans1Sat);
                            if (Trans1Gamma)
                            {
                                YUV16bit = true;
                                for (B = 0; B < 256; B++)
                                {
                                    for (G = 0; G < 256; G++)
                                    {
                                        for (R = 0; R < 256; R++)
                                        {
                                            YUV_R = GammaLUT_I[R];
                                            YUV_G = GammaLUT_I[G];
                                            YUV_B = GammaLUT_I[B];
                                            RGB2YUV();

                                            YUV_C_R_ = YUV_C_R_ * SatFactor;
                                            YUV_C_G_ = YUV_C_G_ * SatFactor;
                                            YUV_C_B_ = YUV_C_B_ * SatFactor;

                                            YUV2RGB();
                                            LUT_R[I] = GammaLUT_O[YUV_R];
                                            LUT_G[I] = GammaLUT_O[YUV_G];
                                            LUT_B[I] = GammaLUT_O[YUV_B];
                                            I++;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                YUV16bit = false;
                                for (B = 0; B < 256; B++)
                                {
                                    for (G = 0; G < 256; G++)
                                    {
                                        for (R = 0; R < 256; R++)
                                        {
                                            YUV_R = R;
                                            YUV_G = G;
                                            YUV_B = B;
                                            RGB2YUV();

                                            YUV_C_R_ = YUV_C_R_ * SatFactor;
                                            YUV_C_G_ = YUV_C_G_ * SatFactor;
                                            YUV_C_B_ = YUV_C_B_ * SatFactor;

                                            YUV2RGB();
                                            LUT_R[I] = YUV_R;
                                            LUT_G[I] = YUV_G;
                                            LUT_B[I] = YUV_B;
                                            I++;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case 2: // RGB -> YUV
                        {
                            PrepareYUV();
                            I = 0;
                            switch (Trans1YuvType)
                            {
                                case 0:
                                    if (Trans1Gamma)
                                    {
                                        YUV16bit = true;
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    YUV_R = GammaLUT_I[R];
                                                    YUV_G = GammaLUT_I[G];
                                                    YUV_B = GammaLUT_I[B];
                                                    RGB2YUV();
                                                    RGB2YUV_();
                                                    LUT_R[I] = GammaLUT_O[YUV_C_R];
                                                    LUT_G[I] = GammaLUT_O[YUV_L];
                                                    LUT_B[I] = GammaLUT_O[YUV_C_B];
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        YUV16bit = false;
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    YUV_R = R;
                                                    YUV_G = G;
                                                    YUV_B = B;
                                                    RGB2YUV();
                                                    RGB2YUV_();
                                                    LUT_R[I] = YUV_C_R;
                                                    LUT_G[I] = YUV_L;
                                                    LUT_B[I] = YUV_C_B;
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                case 1:
                                    if (Trans1Gamma)
                                    {
                                        YUV16bit = true;
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    YUV_R = GammaLUT_I[R];
                                                    YUV_G = GammaLUT_I[G];
                                                    YUV_B = GammaLUT_I[B];
                                                    RGB2YUV();
                                                    RGB2YUV_();
                                                    LUT_R[I] = GammaLUT_O[YUV_C_R];
                                                    LUT_G[I] = GammaLUT_O[YUV_C_G];
                                                    LUT_B[I] = GammaLUT_O[YUV_L];
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        YUV16bit = false;
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    YUV_R = R;
                                                    YUV_G = G;
                                                    YUV_B = B;
                                                    RGB2YUV();
                                                    RGB2YUV_();
                                                    LUT_R[I] = YUV_C_R;
                                                    LUT_G[I] = YUV_C_G;
                                                    LUT_B[I] = YUV_L;
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                case 2:
                                    if (Trans1Gamma)
                                    {
                                        YUV16bit = true;
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    YUV_R = GammaLUT_I[R];
                                                    YUV_G = GammaLUT_I[G];
                                                    YUV_B = GammaLUT_I[B];
                                                    RGB2YUV();
                                                    RGB2YUV_();
                                                    LUT_R[I] = GammaLUT_O[YUV_L];
                                                    LUT_G[I] = GammaLUT_O[YUV_C_G];
                                                    LUT_B[I] = GammaLUT_O[YUV_C_B];
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        YUV16bit = false;
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    YUV_R = R;
                                                    YUV_G = G;
                                                    YUV_B = B;
                                                    RGB2YUV();
                                                    RGB2YUV_();
                                                    LUT_R[I] = YUV_L;
                                                    LUT_G[I] = YUV_C_G;
                                                    LUT_B[I] = YUV_C_B;
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                case 3:
                                    if (Trans1Gamma)
                                    {
                                        YUV16bit = true;
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    YUV_R = GammaLUT_I[R];
                                                    YUV_G = GammaLUT_I[G];
                                                    YUV_B = GammaLUT_I[B];
                                                    RGB2YUV();
                                                    RGB2YUV_();
                                                    LUT_R[I] = GammaLUT_O[YUV_C_R];
                                                    LUT_G[I] = GammaLUT_O[YUV_C_G];
                                                    LUT_B[I] = GammaLUT_O[YUV_C_B];
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        YUV16bit = false;
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    YUV_R = R;
                                                    YUV_G = G;
                                                    YUV_B = B;
                                                    RGB2YUV();
                                                    RGB2YUV_();
                                                    LUT_R[I] = YUV_C_R;
                                                    LUT_G[I] = YUV_C_G;
                                                    LUT_B[I] = YUV_C_B;
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    break;
                            }
                        }
                        break;
                    case 3: // YUV -> RGB
                        {
                            PrepareYUV();
                            I = 0;
                            switch (Trans1YuvType)
                            {
                                case 0:
                                    if (Trans1Gamma)
                                    {
                                        YUV16bit = true;
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    YUV_C_R = GammaLUT_I[R];
                                                    YUV_L = GammaLUT_I[G];
                                                    YUV_C_B = GammaLUT_I[B];
                                                    YUV2RGB_();
                                                    YUV2RGB_G();
                                                    LUT_R[I] = GammaLUT_O[YUV_R];
                                                    LUT_G[I] = GammaLUT_O[YUV_G];
                                                    LUT_B[I] = GammaLUT_O[YUV_B];
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        YUV16bit = false;
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    YUV_C_R = R;
                                                    YUV_L = G;
                                                    YUV_C_B = B;
                                                    YUV2RGB_();
                                                    YUV2RGB_G();
                                                    LUT_R[I] = YUV_R;
                                                    LUT_G[I] = YUV_G;
                                                    LUT_B[I] = YUV_B;
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                case 1:
                                    if (Trans1Gamma)
                                    {
                                        YUV16bit = true;
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    YUV_C_R = GammaLUT_I[R];
                                                    YUV_C_G = GammaLUT_I[G];
                                                    YUV_L = GammaLUT_I[B];
                                                    YUV2RGB_();
                                                    YUV2RGB_B();
                                                    LUT_R[I] = GammaLUT_O[YUV_R];
                                                    LUT_G[I] = GammaLUT_O[YUV_G];
                                                    LUT_B[I] = GammaLUT_O[YUV_B];
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        YUV16bit = false;
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    YUV_C_R = R;
                                                    YUV_C_G = G;
                                                    YUV_L = B;
                                                    YUV2RGB_();
                                                    YUV2RGB_B();
                                                    LUT_R[I] = YUV_R;
                                                    LUT_G[I] = YUV_G;
                                                    LUT_B[I] = YUV_B;
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                case 2:
                                    if (Trans1Gamma)
                                    {
                                        YUV16bit = true;
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    YUV_L = GammaLUT_I[R];
                                                    YUV_C_G = GammaLUT_I[G];
                                                    YUV_C_B = GammaLUT_I[B];
                                                    YUV2RGB_();
                                                    YUV2RGB_R();
                                                    LUT_R[I] = GammaLUT_O[YUV_R];
                                                    LUT_G[I] = GammaLUT_O[YUV_G];
                                                    LUT_B[I] = GammaLUT_O[YUV_B];
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        YUV16bit = false;
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    YUV_L = R;
                                                    YUV_C_G = G;
                                                    YUV_C_B = B;
                                                    YUV2RGB_();
                                                    YUV2RGB_R();
                                                    LUT_R[I] = YUV_R;
                                                    LUT_G[I] = YUV_G;
                                                    LUT_B[I] = YUV_B;
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                case 3:
                                    if (Trans1Gamma)
                                    {
                                        YUV16bit = true;
                                        YUV_L = Trans1YuvLuma << 8;
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    YUV_C_R = GammaLUT_I[R];
                                                    YUV_C_G = GammaLUT_I[G];
                                                    YUV_C_B = GammaLUT_I[B];
                                                    YUV2RGB_();
                                                    YUV2RGB();
                                                    LUT_R[I] = GammaLUT_O[YUV_R];
                                                    LUT_G[I] = GammaLUT_O[YUV_G];
                                                    LUT_B[I] = GammaLUT_O[YUV_B];
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        YUV16bit = false;
                                        YUV_L = Trans1YuvLuma;
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    YUV_C_R = R;
                                                    YUV_C_G = G;
                                                    YUV_C_B = B;
                                                    YUV2RGB_();
                                                    YUV2RGB();
                                                    LUT_R[I] = YUV_R;
                                                    LUT_G[I] = YUV_G;
                                                    LUT_B[I] = YUV_B;
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    break;
                            }
                        }
                        break;
                    case 4: // Swap channels
                        {
                            I = 0;
                            switch (Trans1Chan)
                            {
                                case 0: // R <-> G
                                    {
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    LUT_R[I] = G;
                                                    LUT_G[I] = R;
                                                    LUT_B[I] = B;
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                case 1: // G <-> B
                                    {
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    LUT_R[I] = R;
                                                    LUT_G[I] = B;
                                                    LUT_B[I] = G;
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                case 2: // B <-> R
                                    {
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    LUT_R[I] = B;
                                                    LUT_G[I] = G;
                                                    LUT_B[I] = R;
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                case 3: // RGB <-> GBR
                                    {
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    LUT_R[I] = B;
                                                    LUT_G[I] = R;
                                                    LUT_B[I] = G;
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                case 4: // RGB <-> BRG
                                    {
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    LUT_R[I] = G;
                                                    LUT_G[I] = B;
                                                    LUT_B[I] = R;
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                case 5: // R -> GB
                                    {
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    LUT_R[I] = R;
                                                    LUT_G[I] = R;
                                                    LUT_B[I] = R;
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                case 6: // G -> BR
                                    {
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    LUT_R[I] = G;
                                                    LUT_G[I] = G;
                                                    LUT_B[I] = G;
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                case 7: // B -> RG
                                    {
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    LUT_R[I] = B;
                                                    LUT_G[I] = B;
                                                    LUT_B[I] = B;
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                case 8: // R -> G
                                    {
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    LUT_R[I] = R;
                                                    LUT_G[I] = R;
                                                    LUT_B[I] = B;
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                case 9: // G -> B
                                    {
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    LUT_R[I] = R;
                                                    LUT_G[I] = G;
                                                    LUT_B[I] = G;
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                case 10: // B -> R
                                    {
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    LUT_R[I] = B;
                                                    LUT_G[I] = G;
                                                    LUT_B[I] = B;
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                case 11: // B -> G
                                    {
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    LUT_R[I] = R;
                                                    LUT_G[I] = B;
                                                    LUT_B[I] = B;
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                case 12: // G -> R
                                    {
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    LUT_R[I] = G;
                                                    LUT_G[I] = G;
                                                    LUT_B[I] = B;
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                case 13: // R -> B
                                    {
                                        for (B = 0; B < 256; B++)
                                        {
                                            for (G = 0; G < 256; G++)
                                            {
                                                for (R = 0; R < 256; R++)
                                                {
                                                    LUT_R[I] = R;
                                                    LUT_G[I] = G;
                                                    LUT_B[I] = R;
                                                    I++;
                                                }
                                            }
                                        }
                                    }
                                    break;
                            }
                        }
                        break;
                }
            }
            break;
    }
}

///
/// \brief TransformItem::SaveLUT - Saving LUT table into file
/// \param FileName - File name
/// \param Resolution - Number from 1 to 8, which determines LUT resolution
///
void TransformItem::SaveLUT(string FileName, int Resolution)
{
    string FileTypeSignature = Eden::ToLower(FileName.substr(FileName.size() - 4));
    bool Binary = (FileTypeSignature == ".bin") ? true : false;
    switch (TransType)
    {
        case 0:
            {
                uchar * TempR = new uchar[256];
                uchar * TempG = new uchar[256];
                uchar * TempB = new uchar[256];
                FillLUT(TempR, TempG, TempB);
                fstream FS(Eden::File(FileName), Binary ? (ios::out | ios::binary) : (ios::out));
                if (FS.is_open())
                {
                    uchar * TempX;
                    if (Binary)
                    {
                        TempX = new uchar[769];
                        TempX[0] = Resolution;
                    }
                    else
                    {
                        FS << Eden::ToStr(Resolution) << endl;
                    }

                    int I_L = 0;
                    int II_L = 0;
                    switch (Resolution)
                    {
                        case 1: { I_L =   2; II_L = 128; } break;
                        case 2: { I_L =   4; II_L =  64; } break;
                        case 3: { I_L =   8; II_L =  32; } break;
                        case 4: { I_L =  16; II_L =  16; } break;
                        case 5: { I_L =  32; II_L =   8; } break;
                        case 6: { I_L =  64; II_L =   4; } break;
                        case 7: { I_L = 128; II_L =   2; } break;
                        case 8: { I_L = 256; II_L =   1; } break;
                    }

                    int P = 0;
                    for (int I = 0; I < I_L; I++)
                    {
                        int XR = 0;
                        int XG = 0;
                        int XB = 0;
                        for (int II = 0; II < II_L; II++)
                        {
                            XR += (int)TempR[P];
                            XG += (int)TempG[P];
                            XB += (int)TempB[P];
                            P++;
                        }
                        XR = round(((double)XR) / ((double)II_L));
                        XG = round(((double)XG) / ((double)II_L));
                        XB = round(((double)XB) / ((double)II_L));

                        if (Binary)
                        {
                            TempX[I * 3 + 1] = XR;
                            TempX[I * 3 + 2] = XG;
                            TempX[I * 3 + 3] = XB;
                        }
                        else
                        {
                            FS << Eden::ToStr(XR) << "\t" << Eden::ToStr(XG) << "\t" << Eden::ToStr(XB) << endl;
                        }
                    }

                    if (Binary)
                    {
                        FS.write((char*)TempX, 1 + (I_L * 3));
                        delete[] TempX;
                    }

                    FS.close();
                }
                delete[] TempR;
                delete[] TempG;
                delete[] TempB;
            }
            break;
        case 1:
            {
                uchar * TempR = new uchar[16777216];
                uchar * TempG = new uchar[16777216];
                uchar * TempB = new uchar[16777216];
                FillLUT(TempR, TempG, TempB);
                fstream FS(Eden::File(FileName), Binary ? (ios::out | ios::binary) : (ios::out));
                if (FS.is_open())
                {
                    int I_L = 0;
                    int II_L = 0;
                    uchar * TempX;
                    switch (Resolution)
                    {
                        case 1: { I_L =   2; II_L = 128; } break;
                        case 2: { I_L =   4; II_L =  64; } break;
                        case 3: { I_L =   8; II_L =  32; } break;
                        case 4: { I_L =  16; II_L =  16; } break;
                        case 5: { I_L =  32; II_L =   8; } break;
                        case 6: { I_L =  64; II_L =   4; } break;
                        case 7: { I_L = 128; II_L =   2; } break;
                        case 8: { I_L = 256; II_L =   1; } break;
                    }

                    if (Binary)
                    {
                        TempX = new uchar[1 + (3 * I_L * I_L * I_L)];
                        TempX[0] = Resolution;
                    }
                    else
                    {
                        FS << Eden::ToStr(Resolution) << "\t" << Eden::ToStr(I_L);
                    }


                    int I = 0;
                    int P = 0;
                    for (int B = 0; B < I_L; B++)
                    {
                        for (int G = 0; G < I_L; G++)
                        {
                            for (int R = 0; R < I_L; R++)
                            {
                                long XR = 0;
                                long XG = 0;
                                long XB = 0;
                                int PP = P;
                                for (int BB = 0; BB < II_L; BB++)
                                {
                                    for (int GG = 0; GG < II_L; GG++)
                                    {
                                        for (int RR = 0; RR < II_L; RR++)
                                        {
                                            XR += (long)TempR[PP];
                                            XG += (long)TempG[PP];
                                            XB += (long)TempB[PP];
                                            PP++;
                                        }
                                        PP -= II_L;
                                        PP += (1 << 8);
                                    }
                                    PP -= (II_L << 8);
                                    PP += (1 << 16);
                                }

                                XR = round(((double)XR) / ((double)(II_L * II_L * II_L)));
                                XG = round(((double)XG) / ((double)(II_L * II_L * II_L)));
                                XB = round(((double)XB) / ((double)(II_L * II_L * II_L)));

                                if (Binary)
                                {
                                    TempX[I * 3 + 1] = XR;
                                    TempX[I * 3 + 2] = XG;
                                    TempX[I * 3 + 3] = XB;
                                }
                                else
                                {
                                    if ((I % I_L) == 0)
                                    {
                                        FS << endl;
                                    }
                                    else
                                    {
                                        FS << "\t";
                                    }
                                    FS << Eden::ToStr(XR) << "\t" << Eden::ToStr(XG) << "\t" << Eden::ToStr(XB);
                                }
                                I++;
                                P += II_L;
                            }
                            P -= 256;
                            P += (II_L << 8);
                        }
                        P -= 65536;
                        P += (II_L << 16);
                    }

                    if (Binary)
                    {
                        FS.write((char*)TempX, 1 + (3 * I_L * I_L * I_L));
                        delete[] TempX;
                    }
                    else
                    {
                        FS << endl;
                    }

                    FS.close();
                }
                delete[] TempR;
                delete[] TempG;
                delete[] TempB;
            }
            break;
    }
}

///
/// \brief TransformItem::Convert256To16M - Convert 3x256 LUT into 16M LUT meaning the same transform, udet in LUT merging
/// \param LUT_R
/// \param LUT_G
/// \param LUT_B
/// \param LUT_R_
/// \param LUT_G_
/// \param LUT_B_
///
void TransformItem::Convert256To16M(uchar *LUT_R, uchar *LUT_G, uchar *LUT_B, uchar *LUT_R_, uchar *LUT_G_, uchar *LUT_B_)
{
    int I = 0;
    for (int B = 0; B < 256; B++)
    {
        for (int G = 0; G < 256; G++)
        {
            for (int R = 0; R < 256; R++)
            {
                LUT_R_[I] = LUT_R[R];
                LUT_G_[I] = LUT_G[G];
                LUT_B_[I] = LUT_B[B];
                I++;
            }
        }
    }
}

///
/// \brief TransformItem::Merge256 - Merge 3x256 LUT with other 3x256 LUT
/// \param LUT_R
/// \param LUT_G
/// \param LUT_B
/// \param LUT_R_
/// \param LUT_G_
/// \param LUT_B_
///
void TransformItem::Merge256(uchar *LUT_R, uchar *LUT_G, uchar *LUT_B, uchar *LUT_R_, uchar *LUT_G_, uchar *LUT_B_)
{
    for (int I = 0; I < 256; I++)
    {
        LUT_R[I] = LUT_R_[LUT_R[I]];
        LUT_G[I] = LUT_G_[LUT_G[I]];
        LUT_B[I] = LUT_B_[LUT_B[I]];
    }
}

///
/// \brief TransformItem::Merge16M - Merge 16M LUT with other 16M LUT
/// \param LUT_R
/// \param LUT_G
/// \param LUT_B
/// \param LUT_R_
/// \param LUT_G_
/// \param LUT_B_
///
void TransformItem::Merge16M(uchar *LUT_R, uchar *LUT_G, uchar *LUT_B, uchar *LUT_R_, uchar *LUT_G_, uchar *LUT_B_)
{
    int I = 0;
    int RGB, R_, G_, B_;
    for (int B = 0; B < 256; B++)
    {
        for (int G = 0; G < 256; G++)
        {
            for (int R = 0; R < 256; R++)
            {
                R_ = LUT_R[I];
                G_ = LUT_G[I];
                B_ = LUT_B[I];
                RGB = (B_ << 16) + (G_ << 8) + (R_);
                LUT_R[I] = LUT_R_[RGB];
                LUT_G[I] = LUT_G_[RGB];
                LUT_B[I] = LUT_B_[RGB];
                I++;
            }
        }
    }
}

///
/// \brief TransformItem::FillConv - Get convolution table into pointed matrices
/// \param Conv_R - Pointer to R matrix
/// \param Conv_G - Pointer to G matrix
/// \param Conv_B - Pointer to B matrix
///
void TransformItem::FillConv(int *Conv_R, int *Conv_G, int *Conv_B)
{
    Trans2MatrixR[25] = Trans2Offset1R;
    Trans2MatrixR[26] = Trans2GainR;
    Trans2MatrixR[27] = Trans2Offset2R;

    Trans2MatrixG[25] = Trans2Offset1G;
    Trans2MatrixG[26] = Trans2GainG;
    Trans2MatrixG[27] = Trans2Offset2G;

    Trans2MatrixB[25] = Trans2Offset1B;
    Trans2MatrixB[26] = Trans2GainB;
    Trans2MatrixB[27] = Trans2Offset2B;

    for (int I = 0; I < 28; I++)
    {
        switch (Trans2Common)
        {
            case 0: Conv_R[I] = Trans2MatrixR[I]; Conv_G[I] = Trans2MatrixG[I]; Conv_B[I] = Trans2MatrixB[I]; break;
            case 1: Conv_R[I] = Trans2MatrixR[I]; Conv_G[I] = Trans2MatrixR[I]; Conv_B[I] = Trans2MatrixR[I]; break;
            case 2: Conv_R[I] = Trans2MatrixG[I]; Conv_G[I] = Trans2MatrixG[I]; Conv_B[I] = Trans2MatrixG[I]; break;
            case 3: Conv_R[I] = Trans2MatrixB[I]; Conv_G[I] = Trans2MatrixB[I]; Conv_B[I] = Trans2MatrixB[I]; break;
            case 4: Conv_R[I] = Trans2MatrixR[I]; Conv_G[I] = Trans2MatrixR[I]; Conv_B[I] = Trans2MatrixB[I]; break;
            case 5: Conv_R[I] = Trans2MatrixR[I]; Conv_G[I] = Trans2MatrixG[I]; Conv_B[I] = Trans2MatrixG[I]; break;
            case 6: Conv_R[I] = Trans2MatrixB[I]; Conv_G[I] = Trans2MatrixG[I]; Conv_B[I] = Trans2MatrixB[I]; break;
            case 7: Conv_R[I] = Trans2MatrixR[I]; Conv_G[I] = Trans2MatrixG[I]; Conv_B[I] = Trans2MatrixR[I]; break;
            case 8: Conv_R[I] = Trans2MatrixG[I]; Conv_G[I] = Trans2MatrixG[I]; Conv_B[I] = Trans2MatrixB[I]; break;
            case 9: Conv_R[I] = Trans2MatrixR[I]; Conv_G[I] = Trans2MatrixB[I]; Conv_B[I] = Trans2MatrixB[I]; break;
        }
    }
}

///
/// \brief TransformItem::ValDecibel - Calculate double value from decibel
/// \param DB
/// \return
///
double TransformItem::ValDecibel(int DB)
{
    if ((DB > (-201)) && (DB < (201)))
    {
        double Val = DB;
        Val = DB * 0.01;
        Val = pow(10.0, Val);
        return Val;
    }
    else
    {
        if (DB < 0)
        {
            return 0;
        }
        else
        {
            return 1000000;
        }
    }
}

///
/// \brief TransformItem::ValDecibelL - Calculate long double value from decibel
/// \param DB
/// \return
///
ldouble TransformItem::ValDecibelL(int DB)
{
    if ((DB > (-201)) && (DB < (201)))
    {
        ldouble Val = DB;
        Val = DB * 0.01L;
        Val = powl(10.0L, Val);
        return Val;
    }
    else
    {
        if (DB < 0)
        {
            return 0;
        }
        else
        {
            return 1000000;
        }
    }
}

///
/// \brief TransformItem::RGB2YUV - Convert RGB into luma/chroma
///
void TransformItem::RGB2YUV()
{
    YUV_R_ = YUV_R;
    YUV_G_ = YUV_G;
    YUV_B_ = YUV_B;
    if (YUV16bit)
    {
        YUV_R_ = YUV_R_ / 65535.0;
        YUV_G_ = YUV_G_ / 65535.0;
        YUV_B_ = YUV_B_ / 65535.0;
    }
    else
    {
        YUV_R_ = YUV_R_ / 255.0;
        YUV_G_ = YUV_G_ / 255.0;
        YUV_B_ = YUV_B_ / 255.0;
    }

    YUV_L_ = (YUV_RW * YUV_R_) + (YUV_GW * YUV_G_) + (YUV_BW * YUV_B_);
    YUV_C_R_ = 0.5 * ((YUV_R_ - YUV_L_) / (1.0L - YUV_RW));
    YUV_C_G_ = 0.5 * ((YUV_G_ - YUV_L_) / (1.0L - YUV_GW));
    YUV_C_B_ = 0.5 * ((YUV_B_ - YUV_L_) / (1.0L - YUV_BW));
}

///
/// \brief TransformItem::RGB2YUV_ - Set luma/chroma into 8-bit values
///
void TransformItem::RGB2YUV_()
{
    if (YUV16bit)
    {
        YUV_L = Range(round(YUV_L_ * 65535.0), 0, 65535);
        YUV_C_R = Range(round(YUV_C_R_ * 65535.0), -32767, 32768) + 32767;
        YUV_C_G = Range(round(YUV_C_G_ * 65535.0), -32767, 32768) + 32767;
        YUV_C_B = Range(round(YUV_C_B_ * 65535.0), -32767, 32768) + 32767;
    }
    else
    {
        YUV_L = Range(round(YUV_L_ * 255.0), 0, 255);
        YUV_C_R = Range(round(YUV_C_R_ * 255.0), -127, 128) + 127;
        YUV_C_G = Range(round(YUV_C_G_ * 255.0), -127, 128) + 127;
        YUV_C_B = Range(round(YUV_C_B_ * 255.0), -127, 128) + 127;
    }
}

///
/// \brief TransformItem::YUV2RGB_ - Get luma/chroma from 8-bit values
///
void TransformItem::YUV2RGB_()
{
    YUV_L_ = YUV_L;
    if (YUV16bit)
    {
        YUV_L_ = YUV_L_ / 65535.0;
        YUV_C_R_ = YUV_C_R - 32767;
        YUV_C_R_ = YUV_C_R_ / 65535.0;
        YUV_C_G_ = YUV_C_G - 32767;
        YUV_C_G_ = YUV_C_G_ / 65535.0;
        YUV_C_B_ = YUV_C_B - 32767;
        YUV_C_B_ = YUV_C_B_ / 65535.0;
    }
    else
    {
        YUV_L_ = YUV_L_ / 255.0;
        YUV_C_R_ = YUV_C_R - 127;
        YUV_C_R_ = YUV_C_R_ / 255.0;
        YUV_C_G_ = YUV_C_G - 127;
        YUV_C_G_ = YUV_C_G_ / 255.0;
        YUV_C_B_ = YUV_C_B - 127;
        YUV_C_B_ = YUV_C_B_ / 255.0;
    }
}

///
/// \brief TransformItem::YUV2RGB - Convert luma and all chroma values into RGB
///
void TransformItem::YUV2RGB()
{
    YUV_R_ = YUV_L_ + (YUV_C_R_ * YUV_RW1);
    YUV_G_ = YUV_L_ + (YUV_C_G_ * YUV_GW1);
    YUV_B_ = YUV_L_ + (YUV_C_B_ * YUV_BW1);

    if (YUV16bit)
    {
        YUV_R = Range(round(YUV_R_ * 65535.0), 0, 65535);
        YUV_G = Range(round(YUV_G_ * 65535.0), 0, 65535);
        YUV_B = Range(round(YUV_B_ * 65535.0), 0, 65535);
    }
    else
    {
        YUV_R = Range(round(YUV_R_ * 255.0), 0, 255);
        YUV_G = Range(round(YUV_G_ * 255.0), 0, 255);
        YUV_B = Range(round(YUV_B_ * 255.0), 0, 255);
    }
}

///
/// \brief TransformItem::YUV2RGB_R - Convert luma and GB chroma values into RGB
///
void TransformItem::YUV2RGB_R()
{
    YUV_R_ = YUV_L_ - (YUV_C_G_ * YUV_GW_RW) - (YUV_C_B_ * YUV_BW_RW);
    YUV_G_ = YUV_L_ + (YUV_C_G_ * YUV_GW1);
    YUV_B_ = YUV_L_ + (YUV_C_B_ * YUV_BW1);

    if (YUV16bit)
    {
        YUV_R = Range(round(YUV_R_ * 65535.0), 0, 65535);
        YUV_G = Range(round(YUV_G_ * 65535.0), 0, 65535);
        YUV_B = Range(round(YUV_B_ * 65535.0), 0, 65535);
    }
    else
    {
        YUV_R = Range(round(YUV_R_ * 255.0), 0, 255);
        YUV_G = Range(round(YUV_G_ * 255.0), 0, 255);
        YUV_B = Range(round(YUV_B_ * 255.0), 0, 255);
    }
}

///
/// \brief TransformItem::YUV2RGB_G - Convert luma and BR chroma values into RGB
///
void TransformItem::YUV2RGB_G()
{
    YUV_R_ = YUV_L_ + (YUV_C_R_ * YUV_RW1);
    YUV_G_ = YUV_L_ - (YUV_C_B_ * YUV_BW_GW) - (YUV_C_R_ * YUV_RW_GW);
    YUV_B_ = YUV_L_ + (YUV_C_B_ * YUV_BW1);

    if (YUV16bit)
    {
        YUV_R = Range(round(YUV_R_ * 65535.0), 0, 65535);
        YUV_G = Range(round(YUV_G_ * 65535.0), 0, 65535);
        YUV_B = Range(round(YUV_B_ * 65535.0), 0, 65535);
    }
    else
    {
        YUV_R = Range(round(YUV_R_ * 255.0), 0, 255);
        YUV_G = Range(round(YUV_G_ * 255.0), 0, 255);
        YUV_B = Range(round(YUV_B_ * 255.0), 0, 255);
    }
}

///
/// \brief TransformItem::YUV2RGB_B - Convert luma and RG chroma values into RGB
///
void TransformItem::YUV2RGB_B()
{
    YUV_R_ = YUV_L_ + (YUV_C_R_ * YUV_RW1);
    YUV_G_ = YUV_L_ + (YUV_C_G_ * YUV_GW1);
    YUV_B_ = YUV_L_ - (YUV_C_R_ * YUV_RW_BW) - (YUV_C_G_ * YUV_GW_BW);

    if (YUV16bit)
    {
        YUV_R = Range(round(YUV_R_ * 65535.0), 0, 65535);
        YUV_G = Range(round(YUV_G_ * 65535.0), 0, 65535);
        YUV_B = Range(round(YUV_B_ * 65535.0), 0, 65535);
    }
    else
    {
        YUV_R = Range(round(YUV_R_ * 255.0), 0, 255);
        YUV_G = Range(round(YUV_G_ * 255.0), 0, 255);
        YUV_B = Range(round(YUV_B_ * 255.0), 0, 255);
    }
}


///
/// \brief TransformItem::Trans3CurrentGet - Get dedither matrix into current
///
void TransformItem::Trans3CurrentGet()
{
    if (Trans3CurrentItem < Trans3ItemCount)
    {
        Trans3CurrentProp1 = Trans3Prop[Trans3CurrentItem * 4 + 0];
        Trans3CurrentProp2 = Trans3Prop[Trans3CurrentItem * 4 + 1];
        Trans3CurrentProp3 = Trans3Prop[Trans3CurrentItem * 4 + 2];
        Trans3CurrentProp4 = Trans3Prop[Trans3CurrentItem * 4 + 3];
        Trans3CurrentRot0 = Trans3Rot[Trans3CurrentItem * 4 + 0];
        Trans3CurrentRot1 = Trans3Rot[Trans3CurrentItem * 4 + 1];
        Trans3CurrentRot2 = Trans3Rot[Trans3CurrentItem * 4 + 2];
        Trans3CurrentRot3 = Trans3Rot[Trans3CurrentItem * 4 + 3];
        for (int I = 0; I < 25; I++)
        {
            Trans3CurrentMatrix[I] = Trans3Matrix[Trans3CurrentItem * 25 + I];
        }
    }
    else
    {
        Trans3CurrentProp1 = 0;
        Trans3CurrentProp2 = 0;
        Trans3CurrentProp3 = 0;
        Trans3CurrentProp4 = 0;
        Trans3CurrentRot0 = false;
        Trans3CurrentRot1 = false;
        Trans3CurrentRot2 = false;
        Trans3CurrentRot3 = false;
        for (int I = 0; I < 25; I++)
        {
            Trans3CurrentMatrix[I] = 0;
        }
    }
}

///
/// \brief TransformItem::Trans3CurrentSet - Set dedither matrix from current
///
void TransformItem::Trans3CurrentSet()
{
    if (Trans3CurrentItem < Trans3ItemCount)
    {
        Trans3Prop[Trans3CurrentItem * 4 + 0] = Trans3CurrentProp1;
        Trans3Prop[Trans3CurrentItem * 4 + 1] = Trans3CurrentProp2;
        Trans3Prop[Trans3CurrentItem * 4 + 2] = Trans3CurrentProp3;
        Trans3Prop[Trans3CurrentItem * 4 + 3] = Trans3CurrentProp4;
        Trans3Rot[Trans3CurrentItem * 4 + 0] = Trans3CurrentRot0;
        Trans3Rot[Trans3CurrentItem * 4 + 1] = Trans3CurrentRot1;
        Trans3Rot[Trans3CurrentItem * 4 + 2] = Trans3CurrentRot2;
        Trans3Rot[Trans3CurrentItem * 4 + 3] = Trans3CurrentRot3;
        for (int I = 0; I < 25; I++)
        {
            Trans3Matrix[Trans3CurrentItem * 25 + I] = Trans3CurrentMatrix[I];
        }
    }
}

///
/// \brief TransformItem::Trans3CurrentInfo - Get text information about number of dedither matrices
/// \return
///
string TransformItem::Trans3CurrentInfo()
{
    if (Trans3ItemCount > 0)
    {
        return "Template " + Eden::ToStr(Trans3CurrentItem + 1) + " of " + Eden::ToStr(Trans3ItemCount);
    }
    else
    {
        return "No templates";
    }
}

///
/// \brief TransformItem::Trans3ItemAdd - Add dedither matrix
///
void TransformItem::Trans3ItemAdd()
{
    Trans3Prop.push_back(Trans3CurrentProp1);
    Trans3Prop.push_back(Trans3CurrentProp2);
    Trans3Prop.push_back(Trans3CurrentProp3);
    Trans3Prop.push_back(Trans3CurrentProp4);
    Trans3Rot.push_back(Trans3CurrentRot0);
    Trans3Rot.push_back(Trans3CurrentRot1);
    Trans3Rot.push_back(Trans3CurrentRot2);
    Trans3Rot.push_back(Trans3CurrentRot3);
    for (int I = 0; I < 25; I++)
    {
        Trans3Matrix.push_back(Trans3CurrentMatrix[I]);
    }
    Trans3CurrentItem = Trans3ItemCount;
    Trans3ItemCount++;
}

///
/// \brief TransformItem::Trans3ItemRem - Remove dedither matrix
///
void TransformItem::Trans3ItemRem()
{
    if (Trans3CurrentItem >= Trans3ItemCount)
    {
        return;
    }

    for (int I = 0; I < 4; I++)
    {
        Trans3Prop.erase(Trans3Prop.begin() + (Trans3CurrentItem * 4));
        Trans3Rot.erase(Trans3Rot.begin() + (Trans3CurrentItem * 4));
    }
    for (int I = 0; I < 25; I++)
    {
        Trans3Matrix.erase(Trans3Matrix.begin() + (Trans3CurrentItem * 25));
    }

    Trans3ItemCount--;
    if (Trans3CurrentItem >= Trans3ItemCount)
    {
        Trans3CurrentItem--;
        if (Trans3CurrentItem < 0)
        {
            Trans3CurrentItem = 0;
        }
    }
}

///
/// \brief TransformItem::Trans3ItemMovePrev - Move dedither matrix to previous position
///
void TransformItem::Trans3ItemMovePrev()
{
    if ((Trans3CurrentItem < Trans3ItemCount) && (Trans3CurrentItem >= 1))
    {
        int Temp;
        for (int I = 0; I < 4; I++)
        {
            Temp = Trans3Prop[Trans3CurrentItem * 4 + I];
            Trans3Prop[Trans3CurrentItem * 4 + I] = Trans3Prop[(Trans3CurrentItem - 1) * 4 + I];
            Trans3Prop[(Trans3CurrentItem - 1) * 4 + I] = Temp;
            Temp = Trans3Rot[Trans3CurrentItem * 4 + I];
            Trans3Rot[Trans3CurrentItem * 4 + I] = Trans3Rot[(Trans3CurrentItem - 1) * 4 + I];
            Trans3Rot[(Trans3CurrentItem - 1) * 4 + I] = Temp;
        }
        for (int I = 0; I < 25; I++)
        {
            Temp = Trans3Matrix[Trans3CurrentItem * 25 + I];
            Trans3Matrix[Trans3CurrentItem * 25 + I] = Trans3Matrix[(Trans3CurrentItem - 1) * 25 + I];
            Trans3Matrix[(Trans3CurrentItem - 1) * 25 + I] = Temp;
        }
        Trans3CurrentItem--;
    }
}

///
/// \brief TransformItem::Trans3ItemMoveNext - Move dedither matrix to next position
///
void TransformItem::Trans3ItemMoveNext()
{
    if ((Trans3CurrentItem < (Trans3ItemCount - 1)) && (Trans3CurrentItem >= 0))
    {
        int Temp;
        for (int I = 0; I < 4; I++)
        {
            Temp = Trans3Prop[Trans3CurrentItem * 4 + I];
            Trans3Prop[Trans3CurrentItem * 4 + I] = Trans3Prop[(Trans3CurrentItem + 1) * 4 + I];
            Trans3Prop[(Trans3CurrentItem + 1) * 4 + I] = Temp;
            Temp = Trans3Rot[Trans3CurrentItem * 4 + I];
            Trans3Rot[Trans3CurrentItem * 4 + I] = Trans3Rot[(Trans3CurrentItem + 1) * 4 + I];
            Trans3Rot[(Trans3CurrentItem + 1) * 4 + I] = Temp;
        }
        for (int I = 0; I < 25; I++)
        {
            Temp = Trans3Matrix[Trans3CurrentItem * 25 + I];
            Trans3Matrix[Trans3CurrentItem * 25 + I] = Trans3Matrix[(Trans3CurrentItem + 1) * 25 + I];
            Trans3Matrix[(Trans3CurrentItem + 1) * 25 + I] = Temp;
        }
        Trans3CurrentItem++;
    }
}

///
/// \brief TransformItem::Trans3ItemPrev - Change to previous dedither matrix
///
void TransformItem::Trans3ItemPrev()
{
    if (Trans3CurrentItem > 0)
    {
        Trans3CurrentItem--;
    }
}

///
/// \brief TransformItem::Trans3ItemNext - Change to next dedither matrix
///
void TransformItem::Trans3ItemNext()
{
    if (Trans3CurrentItem < (Trans3ItemCount - 1))
    {
        Trans3CurrentItem++;
    }
}

///
/// \brief TransformItem::ReadVector - Read vector (string values separated by tab) from file
/// \param F - Pointer to descriptor
/// \param Vec - Pointer to string vector
/// \param Loop - if true, there will be read the first non-blank vector
/// \return
///
bool TransformItem::ReadVector(fstream &F, vector<string> &Vec, bool Loop)
{
    if (Loop)
    {
        bool XX = ReadVector(F, Vec, false);
        while (XX && (Vec.size() == 0))
        {
            XX = ReadVector(F, Vec, false);
        }
        return XX;
    }

    string BufX;
    Vec.clear();
    if (getline(F, BufX))
    {
        string X = "";
        for (uint I = 0; I < BufX.size(); I++)
        {
            if (BufX[I] == 9)
            {
                Vec.push_back(X);
                X = "";
            }
            else
            {
                if (BufX[I] >= 32)
                {
                    X += BufX[I];
                }
            }
        }
        if (X.size() > 0)
        {
            Vec.push_back(X);
        }
        return true;
    }
    else
    {
        return false;
    }
}

///
/// \brief TransformItem::BinIntRead - Read 32-bit signed integer value from char array
/// \param Raw
/// \param Pos
/// \return
///
int TransformItem::BinIntRead(uchar * Raw, int Pos)
{
    int S = Raw[Pos + 0] & 128;
    int N1 = Raw[Pos + 0] & 127;
    int N2 = Raw[Pos + 1];
    int N3 = Raw[Pos + 2];
    int N4 = Raw[Pos + 3];
    int N = (N1 << 24) + (N2 << 16) + (N3 << 8) + (N4);
    if (S == 0)
    {
        return N;
    }
    else
    {
        return 0 - N;
    }
}

///
/// \brief TransformItem::BinIntWrite - Write 32-bit signed integer value to char array
/// \param Raw
/// \param Pos
/// \param Val
///
void TransformItem::BinIntWrite(uchar * Raw, int Pos, int Val)
{
    int N = (Val >= 0) ? Val : 0 - Val;
    int N1 = (N >> 24) & 128;
    int N2 = (N >> 16) & 255;
    int N3 = (N >> 8) & 255;
    int N4 = (N) & 255;
    if (Val < 0)
    {
        N1 += 128;
    }
    Raw[Pos + 0] = N1;
    Raw[Pos + 1] = N2;
    Raw[Pos + 2] = N3;
    Raw[Pos + 3] = N4;
}
