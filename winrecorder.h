#ifndef WINRECORDER_H
#define WINRECORDER_H

#include <QDialog>
#include "recorder.h"
#include <QTimer>
#include <QCloseEvent>
#include <QFileDialog>

namespace Ui {
class WinRecorder;
}

class WinRecorder : public QDialog
{
    Q_OBJECT

public:
    explicit WinRecorder(QWidget *parent = nullptr);
    ~WinRecorder();
    void Init();

    Recorder * Recorder_;
    QTimer * FPS;
    void AfterShow();
    void UpdateSettings();

private slots:
    void on_ModeRestart_clicked();
    void closeEvent(QCloseEvent *event);
    void FPSDisp();
    void on_RecRecord_clicked();

    void on_RecRecord0_clicked();

    void on_RecStop_clicked();

    void on_RecStill_clicked();

    void on_RecFwd1_clicked();

    void on_RecFwd2_clicked();

    void on_RecFwd3_clicked();

    void on_RecFwd4_clicked();

    void on_RecRev1_clicked();

    void on_RecRev2_clicked();

    void on_RecRev3_clicked();

    void on_RecRev4_clicked();

    void RecorderInit();

    void on_FileBrowse_clicked();

    void on_RecText_clicked();

private:
    Ui::WinRecorder *ui;
    bool FirstShow = true;

signals:
    void LivePicRestart();

private slots:
    void TextCaptureFinish();


    void on_FileApply_clicked();
    void on_FileExport_clicked();
    void on_ModeT_currentIndexChanged(int index);
    void on_FileT_textChanged(const QString &arg1);
    void on_FormatT_currentIndexChanged(int index);
    void on_FormatQ_valueChanged(int arg1);
    void on_FileMemo_toggled(bool checked);
    void on_TextTimeT_valueChanged(int arg1);
    void on_Speed1T_valueChanged(int arg1);
    void on_Speed2T_valueChanged(int arg1);
};

#endif // WINRECORDER_H
