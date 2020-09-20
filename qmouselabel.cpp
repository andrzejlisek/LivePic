#include "qmouselabel.h"

QMouseLabel::QMouseLabel(QWidget *parent) : QLabel(parent)
{
    setMouseTracking(false);
}

void QMouseLabel::mouseMoveEvent(QMouseEvent *event)
{
    emit MouseMove(event->buttons(), event->x(), event->y());
}

void QMouseLabel::mousePressEvent(QMouseEvent *event)
{
    emit MousePress(event->buttons(), event->x(), event->y());
}

void QMouseLabel::mouseReleaseEvent(QMouseEvent *event)
{
    emit MouseRelease(event->buttons(), event->x(), event->y());
    PaintMTX.lock();
    CalcDraw();
    PaintMTX.unlock();
}

void QMouseLabel::Repaint_()
{
    this->repaint();
}

void QMouseLabel::paintEvent(QPaintEvent *event)
{
    event->isAccepted();

    if (PaintMTX.try_lock())
    {
        if ((ImgX != NULL) && ImgCorrect)
        {
            if (Settings_ == NULL)
            {
                PaintMTX.unlock();
                return;
            }

            if (Settings_->_PicDstNet)
            {
                PaintMTX.unlock();
                return;
            }

            // 0 - Center
            // 1 - Margin
            // 2 - Margin int
            // 3 - Fill
            // 4 - Fill int
            // 5 - Stretch
            // 6 - Stretch int
            // 7 - Tile 1
            // 8 - Tile 2

            QPainter painter(this);
            if (DrawStretched == 0)
            {
                painter.drawImage(ImgDst, *ImgX, ImgSrc);
            }
            else
            {
                if ((DrawStretched != 7) && (DrawStretched != 8))
                {
                    if ((DrawStretched == 2) || (DrawStretched == 4) || (DrawStretched == 6))
                    {
                        painter.drawImage(ImgDst, (*ImgX).scaled(ImgDstXS, Qt::IgnoreAspectRatio, Qt::SmoothTransformation), ImgDstX);
                    }
                    else
                    {
                        painter.drawImage(ImgDst, *ImgX, ImgSrc);
                    }
                }
                else
                {
                    int X, Y;
                    int X0 = DrawOffsetX;
                    int Y0 = DrawOffsetY;
                    int W = ImgDst.width();
                    int H = ImgDst.height();
                    int W0 = ImgSrc.width();
                    int H0 = ImgSrc.height();

                    if (DrawStretched == 7)
                    {
                        X0 += (W - W0) >> 1;
                        Y0 += (H - H0) >> 1;
                    }
                    else
                    {
                        X0 += W >> 1;
                        Y0 += H >> 1;
                    }


                    while (X0 > 0) { X0 -= W0; }
                    while (Y0 > 0) { Y0 -= H0; }
                    while (X0 < (0 - W0)) { X0 += W0; }
                    while (Y0 < (0 - H0)) { Y0 += H0; }

                    ImgTileDst.setX(ImgDst.x());
                    ImgTileDst.setY(ImgDst.y());
                    ImgTileDst.setWidth(ImgDst.width());
                    ImgTileDst.setHeight(ImgDst.height());

                    for (Y = Y0; Y < H; Y += H0)
                    {
                        for (X = X0; X < W; X += W0)
                        {
                            int XX = X;
                            int YY = Y;
                            int W00 = W0;
                            int H00 = H0;
                            int SX = 0;
                            int SY = 0;
                            if (X < 0) { XX = 0; SX = 0 - X; }
                            if (Y < 0) { YY = 0; SY = 0 - Y; }
                            if ((XX + DrawMarginLeft + W0) > W) { W00 = W - XX; }
                            if ((YY + DrawMarginTop + H0) > H) { H00 = H - YY; }
                            painter.drawImage(XX + DrawMarginLeft, YY + DrawMarginTop, *ImgX, SX, SY, W00, H00);
                        }
                    }
                }
            }
        }
        PaintMTX.unlock();
    }
}

void QMouseLabel::CalcDraw()
{
    if ((ImgX != NULL))
    {
        QRect Geo = this->geometry();

        int BaseX = DrawMarginLeft;
        int BaseY = DrawMarginTop;
        int BaseW = Geo.width() - DrawMarginLeft - DrawMarginRight;
        int BaseH = Geo.height() - DrawMarginTop - DrawMarginBottom;
        int ImgW = ImgX->width();
        int ImgH = ImgX->height();

        // No stretching
        if (DrawStretched == 0)
        {
            int TempX = (BaseW >> 1) - (ImgW >> 1) + DrawOffsetX;
            int TempY = (BaseH >> 1) - (ImgH >> 1) + DrawOffsetY;

            TempX = BaseX + TempX;
            TempY = BaseY + TempY;
            if (TempX < DrawMarginLeft)
            {
                ImgSrc.setX(DrawMarginLeft - TempX);
                ImgW = ImgW - (DrawMarginLeft - TempX);
                TempX = DrawMarginLeft;
            }
            else
            {
                ImgSrc.setX(0);
            }
            if (TempY < DrawMarginTop)
            {
                ImgSrc.setY(DrawMarginTop - TempY);
                ImgH = ImgH - (DrawMarginTop - TempY);
                TempY = DrawMarginTop;
            }
            else
            {
                ImgSrc.setY(0);
            }
            if ((TempX - DrawMarginLeft + ImgW) > BaseW) { ImgW = BaseW - (TempX - DrawMarginLeft); }
            if ((TempY - DrawMarginTop + ImgH) > BaseH) { ImgH = BaseH - (TempY - DrawMarginTop); }

            ImgSrc.setWidth(ImgW);
            ImgSrc.setHeight(ImgH);

            ImgDst.setX(TempX);
            ImgDst.setY(TempY);
            ImgDst.setWidth(ImgW);
            ImgDst.setHeight(ImgH);
        }

        if ((ImgW <= 0) || (ImgH <= 0) || (BaseW <= 0) || (BaseH <= 0))
        {
            return;
        }

        // Proportional stretching with margins
        if ((DrawStretched == 1) || (DrawStretched == 2))
        {
            ImgSrc.setX(0);
            ImgSrc.setY(0);
            ImgSrc.setWidth(ImgW);
            ImgSrc.setHeight(ImgH);

            int RatioB = ((BaseW << ZoomAccuracy) / BaseH);
            int RatioI = ((ImgW << ZoomAccuracy) / ImgH);

            if (RatioB > RatioI)
            {
                int T = (BaseH * RatioI) >> ZoomAccuracy;
                ImgDst.setX(BaseX + ((BaseW >> 1) - (T >> 1)));
                ImgDst.setY(BaseY);
                ImgDst.setWidth(T);
                ImgDst.setHeight(BaseH);

                ImgDstX.setX(0);
                ImgDstX.setY(DrawMarginTop - BaseY);
            }
            if (RatioB == RatioI)
            {
                ImgDst.setX(BaseX);
                ImgDst.setY(BaseY);
                ImgDst.setWidth(BaseW);
                ImgDst.setHeight(BaseH);

                ImgDstX.setX(0);
                ImgDstX.setY(0);
            }
            if (RatioB < RatioI)
            {
                int T = (BaseW << ZoomAccuracy) / RatioI;
                ImgDst.setX(BaseX);
                ImgDst.setY(BaseY + ((BaseH >> 1) - (T >> 1)));
                ImgDst.setWidth(BaseW);
                ImgDst.setHeight(T);

                ImgDstX.setX(DrawMarginLeft - BaseX);
                ImgDstX.setY(0);
            }
            ImgDstX.setWidth(ImgDst.width());
            ImgDstX.setHeight(ImgDst.height());
            ImgDstXS = ImgDstX.size();
        }

        // Proportional stretching by filling
        if ((DrawStretched == 3) || (DrawStretched == 4))
        {
            int RatioB = ((BaseW << ZoomAccuracy) / BaseH);
            int RatioI = ((ImgW << ZoomAccuracy) / ImgH);

            if (RatioB > RatioI)
            {
                int ZoomFactor = ((ImgW << ZoomAccuracy) / BaseW);
                int T = (BaseW << 14) / RatioI;
                T = (T >> 1) - (BaseH >> 1);
                ImgSrc.setX(0);
                ImgSrc.setY(((T * ZoomFactor) >> ZoomAccuracy) + 1);
                ImgSrc.setWidth(ImgW);
                ImgSrc.setHeight((BaseH * ZoomFactor) >> ZoomAccuracy);

                ImgDstX.setX(0);
                ImgDstX.setY(T);
                ImgDstXS.setWidth(BaseW);
                ImgDstXS.setHeight((ImgH << ZoomAccuracy) / ZoomFactor);
            }
            if (RatioB == RatioI)
            {
                ImgSrc.setX(0);
                ImgSrc.setY(0);
                ImgSrc.setWidth(ImgW);
                ImgSrc.setHeight(ImgH);

                ImgDstX.setX(0);
                ImgDstX.setY(0);
                ImgDstXS.setWidth(BaseW);
                ImgDstXS.setHeight(BaseH);
            }
            if (RatioB < RatioI)
            {
                int ZoomFactor = ((ImgH << ZoomAccuracy) / BaseH);
                int T = (BaseH * RatioI) >> ZoomAccuracy;
                T = (T >> 1) - (BaseW >> 1);
                ImgSrc.setX(((T * ZoomFactor) >> ZoomAccuracy) + 1);
                ImgSrc.setY(0);
                ImgSrc.setWidth((BaseW * ZoomFactor) >> ZoomAccuracy);
                ImgSrc.setHeight(ImgH);

                ImgDstX.setX(T);
                ImgDstX.setY(0);
                ImgDstXS.setWidth((ImgW << ZoomAccuracy) / ZoomFactor);
                ImgDstXS.setHeight(BaseH);
            }
            ImgDstX.setWidth(BaseW);
            ImgDstX.setHeight(BaseH);
            if (DrawStretched == 4)
            {
                ImgDst.setX(DrawMarginLeft);
                ImgDst.setY(DrawMarginTop);
            }
            else
            {
                ImgDst.setX(BaseX);
                ImgDst.setY(BaseY);
            }
            ImgDst.setWidth(BaseW);
            ImgDst.setHeight(BaseH);
        }

        // Non-proportiona stretching
        if ((DrawStretched == 5) || (DrawStretched == 6))
        {
            ImgSrc.setX(0);
            ImgSrc.setY(0);
            ImgSrc.setWidth(ImgW);
            ImgSrc.setHeight(ImgH);

            ImgDst.setX(BaseX);
            ImgDst.setY(BaseY);
            ImgDst.setWidth(BaseW);
            ImgDst.setHeight(BaseH);

            ImgDstX.setX(0);
            ImgDstX.setY(0);
            ImgDstX.setWidth(BaseW);
            ImgDstX.setHeight(BaseH);

            ImgDstXS = ImgDstX.size();
        }

        // Tile filling
        if ((DrawStretched == 7) || (DrawStretched == 8))
        {
            ImgSrc.setX(0);
            ImgSrc.setY(0);
            ImgSrc.setWidth(ImgW);
            ImgSrc.setHeight(ImgH);

            ImgDst.setX(BaseX);
            ImgDst.setY(BaseY);
            ImgDst.setWidth(BaseW);
            ImgDst.setHeight(BaseH);
        }


        ImgCorrect = false;
        if ((ImgSrc.width() > 0) && (ImgSrc.height() > 0))
        {
            if ((ImgDst.width() > 0) && (ImgDst.height() > 0))
            {
                ImgCorrect = true;
            }
        }
    }
}
