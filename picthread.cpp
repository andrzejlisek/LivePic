#include "picthread.h"

PicThread::PicThread(QObject *parent) : QThread(parent)
{
    BmpDisp = NULL;
    BmpDispW = 0;
    BmpDispH = 0;
    FPS = 0;

    int C, R, G, B;
    for (C = 0; C < 16777215; C++)
    {
        R = (C & 0xFF0000) >> 16;
        G = (C & 0x00FF00) >> 8;
        B = C & 0x0000FF;
        HQX_YUV_Y[C] = (int)(0.299 * R + 0.587 * G + 0.114 * B);
        HQX_YUV_U[C] = (int)(-0.169 * R - 0.331 * G + 0.5 * B) + 128;
        HQX_YUV_V[C] = (int)(0.5 * R - 0.419 * G - 0.081 * B) + 128;
    }
    BmpBufN = 0;
    BmpBuf = NULL;
    ThrPicLines = NULL;
    OpC1 = 0;
}

PicThread::~PicThread()
{

}

bool PicThread::HQX_Diff_RGB(int R1, int G1, int B1, int R2, int G2, int B2)
{
    return HQX_Diff_YUV(HQX_RGB2YUV(R1, G1, B1), HQX_RGB2YUV(R2, G2, B2));
}

bool PicThread::HQX_Diff_YUV(int YUV1, int YUV2)
{
    return ((abs(HQX_YUV_Y[YUV1] - HQX_YUV_Y[YUV2]) > HQX_DiffY) || (abs(HQX_YUV_U[YUV1] - HQX_YUV_U[YUV2]) > HQX_DiffU) || (abs(HQX_YUV_V[YUV1] - HQX_YUV_V[YUV2]) > HQX_DiffV));
}

///
/// \brief PicThread::OpLoad - Loading transform options into transform structures
///
void PicThread::OpLoad()
{
    PicThreads = Settings_->PicThreads;
    PipeCount = Settings_->PipeCount;

    PropCol1.clear();
    PropCol2.clear();
    PropVal1.clear();
    PropVal2.clear();
    PropResult.clear();

    for (uint I = 0; I < OpMatrix.size(); I++) { delete[] OpMatrix[I]; }
    for (uint I = 0; I < OpMatrixR.size(); I++) { delete[] OpMatrixR[I]; }
    for (uint I = 0; I < OpMatrixG.size(); I++) { delete[] OpMatrixG[I]; }
    for (uint I = 0; I < OpMatrixB.size(); I++) { delete[] OpMatrixB[I]; }
    for (uint I = 0; I < OpMatrixIR.size(); I++) { delete[] OpMatrixIR[I]; }
    for (uint I = 0; I < OpMatrixIG.size(); I++) { delete[] OpMatrixIG[I]; }
    for (uint I = 0; I < OpMatrixIB.size(); I++) { delete[] OpMatrixIB[I]; }
    OpType.clear();
    OpMatrix.clear();
    OpMatrixR.clear();
    OpMatrixG.clear();
    OpMatrixB.clear();
    OpMatrixIR.clear();
    OpMatrixIG.clear();
    OpMatrixIB.clear();
    OpMatrixDither.clear();


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

    for (int I = 0; I < (65536 * 3); I++)
    {
        ColorDiv3[I] = GammaLUT_O[I / 3];
    }


    if (OpType.size() == 0)
    {

        int I, IL;
        int LastOpType = -1;
        int OpTypeX = 0;
        int LastItem = -1;

        IL = TransformCore_->TransformList.size();
        for (I = 0; I < IL; I++)
        {
            TransformItem TransformItem_ = TransformCore_->TransformList[I];
            if (TransformItem_.TransEnabled)
            {
                uchar * OpMatrixX = NULL;
                uchar * OpMatrixRX = NULL;
                uchar * OpMatrixGX = NULL;
                uchar * OpMatrixBX = NULL;
                vector<DitherMatrixElement> OpMatrixDitherX;
                DitherMatrixElement TX;
                int T5[5][5];
                int * OpMatrixIRX = NULL;
                int * OpMatrixIGX = NULL;
                int * OpMatrixIBX = NULL;

                OpTypeX = TransformItem_.TransType;

                // Additional conversion between RGB and single-number representation
                if ((OpTypeX == 3) && (LastOpType != 3))
                {
                    LastItem++;
                    OpType.push_back(31);
                    OpMatrix.push_back(NULL);
                    OpMatrixR.push_back(NULL);
                    OpMatrixG.push_back(NULL);
                    OpMatrixB.push_back(NULL);
                    OpMatrixIR.push_back(NULL);
                    OpMatrixIG.push_back(NULL);
                    OpMatrixIB.push_back(NULL);
                    OpMatrixDither.push_back(OpMatrixDitherX);
                }
                if ((OpTypeX != 3) && (LastOpType == 3))
                {
                    LastItem++;
                    OpType.push_back(32);
                    OpMatrix.push_back(NULL);
                    OpMatrixR.push_back(NULL);
                    OpMatrixG.push_back(NULL);
                    OpMatrixB.push_back(NULL);
                    OpMatrixIR.push_back(new int[1]);
                    OpMatrixIG.push_back(NULL);
                    OpMatrixIB.push_back(NULL);
                    OpMatrixDither.push_back(OpMatrixDitherX);
                }

                bool AddItem = true;

                switch (OpTypeX)
                {
                    case 0: // Triple 256-item LUT
                        {
                            OpMatrixRX = new uchar[256];
                            OpMatrixGX = new uchar[256];
                            OpMatrixBX = new uchar[256];
                            TransformItem_.FillLUT(OpMatrixRX, OpMatrixGX, OpMatrixBX);

                            // Merge 3*256 LUT with last 3*256 LUT
                            if (LastOpType == 0)
                            {
                                TransformItem_.Merge256(OpMatrixR[LastItem], OpMatrixG[LastItem], OpMatrixB[LastItem], OpMatrixRX, OpMatrixGX, OpMatrixBX);
                                delete[] OpMatrixRX;
                                delete[] OpMatrixGX;
                                delete[] OpMatrixBX;
                                AddItem = false;
                            }

                            // Convert current 3*256 LUT into 16M LUT, merge with last 16M LUT
                            if (LastOpType == 1)
                            {
                                uchar * OpMatrixRX_16M = new uchar[16777216];
                                uchar * OpMatrixGX_16M = new uchar[16777216];
                                uchar * OpMatrixBX_16M = new uchar[16777216];
                                TransformItem_.Convert256To16M(OpMatrixRX, OpMatrixGX, OpMatrixBX, OpMatrixRX_16M, OpMatrixGX_16M, OpMatrixBX_16M);
                                delete[] OpMatrixRX;
                                delete[] OpMatrixGX;
                                delete[] OpMatrixBX;
                                OpMatrixRX = OpMatrixRX_16M;
                                OpMatrixGX = OpMatrixGX_16M;
                                OpMatrixBX = OpMatrixBX_16M;
                                OpTypeX = 1;

                                TransformItem_.Merge16M(OpMatrixR[LastItem], OpMatrixG[LastItem], OpMatrixB[LastItem], OpMatrixRX, OpMatrixGX, OpMatrixBX);
                                delete[] OpMatrixRX;
                                delete[] OpMatrixGX;
                                delete[] OpMatrixBX;
                                AddItem = false;
                            }
                        }
                        break;
                    case 1: // Single 16M-item LUT
                        {
                            OpMatrixRX = new uchar[16777216];
                            OpMatrixGX = new uchar[16777216];
                            OpMatrixBX = new uchar[16777216];
                            TransformItem_.FillLUT(OpMatrixRX, OpMatrixGX, OpMatrixBX);

                            // Convert last 3*256 LUT into 16M LUT
                            if (LastOpType == 0)
                            {
                                uchar * OpMatrixRX_16M = new uchar[16777216];
                                uchar * OpMatrixGX_16M = new uchar[16777216];
                                uchar * OpMatrixBX_16M = new uchar[16777216];
                                TransformItem_.Convert256To16M(OpMatrixR[LastItem], OpMatrixG[LastItem], OpMatrixB[LastItem], OpMatrixRX_16M, OpMatrixGX_16M, OpMatrixBX_16M);
                                delete[] OpMatrixR[LastItem];
                                delete[] OpMatrixG[LastItem];
                                delete[] OpMatrixB[LastItem];
                                OpMatrixR[LastItem] = OpMatrixRX_16M;
                                OpMatrixG[LastItem] = OpMatrixGX_16M;
                                OpMatrixB[LastItem] = OpMatrixBX_16M;
                                OpType[LastItem] = 1;
                                LastOpType = 1;
                            }

                            // Merge 16M LUT with last 16M LUT
                            if (LastOpType == 1)
                            {
                                TransformItem_.Merge16M(OpMatrixR[LastItem], OpMatrixG[LastItem], OpMatrixB[LastItem], OpMatrixRX, OpMatrixGX, OpMatrixBX);
                                delete[] OpMatrixRX;
                                delete[] OpMatrixGX;
                                delete[] OpMatrixBX;
                                AddItem = false;
                            }
                        }
                        break;
                    case 2: // Convolution
                        {
                            OpMatrixIRX = new int[29];
                            OpMatrixIGX = new int[28];
                            OpMatrixIBX = new int[28];
                            TransformItem_.FillConv(OpMatrixIRX, OpMatrixIGX, OpMatrixIBX);
                            OpMatrixIRX[28] = TransformItem_.Trans2Gamma ? 1 : 0;
                        }
                        break;
                    case 3: // Dedithering
                        {
                            OpMatrixIRX = new int[2];
                            int I4 = 0;
                            int I25 = 0;
                            for (int I = 0; I < TransformItem_.Trans3ItemCount; I++)
                            {
                                TX.Color1 = TransformItem_.Trans3Prop[I4]; I4++;
                                TX.Color2 = TransformItem_.Trans3Prop[I4]; I4++;
                                TX.Color3 = TransformItem_.Trans3Prop[I4]; I4++;
                                TX.Color4 = TransformItem_.Trans3Prop[I4]; I4++;

                                T5[0][0] = TransformItem_.Trans3Matrix[I25]; I25++;
                                T5[1][0] = TransformItem_.Trans3Matrix[I25]; I25++;
                                T5[2][0] = TransformItem_.Trans3Matrix[I25]; I25++;
                                T5[3][0] = TransformItem_.Trans3Matrix[I25]; I25++;
                                T5[4][0] = TransformItem_.Trans3Matrix[I25]; I25++;
                                T5[0][1] = TransformItem_.Trans3Matrix[I25]; I25++;
                                T5[1][1] = TransformItem_.Trans3Matrix[I25]; I25++;
                                T5[2][1] = TransformItem_.Trans3Matrix[I25]; I25++;
                                T5[3][1] = TransformItem_.Trans3Matrix[I25]; I25++;
                                T5[4][1] = TransformItem_.Trans3Matrix[I25]; I25++;
                                T5[0][2] = TransformItem_.Trans3Matrix[I25]; I25++;
                                T5[1][2] = TransformItem_.Trans3Matrix[I25]; I25++;
                                T5[2][2] = TransformItem_.Trans3Matrix[I25]; I25++;
                                T5[3][2] = TransformItem_.Trans3Matrix[I25]; I25++;
                                T5[4][2] = TransformItem_.Trans3Matrix[I25]; I25++;
                                T5[0][3] = TransformItem_.Trans3Matrix[I25]; I25++;
                                T5[1][3] = TransformItem_.Trans3Matrix[I25]; I25++;
                                T5[2][3] = TransformItem_.Trans3Matrix[I25]; I25++;
                                T5[3][3] = TransformItem_.Trans3Matrix[I25]; I25++;
                                T5[4][3] = TransformItem_.Trans3Matrix[I25]; I25++;
                                T5[0][4] = TransformItem_.Trans3Matrix[I25]; I25++;
                                T5[1][4] = TransformItem_.Trans3Matrix[I25]; I25++;
                                T5[2][4] = TransformItem_.Trans3Matrix[I25]; I25++;
                                T5[3][4] = TransformItem_.Trans3Matrix[I25]; I25++;
                                T5[4][4] = TransformItem_.Trans3Matrix[I25]; I25++;

                                int NumColors = 0;
                                NumColors = Max(NumColors, T5[0][0]);
                                NumColors = Max(NumColors, T5[1][0]);
                                NumColors = Max(NumColors, T5[2][0]);
                                NumColors = Max(NumColors, T5[3][0]);
                                NumColors = Max(NumColors, T5[4][0]);
                                NumColors = Max(NumColors, T5[0][1]);
                                NumColors = Max(NumColors, T5[1][1]);
                                NumColors = Max(NumColors, T5[2][1]);
                                NumColors = Max(NumColors, T5[3][1]);
                                NumColors = Max(NumColors, T5[4][1]);
                                NumColors = Max(NumColors, T5[0][2]);
                                NumColors = Max(NumColors, T5[1][2]);
                                NumColors = Max(NumColors, T5[2][2]);
                                NumColors = Max(NumColors, T5[3][2]);
                                NumColors = Max(NumColors, T5[4][2]);
                                NumColors = Max(NumColors, T5[0][3]);
                                NumColors = Max(NumColors, T5[1][3]);
                                NumColors = Max(NumColors, T5[2][3]);
                                NumColors = Max(NumColors, T5[3][3]);
                                NumColors = Max(NumColors, T5[4][3]);
                                NumColors = Max(NumColors, T5[0][4]);
                                NumColors = Max(NumColors, T5[1][4]);
                                NumColors = Max(NumColors, T5[2][4]);
                                NumColors = Max(NumColors, T5[3][4]);
                                NumColors = Max(NumColors, T5[4][4]);

                                for (int II = 0; II < 4; II++)
                                {
                                    int TransRot = TransformItem_.Trans3Rot[I * 4 + II];
                                    switch (TransRot)
                                    {
                                        case 1: // Straight
                                            {
                                                TX.Colors = NumColors;
                                                TX.T[0][0] = T5[0][0]; TX.T[0][1] = T5[0][1]; TX.T[0][2] = T5[0][2]; TX.T[0][3] = T5[0][3]; TX.T[0][4] = T5[0][4];
                                                TX.T[1][0] = T5[1][0]; TX.T[1][1] = T5[1][1]; TX.T[1][2] = T5[1][2]; TX.T[1][3] = T5[1][3]; TX.T[1][4] = T5[1][4];
                                                TX.T[2][0] = T5[2][0]; TX.T[2][1] = T5[2][1]; TX.T[2][2] = T5[2][2]; TX.T[2][3] = T5[2][3]; TX.T[2][4] = T5[2][4];
                                                TX.T[3][0] = T5[3][0]; TX.T[3][1] = T5[3][1]; TX.T[3][2] = T5[3][2]; TX.T[3][3] = T5[3][3]; TX.T[3][4] = T5[3][4];
                                                TX.T[4][0] = T5[4][0]; TX.T[4][1] = T5[4][1]; TX.T[4][2] = T5[4][2]; TX.T[4][3] = T5[4][3]; TX.T[4][4] = T5[4][4];
                                                OpMatrixDitherX.push_back(TX);
                                            }
                                            break;
                                        case 2: // Upside down
                                            {
                                                TX.Colors = NumColors;
                                                TX.T[0][0] = T5[4][4]; TX.T[0][1] = T5[4][3]; TX.T[0][2] = T5[4][2]; TX.T[0][3] = T5[4][1]; TX.T[0][4] = T5[4][0];
                                                TX.T[1][0] = T5[3][4]; TX.T[1][1] = T5[3][3]; TX.T[1][2] = T5[3][2]; TX.T[1][3] = T5[3][1]; TX.T[1][4] = T5[3][0];
                                                TX.T[2][0] = T5[2][4]; TX.T[2][1] = T5[2][3]; TX.T[2][2] = T5[2][2]; TX.T[2][3] = T5[2][1]; TX.T[2][4] = T5[2][0];
                                                TX.T[3][0] = T5[1][4]; TX.T[3][1] = T5[1][3]; TX.T[3][2] = T5[1][2]; TX.T[3][3] = T5[1][1]; TX.T[3][4] = T5[1][0];
                                                TX.T[4][0] = T5[0][4]; TX.T[4][1] = T5[0][3]; TX.T[4][2] = T5[0][2]; TX.T[4][3] = T5[0][1]; TX.T[4][4] = T5[0][0];
                                                OpMatrixDitherX.push_back(TX);
                                            }
                                            break;
                                        case 3: // Flip horizontal
                                            {
                                                TX.Colors = NumColors;
                                                TX.T[0][0] = T5[4][0]; TX.T[0][1] = T5[4][1]; TX.T[0][2] = T5[4][2]; TX.T[0][3] = T5[4][3]; TX.T[0][4] = T5[4][4];
                                                TX.T[1][0] = T5[3][0]; TX.T[1][1] = T5[3][1]; TX.T[1][2] = T5[3][2]; TX.T[1][3] = T5[3][3]; TX.T[1][4] = T5[3][4];
                                                TX.T[2][0] = T5[2][0]; TX.T[2][1] = T5[2][1]; TX.T[2][2] = T5[2][2]; TX.T[2][3] = T5[2][3]; TX.T[2][4] = T5[2][4];
                                                TX.T[3][0] = T5[1][0]; TX.T[3][1] = T5[1][1]; TX.T[3][2] = T5[1][2]; TX.T[3][3] = T5[1][3]; TX.T[3][4] = T5[1][4];
                                                TX.T[4][0] = T5[0][0]; TX.T[4][1] = T5[0][1]; TX.T[4][2] = T5[0][2]; TX.T[4][3] = T5[0][3]; TX.T[4][4] = T5[0][4];
                                                OpMatrixDitherX.push_back(TX);
                                            }
                                            break;
                                        case 4: // Flip vertical
                                            {
                                                TX.Colors = NumColors;
                                                TX.T[0][0] = T5[0][4]; TX.T[0][1] = T5[0][3]; TX.T[0][2] = T5[0][2]; TX.T[0][3] = T5[0][1]; TX.T[0][4] = T5[0][0];
                                                TX.T[1][0] = T5[1][4]; TX.T[1][1] = T5[1][3]; TX.T[1][2] = T5[1][2]; TX.T[1][3] = T5[1][1]; TX.T[1][4] = T5[1][0];
                                                TX.T[2][0] = T5[2][4]; TX.T[2][1] = T5[2][3]; TX.T[2][2] = T5[2][2]; TX.T[2][3] = T5[2][1]; TX.T[2][4] = T5[2][0];
                                                TX.T[3][0] = T5[3][4]; TX.T[3][1] = T5[3][3]; TX.T[3][2] = T5[3][2]; TX.T[3][3] = T5[3][1]; TX.T[3][4] = T5[3][0];
                                                TX.T[4][0] = T5[4][4]; TX.T[4][1] = T5[4][3]; TX.T[4][2] = T5[4][2]; TX.T[4][3] = T5[4][1]; TX.T[4][4] = T5[4][0];
                                                OpMatrixDitherX.push_back(TX);
                                            }
                                            break;
                                        case 5: // Flip by main diagonal
                                            {
                                                TX.Colors = NumColors;
                                                TX.T[0][0] = T5[0][0]; TX.T[0][1] = T5[1][0]; TX.T[0][2] = T5[2][0]; TX.T[0][3] = T5[3][0]; TX.T[0][4] = T5[4][0];
                                                TX.T[1][0] = T5[0][1]; TX.T[1][1] = T5[1][1]; TX.T[1][2] = T5[2][1]; TX.T[1][3] = T5[3][1]; TX.T[1][4] = T5[4][1];
                                                TX.T[2][0] = T5[0][2]; TX.T[2][1] = T5[1][2]; TX.T[2][2] = T5[2][2]; TX.T[2][3] = T5[3][2]; TX.T[2][4] = T5[4][2];
                                                TX.T[3][0] = T5[0][3]; TX.T[3][1] = T5[1][3]; TX.T[3][2] = T5[2][3]; TX.T[3][3] = T5[3][3]; TX.T[3][4] = T5[4][3];
                                                TX.T[4][0] = T5[0][4]; TX.T[4][1] = T5[1][4]; TX.T[4][2] = T5[2][4]; TX.T[4][3] = T5[3][4]; TX.T[4][4] = T5[4][4];
                                                OpMatrixDitherX.push_back(TX);
                                            }
                                            break;
                                        case 6: // Flip by other diagonal
                                            {
                                                TX.Colors = NumColors;
                                                TX.T[0][0] = T5[4][4]; TX.T[0][1] = T5[3][4]; TX.T[0][2] = T5[2][4]; TX.T[0][3] = T5[1][4]; TX.T[0][4] = T5[0][4];
                                                TX.T[1][0] = T5[4][3]; TX.T[1][1] = T5[3][3]; TX.T[1][2] = T5[2][3]; TX.T[1][3] = T5[1][3]; TX.T[1][4] = T5[0][3];
                                                TX.T[2][0] = T5[4][2]; TX.T[2][1] = T5[3][2]; TX.T[2][2] = T5[2][2]; TX.T[2][3] = T5[1][2]; TX.T[2][4] = T5[0][2];
                                                TX.T[3][0] = T5[4][1]; TX.T[3][1] = T5[3][1]; TX.T[3][2] = T5[2][1]; TX.T[3][3] = T5[1][1]; TX.T[3][4] = T5[0][1];
                                                TX.T[4][0] = T5[4][0]; TX.T[4][1] = T5[3][0]; TX.T[4][2] = T5[2][0]; TX.T[4][3] = T5[1][0]; TX.T[4][4] = T5[0][0];
                                                OpMatrixDitherX.push_back(TX);
                                            }
                                            break;
                                        case 7: // Rotate clockwise
                                            {
                                                TX.Colors = NumColors;
                                                TX.T[0][0] = T5[0][4]; TX.T[0][1] = T5[1][4]; TX.T[0][2] = T5[2][4]; TX.T[0][3] = T5[3][4]; TX.T[0][4] = T5[4][4];
                                                TX.T[1][0] = T5[0][3]; TX.T[1][1] = T5[1][3]; TX.T[1][2] = T5[2][3]; TX.T[1][3] = T5[3][3]; TX.T[1][4] = T5[4][3];
                                                TX.T[2][0] = T5[0][2]; TX.T[2][1] = T5[1][2]; TX.T[2][2] = T5[2][2]; TX.T[2][3] = T5[3][2]; TX.T[2][4] = T5[4][2];
                                                TX.T[3][0] = T5[0][1]; TX.T[3][1] = T5[1][1]; TX.T[3][2] = T5[2][1]; TX.T[3][3] = T5[3][1]; TX.T[3][4] = T5[4][1];
                                                TX.T[4][0] = T5[0][0]; TX.T[4][1] = T5[1][0]; TX.T[4][2] = T5[2][0]; TX.T[4][3] = T5[3][0]; TX.T[4][4] = T5[4][0];
                                                OpMatrixDitherX.push_back(TX);
                                            }
                                            break;
                                        case 8: // Rotate counter clockwise
                                            {
                                                TX.Colors = NumColors;
                                                TX.T[0][0] = T5[4][0]; TX.T[0][1] = T5[3][0]; TX.T[0][2] = T5[2][0]; TX.T[0][3] = T5[1][0]; TX.T[0][4] = T5[0][0];
                                                TX.T[1][0] = T5[4][1]; TX.T[1][1] = T5[3][1]; TX.T[1][2] = T5[2][1]; TX.T[1][3] = T5[1][1]; TX.T[1][4] = T5[0][1];
                                                TX.T[2][0] = T5[4][2]; TX.T[2][1] = T5[3][2]; TX.T[2][2] = T5[2][2]; TX.T[2][3] = T5[1][2]; TX.T[2][4] = T5[0][2];
                                                TX.T[3][0] = T5[4][3]; TX.T[3][1] = T5[3][3]; TX.T[3][2] = T5[2][3]; TX.T[3][3] = T5[1][3]; TX.T[3][4] = T5[0][3];
                                                TX.T[4][0] = T5[4][4]; TX.T[4][1] = T5[3][4]; TX.T[4][2] = T5[2][4]; TX.T[4][3] = T5[1][4]; TX.T[4][4] = T5[0][4];
                                                OpMatrixDitherX.push_back(TX);
                                            }
                                            break;
                                    }
                                }
                            }
                        }
                        break;
                    case 4: // Resizing
                        {
                            OpMatrixX = new uchar[17];
                            if (TransformItem_.Trans4Type == 0)
                            {
                                OpMatrixX[0] = TransformItem_.Trans4Size;
                            }
                            if (TransformItem_.Trans4Type == 1)
                            {
                                OpMatrixX[0] = TransformItem_.Trans4Scale + 3;
                                OpMatrixX[5] = (TransformItem_.Trans4Channels) ? 1 : 0;
                            }
                            if (TransformItem_.Trans4Type == 2)
                            {
                                if (TransformItem_.Trans4LcdOp >= 2)
                                {
                                    OpMatrixX[0] = 12;
                                    if (TransformItem_.Trans4LcdInterpolation)
                                    {
                                        OpMatrixX[0] += 100;
                                    }
                                    OpMatrixX[5] = TransformItem_.Trans4LcdOp;
                                }
                                else
                                {
                                    OpMatrixX[0] = 11;
                                    OpMatrixX[5] = TransformItem_.Trans4LcdOp;
                                    if (TransformItem_.Trans4LcdInterpolation)
                                    {
                                        OpMatrixX[5] += 2;
                                    }
                                }
                                OpMatrixX[6] = TransformItem_.Trans4LcdType;
                                OpMatrixX[8] = (TransformItem_.Trans4LcdWeightR >> 8);
                                OpMatrixX[9] = (TransformItem_.Trans4LcdWeightR & 255);
                                OpMatrixX[10] = (TransformItem_.Trans4LcdWeightG >> 8);
                                OpMatrixX[11] = (TransformItem_.Trans4LcdWeightG & 255);
                                OpMatrixX[12] = (TransformItem_.Trans4LcdWeightB >> 8);
                                OpMatrixX[13] = (TransformItem_.Trans4LcdWeightB & 255);

                                OpMatrixX[14] = (TransformItem_.Trans4LcdChromaB > 0) ? (TransformItem_.Trans4LcdChromaB * 2 - 1) : 0;
                                OpMatrixX[15] = (TransformItem_.Trans4LcdChromaV > 0) ? (TransformItem_.Trans4LcdChromaV * 2 - 1) : 0;
                                OpMatrixX[16] = (TransformItem_.Trans4LcdChromaX > 0) ? (TransformItem_.Trans4LcdChromaX * 2 - 1) : 0;

                                if ((TransformItem_.Trans4LcdWeightR < 0) || (TransformItem_.Trans4LcdWeightG < 0) || (TransformItem_.Trans4LcdWeightB < 0) || ((TransformItem_.Trans4LcdWeightR + TransformItem_.Trans4LcdWeightG + TransformItem_.Trans4LcdWeightB) == 0))
                                {
                                    OpMatrixX[8] = 0;
                                    OpMatrixX[9] = 1;
                                    OpMatrixX[10] = 0;
                                    OpMatrixX[11] = 1;
                                    OpMatrixX[12] = 0;
                                    OpMatrixX[13] = 1;
                                }
                            }

                            OpMatrixX[1] = TransformItem_.Trans4Size1W;
                            OpMatrixX[2] = TransformItem_.Trans4Size2W;
                            OpMatrixX[3] = TransformItem_.Trans4Size1H;
                            OpMatrixX[4] = TransformItem_.Trans4Size2H;

                            if ((OpMatrixX[0] == 3) || (OpMatrixX[0] == 5) || (OpMatrixX[0] == 6))
                            {
                                OpMatrixX[1] = 2;
                                OpMatrixX[2] = 1;
                                OpMatrixX[3] = 2;
                                OpMatrixX[4] = 1;
                            }
                            if ((OpMatrixX[0] == 4) || (OpMatrixX[0] == 7) || (OpMatrixX[0] == 12) || (OpMatrixX[0] == 112))
                            {
                                OpMatrixX[1] = 3;
                                OpMatrixX[2] = 1;
                                OpMatrixX[3] = 3;
                                OpMatrixX[4] = 1;
                            }
                            if ((OpMatrixX[0] == 8))
                            {
                                OpMatrixX[1] = 4;
                                OpMatrixX[2] = 1;
                                OpMatrixX[3] = 4;
                                OpMatrixX[4] = 1;
                            }
                            if ((OpMatrixX[0] == 11))
                            {
                                OpMatrixX[1] = 1;
                                OpMatrixX[2] = 3;
                                OpMatrixX[3] = 1;
                                OpMatrixX[4] = 3;
                            }

                            // Resize 1:1 x 1:1 will not included on transform
                            if ((TransformItem_.Trans4Type == 0) && (TransformItem_.Trans4Size1W == TransformItem_.Trans4Size2W) && (TransformItem_.Trans4Size1H == TransformItem_.Trans4Size2H))
                            {
                                AddItem = false;
                            }
                        }
                        break;
                    case 5: // Flipping/rotating
                        {
                            OpMatrixX = new uchar[1];
                            OpMatrixX[0] = TransformItem_.Trans5Rotate;
                        }
                        break;
                }

                if (AddItem)
                {
                    LastItem++;
                    OpType.push_back(OpTypeX);
                    OpMatrix.push_back(OpMatrixX);
                    OpMatrixR.push_back(OpMatrixRX);
                    OpMatrixG.push_back(OpMatrixGX);
                    OpMatrixB.push_back(OpMatrixBX);
                    OpMatrixIR.push_back(OpMatrixIRX);
                    OpMatrixIG.push_back(OpMatrixIGX);
                    OpMatrixIB.push_back(OpMatrixIBX);
                    OpMatrixDither.push_back(OpMatrixDitherX);
                    LastOpType = OpTypeX;
                }


                if (OpTypeX == 4)
                {
                    // Scale4x means Scale2x twice
                    if (OpMatrixX[0] == 5)
                    {
                        OpMatrixX[0] = 3;

                        OpMatrixX = new uchar[6];
                        OpMatrixX[0] = 3;
                        OpMatrixX[1] = 2;
                        OpMatrixX[2] = 1;
                        OpMatrixX[3] = 2;
                        OpMatrixX[4] = 1;
                        OpMatrixX[5] = OpMatrix[OpMatrix.size() - 1][5];
                        LastItem++;
                        OpType.push_back(OpTypeX);
                        OpMatrix.push_back(OpMatrixX);
                        OpMatrixR.push_back(OpMatrixRX);
                        OpMatrixG.push_back(OpMatrixGX);
                        OpMatrixB.push_back(OpMatrixBX);
                        OpMatrixIR.push_back(OpMatrixIRX);
                        OpMatrixIG.push_back(OpMatrixIGX);
                        OpMatrixIB.push_back(OpMatrixIBX);
                        OpMatrixDither.push_back(OpMatrixDitherX);
                        LastOpType = OpTypeX;
                    }


                    // Add interpolation after LCD decomposition
                    if (OpMatrixX[0] == 112)
                    {
                        OpMatrixX[0] = 12;
                        bool VerticalLayout = OpMatrixX[6] > 1;
                        OpMatrixX = new uchar[1];
                        OpMatrixX[0] = VerticalLayout ? 1 : 0;
                        OpTypeX = 41;
                        LastItem++;
                        OpType.push_back(OpTypeX);
                        OpMatrix.push_back(OpMatrixX);
                        OpMatrixR.push_back(OpMatrixRX);
                        OpMatrixG.push_back(OpMatrixGX);
                        OpMatrixB.push_back(OpMatrixBX);
                        OpMatrixIR.push_back(OpMatrixIRX);
                        OpMatrixIG.push_back(OpMatrixIGX);
                        OpMatrixIB.push_back(OpMatrixIBX);
                        OpMatrixDither.push_back(OpMatrixDitherX);
                        LastOpType = OpTypeX;
                    }
                }

            }
        }

        if (LastOpType == 3)
        {
            vector<DitherMatrixElement> OpMatrixDitherX;
            OpType.push_back(32);
            OpMatrix.push_back(NULL);
            OpMatrixR.push_back(NULL);
            OpMatrixG.push_back(NULL);
            OpMatrixB.push_back(NULL);
            OpMatrixIR.push_back(new int[1]);
            OpMatrixIG.push_back(NULL);
            OpMatrixIB.push_back(NULL);
            OpMatrixDither.push_back(OpMatrixDitherX);
        }
    }
}

///
/// \brief PicThread::ReInit - Creating image structures according transform options
///
void PicThread::ReInit()
{
    int PipeI, PipeI_, OpI;
    int PipeCount_ = Max(1, PipeCount);
    if (ThrPicLines != NULL)
    {
        delete[] ThrMinY;
        delete[] ThrMaxY;
        delete[] ThrPicLines;
        delete[] ThrLineDiv;
        delete[] ThrStartPtr;
        delete[] ThrMultiThread;
        ThrPicLines = NULL;
    }
    if (BmpBuf != NULL)
    {
        for (PipeI = 0; PipeI < BmpBufN; PipeI++)
        {
            if ((PipeI % OpC1) > 0)
            {
                delete[] BmpBuf[PipeI];
                if (BmpBufIX_[PipeI] != NULL)
                {
                    delete[] BmpBufIX_[PipeI];
                }
            }
        }
        delete[] BmpBuf;
        delete[] BmpBufIX_;

        delete[] BmpBufW;
        delete[] BmpBufH;
        BmpBufIUnit = 0;
        BmpBufIN = 0;
        BmpBufN = 0;
        BmpBuf = NULL;
    }


    PicW = Settings_->PicW;
    PicH = Settings_->PicH;
    PicWDisp = PicW;
    PicHDisp = PicH;
    PicWMax = PicW;
    PicHMax = PicW;


    OpC = OpType.size();
    OpC1 = OpC + 1;
    BmpBufW = new int[OpC1];
    BmpBufH = new int[OpC1];
    BmpBufW[0] = PicWDisp;
    BmpBufH[0] = PicHDisp;
    if (OpC > 0)
    {
        ThrMinY = new int[(OpC + 2) << MaxThreadCountBit];
        ThrMaxY = new int[(OpC + 2) << MaxThreadCountBit];
        ThrStartPtr = new int[(OpC + 2) << MaxThreadCountBit];
        ThrLineDiv = new int[OpC + 2];
        ThrPicLines = new int[OpC + 2];
        ThrMultiThread = new uchar[OpC + 2];
        for (OpI = 1; OpI <= OpC; OpI++)
        {
            BmpBufW[OpI] = BmpBufW[OpI - 1];
            BmpBufH[OpI] = BmpBufH[OpI - 1];
            if (OpType[OpI - 1] == 4)
            {
                int FactorW1 = OpMatrix[OpI - 1][1];
                int FactorW2 = OpMatrix[OpI - 1][2];
                int FactorH1 = OpMatrix[OpI - 1][3];
                int FactorH2 = OpMatrix[OpI - 1][4];
                BmpBufW[OpI] = BmpBufW[OpI] * FactorW1;
                BmpBufW[OpI] = BmpBufW[OpI] / FactorW2;
                BmpBufH[OpI] = BmpBufH[OpI] * FactorH1;
                BmpBufH[OpI] = BmpBufH[OpI] / FactorH2;
            }
            if (OpType[OpI - 1] == 5)
            {
                if (OpMatrix[OpI - 1][0] >= 4)
                {
                    int Temp = BmpBufW[OpI];
                    BmpBufW[OpI] = BmpBufH[OpI];
                    BmpBufH[OpI] = Temp;
                }
            }
            PicWMax = Max(PicWMax, BmpBufW[OpI]);
            PicHMax = Max(PicHMax, BmpBufH[OpI]);
        }
        PicWDisp = BmpBufW[OpC];
        PicHDisp = BmpBufH[OpC];


        int P, PP;
        for (OpI = 0; OpI < OpC; OpI++)
        {
            ThrMultiThread[OpI] = 1;
            if (OpType[OpI] == 5)
            {
                if (OpMatrix[OpI][0] >= 4)
                {
                    ThrMultiThread[OpI] = 0;
                }
            }
            ThrLineDiv[OpI] = 1;
            if (OpType[OpI] == 4)
            {
                int LineDivOpt = OpMatrix[OpI][0];
                if ((LineDivOpt == 3) || (LineDivOpt == 5) || (LineDivOpt == 6))
                {
                    ThrLineDiv[OpI] = 2;
                }
                if ((LineDivOpt == 4) || (LineDivOpt == 7) || (LineDivOpt == 12))
                {
                    ThrLineDiv[OpI] = 3;
                }
                if ((LineDivOpt == 8))
                {
                    ThrLineDiv[OpI] = 4;
                }
            }
            PP = (OpI << MaxThreadCountBit);
            for (P = 1; P <= PicThreads; P++)
            {
                if (P == 1)
                {
                    ThrMinY[PP + P] = 0;
                }
                else
                {
                    ThrMinY[PP + P] = ThrMaxY[PP + P - 1];
                }
                ThrMaxY[PP + P] = (BmpBufH[OpI + 1] * P) / (PicThreads * ThrLineDiv[OpI]);
                ThrStartPtr[PP + P] = ThrMinY[PP + P] * (BmpBufW[OpI + 1] << 2) * ThrLineDiv[OpI];
            }
            ThrStartPtr[PP + 1] = 0;
            ThrPicLines[OpI] = BmpBufH[OpI + 1] / ThrLineDiv[OpI];
            ThrMinY[PP + 1] = 0;
            ThrMaxY[PP + PicThreads] = ThrPicLines[OpI];
        }
    }

    PicRawSizeDisp = (PicWDisp * PicHDisp) << 2;
    if (PicRawDummyDisp != NULL)
    {
        delete[] PicRawDummyDisp;
    }
    PicRawDummyDisp = new uchar[PicRawSizeDisp];
    for (int II = 0; II < PicRawSizeDisp; II++)
    {
        PicRawDummyDisp[II] = rand();
    }

    if (BmpDisp != NULL)
    {
        if ((PicWDisp != BmpDispW) || (PicHDisp != BmpDispH))
        {
            // The old BmpDisp object will be deleted in MainWindow::UpdatePixmap
            //delete BmpDisp;
            BmpDisp = NULL;
        }
    }
    if (BmpDisp == NULL)
    {
        BmpDisp = new QImage(PicWDisp, PicHDisp, QImage::Format_ARGB32);
        BmpDispRaw = BmpDisp->bits();
        BmpDispW = PicWDisp;
        BmpDispH = PicHDisp;
    }


    BmpBufIUnit = (PicWMax + PicBufIMargin + PicBufIMargin) * (PicHMax + PicBufIMargin + PicBufIMargin);
    BmpBufIN = BmpBufIUnit * PipeCount_;

    int P = 0;
    BmpBufN = OpC1 * PipeCount_;
    BmpBuf = new uchar*[BmpBufN];
    BmpBufIX_ = new uint*[BmpBufN];
    if (OpC > 0)
    {
        for (PipeI = 0; PipeI < PipeCount_; PipeI++)
        {
            PipeI_ = PipeI * OpC1;
            BmpBuf[PipeI_] = PicRawDummyDisp;
            for (OpI = 0; OpI <= OpC; OpI++)
            {
                BmpBufIX_[PipeI_ + OpI] = NULL;
            }
            for (OpI = 1; OpI < OpC; OpI++)
            {
                BmpBuf[PipeI_ + OpI] = new uchar[(BmpBufW[OpI] * BmpBufH[OpI]) << 2];
            }
            BmpBuf[PipeI_ + OpC] = new uchar[PicRawSizeDisp];
            for (P = (PicRawSizeDisp - 1); P > 0; P -= 4)
            {
                BmpBuf[PipeI_ + OpC][P] = 255;
            }
        }

        // Creating temporary arrays for dedithering, every dedithering
        // transform (3) is preceded by 31 transform an followed by 32 transform
        bool OpDeditherSwap = false;
        int OpDeditherStart = 0;

        for (OpI = 0; OpI < OpC; OpI++)
        {
            if ((OpType[OpI] == 31) || (OpType[OpI] == 32))
            {
                int BufS = (BmpBufW[OpI] + PicBufIMargin + PicBufIMargin) * (BmpBufH[OpI] + PicBufIMargin + PicBufIMargin);
                for (PipeI = 0; PipeI < PipeCount_; PipeI++)
                {
                    int OpIP = OpI + (PipeI * OpC1);
                    BmpBufIX_[OpIP] = new uint[BufS];
                    for (int BufSI = 0; BufSI < BufS; BufSI++)
                    {
                        BmpBufIX_[OpIP][BufSI] = NullColor;
                    }
                }

                if (OpType[OpI] == 31)
                {
                    OpDeditherStart = OpI;
                }

                if (OpType[OpI] == 32)
                {
                    if (OpDeditherSwap)
                    {
                        OpMatrixIR[OpI][0] = OpI - OpDeditherStart;
                    }
                    else
                    {
                        OpMatrixIR[OpI][0] = 0;
                    }
                }

                OpDeditherSwap = true;
            }

            if (OpType[OpI] == 3)
            {
                int OpI_;
                OpI_ = OpI;
                while (OpType[OpI_] != 31)
                {
                    OpI_--;
                }
                if (OpDeditherSwap)
                {
                    OpMatrixIR[OpI][0] = OpI_;
                }
                else
                {
                    OpMatrixIR[OpI][1] = OpI_;
                }
                OpI_ = OpI;
                while (OpType[OpI_] != 32)
                {
                    OpI_++;
                }
                if (OpDeditherSwap)
                {
                    OpMatrixIR[OpI][1] = OpI_;
                }
                else
                {
                    OpMatrixIR[OpI][0] = OpI_;
                }
                OpDeditherSwap = !OpDeditherSwap;
            }
        }
    }
    else
    {
        for (PipeI = 0; PipeI < PipeCount_; PipeI++)
        {
            BmpBuf[PipeI] = PicRawDummyDisp;
            BmpBufIX_[PipeI] = NULL;
        }
    }


    if (DelayLineBuf != NULL)
    {
        delete[] DelayLineBuf;
        DelayLineBuf = NULL;
    }
    if (DelayLineFileObj != NULL)
    {
        if (DelayLineFileObj->is_open())
        {
            DelayLineFileObj->close();
            remove(DelayLineFileName.c_str());
        }
        delete DelayLineFileObj;
        DelayLineFileObj = NULL;
    }
    DelayLineCount = Settings_->DelayLineCount;
    DelayLinePointer = 0;
    DelayLineI = false;
    DelayLineO = false;
    if (DelayLineCount > 0)
    {
        if ((PicW * PicH) <= (PicWDisp * PicHDisp))
        {
            DelayLineI = true;
            DelayLineChunkSize = PicW * PicH * 4;
        }
        else
        {
            DelayLineO = true;
            DelayLineChunkSize = PicWDisp * PicHDisp * 4;
        }
        if (Settings_->DelayLineFileName != "")
        {
            DelayLineFileName = Settings_->DelayLineFileName;
            DelayLineFile = true;
            DelayLineFileObj = new fstream(DelayLineFileName, ios::out | ios::binary);
            DelayLineBuf = new uchar[DelayLineChunkSize];
            for (int I = 0; I < (DelayLineCount + 1); I++)
            {
                for (int II = 0; II < DelayLineChunkSize; II++)
                {
                    DelayLineBuf[II] = rand();
                }
                DelayLineFileObj->write((char*)DelayLineBuf, DelayLineChunkSize);
            }
            DelayLineFileObj->close();
            delete DelayLineFileObj;
            DelayLineFileObj = new fstream(DelayLineFileName, ios::in | ios::out | ios::binary);
            delete[] DelayLineBuf;
            DelayLineBuf = NULL;
        }
        else
        {
            DelayLineFile = false;
            int DelayLineBufL = (DelayLineCount + 1) * DelayLineChunkSize;
            DelayLineBuf = new uchar[DelayLineBufL];
            for (int II = 0; II < DelayLineBufL; II++)
            {
                DelayLineBuf[II] = rand();
            }
        }
    }
    DelayLinePointerCount = (DelayLineCount + 1) * DelayLineChunkSize;
}

void PicThread::DelayLineProcess(uchar *Data)
{
    if (DelayLineFile)
    {
        DelayLineFileObj->seekp(DelayLinePointer);
        DelayLineFileObj->write((char*)Data, DelayLineChunkSize);
        DelayLinePointer += DelayLineChunkSize;
        if (DelayLinePointer == DelayLinePointerCount)
        {
            DelayLinePointer = 0;
        }
        DelayLineFileObj->seekg(DelayLinePointer);
        DelayLineFileObj->read((char*)Data, DelayLineChunkSize);
    }
    else
    {
        memcpy(DelayLineBuf + DelayLinePointer, Data, DelayLineChunkSize);
        DelayLinePointer += DelayLineChunkSize;
        if (DelayLinePointer == DelayLinePointerCount)
        {
            DelayLinePointer = 0;
        }
        memcpy(Data, DelayLineBuf + DelayLinePointer, DelayLineChunkSize);
    }
}

void PicThread::WorkLoop()
{
    if (PicRawDummyDisp != NULL)
    {
        delete[] PicRawDummyDisp;
        PicRawDummyDisp = NULL;
    }

    OpLoad();
    Working = 1;
    FPS = 0;
    QScreen * Scr = QGuiApplication::primaryScreen();
    int ScrOffsetX = Scr->geometry().x();
    int ScrOffsetY = Scr->geometry().y();
    if (!Scr)
    {
        return;
    }

    QImage BmpI_;
    QImage BmpI__[MaxThreadCount];

    ThrPicLines = NULL;


    Settings_->NeedRecalc = true;
    NeedReInit = true;

    std::thread * PipeThr[MaxThreadCount];
    for (int I = 0; I < MaxThreadCount; I++)
    {
        PipeThr[I] = NULL;
    }


    bool DispBefore = (PipeCount > 0);
    bool DispAfter = (PipeCount < 0);
    if (PipeCount < 0)
    {
        PipeCount = 0 - PipeCount;
    }

    int PipeI = 0;
    int PipeI_ = 0;
    int PipeI__ = 0;

    int MouseX, MouseY, PicX, PicY;
    QPoint MouseP;

    if (PipeCount > 0)
    {
        while (Working)
        {
            // Reinitialization after start or source image resize
            if (NeedReInit)
            {
                if (Settings_->MTX.try_lock())
                {
                    PictureScreen->ImgX = NULL;
                    for (int I = 0; I < PipeCount; I++)
                    {
                        if (PipeThr[I] != NULL)
                        {
                            PipeThr[I]->join();
                            delete PipeThr[I];
                            PipeThr[I] = NULL;
                        }
                    }
                    ReInit();
                    Settings_->NeedRecalc = true;
                    NeedReInit = false;
                    for (int I = 0; I < PipeCount; I++)
                    {
                        if (DispBefore || (DispAfter && (I != PipeI)))
                        {
                            PipeThr[I] = new std::thread(&PicThread::ProcessThreadDummy, this);
                        }
                    }
                    Settings_->MTX.unlock();
                }
            }

            if (!NeedReInit)
            {
                // Preparing to source picture capture
                MouseP = QCursor::pos();
                MouseX = MouseP.x();
                MouseY = MouseP.y();
                if (Settings_->FollowMouse)
                {
                    PicX = MouseX - (PicW >> 1);
                    PicY = MouseY - (PicH >> 1);
                    if (PicX < Settings_->BoundX1)
                    {
                        PicX = Settings_->BoundX1;
                    }
                    if (PicX > (Settings_->BoundX2 - PicW))
                    {
                        PicX = (Settings_->BoundX2 - PicW);
                    }
                    if (PicY < Settings_->BoundY1)
                    {
                        PicY = Settings_->BoundY1;
                    }
                    if (PicY > (Settings_->BoundY2 - PicH))
                    {
                        PicY = (Settings_->BoundY2 - PicH);
                    }
                    Settings_->PicX = PicX;
                    Settings_->PicY = PicY;
                }
                else
                {
                    PicX = Settings_->PicX;
                    PicY = Settings_->PicY;
                }

                // Displaying destination picture - before capturing
                if (DispBefore)
                {
                    PipeThr[PipeI]->join();
                    if (DelayLineO)
                    {
                        DelayLineProcess(BmpBuf[PipeI_ + OpC]);
                    }
                    memcpy(BmpDispRaw, BmpBuf[PipeI_ + OpC], PicRawSizeDisp);
                    emit UpdatePixmap(BmpDisp);
                    delete PipeThr[PipeI];
                    PipeThr[PipeI] = NULL;
                }

                // Capturing source picture
                if (Settings_->Throttle > 0)
                {
                    msleep(Settings_->Throttle);
                }
                if (Settings_->_PicSrcNet)
                {
                    BmpI__[PipeI] = PicNetwork_->PicRecv(PicW, PicH);
                    if (PicNetwork_->RealPicDiff)
                    {
                        Settings_->PicW = PicNetwork_->RealPicW;
                        Settings_->PicH = PicNetwork_->RealPicH;
                        NeedReInit = true;
                        emit PicSetRefresh();
                    }
                }
                else
                {
                    BmpI__[PipeI] = Scr->grabWindow(0, PicX - ScrOffsetX, PicY - ScrOffsetY, PicW, PicH).toImage();
                }
                if (Settings_->Throttle < 0)
                {
                    msleep(0 - Settings_->Throttle);
                }
                BmpBuf[PipeI_] = BmpI__[PipeI].bits();
                if (DelayLineI)
                {
                    DelayLineProcess(BmpBuf[PipeI_]);
                }

                PicX_[PipeI] = PicX;
                PicY_[PipeI] = PicY;
                MouseX_[PipeI] = MouseX;
                MouseY_[PipeI] = MouseY;

                PipeThr[PipeI] = new std::thread(&PicThread::ProcessThread, this, PipeI, PipeI_);

                PipeI++;
                if (PipeI == PipeCount)
                {
                    PipeI = 0;
                    PipeI_ = 0;
                    PipeI__ = 0;
                }
                else
                {
                    PipeI_ += OpC1;
                    PipeI__ += BmpBufIUnit;
                }

                // Displaying destination picture - after capturing
                if (DispAfter)
                {
                    PipeThr[PipeI]->join();
                    if (DelayLineO)
                    {
                        DelayLineProcess(BmpBuf[PipeI_ + OpC]);
                    }
                    memcpy(BmpDispRaw, BmpBuf[PipeI_ + OpC], PicRawSizeDisp);
                    emit UpdatePixmap(BmpDisp);
                    delete PipeThr[PipeI];
                    PipeThr[PipeI] = NULL;
                }
            }


            FPS++;
        }

        for (int I = 0; I < PipeCount; I++)
        {
            if (PipeThr[I] != NULL)
            {
                PipeThr[I]->join();
                delete PipeThr[I];
            }
        }
    }
    else
    {
        while (Working)
        {
            // Reinitializing structure after restart or source picture resize
            if (NeedReInit)
            {
                if (Settings_->MTX.try_lock())
                {
                    PictureScreen->ImgX = NULL;
                    ReInit();
                    Settings_->NeedRecalc = true;
                    NeedReInit = false;
                    Settings_->MTX.unlock();
                }
            }

            if (!NeedReInit)
            {
                // Preparing to source picture capture
                MouseP = QCursor::pos();
                MouseX = MouseP.x();
                MouseY = MouseP.y();
                if (Settings_->FollowMouse)
                {
                    PicX = MouseX - (PicW >> 1);
                    PicY = MouseY - (PicH >> 1);
                    if (PicX < Settings_->BoundX1)
                    {
                        PicX = Settings_->BoundX1;
                    }
                    if (PicX > (Settings_->BoundX2 - PicW))
                    {
                        PicX = (Settings_->BoundX2 - PicW);
                    }
                    if (PicY < Settings_->BoundY1)
                    {
                        PicY = Settings_->BoundY1;
                    }
                    if (PicY > (Settings_->BoundY2 - PicH))
                    {
                        PicY = (Settings_->BoundY2 - PicH);
                    }
                    Settings_->PicX = PicX;
                    Settings_->PicY = PicY;
                }
                else
                {
                    PicX = Settings_->PicX;
                    PicY = Settings_->PicY;
                }

                // Capturing source picture
                if (Settings_->Throttle > 0)
                {
                    msleep(Settings_->Throttle);
                }
                if (Settings_->_PicSrcNet)
                {
                    BmpI_ = PicNetwork_->PicRecv(PicW, PicH);
                    if (PicNetwork_->RealPicDiff)
                    {
                        Settings_->PicW = PicNetwork_->RealPicW;
                        Settings_->PicH = PicNetwork_->RealPicH;
                        NeedReInit = true;
                        emit PicSetRefresh();
                    }
                }
                else
                {
                    BmpI_ = Scr->grabWindow(0, PicX - ScrOffsetX, PicY - ScrOffsetY, PicW, PicH).toImage();
                }
                if (Settings_->Throttle < 0)
                {
                    msleep(0 - Settings_->Throttle);
                }
                BmpBuf[0] = BmpI_.bits();
                if (DelayLineI)
                {
                    DelayLineProcess(BmpBuf[0]);
                }
                PicX_[0] = PicX;
                PicY_[0] = PicY;
                MouseX_[0] = MouseX;
                MouseY_[0] = MouseY;

                ProcessThread(0, 0);

                // Displaying destination picture
                if (DelayLineO)
                {
                    DelayLineProcess(BmpBuf[OpC]);
                }
                memcpy(BmpDispRaw, BmpBuf[OpC], PicRawSizeDisp);
                emit UpdatePixmap(BmpDisp);
            }


            FPS++;
        }
    }

    if (ThrPicLines != NULL)
    {
        delete[] ThrLineDiv;
        delete[] ThrStartPtr;
        delete[] ThrPicLines;
        delete[] ThrMinY;
        delete[] ThrMaxY;
        ThrPicLines = NULL;
    }

    BmpDisp = NULL;
    emit UpdatePixmap(BmpDisp);

    if (PicRawDummyDisp != NULL)
    {
        delete[] PicRawDummyDisp;
        PicRawDummyDisp = NULL;
    }

    if (DelayLineFileObj != NULL)
    {
        if (DelayLineFileObj->is_open())
        {
            DelayLineFileObj->close();
            remove(DelayLineFileName.c_str());
        }
        delete DelayLineFileObj;
        DelayLineFileObj = NULL;
    }
}

void PicThread::ProcessThreadDummy()
{

}

void PicThread::ProcessThread(int PipeI, int PipeI_)
{
    // Drawing mouse pointer
    if ((!Settings_->_PicSrcNet) && (Settings_->MousePointerType != 0))
    {
        int MouseX = MouseX_[PipeI];
        int MouseY = MouseY_[PipeI];
        int PicX = PicX_[PipeI];
        int PicY = PicY_[PipeI];
        int PicWPtr = PicW << 2;
        uchar * BmpBufCur = BmpBuf[PipeI_];
        int MouseThickness = Settings_->MouseThickness;
        int MouseSize = Settings_->MouseSize;
        int MouseMargin = MouseSize + MouseThickness;
        if ((MouseX >= (PicX - MouseMargin)) && (MouseY >= (PicY - MouseMargin)) && (MouseX < (PicX + PicW + MouseMargin)) && (MouseY < (PicY + PicH + MouseMargin)))
        {
            MouseX = (MouseX - PicX) << 2;
            MouseY = (MouseY - PicY) * PicWPtr;
            int Step = MouseMargin << 2;
            int MouseX1 = Max(0, MouseX - Step);
            int MouseX2 = Min((PicW - 1) << 2, MouseX + Step);
            Step = MouseMargin * PicWPtr;
            int MouseY1 = Max(0, MouseY - Step);
            int MouseY2 = Min((PicH - 1) * PicWPtr, MouseY + Step);
            int MouseYL1 = Max(PicWPtr * (0 - 1 - MouseThickness), MouseY);
            int MouseYL2 = Min(PicWPtr * (PicH + MouseThickness), MouseY);


            int MouseThickness2H = MouseThickness << 2;
            int MouseThickness1H = 0 - MouseThickness2H;
            int MouseThicknessL = MouseThickness * PicWPtr;
            int MouseThickness2V = MouseThicknessL;
            int MouseThickness1V = 0 - MouseThicknessL;

            while ((MouseX + MouseThickness1H) < 0)
            {
                MouseThickness1H += 4;
            }
            while ((MouseX + MouseThickness2H) >= PicWPtr)
            {
                MouseThickness2H -= 4;
            }
            while ((MouseY + MouseThickness1V) < 0)
            {
                MouseThickness1V += PicWPtr;
            }
            while ((MouseY + MouseThickness2V) >= (PicWPtr * PicH))
            {
                MouseThickness2V -= PicWPtr;
            }

            int III, IIII;

            switch (Settings_->MousePointerType)
            {
                case 1:
                    for (III = (MouseX1 + MouseY); III <= (MouseX2 + MouseY); III += 4)
                    {
                        for (IIII = MouseThickness1V; IIII <= MouseThickness2V; IIII += PicWPtr)
                        {
                            BmpBufCur[III + IIII + 0] = (BmpBufCur[III + IIII + 0] >= 128) ? 0 : 255;
                            BmpBufCur[III + IIII + 1] = (BmpBufCur[III + IIII + 1] >= 128) ? 0 : 255;
                            BmpBufCur[III + IIII + 2] = (BmpBufCur[III + IIII + 2] >= 128) ? 0 : 255;
                        }
                    }
                    for (III = (MouseY1 + MouseX); III < (MouseYL2 + MouseX - MouseThicknessL); III += PicWPtr)
                    {
                        for (IIII = MouseThickness1H; IIII <= MouseThickness2H; IIII += 4)
                        {
                            BmpBufCur[III + IIII + 0] = (BmpBufCur[III + IIII + 0] >= 128) ? 0 : 255;
                            BmpBufCur[III + IIII + 1] = (BmpBufCur[III + IIII + 1] >= 128) ? 0 : 255;
                            BmpBufCur[III + IIII + 2] = (BmpBufCur[III + IIII + 2] >= 128) ? 0 : 255;
                        }
                    }
                    for (III = (MouseYL1 + MouseX + PicWPtr + MouseThicknessL); III <= (MouseY2 + MouseX); III += PicWPtr)
                    {
                        for (IIII = MouseThickness1H; IIII <= MouseThickness2H; IIII += 4)
                        {
                            BmpBufCur[III + IIII + 0] = (BmpBufCur[III + IIII + 0] >= 128) ? 0 : 255;
                            BmpBufCur[III + IIII + 1] = (BmpBufCur[III + IIII + 1] >= 128) ? 0 : 255;
                            BmpBufCur[III + IIII + 2] = (BmpBufCur[III + IIII + 2] >= 128) ? 0 : 255;
                        }
                    }
                    break;
                case 2:
                    for (III = (MouseX1 + MouseY); III <= (MouseX2 + MouseY); III += 4)
                    {
                        for (IIII = MouseThickness1V; IIII <= MouseThickness2V; IIII += PicWPtr)
                        {
                            BmpBufCur[III + IIII + 0] = 255 - BmpBufCur[III + IIII + 0];
                            BmpBufCur[III + IIII + 1] = 255 - BmpBufCur[III + IIII + 1];
                            BmpBufCur[III + IIII + 2] = 255 - BmpBufCur[III + IIII + 2];
                        }
                    }
                    for (III = (MouseY1 + MouseX); III < (MouseYL2 + MouseX - MouseThicknessL); III += PicWPtr)
                    {
                        for (IIII = MouseThickness1H; IIII <= MouseThickness2H; IIII += 4)
                        {
                            BmpBufCur[III + IIII + 0] = 255 - BmpBufCur[III + IIII + 0];
                            BmpBufCur[III + IIII + 1] = 255 - BmpBufCur[III + IIII + 1];
                            BmpBufCur[III + IIII + 2] = 255 - BmpBufCur[III + IIII + 2];
                        }
                    }
                    for (III = (MouseYL1 + MouseX + PicWPtr + MouseThicknessL); III <= (MouseY2 + MouseX); III += PicWPtr)
                    {
                        for (IIII = MouseThickness1H; IIII <= MouseThickness2H; IIII += 4)
                        {
                            BmpBufCur[III + IIII + 0] = 255 - BmpBufCur[III + IIII + 0];
                            BmpBufCur[III + IIII + 1] = 255 - BmpBufCur[III + IIII + 1];
                            BmpBufCur[III + IIII + 2] = 255 - BmpBufCur[III + IIII + 2];
                        }
                    }
                    break;
            }

        }
    }

    // Picture processing
    if (OpC > 0)
    {
        std::thread * Thr[MaxThreadCount];
        int P, PP;
        for (int OpI = 0; OpI < OpC; OpI++)
        {
            if ((PicThreads > 1) && ThrMultiThread[OpI])
            {
                // Processing in threads, every thread process different picture fragment
#ifdef DebugThreadSeq
                for (P = PicThreads; P > 0; P--)
                {
                    PP = (OpI << MaxThreadCountBit) + P;
                    ProcessPicture(ThrMinY[PP], ThrMaxY[PP], ThrStartPtr[PP], OpI, PipeI_);
                }
#else
                for (P = PicThreads; P > 0; P--)
                {
                    PP = (OpI << MaxThreadCountBit) + P;
                    Thr[P] = new std::thread(&PicThread::ProcessPicture, this, ThrMinY[PP], ThrMaxY[PP], ThrStartPtr[PP], OpI, PipeI_);
                }
                for (P = PicThreads; P > 0; P--)
                {
                    Thr[P]->join();
                    delete Thr[P];
                }
#endif
            }
            else
            {
                // Processing without threads
                ProcessPicture(0, ThrPicLines[OpI], 0, OpI, PipeI_);
            }
        }
    }
}

void PicThread::run()
{
    WorkLoop();
}

void PicThread::Stop()
{
    Working = 0;
}
