#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Settings_ = WinSettings_.Settings_;
    PicNetwork_ = new PicNetwork();
    PicNetwork_->Settings_ = Settings_;
    TransformCore_ = new TransformCore();
    TransformCore_->Settings_ = Settings_;
    WinSettings_.TransformCore_ = TransformCore_;
    WinSettings_.PicNetwork_ = PicNetwork_;
    WinRecorder_.Recorder_ = new Recorder();
    WinRecorder_.Recorder_->Settings_ = Settings_;
    WinRecorder_.Recorder_->TextCapture_ = new TextCapture();
    WinRecorder_.Init();

    connect(PicNetwork_, SIGNAL(NetLog(QString)), &WinSettings_, SLOT(PicNetLog(QString)));
    connect(&WinRecorder_, SIGNAL(LivePicRestart()), &WinSettings_, SLOT(on_MainRestart_clicked()));
    connect(&WinSettings_, SIGNAL(ShowRecorder()), this, SLOT(ShowRecorder()));
    MouseBtn = false;
    Qt::WindowFlags flags = windowFlags();
    {
        flags = flags | Qt::FramelessWindowHint;
    }
    if (Settings_->StayOnTopPic)
    {
        flags = flags | Qt::WindowStaysOnTopHint;
    }
    setWindowFlags(flags);

    SetBackColor();

    ui->setupUi(this);
    connect(&WinSettings_, SIGNAL(ViewRepaint()), ui->PictureScreen, SLOT(Repaint_()));

    MouseCursor(0);
    SetWindow(Settings_->ViewX, Settings_->ViewY, Settings_->ViewW, Settings_->ViewH, Settings_->ViewFullscreen);
    QObject::connect(&WinSettings_, SIGNAL(SetWindow(int, int, int, int, bool)), this, SLOT(SetWindow(int, int, int, int, bool)));
    QObject::connect(&WinSettings_, SIGNAL(RunCommand(int)), this, SLOT(RunCommand(int)));

    PicThread_ = new PicThread();
    PicThread_->PicNetwork_ = PicNetwork_;
    PicThread_->TransformCore_ = TransformCore_;
    PicThread_->PictureScreen = ui->PictureScreen;
    PicThread_->Settings_ = Settings_;
    PicThread_->Recorder_ = WinRecorder_.Recorder_;
    PicThread_->TextCapture_ = WinRecorder_.Recorder_->TextCapture_;
    WinSettings_.Settings_ = Settings_;
    WinSettings_.PicThread_ = PicThread_;
    QObject::connect(PicThread_, SIGNAL(UpdatePixmap(QImage*)), this, SLOT(UpdatePixmap(QImage*)));
    QObject::connect(PicThread_, SIGNAL(PicSetRefresh()), &WinSettings_, SLOT(PicSetRefresh()));
    QObject::connect(PicThread_, SIGNAL(RecorderInit()), &WinRecorder_, SLOT(RecorderInit()));
    QObject::connect(PicThread_, SIGNAL(TextCaptureFinish()), &WinRecorder_, SLOT(TextCaptureFinish()));

    ui->PictureScreen->Settings_ = Settings_;
    TransformCore_->ListLoad(Eden::ApplicationDirectory() + "Transform.txt");

    setMouseTracking(true);
    ui->PictureScreen->setMouseTracking(true);

    RunSettings();



    for (int I = 0; I < Settings_->GoogleCloudSlotCount; I++)
    {
        QNetworkRequest R;
        DelayLineAsyncSlot DelayLineAsyncSlot_;
        DelayLineAsyncSlot_.State = 0;
        DelayLineAsyncSlot_.Id = 0;
        DelayLineAsyncSlot_.Pos = 0;
        DelayLineAsyncSlot_.Manager = new QNetworkAccessManager();
        DelayLineAsyncSlot_.Request = R;
        DelayLineAsyncSlotList.push_back(DelayLineAsyncSlot_);

        QObject::connect(DelayLineAsyncSlotList[I].Manager, &QNetworkAccessManager::finished,
            this, [=](QNetworkReply *reply)
            {
                PicThread::DelayLineAsyncThreadData DelayLineAsyncThreadData_;
                DelayLineAsyncThreadData_.Type = DelayLineAsyncSlotList[I].Type;
                DelayLineAsyncThreadData_.Id = DelayLineAsyncSlotList[I].Id;
                DelayLineAsyncThreadData_.Pos = DelayLineAsyncSlotList[I].Pos;
                if (reply->error())
                {
                    DelayLineAsyncThreadData_.Url = reply->errorString();
                    DelayLineAsyncThreadData_.Data = reply->readAll();
                    PicThread_->DelayLineAsyncThreadResult.push(DelayLineAsyncThreadData_);
                }
                else
                {
                    DelayLineAsyncThreadData_.Url = "";
                    DelayLineAsyncThreadData_.Data = reply->readAll();

                    PicThread_->DelayLineAsyncThreadResult.push(DelayLineAsyncThreadData_);
                }
                DelayLineAsyncSlotList[I].State = 0;
            }
        );
    }
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
    delete PicNetwork_;
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
    while (!PicThread_->DelayLineAsyncThreadRequest.empty())
    {
        PicThread::DelayLineAsyncThreadData DelayLineAsyncThreadData_ = PicThread_->DelayLineAsyncThreadRequest.front();
        for (int I = 0; I < DelayLineAsyncSlotList.size(); I++)
        {
            if (DelayLineAsyncSlotList[I].State == 0)
            {
                DelayLineAsyncSlotList[I].Id = DelayLineAsyncThreadData_.Id;
                DelayLineAsyncSlotList[I].Pos = DelayLineAsyncThreadData_.Pos;
                DelayLineAsyncSlotList[I].Type = DelayLineAsyncThreadData_.Type;
                DelayLineAsyncSlotList[I].State = 1;
                DelayLineAsyncSlotList[I].Request.setRawHeader("Content-Type", "application/json");
                DelayLineAsyncSlotList[I].Request.setUrl(QUrl(DelayLineAsyncThreadData_.Url));

                if (DelayLineAsyncThreadData_.Data.size() > 0)
                {
                    DelayLineAsyncSlotList[I].Manager->post(DelayLineAsyncSlotList[I].Request, DelayLineAsyncThreadData_.Data);
                }
                else
                {
                    DelayLineAsyncSlotList[I].Manager->get(DelayLineAsyncSlotList[I].Request);
                }
                break;
            }
        }
        PicThread_->DelayLineAsyncThreadRequest.pop();
    }

    if (Settings_->_PicDstNet)
    {
        PicNetwork_->PicSend(Img);
        return;
    }
    if (Settings_->MTX.try_lock())
    {
        ui->PictureScreen->PaintMTX.lock();
        if (Img != NULL)
        {
            if (ui->PictureScreen->ImgX != Img)
            {
                if (ui->PictureScreen->ImgX != NULL)
                {
                    delete ui->PictureScreen->ImgX;
                }
            }
            ui->PictureScreen->ImgX = Img;
            if (Settings_->NeedRecalc)
            {
                Settings_->NeedRecalc = false;
                ui->PictureScreen->CalcDraw();
            }
        }
        else
        {
            if (ui->PictureScreen->ImgX != NULL)
            {
                delete ui->PictureScreen->ImgX;
            }
            ui->PictureScreen->ImgX = NULL;
        }
        ui->PictureScreen->PaintMTX.unlock();
        ui->PictureScreen->repaint();
        Settings_->MTX.unlock();
    }
}

void MainWindow::on_PictureScreen_MouseMove(int Btn, int X, int Y)
{
    int _W = this->width();
    int _H = this->height();
    MouseCursorMode(MouseBtn, X, Y, _W, _H);

    if (MouseBtn)
    {
        int _X = this->x();
        int _Y = this->y();

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
        SetWindow(_X, _Y, _W, _H, Settings_->ViewFullscreen);
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
    MouseCursorMode(true, X, Y, PicW, PicH);

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
        MouseBtn = true;
    }
}

void MainWindow::on_PictureScreen_MouseRelease(int Btn, int X, int Y)
{
    MouseBtn = false;
    MouseCursorMode(false, X, Y, this->width(), this->height());
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

void MainWindow::SetWindow(int X, int Y, int W, int H, bool FullScreen)
{
    if (FullScreen_ != FullScreen)
    {
        if (FullScreen)
        {
            showFullScreen();
        }
        else
        {
            showNormal();
            this->setGeometry(X, Y, W, H);
        }
    }
    else
    {
        if (!FullScreen)
        {
            this->setGeometry(X, Y, W, H);
        }
    }

    ui->PictureScreen->DrawMarginTop = Settings_->ViewMarginTop;
    ui->PictureScreen->DrawMarginLeft = Settings_->ViewMarginLeft;
    ui->PictureScreen->DrawMarginRight = Settings_->ViewMarginRight;
    ui->PictureScreen->DrawMarginBottom = Settings_->ViewMarginBottom;
    ui->PictureScreen->DrawOffsetX = Settings_->ViewOffsetX;
    ui->PictureScreen->DrawOffsetY = Settings_->ViewOffsetY;

    ui->PictureScreen->DrawStretched = Settings_->ViewStretched;
    ui->PictureScreen->setGeometry(0, 0, W, H);
    ui->PictureScreen->CalcDraw();

    FullScreen_ = FullScreen;
}

void MainWindow::RunCommand(int Cmd)
{
    if (Cmd == 0)
    {
        close();
    }
    if (Cmd == 1)
    {
        ui->PictureScreen->CalcDraw();
    }
    if (Cmd == 2)
    {
        SetBackColor();
    }
}

void MainWindow::FullScreenEvent()
{
    if (FullScreen__ != FullScreen_)
    {
        if (!FullScreen_)
        {
            setGeometry(Settings_->ViewX, Settings_->ViewY, Settings_->ViewW, Settings_->ViewH);
        }
        Settings_->ViewX = this->x();
        Settings_->ViewY = this->y();
        Settings_->ViewW = this->width();
        Settings_->ViewH = this->height();

        FullScreen__ = FullScreen_;
        WinSettings_.LoadSettings(true);
        WinSettings_.UpdateWindow();
    }
}

void MainWindow::moveEvent(QResizeEvent *event)
{
    FullScreenEvent();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    FullScreenEvent();
}

void MainWindow::MouseCursor(int Cur)
{
    if (Cur == MouseCursorType)
    {
        return;
    }
    switch (Cur)
    {
        case 0:
            setCursor(Qt::BlankCursor);
            ui->PictureScreen->setCursor(Qt::BlankCursor);
            break;
        case 1:
            unsetCursor();
            ui->PictureScreen->unsetCursor();
            break;
        case 2:
            setCursor(Qt::BlankCursor);
            ui->PictureScreen->setCursor(Qt::PointingHandCursor);
            break;
        case 3:
            setCursor(Qt::BlankCursor);
            ui->PictureScreen->setCursor(Qt::SizeHorCursor);
            break;
        case 4:
            setCursor(Qt::BlankCursor);
            ui->PictureScreen->setCursor(Qt::SizeVerCursor);
            break;
    }
    MouseCursorType = Cur;
}

void MainWindow::MouseCursorVisible(QCursor Cur)
{
    setCursor(Cur);
    ui->PictureScreen->setCursor(Cur);
}

void MainWindow::MouseCursorMode(bool Btn, int X, int Y, int W, int H)
{
    bool _SizeModeH = false;
    bool _SizeModeV = false;
    int MouseMarginX = Min(Settings_->MouseMargin, W / 2);
    if (X < MouseMarginX) { _SizeModeH = true; }
    if (X >= (W - MouseMarginX)) { _SizeModeH = true; }
    int MouseMarginY = Min(Settings_->MouseMargin, H / 2);
    if (Y < MouseMarginY) { _SizeModeV = true; }
    if (Y >= (H - MouseMarginY)) { _SizeModeV = true; }
    if ((!_SizeModeH) && (!_SizeModeV))
    {
        if (Btn)
        {
            MouseCursor(1);
        }
        else
        {
            MouseCursor(0);
        }
    }
    else
    {
        if ((_SizeModeH) && (_SizeModeV))
        {
            MouseCursor(2);
        }
        else
        {
            if (_SizeModeH)
            {
                MouseCursor(3);
            }
            else
            {
                MouseCursor(4);
            }
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    WinRecorder_.close();
}

void MainWindow::ShowRecorder()
{
    WinRecorder_.show();
    WinRecorder_.activateWindow();
    WinRecorder_.raise();
    WinRecorder_.setFocus();
    WinRecorder_.AfterShow();
}
