#include "picthread.h"

void PicThread::DelayLinePrepare()
{
    TextCapture_->TextState = false;
    GoogleConvert::Init();

    DelayLineAsyncDecimateC = Settings_->GoogleCloudDecimate;
    DelayLineAsyncDecimateI = 0;
    DelayLinePaintCmdTextId = 0;

    while (!DelayLineAsyncThreadRequest.empty())
    {
        DelayLineAsyncThreadRequest.pop();
    }

    if (DelayLineBuf != NULL)
    {
        delete[] DelayLineBuf;
        DelayLineBuf = NULL;
    }
    if (DelayLineId != NULL)
    {
        delete[] DelayLineId;
        DelayLineId = NULL;
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
    DelayLinePos = 0;
    DelayLinePointer = 0;
    DelayLineI = false;
    DelayLineO = false;
    if (DelayLineCount > 0)
    {
        DelayLineId = new int[DelayLineCount + 1];
        if (Settings_->DelayLineMode == 0)
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
        }
        if (Settings_->DelayLineMode == 1)
        {
            DelayLineI = true;
            DelayLineChunkSize = PicW * PicH * 4;
        }
        if (Settings_->DelayLineMode == 2)
        {
            DelayLineO = true;
            DelayLineChunkSize = PicWDisp * PicHDisp * 4;
        }
        if (Settings_->DelayLineFileName != "")
        {
            DelayLineFileName = Settings_->DelayLineFileName;
            DelayLineFile = true;
            DelayLineFileObj = new fstream(Eden::File(DelayLineFileName), ios::out | ios::binary);
            DelayLineBuf = new uchar[DelayLineChunkSize];
            for (int I = 0; I < (DelayLineCount + 1); I++)
            {
                DelayLineId[I] = 0;
                for (int II = 0; II < DelayLineChunkSize; II++)
                {
                    DelayLineBuf[II] = rand();
                }
                DelayLineFileObj->write((char*)DelayLineBuf, DelayLineChunkSize);
            }
            DelayLineFileObj->close();
            delete DelayLineFileObj;
            DelayLineFileObj = new fstream(Eden::File(DelayLineFileName), ios::in | ios::out | ios::binary);
            delete[] DelayLineBuf;
            DelayLineBuf = NULL;
        }
        else
        {
            DelayLineFile = false;
            int DelayLineBufL = (DelayLineCount + 1) * DelayLineChunkSize;
            DelayLineBuf = new uchar[DelayLineBufL];
            for (int I = 0; I < DelayLineBufL; I++)
            {
                DelayLineBuf[I] = rand();
            }
            for (int I = 0; I < (DelayLineCount + 1); I++)
            {
                DelayLineId[I] = 0;
            }
        }
    }
    DelayLineIdCounter = 1;

    if (DelayLineAsyncBitmapMaskMinX != NULL) { delete[] DelayLineAsyncBitmapMaskMinX; }
    if (DelayLineAsyncBitmapMaskMinX_R != NULL) { delete[] DelayLineAsyncBitmapMaskMinX_R; }
    if (DelayLineAsyncBitmapMaskMinX_G != NULL) { delete[] DelayLineAsyncBitmapMaskMinX_G; }
    if (DelayLineAsyncBitmapMaskMinX_B != NULL) { delete[] DelayLineAsyncBitmapMaskMinX_B; }

    if (DelayLineAsyncBitmapMaskMinY != NULL) { delete[] DelayLineAsyncBitmapMaskMinY; }
    if (DelayLineAsyncBitmapMaskMinY_R != NULL) { delete[] DelayLineAsyncBitmapMaskMinY_R; }
    if (DelayLineAsyncBitmapMaskMinY_G != NULL) { delete[] DelayLineAsyncBitmapMaskMinY_G; }
    if (DelayLineAsyncBitmapMaskMinY_B != NULL) { delete[] DelayLineAsyncBitmapMaskMinY_B; }

    if (DelayLineAsyncBitmapMaskMaxX != NULL) { delete[] DelayLineAsyncBitmapMaskMaxX; }
    if (DelayLineAsyncBitmapMaskMaxX_R != NULL) { delete[] DelayLineAsyncBitmapMaskMaxX_R; }
    if (DelayLineAsyncBitmapMaskMaxX_G != NULL) { delete[] DelayLineAsyncBitmapMaskMaxX_G; }
    if (DelayLineAsyncBitmapMaskMaxX_B != NULL) { delete[] DelayLineAsyncBitmapMaskMaxX_B; }

    if (DelayLineAsyncBitmapMaskMaxY != NULL) { delete[] DelayLineAsyncBitmapMaskMaxY; }
    if (DelayLineAsyncBitmapMaskMaxY_R != NULL) { delete[] DelayLineAsyncBitmapMaskMaxY_R; }
    if (DelayLineAsyncBitmapMaskMaxY_G != NULL) { delete[] DelayLineAsyncBitmapMaskMaxY_G; }
    if (DelayLineAsyncBitmapMaskMaxY_B != NULL) { delete[] DelayLineAsyncBitmapMaskMaxY_B; }

    DelayLineAsyncBitmapMaskMinX = new int[PicH];
    DelayLineAsyncBitmapMaskMinX_R = new int[PicH];
    DelayLineAsyncBitmapMaskMinX_G = new int[PicH];
    DelayLineAsyncBitmapMaskMinX_B = new int[PicH];

    DelayLineAsyncBitmapMaskMaxX = new int[PicH];
    DelayLineAsyncBitmapMaskMaxX_R = new int[PicH];
    DelayLineAsyncBitmapMaskMaxX_G = new int[PicH];
    DelayLineAsyncBitmapMaskMaxX_B = new int[PicH];

    DelayLineAsyncBitmapMaskMinY = new int[PicW];
    DelayLineAsyncBitmapMaskMinY_R = new int[PicW];
    DelayLineAsyncBitmapMaskMinY_G = new int[PicW];
    DelayLineAsyncBitmapMaskMinY_B = new int[PicW];

    DelayLineAsyncBitmapMaskMaxY = new int[PicW];
    DelayLineAsyncBitmapMaskMaxY_R = new int[PicW];
    DelayLineAsyncBitmapMaskMaxY_G = new int[PicW];
    DelayLineAsyncBitmapMaskMaxY_B = new int[PicW];
}

void PicThread::DelayLineCleanUp()
{
    DelayLineAsyncList.clear();

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

void PicThread::DelayLineProcess(uchar *Data)
{
    DelayLineAsyncEnd();
    DelayLineId[DelayLinePos] = DelayLineIdCounter;
    if (Settings_->GoogleCloudEnabled)
    {
        if (DelayLineAsyncDecimateI == 0)
        {
            bool CreateNew = true;
            int I;
            for (I = 0; I < DelayLineAsyncList.size(); I++)
            {
                if (DelayLineAsyncList[I].Pos < 0)
                {
                    DelayLineAsyncList[I].Id = DelayLineIdCounter;
                    DelayLineAsyncList[I].Pos = DelayLinePos;
                    memcpy(DelayLineAsyncList[I].Raw, Data, DelayLineChunkSize);
                    CreateNew = false;
                    DelayLineAsyncBegin(DelayLinePos, DelayLineIdCounter);
                    break;
                }
            }
            if (CreateNew)
            {
                I = DelayLineAsyncList.size();
                DelayLineAsyncDef DelayLineAsyncItem;
                DelayLineAsyncItem.RawImg = QImage(PicW, PicH, QImage::Format_ARGB32);
                DelayLineAsyncItem.Id = DelayLineIdCounter;
                DelayLineAsyncItem.Pos = DelayLinePos;
                DelayLineAsyncItem.Raw = DelayLineAsyncItem.RawImg.bits();
                memcpy(DelayLineAsyncItem.Raw, Data, DelayLineChunkSize);
                DelayLineAsyncList.push_back(DelayLineAsyncItem);
                DelayLineAsyncBegin(DelayLinePos, DelayLineIdCounter);
            }
        }
    }
    if (DelayLineFile)
    {
        DelayLineFileObj->seekp(DelayLinePointer);
        DelayLineFileObj->write((char*)Data, DelayLineChunkSize);
        DelayLinePos++;
        DelayLinePointer += DelayLineChunkSize;
        if (DelayLinePos == DelayLineCount)
        {
            DelayLinePos = 0;
            DelayLinePointer = 0;
        }
        DelayLineFileObj->seekg(DelayLinePointer);
        DelayLineFileObj->read((char*)Data, DelayLineChunkSize);
    }
    else
    {
        memcpy(DelayLineBuf + DelayLinePointer, Data, DelayLineChunkSize);
        DelayLinePos++;
        DelayLinePointer += DelayLineChunkSize;
        if (DelayLinePos == DelayLineCount)
        {
            DelayLinePos = 0;
            DelayLinePointer = 0;
        }
        memcpy(Data, DelayLineBuf + DelayLinePointer, DelayLineChunkSize);
    }
    DelayLineAsyncPaint(Data);

    DelayLineIdCounter++;
    DelayLineAsyncDecimateI++;
    if (DelayLineAsyncDecimateI >= DelayLineAsyncDecimateC)
    {
        DelayLineAsyncDecimateI = 0;
    }
}

void PicThread::DelayLineAsyncBegin(int Pos, int Id)
{
    QByteArray Raw;
    QBuffer Raw_(&Raw);
    int Idx = DelayLineAsyncBitmapIdx(Pos);
    if (Settings_->GoogleCloudImageQuality < 0)
    {
        DelayLineAsyncList[Idx].RawImg.save(&Raw_, "PNG", 100);
    }
    else
    {
        DelayLineAsyncList[Idx].RawImg.save(&Raw_, "JPEG", Settings_->GoogleCloudImageQuality);
    }

    QString JSON1 = "{\"requests\":[{\"features\":[{\"maxResults\":10,\"type\":\"TEXT_DETECTION\"}],\"image\":{\"content\": \"";
    QString JSON2 = "\"}}]}";

    DelayLineAsyncThreadData DelayLineAsyncThreadData_;
    DelayLineAsyncThreadData_.Type = 1;
    DelayLineAsyncThreadData_.Pos = Pos;
    DelayLineAsyncThreadData_.Id = Id;
    DelayLineAsyncThreadData_.Data = JSON1.toUtf8() + Raw.toBase64() + JSON2.toUtf8();
    DelayLineAsyncThreadData_.Url = QString("https://vision.googleapis.com/v1/images:annotate?key=") + Eden::ToQStr(Settings_->GoogleCloudKey);

    DelayLineAsyncThreadRequest.push(DelayLineAsyncThreadData_);
}

int PicThread::DelayLineAsyncBitmapIdx(int Pos)
{
    for (int I = 0; I < DelayLineAsyncList.size(); I++)
    {
        if (DelayLineAsyncList[I].Pos == Pos)
        {
            return I;
        }
    }
    return -1;
}


void PicThread::DelayLineAsyncBitmapFlush(int Idx)
{
    if (Idx < 0)
    {
        return;
    }
    DelayLineAsyncList[Idx].Pos = -1;
}

void PicThread::DelayLineAsyncEnd()
{
    while (DelayLineAsyncThreadResult.size() > 0)
    {
        if (Working)
        {
            DelayLineAsyncThreadData DelayLineAsyncThreadData_ = DelayLineAsyncThreadResult.front();

            switch (DelayLineAsyncThreadData_.Type)
            {
                case 1: // Text from picture
                    {
                        int OcrLevel = 1;
                        int AsyncIdx = DelayLineAsyncBitmapIdx(DelayLineAsyncThreadData_.Pos);


                        if (AsyncIdx >= 0)
                        {
                            uchar * BmpRaw = DelayLineAsyncList[AsyncIdx].Raw;

                            vector<DelayLineAsyncTextObjDef> DelayLineAsyncTextObjList;
                            int DelayLineAsyncTextObjNum[3];

                            DelayLineAsyncTextObjList.clear();
                            DelayLineAsyncTextObjNum[0] = 0;
                            DelayLineAsyncTextObjNum[1] = 0;
                            DelayLineAsyncTextObjNum[2] = 0;


                            int I1, I2, I3, I4, I5, I6;
                            QJsonDocument d = QJsonDocument::fromJson(DelayLineAsyncThreadData_.Data);
                            QJsonObject d_obj = d.object();
                            QJsonArray d_obj_resp = d_obj.value(QString("responses")).toArray();
                            for (I1 = 0; I1 < d_obj_resp.size(); I1++)
                            {
                                QJsonObject d_obj_resp_ = d_obj_resp[I1].toObject();
                                QJsonArray d_obj_resp_p = d_obj_resp_.value(QString("fullTextAnnotation")).toObject().value(QString("pages")).toArray();

                                for (I2 = 0; I2 < d_obj_resp_p.size(); I2++)
                                {
                                    QJsonObject d_obj_resp_p_ = d_obj_resp_p[I2].toObject();
                                    QJsonArray d_obj_resp_p_b = d_obj_resp_p_.value(QString("blocks")).toArray();
                                    for (I3 = 0; I3 < d_obj_resp_p_b.size(); I3++)
                                    {
                                        QJsonObject d_obj_resp_p_b_ = d_obj_resp_p_b[I3].toObject();
                                        QJsonArray d_obj_resp_p_b_bounds = d_obj_resp_p_b_.value(QString("boundingBox")).toObject().value(QString("vertices")).toArray();
                                        DelayLineAsyncTextObjDef ObjDef_;
                                        ObjDef_.ObjType = 0;
                                        ObjDef_.TextState = 0;
                                        ObjDef_.X1 = d_obj_resp_p_b_bounds[0].toObject().value(QString("x")).toInt();
                                        ObjDef_.Y1 = d_obj_resp_p_b_bounds[0].toObject().value(QString("y")).toInt();
                                        ObjDef_.X2 = d_obj_resp_p_b_bounds[1].toObject().value(QString("x")).toInt();
                                        ObjDef_.Y2 = d_obj_resp_p_b_bounds[1].toObject().value(QString("y")).toInt();
                                        ObjDef_.X3 = d_obj_resp_p_b_bounds[2].toObject().value(QString("x")).toInt();
                                        ObjDef_.Y3 = d_obj_resp_p_b_bounds[2].toObject().value(QString("y")).toInt();
                                        ObjDef_.X4 = d_obj_resp_p_b_bounds[3].toObject().value(QString("x")).toInt();
                                        ObjDef_.Y4 = d_obj_resp_p_b_bounds[3].toObject().value(QString("y")).toInt();
                                        ObjDef_.MidX = ObjDef_.X1 + ObjDef_.X2 + ObjDef_.X3 + ObjDef_.X4;
                                        ObjDef_.MidY = ObjDef_.Y1 + ObjDef_.Y2 + ObjDef_.Y3 + ObjDef_.Y4;
                                        ObjDef_.ObjText = "";
                                        DelayLineAsyncTextObjList.push_back(ObjDef_);
                                        DelayLineAsyncTextObjNum[0] = DelayLineAsyncTextObjList.size() - 1;

                                        QJsonArray d_obj_resp_p_b_par = d_obj_resp_p_b_.value(QString("paragraphs")).toArray();
                                        for (I4 = 0; I4 < d_obj_resp_p_b_par.size(); I4++)
                                        {
                                            QJsonObject d_obj_resp_p_b_par_ = d_obj_resp_p_b_par[I4].toObject();
                                            QJsonArray d_obj_resp_p_b_par_bounds = d_obj_resp_p_b_par_.value(QString("boundingBox")).toObject().value(QString("vertices")).toArray();
                                            DelayLineAsyncTextObjDef ObjDef_;
                                            ObjDef_.ObjType = 1;
                                            ObjDef_.TextState = 0;
                                            ObjDef_.X1 = d_obj_resp_p_b_par_bounds[0].toObject().value(QString("x")).toInt();
                                            ObjDef_.Y1 = d_obj_resp_p_b_par_bounds[0].toObject().value(QString("y")).toInt();
                                            ObjDef_.X2 = d_obj_resp_p_b_par_bounds[1].toObject().value(QString("x")).toInt();
                                            ObjDef_.Y2 = d_obj_resp_p_b_par_bounds[1].toObject().value(QString("y")).toInt();
                                            ObjDef_.X3 = d_obj_resp_p_b_par_bounds[2].toObject().value(QString("x")).toInt();
                                            ObjDef_.Y3 = d_obj_resp_p_b_par_bounds[2].toObject().value(QString("y")).toInt();
                                            ObjDef_.X4 = d_obj_resp_p_b_par_bounds[3].toObject().value(QString("x")).toInt();
                                            ObjDef_.Y4 = d_obj_resp_p_b_par_bounds[3].toObject().value(QString("y")).toInt();
                                            ObjDef_.MidX = ObjDef_.X1 + ObjDef_.X2 + ObjDef_.X3 + ObjDef_.X4;
                                            ObjDef_.MidY = ObjDef_.Y1 + ObjDef_.Y2 + ObjDef_.Y3 + ObjDef_.Y4;
                                            ObjDef_.ObjText = "";
                                            DelayLineAsyncTextObjList.push_back(ObjDef_);
                                            DelayLineAsyncTextObjNum[1] = DelayLineAsyncTextObjList.size() - 1;

                                            QJsonArray d_obj_resp_p_b_par_word = d_obj_resp_p_b_par_.value(QString("words")).toArray();
                                            for (I5 = 0; I5 < d_obj_resp_p_b_par_word.size(); I5++)
                                            {
                                                QJsonObject d_obj_resp_p_b_par_word_ = d_obj_resp_p_b_par_word[I5].toObject();
                                                QJsonArray d_obj_resp_p_b_par_word_bounds = d_obj_resp_p_b_par_word_.value(QString("boundingBox")).toObject().value(QString("vertices")).toArray();

                                                if (OcrLevel >= 2)
                                                {
                                                    DelayLineAsyncTextObjDef ObjDef_;
                                                    ObjDef_.ObjType = 2;
                                                    ObjDef_.TextState = 0;
                                                    ObjDef_.X1 = d_obj_resp_p_b_par_word_bounds[0].toObject().value(QString("x")).toInt();
                                                    ObjDef_.Y1 = d_obj_resp_p_b_par_word_bounds[0].toObject().value(QString("y")).toInt();
                                                    ObjDef_.X2 = d_obj_resp_p_b_par_word_bounds[1].toObject().value(QString("x")).toInt();
                                                    ObjDef_.Y2 = d_obj_resp_p_b_par_word_bounds[1].toObject().value(QString("y")).toInt();
                                                    ObjDef_.X3 = d_obj_resp_p_b_par_word_bounds[2].toObject().value(QString("x")).toInt();
                                                    ObjDef_.Y3 = d_obj_resp_p_b_par_word_bounds[2].toObject().value(QString("y")).toInt();
                                                    ObjDef_.X4 = d_obj_resp_p_b_par_word_bounds[3].toObject().value(QString("x")).toInt();
                                                    ObjDef_.Y4 = d_obj_resp_p_b_par_word_bounds[3].toObject().value(QString("y")).toInt();
                                                    ObjDef_.MidX = ObjDef_.X1 + ObjDef_.X2 + ObjDef_.X3 + ObjDef_.X4;
                                                    ObjDef_.MidY = ObjDef_.Y1 + ObjDef_.Y2 + ObjDef_.Y3 + ObjDef_.Y4;
                                                    ObjDef_.ObjText = "";
                                                }
                                                DelayLineAsyncTextObjList.push_back(ObjDef_);
                                                DelayLineAsyncTextObjNum[2] = DelayLineAsyncTextObjList.size() - 1;

                                                QJsonArray d_obj_resp_p_b_par_word_symbol = d_obj_resp_p_b_par_word_.value(QString("symbols")).toArray();
                                                for (I6 = 0; I6 < d_obj_resp_p_b_par_word_symbol.size(); I6++)
                                                {
                                                    QJsonObject d_obj_resp_p_b_par_word_symbol_ = d_obj_resp_p_b_par_word_symbol[I6].toObject();
                                                    QJsonArray d_obj_resp_p_b_par_word_symbol_bounds = d_obj_resp_p_b_par_word_symbol_.value(QString("boundingBox")).toObject().value(QString("vertices")).toArray();
                                                    QJsonObject d_obj_resp_p_b_par_word_symbol_prop = d_obj_resp_p_b_par_word_symbol_.value(QString("property")).toObject();

                                                    DelayLineAsyncTextObjDef ObjDef_;
                                                    ObjDef_.BreakType = 0;
                                                    ObjDef_.ObjText = Eden::ToStr(d_obj_resp_p_b_par_word_symbol_.value("text").toString());

                                                    if (d_obj_resp_p_b_par_word_symbol_prop.contains("detectedBreak"))
                                                    {
                                                        QString d_obj_resp_p_b_par_word_symbol_prop_ = d_obj_resp_p_b_par_word_symbol_prop.value(QString("detectedBreak")).toObject().value(QString("type")).toString();
                                                        if (d_obj_resp_p_b_par_word_symbol_prop_ == "SPACE")
                                                        {
                                                            ObjDef_.BreakType = 1;
                                                            ObjDef_.ObjText = ObjDef_.ObjText + " ";
                                                        }
                                                        if (d_obj_resp_p_b_par_word_symbol_prop_ == "LINE_BREAK")
                                                        {
                                                            ObjDef_.BreakType = 2;
                                                            ObjDef_.ObjText = ObjDef_.ObjText + "\n";
                                                        }
                                                        if (d_obj_resp_p_b_par_word_symbol_prop_ == "EOL_SURE_SPACE")
                                                        {
                                                            ObjDef_.BreakType = 3;
                                                            ObjDef_.ObjText = ObjDef_.ObjText + "\n";
                                                        }
                                                    }

                                                    if (OcrLevel >= 3)
                                                    {
                                                        ObjDef_.ObjType = 3;
                                                        ObjDef_.TextState = 0;

                                                        ObjDef_.X1 = d_obj_resp_p_b_par_word_symbol_bounds[0].toObject().value(QString("x")).toInt();
                                                        ObjDef_.Y1 = d_obj_resp_p_b_par_word_symbol_bounds[0].toObject().value(QString("y")).toInt();
                                                        ObjDef_.X2 = d_obj_resp_p_b_par_word_symbol_bounds[1].toObject().value(QString("x")).toInt();
                                                        ObjDef_.Y2 = d_obj_resp_p_b_par_word_symbol_bounds[1].toObject().value(QString("y")).toInt();
                                                        ObjDef_.X3 = d_obj_resp_p_b_par_word_symbol_bounds[2].toObject().value(QString("x")).toInt();
                                                        ObjDef_.Y3 = d_obj_resp_p_b_par_word_symbol_bounds[2].toObject().value(QString("y")).toInt();
                                                        ObjDef_.X4 = d_obj_resp_p_b_par_word_symbol_bounds[3].toObject().value(QString("x")).toInt();
                                                        ObjDef_.Y4 = d_obj_resp_p_b_par_word_symbol_bounds[3].toObject().value(QString("y")).toInt();
                                                        ObjDef_.MidX = ObjDef_.X1 + ObjDef_.X2 + ObjDef_.X3 + ObjDef_.X4;
                                                        ObjDef_.MidY = ObjDef_.Y1 + ObjDef_.Y2 + ObjDef_.Y3 + ObjDef_.Y4;

                                                        DelayLineAsyncTextObjList.push_back(ObjDef_);
                                                    }

                                                    DelayLineAsyncTextObjList[DelayLineAsyncTextObjNum[0]].ObjText += ObjDef_.ObjText;
                                                    if (OcrLevel >= 1)
                                                    {
                                                        DelayLineAsyncTextObjList[DelayLineAsyncTextObjNum[1]].ObjText += ObjDef_.ObjText;
                                                    }
                                                    if (OcrLevel >= 2)
                                                    {
                                                        DelayLineAsyncTextObjList[DelayLineAsyncTextObjNum[2]].ObjText += ObjDef_.ObjText;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            vector<int> Id_;
                            int IdX = DelayLineAsyncThreadData_.Id;
                            int Ixx = DelayLineAsyncDecimateC;
                            while (Ixx > 0)
                            {
                                Id_.push_back(IdX);
                                IdX++;
                                Ixx--;
                            }

                            int MaskOverlay = Settings_->GoogleCloudMaskOverlay;
                            int Bound0 = -1 - MaskOverlay - MaskOverlay;
                            int BoundW = PicW + MaskOverlay + MaskOverlay;
                            int BoundH = PicH + MaskOverlay + MaskOverlay;
                            int PicW1 = PicW - 1;
                            int PicH1 = PicH - 1;
                            for (int Ix = 0; Ix < DelayLineAsyncTextObjList.size(); Ix++)
                            {
                                if (DelayLineAsyncTextObjList[Ix].ObjType == OcrLevel)
                                {

                                    int AreaX[5] = { DelayLineAsyncTextObjList[Ix].X1, DelayLineAsyncTextObjList[Ix].X2, DelayLineAsyncTextObjList[Ix].X3, DelayLineAsyncTextObjList[Ix].X4, 0 };
                                    int AreaY[5] = { DelayLineAsyncTextObjList[Ix].Y1, DelayLineAsyncTextObjList[Ix].Y2, DelayLineAsyncTextObjList[Ix].Y3, DelayLineAsyncTextObjList[Ix].Y4, 0 };

                                    int MiddleX = DelayLineAsyncTextObjList[Ix].MidX;
                                    int MiddleY = DelayLineAsyncTextObjList[Ix].MidY;

                                    int MinX = MiddleX >> 2;
                                    int MaxX = MiddleX >> 2;
                                    int MinY = MiddleY >> 2;
                                    int MaxY = MiddleY >> 2;

                                    for (int i = 0; i < 4; i++)
                                    {
                                        if ((AreaX[i] << 2) < MiddleX) { AreaX[i] -= MaskOverlay; }
                                        if ((AreaX[i] << 2) > MiddleX) { AreaX[i] += MaskOverlay; }
                                        if ((AreaY[i] << 2) < MiddleY) { AreaY[i] -= MaskOverlay; }
                                        if ((AreaY[i] << 2) > MiddleY) { AreaY[i] += MaskOverlay; }

                                        if (MinX > AreaX[i]) { MinX = AreaX[i]; }
                                        if (MaxX < AreaX[i]) { MaxX = AreaX[i]; }
                                        if (MinY > AreaY[i]) { MinY = AreaY[i]; }
                                        if (MaxY < AreaY[i]) { MaxY = AreaY[i]; }
                                    }
                                    AreaX[4] = AreaX[0];
                                    AreaY[4] = AreaY[0];

                                    if (MinX < 0) { MinX = 0; }
                                    if (MaxX > PicW1) { MaxX = PicW1; }
                                    if (MinY < 0) { MinY = 0; }
                                    if (MaxY > PicH1) { MaxY = PicH1; }

                                    DelayLineAsyncTextObjList[Ix].MinX = MinX;
                                    DelayLineAsyncTextObjList[Ix].MaxX = MaxX;
                                    DelayLineAsyncTextObjList[Ix].MinY = MinY;
                                    DelayLineAsyncTextObjList[Ix].MaxY = MaxY;

                                    for (int i = 0; i < PicW; i++)
                                    {
                                        DelayLineAsyncBitmapMaskMinY[i] = BoundH;
                                        DelayLineAsyncBitmapMaskMaxY[i] = Bound0;
                                    }
                                    for (int i = 0; i < PicH; i++)
                                    {
                                        DelayLineAsyncBitmapMaskMinX[i] = BoundW;
                                        DelayLineAsyncBitmapMaskMaxX[i] = Bound0;
                                    }

                                    int Bound1, Bound2;
                                    int Rot1 = 0;
                                    int Rot2 = 0;
                                    bool Rot1__ = false;
                                    bool Rot2__ = false;
                                    for (int i = 0; i < 4; i++)
                                    {
                                        if (AreaX[i] != AreaX[i + 1])
                                        {
                                            double Factor = ((double)AreaY[i] - (double)AreaY[i + 1]) / ((double)AreaX[i] - (double)AreaX[i + 1]);
                                            int Rot1_ = (int)((atan(Factor) * 180 / M_PI));
                                            if (Rot1__)
                                            {
                                                if (Abs(Rot1) > Abs(Rot1_))
                                                {
                                                    Rot1 = Rot1_;
                                                }
                                            }
                                            else
                                            {
                                                Rot1 = Rot1_;
                                                Rot1__ = true;
                                            }

                                            double Offset = (double)AreaY[i] - (double)AreaX[i] * Factor + 0.5;
                                            if (AreaX[i] < AreaX[i + 1])
                                            {
                                                Bound1 = (AreaX[i]);
                                                Bound2 = (AreaX[i + 1]);
                                            }
                                            else
                                            {
                                                Bound1 = (AreaX[i + 1]);
                                                Bound2 = (AreaX[i]);
                                            }
                                            if (Bound1 < 0) { Bound1 = 0; }
                                            if (Bound2 > PicW1) { Bound2 = PicW1; }
                                            for (int ii = Bound1; ii <= Bound2; ii++)
                                            {
                                                int FuncVal1 = (int)(((double)ii) * Factor + Offset);
                                                int FuncVal2 = (int)(((double)ii) * Factor + Offset);
                                                if (FuncVal1 < 0) { FuncVal1 = 0; }
                                                if (FuncVal2 > PicH1) { FuncVal2 = PicH1; }
                                                if ((DelayLineAsyncBitmapMaskMinY[ii] == BoundH) || (DelayLineAsyncBitmapMaskMinY[ii] > FuncVal1))
                                                {
                                                    DelayLineAsyncBitmapMaskMinY[ii] = FuncVal1;
                                                    DelayLineAsyncBitmapMaskMinY_R[ii] = BmpRaw[((ii + FuncVal1 * PicW) << 2) + 2];
                                                    DelayLineAsyncBitmapMaskMinY_G[ii] = BmpRaw[((ii + FuncVal1 * PicW) << 2) + 1];
                                                    DelayLineAsyncBitmapMaskMinY_B[ii] = BmpRaw[((ii + FuncVal1 * PicW) << 2) + 0];
                                                }
                                                if ((DelayLineAsyncBitmapMaskMaxY[ii] == Bound0) || (DelayLineAsyncBitmapMaskMaxY[ii] < FuncVal2))
                                                {
                                                    DelayLineAsyncBitmapMaskMaxY[ii] = FuncVal2;
                                                    DelayLineAsyncBitmapMaskMaxY_R[ii] = BmpRaw[((ii + FuncVal2 * PicW) << 2) + 2];
                                                    DelayLineAsyncBitmapMaskMaxY_G[ii] = BmpRaw[((ii + FuncVal2 * PicW) << 2) + 1];
                                                    DelayLineAsyncBitmapMaskMaxY_B[ii] = BmpRaw[((ii + FuncVal2 * PicW) << 2) + 0];
                                                }
                                            }
                                        }

                                        if (AreaY[i] != AreaY[i + 1])
                                        {
                                            double Factor = ((double)AreaX[i] - (double)AreaX[i + 1]) / ((double)AreaY[i] - (double)AreaY[i + 1]);
                                            int Rot2_ = (int)((atan(-Factor) * 180 / M_PI));
                                            if (Rot2__)
                                            {
                                                if (Abs(Rot2) > Abs(Rot2_))
                                                {
                                                    Rot2 = Rot2_;
                                                }
                                            }
                                            else
                                            {
                                                Rot2 = Rot2_;
                                                Rot2__ = true;
                                            }

                                            double Offset = (double)AreaX[i] - (double)AreaY[i] * Factor + 0.5;
                                            if (AreaY[i] < AreaY[i + 1])
                                            {
                                                Bound1 = (AreaY[i]);
                                                Bound2 = (AreaY[i + 1]);
                                            }
                                            else
                                            {
                                                Bound1 = (AreaY[i + 1]);
                                                Bound2 = (AreaY[i]);
                                            }
                                            if (Bound1 < 0) { Bound1 = 0; }
                                            if (Bound2 > PicH1) { Bound2 = PicH1; }
                                            for (int ii = Bound1; ii <= Bound2; ii++)
                                            {
                                                int FuncVal1 = (int)(((double)ii) * Factor + Offset);
                                                int FuncVal2 = (int)(((double)ii) * Factor + Offset);
                                                if (FuncVal1 < 0) { FuncVal1 = 0; }
                                                if (FuncVal2 > PicW1) { FuncVal2 = PicW1; }
                                                if ((DelayLineAsyncBitmapMaskMinX[ii] == BoundW) || (DelayLineAsyncBitmapMaskMinX[ii] > FuncVal1))
                                                {
                                                    DelayLineAsyncBitmapMaskMinX[ii] = FuncVal1;
                                                    DelayLineAsyncBitmapMaskMinX_R[ii] = BmpRaw[((FuncVal1 + ii * PicW) << 2) + 2];
                                                    DelayLineAsyncBitmapMaskMinX_G[ii] = BmpRaw[((FuncVal1 + ii * PicW) << 2) + 1];
                                                    DelayLineAsyncBitmapMaskMinX_B[ii] = BmpRaw[((FuncVal1 + ii * PicW) << 2) + 0];
                                                }
                                                if ((DelayLineAsyncBitmapMaskMaxX[ii] == Bound0) || (DelayLineAsyncBitmapMaskMaxX[ii] < FuncVal2))
                                                {
                                                    DelayLineAsyncBitmapMaskMaxX[ii] = FuncVal2;
                                                    DelayLineAsyncBitmapMaskMaxX_R[ii] = BmpRaw[((FuncVal2 + ii * PicW) << 2) + 2];
                                                    DelayLineAsyncBitmapMaskMaxX_G[ii] = BmpRaw[((FuncVal2 + ii * PicW) << 2) + 1];
                                                    DelayLineAsyncBitmapMaskMaxX_B[ii] = BmpRaw[((FuncVal2 + ii * PicW) << 2) + 0];
                                                }
                                            }
                                        }
                                    }
                                    if (Rot1__ && Rot2__)
                                    {
                                        DelayLineAsyncTextObjList[Ix].TextRotate = (Rot1 + Rot2) / 2;
                                    }
                                    else
                                    {
                                        DelayLineAsyncTextObjList[Ix].TextRotate = 0;
                                        if (Rot1__)
                                        {
                                            DelayLineAsyncTextObjList[Ix].TextRotate = Rot1;
                                        }
                                        if (Rot2__)
                                        {
                                            DelayLineAsyncTextObjList[Ix].TextRotate = Rot2;
                                        }
                                    }


                                    int * SumMinX = new int[MaxY - MinY + 1];
                                    int * SumMaxX = new int[MaxY - MinY + 1];
                                    int * SumMinY = new int[MaxX - MinX + 1];
                                    int * SumMaxY = new int[MaxX - MinX + 1];

                                    for (int Y = MinY; Y <= MaxY; Y++)
                                    {
                                        SumMinX[Y - MinY] = DelayLineAsyncBitmapMaskMinX[Y];
                                        SumMaxX[Y - MinY] = DelayLineAsyncBitmapMaskMaxX[Y];
                                    }
                                    for (int X = MinX; X <= MaxX; X++)
                                    {
                                        SumMinY[X - MinX] = DelayLineAsyncBitmapMaskMinY[X];
                                        SumMaxY[X - MinX] = DelayLineAsyncBitmapMaskMaxY[X];
                                    }

                                    DelayLinePaintCmdAdd(Id_, 2, MinX, MinY, MaxX, MaxY, "", 0, SumMinX, SumMaxX, SumMinY, SumMaxY);


                                }

                            }


                            for (int Ix = 0; Ix < DelayLineAsyncTextObjList.size(); Ix++)
                            {
                                if (DelayLineAsyncTextObjList[Ix].ObjType == OcrLevel)
                                {
                                    QString T = Eden::ToQStr(DelayLineAsyncTextObjList[Ix].ObjText).trimmed();
                                    if (T.length() > 0)
                                    {
                                        int ItemPos = DelayLinePaintCmdAdd(Id_, 1, DelayLineAsyncTextObjList[Ix].MinX, DelayLineAsyncTextObjList[Ix].MinY, DelayLineAsyncTextObjList[Ix].MaxX - DelayLineAsyncTextObjList[Ix].MinX + 1, DelayLineAsyncTextObjList[Ix].MaxY - DelayLineAsyncTextObjList[Ix].MinY + 1, T, DelayLineAsyncTextObjList[Ix].TextRotate, NULL, NULL, NULL, NULL);
                                        if (Settings_->GoogleCloudLangDst != "")
                                        {
                                            DelayLineAsyncThreadData DelayLineAsyncThreadData_;
                                            DelayLineAsyncThreadData_.Type = 2;
                                            DelayLineAsyncThreadData_.Url = QString("https://translation.googleapis.com/language/translate/v2?key=") + Eden::ToQStr(Settings_->GoogleCloudKey);

                                            QJsonObject TrObj;
                                            if (Settings_->GoogleCloudTranslateLines)
                                            {
                                                TrObj.insert("format", "html");
                                                TrObj.insert("q", GoogleConvert::ConvTextToHtml(T));
                                            }
                                            else
                                            {
                                                TrObj.insert("q", QJsonValue::fromVariant(T));
                                            }
                                            TrObj.insert("target", Eden::ToQStr(Settings_->GoogleCloudLangDst));
                                            if (Settings_->GoogleCloudLangSrc != "")
                                            {
                                                TrObj.insert("source", QJsonValue::fromVariant(Eden::ToQStr(Settings_->GoogleCloudLangSrc)));
                                            }
                                            QJsonDocument TrJSON(TrObj);
                                            DelayLineAsyncThreadData_.Data = TrJSON.toJson();
                                            DelayLineAsyncThreadData_.Pos = ItemPos;
                                            DelayLineAsyncThreadData_.Id = DelayLinePaintCmdList[ItemPos].CmdId;

                                            DelayLineAsyncThreadRequest.push(DelayLineAsyncThreadData_);
                                        }
                                    }
                                }
                            }
                        }
                        DelayLineAsyncBitmapFlush(AsyncIdx);

                    }
                    break;
                case 2: // Translate text
                    {
                        QJsonDocument d = QJsonDocument::fromJson(DelayLineAsyncThreadData_.Data);
                        QJsonObject d_obj = d.object();
                        QJsonArray d_obj_resp = d_obj.value(QString("data")).toObject().value("translations").toArray();
                        if (d_obj_resp.size() > 0)
                        {
                            QString TextResult = d_obj_resp[0].toObject().value("translatedText").toString();
                            if (Settings_->GoogleCloudTranslateLines)
                            {
                                TextResult = GoogleConvert::ConvHtmlToText(TextResult);
                            }

                            if (DelayLineAsyncThreadData_.Id == DelayLinePaintCmdList[DelayLineAsyncThreadData_.Pos].CmdId)
                            {
                                if (TextResult.size() > 0)
                                {
                                    DelayLinePaintCmdList[DelayLineAsyncThreadData_.Pos].PaintText = TextResult;
                                }
                                else
                                {
                                    DelayLinePaintCmdList[DelayLineAsyncThreadData_.Pos].Needed = false;
                                }
                            }
                        }
                    }
                    break;
            }
        }
        DelayLineAsyncThreadResult.pop();
    }
}

int PicThread::DelayLinePaintCmdAdd(vector<int> Id, int Cmd, int X1, int Y1, int X2, int Y2, QString Text, int Rot, int *PointX1, int *PointX2, int *PointY1, int *PointY2)
{
    DelayLinePaintCmdTextId++;
    for (int I = 0; I < DelayLinePaintCmdList.size(); I++)
    {
        if (!DelayLinePaintCmdList[I].Needed)
        {
            DelayLinePaintCmdList[I].CmdId = DelayLinePaintCmdTextId;
            DelayLinePaintCmdList[I].Needed = true;
            DelayLinePaintCmdList[I].Cmd = Cmd;
            DelayLinePaintCmdList[I].Id.clear();;
            for (int II = 0; II < Id.size(); II++)
            {
                DelayLinePaintCmdList[I].Id.push_back(Id[II]);
            }
            DelayLinePaintCmdList[I].PaintRot = Rot;
            DelayLinePaintCmdList[I].PaintX1 = X1;
            DelayLinePaintCmdList[I].PaintY1 = Y1;
            DelayLinePaintCmdList[I].PaintX2 = X2;
            DelayLinePaintCmdList[I].PaintY2 = Y2;
            DelayLinePaintCmdList[I].PaintText = Text;
            if (DelayLinePaintCmdList[I].Cmd == 2)
            {
                delete[] DelayLinePaintCmdList[I].PointX1;
                delete[] DelayLinePaintCmdList[I].PointX2;
                delete[] DelayLinePaintCmdList[I].PointY1;
                delete[] DelayLinePaintCmdList[I].PointY2;
            }
            DelayLinePaintCmdList[I].PointX1 = PointX1;
            DelayLinePaintCmdList[I].PointX2 = PointX2;
            DelayLinePaintCmdList[I].PointY1 = PointY1;
            DelayLinePaintCmdList[I].PointY2 = PointY2;
            return I;
        }
    }
    DelayLinePaintCmdDef C;
    C.CmdId = DelayLinePaintCmdTextId;
    C.Needed = true;
    C.Cmd = Cmd;
    C.Id.clear();;
    for (int II = 0; II < Id.size(); II++)
    {
        C.Id.push_back(Id[II]);
    }
    C.PaintRot = Rot;
    C.PaintX1 = X1;
    C.PaintY1 = Y1;
    C.PaintX2 = X2;
    C.PaintY2 = Y2;
    C.PaintText = Text;
    C.PointX1 = PointX1;
    C.PointX2 = PointX2;
    C.PointY1 = PointY1;
    C.PointY2 = PointY2;
    DelayLinePaintCmdList.push_back(C);
    return DelayLinePaintCmdList.size() - 1;
}

void PicThread::DelayLineAsyncPaint(uchar *Raw)
{
    QImage BmpImg = QImage(PicW, PicH, QImage::Format_ARGB32);
    uchar * Raw_ = BmpImg.bits();
    memcpy(Raw_, Raw, DelayLineChunkSize);
    QPainter QP;
    int CurrentId = DelayLineId[DelayLinePos];
    bool CaptureTextX = TextCapture_->TextState;
    if (CaptureTextX)
    {
        TextCapture_->TextInit(PicW, PicH, Settings_->GoogleCloudTranslateAlignH, Settings_->GoogleCloudTranslateAlignV);
    }
    for (int I = 0; I < DelayLinePaintCmdList.size(); I++)
    {
        DelayLinePaintCmdDef C = DelayLinePaintCmdList[I];
        if (C.Needed)
        {
            if (Abs(C.Id[0] - CurrentId) > (DelayLineCount + DelayLineCount))
            {
                DelayLinePaintCmdList[I].Needed = false;
            }

            for (int II = 0; II < C.Id.size(); II++)
            {
                if (CurrentId == C.Id[II])
                {
                    switch(C.Cmd)
                    {
                        case 1:
                            {
                                int TX = C.PaintX1 + (C.PaintX2 >> 1);
                                int TY = C.PaintY1 + (C.PaintY2 >> 1);
                                int C_R = 299 * (int)Raw_[((TX + TY * PicW) << 2) + 2];
                                int C_G = 587 * (int)Raw_[((TX + TY * PicW) << 2) + 1];
                                int C_B = 114 * (int)Raw_[((TX + TY * PicW) << 2) + 0];
                                if (QP.begin(&BmpImg))
                                {
                                    QP.save();
                                    QP.translate(TX, TY);
                                    QP.rotate(C.PaintRot);
                                    QP.translate(0 - TX, 0 - TY);

                                    if ((C_R + C_G + C_B) >= 127500)
                                    {
                                        QP.setPen(QPen(Qt::black));
                                    }
                                    else
                                    {
                                        QP.setPen(QPen(Qt::white));
                                    }

                                    int FontMinSize = Settings_->GoogleCloudFontSize;
                                    int FontSize = FontMinSize;
                                    QFont QFont_ = QFont(Eden::ToQStr(Settings_->GoogleCloudFontName), FontSize, QFont::Normal);
                                    int TextFlags = Qt::TextDontClip | Qt::TextWordWrap;
                                    switch (Settings_->GoogleCloudTranslateAlignH)
                                    {
                                        case 0: TextFlags = TextFlags | Qt::AlignLeft; break;
                                        case 1: TextFlags = TextFlags | Qt::AlignHCenter; break;
                                        case 2: TextFlags = TextFlags | Qt::AlignRight; break;
                                        case 3: TextFlags = TextFlags | Qt::AlignJustify; break;
                                    }
                                    switch (Settings_->GoogleCloudTranslateAlignV)
                                    {
                                        case 0: TextFlags = TextFlags | Qt::AlignTop; break;
                                        case 1: TextFlags = TextFlags | Qt::AlignVCenter; break;
                                        case 2: TextFlags = TextFlags | Qt::AlignBottom; break;
                                    }
                                    bool TextVertical = false;
                                    QP.setFont(QFont_);
                                    QRect TextRect = QP.boundingRect(C.PaintX1, C.PaintY1, C.PaintX2, C.PaintY2, TextFlags, C.PaintText);
                                    int RectW = TextRect.width();
                                    int RectH = TextRect.height();
                                    if (Settings_->GoogleCloudFontAutoSize)
                                    {
                                        int NewSizeW = FontSize * C.PaintX2 / RectW;
                                        int NewSizeH = FontSize * C.PaintY2 / RectH;
                                        if (NewSizeW > NewSizeH)
                                        {
                                            FontSize = NewSizeH;
                                        }
                                        else
                                        {
                                            FontSize = NewSizeW;
                                        }
                                        while ((RectW <= C.PaintX2) && (RectH <= C.PaintY2))
                                        {
                                            FontSize++;
                                            QFont_.setPixelSize(FontSize);
                                            QP.setFont(QFont_);
                                            TextRect = QP.boundingRect(C.PaintX1, C.PaintY1, C.PaintX2, C.PaintY2, TextFlags, C.PaintText);
                                            RectW = TextRect.width();
                                            RectH = TextRect.height();
                                        }
                                        while ((FontSize > FontMinSize) && ((RectW > C.PaintX2) || (RectH > C.PaintY2)))
                                        {
                                            FontSize--;
                                            QFont_.setPixelSize(FontSize);
                                            QP.setFont(QFont_);
                                            TextRect = QP.boundingRect(C.PaintX1, C.PaintY1, C.PaintX2, C.PaintY2, TextFlags, C.PaintText);
                                            RectW = TextRect.width();
                                            RectH = TextRect.height();
                                        }

                                        if (Settings_->GoogleCloudTextRotate)
                                        {
                                            QP.translate(TX, TY);
                                            QP.rotate(-90);
                                            QP.translate(0 - TX, 0 - TY);

                                            int FontSize_Rotate = FontMinSize;
                                            QFont_.setPixelSize(FontSize_Rotate);
                                            QP.setFont(QFont_);
                                            QRect TextRect_Rotate = QP.boundingRect(C.PaintX1, C.PaintY1, C.PaintY2, C.PaintX2, TextFlags, C.PaintText);
                                            int RectW_Rotate = TextRect_Rotate.width();
                                            int RectH_Rotate = TextRect_Rotate.height();
                                            int NewSizeW_Rotate = FontSize_Rotate * C.PaintY2 / RectW_Rotate;
                                            int NewSizeH_Rotate = FontSize_Rotate * C.PaintX2 / RectH_Rotate;
                                            if (NewSizeW_Rotate > NewSizeH_Rotate)
                                            {
                                                FontSize_Rotate = NewSizeH_Rotate;
                                            }
                                            else
                                            {
                                                FontSize_Rotate = NewSizeW_Rotate;
                                            }
                                            while ((RectW_Rotate <= C.PaintY2) && (RectH_Rotate <= C.PaintX2))
                                            {
                                                FontSize_Rotate++;
                                                QFont_.setPixelSize(FontSize_Rotate);
                                                QP.setFont(QFont_);
                                                TextRect_Rotate = QP.boundingRect(C.PaintX1, C.PaintY1, C.PaintY2, C.PaintX2, TextFlags, C.PaintText);
                                                RectW_Rotate = TextRect_Rotate.width();
                                                RectH_Rotate = TextRect_Rotate.height();
                                            }
                                            while ((FontSize_Rotate > FontMinSize) && ((RectW_Rotate > C.PaintY2) || (RectH_Rotate > C.PaintX2)))
                                            {
                                                FontSize_Rotate--;
                                                QFont_.setPixelSize(FontSize_Rotate);
                                                QP.setFont(QFont_);
                                                TextRect_Rotate = QP.boundingRect(C.PaintX1, C.PaintY1, C.PaintY2, C.PaintX2, TextFlags, C.PaintText);
                                                RectW_Rotate = TextRect_Rotate.width();
                                                RectH_Rotate = TextRect_Rotate.height();
                                            }

                                            if (FontSize_Rotate < FontSize)
                                            {
                                                QP.translate(TX, TY);
                                                QP.rotate(90);
                                                QP.translate(0 - TX, 0 - TY);
                                                QFont_.setPixelSize(FontSize);
                                                QP.setFont(QFont_);
                                            }
                                            else
                                            {
                                                FontSize = FontSize_Rotate;
                                                TextVertical = true;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if (Settings_->GoogleCloudTextRotate)
                                        {
                                            int PropW_1 = 0;
                                            int PropH_1 = 0;
                                            int PropW_2 = 0;
                                            int PropH_2 = 0;

                                            if ((C.PaintX2 << 10 / C.PaintY2) < (RectW << 10 / RectH))
                                            {
                                                PropW_1 = C.PaintX2;
                                                PropH_1 = C.PaintX2 * RectH / RectW;
                                            }
                                            else
                                            {
                                                PropW_1 = C.PaintY2 * RectW / RectH;
                                                PropH_1 = C.PaintY2;
                                            }

                                            if ((C.PaintX2 << 10 / C.PaintY2) < (RectH << 10 / RectW))
                                            {
                                                PropW_2 = C.PaintX2;
                                                PropH_2 = C.PaintX2 * RectW / RectH;
                                            }
                                            else
                                            {
                                                PropW_2 = C.PaintY2 * RectH / RectW;
                                                PropH_2 = C.PaintY2;
                                            }

                                            if ((PropW_2 * PropH_2) > (PropW_1 * PropH_1))
                                            {
                                                QP.translate(TX, TY);
                                                QP.rotate(-90);
                                                QP.translate(0 - TX, 0 - TY);
                                                TextVertical = true;
                                            }
                                        }
                                    }

                                    if (!CaptureTextX)
                                    {
                                        QP.drawText(C.PaintX1, C.PaintY1, C.PaintX2, C.PaintY2, TextFlags, C.PaintText);
                                    }
                                    TextRect = QP.boundingRect(C.PaintX1, C.PaintY1, C.PaintX2, C.PaintY2, TextFlags, C.PaintText);
                                    QP.restore();
                                    QP.end();

                                    if (CaptureTextX)
                                    {
                                        int __X = TextRect.x();
                                        int __Y = TextRect.y();
                                        int __W = TextRect.width();
                                        int __H = TextRect.height();
                                        TextCapture_->TextAdd(__X, __Y, __W, __H, C.PaintRot, Settings_->GoogleCloudFontName, (FontSize * Settings_->RecorderTextSize) / 100, TextVertical, C.PaintText);
                                    }
                                }
                            }
                            break;
                        case 2:
                            {
                                int ColorR = 0;
                                int ColorG = 0;
                                int ColorB = 0;
                                int ColorI = 0;
                                int DX = C.PaintX2 - C.PaintX1 + 1;
                                int DY = C.PaintY2 - C.PaintY1 + 1;
                                for (int X = 0; X < DX; X++)
                                {
                                    if (C.PointY1[X] < C.PointY2[X])
                                    {
                                        int CT1 = (((X + C.PaintX1) + C.PointY1[X] * PicW) << 2);
                                        int CT2 = (((X + C.PaintX1) + C.PointY2[X] * PicW) << 2);
                                        ColorR = ColorR + (int)Raw_[CT1 + 2] + (int)Raw_[CT2 + 2];
                                        ColorG = ColorG + (int)Raw_[CT1 + 1] + (int)Raw_[CT2 + 1];
                                        ColorB = ColorB + (int)Raw_[CT1 + 0] + (int)Raw_[CT2 + 0];
                                        ColorI++;
                                        ColorI++;
                                    }
                                }
                                for (int Y = 0; Y < DY; Y++)
                                {
                                    if (C.PointX1[Y] < C.PointX2[Y])
                                    {
                                        int CT1 = ((C.PointX1[Y] + (Y + C.PaintY1) * PicW) << 2);
                                        int CT2 = ((C.PointX2[Y] + (Y + C.PaintY1) * PicW) << 2);
                                        ColorR = ColorR + (int)Raw_[CT1 + 2] + (int)Raw_[CT2 + 2];
                                        ColorG = ColorG + (int)Raw_[CT1 + 1] + (int)Raw_[CT2 + 1];
                                        ColorB = ColorB + (int)Raw_[CT1 + 0] + (int)Raw_[CT2 + 0];
                                        ColorI++;
                                        ColorI++;
                                    }
                                }
                                if (ColorI > 0)
                                {
                                    ColorR = ColorR / ColorI;
                                    ColorG = ColorG / ColorI;
                                    ColorB = ColorB / ColorI;
                                }
                                else
                                {
                                    ColorR = 0;
                                    ColorG = 0;
                                    ColorB = 0;
                                }
                                for (int Y = C.PaintY1; Y <= C.PaintY2; Y++)
                                {
                                    for (int X = C.PaintX1; X <= C.PaintX2; X++)
                                    {
                                        if ((X >= C.PointX1[Y - C.PaintY1]) && (X <= C.PointX2[Y - C.PaintY1]) && (Y >= C.PointY1[X - C.PaintX1]) && (Y <= C.PointY2[X - C.PaintX1]))
                                        {
                                            int CT = ((X + Y * PicW) << 2);
                                            Raw_[CT + 2] = ColorR;
                                            Raw_[CT + 1] = ColorG;
                                            Raw_[CT + 0] = ColorB;
                                        }
                                    }
                                }
                            }
                            break;
                    }
                    break;
                }
            }
        }
    }
    if (CaptureTextX)
    {
        QByteArray BufBase;
        QBuffer BufBase_(&BufBase);
        BufBase_.open(QIODevice::WriteOnly);
        if (Settings_->RecorderFormat == 3)
        {
            BmpImg.save(&BufBase_, "JPEG", Settings_->RecorderQuality);
        }
        else
        {
            BmpImg.save(&BufBase_, "PNG", 100);
        }
        BufBase = BufBase.toBase64();
        TextCapture_->ImgSet(Eden::ToStr(QTextCodec::codecForName("UTF-8")->toUnicode(BufBase)), Settings_->RecorderFormat);
        TextCapture_->TextState = false;
        emit TextCaptureFinish();
    }
    memcpy(Raw, BmpImg.bits(), DelayLineChunkSize);
}
