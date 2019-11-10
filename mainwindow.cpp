#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Settings_ = new Settings();
    TransformCore_ = new TransformCore();
    TransformCore_->Settings_ = Settings_;
    WinSettings_.TransformCore_ = TransformCore_;
    MouseBtn = false;
    Qt::WindowFlags flags = 0;
    /*if (Settings_->MainWindowBorder)
    {
        flags = Qt::Window;
    }
    else*/
    {
        flags = Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint;
    }
    //flags |= Qt::WindowMaximizeButtonHint;
    //flags |= Qt::WindowContextHelpButtonHint;
    //flags |= Qt::WindowCloseButtonHint;
    setWindowFlags(flags);

    SetBackColor();

    ui->setupUi(this);
    //ui->PictureScreen->setCursor(Qt::BlankCursor);
    SetWindow(Settings_->ViewX, Settings_->ViewY, Settings_->ViewW, Settings_->ViewH);
    QObject::connect(&WinSettings_, SIGNAL(SetWindow(int, int, int, int)), this, SLOT(SetWindow(int, int, int, int)));
    QObject::connect(&WinSettings_, SIGNAL(RunCommand(int)), this, SLOT(RunCommand(int)));

    PicThread_ = new PicThread();
    PicThread_->TransformCore_ = TransformCore_;
    PicThread_->PictureScreen = ui->PictureScreen;
    PicThread_->Settings_ = Settings_;
    WinSettings_.Settings_ = Settings_;
    WinSettings_.PicThread_ = PicThread_;
    QObject::connect(PicThread_, SIGNAL(UpdatePixmap(QImage*)), this, SLOT(UpdatePixmap(QImage*)));

    ui->PictureScreen->Settings_ = Settings_;
    TransformCore_->ListLoad(Eden::ApplicationDirectory() + "Transform.txt");

    RunSettings();
}

MainWindow::~MainWindow()
{
    TransformCore_->ListSave(Eden::ApplicationDirectory() + "Transform.txt");
    Settings_->Save();
    PicThread_->Stop();
    PicThread_->wait();
    ui->PictureScreen->ImgX = NULL;
    //delete PicThread_;
    //delete Settings_;
}

void MainWindow::SetBackColor()
{
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, QColor(Settings_->BackColorR, Settings_->BackColorG, Settings_->BackColorB));
    setAutoFillBackground(true);
    setPalette(Pal);
}

void MainWindow::UpdatePixmap(QImage *Img)
{
    if (Settings_->MTX.try_lock())
    {
        if (Img != NULL)
        {
                ui->PictureScreen->ImgX = Img;
                if (Settings_->NeedRecalc)
                {
                    Settings_->NeedRecalc = false;
                    ui->PictureScreen->CalcDraw(false);
                }
                ui->PictureScreen->DrawAllowed = true;
                ui->PictureScreen->repaint();
                ui->PictureScreen->DrawAllowed = false;
        }
        else
        {
            ui->PictureScreen->ImgX = NULL;
            ui->PictureScreen->repaint();
        }
        Settings_->MTX.unlock();
    }
}

void MainWindow::on_PictureScreen_MouseMove(int Btn, int X, int Y)
{
    if (MouseBtn)
    {
        int _X = this->x();
        int _Y = this->y();
        int _W = this->width();
        int _H = this->height();

        // Position
        if ((SizeModeH == 0) && (SizeModeV == 0))
        {
            _X = _X - (ClickX - X);
            _Y = _Y - (ClickY - Y);
        }

        // Left edge
        if (SizeModeH == 1)
        {
            _W = Max(_W - (X - ClickX), 0);
            _X = _X - (ClickX - X);
        }

        // Top edge
        if (SizeModeV == 1)
        {
            _H = Max(_H - (Y - ClickY), 0);
            _Y = _Y - (ClickY - Y);
        }

        // Right edge
        if (SizeModeH == 2)
        {
            _W = Max(PicW + (X - ClickX), 0);
        }

        // Bottom edge
        if (SizeModeV == 2)
        {
            _H = Max(PicH + (Y - ClickY), 0);
        }

        Settings_->ViewX = _X;
        Settings_->ViewY = _Y;
        Settings_->ViewW = _W;
        Settings_->ViewH = _H;
        WinSettings_.LoadSettings(true);
        SetWindow(_X, _Y, _W, _H);
    }
}

void MainWindow::on_PictureScreen_MousePress(int Btn, int X, int Y)
{
    ClickX = X;
    ClickY = Y;
    PicX = this->x();
    PicY = this->y();
    PicW = this->width();
    PicH = this->height();

    SizeModeH = 0;
    SizeModeV = 0;
    int MouseMarginX = Min(Settings_->MouseMargin, PicW / 2);
    if (ClickX < MouseMarginX) { SizeModeH = 1; }
    if (ClickX >= (PicW - MouseMarginX)) { SizeModeH = 2; }
    int MouseMarginY = Min(Settings_->MouseMargin, PicH / 2);
    if (ClickY < MouseMarginY) { SizeModeV = 1; }
    if (ClickY >= (PicH - MouseMarginY)) { SizeModeV = 2; }
    if ((SizeModeH != 0) && (SizeModeV != 0))
    {
        RunSettings();
    }
    else
    {
        //WinSettings_.MainPause();
        MouseBtn = true;
    }
}

void MainWindow::on_PictureScreen_MouseRelease(int Btn, int X, int Y)
{
    MouseBtn = false;
    //WinSettings_.MainResume();
}

void MainWindow::RunSettings()
{
    WinSettings_.show();
    WinSettings_.activateWindow();
    WinSettings_.raise();
    WinSettings_.setFocus();
    WinSettings_.LoadSettings(false);
    WinSettings_.AfterShow();
    WinSettings_.TransListRefresh();
}

void MainWindow::SetWindow(int X, int Y, int W, int H)
{
    this->setGeometry(X, Y, W, H);

    ui->PictureScreen->DrawMarginTop = Settings_->ViewMarginTop;
    ui->PictureScreen->DrawMarginLeft = Settings_->ViewMarginLeft;
    ui->PictureScreen->DrawMarginRight = Settings_->ViewMarginRight;
    ui->PictureScreen->DrawMarginBottom = Settings_->ViewMarginBottom;
    ui->PictureScreen->DrawOffsetX = Settings_->ViewOffsetX;
    ui->PictureScreen->DrawOffsetY = Settings_->ViewOffsetY;

    ui->PictureScreen->DrawStretched = Settings_->ViewStretched;
    ui->PictureScreen->setGeometry(0, 0, W, H);
    ui->PictureScreen->CalcDraw(false);
}

void MainWindow::RunCommand(int Cmd)
{
    if (Cmd == 0)
    {
        close();
    }
    if (Cmd == 1)
    {
        ui->PictureScreen->CalcDraw(false);
    }
    if (Cmd == 2)
    {
        SetBackColor();
    }
}
