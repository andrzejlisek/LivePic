#include "recorder.h"

Recorder::Recorder()
{
    PicPos = 0;
    PicCount = 0;
    TempoN = 0;
    TempoD_I = 0;
    TempoD_C = 1;
    StateRec = false;
    StatePlay = false;
    LiveJPEG = false;
    PicW = 0;
    PicH = 0;
    PicL = 0;
    for (int I = 0; I < 10; I++)
    {
        NumSuffix[I] = "00" + to_string(I);
    }
    for (int I = 10; I < 100; I++)
    {
        NumSuffix[I] = "0" + to_string(I);
    }
    for (int I = 100; I < 1000; I++)
    {
        NumSuffix[I] = to_string(I);
    }
}

Recorder::~Recorder()
{
    SequenceClose();
}

void Recorder::RecorderProcess(uchar *Raw)
{
    if (PicExportT > 0)
    {
        for (int I = 0; I < PicExportT; I++)
        {
            fstream FS(Eden::File(PicExportDir + (*MemoFileNameI_E)), ios::binary | ios::out);
            if (FS.is_open())
            {
                FS.write((char*)(*MemoPicI_E), *MemoPicSizeI_E);
                FS.close();
            }
            MemoPicI_E++;
            MemoFileNameI_E++;
            MemoPicSizeI_E++;
            PicExportI++;
            if (MemoFileNameI_E == MemoFileName.end())
            {
                PicExportT = 0;
                break;
            }
        }
    }
    if (TextCaptureTimer > 0)
    {
        TextCaptureTimer--;
        if (TextCaptureTimer == 0)
        {
            if (Settings_->GoogleCloudEnabled)
            {
                TextCapture_->TextState = true;
            }

            uchar* Temp;
            int TempL;

            string FileExt_ = "";
            int PicFormat_ = Settings_->RecorderFormat;
            if (PicFormat_ == 0) FileExt_ = ".raw";
            if (PicFormat_ == 1) FileExt_ = ".bmp";
            if (PicFormat_ == 2) FileExt_ = ".png";
            if (PicFormat_ == 3) FileExt_ = ".jpg";
            fstream FS(Eden::File(TextCaptureFileName + FileExt_), ios::binary | ios::out);
            if (FS.is_open())
            {
                if (PicFormat_ == 0)
                {
                    FS.write((char*)Raw, PicL);
                }
                else
                {
                    QImage Temp_(PicW, PicH, QImage::Format_ARGB32);
                    memcpy(Temp_.bits(), Raw, PicL);

                    QByteArray BufBase;
                    QBuffer BufBase_(&BufBase);
                    BufBase_.open(QIODevice::WriteOnly);
                    if (PicFormat_ == 1)
                    {
                        Temp_.save(&BufBase_, "BMP", 100);
                    }
                    else
                    {
                        if (PicFormat_ == 2)
                        {
                            Temp_.save(&BufBase_, "PNG", 100);
                        }
                        else
                        {
                            if (PicFormat_ == 3)
                            {
                                Temp_.save(&BufBase_, "JPEG", Settings_->RecorderQuality);
                            }
                        }
                    }
                    FS.write(BufBase.data(), BufBase.length());
                }
                FS.close();
            }
        }
    }
    if (StateRec)
    {
        uchar* Temp;
        int TempL;

        if (PicFormat == 0)
        {
            Temp = new uchar[PicL];
            memcpy(Temp, Raw, PicL);
            TempL = PicL;
        }
        else
        {
            QImage Temp_(PicW, PicH, QImage::Format_ARGB32);
            memcpy(Temp_.bits(), Raw, PicL);

            QByteArray BufBase;
            QBuffer BufBase_(&BufBase);
            BufBase_.open(QIODevice::WriteOnly);
            if (PicFormat == 1)
            {
                Temp_.save(&BufBase_, "BMP", 100);
            }
            else
            {
                if (PicFormat == 2)
                {
                    Temp_.save(&BufBase_, "PNG", 100);
                }
                else
                {
                    if (PicFormat == 3)
                    {
                        Temp_.save(&BufBase_, "JPEG", PicQuality);
                    }
                }
            }

            TempL = BufBase.length();
            Temp = new uchar[TempL];
            memcpy(Temp, BufBase.data(), TempL);
        }



        string FileName_ = Eden::TimestampMs(false);
        if (FileNameLast == FileName_)
        {
            FileName_ = FileNameLast_ + "_";
        }
        else
        {
            FileNameLast = FileName_;
        }
        FileNameLast_ = FileName_;

        FileName_ = FileNameLast + "_" + NumSuffix[(FileNameLast_.size() - 14)] + PicExt;
        MemoFileName.push_back(FileName_);


        if (PicFile)
        {
            fstream FS(Eden::File(PicFileDir + FileName_), ios::binary | ios::out);
            if (FS.is_open())
            {
                FS.write((char*)Temp, TempL);
                FS.close();
            }
            delete[] Temp;
            MemoPic.push_back(NULL);
        }
        else
        {
            MemoPic.push_back(Temp);
        }
        MemoPicSize.push_back(TempL);

        if (MemoPic.size() == 1)
        {
            MemoPicI = MemoPic.begin();
            MemoPicSizeI = MemoPicSize.begin();
            MemoFileNameI = MemoFileName.begin();
        }
        PicCount++;
    }
    if (StatePlay)
    {
        TempoD_I++;
        if (TempoD_I >= TempoD_C)
        {
            TempoD_I = 0;
            MovePos(TempoN);
        }

        int TempL = *MemoPicSizeI;
        uchar* Temp = *MemoPicI;
        if (PicFile)
        {
            fstream FS(Eden::File(PicFileDir + (*MemoFileNameI)), ios::binary | ios::in);
            if (FS.is_open())
            {
                Temp = new uchar[TempL];
                FS.read((char*)Temp, TempL);
                FS.close();
            }
            else
            {
                Temp = NULL;
            }
        }

        bool BadImg = true;
        if (Temp != NULL)
        {
            if (PicFormat == 0)
            {
                memcpy(Raw, Temp, TempL);
                BadImg = false;
            }
            else
            {
                QImage Temp_;
                if (Temp_.loadFromData(Temp, TempL, nullptr))
                {
                    if ((Temp_.width() == PicW) && (Temp_.height() == PicH))
                    {
                        memcpy(Raw, Temp_.bits(), PicL);
                        BadImg = false;
                    }
                }
            }
            if (PicFile)
            {
                delete[] Temp;
            }
        }
        if (BadImg)
        {
            for (int I = 0; I < PicL; I++)
            {
                Raw[I] = rand() % 256;
            }
        }
    }
    else
    {
        if (LiveJPEG)
        {
            QImage Temp_(PicW, PicH, QImage::Format_ARGB32);
            memcpy(Temp_.bits(), Raw, PicL);

            QByteArray BufBase;
            QBuffer BufBase_(&BufBase);
            BufBase_.open(QIODevice::WriteOnly);
            Temp_.save(&BufBase_, "JPEG", PicQuality);

            if (Temp_.loadFromData((uchar*)BufBase.data(), BufBase.length(), nullptr))
            {
                memcpy(Raw, Temp_.bits(), PicL);
            }
        }
    }
}

void Recorder::RecStart()
{
    if (PicL == 0)
    {
        return;
    }
    StateRec = true;
}

void Recorder::RecStop()
{
    StateRec = false;
}

void Recorder::PlayStart(int N_, int D_)
{
    if (PicL == 0)
    {
        return;
    }
    if (D_ == 0)
    {
        MovePos(N_);
        PlayStart(0, 1);
        return;
    }

    StatePlay = true;
    TempoN = N_;
    TempoD_I = 0;
    TempoD_C = D_;
}

void Recorder::PlayStop()
{
    StatePlay = false;
}

void Recorder::SequenceOpen(string DirName)
{
    SequenceClose();
}

void Recorder::SequenceClose()
{
    StateRec = false;
    StatePlay = false;
    if (MemoPic.size() > 0)
    {
        for (MemoPicI = MemoPic.begin(); MemoPicI != MemoPic.end(); MemoPicI++)
        {
            if ((*MemoPicI) != NULL)
            {
                delete[] (*MemoPicI);
            }
        }
        MemoPic.clear();
        MemoPicSize.clear();
        MemoFileName.clear();
    }
    PicPos = 0;
    PicCount = 0;
}

void Recorder::Init()
{
    PicW = 0;
    PicH = 0;
    PicL = 0;
    if ((Settings_->RecorderMode == 1) || (Settings_->RecorderMode == 2))
    {
        PicW = Settings_->PicW;
        PicH = Settings_->PicH;
    }
    if ((Settings_->RecorderMode == 3) || (Settings_->RecorderMode == 4))
    {
        PicW = Settings_->PicW_disp;
        PicH = Settings_->PicH_disp;
    }
    PicL = (PicW * PicH) << 2;
    MemoPicI = MemoPic.begin();
    MemoPicSizeI = MemoPicSize.begin();
    MemoFileNameI = MemoFileName.begin();
    PicCount = 0;
    PicPos = 0;
}

void Recorder::MovePos(int N)
{
    if ((PicPos + N) < 0) { N = 0 - PicPos; }
    if ((PicPos + N) >= PicCount) { N = PicCount - PicPos - 1; }
    PicPos += N;
    while (N > 0)
    {
        MemoPicI++;
        MemoPicSizeI++;
        MemoFileNameI++;
        N--;
    }
    while (N < 0)
    {
        MemoPicI--;
        MemoPicSizeI--;
        MemoFileNameI--;
        N++;
    }
}

void Recorder::Apply(bool Memo, string Dir, int Format, int Quality)
{
    if ((!StateRec) && (!StatePlay))
    {
        SequenceClose();
        PicFile = !Memo;
        PicFileDir = Eden::CorrectDir(Dir);
        PicFormat = Format;
        PicQuality = Quality;
        LiveJPEG = false;
        if (PicFormat == 0) { PicExt = ".raw"; }
        if (PicFormat == 1) { PicExt = ".bmp"; }
        if (PicFormat == 2) { PicExt = ".png"; }
        if (PicFormat == 3) { PicExt = ".jpg"; LiveJPEG = true; }
    }
}

void Recorder::ExportText(string Dir, int FrameTimeout)
{
    if (TextCaptureTimer > 0)
    {
        TextCaptureTimer = 0;
        return;
    }
    TextCaptureFileName = Eden::CorrectDir(Dir) + Eden::TimestampMs(false);
    TextCaptureTimerL = FrameTimeout;
    TextCaptureTimer = TextCaptureTimerL;

}

void Recorder::ExportPic(string Dir, int PicTempo)
{
    PicExportDir = Eden::CorrectDir(Dir);
    MemoPicI_E = MemoPic.begin();
    MemoPicSizeI_E = MemoPicSize.begin();
    MemoFileNameI_E = MemoFileName.begin();
    PicExportI = 0;
    PicExportT = PicTempo;
}
