#ifndef QMOUSELABEL_H
#define QMOUSELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <iostream>
#include <QPainter>
#include "settings.h"
#include <mutex>

#define ZoomAccuracy 14

using namespace std;

class QMouseLabel : public QLabel
{
    Q_OBJECT
public:
    explicit QMouseLabel(QWidget *parent = 0);
    QImage * ImgX = NULL;
    int DrawMarginLeft = 0;
    int DrawMarginRight = 0;
    int DrawMarginTop = 0;
    int DrawMarginBottom = 0;
    int DrawOffsetX = 0;
    int DrawOffsetY = 0;
    int DrawStretched = 0;
    void CalcDraw();
    QRect ImgSrc;
    QRect ImgDst;
    QRect ImgDstX;
    QRect ImgTileSrc;
    QRect ImgTileDst;
    QSize ImgDstXS;
    Settings * Settings_ = NULL;
    mutex PaintMTX;

    int DebugInt = 0;
    bool ImgCorrect = false;
signals:
    void MouseMove(int Btn, int X, int Y);
    void MousePress(int Btn, int X, int Y);
    void MouseRelease(int Btn, int X, int Y);
public slots:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void Repaint_();
};

#endif // QMOUSELABEL_H
