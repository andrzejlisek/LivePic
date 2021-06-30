#ifndef GOOGLECONVERT_H
#define GOOGLECONVERT_H

#include <QString>
#include <eden.h>

class GoogleConvert
{
public:
    GoogleConvert();
    static QString ConvReplace(QString S, QString From, QString To);
    static QString ConvReplace(QString S, QString From1, QString From2, QString To);
    static QString ConvMagic;
    static QString ConvTextToHtml(QString S);
    static QString ConvHtmlToText(QString S);
    static void Init();
private:
    static void InitMagic();
    static QString ConvMagic10;
    static QString ConvMagic11;
    static QString ConvMagic12;
    static QString ConvMagic20;
    static QString ConvMagic21;
    static QString ConvMagic22;
    static QString ConvMagic30;
    static QString ConvMagic31;
    static QString ConvMagic32;
};

#endif // GOOGLECONVERT_H
