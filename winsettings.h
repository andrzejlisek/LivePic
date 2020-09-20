#ifndef WINSETTINGS_H
#define WINSETTINGS_H

#include <QDialog>
#include <picthread.h>
#include "settings.h"
#include <QTimer>
#include "eden.h"
#include <QColorDialog>
#include <QFileDialog>
#include "transformcore.h"
#include <QInputDialog>
#include "picnetwork.h"

namespace Ui {
class WinSettings;
}

class WinSettings : public QDialog
{
    Q_OBJECT

public:
    explicit WinSettings(QWidget *parent = 0);
    ~WinSettings();
    PicThread * PicThread_;
    PicNetwork * PicNetwork_;
    Settings * Settings_;
    void LoadSettings(bool Window);
    void AfterShow();
    QTimer * FPS;
    bool FPS_ = false;
    void UpdateWindow();
    bool EventActive;
    void WinCommand(int I);
    bool WorkPause();
    void WorkResume(bool Paused);
    TransformCore * TransformCore_;
    void TransListRefresh();
    void TransListRefreshItem();
    void TransformSet();
    void TransformGet();
    bool TransformSetAllow = true;
    string InputBox(string Query, string Title, string Default);
    bool InputBoxOK;
    bool ForceCloseEvent = 0;

signals:
    void SetWindow(int X, int Y, int W, int H, bool Fullscreen);
    void RunCommand(int Cmd);
    void ViewRepaint();

public slots:
    void PicNetLog(QString Msg);
    void PicSetRefresh();

private slots:
    void closeEvent(QCloseEvent *event);


    void FPSDisp();
    void on_MainStart_clicked();
    void on_MainStop_clicked();
    void on_MainRestart_clicked();

    void on_ViewXT_valueChanged(int arg1);

    void on_ViewYT_valueChanged(int arg1);

    void on_ViewWT_valueChanged(int arg1);

    void on_ViewHT_valueChanged(int arg1);

    void on_MarginLeftT_valueChanged(int arg1);

    void on_MarginTopT_valueChanged(int arg1);

    void on_MarginRightT_valueChanged(int arg1);

    void on_MarginBottomT_valueChanged(int arg1);

    void on_PicThreadsT_valueChanged(int arg1);

    void on_PicXT_valueChanged(int arg1);

    void on_PicYT_valueChanged(int arg1);

    void on_PicWT_valueChanged(int arg1);

    void on_PicHT_valueChanged(int arg1);

    void on_MainClose_clicked();

    void on_ViewStretch_currentIndexChanged(int index);

    void on_PicFollowMouse_toggled(bool checked);

    void on_OffsetXT_valueChanged(int arg1);

    void on_OffsetYT_valueChanged(int arg1);

    void on_PicMouseSizeT_valueChanged(int arg1);

    void on_ViewColor_clicked();

    void on_MainClose0_clicked();

    void on_PicThreadsT0_valueChanged(int arg1);

    void on_PicMouseTypeT_currentIndexChanged(int index);

    void on_TransListLoad_clicked();

    void on_TransListSave_clicked();

    void on_TransAdd_clicked();

    void on_TransRemove_clicked();

    void on_TransMoveUp_clicked();

    void on_TransMoveDown_clicked();

    void on_TransEnable_clicked();

    void on_Trans0Op0_toggled(bool checked);

    void on_Trans0Op1_toggled(bool checked);

    void on_Trans0Op2_toggled(bool checked);

    void on_Trans0Op3_toggled(bool checked);

    void on_Trans0File_textChanged(const QString &arg1);

    void on_Trans0BriR_valueChanged(int value);

    void on_Trans0BriG_valueChanged(int value);

    void on_Trans0BriB_valueChanged(int value);

    void on_Trans0ConR_valueChanged(int value);

    void on_Trans0ConG_valueChanged(int value);

    void on_Trans0ConB_valueChanged(int value);

    void on_Trans1Op0_toggled(bool checked);

    void on_Trans1Op1_toggled(bool checked);

    void on_Trans1Op2_toggled(bool checked);

    void on_Trans1Op3_toggled(bool checked);

    void on_Trans1File_textChanged(const QString &arg1);

    void on_Trans1Sat_valueChanged(int value);

    void on_ProcessTabs_currentChanged(int index);

    void on_TransListView_currentRowChanged(int currentRow);

    void on_Trans1Op4_toggled(bool checked);

    void on_Trans1Chan_currentIndexChanged(int index);

    void on_Trans2Offset1R_textChanged(const QString &arg1);

    void on_Trans2Offset1G_textChanged(const QString &arg1);

    void on_Trans2Offset1B_textChanged(const QString &arg1);

    void on_Trans2GainR_textChanged(const QString &arg1);

    void on_Trans2GainG_textChanged(const QString &arg1);

    void on_Trans2GainB_textChanged(const QString &arg1);

    void on_Trans2Offset2R_textChanged(const QString &arg1);

    void on_Trans2Offset2G_textChanged(const QString &arg1);

    void on_Trans2Offset2B_textChanged(const QString &arg1);

    void on_Trans2CommonT_currentIndexChanged(int index);

    void on_Trans2ChanR00_textChanged(const QString &arg1);

    void on_Trans2ChanR01_textChanged(const QString &arg1);

    void on_Trans2ChanR02_textChanged(const QString &arg1);

    void on_Trans2ChanR03_textChanged(const QString &arg1);

    void on_Trans2ChanR04_textChanged(const QString &arg1);

    void on_Trans2ChanR10_textChanged(const QString &arg1);

    void on_Trans2ChanR11_textChanged(const QString &arg1);

    void on_Trans2ChanR12_textChanged(const QString &arg1);

    void on_Trans2ChanR13_textChanged(const QString &arg1);

    void on_Trans2ChanR14_textChanged(const QString &arg1);

    void on_Trans2ChanR20_textChanged(const QString &arg1);

    void on_Trans2ChanR21_textChanged(const QString &arg1);

    void on_Trans2ChanR22_textChanged(const QString &arg1);

    void on_Trans2ChanR23_textChanged(const QString &arg1);

    void on_Trans2ChanR24_textChanged(const QString &arg1);

    void on_Trans2ChanR30_textChanged(const QString &arg1);

    void on_Trans2ChanR31_textChanged(const QString &arg1);

    void on_Trans2ChanR32_textChanged(const QString &arg1);

    void on_Trans2ChanR33_textChanged(const QString &arg1);

    void on_Trans2ChanR34_textChanged(const QString &arg1);

    void on_Trans2ChanR40_textChanged(const QString &arg1);

    void on_Trans2ChanR41_textChanged(const QString &arg1);

    void on_Trans2ChanR42_textChanged(const QString &arg1);

    void on_Trans2ChanR43_textChanged(const QString &arg1);

    void on_Trans2ChanR44_textChanged(const QString &arg1);

    void on_Trans2ChanG00_textChanged(const QString &arg1);

    void on_Trans2ChanG01_textChanged(const QString &arg1);

    void on_Trans2ChanG02_textChanged(const QString &arg1);

    void on_Trans2ChanG03_textChanged(const QString &arg1);

    void on_Trans2ChanG04_textChanged(const QString &arg1);

    void on_Trans2ChanG10_textChanged(const QString &arg1);

    void on_Trans2ChanG11_textChanged(const QString &arg1);

    void on_Trans2ChanG12_textChanged(const QString &arg1);

    void on_Trans2ChanG13_textChanged(const QString &arg1);

    void on_Trans2ChanG14_textChanged(const QString &arg1);

    void on_Trans2ChanG20_textChanged(const QString &arg1);

    void on_Trans2ChanG21_textChanged(const QString &arg1);

    void on_Trans2ChanG22_textChanged(const QString &arg1);

    void on_Trans2ChanG23_textChanged(const QString &arg1);

    void on_Trans2ChanG24_textChanged(const QString &arg1);

    void on_Trans2ChanG30_textChanged(const QString &arg1);

    void on_Trans2ChanG31_textChanged(const QString &arg1);

    void on_Trans2ChanG32_textChanged(const QString &arg1);

    void on_Trans2ChanG33_textChanged(const QString &arg1);

    void on_Trans2ChanG34_textChanged(const QString &arg1);

    void on_Trans2ChanG40_textChanged(const QString &arg1);

    void on_Trans2ChanG41_textChanged(const QString &arg1);

    void on_Trans2ChanG42_textChanged(const QString &arg1);

    void on_Trans2ChanG43_textChanged(const QString &arg1);

    void on_Trans2ChanG44_textChanged(const QString &arg1);

    void on_Trans2ChanB00_textChanged(const QString &arg1);

    void on_Trans2ChanB01_textChanged(const QString &arg1);

    void on_Trans2ChanB02_textChanged(const QString &arg1);

    void on_Trans2ChanB03_textChanged(const QString &arg1);

    void on_Trans2ChanB04_textChanged(const QString &arg1);

    void on_Trans2ChanB10_textChanged(const QString &arg1);

    void on_Trans2ChanB11_textChanged(const QString &arg1);

    void on_Trans2ChanB12_textChanged(const QString &arg1);

    void on_Trans2ChanB13_textChanged(const QString &arg1);

    void on_Trans2ChanB14_textChanged(const QString &arg1);

    void on_Trans2ChanB20_textChanged(const QString &arg1);

    void on_Trans2ChanB21_textChanged(const QString &arg1);

    void on_Trans2ChanB22_textChanged(const QString &arg1);

    void on_Trans2ChanB23_textChanged(const QString &arg1);

    void on_Trans2ChanB24_textChanged(const QString &arg1);

    void on_Trans2ChanB30_textChanged(const QString &arg1);

    void on_Trans2ChanB31_textChanged(const QString &arg1);

    void on_Trans2ChanB32_textChanged(const QString &arg1);

    void on_Trans2ChanB33_textChanged(const QString &arg1);

    void on_Trans2ChanB34_textChanged(const QString &arg1);

    void on_Trans2ChanB40_textChanged(const QString &arg1);

    void on_Trans2ChanB41_textChanged(const QString &arg1);

    void on_Trans2ChanB42_textChanged(const QString &arg1);

    void on_Trans2ChanB43_textChanged(const QString &arg1);

    void on_Trans2ChanB44_textChanged(const QString &arg1);

    void on_Trans4Op0_toggled(bool checked);

    void on_Trans4Op1_toggled(bool checked);

    void on_Trans4Size_currentIndexChanged(int index);

    void on_Trans4Size1W_textChanged(const QString &arg1);

    void on_Trans4Size1H_textChanged(const QString &arg1);

    void on_Trans4Size2W_textChanged(const QString &arg1);

    void on_Trans4Size2H_textChanged(const QString &arg1);

    void on_Trans4Scale_currentIndexChanged(int index);

    void on_Trans4ScaleChannels_toggled(bool checked);

    void on_Trans3Color1_textChanged(const QString &arg1);

    void on_Trans3Color2_textChanged(const QString &arg1);

    void on_Trans3Color3_textChanged(const QString &arg1);

    void on_Trans3Color4_textChanged(const QString &arg1);

    void on_Trans3Matrix00_textChanged(const QString &arg1);

    void on_Trans3Matrix01_textChanged(const QString &arg1);

    void on_Trans3Matrix02_textChanged(const QString &arg1);

    void on_Trans3Matrix03_textChanged(const QString &arg1);

    void on_Trans3Matrix04_textChanged(const QString &arg1);

    void on_Trans3Matrix10_textChanged(const QString &arg1);

    void on_Trans3Matrix11_textChanged(const QString &arg1);

    void on_Trans3Matrix12_textChanged(const QString &arg1);

    void on_Trans3Matrix13_textChanged(const QString &arg1);

    void on_Trans3Matrix14_textChanged(const QString &arg1);

    void on_Trans3Matrix20_textChanged(const QString &arg1);

    void on_Trans3Matrix21_textChanged(const QString &arg1);

    void on_Trans3Matrix22_textChanged(const QString &arg1);

    void on_Trans3Matrix23_textChanged(const QString &arg1);

    void on_Trans3Matrix24_textChanged(const QString &arg1);

    void on_Trans3Matrix30_textChanged(const QString &arg1);

    void on_Trans3Matrix31_textChanged(const QString &arg1);

    void on_Trans3Matrix32_textChanged(const QString &arg1);

    void on_Trans3Matrix33_textChanged(const QString &arg1);

    void on_Trans3Matrix34_textChanged(const QString &arg1);

    void on_Trans3Matrix40_textChanged(const QString &arg1);

    void on_Trans3Matrix41_textChanged(const QString &arg1);

    void on_Trans3Matrix42_textChanged(const QString &arg1);

    void on_Trans3Matrix43_textChanged(const QString &arg1);

    void on_Trans3Matrix44_textChanged(const QString &arg1);

    void on_Trans3Add_clicked();

    void on_Trans3Rem_clicked();

    void on_Trans3MovePrev_clicked();

    void on_Trans3MoveNext_clicked();

    void on_Trans3DispPrev_clicked();

    void on_Trans3DispNext_clicked();

    void on_Trans0FileBtn_clicked();

    void on_Trans1FileBtn_clicked();

    void on_Trans0FileSave_clicked();

    void on_Trans1FileSave_clicked();

    void on_Trans0InvR_valueChanged(int value);

    void on_Trans0InvG_valueChanged(int value);

    void on_Trans0InvB_valueChanged(int value);

    void on_Trans5RotateT_currentIndexChanged(int index);

    void on_DelayLineCountT_valueChanged(int arg1);

    void on_DelayLineFileNameT_textChanged(const QString &arg1);

    void on_DelayLineFileNameB_clicked();

    void on_Trans4LcdOp_currentIndexChanged(int index);

    void on_Trans4LcdType_currentIndexChanged(int index);

    void on_Trans4Op2_toggled(bool checked);

    void on_Trans1YuvType_currentIndexChanged(int index);

    void on_Trans1YuvWeightR_textChanged(const QString &arg1);

    void on_Trans1YuvWeightG_textChanged(const QString &arg1);

    void on_Trans1YuvWeightB_textChanged(const QString &arg1);

    void on_Trans4LcdWeightR_textChanged(const QString &arg1);

    void on_Trans4LcdWeightG_textChanged(const QString &arg1);

    void on_Trans4LcdWeightB_textChanged(const QString &arg1);

    void on_Trans1YuvLumaT_textChanged(const QString &arg1);

    void on_PicMouseMarginT_valueChanged(int arg1);

    void on_PicGammaT_valueChanged(int arg1);

    void on_Trans4LcdInterpolation_toggled(bool checked);

    void on_PicMouseSizeTT_valueChanged(int arg1);

    void on_Trans2Gamma_toggled(bool checked);

    void on_Trans0Op4_toggled(bool checked);

    void on_Trans0GammaR_valueChanged(int value);

    void on_Trans0GammaG_valueChanged(int value);

    void on_Trans0GammaB_valueChanged(int value);

    void on_Trans0Gamma_toggled(bool checked);

    void on_Trans1Gamma_toggled(bool checked);

    void on_Trans3Rot0_currentIndexChanged(int index);

    void on_Trans3Rot1_currentIndexChanged(int index);

    void on_Trans3Rot2_currentIndexChanged(int index);

    void on_Trans3Rot3_currentIndexChanged(int index);

    void on_Trans0ConBiasR_valueChanged(int value);

    void on_Trans0ConBiasG_valueChanged(int value);

    void on_Trans0ConBiasB_valueChanged(int value);

    void on_Trans4LcdChromaB_currentIndexChanged(int index);

    void on_Trans4LcdChromaV_currentIndexChanged(int index);

    void on_Trans4LcdChromaX_currentIndexChanged(int index);

    void on_OnTopPictuceC_toggled(bool checked);

    void on_OnTopSettingsC_toggled(bool checked);

    void on_SetCloseApp_toggled(bool checked);

    void on_ThrottleT_valueChanged(int arg1);

    void on_NetAddrT_textChanged(const QString &arg1);

    void on_NetPortT_valueChanged(int arg1);

    void on_NetStartSrv_clicked();

    void on_NetStartCli_clicked();

    void on_NetStop_clicked();

    void on_NetMsgSend_clicked();

    void on_NetMsgClear_clicked();

    void on_NetPicSrcDst_currentIndexChanged(int index);

    void on_NetQuality1T_valueChanged(int arg1);

    void on_NetQuality2T_valueChanged(int arg1);

    void on_ScreenBoundsX1_valueChanged(int arg1);

    void on_ScreenBoundsY1_valueChanged(int arg1);

    void on_ScreenBoundsX2_valueChanged(int arg1);

    void on_ScreenBoundsY2_valueChanged(int arg1);

    void on_NetStartBind_clicked();

    void on_ViewFullscreenT_toggled(bool checked);

    void on_ScreenBoundsAuto_clicked();

    void on_NetPicSrcDstRefresh_clicked();

    void on_NetMsgTest_clicked();

private:
    Ui::WinSettings *ui;
    bool Working;
    QString LastPath;
    void SaveLastPath(QString X, bool OpenDir);
};

#endif // WINSETTINGS_H
