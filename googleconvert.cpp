#include "googleconvert.h"

GoogleConvert::GoogleConvert()
{

}

QString GoogleConvert::ConvMagic = "";
QString GoogleConvert::ConvMagic10 = "";
QString GoogleConvert::ConvMagic20 = "";
QString GoogleConvert::ConvMagic30 = "";
QString GoogleConvert::ConvMagic11 = "";
QString GoogleConvert::ConvMagic21 = "";
QString GoogleConvert::ConvMagic31 = "";
QString GoogleConvert::ConvMagic12 = "";
QString GoogleConvert::ConvMagic22 = "";
QString GoogleConvert::ConvMagic32 = "";

void GoogleConvert::Init()
{
    GoogleConvert::ConvMagic = "XXXQQQXXX";
    GoogleConvert::InitMagic();
}

void GoogleConvert::InitMagic()
{
    GoogleConvert::ConvMagic10 = "<" + GoogleConvert::ConvMagic + "1>0</" + GoogleConvert::ConvMagic + "1>";
    GoogleConvert::ConvMagic20 = "<" + GoogleConvert::ConvMagic + "2>0</" + GoogleConvert::ConvMagic + "2>";
    GoogleConvert::ConvMagic30 = "<" + GoogleConvert::ConvMagic + "3>0</" + GoogleConvert::ConvMagic + "3>";

    GoogleConvert::ConvMagic11 = "<" + GoogleConvert::ConvMagic + "1>";
    GoogleConvert::ConvMagic21 = "<" + GoogleConvert::ConvMagic + "2>";
    GoogleConvert::ConvMagic31 = "<" + GoogleConvert::ConvMagic + "3>";

    GoogleConvert::ConvMagic12 = "</" + GoogleConvert::ConvMagic + "1>";
    GoogleConvert::ConvMagic22 = "</" + GoogleConvert::ConvMagic + "2>";
    GoogleConvert::ConvMagic32 = "</" + GoogleConvert::ConvMagic + "3>";
}

QString GoogleConvert::ConvReplace(QString S, QString From, QString To)
{
    int Idx = S.indexOf(From);
    while (Idx >= 0)
    {
        S = S.mid(0, Idx) + To + S.mid(Idx + From.length());
        Idx = S.indexOf(From, Idx + To.length());
    }
    return S;
}

QString GoogleConvert::ConvReplace(QString S, QString From1, QString From2, QString To)
{
    int Idx1 = S.indexOf(From1);
    int Idx2 = S.indexOf(From2, Idx1);
    while (Idx1 >= 0)
    {
        S = S.mid(0, Idx1) + To + S.mid(Idx2 + From2.length());
        Idx1 = S.indexOf(From1, Idx1 + To.length());
        Idx2 = S.indexOf(From2, Idx1);
    }
    return S;
}

QString GoogleConvert::ConvTextToHtml(QString S)
{
    while (S.indexOf(GoogleConvert::ConvMagic) > 0)
    {
        GoogleConvert::ConvMagic = "A" + GoogleConvert::ConvMagic + "A";
        GoogleConvert::InitMagic();
    }

    S = GoogleConvert::ConvReplace(S, "&", "&amp;");
    S = GoogleConvert::ConvReplace(S, "\n", GoogleConvert::ConvMagic10);
    S = GoogleConvert::ConvReplace(S, "\r\n", GoogleConvert::ConvMagic20);
    S = GoogleConvert::ConvReplace(S, "\r", GoogleConvert::ConvMagic30);
    return S;
}

QString GoogleConvert::ConvHtmlToText(QString S)
{
    S = GoogleConvert::ConvReplace(S, GoogleConvert::ConvMagic11, GoogleConvert::ConvMagic12, "\n");
    S = GoogleConvert::ConvReplace(S, GoogleConvert::ConvMagic21, GoogleConvert::ConvMagic22, "\r\n");
    S = GoogleConvert::ConvReplace(S, GoogleConvert::ConvMagic31, GoogleConvert::ConvMagic32, "\r");

    int L1 = S.length();
    int L2 = 0;
    while (L1 != L2)
    {
        L1 = S.length();
        S = GoogleConvert::ConvReplace(S, "\n ", "\n");
        S = GoogleConvert::ConvReplace(S, " \n", "\n");
        L2 = S.length();
    }
    L1 = S.length();
    L2 = 0;
    while (L1 != L2)
    {
        L1 = S.length();
        S = GoogleConvert::ConvReplace(S, "\r ", "\r");
        S = GoogleConvert::ConvReplace(S, " \r", "\r");
        L2 = S.length();
    }

    int Idx1 = S.indexOf("&#");
    if (Idx1 > 0)
    {
        int Idx2 = S.indexOf(";", Idx1 + 1);
        if (Idx2 > 0)
        {
            QString CharCodeS = (S.mid(Idx1, Idx2 - Idx1 + 1));
            int CharCodeI = Eden::ToInt(CharCodeS.mid(2, CharCodeS.length() - 3));
            S = GoogleConvert::ConvReplace(S, CharCodeS, QString((char)CharCodeI));
        }
    }

    S = GoogleConvert::ConvReplace(S, "&lt;", "<");
    S = GoogleConvert::ConvReplace(S, "&gt;", ">");
    S = GoogleConvert::ConvReplace(S, "&quot;", "\"");
    S = GoogleConvert::ConvReplace(S, "&apos;", "'");
    S = GoogleConvert::ConvReplace(S, "&amp;", "&");
    return S.trimmed();
}
