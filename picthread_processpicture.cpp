#include "picthread.h"

///
/// \brief PicThread::ColorProp - Calculating output color used by dedithering
/// \param Col1
/// \param Col2
/// \param Val1
/// \param Val2
/// \return
///
inline uint PicThread::ColorProp(uint Col1, uint Col2, uint Val1, uint Val2)
{
    return GammaLUT_O[((GammaLUT_I[Col1] * Val1) + (GammaLUT_I[Col2] * Val2)) / (Val1 + Val2)];
}

///
/// \brief PicThread::ColorProp - Calculating output color used by dedithering
/// \param Col1
/// \param Col2
/// \param Col3
/// \param Val1
/// \param Val2
/// \param Val3
/// \return
///
inline uint PicThread::ColorProp(uint Col1, uint Col2, uint Col3, uint Val1, uint Val2, uint Val3)
{
    return GammaLUT_O[((GammaLUT_I[Col1] * Val1) + (GammaLUT_I[Col2] * Val2) + (GammaLUT_I[Col3] * Val3)) / (Val1 + Val2 + Val3)];
}

///
/// \brief PicThread::ColorProp - Calculating output color used by dedithering
/// \param Col1
/// \param Col2
/// \param Col3
/// \param Col4
/// \param Val1
/// \param Val2
/// \param Val3
/// \param Val4
/// \return
///
inline uint PicThread::ColorProp(uint Col1, uint Col2, uint Col3, uint Col4, uint Val1, uint Val2, uint Val3, uint Val4)
{
    return GammaLUT_O[((GammaLUT_I[Col1] * Val1) + (GammaLUT_I[Col2] * Val2) + (GammaLUT_I[Col3] * Val3) + (GammaLUT_I[Col4] * Val4)) / (Val1 + Val2 + Val3 + Val4)];
}

///
/// \brief PicThread::ProcessPicture - Picture transforming
/// \param MinY - The first picture line
/// \param MaxY - The one after the last picture line
/// \param P - The first byte in the picture array
///
void PicThread::ProcessPicture(int MinY, int MaxY, int P, int OpNr, int PipeI_, int PipeI__)
{
    string ThrX;
    int X, Y;
    int OpNrX = OpNr + 1;
    int PicW_ = BmpBufW[OpNr];
    int PicH_ = BmpBufH[OpNr];
    int PicW_X = BmpBufW[OpNrX];
    int OpNr_ = OpNr + PipeI_;
    int OpNrX_ = OpNrX + PipeI_;
    int PP = ((PicW_ + PicBufIMargin + PicBufIMargin) * (PicBufIMargin + MinY)) + PicBufIMargin;



    switch (OpType[OpNr])
    {
        case 0: // Three 256-item LUT tables
        {
            for (Y = MinY; Y < MaxY; Y++)
            {
                for (X = 0; X < PicW_; X++)
                {
                    BmpBuf[OpNrX_][P + 2] = OpMatrixR[OpNr][BmpBuf[OpNr_][P + 2]];
                    BmpBuf[OpNrX_][P + 1] = OpMatrixG[OpNr][BmpBuf[OpNr_][P + 1]];
                    BmpBuf[OpNrX_][P + 0] = OpMatrixB[OpNr][BmpBuf[OpNr_][P + 0]];
                    P += 4;
                }
            }
            break;
        }

        case 1: // Single 16777216-item LUT table
        {
            int RGB;
            for (Y = MinY; Y < MaxY; Y++)
            {
                for (X = 0; X < PicW_; X++)
                {
                    RGB = (((int)BmpBuf[OpNr_][P + 0]) << 16) + (((int)BmpBuf[OpNr_][P + 1]) << 8) + ((int)BmpBuf[OpNr_][P + 2]);
                    BmpBuf[OpNrX_][P + 2] = OpMatrixR[OpNr][RGB];
                    BmpBuf[OpNrX_][P + 1] = OpMatrixG[OpNr][RGB];
                    BmpBuf[OpNrX_][P + 0] = OpMatrixB[OpNr][RGB];
                    P += 4;
                }
            }
            break;
        }

        case 2: // 5x5 matrix convolution
        {
            if (OpMatrixIR[OpNr][28] == 1)
            {
                Convolution_Process_Gamma(BmpBuf[OpNr_], BmpBuf[OpNrX_], MinY, MaxY, PicW_, PicH_, P, OpMatrixIR[OpNr], OpMatrixIG[OpNr], OpMatrixIB[OpNr]);
            }
            else
            {
                Convolution_Process(BmpBuf[OpNr_], BmpBuf[OpNrX_], MinY, MaxY, PicW_, PicH_, P, OpMatrixIR[OpNr], OpMatrixIG[OpNr], OpMatrixIB[OpNr]);
            }
            break;
        }

        case 31: // Conversion from RGB table to single-number table
        {
            for (Y = MinY; Y < MaxY; Y++)
            {
                for (X = 0; X < PicW_; X++)
                {
                    BmpBufIX_[OpNr_][PP] = (BmpBuf[OpNr_][P + 0] << 16) + (BmpBuf[OpNr_][P + 1] << 8) + (BmpBuf[OpNr_][P + 2]);
                    PP++;
                    P += 4;
                }
                PP += PicBufIMargin;
                PP += PicBufIMargin;
            }
            break;
        }

        case 32: // Conversion from single-number table to RGB table
        {
            int BitPtr = OpNr_ - OpMatrixIR[OpNr][0];
            for (Y = MinY; Y < MaxY; Y++)
            {
                for (X = 0; X < PicW_; X++)
                {
                    BmpBuf[OpNrX_][P + 2] = (BmpBufIX_[BitPtr][PP] & 255);
                    BmpBuf[OpNrX_][P + 1] = (BmpBufIX_[BitPtr][PP] & 65280) >> 8;
                    BmpBuf[OpNrX_][P + 0] = (BmpBufIX_[BitPtr][PP] & 16711680) >> 16;
                    PP++;
                    P += 4;
                }
                PP += PicBufIMargin;
                PP += PicBufIMargin;
            }
            break;
        }


        case 3: // Dithering removal (dedithering)
        {
            int BmpSrc = OpMatrixIR[OpNr][0] + PipeI_;
            int BmpDst = OpMatrixIR[OpNr][1] + PipeI_;

            int ColorCount;
            uint Color1, Color2, Color3, Color4, ColorT, ColorTX;
            ColorT = NullColor;
            int XX, YY, I;
            int PicW_2 = (PicW_ + PicBufIMargin + PicBufIMargin);
            int YY1 = 0 - PicW_2 - PicW_2;
            int YY2 = PicW_2 + PicW_2;
            uint DM[5][5];
            vector<DitherMatrixElement> T = OpMatrixDither[OpNr];
            int TL = T.size();

            for (Y = MinY; Y < MaxY; Y++)
            {
                for (X = 0; X < PicW_; X++)
                {
                    // Color matrix generating
                    ColorCount = 0;
                    for (YY = YY1; YY <= YY2; YY += PicW_2)
                    {
                        for (XX = -2; XX <= 2; XX++)
                        {
                            DM[XX + 2][ColorCount] = BmpBufIX_[BmpSrc][PP + XX + YY];
                        }
                        ColorCount++;
                    }

                    // The deafult destination color is the same as source color
                    ColorTX = DM[2][2];

                    // Searching matching color layout pattern, the loop braks after finding matching pattern
                    for (I = 0; I < TL; I++)
                    {
                        ColorCount = T[I].Colors;
                        Color1 = NullColor;
                        Color2 = NullColor;
                        Color3 = NullColor;
                        Color4 = NullColor;

                        // Searching for dedither matrix matching
                        for (int YY = 0; YY < 5; YY++)
                        {
                            for (int XX = 0; XX < 5; XX++)
                            {
                                if (T[I].T[XX][YY] > 0)
                                {
                                    ColorT = DM[XX][YY];

                                    if (T[I].T[XX][YY] == 1)
                                    {
                                        if (Color1 == NullColor)
                                        {
                                            Color1 = ColorT;
                                        }
                                        if (Color1 != ColorT)
                                        {
                                            ColorCount = 0;
                                            YY = 5;
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        if (T[I].T[XX][YY] == 2)
                                        {
                                            if (Color2 == NullColor)
                                            {
                                                Color2 = ColorT;
                                            }
                                            if (Color2 != ColorT)
                                            {
                                                ColorCount = 0;
                                                YY = 5;
                                                break;
                                            }
                                        }
                                        else
                                        {
                                            if (T[I].T[XX][YY] == 3)
                                            {
                                                if (Color3 == NullColor)
                                                {
                                                    Color3 = ColorT;
                                                }
                                                if (Color3 != ColorT)
                                                {
                                                    ColorCount = 0;
                                                    YY = 5;
                                                    break;
                                                }
                                            }
                                            else
                                            {
                                                if (T[I].T[XX][YY] == 4)
                                                {
                                                    if (Color4 == NullColor)
                                                    {
                                                        Color4 = ColorT;
                                                    }
                                                    if (Color4 != ColorT)
                                                    {
                                                        ColorCount = 0;
                                                        YY = 5;
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        // If matching pattern found, computing destination color
                        if (ColorCount != 0)
                        {
                            if (ColorCount == 2)
                            {
                                if ((Color1 != Color2))
                                {
                                    uint T1 = T[I].Color1;
                                    uint T2 = T[I].Color2;
                                    uint XColor1 = ColorProp(((Color1      ) & 255), ((Color2      ) & 255), T1, T2);
                                    uint XColor2 = ColorProp(((Color1 >>  8) & 255), ((Color2 >>  8) & 255), T1, T2);
                                    uint XColor3 = ColorProp(((Color1 >> 16) & 255), ((Color2 >> 16) & 255), T1, T2);
                                    ColorTX = (XColor1) + (XColor2 << 8) + (XColor3 << 16);
                                    break;
                                }
                            }
                            else
                            {
                                if (ColorCount == 3)
                                {
                                    if ((Color1 != Color2) && (Color1 != Color3) && (Color2 != Color3))
                                    {
                                        uint T1 = T[I].Color1;
                                        uint T2 = T[I].Color2;
                                        uint T3 = T[I].Color3;
                                        uint XColor1 = ColorProp(((Color1      ) & 255), ((Color2      ) & 255), ((Color3      ) & 255), T1, T2, T3);
                                        uint XColor2 = ColorProp(((Color1 >>  8) & 255), ((Color2 >>  8) & 255), ((Color3 >>  8) & 255), T1, T2, T3);
                                        uint XColor3 = ColorProp(((Color1 >> 16) & 255), ((Color2 >> 16) & 255), ((Color3 >> 16) & 255), T1, T2, T3);
                                        ColorTX = (XColor1) + (XColor2 << 8) + (XColor3 << 16);
                                        break;
                                    }
                                }
                                else
                                {
                                    if (ColorCount == 4)
                                    {
                                        if ((Color1 != Color2) && (Color1 != Color3) && (Color1 != Color4) && (Color2 != Color3) && (Color2 != Color4) && (Color3 != Color4))
                                        {
                                            uint T1 = T[I].Color1;
                                            uint T2 = T[I].Color2;
                                            uint T3 = T[I].Color3;
                                            uint T4 = T[I].Color4;
                                            uint XColor1 = ColorProp(((Color1      ) & 255), ((Color2      ) & 255), ((Color3      ) & 255), ((Color4      ) & 255), T1, T2, T3, T4);
                                            uint XColor2 = ColorProp(((Color1 >>  8) & 255), ((Color2 >>  8) & 255), ((Color3 >>  8) & 255), ((Color4 >>  8) & 255), T1, T2, T3, T4);
                                            uint XColor3 = ColorProp(((Color1 >> 16) & 255), ((Color2 >> 16) & 255), ((Color3 >> 16) & 255), ((Color4 >> 16) & 255), T1, T2, T3, T4);
                                            ColorTX = (XColor1) + (XColor2 << 8) + (XColor3 << 16);
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }

                    // Setting destination color
                    BmpBufIX_[BmpDst][PP] = ColorTX;

                    PP++;
                }
                PP += PicBufIMargin;
                PP += PicBufIMargin;
            }
            break;
        }

        case 4: // Image resize
        {
            int FactorW1 = OpMatrix[OpNr][1];
            int FactorW2 = OpMatrix[OpNr][2];
            int FactorH1 = OpMatrix[OpNr][3];
            int FactorH2 = OpMatrix[OpNr][4];

            uchar * BmpBuf_ = BmpBuf[OpNr_];
            uchar * BmpBufX_ = BmpBuf[OpNrX_];

            switch (OpMatrix[OpNr][0])
            {
                case 0: // Without interpolation (nearest neighbour)
                    {
                        for (Y = MinY; Y < MaxY; Y++)
                        {
                            for (X = 0; X < PicW_X; X++)
                            {
                                int XX = (X * FactorW2) / FactorW1;
                                int YY = (Y * FactorH2) / FactorH1;
                                int PicP = ((YY * PicW_) + XX) << 2;

                                BmpBufX_[P + 2] = BmpBuf_[(PicP) + 2];
                                BmpBufX_[P + 1] = BmpBuf_[(PicP) + 1];
                                BmpBufX_[P + 0] = BmpBuf_[(PicP) + 0];
                                P += 4;
                            }
                        }
                    }
                    break;
                case 1: // Fast interpolation
                    {
                        int R, G, B, PicP;
                        int R11, G11, B11, R12, G12, B12, R21, G21, B21, R22, G22, B22;

                        // Accuracy = 64; - it must be 2^n
                        int AccuracyV = 32; // Accuracy / 2
                        int AccuracyB = 6;  // Log(Accuracy) / Log(2)
                        int AccuracyM = 63; // Accuracy - 1

                        int FactorW1X = FactorW1 << 1;
                        int FactorH1X = FactorH1 << 1;
                        int FactorW2X = FactorW2 << AccuracyB;
                        int FactorH2X = FactorH2 << AccuracyB;

                        int XOffset = (FactorW2X / FactorW1X) - AccuracyV;
                        int YOffset = (FactorH2X / FactorH1X) - AccuracyV;

                        for (Y = MinY; Y < MaxY; Y++)
                        {
                            for (X = 0; X < PicW_X; X++)
                            {
                                int XX = ((X * FactorW2X) / FactorW1) + XOffset;
                                int YY = ((Y * FactorH2X) / FactorH1) + YOffset;

                                int XX1 = Range(XX >> AccuracyB, 0, PicW_ - 1);
                                int YY1 = Range(YY >> AccuracyB, 0, PicH_ - 1);
                                int XX2 = Range((XX >> AccuracyB) + (((XX & AccuracyM) > 0) ? 1 : 0), 0, PicW_ - 1);
                                int YY2 = Range((YY >> AccuracyB) + (((YY & AccuracyM) > 0) ? 1 : 0), 0, PicH_ - 1);

                                int XDist1 = XX - (XX1 << AccuracyB);
                                int YDist1 = YY - (YY1 << AccuracyB);
                                int XDist2 = (XX2 << AccuracyB) - XX;
                                int YDist2 = (YY2 << AccuracyB) - YY;


                                PicP = ((YY1 * PicW_) + XX1) << 2;
                                R11 = BmpBuf_[PicP + 2];
                                G11 = BmpBuf_[PicP + 1];
                                B11 = BmpBuf_[PicP + 0];

                                PicP = ((YY2 * PicW_) + XX1) << 2;
                                R12 = BmpBuf_[PicP + 2];
                                G12 = BmpBuf_[PicP + 1];
                                B12 = BmpBuf_[PicP + 0];

                                PicP = ((YY1 * PicW_) + XX2) << 2;
                                R21 = BmpBuf_[PicP + 2];
                                G21 = BmpBuf_[PicP + 1];
                                B21 = BmpBuf_[PicP + 0];

                                PicP = ((YY2 * PicW_) + XX2) << 2;
                                R22 = BmpBuf_[PicP + 2];
                                G22 = BmpBuf_[PicP + 1];
                                B22 = BmpBuf_[PicP + 0];


                                if ((XDist1 + XDist2) == 0)
                                {
                                    XDist1 = 1;
                                    XDist2 = 1;
                                }
                                if ((YDist1 + YDist2) == 0)
                                {
                                    YDist1 = 1;
                                    YDist2 = 1;
                                }

                                int DistTotal = ((XDist1 + XDist2) * (YDist1 + YDist2));

                                R11 = ((R11 * XDist2) + (R21 * XDist1));
                                R12 = ((R12 * XDist2) + (R22 * XDist1));
                                R = ((R11 * YDist2 + R12 * YDist1) / DistTotal);

                                G11 = ((G11 * XDist2) + (G21 * XDist1));
                                G12 = ((G12 * XDist2) + (G22 * XDist1));
                                G = ((G11 * YDist2 + G12 * YDist1) / DistTotal);

                                B11 = ((B11 * XDist2) + (B21 * XDist1));
                                B12 = ((B12 * XDist2) + (B22 * XDist1));
                                B = ((B11 * YDist2 + B12 * YDist1) / DistTotal);

                                BmpBufX_[P + 2] = R;
                                BmpBufX_[P + 1] = G;
                                BmpBufX_[P + 0] = B;
                                P += 4;
                            }
                        }
                    }
                    break;
                case 2: // Accurate interpolation
                    {
                        int R, G, B;
                        int R11, G11, B11, R12, G12, B12, R21, G21, B21, R22, G22, B22;
                        int T11, T12, T21, T22;


                        int XFactor = (FactorW2 / (FactorW1 << 1));
                        int YFactor = (FactorH2 / (FactorH1 << 1));

                        int FactorW1X = FactorW1 << 1;
                        int FactorH1X = FactorH1 << 1;
                        int FactorW2X = FactorW2 << InterpolationAccuracyB;
                        int FactorH2X = FactorH2 << InterpolationAccuracyB;

                        int XOffset = (FactorW2X / FactorW1X) - InterpolationAccuracyV;
                        int YOffset = (FactorH2X / FactorH1X) - InterpolationAccuracyV;

                        for (Y = MinY; Y < MaxY; Y++)
                        {
                            for (X = 0; X < PicW_X; X++)
                            {
                                int XX = ((X * FactorW2X) / FactorW1) + XOffset;
                                int YY = ((Y * FactorH2X) / FactorH1) + YOffset;

                                int XX1 = Range(XX >> InterpolationAccuracyB, 0, PicW_ - 1);
                                int YY1 = Range(YY >> InterpolationAccuracyB, 0, PicH_ - 1);
                                int XX2 = Range((XX >> InterpolationAccuracyB) + (((XX & InterpolationAccuracyM) > 0) ? 1 : 0), 0, PicW_ - 1);
                                int YY2 = Range((YY >> InterpolationAccuracyB) + (((YY & InterpolationAccuracyM) > 0) ? 1 : 0), 0, PicH_ - 1);

                                int XDist1 = XX - (XX1 << InterpolationAccuracyB);
                                int YDist1 = YY - (YY1 << InterpolationAccuracyB);
                                int XDist2 = (XX2 << InterpolationAccuracyB) - XX;
                                int YDist2 = (YY2 << InterpolationAccuracyB) - YY;

                                GetColor(BmpBuf_, PicW_, PicH_, XX1, YY1, XFactor, YFactor, R11, G11, B11, T11);
                                GetColor(BmpBuf_, PicW_, PicH_, XX1, YY2, XFactor, YFactor, R12, G12, B12, T12);
                                GetColor(BmpBuf_, PicW_, PicH_, XX2, YY1, XFactor, YFactor, R21, G21, B21, T21);
                                GetColor(BmpBuf_, PicW_, PicH_, XX2, YY2, XFactor, YFactor, R22, G22, B22, T22);

                                if ((XDist1 + XDist2) == 0)
                                {
                                    XDist1 = 1;
                                    XDist2 = 1;
                                }
                                if ((YDist1 + YDist2) == 0)
                                {
                                    YDist1 = 1;
                                    YDist2 = 1;
                                }

                                int DistTotal = ((XDist1 + XDist2) * (YDist1 + YDist2));

                                R11 = ((R11 * XDist2 / T11) + (R21 * XDist1 / T21));
                                R12 = ((R12 * XDist2 / T12) + (R22 * XDist1 / T22));
                                R = ((R11 * YDist2 + R12 * YDist1) / DistTotal);

                                G11 = ((G11 * XDist2 / T11) + (G21 * XDist1 / T21));
                                G12 = ((G12 * XDist2 / T12) + (G22 * XDist1 / T22));
                                G = ((G11 * YDist2 + G12 * YDist1) / DistTotal);

                                B11 = ((B11 * XDist2 / T11) + (B21 * XDist1 / T21));
                                B12 = ((B12 * XDist2 / T12) + (B22 * XDist1 / T22));
                                B = ((B11 * YDist2 + B12 * YDist1) / DistTotal);

                                BmpBufX_[P + 2] = R;
                                BmpBufX_[P + 1] = G;
                                BmpBufX_[P + 0] = B;
                                P += 4;
                            }
                        }
                    }
                    break;
                case 3: // Scale2x
                    {
                        bool NoChannels = (OpMatrix[OpNr][5] == 0);
                        int L = PicW_X << 2;
                        int XW, XE, YN, YS;
                        int PicW_1 = PicW_ - 1;
                        int PicH_1 = PicH_ - 1;
                        int _P__R, _P__G, _P__B;
                        int _N__R, _N__G, _N__B, _N__X;
                        int _S__R, _S__G, _S__B, _S__X;
                        int _E__R, _E__G, _E__B, _E__X;
                        int _W__R, _W__G, _W__B, _W__X;
                        int PicP;
                        int _NER, _NWR, _SER, _SWR;
                        int _NEG, _NWG, _SEG, _SWG;
                        int _NEB, _NWB, _SEB, _SWB;

                        for (Y = MinY; Y < MaxY; Y++)
                        {
                            YN = Max(Y - 1, 0);
                            YS = Min(Y + 1, PicH_1);
                            for (X = 0; X < PicW_; X++)
                            {
                                XW = Max(X - 1, 0);
                                XE = Min(X + 1, PicW_1);

                                PicP = ((Y * PicW_) + X) << 2;
                                _P__R = BmpBuf_[PicP + 2];
                                _P__G = BmpBuf_[PicP + 1];
                                _P__B = BmpBuf_[PicP + 0];

                                PicP = ((YN * PicW_) + X) << 2;
                                _N__R = BmpBuf_[PicP + 2];
                                _N__G = BmpBuf_[PicP + 1];
                                _N__B = BmpBuf_[PicP + 0];

                                PicP = ((YS * PicW_) + X) << 2;
                                _S__R = BmpBuf_[PicP + 2];
                                _S__G = BmpBuf_[PicP + 1];
                                _S__B = BmpBuf_[PicP + 0];

                                PicP = ((Y * PicW_) + XE) << 2;
                                _E__R = BmpBuf_[PicP + 2];
                                _E__G = BmpBuf_[PicP + 1];
                                _E__B = BmpBuf_[PicP + 0];

                                PicP = ((Y * PicW_) + XW) << 2;
                                _W__R = BmpBuf_[PicP + 2];
                                _W__G = BmpBuf_[PicP + 1];
                                _W__B = BmpBuf_[PicP + 0];


                                _NWR = _P__R;
                                _NER = _P__R;
                                _SWR = _P__R;
                                _SER = _P__R;

                                _NWG = _P__G;
                                _NEG = _P__G;
                                _SWG = _P__G;
                                _SEG = _P__G;

                                _NWB = _P__B;
                                _NEB = _P__B;
                                _SWB = _P__B;
                                _SEB = _P__B;

                                if (NoChannels)
                                {
                                    _N__X = (_N__R << 16) + (_N__G << 8) + (_N__B);
                                    _S__X = (_S__R << 16) + (_S__G << 8) + (_S__B);
                                    _E__X = (_E__R << 16) + (_E__G << 8) + (_E__B);
                                    _W__X = (_W__R << 16) + (_W__G << 8) + (_W__B);

                                    if ((_N__X == _W__X) && (_N__X != _E__X) && (_N__X != _S__X)) { _NWR = _N__R; _NWG = _N__G; _NWB = _N__B; }
                                    if ((_N__X == _E__X) && (_N__X != _W__X) && (_N__X != _S__X)) { _NER = _N__R; _NEG = _N__G; _NEB = _N__B; }
                                    if ((_S__X == _W__X) && (_S__X != _E__X) && (_S__X != _N__X)) { _SWR = _S__R; _SWG = _S__G; _SWB = _S__B; }
                                    if ((_S__X == _E__X) && (_S__X != _W__X) && (_S__X != _N__X)) { _SER = _S__R; _SEG = _S__G; _SEB = _S__B; }
                                }
                                else
                                {
                                    if ((_N__R == _W__R) && (_N__R != _E__R) && (_N__R != _S__R)) { _NWR = _N__R; }
                                    if ((_N__R == _E__R) && (_N__R != _W__R) && (_N__R != _S__R)) { _NER = _N__R; }
                                    if ((_S__R == _W__R) && (_S__R != _E__R) && (_S__R != _N__R)) { _SWR = _S__R; }
                                    if ((_S__R == _E__R) && (_S__R != _W__R) && (_S__R != _N__R)) { _SER = _S__R; }

                                    if ((_N__G == _W__G) && (_N__G != _E__G) && (_N__G != _S__G)) { _NWG = _N__G; }
                                    if ((_N__G == _E__G) && (_N__G != _W__G) && (_N__G != _S__G)) { _NEG = _N__G; }
                                    if ((_S__G == _W__G) && (_S__G != _E__G) && (_S__G != _N__G)) { _SWG = _S__G; }
                                    if ((_S__G == _E__G) && (_S__G != _W__G) && (_S__G != _N__G)) { _SEG = _S__G; }

                                    if ((_N__B == _W__B) && (_N__B != _E__B) && (_N__B != _S__B)) { _NWB = _N__B; }
                                    if ((_N__B == _E__B) && (_N__B != _W__B) && (_N__B != _S__B)) { _NEB = _N__B; }
                                    if ((_S__B == _W__B) && (_S__B != _E__B) && (_S__B != _N__B)) { _SWB = _S__B; }
                                    if ((_S__B == _E__B) && (_S__B != _W__B) && (_S__B != _N__B)) { _SEB = _S__B; }
                                }

                                BmpBufX_[P + 2] = _NWR;
                                BmpBufX_[P + 1] = _NWG;
                                BmpBufX_[P + 0] = _NWB;
                                BmpBufX_[L + P + 2] = _SWR;
                                BmpBufX_[L + P + 1] = _SWG;
                                BmpBufX_[L + P + 0] = _SWB;
                                P += 4;

                                BmpBufX_[P + 2] = _NER;
                                BmpBufX_[P + 1] = _NEG;
                                BmpBufX_[P + 0] = _NEB;
                                BmpBufX_[L + P + 2] = _SER;
                                BmpBufX_[L + P + 1] = _SEG;
                                BmpBufX_[L + P + 0] = _SEB;
                                P += 4;
                            }
                            P += L;
                        }
                    }
                    break;
                case 4: // Scale3x
                    {
                        bool NoChannels = (OpMatrix[OpNr][5] == 0);
                        int L = PicW_X << 2;
                        int LL = L << 1;
                        int XW, XE, YN, YS;
                        int PicW_1 = PicW_ - 1;
                        int PicH_1 = PicH_ - 1;
                        int _P__R, _P__G, _P__B;
                        int _N__R, _N__G, _N__B, _N__X;
                        int _S__R, _S__G, _S__B, _S__X;
                        int _E__R, _E__G, _E__B, _E__X;
                        int _W__R, _W__G, _W__B, _W__X;
                        int _NE_R, _NE_G, _NE_B, _NE_X;
                        int _SE_R, _SE_G, _SE_B, _SE_X;
                        int _NW_R, _NW_G, _NW_B, _NW_X;
                        int _SW_R, _SW_G, _SW_B, _SW_X;
                        int PicP;
                        int _NER, _NWR, _SER, _SWR, _N_R, _S_R, _E_R, _W_R, _P_R;
                        int _NEG, _NWG, _SEG, _SWG, _N_G, _S_G, _E_G, _W_G, _P_G;
                        int _NEB, _NWB, _SEB, _SWB, _N_B, _S_B, _E_B, _W_B, _P_B;
                        int _P_X;
                        bool X_NER, X_NWR, X_SER, X_SWR;
                        bool X_NEG, X_NWG, X_SEG, X_SWG;
                        bool X_NEB, X_NWB, X_SEB, X_SWB;
                        bool X_NEX, X_NWX, X_SEX, X_SWX;
                        for (Y = MinY; Y < MaxY; Y++)
                        {
                            YN = Max(Y - 1, 0);
                            YS = Min(Y + 1, PicH_1);
                            for (X = 0; X < PicW_; X++)
                            {
                                XW = Max(X - 1, 0);
                                XE = Min(X + 1, PicW_1);

                                PicP = ((Y * PicW_) + X) << 2;
                                _P__R = BmpBuf_[PicP + 2];
                                _P__G = BmpBuf_[PicP + 1];
                                _P__B = BmpBuf_[PicP + 0];

                                PicP = ((YN * PicW_) + X) << 2;
                                _N__R = BmpBuf_[PicP + 2];
                                _N__G = BmpBuf_[PicP + 1];
                                _N__B = BmpBuf_[PicP + 0];

                                PicP = ((YS * PicW_) + X) << 2;
                                _S__R = BmpBuf_[PicP + 2];
                                _S__G = BmpBuf_[PicP + 1];
                                _S__B = BmpBuf_[PicP + 0];

                                PicP = ((Y * PicW_) + XE) << 2;
                                _E__R = BmpBuf_[PicP + 2];
                                _E__G = BmpBuf_[PicP + 1];
                                _E__B = BmpBuf_[PicP + 0];

                                PicP = ((Y * PicW_) + XW) << 2;
                                _W__R = BmpBuf_[PicP + 2];
                                _W__G = BmpBuf_[PicP + 1];
                                _W__B = BmpBuf_[PicP + 0];

                                PicP = ((YN * PicW_) + XE) << 2;
                                _NE_R = BmpBuf_[PicP + 2];
                                _NE_G = BmpBuf_[PicP + 1];
                                _NE_B = BmpBuf_[PicP + 0];

                                PicP = ((YS * PicW_) + XE) << 2;
                                _SE_R = BmpBuf_[PicP + 2];
                                _SE_G = BmpBuf_[PicP + 1];
                                _SE_B = BmpBuf_[PicP + 0];

                                PicP = ((YN * PicW_) + XW) << 2;
                                _NW_R = BmpBuf_[PicP + 2];
                                _NW_G = BmpBuf_[PicP + 1];
                                _NW_B = BmpBuf_[PicP + 0];

                                PicP = ((YS * PicW_) + XW) << 2;
                                _SW_R = BmpBuf_[PicP + 2];
                                _SW_G = BmpBuf_[PicP + 1];
                                _SW_B = BmpBuf_[PicP + 0];

                                _P_R = _P__R;
                                _N_R = _P__R;
                                _S_R = _P__R;
                                _E_R = _P__R;
                                _W_R = _P__R;
                                _NWR = _P__R;
                                _NER = _P__R;
                                _SWR = _P__R;
                                _SER = _P__R;

                                _P_G = _P__G;
                                _N_G = _P__G;
                                _S_G = _P__G;
                                _E_G = _P__G;
                                _W_G = _P__G;
                                _NWG = _P__G;
                                _NEG = _P__G;
                                _SWG = _P__G;
                                _SEG = _P__G;

                                _P_B = _P__B;
                                _N_B = _P__B;
                                _S_B = _P__B;
                                _E_B = _P__B;
                                _W_B = _P__B;
                                _NWB = _P__B;
                                _NEB = _P__B;
                                _SWB = _P__B;
                                _SEB = _P__B;

                                if (NoChannels)
                                {
                                    _N__X = (_N__R << 16) + (_N__G << 8) + (_N__B);
                                    _S__X = (_S__R << 16) + (_S__G << 8) + (_S__B);
                                    _E__X = (_E__R << 16) + (_E__G << 8) + (_E__B);
                                    _W__X = (_W__R << 16) + (_W__G << 8) + (_W__B);

                                    if ((_N__X == _W__X) && (_N__X != _E__X) && (_N__X != _S__X)) { _NWR = _N__R; _NWG = _N__G; _NWB = _N__B; X_NWX = true; } else { X_NWX = false; }
                                    if ((_N__X == _E__X) && (_N__X != _W__X) && (_N__X != _S__X)) { _NER = _N__R; _NEG = _N__G; _NEB = _N__B; X_NEX = true; } else { X_NEX = false; }
                                    if ((_S__X == _W__X) && (_S__X != _E__X) && (_S__X != _N__X)) { _SWR = _S__R; _SWG = _S__G; _SWB = _S__B; X_SWX = true; } else { X_SWX = false; }
                                    if ((_S__X == _E__X) && (_S__X != _W__X) && (_S__X != _N__X)) { _SER = _S__R; _SEG = _S__G; _SEB = _S__B; X_SEX = true; } else { X_SEX = false; }

                                    if (X_NWX || X_NEX || X_SWX || X_SEX)
                                    {
                                        _P_X = (_P_R << 16) + (_P_G << 8) + (_P_B);
                                        _NE_X = (_NE_R << 16) + (_NE_G << 8) + (_NE_B);
                                        _SE_X = (_SE_R << 16) + (_SE_G << 8) + (_SE_B);
                                        _NW_X = (_NW_R << 16) + (_NW_G << 8) + (_NW_B);
                                        _SW_X = (_SW_R << 16) + (_SW_G << 8) + (_SW_B);

                                        if ((X_NWX && (_P_X != _NE_X)) || (X_NEX && (_P_X != _NW_X))) { _N_R = _N__R; _N_G = _N__G; _N_B = _N__B; }
                                        if ((X_NEX && (_P_X != _SE_X)) || (X_SEX && (_P_X != _NE_X))) { _E_R = _E__R; _E_G = _E__G; _E_B = _E__B; }
                                        if ((X_SWX && (_P_X != _NW_X)) || (X_NWX && (_P_X != _SW_X))) { _W_R = _W__R; _W_G = _W__G; _W_B = _W__B; }
                                        if ((X_SEX && (_P_X != _SW_X)) || (X_SWX && (_P_X != _SE_X))) { _S_R = _S__R; _S_G = _S__G; _S_B = _S__B; }
                                    }
                                }
                                else
                                {
                                    if ((_N__R == _W__R) && (_N__R != _E__R) && (_N__R != _S__R)) { _NWR = _N__R; X_NWR = true; } else { X_NWR = false; }
                                    if ((_N__R == _E__R) && (_N__R != _W__R) && (_N__R != _S__R)) { _NER = _N__R; X_NER = true; } else { X_NER = false; }
                                    if ((_S__R == _W__R) && (_S__R != _E__R) && (_S__R != _N__R)) { _SWR = _S__R; X_SWR = true; } else { X_SWR = false; }
                                    if ((_S__R == _E__R) && (_S__R != _W__R) && (_S__R != _N__R)) { _SER = _S__R; X_SER = true; } else { X_SER = false; }

                                    if ((_N__G == _W__G) && (_N__G != _E__G) && (_N__G != _S__G)) { _NWG = _N__G; X_NWG = true; } else { X_NWG = false; }
                                    if ((_N__G == _E__G) && (_N__G != _W__G) && (_N__G != _S__G)) { _NEG = _N__G; X_NEG = true; } else { X_NEG = false; }
                                    if ((_S__G == _W__G) && (_S__G != _E__G) && (_S__G != _N__G)) { _SWG = _S__G; X_SWG = true; } else { X_SWG = false; }
                                    if ((_S__G == _E__G) && (_S__G != _W__G) && (_S__G != _N__G)) { _SEG = _S__G; X_SEG = true; } else { X_SEG = false; }

                                    if ((_N__B == _W__B) && (_N__B != _E__B) && (_N__B != _S__B)) { _NWB = _N__B; X_NWB = true; } else { X_NWB = false; }
                                    if ((_N__B == _E__B) && (_N__B != _W__B) && (_N__B != _S__B)) { _NEB = _N__B; X_NEB = true; } else { X_NEB = false; }
                                    if ((_S__B == _W__B) && (_S__B != _E__B) && (_S__B != _N__B)) { _SWB = _S__B; X_SWB = true; } else { X_SWB = false; }
                                    if ((_S__B == _E__B) && (_S__B != _W__B) && (_S__B != _N__B)) { _SEB = _S__B; X_SEB = true; } else { X_SEB = false; }

                                    if (X_NWR || X_NER || X_SWR || X_SER)
                                    {
                                        if ((X_NWR && (_P_R != _NE_R)) || (X_NER && (_P_R != _NW_R))) { _N_R = _N__R; }
                                        if ((X_NER && (_P_R != _SE_R)) || (X_SER && (_P_R != _NE_R))) { _E_R = _E__R; }
                                        if ((X_SWR && (_P_R != _NW_R)) || (X_NWR && (_P_R != _SW_R))) { _W_R = _W__R; }
                                        if ((X_SER && (_P_R != _SW_R)) || (X_SWR && (_P_R != _SE_R))) { _S_R = _S__R; }
                                    }

                                    if (X_NWG || X_NEG || X_SWG || X_SER)
                                    {
                                        if ((X_NWG && (_P_G != _NE_G)) || (X_NEG && (_P_G != _NW_G))) { _N_G = _N__G; }
                                        if ((X_NEG && (_P_G != _SE_G)) || (X_SEG && (_P_G != _NE_G))) { _E_G = _E__G; }
                                        if ((X_SWG && (_P_G != _NW_G)) || (X_NWG && (_P_G != _SW_G))) { _W_G = _W__G; }
                                        if ((X_SEG && (_P_G != _SW_G)) || (X_SWG && (_P_G != _SE_G))) { _S_G = _S__G; }
                                    }

                                    if (X_NWB || X_NEB || X_SWB || X_SER)
                                    {
                                        if ((X_NWB && (_P_B != _NE_B)) || (X_NEB && (_P_B != _NW_B))) { _N_B = _N__B; }
                                        if ((X_NEB && (_P_B != _SE_B)) || (X_SEB && (_P_B != _NE_B))) { _E_B = _E__B; }
                                        if ((X_SWB && (_P_B != _NW_B)) || (X_NWB && (_P_B != _SW_B))) { _W_B = _W__B; }
                                        if ((X_SEB && (_P_B != _SW_B)) || (X_SWB && (_P_B != _SE_B))) { _S_B = _S__B; }
                                    }
                                }

                                BmpBufX_[P + 2] = _NWR;
                                BmpBufX_[P + 1] = _NWG;
                                BmpBufX_[P + 0] = _NWB;
                                BmpBufX_[L + P + 2] = _W_R;
                                BmpBufX_[L + P + 1] = _W_G;
                                BmpBufX_[L + P + 0] = _W_B;
                                BmpBufX_[LL + P + 2] = _SWR;
                                BmpBufX_[LL + P + 1] = _SWG;
                                BmpBufX_[LL + P + 0] = _SWB;
                                P += 4;

                                BmpBufX_[P + 2] = _N_R;
                                BmpBufX_[P + 1] = _N_G;
                                BmpBufX_[P + 0] = _N_B;
                                BmpBufX_[L + P + 2] = _P_R;
                                BmpBufX_[L + P + 1] = _P_G;
                                BmpBufX_[L + P + 0] = _P_B;
                                BmpBufX_[LL + P + 2] = _S_R;
                                BmpBufX_[LL + P + 1] = _S_G;
                                BmpBufX_[LL + P + 0] = _S_B;
                                P += 4;

                                BmpBufX_[P + 2] = _NER;
                                BmpBufX_[P + 1] = _NEG;
                                BmpBufX_[P + 0] = _NEB;
                                BmpBufX_[L + P + 2] = _E_R;
                                BmpBufX_[L + P + 1] = _E_G;
                                BmpBufX_[L + P + 0] = _E_B;
                                BmpBufX_[LL + P + 2] = _SER;
                                BmpBufX_[LL + P + 1] = _SEG;
                                BmpBufX_[LL + P + 0] = _SEB;
                                P += 4;
                            }
                            P += LL;
                        }
                    }
                    break;
                case 6: // HQ2x
                    {
                        bool NoChannels = (OpMatrix[OpNr][5] == 0);
                        if (NoChannels)
                        {
                            HQ2X_Process1(BmpBuf_, BmpBufX_, MinY, MaxY, PicW_, PicH_, P, PicW_X << 2);
                        }
                        else
                        {
                            HQ2X_Process2(BmpBuf_, BmpBufX_, MinY, MaxY, PicW_, PicH_, P, PicW_X << 2);
                        }
                    }
                    break;
                case 7: // HQ3x
                    {
                        bool NoChannels = (OpMatrix[OpNr][5] == 0);
                        if (NoChannels)
                        {
                            HQ3X_Process1(BmpBuf_, BmpBufX_, MinY, MaxY, PicW_, PicH_, P, PicW_X << 2);
                        }
                        else
                        {
                            HQ3X_Process2(BmpBuf_, BmpBufX_, MinY, MaxY, PicW_, PicH_, P, PicW_X << 2);
                        }
                    }
                    break;
                case 8: // HQ4x
                    {
                        bool NoChannels = (OpMatrix[OpNr][5] == 0);
                        if (NoChannels)
                        {
                            HQ4X_Process1(BmpBuf_, BmpBufX_, MinY, MaxY, PicW_, PicH_, P, PicW_X << 2);
                        }
                        else
                        {
                            HQ4X_Process2(BmpBuf_, BmpBufX_, MinY, MaxY, PicW_, PicH_, P, PicW_X << 2);
                        }
                    }
                    break;
                case 11: // LCD composite
                    {
                        int LcdLayout = OpMatrix[OpNr][6];
                        int _L2R, _L1R, _00R, _R1R, _R2R;
                        int _L2G, _L1G, _00G, _R1G, _R2G;
                        int _L2B, _L1B, _00B, _R1B, _R2B;
                        int ValR = 0;
                        int ValG = 0;
                        int ValB = 0;

                        int YY = (MinY * 3) + 1;
                        int XX = 0;
                        int PicW_4 = PicW_ << 2;
                        int PicW_4_2 = PicW_4 + PicW_4;
                        int PicW_X1 = PicW_X - 1;
                        int LineU1, LineU2, LineD1, LineD2;
                        int PicH1 = (PicH_ / 3) - 1;
                        int PicH2 = (PicH_ / 3) - 2;
                        bool LcdNoInvert = ((LcdLayout == 0) || (LcdLayout == 2));

                        // 0 - color
                        // 1 - luminance
                        int Mode = OpMatrix[OpNr][5];

                        int RWeight = (((int)OpMatrix[OpNr][8]) << 8) + ((int)OpMatrix[OpNr][9]);
                        int GWeight = (((int)OpMatrix[OpNr][10]) << 8) + ((int)OpMatrix[OpNr][11]);
                        int BWeight = (((int)OpMatrix[OpNr][12]) << 8) + ((int)OpMatrix[OpNr][13]);
                        int TWeight = 3 * (RWeight + GWeight + BWeight);
                        int TWeight3 = TWeight * 3;


                        for (Y = MinY; Y < MaxY; Y++)
                        {
                            LineU2 = 0;
                            LineU1 = 0;
                            LineD1 = 0;
                            LineD2 = 0;

                            if (Y > 0) { LineU1 = PicW_4; }
                            if (Y > 1) { LineU2 = PicW_4_2; }
                            if (Y < PicH1) { LineD1 = PicW_4; }
                            if (Y < PicH2) { LineD2 = PicW_4_2; }

                            XX = 0;
                            for (X = 0; X < PicW_X; X++)
                            {
                                int PicP = ((YY * PicW_) + XX) << 2;
                                if (LcdLayout < 2)
                                {
                                    if (X > 0)
                                    {
                                        _L2R = GammaLUT_I[BmpBuf_[(PicP) - 2]] + GammaLUT_I[BmpBuf_[(PicP) - 2 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) - 2 + LineD1]];
                                        _L2G = GammaLUT_I[BmpBuf_[(PicP) - 3]] + GammaLUT_I[BmpBuf_[(PicP) - 3 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) - 3 + LineD1]];
                                        _L2B = GammaLUT_I[BmpBuf_[(PicP) - 4]] + GammaLUT_I[BmpBuf_[(PicP) - 4 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) - 4 + LineD1]];
                                    }
                                    else
                                    {
                                        _L2R = GammaLUT_I[BmpBuf_[(PicP) + 2]] + GammaLUT_I[BmpBuf_[(PicP) + 2 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) + 2 + LineD1]];
                                        _L2G = GammaLUT_I[BmpBuf_[(PicP) + 1]] + GammaLUT_I[BmpBuf_[(PicP) + 1 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) + 1 + LineD1]];
                                        _L2B = GammaLUT_I[BmpBuf_[(PicP) + 0]] + GammaLUT_I[BmpBuf_[(PicP) + 0 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) + 0 + LineD1]];
                                    }

                                    _L1R = GammaLUT_I[BmpBuf_[(PicP) + 2]] + GammaLUT_I[BmpBuf_[(PicP) + 2 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) + 2 + LineD1]];
                                    _L1G = GammaLUT_I[BmpBuf_[(PicP) + 1]] + GammaLUT_I[BmpBuf_[(PicP) + 1 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) + 1 + LineD1]];
                                    _L1B = GammaLUT_I[BmpBuf_[(PicP) + 0]] + GammaLUT_I[BmpBuf_[(PicP) + 0 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) + 0 + LineD1]];

                                    _00R = GammaLUT_I[BmpBuf_[(PicP) + 6]] + GammaLUT_I[BmpBuf_[(PicP) + 6 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) + 6 + LineD1]];
                                    _00G = GammaLUT_I[BmpBuf_[(PicP) + 5]] + GammaLUT_I[BmpBuf_[(PicP) + 5 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) + 5 + LineD1]];
                                    _00B = GammaLUT_I[BmpBuf_[(PicP) + 4]] + GammaLUT_I[BmpBuf_[(PicP) + 4 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) + 4 + LineD1]];

                                    _R1R = GammaLUT_I[BmpBuf_[(PicP) +10]] + GammaLUT_I[BmpBuf_[(PicP) +10 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) +10 + LineD1]];
                                    _R1G = GammaLUT_I[BmpBuf_[(PicP) + 9]] + GammaLUT_I[BmpBuf_[(PicP) + 9 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) + 9 + LineD1]];
                                    _R1B = GammaLUT_I[BmpBuf_[(PicP) + 8]] + GammaLUT_I[BmpBuf_[(PicP) + 8 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) + 8 + LineD1]];

                                    if (X < (PicW_X1))
                                    {
                                        _R2R = GammaLUT_I[BmpBuf_[(PicP) +14]] + GammaLUT_I[BmpBuf_[(PicP) +14 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) +14 + LineD1]];
                                        _R2G = GammaLUT_I[BmpBuf_[(PicP) +13]] + GammaLUT_I[BmpBuf_[(PicP) +13 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) +13 + LineD1]];
                                        _R2B = GammaLUT_I[BmpBuf_[(PicP) +12]] + GammaLUT_I[BmpBuf_[(PicP) +12 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) +12 + LineD1]];
                                    }
                                    else
                                    {
                                        _R2R = GammaLUT_I[BmpBuf_[(PicP) +10]] + GammaLUT_I[BmpBuf_[(PicP) +10 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) +10 + LineD1]];
                                        _R2G = GammaLUT_I[BmpBuf_[(PicP) + 9]] + GammaLUT_I[BmpBuf_[(PicP) + 9 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) + 9 + LineD1]];
                                        _R2B = GammaLUT_I[BmpBuf_[(PicP) + 8]] + GammaLUT_I[BmpBuf_[(PicP) + 8 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) + 8 + LineD1]];
                                    }
                                }
                                else
                                {
                                    _L2R = GammaLUT_I[BmpBuf_[(PicP) + 2 - LineU2]] + GammaLUT_I[BmpBuf_[(PicP) + 6 - LineU2]] + GammaLUT_I[BmpBuf_[(PicP) +10 - LineU2]];
                                    _L2G = GammaLUT_I[BmpBuf_[(PicP) + 1 - LineU2]] + GammaLUT_I[BmpBuf_[(PicP) + 5 - LineU2]] + GammaLUT_I[BmpBuf_[(PicP) + 9 - LineU2]];
                                    _L2B = GammaLUT_I[BmpBuf_[(PicP) + 0 - LineU2]] + GammaLUT_I[BmpBuf_[(PicP) + 4 - LineU2]] + GammaLUT_I[BmpBuf_[(PicP) + 8 - LineU2]];

                                    _L1R = GammaLUT_I[BmpBuf_[(PicP) + 2 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) + 6 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) +10 - LineU1]];
                                    _L1G = GammaLUT_I[BmpBuf_[(PicP) + 1 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) + 5 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) + 9 - LineU1]];
                                    _L1B = GammaLUT_I[BmpBuf_[(PicP) + 0 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) + 4 - LineU1]] + GammaLUT_I[BmpBuf_[(PicP) + 8 - LineU1]];

                                    _00R = GammaLUT_I[BmpBuf_[(PicP) + 2         ]] + GammaLUT_I[BmpBuf_[(PicP) + 6         ]] + GammaLUT_I[BmpBuf_[(PicP) +10         ]];
                                    _00G = GammaLUT_I[BmpBuf_[(PicP) + 1         ]] + GammaLUT_I[BmpBuf_[(PicP) + 5         ]] + GammaLUT_I[BmpBuf_[(PicP) + 9         ]];
                                    _00B = GammaLUT_I[BmpBuf_[(PicP) + 0         ]] + GammaLUT_I[BmpBuf_[(PicP) + 4         ]] + GammaLUT_I[BmpBuf_[(PicP) + 8         ]];

                                    _R1R = GammaLUT_I[BmpBuf_[(PicP) + 2 + LineD1]] + GammaLUT_I[BmpBuf_[(PicP) + 6 + LineD1]] + GammaLUT_I[BmpBuf_[(PicP) +10 + LineD1]];
                                    _R1G = GammaLUT_I[BmpBuf_[(PicP) + 1 + LineD1]] + GammaLUT_I[BmpBuf_[(PicP) + 5 + LineD1]] + GammaLUT_I[BmpBuf_[(PicP) + 9 + LineD1]];
                                    _R1B = GammaLUT_I[BmpBuf_[(PicP) + 0 + LineD1]] + GammaLUT_I[BmpBuf_[(PicP) + 4 + LineD1]] + GammaLUT_I[BmpBuf_[(PicP) + 8 + LineD1]];

                                    _R2R = GammaLUT_I[BmpBuf_[(PicP) + 2 + LineD2]] + GammaLUT_I[BmpBuf_[(PicP) + 6 + LineD2]] + GammaLUT_I[BmpBuf_[(PicP) +10 + LineD2]];
                                    _R2G = GammaLUT_I[BmpBuf_[(PicP) + 1 + LineD2]] + GammaLUT_I[BmpBuf_[(PicP) + 5 + LineD2]] + GammaLUT_I[BmpBuf_[(PicP) + 9 + LineD2]];
                                    _R2B = GammaLUT_I[BmpBuf_[(PicP) + 0 + LineD2]] + GammaLUT_I[BmpBuf_[(PicP) + 4 + LineD2]] + GammaLUT_I[BmpBuf_[(PicP) + 8 + LineD2]];
                                }
                                switch (Mode)
                                {
                                    case 0: // Color without interpolation
                                        {
                                            if (LcdNoInvert)
                                            {
                                                ValR = _L1R / 3;
                                                ValG = _00G / 3;
                                                ValB = _R1B / 3;
                                            }
                                            else
                                            {
                                                ValR = _R1R / 3;
                                                ValG = _00G / 3;
                                                ValB = _L1B / 3;
                                            }
                                        }
                                        break;
                                    case 1: // Luminance without interpolation
                                        {
                                            if (LcdNoInvert)
                                            {
                                                ValR = ((_L1R * RWeight) + (_L1G * GWeight) + (_L1B * BWeight)) / TWeight;
                                                ValG = ((_00R * RWeight) + (_00G * GWeight) + (_00B * BWeight)) / TWeight;
                                                ValB = ((_R1R * RWeight) + (_R1G * GWeight) + (_R1B * BWeight)) / TWeight;
                                            }
                                            else
                                            {
                                                ValR = ((_R1R * RWeight) + (_R1G * GWeight) + (_R1B * BWeight)) / TWeight;
                                                ValG = ((_00R * RWeight) + (_00G * GWeight) + (_00B * BWeight)) / TWeight;
                                                ValB = ((_L1R * RWeight) + (_L1G * GWeight) + (_L1B * BWeight)) / TWeight;
                                            }
                                        }
                                        break;
                                    case 2: // Color with interpolation
                                        {
                                            if (LcdNoInvert)
                                            {
                                                ValR = (_L2R + _L1R + _00R) / 9;
                                                ValG = (_L1G + _00G + _R1G) / 9;
                                                ValB = (_00B + _R1B + _R2B) / 9;
                                            }
                                            else
                                            {
                                                ValR = (_00R + _R1R + _R2R) / 9;
                                                ValG = (_L1G + _00G + _R1G) / 9;
                                                ValB = (_L2B + _L1B + _00B) / 9;
                                            }
                                        }
                                        break;
                                    case 3: // Luminance with interpolation
                                        {
                                            if (LcdNoInvert)
                                            {
                                                ValR = ((_L2R * RWeight) + (_L2G * GWeight) + (_L2B * BWeight) + (_L1R * RWeight) + (_L1G * GWeight) + (_L1B * BWeight) + (_00R * RWeight) + (_00G * GWeight) + (_00B * BWeight)) / TWeight3;
                                                ValG = ((_L1R * RWeight) + (_L1G * GWeight) + (_L1B * BWeight) + (_00R * RWeight) + (_00G * GWeight) + (_00B * BWeight) + (_R1R * RWeight) + (_R1G * GWeight) + (_R1B * BWeight)) / TWeight3;
                                                ValB = ((_00R * RWeight) + (_00G * GWeight) + (_00B * BWeight) + (_R1R * RWeight) + (_R1G * GWeight) + (_R1B * BWeight) + (_R2R * RWeight) + (_R2G * GWeight) + (_R2B * BWeight)) / TWeight3;
                                            }
                                            else
                                            {
                                                ValR = ((_00R * RWeight) + (_00G * GWeight) + (_00B * BWeight) + (_R1R * RWeight) + (_R1G * GWeight) + (_R1B * BWeight) + (_R2R * RWeight) + (_R2G * GWeight) + (_R2B * BWeight)) / TWeight3;
                                                ValG = ((_L1R * RWeight) + (_L1G * GWeight) + (_L1B * BWeight) + (_00R * RWeight) + (_00G * GWeight) + (_00B * BWeight) + (_R1R * RWeight) + (_R1G * GWeight) + (_R1B * BWeight)) / TWeight3;
                                                ValB = ((_L2R * RWeight) + (_L2G * GWeight) + (_L2B * BWeight) + (_L1R * RWeight) + (_L1G * GWeight) + (_L1B * BWeight) + (_00R * RWeight) + (_00G * GWeight) + (_00B * BWeight)) / TWeight3;
                                            }
                                        }
                                }
                                BmpBufX_[P + 2] = GammaLUT_O[ValR];
                                BmpBufX_[P + 1] = GammaLUT_O[ValG];
                                BmpBufX_[P + 0] = GammaLUT_O[ValB];
                                P += 4;
                                XX += 3;
                            }
                            YY += 3;
                        }
                    }
                    break;
                case 12: // LCD decomposite
                    {
                        int LcdLayout = OpMatrix[OpNr][6];

                        // 0 - Color subpixels
                        // 1 - Gray subpixels
                        // 2 - Subpixel luminance
                        // 3 - Subpixel luminance with chrominance 1
                        // 4 - Subpixel luminance with chrominance 3
                        // 5 - Subpixel luminance with chrominance 5
                        // 6 - Subpixel luminance with chrominance 1+1
                        // 7 - Subpixel luminance with chrominance 3+1
                        // 8 - Subpixel luminance with chrominance 5+1
                        // 9 - Subpixel luminance with chrominance 3+3
                        // 10 - Subpixel luminance with chrominance 5+3
                        // 11 - Subpixel luminance with chrominance 5+5
                        int Mode = OpMatrix[OpNr][5] - 2;

                        bool ChromaBase1 = (Mode == 3) || (Mode == 6);
                        bool ChromaBase3 = (Mode == 4) || (Mode == 7) || (Mode == 9);
                        bool ChromaBase5 = (Mode == 5) || (Mode == 8) || (Mode == 10) || (Mode == 11);

                        bool ChromaVert1 = (Mode == 6) || (Mode == 7) || (Mode == 8);
                        bool ChromaVert3 = (Mode == 9) || (Mode == 10);
                        bool ChromaVert5 = (Mode == 11);

                        bool ChromaBase = (Mode > 2);
                        bool ChromaVert = (Mode > 5);

                        int ChromaDiv = 1;
                        if (ChromaBase1) { ChromaDiv = 1; }
                        if (ChromaBase3) { ChromaDiv = 3; }
                        if (ChromaBase5) { ChromaDiv = 5; }

                        if (ChromaVert1) { ChromaDiv += 2; }
                        if (ChromaVert3) { ChromaDiv += 6; }
                        if (ChromaVert5) { ChromaDiv += 10; }


                        int RWeight = (((int)OpMatrix[OpNr][8]) << 8) + ((int)OpMatrix[OpNr][9]);
                        int GWeight = (((int)OpMatrix[OpNr][10]) << 8) + ((int)OpMatrix[OpNr][11]);
                        int BWeight = (((int)OpMatrix[OpNr][12]) << 8) + ((int)OpMatrix[OpNr][13]);
                        int TWeight = RWeight + GWeight + BWeight;

                        int L1 = PicW_X << 2;
                        int L2 = L1 << 1;
                        int XW, XE, YN, YS;
                        int PicW_1 = PicW_ - 1;
                        int PicH_1 = PicH_ - 1;
                        int _P__R, _P__G, _P__B;
                        int _N__R, _N__G, _N__B;
                        int _S__R, _S__G, _S__B;
                        int _E__R, _E__G, _E__B;
                        int _W__R, _W__G, _W__B;
                        int _NE_R, _NE_G, _NE_B;
                        int _SE_R, _SE_G, _SE_B;
                        int _NW_R, _NW_G, _NW_B;
                        int _SW_R, _SW_G, _SW_B;
                        int PicP;
                        int _NER, _NWR, _SER, _SWR, _N_R, _S_R, _E_R, _W_R, _P_R;
                        int _NEG, _NWG, _SEG, _SWG, _N_G, _S_G, _E_G, _W_G, _P_G;
                        int _NEB, _NWB, _SEB, _SWB, _N_B, _S_B, _E_B, _W_B, _P_B;
                        for (Y = MinY; Y < MaxY; Y++)
                        {
                            YN = Max(Y - 1, 0);
                            YS = Min(Y + 1, PicH_1);
                            for (X = 0; X < PicW_; X++)
                            {
                                XW = Max(X - 1, 0);
                                XE = Min(X + 1, PicW_1);

                                switch (LcdLayout)
                                {
                                    case 0: // H-RGB
                                        {
                                            PicP = ((Y * PicW_) + X) << 2;
                                            _P__R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _P__G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _P__B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((YN * PicW_) + X) << 2;
                                            _N__R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _N__G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _N__B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((YS * PicW_) + X) << 2;
                                            _S__R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _S__G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _S__B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((Y * PicW_) + XE) << 2;
                                            _E__R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _E__G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _E__B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((Y * PicW_) + XW) << 2;
                                            _W__R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _W__G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _W__B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((YN * PicW_) + XE) << 2;
                                            _NE_R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _NE_G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _NE_B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((YS * PicW_) + XE) << 2;
                                            _SE_R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _SE_G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _SE_B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((YN * PicW_) + XW) << 2;
                                            _NW_R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _NW_G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _NW_B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((YS * PicW_) + XW) << 2;
                                            _SW_R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _SW_G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _SW_B = GammaLUT_I[BmpBuf_[PicP + 0]];
                                        }
                                        break;
                                    case 1: // H-BGR
                                        {
                                            PicP = ((Y * PicW_) + X) << 2;
                                            _P__R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _P__G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _P__B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((YN * PicW_) + X) << 2;
                                            _N__R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _N__G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _N__B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((YS * PicW_) + X) << 2;
                                            _S__R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _S__G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _S__B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((Y * PicW_) + XE) << 2;
                                            _W__R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _W__G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _W__B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((Y * PicW_) + XW) << 2;
                                            _E__R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _E__G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _E__B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((YN * PicW_) + XE) << 2;
                                            _NW_R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _NW_G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _NW_B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((YS * PicW_) + XE) << 2;
                                            _SW_R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _SW_G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _SW_B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((YN * PicW_) + XW) << 2;
                                            _NE_R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _NE_G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _NE_B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((YS * PicW_) + XW) << 2;
                                            _SE_R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _SE_G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _SE_B = GammaLUT_I[BmpBuf_[PicP + 0]];
                                        }
                                        break;
                                    case 2: // V-RGB
                                        {
                                            PicP = ((Y * PicW_) + X) << 2;
                                            _P__R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _P__G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _P__B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((YN * PicW_) + X) << 2;
                                            _W__R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _W__G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _W__B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((YS * PicW_) + X) << 2;
                                            _E__R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _E__G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _E__B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((Y * PicW_) + XE) << 2;
                                            _S__R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _S__G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _S__B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((Y * PicW_) + XW) << 2;
                                            _N__R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _N__G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _N__B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((YN * PicW_) + XE) << 2;
                                            _SW_R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _SW_G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _SW_B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((YS * PicW_) + XE) << 2;
                                            _SE_R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _SE_G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _SE_B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((YN * PicW_) + XW) << 2;
                                            _NW_R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _NW_G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _NW_B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((YS * PicW_) + XW) << 2;
                                            _NE_R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _NE_G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _NE_B = GammaLUT_I[BmpBuf_[PicP + 0]];
                                        }
                                        break;
                                    case 3: // V-BGR
                                        {
                                            PicP = ((Y * PicW_) + X) << 2;
                                            _P__R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _P__G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _P__B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((YN * PicW_) + X) << 2;
                                            _E__R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _E__G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _E__B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((YS * PicW_) + X) << 2;
                                            _W__R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _W__G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _W__B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((Y * PicW_) + XE) << 2;
                                            _S__R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _S__G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _S__B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((Y * PicW_) + XW) << 2;
                                            _N__R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _N__G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _N__B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((YN * PicW_) + XE) << 2;
                                            _SE_R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _SE_G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _SE_B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((YS * PicW_) + XE) << 2;
                                            _SW_R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _SW_G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _SW_B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((YN * PicW_) + XW) << 2;
                                            _NE_R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _NE_G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _NE_B = GammaLUT_I[BmpBuf_[PicP + 0]];

                                            PicP = ((YS * PicW_) + XW) << 2;
                                            _NW_R = GammaLUT_I[BmpBuf_[PicP + 2]];
                                            _NW_G = GammaLUT_I[BmpBuf_[PicP + 1]];
                                            _NW_B = GammaLUT_I[BmpBuf_[PicP + 0]];
                                        }
                                        break;
                                }


                                switch (Mode)
                                {
                                    case 0:
                                        {
                                            _W_R = _P__R;
                                            _W_G = 0;
                                            _W_B = 0;

                                            _P_R = 0;
                                            _P_G = _P__G;
                                            _P_B = 0;

                                            _E_R = 0;
                                            _E_G = 0;
                                            _E_B = _P__B;
                                        }
                                        break;
                                    case 1:
                                        {
                                            _W_R = _P__R;
                                            _W_G = _P__R;
                                            _W_B = _P__R;

                                            _P_R = _P__G;
                                            _P_G = _P__G;
                                            _P_B = _P__G;

                                            _E_R = _P__B;
                                            _E_G = _P__B;
                                            _E_B = _P__B;
                                        }
                                        break;
                                    case 2:
                                    case 3:
                                    case 4:
                                    case 5:
                                    case 6:
                                    case 7:
                                    case 8:
                                    case 9:
                                    case 10:
                                    case 11:
                                        {

                                            int LumaL3 = YUV_RGB_L(_W__R, _W__G, _W__B);
                                            int LumaL2 = YUV_RGB_L(_P__R, _W__G, _W__B);
                                            int LumaL1 = YUV_RGB_L(_P__R, _P__G, _W__B);
                                            int Luma00 = YUV_RGB_L(_P__R, _P__G, _P__B);
                                            int LumaR1 = YUV_RGB_L(_E__R, _P__G, _P__B);
                                            int LumaR2 = YUV_RGB_L(_E__R, _E__G, _P__B);
                                            int LumaR3 = YUV_RGB_L(_E__R, _E__G, _E__B);

                                            int ChromaRL3B = 0;
                                            int ChromaGL3B = 0;
                                            int ChromaBL3B = 0;
                                            int ChromaRL2B = 0;
                                            int ChromaGL2B = 0;
                                            int ChromaBL2B = 0;
                                            int ChromaRL1B = 0;
                                            int ChromaGL1B = 0;
                                            int ChromaBL1B = 0;
                                            int ChromaR00B = 0;
                                            int ChromaG00B = 0;
                                            int ChromaB00B = 0;
                                            int ChromaRR1B = 0;
                                            int ChromaGR1B = 0;
                                            int ChromaBR1B = 0;
                                            int ChromaRR2B = 0;
                                            int ChromaGR2B = 0;
                                            int ChromaBR2B = 0;
                                            int ChromaRR3B = 0;
                                            int ChromaGR3B = 0;
                                            int ChromaBR3B = 0;

                                            int ChromaRL3V = 0;
                                            int ChromaGL3V = 0;
                                            int ChromaBL3V = 0;
                                            int ChromaRL2V = 0;
                                            int ChromaGL2V = 0;
                                            int ChromaBL2V = 0;
                                            int ChromaRL1V = 0;
                                            int ChromaGL1V = 0;
                                            int ChromaBL1V = 0;
                                            int ChromaR00V = 0;
                                            int ChromaG00V = 0;
                                            int ChromaB00V = 0;
                                            int ChromaRR1V = 0;
                                            int ChromaGR1V = 0;
                                            int ChromaBR1V = 0;
                                            int ChromaRR2V = 0;
                                            int ChromaGR2V = 0;
                                            int ChromaBR2V = 0;
                                            int ChromaRR3V = 0;
                                            int ChromaGR3V = 0;
                                            int ChromaBR3V = 0;

                                            if (ChromaBase)
                                            {
                                                ChromaRL3B = YUV_RGB_R(LumaL3, _W__R);
                                                ChromaGL3B = YUV_RGB_G(LumaL3, _W__G);
                                                ChromaBL3B = YUV_RGB_B(LumaL3, _W__B);
                                                ChromaRL2B = YUV_RGB_R(LumaL2, _P__R);
                                                ChromaGL2B = YUV_RGB_G(LumaL2, _W__G);
                                                ChromaBL2B = YUV_RGB_B(LumaL2, _W__B);
                                                ChromaRL1B = YUV_RGB_R(LumaL1, _P__R);
                                                ChromaGL1B = YUV_RGB_G(LumaL1, _P__G);
                                                ChromaBL1B = YUV_RGB_B(LumaL1, _W__B);
                                                ChromaR00B = YUV_RGB_R(Luma00, _P__R);
                                                ChromaG00B = YUV_RGB_G(Luma00, _P__G);
                                                ChromaB00B = YUV_RGB_B(Luma00, _P__B);
                                                ChromaRR1B = YUV_RGB_R(LumaR1, _E__R);
                                                ChromaGR1B = YUV_RGB_G(LumaR1, _P__G);
                                                ChromaBR1B = YUV_RGB_B(LumaR1, _P__B);
                                                ChromaRR2B = YUV_RGB_R(LumaR2, _E__R);
                                                ChromaGR2B = YUV_RGB_G(LumaR2, _E__G);
                                                ChromaBR2B = YUV_RGB_B(LumaR2, _P__B);
                                                ChromaRR3B = YUV_RGB_R(LumaR3, _E__R);
                                                ChromaGR3B = YUV_RGB_G(LumaR3, _E__G);
                                                ChromaBR3B = YUV_RGB_B(LumaR3, _E__B);
                                            }

                                            if (ChromaVert)
                                            {
                                                int LumaL3N = YUV_RGB_L(_NW_R, _NW_G, _NW_B);
                                                int LumaL2N = YUV_RGB_L(_N__R, _NW_G, _NW_B);
                                                int LumaL1N = YUV_RGB_L(_N__R, _N__G, _NW_B);
                                                int Luma00N = YUV_RGB_L(_N__R, _N__G, _N__B);
                                                int LumaR1N = YUV_RGB_L(_NE_R, _N__G, _N__B);
                                                int LumaR2N = YUV_RGB_L(_NE_R, _NE_G, _N__B);
                                                int LumaR3N = YUV_RGB_L(_NE_R, _NE_G, _NE_B);

                                                int LumaL3S = YUV_RGB_L(_SW_R, _SW_G, _SW_B);
                                                int LumaL2S = YUV_RGB_L(_S__R, _SW_G, _SW_B);
                                                int LumaL1S = YUV_RGB_L(_S__R, _S__G, _SW_B);
                                                int Luma00S = YUV_RGB_L(_S__R, _S__G, _S__B);
                                                int LumaR1S = YUV_RGB_L(_SE_R, _S__G, _S__B);
                                                int LumaR2S = YUV_RGB_L(_SE_R, _SE_G, _S__B);
                                                int LumaR3S = YUV_RGB_L(_SE_R, _SE_G, _SE_B);

                                                ChromaRL3V = YUV_RGB_R(LumaL3N, _NW_R) + YUV_RGB_R(LumaL3S, _SW_R);
                                                ChromaGL3V = YUV_RGB_G(LumaL3N, _NW_G) + YUV_RGB_G(LumaL3S, _SW_G);
                                                ChromaBL3V = YUV_RGB_B(LumaL3N, _NW_B) + YUV_RGB_B(LumaL3S, _SW_B);
                                                ChromaRL2V = YUV_RGB_R(LumaL2N, _N__R) + YUV_RGB_R(LumaL2S, _S__R);
                                                ChromaGL2V = YUV_RGB_G(LumaL2N, _NW_G) + YUV_RGB_G(LumaL2S, _SW_G);
                                                ChromaBL2V = YUV_RGB_B(LumaL2N, _NW_B) + YUV_RGB_B(LumaL2S, _SW_B);
                                                ChromaRL1V = YUV_RGB_R(LumaL1N, _N__R) + YUV_RGB_R(LumaL1S, _S__R);
                                                ChromaGL1V = YUV_RGB_G(LumaL1N, _N__G) + YUV_RGB_G(LumaL1S, _S__G);
                                                ChromaBL1V = YUV_RGB_B(LumaL1N, _NW_B) + YUV_RGB_B(LumaL1S, _SW_B);
                                                ChromaR00V = YUV_RGB_R(Luma00N, _N__R) + YUV_RGB_R(Luma00S, _S__R);
                                                ChromaG00V = YUV_RGB_G(Luma00N, _N__G) + YUV_RGB_G(Luma00S, _S__G);
                                                ChromaB00V = YUV_RGB_B(Luma00N, _N__B) + YUV_RGB_B(Luma00S, _S__B);
                                                ChromaRR1V = YUV_RGB_R(LumaR1N, _NE_R) + YUV_RGB_R(LumaR1S, _SE_R);
                                                ChromaGR1V = YUV_RGB_G(LumaR1N, _N__G) + YUV_RGB_G(LumaR1S, _S__G);
                                                ChromaBR1V = YUV_RGB_B(LumaR1N, _N__B) + YUV_RGB_B(LumaR1S, _S__B);
                                                ChromaRR2V = YUV_RGB_R(LumaR2N, _NE_R) + YUV_RGB_R(LumaR2S, _SE_R);
                                                ChromaGR2V = YUV_RGB_G(LumaR2N, _NE_G) + YUV_RGB_G(LumaR2S, _SE_G);
                                                ChromaBR2V = YUV_RGB_B(LumaR2N, _N__B) + YUV_RGB_B(LumaR2S, _S__B);
                                                ChromaRR3V = YUV_RGB_R(LumaR3N, _NE_R) + YUV_RGB_R(LumaR3S, _SE_R);
                                                ChromaGR3V = YUV_RGB_G(LumaR3N, _NE_G) + YUV_RGB_G(LumaR3S, _SE_G);
                                                ChromaBR3V = YUV_RGB_B(LumaR3N, _NE_B) + YUV_RGB_B(LumaR3S, _SE_B);
                                            }

                                            int ChromaXRL1 = 0;
                                            int ChromaXGL1 = 0;
                                            int ChromaXBL1 = 0;
                                            int ChromaXR00 = 0;
                                            int ChromaXG00 = 0;
                                            int ChromaXB00 = 0;
                                            int ChromaXRR1 = 0;
                                            int ChromaXGR1 = 0;
                                            int ChromaXBR1 = 0;

                                            if (ChromaBase1)
                                            {
                                                ChromaXRL1 = ChromaRL1B;
                                                ChromaXGL1 = ChromaGL1B;
                                                ChromaXBL1 = ChromaBL1B;
                                                ChromaXR00 = ChromaR00B;
                                                ChromaXG00 = ChromaG00B;
                                                ChromaXB00 = ChromaB00B;
                                                ChromaXRR1 = ChromaRR1B;
                                                ChromaXGR1 = ChromaGR1B;
                                                ChromaXBR1 = ChromaBR1B;
                                            }

                                            if (ChromaBase3)
                                            {
                                                ChromaXRL1 = ChromaRL2B + ChromaRL1B + ChromaR00B;
                                                ChromaXGL1 = ChromaGL2B + ChromaGL1B + ChromaG00B;
                                                ChromaXBL1 = ChromaBL2B + ChromaBL1B + ChromaB00B;
                                                ChromaXR00 = ChromaRL1B + ChromaR00B + ChromaRR1B;
                                                ChromaXG00 = ChromaGL1B + ChromaG00B + ChromaGR1B;
                                                ChromaXB00 = ChromaBL1B + ChromaB00B + ChromaBR1B;
                                                ChromaXRR1 = ChromaR00B + ChromaRR1B + ChromaRR2B;
                                                ChromaXGR1 = ChromaG00B + ChromaGR1B + ChromaGR2B;
                                                ChromaXBR1 = ChromaB00B + ChromaBR1B + ChromaBR2B;
                                            }

                                            if (ChromaBase5)
                                            {
                                                ChromaXRL1 = ChromaRL3B + ChromaRL2B + ChromaRL1B + ChromaR00B + ChromaRR1B;
                                                ChromaXGL1 = ChromaGL3B + ChromaGL2B + ChromaGL1B + ChromaG00B + ChromaGR1B;
                                                ChromaXBL1 = ChromaBL3B + ChromaBL2B + ChromaBL1B + ChromaB00B + ChromaBR1B;
                                                ChromaXR00 = ChromaRL2B + ChromaRL1B + ChromaR00B + ChromaRR1B + ChromaRR2B;
                                                ChromaXG00 = ChromaGL2B + ChromaGL1B + ChromaG00B + ChromaGR1B + ChromaGR2B;
                                                ChromaXB00 = ChromaBL2B + ChromaBL1B + ChromaB00B + ChromaBR1B + ChromaBR2B;
                                                ChromaXRR1 = ChromaRL1B + ChromaR00B + ChromaRR1B + ChromaRR2B + ChromaRR3B;
                                                ChromaXGR1 = ChromaGL1B + ChromaG00B + ChromaGR1B + ChromaGR2B + ChromaGR3B;
                                                ChromaXBR1 = ChromaBL1B + ChromaB00B + ChromaBR1B + ChromaBR2B + ChromaBR3B;
                                            }

                                            if (ChromaVert1)
                                            {
                                                ChromaXRL1 = ChromaXRL1 + ChromaRL1V;
                                                ChromaXGL1 = ChromaXGL1 + ChromaGL1V;
                                                ChromaXBL1 = ChromaXBL1 + ChromaBL1V;
                                                ChromaXR00 = ChromaXR00 + ChromaR00V;
                                                ChromaXG00 = ChromaXG00 + ChromaG00V;
                                                ChromaXB00 = ChromaXB00 + ChromaB00V;
                                                ChromaXRR1 = ChromaXRR1 + ChromaRR1V;
                                                ChromaXGR1 = ChromaXGR1 + ChromaGR1V;
                                                ChromaXBR1 = ChromaXBR1 + ChromaBR1V;
                                            }

                                            if (ChromaVert3)
                                            {
                                                ChromaXRL1 = ChromaXRL1 + ChromaRL2V + ChromaRL1V + ChromaR00V;
                                                ChromaXGL1 = ChromaXGL1 + ChromaGL2V + ChromaGL1V + ChromaG00V;
                                                ChromaXBL1 = ChromaXBL1 + ChromaBL2V + ChromaBL1V + ChromaB00V;
                                                ChromaXR00 = ChromaXR00 + ChromaRL1V + ChromaR00V + ChromaRR1V;
                                                ChromaXG00 = ChromaXG00 + ChromaGL1V + ChromaG00V + ChromaGR1V;
                                                ChromaXB00 = ChromaXB00 + ChromaBL1V + ChromaB00V + ChromaBR1V;
                                                ChromaXRR1 = ChromaXRR1 + ChromaR00V + ChromaRR1V + ChromaRR2V;
                                                ChromaXGR1 = ChromaXGR1 + ChromaG00V + ChromaGR1V + ChromaGR2V;
                                                ChromaXBR1 = ChromaXBR1 + ChromaB00V + ChromaBR1V + ChromaBR2V;
                                            }

                                            if (ChromaVert5)
                                            {
                                                ChromaXRL1 = ChromaXRL1 + ChromaRL3V + ChromaRL2V + ChromaRL1V + ChromaR00V + ChromaRR1V;
                                                ChromaXGL1 = ChromaXGL1 + ChromaGL3V + ChromaGL2V + ChromaGL1V + ChromaG00V + ChromaGR1V;
                                                ChromaXBL1 = ChromaXBL1 + ChromaBL3V + ChromaBL2V + ChromaBL1V + ChromaB00V + ChromaBR1V;
                                                ChromaXR00 = ChromaXR00 + ChromaRL2V + ChromaRL1V + ChromaR00V + ChromaRR1V + ChromaRR2V;
                                                ChromaXG00 = ChromaXG00 + ChromaGL2V + ChromaGL1V + ChromaG00V + ChromaGR1V + ChromaGR2V;
                                                ChromaXB00 = ChromaXB00 + ChromaBL2V + ChromaBL1V + ChromaB00V + ChromaBR1V + ChromaBR2V;
                                                ChromaXRR1 = ChromaXRR1 + ChromaRL1V + ChromaR00V + ChromaRR1V + ChromaRR2V + ChromaRR3V;
                                                ChromaXGR1 = ChromaXGR1 + ChromaGL1V + ChromaG00V + ChromaGR1V + ChromaGR2V + ChromaGR3V;
                                                ChromaXBR1 = ChromaXBR1 + ChromaBL1V + ChromaB00V + ChromaBR1V + ChromaBR2V + ChromaBR3V;
                                            }

                                            ChromaXRL1 = ChromaXRL1 / ChromaDiv;
                                            ChromaXGL1 = ChromaXGL1 / ChromaDiv;
                                            ChromaXBL1 = ChromaXBL1 / ChromaDiv;
                                            ChromaXR00 = ChromaXR00 / ChromaDiv;
                                            ChromaXG00 = ChromaXG00 / ChromaDiv;
                                            ChromaXB00 = ChromaXB00 / ChromaDiv;
                                            ChromaXRR1 = ChromaXRR1 / ChromaDiv;
                                            ChromaXGR1 = ChromaXGR1 / ChromaDiv;
                                            ChromaXBR1 = ChromaXBR1 / ChromaDiv;

                                            _W_R = YUV_C_R(LumaL1, ChromaXRL1);
                                            _W_G = YUV_C_G(LumaL1, ChromaXGL1);
                                            _W_B = YUV_C_B(LumaL1, ChromaXBL1);

                                            _P_R = YUV_C_R(Luma00, ChromaXR00);
                                            _P_G = YUV_C_G(Luma00, ChromaXG00);
                                            _P_B = YUV_C_B(Luma00, ChromaXB00);

                                            _E_R = YUV_C_R(LumaR1, ChromaXRR1);
                                            _E_G = YUV_C_G(LumaR1, ChromaXGR1);
                                            _E_B = YUV_C_B(LumaR1, ChromaXBR1);
                                        }
                                        break;
                                }

                                _NWR = _W_R; _N_R = _P_R; _NER = _E_R;
                                _SWR = _W_R; _S_R = _P_R; _SER = _E_R;
                                _NWG = _W_G; _N_G = _P_G; _NEG = _E_G;
                                _SWG = _W_G; _S_G = _P_G; _SEG = _E_G;
                                _NWB = _W_B; _N_B = _P_B; _NEB = _E_B;
                                _SWB = _W_B; _S_B = _P_B; _SEB = _E_B;

                                switch (LcdLayout)
                                {
                                    case 0: // H-RGB
                                        {
                                            BmpBufX_[00 + P + 2] = GammaLUT_O[_NWR];
                                            BmpBufX_[00 + P + 1] = GammaLUT_O[_NWG];
                                            BmpBufX_[00 + P + 0] = GammaLUT_O[_NWB];
                                            BmpBufX_[L1 + P + 2] = GammaLUT_O[_W_R];
                                            BmpBufX_[L1 + P + 1] = GammaLUT_O[_W_G];
                                            BmpBufX_[L1 + P + 0] = GammaLUT_O[_W_B];
                                            BmpBufX_[L2 + P + 2] = GammaLUT_O[_SWR];
                                            BmpBufX_[L2 + P + 1] = GammaLUT_O[_SWG];
                                            BmpBufX_[L2 + P + 0] = GammaLUT_O[_SWB];
                                            P += 4;

                                            BmpBufX_[00 + P + 2] = GammaLUT_O[_N_R];
                                            BmpBufX_[00 + P + 1] = GammaLUT_O[_N_G];
                                            BmpBufX_[00 + P + 0] = GammaLUT_O[_N_B];
                                            BmpBufX_[L1 + P + 2] = GammaLUT_O[_P_R];
                                            BmpBufX_[L1 + P + 1] = GammaLUT_O[_P_G];
                                            BmpBufX_[L1 + P + 0] = GammaLUT_O[_P_B];
                                            BmpBufX_[L2 + P + 2] = GammaLUT_O[_S_R];
                                            BmpBufX_[L2 + P + 1] = GammaLUT_O[_S_G];
                                            BmpBufX_[L2 + P + 0] = GammaLUT_O[_S_B];
                                            P += 4;

                                            BmpBufX_[00 + P + 2] = GammaLUT_O[_NER];
                                            BmpBufX_[00 + P + 1] = GammaLUT_O[_NEG];
                                            BmpBufX_[00 + P + 0] = GammaLUT_O[_NEB];
                                            BmpBufX_[L1 + P + 2] = GammaLUT_O[_E_R];
                                            BmpBufX_[L1 + P + 1] = GammaLUT_O[_E_G];
                                            BmpBufX_[L1 + P + 0] = GammaLUT_O[_E_B];
                                            BmpBufX_[L2 + P + 2] = GammaLUT_O[_SER];
                                            BmpBufX_[L2 + P + 1] = GammaLUT_O[_SEG];
                                            BmpBufX_[L2 + P + 0] = GammaLUT_O[_SEB];
                                            P += 4;
                                        }
                                        break;
                                    case 1: // H-BGR
                                        {
                                            BmpBufX_[00 + P + 2] = GammaLUT_O[_NER];
                                            BmpBufX_[00 + P + 1] = GammaLUT_O[_NEG];
                                            BmpBufX_[00 + P + 0] = GammaLUT_O[_NEB];
                                            BmpBufX_[L1 + P + 2] = GammaLUT_O[_E_R];
                                            BmpBufX_[L1 + P + 1] = GammaLUT_O[_E_G];
                                            BmpBufX_[L1 + P + 0] = GammaLUT_O[_E_B];
                                            BmpBufX_[L2 + P + 2] = GammaLUT_O[_SER];
                                            BmpBufX_[L2 + P + 1] = GammaLUT_O[_SEG];
                                            BmpBufX_[L2 + P + 0] = GammaLUT_O[_SEB];
                                            P += 4;

                                            BmpBufX_[00 + P + 2] = GammaLUT_O[_N_R];
                                            BmpBufX_[00 + P + 1] = GammaLUT_O[_N_G];
                                            BmpBufX_[00 + P + 0] = GammaLUT_O[_N_B];
                                            BmpBufX_[L1 + P + 2] = GammaLUT_O[_P_R];
                                            BmpBufX_[L1 + P + 1] = GammaLUT_O[_P_G];
                                            BmpBufX_[L1 + P + 0] = GammaLUT_O[_P_B];
                                            BmpBufX_[L2 + P + 2] = GammaLUT_O[_S_R];
                                            BmpBufX_[L2 + P + 1] = GammaLUT_O[_S_G];
                                            BmpBufX_[L2 + P + 0] = GammaLUT_O[_S_B];
                                            P += 4;

                                            BmpBufX_[00 + P + 2] = GammaLUT_O[_NWR];
                                            BmpBufX_[00 + P + 1] = GammaLUT_O[_NWG];
                                            BmpBufX_[00 + P + 0] = GammaLUT_O[_NWB];
                                            BmpBufX_[L1 + P + 2] = GammaLUT_O[_W_R];
                                            BmpBufX_[L1 + P + 1] = GammaLUT_O[_W_G];
                                            BmpBufX_[L1 + P + 0] = GammaLUT_O[_W_B];
                                            BmpBufX_[L2 + P + 2] = GammaLUT_O[_SWR];
                                            BmpBufX_[L2 + P + 1] = GammaLUT_O[_SWG];
                                            BmpBufX_[L2 + P + 0] = GammaLUT_O[_SWB];
                                            P += 4;
                                        }
                                        break;
                                    case 2: // V-RGB
                                        {
                                            BmpBufX_[00 + P + 2] = GammaLUT_O[_NWR];
                                            BmpBufX_[00 + P + 1] = GammaLUT_O[_NWG];
                                            BmpBufX_[00 + P + 0] = GammaLUT_O[_NWB];
                                            BmpBufX_[L1 + P + 2] = GammaLUT_O[_N_R];
                                            BmpBufX_[L1 + P + 1] = GammaLUT_O[_N_G];
                                            BmpBufX_[L1 + P + 0] = GammaLUT_O[_N_B];
                                            BmpBufX_[L2 + P + 2] = GammaLUT_O[_NER];
                                            BmpBufX_[L2 + P + 1] = GammaLUT_O[_NEG];
                                            BmpBufX_[L2 + P + 0] = GammaLUT_O[_NEB];
                                            P += 4;

                                            BmpBufX_[00 + P + 2] = GammaLUT_O[_W_R];
                                            BmpBufX_[00 + P + 1] = GammaLUT_O[_W_G];
                                            BmpBufX_[00 + P + 0] = GammaLUT_O[_W_B];
                                            BmpBufX_[L1 + P + 2] = GammaLUT_O[_P_R];
                                            BmpBufX_[L1 + P + 1] = GammaLUT_O[_P_G];
                                            BmpBufX_[L1 + P + 0] = GammaLUT_O[_P_B];
                                            BmpBufX_[L2 + P + 2] = GammaLUT_O[_E_R];
                                            BmpBufX_[L2 + P + 1] = GammaLUT_O[_E_G];
                                            BmpBufX_[L2 + P + 0] = GammaLUT_O[_E_B];
                                            P += 4;

                                            BmpBufX_[00 + P + 2] = GammaLUT_O[_SWR];
                                            BmpBufX_[00 + P + 1] = GammaLUT_O[_SWG];
                                            BmpBufX_[00 + P + 0] = GammaLUT_O[_SWB];
                                            BmpBufX_[L1 + P + 2] = GammaLUT_O[_S_R];
                                            BmpBufX_[L1 + P + 1] = GammaLUT_O[_S_G];
                                            BmpBufX_[L1 + P + 0] = GammaLUT_O[_S_B];
                                            BmpBufX_[L2 + P + 2] = GammaLUT_O[_SER];
                                            BmpBufX_[L2 + P + 1] = GammaLUT_O[_SEG];
                                            BmpBufX_[L2 + P + 0] = GammaLUT_O[_SEB];
                                            P += 4;
                                        }
                                        break;
                                    case 3: // V-BGR
                                        {
                                            BmpBufX_[00 + P + 2] = GammaLUT_O[_NER];
                                            BmpBufX_[00 + P + 1] = GammaLUT_O[_NEG];
                                            BmpBufX_[00 + P + 0] = GammaLUT_O[_NEB];
                                            BmpBufX_[L1 + P + 2] = GammaLUT_O[_N_R];
                                            BmpBufX_[L1 + P + 1] = GammaLUT_O[_N_G];
                                            BmpBufX_[L1 + P + 0] = GammaLUT_O[_N_B];
                                            BmpBufX_[L2 + P + 2] = GammaLUT_O[_NWR];
                                            BmpBufX_[L2 + P + 1] = GammaLUT_O[_NWG];
                                            BmpBufX_[L2 + P + 0] = GammaLUT_O[_NWB];
                                            P += 4;

                                            BmpBufX_[00 + P + 2] = GammaLUT_O[_E_R];
                                            BmpBufX_[00 + P + 1] = GammaLUT_O[_E_G];
                                            BmpBufX_[00 + P + 0] = GammaLUT_O[_E_B];
                                            BmpBufX_[L1 + P + 2] = GammaLUT_O[_P_R];
                                            BmpBufX_[L1 + P + 1] = GammaLUT_O[_P_G];
                                            BmpBufX_[L1 + P + 0] = GammaLUT_O[_P_B];
                                            BmpBufX_[L2 + P + 2] = GammaLUT_O[_W_R];
                                            BmpBufX_[L2 + P + 1] = GammaLUT_O[_W_G];
                                            BmpBufX_[L2 + P + 0] = GammaLUT_O[_W_B];
                                            P += 4;

                                            BmpBufX_[00 + P + 2] = GammaLUT_O[_SER];
                                            BmpBufX_[00 + P + 1] = GammaLUT_O[_SEG];
                                            BmpBufX_[00 + P + 0] = GammaLUT_O[_SEB];
                                            BmpBufX_[L1 + P + 2] = GammaLUT_O[_S_R];
                                            BmpBufX_[L1 + P + 1] = GammaLUT_O[_S_G];
                                            BmpBufX_[L1 + P + 0] = GammaLUT_O[_S_B];
                                            BmpBufX_[L2 + P + 2] = GammaLUT_O[_SWR];
                                            BmpBufX_[L2 + P + 1] = GammaLUT_O[_SWG];
                                            BmpBufX_[L2 + P + 0] = GammaLUT_O[_SWB];
                                            P += 4;
                                        }
                                        break;
                                }
                            }
                            P += L2;
                        }
                    }
                    break;
            }
            break;
        }
        case 41: // Interpolation after LCD decomposition
        {
            if (OpMatrix[OpNr][0] == 1)
            {
                // Vertical RGB layout
                if (PicW_ < 6)
                {
                    for (Y = MinY; Y < MaxY; Y++)
                    {
                        for (X = 0; X < PicW_; X++)
                        {
                            BmpBuf[OpNrX_][P + 2] = BmpBuf[OpNr_][P + 2];
                            BmpBuf[OpNrX_][P + 1] = BmpBuf[OpNr_][P + 1];
                            BmpBuf[OpNrX_][P + 0] = BmpBuf[OpNr_][P + 0];
                            P += 4;
                        }
                    }
                }
                else
                {
                    int PicW_3 = (PicW_ / 3) - 2;

                    for (Y = MinY; Y < MaxY; Y++)
                    {
                        BmpBuf[OpNrX_][P + 6] = BmpBuf[OpNr_][P + 6];
                        BmpBuf[OpNrX_][P + 5] = BmpBuf[OpNr_][P + 5];
                        BmpBuf[OpNrX_][P + 4] = BmpBuf[OpNr_][P + 4];

                        BmpBuf[OpNrX_][P + 2] = BmpBuf[OpNr_][P + 6];
                        BmpBuf[OpNrX_][P + 1] = BmpBuf[OpNr_][P + 5];
                        BmpBuf[OpNrX_][P + 0] = BmpBuf[OpNr_][P + 4];

                        BmpBuf[OpNrX_][P +10] = ColorDiv3[(GammaLUT_I[BmpBuf[OpNr_][P + 18]]) + (GammaLUT_I[BmpBuf[OpNr_][P +  6]]) + (GammaLUT_I[BmpBuf[OpNr_][P +  6]])];
                        BmpBuf[OpNrX_][P + 9] = ColorDiv3[(GammaLUT_I[BmpBuf[OpNr_][P + 17]]) + (GammaLUT_I[BmpBuf[OpNr_][P +  5]]) + (GammaLUT_I[BmpBuf[OpNr_][P +  5]])];
                        BmpBuf[OpNrX_][P + 8] = ColorDiv3[(GammaLUT_I[BmpBuf[OpNr_][P + 16]]) + (GammaLUT_I[BmpBuf[OpNr_][P +  4]]) + (GammaLUT_I[BmpBuf[OpNr_][P +  4]])];
                        P += 12;

                        for (X = 0; X < PicW_3; X++)
                        {
                            BmpBuf[OpNrX_][P + 2] = ColorDiv3[(GammaLUT_I[BmpBuf[OpNr_][P -  6]]) + (GammaLUT_I[BmpBuf[OpNr_][P +  6]]) + (GammaLUT_I[BmpBuf[OpNr_][P +  6]])];
                            BmpBuf[OpNrX_][P + 1] = ColorDiv3[(GammaLUT_I[BmpBuf[OpNr_][P -  7]]) + (GammaLUT_I[BmpBuf[OpNr_][P +  5]]) + (GammaLUT_I[BmpBuf[OpNr_][P +  5]])];
                            BmpBuf[OpNrX_][P + 0] = ColorDiv3[(GammaLUT_I[BmpBuf[OpNr_][P -  8]]) + (GammaLUT_I[BmpBuf[OpNr_][P +  4]]) + (GammaLUT_I[BmpBuf[OpNr_][P +  4]])];

                            BmpBuf[OpNrX_][P + 6] = BmpBuf[OpNr_][P +  6];
                            BmpBuf[OpNrX_][P + 5] = BmpBuf[OpNr_][P +  5];
                            BmpBuf[OpNrX_][P + 4] = BmpBuf[OpNr_][P +  4];

                            BmpBuf[OpNrX_][P +10] = ColorDiv3[(GammaLUT_I[BmpBuf[OpNr_][P + 18]]) + (GammaLUT_I[BmpBuf[OpNr_][P +  6]]) + (GammaLUT_I[BmpBuf[OpNr_][P +  6]])];
                            BmpBuf[OpNrX_][P + 9] = ColorDiv3[(GammaLUT_I[BmpBuf[OpNr_][P + 17]]) + (GammaLUT_I[BmpBuf[OpNr_][P +  5]]) + (GammaLUT_I[BmpBuf[OpNr_][P +  5]])];
                            BmpBuf[OpNrX_][P + 8] = ColorDiv3[(GammaLUT_I[BmpBuf[OpNr_][P + 16]]) + (GammaLUT_I[BmpBuf[OpNr_][P +  4]]) + (GammaLUT_I[BmpBuf[OpNr_][P +  4]])];
                            P += 12;
                        }

                        BmpBuf[OpNrX_][P + 2] = ColorDiv3[(GammaLUT_I[BmpBuf[OpNr_][P -  6]]) + (GammaLUT_I[BmpBuf[OpNr_][P +  6]]) + (GammaLUT_I[BmpBuf[OpNr_][P +  6]])];
                        BmpBuf[OpNrX_][P + 1] = ColorDiv3[(GammaLUT_I[BmpBuf[OpNr_][P -  7]]) + (GammaLUT_I[BmpBuf[OpNr_][P +  5]]) + (GammaLUT_I[BmpBuf[OpNr_][P +  5]])];
                        BmpBuf[OpNrX_][P + 0] = ColorDiv3[(GammaLUT_I[BmpBuf[OpNr_][P -  8]]) + (GammaLUT_I[BmpBuf[OpNr_][P +  4]]) + (GammaLUT_I[BmpBuf[OpNr_][P +  4]])];

                        BmpBuf[OpNrX_][P + 6] = BmpBuf[OpNr_][P + 6];
                        BmpBuf[OpNrX_][P + 5] = BmpBuf[OpNr_][P + 5];
                        BmpBuf[OpNrX_][P + 4] = BmpBuf[OpNr_][P + 4];

                        BmpBuf[OpNrX_][P +10] = BmpBuf[OpNr_][P + 6];
                        BmpBuf[OpNrX_][P + 9] = BmpBuf[OpNr_][P + 5];
                        BmpBuf[OpNrX_][P + 8] = BmpBuf[OpNr_][P + 4];
                        P += 12;
                    }
                }
            }
            else
            {
                // Horizontal RGB layout
                if (PicH_ < 6)
                {
                    for (Y = MinY; Y < MaxY; Y++)
                    {
                        for (X = 0; X < PicW_; X++)
                        {
                            BmpBuf[OpNrX_][P + 2] = BmpBuf[OpNr_][P + 2];
                            BmpBuf[OpNrX_][P + 1] = BmpBuf[OpNr_][P + 1];
                            BmpBuf[OpNrX_][P + 0] = BmpBuf[OpNr_][P + 0];
                            P += 4;
                        }
                    }
                }
                else
                {
                    int MinY_3 = MinY / 3;
                    int MaxY_3 = MaxY / 3;

                    int L1 = PicW_ << 2;
                    int L2 = L1 + L1;
                    int L3 = L1 + L2;
                    int LL = L1 * (MaxY - MinY - 1);

                    if (MaxY == PicH_)
                    {
                        MaxY_3--;
                        for (X = 0; X < PicW_; X++)
                        {
                            BmpBuf[OpNrX_][P + LL - L2 + 2] = ColorDiv3[(GammaLUT_I[BmpBuf[OpNr_][P + LL - L3 + 2]]) + (GammaLUT_I[BmpBuf[OpNr_][P + LL + 2]]) + (GammaLUT_I[BmpBuf[OpNr_][P + LL + 2]])];
                            BmpBuf[OpNrX_][P + LL - L2 + 1] = ColorDiv3[(GammaLUT_I[BmpBuf[OpNr_][P + LL - L3 + 1]]) + (GammaLUT_I[BmpBuf[OpNr_][P + LL + 1]]) + (GammaLUT_I[BmpBuf[OpNr_][P + LL + 1]])];
                            BmpBuf[OpNrX_][P + LL - L2 + 0] = ColorDiv3[(GammaLUT_I[BmpBuf[OpNr_][P + LL - L3 + 0]]) + (GammaLUT_I[BmpBuf[OpNr_][P + LL + 0]]) + (GammaLUT_I[BmpBuf[OpNr_][P + LL + 0]])];
                            BmpBuf[OpNrX_][P + LL - L1 + 2] = BmpBuf[OpNr_][P + LL + 2];
                            BmpBuf[OpNrX_][P + LL - L1 + 1] = BmpBuf[OpNr_][P + LL + 1];
                            BmpBuf[OpNrX_][P + LL - L1 + 0] = BmpBuf[OpNr_][P + LL + 0];
                            BmpBuf[OpNrX_][P + LL      + 2] = BmpBuf[OpNr_][P + LL + 2];
                            BmpBuf[OpNrX_][P + LL      + 1] = BmpBuf[OpNr_][P + LL + 1];
                            BmpBuf[OpNrX_][P + LL      + 0] = BmpBuf[OpNr_][P + LL + 0];
                            P += 4;
                        }
                        P -= L1;
                    }
                    if (MinY == 0)
                    {
                        MinY_3++;
                        for (X = 0; X < PicW_; X++)
                        {
                            BmpBuf[OpNrX_][P           + 2] = BmpBuf[OpNr_][P      + 2];
                            BmpBuf[OpNrX_][P           + 1] = BmpBuf[OpNr_][P      + 1];
                            BmpBuf[OpNrX_][P           + 0] = BmpBuf[OpNr_][P      + 0];
                            BmpBuf[OpNrX_][P      + L1 + 2] = BmpBuf[OpNr_][P      + 2];
                            BmpBuf[OpNrX_][P      + L1 + 1] = BmpBuf[OpNr_][P      + 1];
                            BmpBuf[OpNrX_][P      + L1 + 0] = BmpBuf[OpNr_][P      + 0];
                            BmpBuf[OpNrX_][P      + L2 + 2] = ColorDiv3[(GammaLUT_I[BmpBuf[OpNr_][P      + L3 + 2]]) + (GammaLUT_I[BmpBuf[OpNr_][P      + 2]]) + (GammaLUT_I[BmpBuf[OpNr_][P      + 2]])];
                            BmpBuf[OpNrX_][P      + L2 + 1] = ColorDiv3[(GammaLUT_I[BmpBuf[OpNr_][P      + L3 + 1]]) + (GammaLUT_I[BmpBuf[OpNr_][P      + 1]]) + (GammaLUT_I[BmpBuf[OpNr_][P      + 1]])];
                            BmpBuf[OpNrX_][P      + L2 + 0] = ColorDiv3[(GammaLUT_I[BmpBuf[OpNr_][P      + L3 + 0]]) + (GammaLUT_I[BmpBuf[OpNr_][P      + 0]]) + (GammaLUT_I[BmpBuf[OpNr_][P      + 0]])];
                            P += 4;
                        }
                        P += L3;
                    }
                    else
                    {
                        P += L1;
                    }

                    for (Y = MinY_3; Y < MaxY_3; Y++)
                    {
                        for (X = 0; X < PicW_; X++)
                        {
                            BmpBuf[OpNrX_][P - L1 + 2] = ColorDiv3[(GammaLUT_I[BmpBuf[OpNr_][P - L2 + 2]]) + (GammaLUT_I[BmpBuf[OpNr_][P + 2]]) + (GammaLUT_I[BmpBuf[OpNr_][P + 2]])];
                            BmpBuf[OpNrX_][P - L1 + 1] = ColorDiv3[(GammaLUT_I[BmpBuf[OpNr_][P - L2 + 1]]) + (GammaLUT_I[BmpBuf[OpNr_][P + 1]]) + (GammaLUT_I[BmpBuf[OpNr_][P + 1]])];
                            BmpBuf[OpNrX_][P - L1 + 0] = ColorDiv3[(GammaLUT_I[BmpBuf[OpNr_][P - L2 + 0]]) + (GammaLUT_I[BmpBuf[OpNr_][P + 0]]) + (GammaLUT_I[BmpBuf[OpNr_][P + 0]])];
                            BmpBuf[OpNrX_][P + 2] = BmpBuf[OpNr_][P + 2];
                            BmpBuf[OpNrX_][P + 1] = BmpBuf[OpNr_][P + 1];
                            BmpBuf[OpNrX_][P + 0] = BmpBuf[OpNr_][P + 0];
                            BmpBuf[OpNrX_][P + L1 + 2] = ColorDiv3[(GammaLUT_I[BmpBuf[OpNr_][P + L2 + 2]]) + (GammaLUT_I[BmpBuf[OpNr_][P + 2]]) + (GammaLUT_I[BmpBuf[OpNr_][P + 2]])];
                            BmpBuf[OpNrX_][P + L1 + 1] = ColorDiv3[(GammaLUT_I[BmpBuf[OpNr_][P + L2 + 1]]) + (GammaLUT_I[BmpBuf[OpNr_][P + 1]]) + (GammaLUT_I[BmpBuf[OpNr_][P + 1]])];
                            BmpBuf[OpNrX_][P + L1 + 0] = ColorDiv3[(GammaLUT_I[BmpBuf[OpNr_][P + L2 + 0]]) + (GammaLUT_I[BmpBuf[OpNr_][P + 0]]) + (GammaLUT_I[BmpBuf[OpNr_][P + 0]])];
                            P += 4;
                        }
                        P += L2;
                    }
                }
            }
            break;
        }
        case 5: // Image flip / rotate
        {
            switch (OpMatrix[OpNr][0])
            {
                case 0: // None
                    {
                        for (Y = MinY; Y < MaxY; Y++)
                        {
                            for (X = 0; X < PicW_; X++)
                            {
                                BmpBuf[OpNrX_][P + 2] = BmpBuf[OpNr_][P + 2];
                                BmpBuf[OpNrX_][P + 1] = BmpBuf[OpNr_][P + 1];
                                BmpBuf[OpNrX_][P + 0] = BmpBuf[OpNr_][P + 0];
                                P += 4;
                            }
                        }
                    }
                    break;
                case 1: // Upside down
                    {
                        int PicW4 = PicW_ << 2;
                        int P_ = P;
                        P_ = P_ - (PicW4 * MinY);
                        P_ = P_ - (PicW4 * MinY);
                        P_ = P_ + (PicW4 * PicH_);
                        P_ = P_ - PicW4;
                        P_ = P_ - 4;
                        for (Y = MinY; Y < MaxY; Y++)
                        {
                            P_ = P_ + PicW4;
                            for (X = 0; X < PicW_; X++)
                            {
                                BmpBuf[OpNrX_][P + 2] = BmpBuf[OpNr_][P_ + 2];
                                BmpBuf[OpNrX_][P + 1] = BmpBuf[OpNr_][P_ + 1];
                                BmpBuf[OpNrX_][P + 0] = BmpBuf[OpNr_][P_ + 0];
                                P += 4;
                                P_ -= 4;
                            }
                            P_ = P_ - PicW4;
                        }
                    }
                    break;
                case 2: // Flip horizontal
                    {
                        int PicW4 = PicW_ << 2;
                        int P_ = P - 4;
                        for (Y = MinY; Y < MaxY; Y++)
                        {
                            P_ = P_ + PicW4;
                            for (X = 0; X < PicW_; X++)
                            {
                                BmpBuf[OpNrX_][P + 2] = BmpBuf[OpNr_][P_ + 2];
                                BmpBuf[OpNrX_][P + 1] = BmpBuf[OpNr_][P_ + 1];
                                BmpBuf[OpNrX_][P + 0] = BmpBuf[OpNr_][P_ + 0];
                                P += 4;
                                P_ -= 4;
                            }
                            P_ = P_ + PicW4;
                        }
                    }
                    break;
                case 3: // Flip vertical
                    {
                        int PicW4 = PicW_ << 2;
                        int P_ = P;
                        P_ = P_ - (PicW4 * MinY);
                        P_ = P_ - (PicW4 * MinY);
                        P_ = P_ + (PicW4 * PicH_);
                        P_ = P_ - PicW4;
                        for (Y = MinY; Y < MaxY; Y++)
                        {
                            for (X = 0; X < PicW_; X++)
                            {
                                BmpBuf[OpNrX_][P + 2] = BmpBuf[OpNr_][P_ + 2];
                                BmpBuf[OpNrX_][P + 1] = BmpBuf[OpNr_][P_ + 1];
                                BmpBuf[OpNrX_][P + 0] = BmpBuf[OpNr_][P_ + 0];
                                P += 4;
                                P_ += 4;
                            }
                            P_ = P_ - PicW4;
                            P_ = P_ - PicW4;
                        }
                    }
                    break;
                case 4: // Main diagonal
                    {
                        int PicW4 = PicW_ << 2;
                        int PointX = 0;
                        int PointY = 0;
                        int PointX_ = PicH_;
                        for (Y = 0; Y < PicH_; Y++)
                        {
                            for (X = 0; X < PicW_; X++)
                            {
                                int P_ = PointX + PointY;
                                BmpBuf[OpNrX_][P + 2] = BmpBuf[OpNr_][P_ + 2];
                                BmpBuf[OpNrX_][P + 1] = BmpBuf[OpNr_][P_ + 1];
                                BmpBuf[OpNrX_][P + 0] = BmpBuf[OpNr_][P_ + 0];
                                P += 4;
                                PointX_--;
                                PointX += PicW4;
                                if (PointX_ == 0)
                                {
                                    PointX_ = PicH_;
                                    PointX = 0;
                                    PointY += 4;
                                }
                            }
                        }
                    }
                    break;
                case 5: // Other diagonal
                    {
                        int PicW4 = PicW_ << 2;
                        int PointX0 = PicW4 * (PicH_ - 1);
                        int PointX = PointX0;
                        int PointY = PicW4 - 4;
                        int PointX_ = PicH_;
                        for (Y = 0; Y < PicH_; Y++)
                        {
                            for (X = 0; X < PicW_; X++)
                            {
                                int P_ = PointX + PointY;
                                BmpBuf[OpNrX_][P + 2] = BmpBuf[OpNr_][P_ + 2];
                                BmpBuf[OpNrX_][P + 1] = BmpBuf[OpNr_][P_ + 1];
                                BmpBuf[OpNrX_][P + 0] = BmpBuf[OpNr_][P_ + 0];
                                P += 4;
                                PointX_--;
                                PointX -= PicW4;
                                if (PointX_ == 0)
                                {
                                    PointX_ = PicH_;
                                    PointX = PointX0;
                                    PointY -= 4;
                                }
                            }
                        }
                    }
                    break;
                case 6: // Rotate clockwise
                    {
                        int PicW4 = PicW_ << 2;
                        int PointX0 = PicW4 * (PicH_ - 1);
                        int PointX = PointX0;
                        int PointY = 0;
                        int PointX_ = PicH_;
                        for (Y = 0; Y < PicH_; Y++)
                        {
                            for (X = 0; X < PicW_; X++)
                            {
                                int P_ = PointX + PointY;
                                BmpBuf[OpNrX_][P + 2] = BmpBuf[OpNr_][P_ + 2];
                                BmpBuf[OpNrX_][P + 1] = BmpBuf[OpNr_][P_ + 1];
                                BmpBuf[OpNrX_][P + 0] = BmpBuf[OpNr_][P_ + 0];
                                P += 4;
                                PointX_--;
                                PointX -= PicW4;
                                if (PointX_ == 0)
                                {
                                    PointX_ = PicH_;
                                    PointX = PointX0;
                                    PointY += 4;
                                }
                            }
                        }
                    }
                    break;
                case 7: // Rotate counter clockwise
                    {
                        int PicW4 = PicW_ << 2;
                        int PointX = 0;
                        int PointY = PicW4 - 4;
                        int PointX_ = PicH_;
                        for (Y = 0; Y < PicH_; Y++)
                        {
                            for (X = 0; X < PicW_; X++)
                            {
                                int P_ = PointX + PointY;
                                BmpBuf[OpNrX_][P + 2] = BmpBuf[OpNr_][P_ + 2];
                                BmpBuf[OpNrX_][P + 1] = BmpBuf[OpNr_][P_ + 1];
                                BmpBuf[OpNrX_][P + 0] = BmpBuf[OpNr_][P_ + 0];
                                P += 4;
                                PointX_--;
                                PointX += PicW4;
                                if (PointX_ == 0)
                                {
                                    PointX_ = PicH_;
                                    PointX = 0;
                                    PointY -= 4;
                                }
                            }
                        }
                    }
                    break;
            }
        }

    }
}

///
/// \brief PicThread::GetColor - Function used in accurate interpolation in picture resizing
/// \param Bmp
/// \param PicW__
/// \param PicH__
/// \param X
/// \param Y
/// \param TX
/// \param TY
/// \param R
/// \param G
/// \param B
/// \param T
///
inline void PicThread::GetColor(uchar * Bmp, int PicW__, int PicH__, int X, int Y, int TX, int TY, int &R, int &G, int &B, int &T)
{
    R = 0;
    G = 0;
    B = 0;
    T = 0;
    int PicP, XX, YY;
    for (YY = (Y - TY); YY <= (Y + TY); YY++)
    {
        if ((YY >= 0) && (YY < PicH__))
        {
            for (XX = (X - TX); XX <= (X + TX); XX++)
            {
                if ((XX >= 0) && (XX < PicW__))
                {
                    PicP = ((YY * PicW__) + XX) << 2;
                    R = R + Bmp[PicP + 2];
                    G = G + Bmp[PicP + 1];
                    B = B + Bmp[PicP + 0];
                    T++;
                }
            }
        }
    }
}
