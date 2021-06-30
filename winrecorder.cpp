#include "winrecorder.h"
#include "ui_winrecorder.h"

WinRecorder::WinRecorder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinRecorder)
{
    ui->setupUi(this);
    FPS = new QTimer(this);
    connect(FPS, SIGNAL(timeout()), this, SLOT(FPSDisp()));
}

WinRecorder::~WinRecorder()
{
    delete ui;
}

void WinRecorder::Init()
{
    if (Recorder_->Settings_->RecorderWindowOnTop)
    {
        Qt::WindowFlags flags = this->windowFlags();
        flags = flags | Qt::WindowStaysOnTopHint;
        setWindowFlags(flags);
    }
}

void WinRecorder::on_ModeRestart_clicked()
{
    Recorder_->RecStop();
    Recorder_->PlayStop();
    Recorder_->SequenceClose();
    emit LivePicRestart();
}

void WinRecorder::AfterShow()
{
    ui->ModeT->setCurrentIndex(Recorder_->Settings_->RecorderMode);
    ui->FormatT->setCurrentIndex(Recorder_->Settings_->RecorderFormat);
    ui->FormatQ->setValue(Recorder_->Settings_->RecorderQuality);
    ui->FileT->setText(Eden::ToQStr(Recorder_->Settings_->RecorderDirectory));
    ui->Speed1T->setValue(Recorder_->Settings_->RecorderFactor1);
    ui->Speed2T->setValue(Recorder_->Settings_->RecorderFactor2);
    ui->TextTimeT->setValue(Recorder_->Settings_->RecorderTextTimeout);
    ui->FileMemo->setChecked(Recorder_->Settings_->RecorderMemory);
    if (FirstShow)
    {
        on_FileApply_clicked();
        FirstShow = false;
    }
    FPS->start(250);
}

void WinRecorder::UpdateSettings()
{
    if (!FirstShow)
    {
        Recorder_->Settings_->RecorderMode = ui->ModeT->currentIndex();
        Recorder_->Settings_->RecorderFormat = ui->FormatT->currentIndex();
        Recorder_->Settings_->RecorderQuality = ui->FormatQ->value();
        Recorder_->Settings_->RecorderDirectory = Eden::ToStr(ui->FileT->text());
        Recorder_->Settings_->RecorderFactor1 = ui->Speed1T->value();
        Recorder_->Settings_->RecorderFactor2 = ui->Speed2T->value();
        Recorder_->Settings_->RecorderTextTimeout = ui->TextTimeT->value();
        Recorder_->Settings_->RecorderMemory = ui->FileMemo->isChecked();
    }
}

void WinRecorder::closeEvent(QCloseEvent *event)
{
    FPS->stop();
    event->accept();
}

void WinRecorder::FPSDisp()
{
    ui->RecPosition->setMaximum(Recorder_->PicCount > 1 ? Recorder_->PicCount - 1 : 1);
    ui->RecPosition->setValue(Recorder_->PicPos);
    ui->RecPosition->setTextVisible(true);
    ui->RecPosition->setFormat(Eden::ToQStr(Recorder_->PicPos) + " / " + Eden::ToQStr(Recorder_->PicCount));
    ui->RecPosition->update();

    if (Recorder_->PicExportT > 0)
    {
        ui->TextTimeProgress->setMaximum(Recorder_->PicCount);
        ui->TextTimeProgress->setValue(Recorder_->PicExportI);
    }
    else
    {
        ui->TextTimeProgress->setMaximum(Recorder_->TextCaptureTimerL);
        if (Recorder_->TextCaptureTimer == 0)
        {
            ui->TextTimeProgress->setValue(0);
        }
        else
        {
            ui->TextTimeProgress->setValue(Recorder_->TextCaptureTimerL - Recorder_->TextCaptureTimer);
        }
    }
    ui->TextTimeProgress->update();

    ui->PicSizeT->setText(Eden::ToQStr(Recorder_->PicW) + "x" + Eden::ToQStr(Recorder_->PicH));
}

void WinRecorder::on_RecRecord_clicked()
{
    Recorder_->RecStart();
}

void WinRecorder::on_RecRecord0_clicked()
{
    Recorder_->RecStop();
}

void WinRecorder::on_RecStop_clicked()
{
    Recorder_->PlayStop();
}

void WinRecorder::on_RecStill_clicked()
{
    Recorder_->PlayStart(0, 1);
}

void WinRecorder::on_RecFwd1_clicked()
{
    Recorder_->PlayStart(1, 0);
}

void WinRecorder::on_RecFwd2_clicked()
{
    Recorder_->PlayStart(1, Recorder_->Settings_->RecorderFactor1);
}

void WinRecorder::on_RecFwd3_clicked()
{
    Recorder_->PlayStart(1, 1);
}

void WinRecorder::on_RecFwd4_clicked()
{
    Recorder_->PlayStart(Recorder_->Settings_->RecorderFactor2, 1);
}

void WinRecorder::on_RecRev1_clicked()
{
    Recorder_->PlayStart(-1, 0);
}

void WinRecorder::on_RecRev2_clicked()
{
    Recorder_->PlayStart(-1, Recorder_->Settings_->RecorderFactor1);
}

void WinRecorder::on_RecRev3_clicked()
{
    Recorder_->PlayStart(-1, 1);
}

void WinRecorder::on_RecRev4_clicked()
{
    Recorder_->PlayStart(0 - Recorder_->Settings_->RecorderFactor2, 1);
}

void WinRecorder::RecorderInit()
{
    Recorder_->Init();
}

void WinRecorder::on_FileBrowse_clicked()
{
    QString FN = QFileDialog::getExistingDirectory(this, "Select base directory");
    ui->FileT->setText(FN);
}

void WinRecorder::on_RecText_clicked()
{
    Recorder_->ExportText(Eden::ToStr(ui->FileT->text()), ui->TextTimeT->value());
}

void WinRecorder::TextCaptureFinish()
{
    Recorder_->TextCapture_->Save(Recorder_->TextCaptureFileName);
}

void WinRecorder::on_FileApply_clicked()
{
    Recorder_->Apply(ui->FileMemo->isChecked(), Eden::ToStr(ui->FileT->text()), ui->FormatT->currentIndex(), ui->FormatQ->value());
}

void WinRecorder::on_FileExport_clicked()
{
    Recorder_->ExportPic(Eden::ToStr(ui->FileT->text()), ui->TextTimeT->value());
}

void WinRecorder::on_ModeT_currentIndexChanged(int index)
{
    UpdateSettings();
}

void WinRecorder::on_FileT_textChanged(const QString &arg1)
{
    UpdateSettings();
}

void WinRecorder::on_FormatT_currentIndexChanged(int index)
{
    UpdateSettings();
}

void WinRecorder::on_FormatQ_valueChanged(int arg1)
{
    UpdateSettings();
}

void WinRecorder::on_FileMemo_toggled(bool checked)
{
    UpdateSettings();
}

void WinRecorder::on_TextTimeT_valueChanged(int arg1)
{
    UpdateSettings();
}

void WinRecorder::on_Speed1T_valueChanged(int arg1)
{
    UpdateSettings();
}

void WinRecorder::on_Speed2T_valueChanged(int arg1)
{
    UpdateSettings();
}
