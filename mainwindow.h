#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QScreen>
#include <QThread>
#include <picthread.h>
#include "eden.h"
#include "winsettings.h"
#include "settings.h"
#include "transformcore.h"
#include "winrecorder.h"
#include "picnetwork.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QObject>
#include <iostream>

namespace Ui {
class MainWindow;
}

#define min()

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    struct DelayLineAsyncSlot
    {
    public:
        QNetworkAccessManager* Manager;
        QNetworkRequest Request;
        int State;
        int Pos;
        int Id;
        int Type;
    };
    vector<DelayLineAsyncSlot> DelayLineAsyncSlotList;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPixmap Bmp;
    PicThread * PicThread_;
    int SizeModeH;
    int SizeModeV;
    int ClickX;
    int ClickY;
    bool MouseBtn;
    int PicX;
    int PicY;
    int PicW;
    int PicH;
    WinSettings WinSettings_;
    WinRecorder WinRecorder_;
    Settings * Settings_;
    TransformCore * TransformCore_;
    void SetBackColor();
    PicNetwork * PicNetwork_;
    void FullScreenEvent();

private slots:
    void on_PictureScreen_MouseMove(int Btn, int X, int Y);
    void on_PictureScreen_MousePress(int Btn, int X, int Y);
    void on_PictureScreen_MouseRelease(int Btn, int X, int Y);
    void SetWindow(int X, int Y, int W, int H, bool FullScreen);
    void UpdatePixmap(QImage *Img);
    void RunCommand(int Cmd);
    void resizeEvent(QResizeEvent *event);
    void moveEvent(QResizeEvent *event);
    void closeEvent(QCloseEvent *event);
    void ShowRecorder();

private:
    Ui::MainWindow *ui;
    void RunSettings();
    bool FullScreen_ = false;
    bool FullScreen__ = false;
    void MouseCursor(int Cur);
    void MouseCursorVisible(QCursor Cur);
    void MouseCursorMode(bool Btn, int X, int Y, int W, int H);
    int MouseCursorType = -1;

};

#endif // MAINWINDOW_H
