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

namespace Ui {
class MainWindow;
}

#define min()

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
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
    Settings * Settings_;
    TransformCore * TransformCore_;
    void SetBackColor();

private slots:
    void on_PictureScreen_MouseMove(int Btn, int X, int Y);
    void on_PictureScreen_MousePress(int Btn, int X, int Y);
    void on_PictureScreen_MouseRelease(int Btn, int X, int Y);
    void SetWindow(int X, int Y, int W, int H);
    void UpdatePixmap(QImage *Img);
    void RunCommand(int Cmd);

private:
    Ui::MainWindow *ui;
    void RunSettings();

};

#endif // MAINWINDOW_H
