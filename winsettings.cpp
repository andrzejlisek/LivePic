#include "winsettings.h"
#include "ui_winsettings.h"

WinSettings::WinSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinSettings)
{
    // https://cloud.google.com/translate/docs/languages
    // ceb (ISO-639-2)
    // zh-CN or zh (BCP-47)
    // zh-TW (BCP-47)
    // haw (ISO-639-2)
    // he or iw
    // hmn (ISO-639-2)
    LangCode.push_back("");   LangName.push_back("");
    LangCode.push_back("af"); LangName.push_back("Afrikaans");
    LangCode.push_back("sq"); LangName.push_back("Albanian");
    LangCode.push_back("am"); LangName.push_back("Amharic");
    LangCode.push_back("ar"); LangName.push_back("Arabic");
    LangCode.push_back("hy"); LangName.push_back("Armenian");
    LangCode.push_back("az"); LangName.push_back("Azerbaijani");
    LangCode.push_back("eu"); LangName.push_back("Basque");
    LangCode.push_back("be"); LangName.push_back("Belarusian");
    LangCode.push_back("bn"); LangName.push_back("Bengali");
    LangCode.push_back("bs"); LangName.push_back("Bosnian");
    LangCode.push_back("bg"); LangName.push_back("Bulgarian");
    LangCode.push_back("ca"); LangName.push_back("Catalan");
    LangCode.push_back("ceb");LangName.push_back("Cebuano");
    LangCode.push_back("zh-CN"); LangName.push_back("Chinese (Simplified)");
    LangCode.push_back("zh-TW"); LangName.push_back("Chinese (Traditional)");
    LangCode.push_back("co"); LangName.push_back("Corsican");
    LangCode.push_back("hr"); LangName.push_back("Croatian");
    LangCode.push_back("cs"); LangName.push_back("Czech");
    LangCode.push_back("da"); LangName.push_back("Danish");
    LangCode.push_back("nl"); LangName.push_back("Dutch");
    LangCode.push_back("en"); LangName.push_back("English");
    LangCode.push_back("eo"); LangName.push_back("Esperanto");
    LangCode.push_back("et"); LangName.push_back("Estonian");
    LangCode.push_back("fi"); LangName.push_back("Finnish");
    LangCode.push_back("fr"); LangName.push_back("French");
    LangCode.push_back("fy"); LangName.push_back("Frisian");
    LangCode.push_back("gl"); LangName.push_back("Galician");
    LangCode.push_back("ka"); LangName.push_back("Georgian");
    LangCode.push_back("de"); LangName.push_back("German");
    LangCode.push_back("el"); LangName.push_back("Greek");
    LangCode.push_back("gu"); LangName.push_back("Gujarati");
    LangCode.push_back("ht"); LangName.push_back("Haitian Creole");
    LangCode.push_back("ha"); LangName.push_back("Hausa");
    LangCode.push_back("haw");LangName.push_back("Hawaiian");
    LangCode.push_back("he"); LangName.push_back("Hebrew");
    LangCode.push_back("hi"); LangName.push_back("Hindi");
    LangCode.push_back("hmn");LangName.push_back("Hmong");
    LangCode.push_back("hu"); LangName.push_back("Hungarian");
    LangCode.push_back("is"); LangName.push_back("Icelandic");
    LangCode.push_back("ig"); LangName.push_back("Igbo");
    LangCode.push_back("id"); LangName.push_back("Indonesian");
    LangCode.push_back("ga"); LangName.push_back("Irish");
    LangCode.push_back("it"); LangName.push_back("Italian");
    LangCode.push_back("ja"); LangName.push_back("Japanese");
    LangCode.push_back("jv"); LangName.push_back("Javanese");
    LangCode.push_back("kn"); LangName.push_back("Kannada");
    LangCode.push_back("kk"); LangName.push_back("Kazakh");
    LangCode.push_back("km"); LangName.push_back("Khmer");
    LangCode.push_back("rw"); LangName.push_back("Kinyarwanda");
    LangCode.push_back("ko"); LangName.push_back("Korean");
    LangCode.push_back("ku"); LangName.push_back("Kurdish");
    LangCode.push_back("ky"); LangName.push_back("Kyrgyz");
    LangCode.push_back("lo"); LangName.push_back("Lao");
    LangCode.push_back("la"); LangName.push_back("Latin");
    LangCode.push_back("lv"); LangName.push_back("Latvian");
    LangCode.push_back("lt"); LangName.push_back("Lithuanian");
    LangCode.push_back("lb"); LangName.push_back("Luxembourgish");
    LangCode.push_back("mk"); LangName.push_back("Macedonian");
    LangCode.push_back("mg"); LangName.push_back("Malagasy");
    LangCode.push_back("ms"); LangName.push_back("Malay");
    LangCode.push_back("ml"); LangName.push_back("Malayalam");
    LangCode.push_back("mt"); LangName.push_back("Maltese");
    LangCode.push_back("mi"); LangName.push_back("Maori");
    LangCode.push_back("mr"); LangName.push_back("Marathi");
    LangCode.push_back("mn"); LangName.push_back("Mongolian");
    LangCode.push_back("my"); LangName.push_back("Myanmar (Burmese)");
    LangCode.push_back("ne"); LangName.push_back("Nepali");
    LangCode.push_back("no"); LangName.push_back("Norwegian");
    LangCode.push_back("ny"); LangName.push_back("Nyanja (Chichewa)");
    LangCode.push_back("or"); LangName.push_back("Odia (Oriya)");
    LangCode.push_back("ps"); LangName.push_back("Pashto");
    LangCode.push_back("fa"); LangName.push_back("Persian");
    LangCode.push_back("pl"); LangName.push_back("Polish");
    LangCode.push_back("pt"); LangName.push_back("Portuguese (Portugal, Brazil)");
    LangCode.push_back("pa"); LangName.push_back("Punjabi");
    LangCode.push_back("ro"); LangName.push_back("Romanian");
    LangCode.push_back("ru"); LangName.push_back("Russian");
    LangCode.push_back("sm"); LangName.push_back("Samoan");
    LangCode.push_back("gd"); LangName.push_back("Scots Gaelic");
    LangCode.push_back("sr"); LangName.push_back("Serbian");
    LangCode.push_back("st"); LangName.push_back("Sesotho");
    LangCode.push_back("sn"); LangName.push_back("Shona");
    LangCode.push_back("sd"); LangName.push_back("Sindhi");
    LangCode.push_back("si"); LangName.push_back("Sinhala (Sinhalese)");
    LangCode.push_back("sk"); LangName.push_back("Slovak");
    LangCode.push_back("sl"); LangName.push_back("Slovenian");
    LangCode.push_back("so"); LangName.push_back("Somali");
    LangCode.push_back("es"); LangName.push_back("Spanish");
    LangCode.push_back("su"); LangName.push_back("Sundanese");
    LangCode.push_back("sw"); LangName.push_back("Swahili");
    LangCode.push_back("sv"); LangName.push_back("Swedish");
    LangCode.push_back("tl"); LangName.push_back("Tagalog (Filipino)");
    LangCode.push_back("tg"); LangName.push_back("Tajik");
    LangCode.push_back("ta"); LangName.push_back("Tamil");
    LangCode.push_back("tt"); LangName.push_back("Tatar");
    LangCode.push_back("te"); LangName.push_back("Telugu");
    LangCode.push_back("th"); LangName.push_back("Thai");
    LangCode.push_back("tr"); LangName.push_back("Turkish");
    LangCode.push_back("tk"); LangName.push_back("Turkmen");
    LangCode.push_back("uk"); LangName.push_back("Ukrainian");
    LangCode.push_back("ur"); LangName.push_back("Urdu");
    LangCode.push_back("ug"); LangName.push_back("Uyghur");
    LangCode.push_back("uz"); LangName.push_back("Uzbek");
    LangCode.push_back("vi"); LangName.push_back("Vietnamese");
    LangCode.push_back("cy"); LangName.push_back("Welsh");
    LangCode.push_back("xh"); LangName.push_back("Xhosa");
    LangCode.push_back("yi"); LangName.push_back("Yiddish");
    LangCode.push_back("yo"); LangName.push_back("Yoruba");
    LangCode.push_back("zu"); LangName.push_back("Zulu");

    ui->setupUi(this);
    srand(time(NULL));


    for (int I = 0; I < LangCode.size(); I++)
    {
        ui->GoogleLangSrcT->addItem(Eden::ToQStr(LangName[I]));
        ui->GoogleLangDstT->addItem(Eden::ToQStr(LangName[I]));
    }
    ui->GoogleLangSrcT->setItemText(0, "(auto detect)");
    ui->GoogleLangDstT->setItemText(0, "(no translation)");

    Settings_ = new Settings();
    if (Settings_->StayOnTopSet)
    {
        Qt::WindowFlags flags = this->windowFlags();
        flags = flags | Qt::WindowStaysOnTopHint;
        setWindowFlags(flags);
    }

    FPS = new QTimer(this);
    QObject::connect(FPS, SIGNAL(timeout()), this, SLOT(FPSDisp()));
    Working = false;
    EventActive = false;

    if (!FPS_)
    {
        FPS->start(1000);
        FPS_ = true;
    }
}

WinSettings::~WinSettings()
{
    if (FPS_)
    {
        FPS->stop();
        ui->MainFPS->setText("FPS");
        FPS_ = false;
    }
    on_MainStop_clicked();
    delete FPS;
    delete ui;
}

void WinSettings::AfterShow()
{
    if (!FPS_)
    {
        FPS->start(1000);
        FPS_ = true;
    }
}

void WinSettings::LoadSettings(bool Window)
{
    EventActive = false;

    ui->ScreenBoundsX1->setValue(Settings_->BoundX1);
    ui->ScreenBoundsY1->setValue(Settings_->BoundX1);
    ui->ScreenBoundsX2->setValue(Settings_->BoundX2);
    ui->ScreenBoundsY2->setValue(Settings_->BoundY2);
    ui->NetAddrT->setText(Eden::ToQStr(Settings_->NetAddr));
    ui->NetPortT->setValue(Settings_->NetPort);
    ui->NetQuality1T->setValue(Settings_->NetQuality1);
    ui->NetQuality2T->setValue(Settings_->NetQuality2);
    ui->NetPicSrcDst->setCurrentIndex(Settings_->PicSrcDst);

    ui->OnTopPictuceC->setChecked(Settings_->StayOnTopPic);
    ui->OnTopSettingsC->setChecked(Settings_->StayOnTopSet);
    ui->OnTopRecorderC->setChecked(Settings_->RecorderWindowOnTop);
    ui->SetCloseApp->setChecked(Settings_->SetCloseApp);
    ui->ViewFullscreenT->setChecked(Settings_->ViewFullscreen);

    ui->PicXT->setValue(Settings_->PicX);
    ui->PicYT->setValue(Settings_->PicY);
    ui->PicWT->setValue(Settings_->PicW);
    ui->PicHT->setValue(Settings_->PicH);
    ui->ViewXT->setValue(Settings_->ViewX);
    ui->ViewYT->setValue(Settings_->ViewY);
    ui->ViewWT->setValue(Settings_->ViewW);
    ui->ViewHT->setValue(Settings_->ViewH);
    ui->PicMouseMarginT->setValue(Settings_->MouseMargin);
    ui->PicGammaT->setValue(Settings_->Gamma);

    ui->ThrottleT->setValue(Settings_->Throttle);
    ui->DelayLineCountT->setValue(Settings_->DelayLineCount);
    ui->DelayLineModeT->setCurrentIndex(Settings_->DelayLineMode);
    ui->DelayLineFileNameT->setText(Eden::ToQStr(Settings_->DelayLineFileName));

    ui->GoogleEnableT->setChecked(Settings_->GoogleCloudEnabled);
    ui->GoogleKeyT->setText(Eden::ToQStr(Settings_->GoogleCloudKey));
    ui->GoogleSlotCountT->setValue(Settings_->GoogleCloudSlotCount);
    ui->GoogleImageQualityT->setValue(Settings_->GoogleCloudImageQuality);
    ui->GoogleMaskOverlayT->setValue(Settings_->GoogleCloudMaskOverlay);
    ui->GoogleDecimateT->setValue(Settings_->GoogleCloudDecimate);
    ui->GoogleLangSrcT->setCurrentIndex(LangIndexGet(Settings_->GoogleCloudLangSrc));
    ui->GoogleLangDstT->setCurrentIndex(LangIndexGet(Settings_->GoogleCloudLangDst));
    ui->GoogleFontNameT->setText(Eden::ToQStr(Settings_->GoogleCloudFontName));
    ui->GoogleFontSizeT->setValue(Settings_->GoogleCloudFontSize);
    ui->GoogleTextRotate->setChecked(Settings_->GoogleCloudTextRotate);
    ui->GoogleFontAutoT->setChecked(Settings_->GoogleCloudFontAutoSize);
    ui->GoogleLinesT->setChecked(Settings_->GoogleCloudTranslateLines);
    ui->GoogleAlignH->setCurrentIndex(Settings_->GoogleCloudTranslateAlignH);
    ui->GoogleAlignV->setCurrentIndex(Settings_->GoogleCloudTranslateAlignV);
    ui->GoogleCaptureTextSizeT->setValue(Settings_->RecorderTextSize);

    if (!Window)
    {
        ui->MarginLeftT->setValue(Settings_->ViewMarginLeft);
        ui->MarginTopT->setValue(Settings_->ViewMarginTop);
        ui->MarginRightT->setValue(Settings_->ViewMarginRight);
        ui->MarginBottomT->setValue(Settings_->ViewMarginBottom);
        ui->OffsetXT->setValue(Settings_->ViewOffsetX);
        ui->OffsetYT->setValue(Settings_->ViewOffsetY);
        ui->ViewStretch->setCurrentIndex(Settings_->ViewStretched);
        ui->PicThreadsT0->setValue(Settings_->PipeCount);
        ui->PicThreadsT->setValue(Settings_->PicThreads);
        ui->PicFollowMouse->setChecked(Settings_->FollowMouse);
        ui->PicMouseTypeT->setCurrentIndex(Settings_->MousePointerType);
        ui->PicMouseSizeT->setValue(Settings_->MouseSize);
        ui->PicMouseSizeTT->setValue(Settings_->MouseThickness);
    }
    EventActive = true;
}

void WinSettings::FPSDisp()
{
    ui->MainFPS->setText("FPS: " + Eden::ToQStr(PicThread_->FPS));
    ui->NetStatus->setText(PicNetwork_->StatsGet());
    PicThread_->FPS = 0;
}

///
/// \brief WinSettings::on_MainStart_clicked - Start picture transform/view
///
void WinSettings::on_MainStart_clicked()
{
    if (!Working)
    {
        /*QThread::IdlePriority	0	scheduled only when no other threads are running.
        QThread::LowestPriority	1	scheduled less often than LowPriority.
        QThread::LowPriority	2	scheduled less often than NormalPriority.
        QThread::NormalPriority	3	the default priority of the operating system.
        QThread::HighPriority	4	scheduled more often than NormalPriority.
        QThread::HighestPriority	5	scheduled more often than HighPriority.
        QThread::TimeCriticalPriority	6	scheduled as often as possible.
        QThread::InheritPriority	7	use the same priority as the creating thread. This is the default.*/

        Working = true;
        PicThread_->start(QThread::TimeCriticalPriority);
    }
}

///
/// \brief WinSettings::on_MainStop_clicked - Stop picture transform/view
///
void WinSettings::on_MainStop_clicked()
{
    if (Working)
    {
        Working = false;
        PicThread_->Stop();
        PicThread_->wait();
    }
}

///
/// \brief WinSettings::on_MainRestart_clicked - Stop and start picture transform/view again
///
void WinSettings::on_MainRestart_clicked()
{
    bool WP = WorkPause();
    WorkResume(WP);
}

void WinSettings::on_ViewXT_valueChanged(int arg1)
{
    Settings_->ViewX = arg1;
    UpdateWindow();
}

void WinSettings::on_ViewYT_valueChanged(int arg1)
{
    Settings_->ViewY = arg1;
    UpdateWindow();
}

void WinSettings::on_ViewWT_valueChanged(int arg1)
{
    Settings_->ViewW = arg1;
    UpdateWindow();
}

void WinSettings::on_ViewHT_valueChanged(int arg1)
{
    Settings_->ViewH = arg1;
    UpdateWindow();
}

void WinSettings::on_MarginLeftT_valueChanged(int arg1)
{
    Settings_->ViewMarginLeft = arg1;
    UpdateWindow();
}

void WinSettings::on_MarginTopT_valueChanged(int arg1)
{
    Settings_->ViewMarginTop = arg1;
    UpdateWindow();
}

void WinSettings::on_MarginRightT_valueChanged(int arg1)
{
    Settings_->ViewMarginRight = arg1;
    UpdateWindow();
}

void WinSettings::on_MarginBottomT_valueChanged(int arg1)
{
    Settings_->ViewMarginBottom = arg1;
    UpdateWindow();
}

void WinSettings::UpdateWindow()
{
    if (EventActive)
    {
        emit SetWindow(Settings_->ViewX, Settings_->ViewY, Settings_->ViewW, Settings_->ViewH, Settings_->ViewFullscreen);
    }
}

void WinSettings::on_PicThreadsT_valueChanged(int arg1)
{
    Settings_->PicThreads = arg1;
}

void WinSettings::on_PicXT_valueChanged(int arg1)
{
    Settings_->PicX = arg1;
}

void WinSettings::on_PicYT_valueChanged(int arg1)
{
    Settings_->PicY = arg1;
}

void WinSettings::on_PicWT_valueChanged(int arg1)
{
    Settings_->PicW = arg1;
    PicThread_->NeedReInit = true;
}

void WinSettings::on_PicHT_valueChanged(int arg1)
{
    Settings_->PicH = arg1;
    PicThread_->NeedReInit = true;
}

void WinSettings::closeEvent(QCloseEvent *event)
{
    if (FPS_)
    {
        FPS->stop();
        ui->MainFPS->setText("FPS");
        FPS_ = false;
    }
    if (!ForceCloseEvent)
    {
        if (Settings_->SetCloseApp)
        {
            emit RunCommand(0);
        }
    }
    ForceCloseEvent = false;
    event->accept();
}

void WinSettings::on_MainClose_clicked()
{
    ForceCloseEvent = true;
    emit RunCommand(0);
    close();
}

void WinSettings::on_MainClose0_clicked()
{
    ForceCloseEvent = true;
    close();
}

void WinSettings::on_ViewStretch_currentIndexChanged(int index)
{
    Settings_->ViewStretched = index;
    UpdateWindow();
}

void WinSettings::on_PicFollowMouse_toggled(bool checked)
{
    Settings_->FollowMouse = checked;
    ui->PicXT->setValue(Settings_->PicX);
    ui->PicYT->setValue(Settings_->PicY);
    UpdateWindow();
}

void WinSettings::on_OffsetXT_valueChanged(int arg1)
{
    Settings_->ViewOffsetX = arg1;
    UpdateWindow();
}

void WinSettings::on_OffsetYT_valueChanged(int arg1)
{
    Settings_->ViewOffsetY = arg1;
    UpdateWindow();
}

void WinSettings::on_PicMouseSizeT_valueChanged(int arg1)
{
    Settings_->MouseSize = arg1;
    UpdateWindow();
}

void WinSettings::on_ViewColor_clicked()
{
    bool WP = WorkPause();
    QColor C;
    C.setRgb(Settings_->BackColorR, Settings_->BackColorG, Settings_->BackColorB);
    C = QColorDialog::getColor(C, this, "", 0);
    Settings_->BackColorR = C.red();
    Settings_->BackColorG = C.green();
    Settings_->BackColorB = C.blue();
    emit RunCommand(2);
    UpdateWindow();
    WorkResume(WP);
}

void WinSettings::WinCommand(int I)
{
    if (I == 0)
    {
        on_MainStart_clicked();
    }
}

bool WinSettings::WorkPause()
{
    if (Working)
    {
        on_MainStop_clicked();
        return true;
    }
    else
    {
        return false;
    }
}

void WinSettings::WorkResume(bool Paused)
{
    if (Paused)
    {
        on_MainStart_clicked();
    }
}

void WinSettings::SaveLastPath(QString X, bool OpenDir)
{
    if (!X.isEmpty())
    {
        if (OpenDir)
        {
            LastPath = QFileInfo(X).filePath();
        }
        else
        {
            LastPath = QFileInfo(X).path();
        }
    }
}

void WinSettings::on_PicThreadsT0_valueChanged(int arg1)
{
    Settings_->PipeCount = arg1;
}

void WinSettings::on_PicMouseTypeT_currentIndexChanged(int index)
{
    Settings_->MousePointerType = index;
}

///
/// \brief WinSettings::TransListRefresh - Update all items on transform list
///
void WinSettings::TransListRefresh()
{
    TransListEvent = false;
    string X = TransformCore_->GetListNames(-1);
    int T = 0;
    string Buf = "";
    for (uint I = 0; I < X.length(); I++)
    {
        if (X[I] != '|')
        {
            Buf = Buf + X[I];
        }
        else
        {
            if (T >= ui->TransList->count())
            {
                ui->TransList->addItem(Eden::ToQStr(Buf));
            }
            else
            {
                ui->TransList->setItemText(T, Eden::ToQStr(Buf));
            }
            T++;
            Buf = "";
        }
    }
    while (T < ui->TransList->count())
    {
        ui->TransList->removeItem(T);
    }
    if (ui->TransList->currentIndex() != TransformCore_->TransformListCurrent)
    {
        ui->TransList->setCurrentIndex(TransformCore_->TransformListCurrent);
    }
    TransListEvent = true;

    X = TransformCore_->GetItemTextList(false);
    T = 0;
    Buf = "";
    for (uint I = 0; I < X.length(); I++)
    {
        if (X[I] != '|')
        {
            Buf = Buf + X[I];
        }
        else
        {
            if (T >= ui->TransListView->count())
            {
                ui->TransListView->addItem(Eden::ToQStr(Buf));
            }
            else
            {
                ui->TransListView->item(T)->setText(Eden::ToQStr(Buf));
            }
            T++;
            Buf = "";
        }
    }
    while (T < ui->TransListView->count())
    {
        ui->TransListView->removeItemWidget(ui->TransListView->takeItem(T));
    }
    TransformGet();
}

///
/// \brief WinSettings::TransListRefreshItem - Update one item on transform list
///
void WinSettings::TransListRefreshItem()
{
    if (TransformCore_->SelectedItem >= 0)
    {
        string X = TransformCore_->GetItemTextList(true);
        ui->TransListView->currentItem()->setText(Eden::ToQStr(X));
    }
}

///
/// \brief WinSettings::on_TransListLoad_clicked - Load transform list from file
///
void WinSettings::on_TransListLoad_clicked()
{
    string ListName = InputBox("Transform list name", "", TransformCore_->GetListNames(TransformCore_->TransformListCurrent));
    TransformCore_->ListAdd(ListName);
    TransListRefresh();

    /*QString FileNameX = QFileDialog::getOpenFileName(this, "Set transform file", LastPath, "Text (*.txt)");
    SaveLastPath(FileNameX, false);
    if (!FileNameX.isEmpty())
    {
        TransformCore_->ListLoad(Eden::ToStr(FileNameX));
    }
    TransListRefresh();*/
}

///
/// \brief WinSettings::on_TransListSave_clicked - Save transform list into file
///
void WinSettings::on_TransListSave_clicked()
{
    TransformCore_->ListRem();
    TransListRefresh();

    /*QString FileNameX = QFileDialog::getSaveFileName(this, "Set transform file", LastPath, "Text (*.txt)");
    SaveLastPath(FileNameX, false);
    if (!FileNameX.isEmpty())
    {
        TransformCore_->ListSave(Eden::ToStr(FileNameX));
    }
    TransListRefresh();*/
}

///
/// \brief WinSettings::on_TransAdd_clicked - Add transform item
///
void WinSettings::on_TransAdd_clicked()
{
    TransformCore_->ItemAdd();
    ui->TransListView->setCurrentRow(TransformCore_->SelectedItem);
    TransListRefresh();
}

///
/// \brief WinSettings::on_TransRemove_clicked - Remove transform item
///
void WinSettings::on_TransRemove_clicked()
{
    TransformCore_->SelectedItem = ui->TransListView->currentRow();
    TransformCore_->ItemRemove();
    ui->TransListView->setCurrentRow(TransformCore_->SelectedItem);
    TransListRefresh();
}

///
/// \brief WinSettings::on_TransMoveUp_clicked - Move transform item up
///
void WinSettings::on_TransMoveUp_clicked()
{
    TransformCore_->SelectedItem = ui->TransListView->currentRow();
    TransformCore_->ItemMoveUp();
    ui->TransListView->setCurrentRow(TransformCore_->SelectedItem);
    TransListRefresh();
}

///
/// \brief WinSettings::on_TransMoveDown_clicked - Move transform item down
///
void WinSettings::on_TransMoveDown_clicked()
{
    TransformCore_->SelectedItem = ui->TransListView->currentRow();
    TransformCore_->ItemMoveDown();
    ui->TransListView->setCurrentRow(TransformCore_->SelectedItem);
    TransListRefresh();
}

///
/// \brief WinSettings::on_TransEnable_clicked - Enable/disable transform item
///
void WinSettings::on_TransEnable_clicked()
{
    TransformCore_->SelectedItem = ui->TransListView->currentRow();
    TransformCore_->ItemEnable();
    TransListRefresh();
}

///
/// \brief WinSettings::TransformSet - Save transform item parameters from form to structure
///
void WinSettings::TransformSet()
{
    if (!TransformSetAllow)
    {
        return;
    }

    if (TransformCore_->SelectedItem >= 0)
    {
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].TransType = ui->ProcessTabs->currentIndex();

        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0Type = 0;
        if (ui->Trans0Op0->isChecked()) { TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0Type = 0; }
        if (ui->Trans0Op1->isChecked()) { TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0Type = 1; }
        if (ui->Trans0Op2->isChecked()) { TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0Type = 2; }
        if (ui->Trans0Op3->isChecked()) { TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0Type = 3; }
        if (ui->Trans0Op4->isChecked()) { TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0Type = 4; }
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0File = Eden::ToStr(ui->Trans0File->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0Gamma = ui->Trans0Gamma->isChecked();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0BriR = ui->Trans0BriR->value();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0BriG = ui->Trans0BriG->value();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0BriB = ui->Trans0BriB->value();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0ConR = ui->Trans0ConR->value();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0ConG = ui->Trans0ConG->value();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0ConB = ui->Trans0ConB->value();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0ConBiasR = ui->Trans0ConBiasR->value();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0ConBiasG = ui->Trans0ConBiasG->value();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0ConBiasB = ui->Trans0ConBiasB->value();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0InvR = ui->Trans0InvR->value();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0InvG = ui->Trans0InvG->value();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0InvB = ui->Trans0InvB->value();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0GammaR = ui->Trans0GammaR->value();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0GammaG = ui->Trans0GammaG->value();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0GammaB = ui->Trans0GammaB->value();

        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1Type = 0;
        if (ui->Trans1Op0->isChecked()) { TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1Type = 0; }
        if (ui->Trans1Op1->isChecked()) { TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1Type = 1; }
        if (ui->Trans1Op2->isChecked()) { TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1Type = 2; }
        if (ui->Trans1Op3->isChecked()) { TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1Type = 3; }
        if (ui->Trans1Op4->isChecked()) { TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1Type = 4; }
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1File = Eden::ToStr(ui->Trans1File->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1Gamma = ui->Trans1Gamma->isChecked();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1Sat = ui->Trans1Sat->value();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1Chan = ui->Trans1Chan->currentIndex();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1YuvType = ui->Trans1YuvType->currentIndex();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1YuvWeightR = Eden::ToInt(ui->Trans1YuvWeightR->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1YuvWeightG = Eden::ToInt(ui->Trans1YuvWeightG->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1YuvWeightB = Eden::ToInt(ui->Trans1YuvWeightB->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1YuvLuma = Eden::ToInt(ui->Trans1YuvLumaT->text());

        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2Offset1R = Eden::ToInt(ui->Trans2Offset1R->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2Offset1G = Eden::ToInt(ui->Trans2Offset1G->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2Offset1B = Eden::ToInt(ui->Trans2Offset1B->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2GainR = Eden::ToInt(ui->Trans2GainR->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2GainG = Eden::ToInt(ui->Trans2GainG->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2GainB = Eden::ToInt(ui->Trans2GainB->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2Offset2R = Eden::ToInt(ui->Trans2Offset2R->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2Offset2G = Eden::ToInt(ui->Trans2Offset2G->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2Offset2B = Eden::ToInt(ui->Trans2Offset2B->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2Gamma = ui->Trans2Gamma->isChecked();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2Common = ui->Trans2CommonT->currentIndex();

        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[0]  = Eden::ToInt(ui->Trans2ChanR00->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[1]  = Eden::ToInt(ui->Trans2ChanR01->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[2]  = Eden::ToInt(ui->Trans2ChanR02->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[3]  = Eden::ToInt(ui->Trans2ChanR03->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[4]  = Eden::ToInt(ui->Trans2ChanR04->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[5]  = Eden::ToInt(ui->Trans2ChanR10->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[6]  = Eden::ToInt(ui->Trans2ChanR11->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[7]  = Eden::ToInt(ui->Trans2ChanR12->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[8]  = Eden::ToInt(ui->Trans2ChanR13->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[9]  = Eden::ToInt(ui->Trans2ChanR14->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[10] = Eden::ToInt(ui->Trans2ChanR20->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[11] = Eden::ToInt(ui->Trans2ChanR21->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[12] = Eden::ToInt(ui->Trans2ChanR22->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[13] = Eden::ToInt(ui->Trans2ChanR23->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[14] = Eden::ToInt(ui->Trans2ChanR24->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[15] = Eden::ToInt(ui->Trans2ChanR30->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[16] = Eden::ToInt(ui->Trans2ChanR31->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[17] = Eden::ToInt(ui->Trans2ChanR32->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[18] = Eden::ToInt(ui->Trans2ChanR33->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[19] = Eden::ToInt(ui->Trans2ChanR34->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[20] = Eden::ToInt(ui->Trans2ChanR40->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[21] = Eden::ToInt(ui->Trans2ChanR41->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[22] = Eden::ToInt(ui->Trans2ChanR42->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[23] = Eden::ToInt(ui->Trans2ChanR43->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[24] = Eden::ToInt(ui->Trans2ChanR44->text());

        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[0]  = Eden::ToInt(ui->Trans2ChanG00->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[1]  = Eden::ToInt(ui->Trans2ChanG01->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[2]  = Eden::ToInt(ui->Trans2ChanG02->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[3]  = Eden::ToInt(ui->Trans2ChanG03->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[4]  = Eden::ToInt(ui->Trans2ChanG04->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[5]  = Eden::ToInt(ui->Trans2ChanG10->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[6]  = Eden::ToInt(ui->Trans2ChanG11->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[7]  = Eden::ToInt(ui->Trans2ChanG12->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[8]  = Eden::ToInt(ui->Trans2ChanG13->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[9]  = Eden::ToInt(ui->Trans2ChanG14->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[10] = Eden::ToInt(ui->Trans2ChanG20->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[11] = Eden::ToInt(ui->Trans2ChanG21->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[12] = Eden::ToInt(ui->Trans2ChanG22->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[13] = Eden::ToInt(ui->Trans2ChanG23->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[14] = Eden::ToInt(ui->Trans2ChanG24->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[15] = Eden::ToInt(ui->Trans2ChanG30->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[16] = Eden::ToInt(ui->Trans2ChanG31->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[17] = Eden::ToInt(ui->Trans2ChanG32->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[18] = Eden::ToInt(ui->Trans2ChanG33->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[19] = Eden::ToInt(ui->Trans2ChanG34->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[20] = Eden::ToInt(ui->Trans2ChanG40->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[21] = Eden::ToInt(ui->Trans2ChanG41->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[22] = Eden::ToInt(ui->Trans2ChanG42->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[23] = Eden::ToInt(ui->Trans2ChanG43->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[24] = Eden::ToInt(ui->Trans2ChanG44->text());

        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[0]  = Eden::ToInt(ui->Trans2ChanB00->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[1]  = Eden::ToInt(ui->Trans2ChanB01->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[2]  = Eden::ToInt(ui->Trans2ChanB02->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[3]  = Eden::ToInt(ui->Trans2ChanB03->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[4]  = Eden::ToInt(ui->Trans2ChanB04->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[5]  = Eden::ToInt(ui->Trans2ChanB10->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[6]  = Eden::ToInt(ui->Trans2ChanB11->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[7]  = Eden::ToInt(ui->Trans2ChanB12->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[8]  = Eden::ToInt(ui->Trans2ChanB13->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[9]  = Eden::ToInt(ui->Trans2ChanB14->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[10] = Eden::ToInt(ui->Trans2ChanB20->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[11] = Eden::ToInt(ui->Trans2ChanB21->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[12] = Eden::ToInt(ui->Trans2ChanB22->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[13] = Eden::ToInt(ui->Trans2ChanB23->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[14] = Eden::ToInt(ui->Trans2ChanB24->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[15] = Eden::ToInt(ui->Trans2ChanB30->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[16] = Eden::ToInt(ui->Trans2ChanB31->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[17] = Eden::ToInt(ui->Trans2ChanB32->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[18] = Eden::ToInt(ui->Trans2ChanB33->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[19] = Eden::ToInt(ui->Trans2ChanB34->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[20] = Eden::ToInt(ui->Trans2ChanB40->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[21] = Eden::ToInt(ui->Trans2ChanB41->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[22] = Eden::ToInt(ui->Trans2ChanB42->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[23] = Eden::ToInt(ui->Trans2ChanB43->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[24] = Eden::ToInt(ui->Trans2ChanB44->text());

        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentProp1 = Eden::ToInt(ui->Trans3Color1->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentProp2 = Eden::ToInt(ui->Trans3Color2->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentProp3 = Eden::ToInt(ui->Trans3Color3->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentProp4 = Eden::ToInt(ui->Trans3Color4->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentRot0 = ui->Trans3Rot0->currentIndex();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentRot1 = ui->Trans3Rot1->currentIndex();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentRot2 = ui->Trans3Rot2->currentIndex();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentRot3 = ui->Trans3Rot3->currentIndex();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[0]  = Eden::ToInt(ui->Trans3Matrix00->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[1]  = Eden::ToInt(ui->Trans3Matrix01->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[2]  = Eden::ToInt(ui->Trans3Matrix02->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[3]  = Eden::ToInt(ui->Trans3Matrix03->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[4]  = Eden::ToInt(ui->Trans3Matrix04->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[5]  = Eden::ToInt(ui->Trans3Matrix10->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[6]  = Eden::ToInt(ui->Trans3Matrix11->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[7]  = Eden::ToInt(ui->Trans3Matrix12->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[8]  = Eden::ToInt(ui->Trans3Matrix13->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[9]  = Eden::ToInt(ui->Trans3Matrix14->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[10] = Eden::ToInt(ui->Trans3Matrix20->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[11] = Eden::ToInt(ui->Trans3Matrix21->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[12] = Eden::ToInt(ui->Trans3Matrix22->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[13] = Eden::ToInt(ui->Trans3Matrix23->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[14] = Eden::ToInt(ui->Trans3Matrix24->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[15] = Eden::ToInt(ui->Trans3Matrix30->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[16] = Eden::ToInt(ui->Trans3Matrix31->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[17] = Eden::ToInt(ui->Trans3Matrix32->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[18] = Eden::ToInt(ui->Trans3Matrix33->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[19] = Eden::ToInt(ui->Trans3Matrix34->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[20] = Eden::ToInt(ui->Trans3Matrix40->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[21] = Eden::ToInt(ui->Trans3Matrix41->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[22] = Eden::ToInt(ui->Trans3Matrix42->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[23] = Eden::ToInt(ui->Trans3Matrix43->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[24] = Eden::ToInt(ui->Trans3Matrix44->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentSet();

        if (ui->Trans4Op0->isChecked()) { TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4Type = 0; }
        if (ui->Trans4Op1->isChecked()) { TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4Type = 1; }
        if (ui->Trans4Op2->isChecked()) { TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4Type = 2; }
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4Size = ui->Trans4Size->currentIndex();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4Size1W = Eden::ToInt(ui->Trans4Size1W->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4Size1H = Eden::ToInt(ui->Trans4Size1H->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4Size2W = Eden::ToInt(ui->Trans4Size2W->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4Size2H = Eden::ToInt(ui->Trans4Size2H->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4Scale = ui->Trans4Scale->currentIndex();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4Channels = ui->Trans4ScaleChannels->isChecked();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4LcdType = ui->Trans4LcdType->currentIndex();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4LcdOp = ui->Trans4LcdOp->currentIndex();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4LcdChromaB = ui->Trans4LcdChromaB->currentIndex();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4LcdChromaV = ui->Trans4LcdChromaV->currentIndex();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4LcdChromaX = ui->Trans4LcdChromaX->currentIndex();
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4LcdWeightR = Eden::ToInt(ui->Trans4LcdWeightR->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4LcdWeightG = Eden::ToInt(ui->Trans4LcdWeightG->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4LcdWeightB = Eden::ToInt(ui->Trans4LcdWeightB->text());
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4LcdInterpolation = ui->Trans4LcdInterpolation->isChecked();

        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans5Rotate = ui->Trans5RotateT->currentIndex();
    }
    TransListRefreshItem();
}

///
/// \brief WinSettings::TransformGet - Load transform item parameters from structure to form
///
void WinSettings::TransformGet()
{
    TransformSetAllow = false;
    if (TransformCore_->SelectedItem >= 0)
    {
        ui->ProcessTabs->setCurrentIndex(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].TransType);

        switch (TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0Type)
        {
            case 0: ui->Trans0Op0->setChecked(true); break;
            case 1: ui->Trans0Op1->setChecked(true); break;
            case 2: ui->Trans0Op2->setChecked(true); break;
            case 3: ui->Trans0Op3->setChecked(true); break;
            case 4: ui->Trans0Op4->setChecked(true); break;
        }
        ui->Trans0File->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0File));
        ui->Trans0Gamma->setChecked(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0Gamma);
        ui->Trans0BriR->setValue(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0BriR);
        ui->Trans0BriG->setValue(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0BriG);
        ui->Trans0BriB->setValue(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0BriB);
        ui->Trans0ConR->setValue(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0ConR);
        ui->Trans0ConG->setValue(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0ConG);
        ui->Trans0ConB->setValue(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0ConB);
        ui->Trans0ConBiasR->setValue(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0ConBiasR);
        ui->Trans0ConBiasG->setValue(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0ConBiasG);
        ui->Trans0ConBiasB->setValue(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0ConBiasB);
        ui->Trans0InvR->setValue(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0InvR);
        ui->Trans0InvG->setValue(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0InvG);
        ui->Trans0InvB->setValue(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0InvB);
        ui->Trans0GammaR->setValue(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0GammaR);
        ui->Trans0GammaG->setValue(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0GammaG);
        ui->Trans0GammaB->setValue(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans0GammaB);

        switch (TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1Type)
        {
            case 0: ui->Trans1Op0->setChecked(true); break;
            case 1: ui->Trans1Op1->setChecked(true); break;
            case 2: ui->Trans1Op2->setChecked(true); break;
            case 3: ui->Trans1Op3->setChecked(true); break;
            case 4: ui->Trans1Op4->setChecked(true); break;
        }
        ui->Trans1File->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1File));
        ui->Trans1Gamma->setChecked(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1Gamma);
        ui->Trans1Sat->setValue(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1Sat);
        ui->Trans1Chan->setCurrentIndex(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1Chan);
        ui->Trans1YuvType->setCurrentIndex(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1YuvType);
        ui->Trans1YuvWeightR->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1YuvWeightR));
        ui->Trans1YuvWeightG->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1YuvWeightG));
        ui->Trans1YuvWeightB->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1YuvWeightB));
        ui->Trans1YuvLumaT->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans1YuvLuma));

        ui->Trans2Offset1R->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2Offset1R));
        ui->Trans2Offset1G->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2Offset1G));
        ui->Trans2Offset1B->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2Offset1B));
        ui->Trans2GainR->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2GainR));
        ui->Trans2GainG->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2GainG));
        ui->Trans2GainB->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2GainB));
        ui->Trans2Offset2R->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2Offset2R));
        ui->Trans2Offset2G->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2Offset2G));
        ui->Trans2Offset2B->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2Offset2B));
        ui->Trans2Gamma->setChecked(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2Gamma);
        ui->Trans2CommonT->setCurrentIndex(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2Common);

        ui->Trans2ChanR00->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[0]));
        ui->Trans2ChanR01->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[1]));
        ui->Trans2ChanR02->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[2]));
        ui->Trans2ChanR03->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[3]));
        ui->Trans2ChanR04->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[4]));
        ui->Trans2ChanR10->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[5]));
        ui->Trans2ChanR11->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[6]));
        ui->Trans2ChanR12->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[7]));
        ui->Trans2ChanR13->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[8]));
        ui->Trans2ChanR14->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[9]));
        ui->Trans2ChanR20->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[10]));
        ui->Trans2ChanR21->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[11]));
        ui->Trans2ChanR22->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[12]));
        ui->Trans2ChanR23->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[13]));
        ui->Trans2ChanR24->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[14]));
        ui->Trans2ChanR30->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[15]));
        ui->Trans2ChanR31->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[16]));
        ui->Trans2ChanR32->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[17]));
        ui->Trans2ChanR33->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[18]));
        ui->Trans2ChanR34->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[19]));
        ui->Trans2ChanR40->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[20]));
        ui->Trans2ChanR41->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[21]));
        ui->Trans2ChanR42->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[22]));
        ui->Trans2ChanR43->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[23]));
        ui->Trans2ChanR44->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixR[24]));

        ui->Trans2ChanG00->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[0]));
        ui->Trans2ChanG01->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[1]));
        ui->Trans2ChanG02->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[2]));
        ui->Trans2ChanG03->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[3]));
        ui->Trans2ChanG04->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[4]));
        ui->Trans2ChanG10->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[5]));
        ui->Trans2ChanG11->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[6]));
        ui->Trans2ChanG12->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[7]));
        ui->Trans2ChanG13->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[8]));
        ui->Trans2ChanG14->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[9]));
        ui->Trans2ChanG20->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[10]));
        ui->Trans2ChanG21->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[11]));
        ui->Trans2ChanG22->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[12]));
        ui->Trans2ChanG23->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[13]));
        ui->Trans2ChanG24->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[14]));
        ui->Trans2ChanG30->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[15]));
        ui->Trans2ChanG31->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[16]));
        ui->Trans2ChanG32->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[17]));
        ui->Trans2ChanG33->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[18]));
        ui->Trans2ChanG34->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[19]));
        ui->Trans2ChanG40->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[20]));
        ui->Trans2ChanG41->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[21]));
        ui->Trans2ChanG42->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[22]));
        ui->Trans2ChanG43->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[23]));
        ui->Trans2ChanG44->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixG[24]));

        ui->Trans2ChanB00->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[0]));
        ui->Trans2ChanB01->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[1]));
        ui->Trans2ChanB02->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[2]));
        ui->Trans2ChanB03->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[3]));
        ui->Trans2ChanB04->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[4]));
        ui->Trans2ChanB10->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[5]));
        ui->Trans2ChanB11->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[6]));
        ui->Trans2ChanB12->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[7]));
        ui->Trans2ChanB13->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[8]));
        ui->Trans2ChanB14->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[9]));
        ui->Trans2ChanB20->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[10]));
        ui->Trans2ChanB21->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[11]));
        ui->Trans2ChanB22->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[12]));
        ui->Trans2ChanB23->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[13]));
        ui->Trans2ChanB24->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[14]));
        ui->Trans2ChanB30->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[15]));
        ui->Trans2ChanB31->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[16]));
        ui->Trans2ChanB32->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[17]));
        ui->Trans2ChanB33->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[18]));
        ui->Trans2ChanB34->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[19]));
        ui->Trans2ChanB40->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[20]));
        ui->Trans2ChanB41->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[21]));
        ui->Trans2ChanB42->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[22]));
        ui->Trans2ChanB43->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[23]));
        ui->Trans2ChanB44->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans2MatrixB[24]));

        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentGet();
        ui->Trans3Info->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentInfo()));
        ui->Trans3Color1->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentProp1));
        ui->Trans3Color2->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentProp2));
        ui->Trans3Color3->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentProp3));
        ui->Trans3Color4->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentProp4));
        ui->Trans3Rot0->setCurrentIndex(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentRot0);
        ui->Trans3Rot1->setCurrentIndex(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentRot1);
        ui->Trans3Rot2->setCurrentIndex(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentRot2);
        ui->Trans3Rot3->setCurrentIndex(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentRot3);
        ui->Trans3Matrix00->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[0]));
        ui->Trans3Matrix01->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[1]));
        ui->Trans3Matrix02->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[2]));
        ui->Trans3Matrix03->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[3]));
        ui->Trans3Matrix04->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[4]));
        ui->Trans3Matrix10->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[5]));
        ui->Trans3Matrix11->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[6]));
        ui->Trans3Matrix12->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[7]));
        ui->Trans3Matrix13->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[8]));
        ui->Trans3Matrix14->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[9]));
        ui->Trans3Matrix20->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[10]));
        ui->Trans3Matrix21->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[11]));
        ui->Trans3Matrix22->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[12]));
        ui->Trans3Matrix23->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[13]));
        ui->Trans3Matrix24->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[14]));
        ui->Trans3Matrix30->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[15]));
        ui->Trans3Matrix31->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[16]));
        ui->Trans3Matrix32->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[17]));
        ui->Trans3Matrix33->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[18]));
        ui->Trans3Matrix34->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[19]));
        ui->Trans3Matrix40->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[20]));
        ui->Trans3Matrix41->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[21]));
        ui->Trans3Matrix42->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[22]));
        ui->Trans3Matrix43->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[23]));
        ui->Trans3Matrix44->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3CurrentMatrix[24]));

        switch (TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4Type)
        {
            case 0: ui->Trans4Op0->setChecked(true); break;
            case 1: ui->Trans4Op1->setChecked(true); break;
            case 2: ui->Trans4Op2->setChecked(true); break;
        }
        ui->Trans4Size->setCurrentIndex(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4Size);
        ui->Trans4Size1W->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4Size1W));
        ui->Trans4Size1H->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4Size1H));
        ui->Trans4Size2W->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4Size2W));
        ui->Trans4Size2H->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4Size2H));
        ui->Trans4Scale->setCurrentIndex(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4Scale);
        ui->Trans4ScaleChannels->setChecked(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4Channels);
        ui->Trans4LcdType->setCurrentIndex(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4LcdType);
        ui->Trans4LcdOp->setCurrentIndex(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4LcdOp);
        ui->Trans4LcdChromaB->setCurrentIndex(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4LcdChromaB);
        ui->Trans4LcdChromaV->setCurrentIndex(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4LcdChromaV);
        ui->Trans4LcdChromaX->setCurrentIndex(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4LcdChromaX);
        ui->Trans4LcdWeightR->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4LcdWeightR));
        ui->Trans4LcdWeightG->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4LcdWeightG));
        ui->Trans4LcdWeightB->setText(Eden::ToQStr(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4LcdWeightB));
        ui->Trans4LcdInterpolation->setChecked(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans4LcdInterpolation);

        ui->Trans5RotateT->setCurrentIndex(TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans5Rotate);
    }
    TransformSetAllow = true;
}

void WinSettings::on_Trans0Op0_toggled(bool checked)
{
    TransformSet();
}

void WinSettings::on_Trans0Op1_toggled(bool checked)
{
    TransformSet();
}

void WinSettings::on_Trans0Op2_toggled(bool checked)
{
    TransformSet();
}

void WinSettings::on_Trans0Op3_toggled(bool checked)
{
    TransformSet();
}

void WinSettings::on_Trans0File_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans0BriR_valueChanged(int value)
{
    TransformSet();
}

void WinSettings::on_Trans0BriG_valueChanged(int value)
{
    TransformSet();
}

void WinSettings::on_Trans0BriB_valueChanged(int value)
{
    TransformSet();
}

void WinSettings::on_Trans0ConR_valueChanged(int value)
{
    TransformSet();
}

void WinSettings::on_Trans0ConG_valueChanged(int value)
{
    TransformSet();
}

void WinSettings::on_Trans0ConB_valueChanged(int value)
{
    TransformSet();
}

void WinSettings::on_Trans1Op0_toggled(bool checked)
{
    TransformSet();
}

void WinSettings::on_Trans1Op1_toggled(bool checked)
{
    TransformSet();
}

void WinSettings::on_Trans1Op2_toggled(bool checked)
{
    TransformSet();
}

void WinSettings::on_Trans1Op3_toggled(bool checked)
{
    TransformSet();
}

void WinSettings::on_Trans1File_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans1Sat_valueChanged(int value)
{
    TransformSet();
}

void WinSettings::on_ProcessTabs_currentChanged(int index)
{
    TransformSet();
}

void WinSettings::on_TransListView_currentRowChanged(int currentRow)
{
    TransformCore_->SelectedItem = ui->TransListView->currentRow();
    TransformGet();
}

void WinSettings::on_Trans1Op4_toggled(bool checked)
{
    TransformSet();
}

void WinSettings::on_Trans1Chan_currentIndexChanged(int index)
{
    TransformSet();
}

void WinSettings::on_Trans2Offset1R_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2Offset1G_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2Offset1B_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2GainR_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2GainG_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2GainB_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2Offset2R_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2Offset2G_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2Offset2B_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2CommonT_currentIndexChanged(int index)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR00_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR01_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR02_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR03_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR04_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR10_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR11_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR12_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR13_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR14_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR20_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR21_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR22_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR23_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR24_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR30_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR31_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR32_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR33_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR34_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR40_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR41_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR42_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR43_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanR44_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG00_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG01_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG02_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG03_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG04_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG10_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG11_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG12_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG13_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG14_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG20_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG21_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG22_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG23_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG24_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG30_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG31_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG32_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG33_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG34_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG40_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG41_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG42_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG43_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanG44_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB00_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB01_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB02_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB03_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB04_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB10_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB11_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB12_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB13_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB14_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB20_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB21_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB22_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB23_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB24_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB30_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB31_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB32_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB33_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB34_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB40_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB41_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB42_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB43_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans2ChanB44_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans4Op0_toggled(bool checked)
{
    TransformSet();
}

void WinSettings::on_Trans4Op1_toggled(bool checked)
{
    TransformSet();
}

void WinSettings::on_Trans4Size_currentIndexChanged(int index)
{
    TransformSet();
}

void WinSettings::on_Trans4Size1W_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans4Size1H_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans4Size2W_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans4Size2H_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans4Scale_currentIndexChanged(int index)
{
    TransformSet();
}

void WinSettings::on_Trans4ScaleChannels_toggled(bool checked)
{
    TransformSet();
}

void WinSettings::on_Trans3Color1_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Color2_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Color3_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Color4_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix00_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix01_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix02_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix03_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix04_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix10_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix11_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix12_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix13_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix14_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix20_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix21_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix22_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix23_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix24_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix30_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix31_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix32_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix33_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix34_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix40_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix41_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix42_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix43_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Matrix44_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans3Add_clicked()
{
    TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3ItemAdd();
    TransformGet();
    TransListRefreshItem();
}

void WinSettings::on_Trans3Rem_clicked()
{
    TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3ItemRem();
    TransformGet();
    TransListRefreshItem();
}

void WinSettings::on_Trans3MovePrev_clicked()
{
    TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3ItemMovePrev();
    TransformGet();
    TransListRefreshItem();
}

void WinSettings::on_Trans3MoveNext_clicked()
{
    TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3ItemMoveNext();
    TransformGet();
    TransListRefreshItem();
}

void WinSettings::on_Trans3DispPrev_clicked()
{
    TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3ItemPrev();
    TransformGet();
    TransListRefreshItem();
}

void WinSettings::on_Trans3DispNext_clicked()
{
    TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].Trans3ItemNext();
    TransformGet();
    TransListRefreshItem();
}

///
/// \brief WinSettings::on_Trans0FileBtn_clicked - Select file to 3x256 LUT transform
///
void WinSettings::on_Trans0FileBtn_clicked()
{
    bool WP = WorkPause();
    QString FileNameX = QFileDialog::getOpenFileName(this, "Set LUT file", LastPath, "Text (*.txt);;Binary (*.bin)");
    SaveLastPath(FileNameX, false);
    if (!FileNameX.isEmpty())
    {
        ui->Trans0File->setText(FileNameX);
    }
    TransformSet();
    WorkResume(WP);
}

///
/// \brief WinSettings::on_Trans1FileBtn_clicked - Select file to 16M LUT transform
///
void WinSettings::on_Trans1FileBtn_clicked()
{
    bool WP = WorkPause();
    QString FileNameX = QFileDialog::getOpenFileName(this, "Set LUT file", LastPath, "Text (*.txt);;Binary (*.bin)");
    SaveLastPath(FileNameX, false);
    if (!FileNameX.isEmpty())
    {
        ui->Trans1File->setText(FileNameX);
    }
    TransformSet();
    WorkResume(WP);
}

///
/// \brief WinSettings::InputBox - Display input box and get string answer.
/// \param Query
/// \param Title
/// \param Default
/// \return
///
string WinSettings::InputBox(string Query, string Title, string Default)
{
    bool OK;
    QString X = QInputDialog::getText(this, Eden::ToQStr(Title), Eden::ToQStr(Query), QLineEdit::Normal, Eden::ToQStr(Default), &OK);
    if (OK)
    {
        InputBoxOK = true;
        return Eden::ToStr(X);
    }
    else
    {
        InputBoxOK = false;
        return "";
    }
}

///
/// \brief WinSettings::on_Trans0FileSave_clicked - Save current 3x256 LUT transform to file
///
void WinSettings::on_Trans0FileSave_clicked()
{
    bool WP = WorkPause();
    int Resolution = 0;
    while ((Resolution < 1) || (Resolution > 8))
    {
        Resolution = Eden::ToInt(InputBox("Resolution (1-8)", "", "8"));
        if (!InputBoxOK)
        {
            WorkResume(WP);
            return;
        }
    }

    QString FileNameX = QFileDialog::getSaveFileName(this, "Set LUT file", LastPath, "Text (*.txt);;Binary (*.bin)");
    SaveLastPath(FileNameX, false);
    if (!FileNameX.isEmpty())
    {
        TransformCore_->TransformListItem[TransformCore_->TransformListCurrent][TransformCore_->SelectedItem].SaveLUT(Eden::ToStr(FileNameX), Resolution);
    }
    WorkResume(WP);
}

///
/// \brief WinSettings::on_Trans1FileSave_clicked - Save current 16M LUT transform to file
///
void WinSettings::on_Trans1FileSave_clicked()
{
    on_Trans0FileSave_clicked();
}

void WinSettings::on_Trans0InvR_valueChanged(int value)
{
    TransformSet();
}

void WinSettings::on_Trans0InvG_valueChanged(int value)
{
    TransformSet();
}

void WinSettings::on_Trans0InvB_valueChanged(int value)
{
    TransformSet();
}

void WinSettings::on_Trans5RotateT_currentIndexChanged(int index)
{
    TransformSet();
}

void WinSettings::on_DelayLineCountT_valueChanged(int arg1)
{
    Settings_->DelayLineCount = arg1;
}

void WinSettings::on_DelayLineFileNameT_textChanged(const QString &arg1)
{
    Settings_->DelayLineFileName = Eden::ToStr(arg1);
}

///
/// \brief WinSettings::on_DelayLineFileNameB_clicked - Select delay line file
///
void WinSettings::on_DelayLineFileNameB_clicked()
{
    bool WP = WorkPause();

    QString FileNameX = QFileDialog::getSaveFileName(this, "Set temporary file", LastPath, "");
    SaveLastPath(FileNameX, false);
    if (!FileNameX.isEmpty())
    {
        ui->DelayLineFileNameT->setText(FileNameX);
        Settings_->DelayLineFileName = Eden::ToStr(FileNameX);
    }
    WorkResume(WP);
}

void WinSettings::on_Trans4LcdOp_currentIndexChanged(int index)
{
    TransformSet();
}

void WinSettings::on_Trans4LcdType_currentIndexChanged(int index)
{
    TransformSet();
}

void WinSettings::on_Trans4Op2_toggled(bool checked)
{
    TransformSet();
}

void WinSettings::on_Trans1YuvType_currentIndexChanged(int index)
{
    TransformSet();
}

void WinSettings::on_Trans1YuvWeightR_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans1YuvWeightG_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans1YuvWeightB_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans4LcdWeightR_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans4LcdWeightG_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans4LcdWeightB_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_Trans1YuvLumaT_textChanged(const QString &arg1)
{
    TransformSet();
}

void WinSettings::on_PicMouseMarginT_valueChanged(int arg1)
{
    Settings_->MouseMargin = arg1;
}

void WinSettings::on_PicGammaT_valueChanged(int arg1)
{
    Settings_->Gamma = arg1;
}

void WinSettings::on_Trans4LcdInterpolation_toggled(bool checked)
{
    TransformSet();
}

void WinSettings::on_PicMouseSizeTT_valueChanged(int arg1)
{
    Settings_->MouseThickness = arg1;
}

void WinSettings::on_Trans2Gamma_toggled(bool checked)
{
    TransformSet();
}

void WinSettings::on_Trans0Op4_toggled(bool checked)
{
    TransformSet();
}

void WinSettings::on_Trans0GammaR_valueChanged(int value)
{
    TransformSet();
}

void WinSettings::on_Trans0GammaG_valueChanged(int value)
{
    TransformSet();
}

void WinSettings::on_Trans0GammaB_valueChanged(int value)
{
    TransformSet();
}

void WinSettings::on_Trans0Gamma_toggled(bool checked)
{
    TransformSet();
}

void WinSettings::on_Trans1Gamma_toggled(bool checked)
{
    TransformSet();
}

void WinSettings::on_Trans3Rot0_currentIndexChanged(int index)
{
    TransformSet();
}

void WinSettings::on_Trans3Rot1_currentIndexChanged(int index)
{
    TransformSet();
}

void WinSettings::on_Trans3Rot2_currentIndexChanged(int index)
{
    TransformSet();
}

void WinSettings::on_Trans3Rot3_currentIndexChanged(int index)
{
    TransformSet();
}

void WinSettings::on_Trans0ConBiasR_valueChanged(int value)
{
    TransformSet();
}

void WinSettings::on_Trans0ConBiasG_valueChanged(int value)
{
    TransformSet();
}

void WinSettings::on_Trans0ConBiasB_valueChanged(int value)
{
    TransformSet();
}

void WinSettings::on_Trans4LcdChromaB_currentIndexChanged(int index)
{
    TransformSet();
}

void WinSettings::on_Trans4LcdChromaV_currentIndexChanged(int index)
{
    TransformSet();
}

void WinSettings::on_Trans4LcdChromaX_currentIndexChanged(int index)
{
    TransformSet();
}

void WinSettings::on_OnTopPictuceC_toggled(bool checked)
{
    Settings_->StayOnTopPic = checked;
}

void WinSettings::on_OnTopSettingsC_toggled(bool checked)
{
    Settings_->StayOnTopSet = checked;
}

void WinSettings::on_SetCloseApp_toggled(bool checked)
{
    Settings_->SetCloseApp = checked;
}

void WinSettings::on_ThrottleT_valueChanged(int arg1)
{
    Settings_->Throttle = arg1;
}

void WinSettings::on_NetAddrT_textChanged(const QString &arg1)
{
    Settings_->NetAddr = Eden::ToStr(arg1);
}

void WinSettings::on_NetPortT_valueChanged(int arg1)
{
    Settings_->NetPort = arg1;
}

void WinSettings::on_NetStartSrv_clicked()
{
    PicNetwork_->StartSrv(ui->NetAddrT->text(), ui->NetPortT->value());
}

void WinSettings::on_NetStartCli_clicked()
{
    PicNetwork_->StartCli(ui->NetAddrT->text(), ui->NetPortT->value());
}

void WinSettings::on_NetStop_clicked()
{
    PicNetwork_->Stop();
}

void WinSettings::on_NetMsgSend_clicked()
{
    PicNetwork_->MsgSend("0" + PicNetwork_->ToQS(rand()));
}

void WinSettings::on_NetMsgClear_clicked()
{
    ui->NetMsgLog->clear();
}

void WinSettings::PicNetLog(QString Msg)
{
    ui->NetMsgLog->appendPlainText(Msg);
}

void WinSettings::on_NetPicSrcDst_currentIndexChanged(int index)
{
    Settings_->PicSrcDst = index;
    Settings_->RefreshWorkingSettings();
    emit ViewRepaint();
}

void WinSettings::on_NetQuality1T_valueChanged(int arg1)
{
    Settings_->NetQuality1 = arg1;
}

void WinSettings::on_NetQuality2T_valueChanged(int arg1)
{
    Settings_->NetQuality2 = arg1;
}

void WinSettings::on_ScreenBoundsX1_valueChanged(int arg1)
{
    Settings_->BoundX1 = arg1;
}

void WinSettings::on_ScreenBoundsY1_valueChanged(int arg1)
{
    Settings_->BoundY1 = arg1;
}

void WinSettings::on_ScreenBoundsX2_valueChanged(int arg1)
{
    Settings_->BoundX2 = arg1;
}

void WinSettings::on_ScreenBoundsY2_valueChanged(int arg1)
{
    Settings_->BoundY2 = arg1;
}

void WinSettings::on_NetStartBind_clicked()
{
    PicNetwork_->StartBind(ui->NetAddrT->text(), ui->NetPortT->value());
}

void WinSettings::on_ViewFullscreenT_toggled(bool checked)
{
    Settings_->ViewFullscreen = checked;
    UpdateWindow();
}

void WinSettings::PicSetRefresh()
{
    ui->PicWT->setValue(Settings_->PicW);
    ui->PicHT->setValue(Settings_->PicH);
}

void WinSettings::on_ScreenBoundsAuto_clicked()
{
    uint Idx = Settings_->_BoundX1.size();
    for (uint I = 0; I < Settings_->_BoundX1.size(); I++)
    {
        if ((ui->ScreenBoundsX1->value() == Settings_->_BoundX1[I]) && (ui->ScreenBoundsY1->value() == Settings_->_BoundY1[I]))
        {
            if ((ui->ScreenBoundsX2->value() == Settings_->_BoundX2[I]) && (ui->ScreenBoundsY2->value() == Settings_->_BoundY2[I]))
            {
                Idx = I;
            }
        }
    }
    if (Idx == Settings_->_BoundX1.size())
    {
        Idx = 0;
    }
    else
    {
        Idx++;
    }
    if (Idx == Settings_->_BoundX1.size())
    {
        Idx = 0;
    }
    ui->ScreenBoundsX1->setValue(Settings_->_BoundX1[Idx]);
    ui->ScreenBoundsY1->setValue(Settings_->_BoundY1[Idx]);
    ui->ScreenBoundsX2->setValue(Settings_->_BoundX2[Idx]);
    ui->ScreenBoundsY2->setValue(Settings_->_BoundY2[Idx]);
}

void WinSettings::on_NetPicSrcDstRefresh_clicked()
{
    if (Settings_->_PicDstNet)
    {
        PicNetwork_->ForceNewPic(true);
    }
    if (Settings_->_PicSrcNet)
    {
        PicNetwork_->MsgSend("3X");
    }
}

void WinSettings::on_NetMsgTest_clicked()
{
    PicNetwork_->MsgSend("4" + PicNetwork_->ToQS(rand()));
}


void WinSettings::on_TransList_currentIndexChanged(int index)
{
    if (TransListEvent)
    {
        TransformCore_->TransformListCurrent = index;
        TransListRefresh();
    }
}

void WinSettings::on_DelayLineModeT_currentIndexChanged(int index)
{
    Settings_->DelayLineMode = index;
}

void WinSettings::on_GoogleEnableT_toggled(bool checked)
{
    Settings_->GoogleCloudEnabled = checked;
}

void WinSettings::on_GoogleKeyT_textChanged(const QString &arg1)
{
    Settings_->GoogleCloudKey = Eden::ToStr(arg1);
}

void WinSettings::on_GoogleMaskOverlayT_valueChanged(int arg1)
{
    Settings_->GoogleCloudMaskOverlay = arg1;
}

void WinSettings::on_GoogleDecimateT_valueChanged(int arg1)
{
    Settings_->GoogleCloudDecimate = arg1;
}

void WinSettings::on_GoogleLangSrcT_currentIndexChanged(int index)
{
    if (EventActive)
    {
        Settings_->GoogleCloudLangSrc = LangIndexSet(index);
    }
}

void WinSettings::on_GoogleLangDstT_currentIndexChanged(int index)
{
    if (EventActive)
    {
        Settings_->GoogleCloudLangDst = LangIndexSet(index);
    }
}

void WinSettings::on_GoogleFontNameT_textChanged(const QString &arg1)
{
    Settings_->GoogleCloudFontName = Eden::ToStr(arg1);
}

void WinSettings::on_GoogleFontSizeT_valueChanged(int arg1)
{
    Settings_->GoogleCloudFontSize = arg1;
}

void WinSettings::on_GoogleFontAutoT_toggled(bool checked)
{
    Settings_->GoogleCloudFontAutoSize = checked;
}

void WinSettings::on_GoogleLinesT_toggled(bool checked)
{
    Settings_->GoogleCloudTranslateLines = checked;
}

string WinSettings::LangIndexSet(int Idx)
{
    return LangCode[Idx];
}

int WinSettings::LangIndexGet(string Code)
{
    for (int I = 0; I < LangCode.size(); I++)
    {
        if (LangCode[I] == Code)
        {
            return I;
        }
    }
    return 0;
}

void WinSettings::on_GoogleAlignH_currentIndexChanged(int index)
{
    Settings_->GoogleCloudTranslateAlignH = index;
}

void WinSettings::on_GoogleAlignV_currentIndexChanged(int index)
{
    Settings_->GoogleCloudTranslateAlignV = index;
}

void WinSettings::on_MainRecorder_clicked()
{
    emit ShowRecorder();
}

void WinSettings::on_OnTopRecorderC_toggled(bool checked)
{
    Settings_->RecorderWindowOnTop = checked;
}

void WinSettings::on_GoogleTextRotate_toggled(bool checked)
{
    Settings_->GoogleCloudTextRotate = checked;
}

void WinSettings::on_GoogleImageQualityT_valueChanged(int arg1)
{
    Settings_->GoogleCloudImageQuality = arg1;
}

void WinSettings::on_GoogleCaptureTextSizeT_valueChanged(int arg1)
{
    Settings_->RecorderTextSize = arg1;
}

void WinSettings::on_GoogleSlotCountT_valueChanged(int arg1)
{
    Settings_->GoogleCloudSlotCount = arg1;
}
