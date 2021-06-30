#ifndef RECORDER_H
#define RECORDER_H

#include "settings.h"
#include <list>
#include "eden.h"
#include <iostream>
#include <QImage>
#include <QBuffer>
#include <fstream>
#include "textcapture.h"

class Recorder
{
public:
    Recorder();
    ~Recorder();
    Settings * Settings_;
    void RecorderProcess(uchar * Raw);
    void RecStart();
    void RecStop();
    void PlayStart(int N_, int D_);
    void PlayStop();
    void Init();
    int PicCount;
    int PicPos;
    int PicW;
    int PicH;
    int PicL;
    void SequenceOpen(string DirName);
    void SequenceClose();
    TextCapture * TextCapture_;
    string PicFileDir = "";
    int TextCaptureTimer = 0;
    int TextCaptureTimerL = 1;
    string TextCaptureFileName = "";
    void Apply(bool Memo, string Dir, int Format, int Quality);
    void ExportText(string Dir, int FrameTimeout);
    void ExportPic(string Dir, int PicTempo);
    int PicExportT = 0;
    int PicExportI = 0;
    string PicExportDir = "";
private:
    string NumSuffix[1000];
    bool RecordFile;
    list<int> MemoPicSize;
    list<int>::iterator MemoPicSizeI;
    list<int>::iterator MemoPicSizeI_E;
    list<uchar*> MemoPic;
    list<uchar*>::iterator MemoPicI;
    list<uchar*>::iterator MemoPicI_E;
    list<string> MemoFileName;
    list<string>::iterator MemoFileNameI;
    list<string>::iterator MemoFileNameI_E;
    int TempoN;
    int TempoD_I;
    int TempoD_C;
    bool StateRec;
    bool StatePlay;
    bool LiveJPEG;
    void MovePos(int N);

    bool PicFile = false;
    int PicFormat = 0;
    int PicQuality = 100;
    string PicExt = ".xxx";
    string FileNameLast = "";
    string FileNameLast_ = "";
};

#endif // RECORDER_H
