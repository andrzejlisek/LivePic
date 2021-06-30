#include "textcapture.h"

TextCapture::TextCapture()
{

}

void TextCapture::ImgSet(string Base64Raw, int FileFormat)
{
    if (FileFormat == 3)
    {
        ImgRaw = "data:image/jpeg;base64," + Base64Raw;
    }
    else
    {
        ImgRaw = "data:image/png;base64," + Base64Raw;
    }
}

void TextCapture::TextInit(int PicW, int PicH, int AlignH, int AlignV)
{
    TextPicW = PicW;
    TextPicH = PicH;
    TextAlignH = AlignH;
    TextAlignV = AlignV;
    TextX.clear();
    TextY.clear();
    TextW.clear();
    TextH.clear();
    TextO.clear();
    TextFont.clear();
    TextSize.clear();
    TextText.clear();
}

void TextCapture::TextAdd(int X, int Y, int W, int H, int O, string Font, int Size, bool Vertical, QString Text)
{
    TextX.push_back(X);
    TextY.push_back(Y);
    TextW.push_back(W);
    TextH.push_back(H);
    if (Vertical)
    {
        TextO.push_back(O - 90);
    }
    else
    {
        TextO.push_back(O);
    }
    TextFont.push_back(Font);
    TextSize.push_back(Size);
    TextText.push_back(Text);
}

void TextCapture::SaveChar(fstream &FS, int CharCode)
{
    if (CharCode < 0x7F)
    {
        FS << (char)(CharCode & 127);
    }
    else
    {
        if (CharCode < 0x7FF)
        {
            FS << (char)(((CharCode >> 6) & 31) + 128 + 64);
            FS << (char)((CharCode & 63) + 128);
        }
        else
        {
            if (CharCode < 0x7FFF)
            {
                FS << (char)(((CharCode >> 12) & 15) + 128 + 64 + 32);
                FS << (char)(((CharCode >> 6) & 63) + 128);
                FS << (char)((CharCode & 63) + 128);
            }
        }
    }
}

void TextCapture::Save(string FileName)
{
    string FileName1 = FileName + ".htm";
    string FileName2 = FileName + ".csv";
    fstream FS1(Eden::File(FileName1), ios::out);
    fstream FS2(Eden::File(FileName2), ios::out);

    // HTML file
    if (FS1.is_open())
    {
        int BorderSize = 1;
        string SizeUnit = "px";
        FS1 << "<!DOCTYPE html>" << endl;
        FS1 << "<html>" << endl;
        FS1 << "    <head>" << endl;
        FS1 << "        <meta charset=\"UTF-8\">" << endl;
        FS1 << "        <style>" << endl;
        FS1 << "            div.h" << endl;
        FS1 << "            {" << endl;
        FS1 << "                position:absolute;" << endl;
        FS1 << "            }" << endl;
        FS1 << "            div.t1" << endl;
        FS1 << "            {" << endl;
        FS1 << "                position:absolute;" << endl;
        FS1 << "                display: table;" << endl;
        FS1 << "            }" << endl;
        FS1 << "            div.t2" << endl;
        FS1 << "            {" << endl;
        switch (TextAlignH)
        {
            case 0: FS1 << "                text-align: left;" << endl; break;
            case 1: FS1 << "                text-align: center;" << endl; break;
            case 2: FS1 << "                text-align: right;" << endl; break;
            case 3: FS1 << "                text-align: justify;" << endl; break;
        }
        switch (TextAlignV)
        {
            case 0: FS1 << "                vertical-align: top;" << endl; break;
            case 1: FS1 << "                vertical-align: middle;" << endl; break;
            case 2: FS1 << "                vertical-align: bottom;" << endl; break;
        }
        FS1 << "                display: table-cell;" << endl;
        FS1 << "            }" << endl;
        FS1 << "        </style>" << endl;
        FS1 << "    </head>" << endl;
        FS1 << "    <body>" << endl;
        FS1 << "        <img style=\"position:absolute;left:0" + SizeUnit + ";top:0" + SizeUnit + ";\" src=\"" + ImgRaw + "\">" << endl;
        FS1 << "        <div class=\"h\" style=\"left:0" + SizeUnit + ";top:0" + SizeUnit + ";width:" + to_string(TextPicW - BorderSize - BorderSize) + SizeUnit + ";height:" + to_string(TextPicH - BorderSize - BorderSize) + SizeUnit + "\"></div>" << endl;
        for (int I = 0; I < TextText.size(); I++)
        {
            string Rot = "";
            if (TextO[I] != 0)
            {
                Rot = "transform:rotate(" + to_string(TextO[I]) + "deg);";
            }
            FS1 << "        <div class=\"t1\" style=\"left:" + to_string(TextX[I]) + SizeUnit + ";top:" + to_string(TextY[I]) + SizeUnit + ";width:" + to_string(TextW[I] - BorderSize - BorderSize) + SizeUnit + ";height:" + to_string(TextH[I] - BorderSize - BorderSize) + SizeUnit + ";" + Rot + "\">";
            FS1 << "<div class=\"t2\" style=\"font-family:" + TextFont[I] + ";font-size:" + to_string(TextSize[I]) + SizeUnit + ";\">";
            QString S = TextText[I];
            for (int II = 0; II < S.length(); II++)
            {
                QChar S_ = S[II];
                switch (S_.unicode())
                {
                    case '\n': FS1 << "<br>"; break;
                    case '<': FS1 << "&lt;"; break;
                    case '>': FS1 << "&gt;"; break;
                    case '\"': FS1 << "&quot;"; break;
                    case '\'': FS1 << "&apos;"; break;
                    case '&': FS1 << "&amp;"; break;
                    default:
                        {
                            SaveChar(FS1, S_.unicode());
                        }
                        break;
                }
            }
            FS1 << "</div>";
            FS1 << "</div>" << endl;
        }
        FS1 << "    </body>" << endl;
        FS1 << "</html>" << endl;
        FS1.close();
    }

    // CSV file
    if (FS2.is_open())
    {
        string Sep = ",";
        FS2 << "Left" + Sep + "Top" + Sep + "Width" + Sep + "Height" + Sep + "Angle" + Sep + "Font" + Sep + "Size" + Sep + "Text" << endl;
        for (int I = 0; I < TextText.size(); I++)
        {
            FS2 << TextX[I] << Sep << TextY[I] << Sep << TextH[I] << Sep << TextH[I] << Sep << TextO[I] << Sep;
            FS2 << "\"" << TextFont[I] << "\"" << Sep << TextSize[I] << Sep;
            FS2 << "\"";
            for (int II = 0; II < TextText[I].length(); II++)
            {
                if (TextText[I][II] == '\"')
                {
                    FS2 << "\"\"";
                }
                else
                {
                    SaveChar(FS2, TextText[I][II].unicode());
                }
            }
            FS2 << "\"";
            FS2 << endl;
        }
        FS2.close();
    }
}
