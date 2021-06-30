#ifndef TEXTCAPTURE_H
#define TEXTCAPTURE_H

#include <vector>
#include <string>
#include <QString>
#include <sstream>
#include <fstream>
#include "eden.h"

using namespace std;

class TextCapture
{
public:
    TextCapture();
    bool TextState = false;
    int TextPicW = 0;
    int TextPicH = 0;
    int TextAlignH = 0;
    int TextAlignV = 0;
    void ImgSet(string Base64Raw, int FileFormat);
    void TextInit(int PicW, int PicH, int AlignH, int AlignV);
    void TextAdd(int X, int Y, int W, int H, int O, string Font, int Size, bool Vertical, QString Text);
    void Save(string FileName);
    void SaveChar(fstream &FS, int CharCode);
private:
    string ImgRaw;
    vector<int> TextX;
    vector<int> TextY;
    vector<int> TextW;
    vector<int> TextH;
    vector<int> TextO;
    vector<string> TextFont;
    vector<int> TextSize;
    vector<QString> TextText;
};

#endif // TEXTCAPTURE_H
