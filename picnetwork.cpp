#include "picnetwork.h"

PicNetwork::PicNetwork()
{
    TcpServer_ = NULL;
    TcpSocket_ = NULL;
    UdpSocket_ = NULL;
    PicBuf = new uchar[1];
}

PicNetwork::~PicNetwork()
{
    if (TcpSocket_ != NULL)
    {
        delete TcpSocket_;
        TcpSocket_ = NULL;
    }
    if (TcpServer_ != NULL)
    {
        delete TcpServer_;
        TcpServer_ = NULL;
    }
    if (UdpSocket_ != NULL)
    {
        delete UdpSocket_;
        UdpSocket_ = NULL;
    }
    delete[] PicBuf;
}

void PicNetwork::StartBind(QString Addr, int Port)
{
    if (WorkMode != 0)
    {
        return;
    }

    RecvBuf_.clear();
    WorkMode = 3;
    SetAddr = Addr;
    SetPort = Port;

    PicBufW = 0;
    PicBufH = 0;
    UdpSocket_ = new QUdpSocket(this);
    if (UdpSocket_->bind(QHostAddress(Addr), Port))
    {
        connect(UdpSocket_, SIGNAL(readyRead()), this, SLOT(UdpMsgRecvEvent()));
        connect(UdpSocket_, SIGNAL(disconnected()), this, SLOT(DisconnectUdpEvent()));
        emit NetLog("UDP bound with " + AddrPort(Addr, Port));
    }
    else
    {
        emit NetLog("UDP binding with " + AddrPort(Addr, Port) + " error: " + UdpSocket_->errorString());
        WorkMode = 0;
    }
}

void PicNetwork::StartSrv(QString Addr, int Port)
{
    if (WorkMode != 0)
    {
        return;
    }

    RecvBuf_.clear();
    WorkMode = 11;
    SetAddr = Addr;
    SetPort = Port;

    TcpServer_ = new QTcpServer(this);
    connect(TcpServer_, SIGNAL(newConnection()), this, SLOT(SrvConn()));
    TcpServer_->listen(QHostAddress(Addr), Port);
    emit NetLog("TCP server started on " + AddrPort(Addr, Port));
}

void PicNetwork::StartCli(QString Addr, int Port)
{
    if (WorkMode != 0)
    {
        return;
    }

    RecvBuf_.clear();
    WorkMode = 2;
    SetAddr = Addr;
    SetPort = Port;

    PicBufW = 0;
    PicBufH = 0;
    TcpSocket_ = new QTcpSocket(this);
    TcpSocket_->connectToHost(QHostAddress(Addr), Port);
    if (TcpSocket_->waitForConnected(5000))
    {
        connect(TcpSocket_, SIGNAL(readyRead()), this, SLOT(TcpMsgRecvEvent()));
        connect(TcpSocket_, SIGNAL(disconnected()), this, SLOT(DisconnectCliEvent()));
        emit NetLog("TCP connected to server " + AddrPort(Addr, Port));
    }
    else
    {
        emit NetLog("TCP connecting to " + AddrPort(Addr, Port) + " error: " + TcpSocket_->errorString());
        WorkMode = 0;
    }
}

void PicNetwork::Stop()
{
    if ((WorkMode == 11) || (WorkMode == 1))
    {
        if (TcpSocket_ != NULL)
        {
            TcpSocket_->close();
            delete TcpSocket_;
            TcpSocket_ = NULL;
        }

        if (TcpServer_ != NULL)
        {
            TcpServer_->close();
            disconnect(TcpServer_, SIGNAL(newConnection()), this, SLOT(SrvConn()));
            delete TcpServer_;
            TcpServer_ = NULL;
        }

        emit NetLog("TCP connection closed");
        WorkMode = 0;
        PicBufW = 0;
        PicBufH = 0;
        return;
    }

    if (WorkMode == 2)
    {
        if (TcpSocket_ != NULL)
        {
            TcpSocket_->disconnectFromHost();
            delete TcpSocket_;
            TcpSocket_ = NULL;
        }

        emit NetLog("TCP connection closed");
        WorkMode = 0;
        PicBufW = 0;
        PicBufH = 0;
        return;
    }

    if (WorkMode == 3)
    {
        if (UdpSocket_ != NULL)
        {
            UdpSocket_->disconnect();
            UdpSocket_->close();
            delete UdpSocket_;

            emit NetLog("UDP address unbound");
            WorkMode = 0;
            PicBufW = 0;
            PicBufH = 0;
            return;
        }
    }
}


void PicNetwork::SrvConn()
{
    while (TcpServer_->hasPendingConnections())
    {
        PicBufW = 0;
        PicBufH = 0;
        TcpSocket_ = TcpServer_->nextPendingConnection();
        TcpServer_->close();
        WorkMode = 1;
        connect(TcpSocket_, SIGNAL(readyRead()), this, SLOT(TcpMsgRecvEvent()));
        connect(TcpSocket_, SIGNAL(disconnected()), this, SLOT(DisconnectSrvEvent()));
        emit NetLog("TCP client " + AddrPort(TcpSocket_->peerAddress(), TcpSocket_->peerPort()) + " connected");
    }
}

void PicNetwork::MsgSend(QString Msg)
{
    QByteArray buffer = Msg.toUtf8();
    buffer.insert(0, "    ");
    SizeWrite(buffer.length(), buffer);
    QString MsgAddr = "?.?.?.?:?";
    if ((WorkMode == 1) || (WorkMode == 2))
    {
        MsgAddr = AddrPort(TcpSocket_->peerAddress(), TcpSocket_->peerPort());
    }
    if (WorkMode == 3)
    {
        MsgAddr = AddrPort(Settings_->NetAddr, Settings_->NetPort);
    }
    if (NetSend(buffer))
    {
        if (buffer[4] == '0')
        {
            emit NetLog(MsgAddr + " - message " + Msg.mid(1) + " sent");
            return;
        }
        if (buffer[4] == '4')
        {
            emit NetLog(MsgAddr + " - request " + Msg.mid(1) + " sent");
            return;
        }
        if (buffer[4] == '5')
        {
            emit NetLog(MsgAddr + " - response " + Msg.mid(1) + " sent");
            return;
        }
    }
    else
    {
        if (buffer[4] == '0')
        {
            emit NetLog(MsgAddr + " - message " + Msg.mid(1) + " sending error: " + ErrorMsg);
            return;
        }
        if (buffer[4] == '4')
        {
            emit NetLog(MsgAddr + " - request " + Msg.mid(1) + " sending error: " + ErrorMsg);
            return;
        }
        if (buffer[4] == '5')
        {
            emit NetLog(MsgAddr + " - response " + Msg.mid(1) + " sending error: " + ErrorMsg);
        }
    }
}

void PicNetwork::PicSend(QImage *Msg)
{
    if (Msg == NULL)
    {
        return;
    }

    if (WorkMode == 0)
    {
        return;
    }

    NetMTX.lock();
    bool DiffPic = (Settings_->PicSrcDst == 2);
    if ((Msg->width() != PicBufW) || (Msg->height() != PicBufH))
    {
        DiffPic = false;
        PicBufW = Msg->width();
        PicBufH = Msg->height();
        PicBufS = PicBufW * PicBufH * 4;
        delete[] PicBuf;
        PicBuf = new uchar[PicBufS > 0 ? PicBufS : 1];
        for (int I = 0; I < PicBufS; I += 4)
        {
            PicBuf[I + 0] = 128;
            PicBuf[I + 1] = 128;
            PicBuf[I + 2] = 128;
            PicBuf[I + 3] = 255;
        }
    }

    QByteArray BufBase;
    QBuffer BufBase_(&BufBase);
    BufBase_.open(QIODevice::WriteOnly);
    if (Settings_->NetQuality1 < 0)
    {
        Msg->save(&BufBase_, "PNG", 100);
    }
    else
    {
        Msg->save(&BufBase_, "JPEG", Settings_->NetQuality1);
    }
    uint LengthBase = BufBase.length();
    ulong StatsSize_;

    uchar * RawData;
    if (DiffPic)
    {
        RawData = Msg->bits();
        QImage DiffImgTemp(PicBufW, PicBufH, QImage::Format_ARGB32);
        uchar * RawData_ = DiffImgTemp.bits();
        int ValR;
        int ValG;
        int ValB;
        for (int I = 0; I < PicBufS; I += 4)
        {
            ValB = (((int)RawData[I + 0]) - ((int)PicBuf[I + 0])) + 128;
            ValG = (((int)RawData[I + 1]) - ((int)PicBuf[I + 1])) + 128;
            ValR = (((int)RawData[I + 2]) - ((int)PicBuf[I + 2])) + 128;
            if (ValB < 0) { ValB = 0; }
            if (ValG < 0) { ValG = 0; }
            if (ValR < 0) { ValR = 0; }
            if (ValB > 255) { ValB = 255; }
            if (ValG > 255) { ValG = 255; }
            if (ValR > 255) { ValR = 255; }
            RawData_[I + 0] = ValB;
            RawData_[I + 1] = ValG;
            RawData_[I + 2] = ValR;
            RawData_[I + 3] = 255;
        }

        QByteArray BufDiff;
        QBuffer BufDiff_(&BufDiff);
        BufDiff_.open(QIODevice::WriteOnly);
        if (Settings_->NetQuality2 < 0)
        {
            DiffImgTemp.save(&BufDiff_, "PNG", 100);
        }
        else
        {
            DiffImgTemp.save(&BufDiff_, "JPEG", Settings_->NetQuality2);
        }
        uint LengthDiff = BufDiff.length();

        if (LengthDiff < LengthBase)
        {
            QImage ImgTempDiff = QImage::fromData(BufDiff, nullptr);
            uchar * RawDataDiff = ImgTempDiff.bits();
            for (int I = 0; I < PicBufS; I += 4)
            {
                int ValB = ((int)PicBuf[I + 0]) + (((int)RawDataDiff[I + 0]) - 128);
                int ValG = ((int)PicBuf[I + 1]) + (((int)RawDataDiff[I + 1]) - 128);
                int ValR = ((int)PicBuf[I + 2]) + (((int)RawDataDiff[I + 2]) - 128);
                if (ValB < 0) { ValB = 0; }
                if (ValG < 0) { ValG = 0; }
                if (ValR < 0) { ValR = 0; }
                if (ValB > 255) { ValB = 255; }
                if (ValG > 255) { ValG = 255; }
                if (ValR > 255) { ValR = 255; }
                PicBuf[I + 0] = ValB;
                PicBuf[I + 1] = ValG;
                PicBuf[I + 2] = ValR;
            }

            StatsSize_ = BufDiff.length();
            StatsSize += StatsSize_;
            if (StatsMin > StatsSize_)
            {
                StatsMin = StatsSize_;
            }
            if (StatsMax < StatsSize_)
            {
                StatsMax = StatsSize_;
            }
            StatsCount++;
            BufDiff.insert(0, "    2");
            SizeWrite(BufDiff.length(), BufDiff);
            NetSend(BufDiff);
            NetMTX.unlock();
            return;
        }
    }


    QImage ImgTemp = QImage::fromData(BufBase, nullptr);
    RawData = ImgTemp.bits();
    for (int I = 0; I < PicBufS; I += 4)
    {
        PicBuf[I + 0] = RawData[I + 0];
        PicBuf[I + 1] = RawData[I + 1];
        PicBuf[I + 2] = RawData[I + 2];
    }

    StatsSize_ = BufBase.length();
    StatsSize += StatsSize_;
    if (StatsMin > StatsSize_)
    {
        StatsMin = StatsSize_;
    }
    if (StatsMax < StatsSize_)
    {
        StatsMax = StatsSize_;
    }
    StatsCount++;
    BufBase.insert(0, "    1");
    SizeWrite(BufBase.length(), BufBase);
    NetSend(BufBase);
    DiffPic = true;
    NetMTX.unlock();
}

bool PicNetwork::NetSend(QByteArray &Buf)
{
    if (TcpSocket_ != NULL)
    {
        if (TcpSocket_->write(Buf) >= 0)
        {
            return true;
        }
        else
        {
            ErrorMsg = TcpSocket_->errorString();
            return false;
        }
    }

    if (UdpSocket_ != NULL)
    {
        if (UdpSocket_->writeDatagram(Buf, QHostAddress(QString(Settings_->NetAddr.c_str())), Settings_->NetPort) > 0)
        {
            return true;
        }
        else
        {
            ErrorMsg = UdpSocket_->errorString();
            return false;
        }
    }

    ErrorMsg = "Connection not established";
    return false;
}

void PicNetwork::DisconnectSrvEvent()
{
    disconnect(TcpSocket_, SIGNAL(disconnected()), this, SLOT(DisconnectSrvEvent()));
    disconnect(TcpSocket_, SIGNAL(readyRead()), this, SLOT(TcpMsgRecvEvent()));
    emit NetLog("TCP client disconnected");
    TcpServer_->listen(QHostAddress(SetAddr), SetPort);
    WorkMode = 11;
}

void PicNetwork::DisconnectCliEvent()
{
    disconnect(TcpSocket_, SIGNAL(disconnected()), this, SLOT(DisconnectCliEvent()));
    disconnect(TcpSocket_, SIGNAL(readyRead()), this, SLOT(TcpMsgRecvEvent()));
    emit NetLog("TCP server disconnected");
    WorkMode = 0;
}

void PicNetwork::DisconnectUdpEvent()
{
    disconnect(TcpSocket_, SIGNAL(disconnected()), this, SLOT(DisconnectUdpEvent()));
    disconnect(TcpSocket_, SIGNAL(readyRead()), this, SLOT(UdpMsgRecvEvent()));
    emit NetLog("UDP address unbound");
    WorkMode = 0;
}

QString PicNetwork::ToQS(int N)
{
    return QString(to_string(N).c_str());
}

QString PicNetwork::AddrPort(QHostAddress Addr, int Port)
{
    return QString(Addr.toString()) + ":" + ToQS(Port);
}

QString PicNetwork::AddrPort(QString Addr, int Port)
{
    return Addr + ":" + ToQS(Port);
}

QString PicNetwork::AddrPort(string Addr, int Port)
{
    return QString(Addr.c_str()) + ":" + ToQS(Port);
}

QString PicNetwork::DataSize(ulong S)
{
    if (S > 1048576 * 10)
    {
        return ToQS(S / 1048576) + "MB";
    }
    if (S > 1024 * 10)
    {
        return ToQS(S / 1024) + "kB";
    }
    return ToQS(S) + "B";
}

void PicNetwork::TcpMsgRecvEvent()
{
    QByteArray buffer = TcpSocket_->readAll();
    MsgRecvEvent(buffer, TcpSocket_->peerAddress(), TcpSocket_->peerPort());
}

void PicNetwork::UdpMsgRecvEvent()
{
    while (UdpSocket_->hasPendingDatagrams())
    {
        QByteArray buffer;
        buffer.resize(UdpSocket_->pendingDatagramSize());
        QHostAddress MsgAddr;
        quint16 MsgPort;
        UdpSocket_->readDatagram(buffer.data(), buffer.size(), &MsgAddr, &MsgPort);
        MsgRecvEvent(buffer, MsgAddr, MsgPort);
    }
}

void PicNetwork::ForceNewPic(bool NetMtxLock)
{
    if (NetMtxLock)
    {
        NetMTX.lock();
        PicBufW = 0;
        PicBufH = 0;
        NetMTX.unlock();
    }
    else
    {
        PicBufW = 0;
        PicBufH = 0;
    }
}

void PicNetwork::MsgRecvEvent(QByteArray &Msg, QHostAddress MsgAddr, quint16 MsgPort)
{
    NetMTX.lock();
    RecvBuf_.append(Msg);

    uint BufSize_ = RecvBuf_.length();
    uint BufSize = SizeRead(RecvBuf_);
    while (BufSize_ >= BufSize)
    {
        uchar MsgType = RecvBuf_[4];
        RecvBuf_.remove(0, 5);
        BufSize_ -= 5;
        BufSize -= 5;
        switch (MsgType)
        {
            case '0':
                emit NetLog(AddrPort(MsgAddr, MsgPort) + " - message " + QString(RecvBuf_.toStdString().c_str()) + " received");
                break;
            case '1':
            case '2':
                {
                    ulong StatsSize_ = RecvBuf_.length();
                    StatsSize += StatsSize_;
                    if (StatsMin > StatsSize_)
                    {
                        StatsMin = StatsSize_;
                    }
                    if (StatsMax < StatsSize_)
                    {
                        StatsMax = StatsSize_;
                    }
                    StatsCount++;
                    QImage ImgX2 = QImage::fromData(RecvBuf_, nullptr);
                    if ((ImgX2.width() != PicBufW) || (ImgX2.height() != PicBufH))
                    {
                        PicBufW = ImgX2.width();
                        PicBufH = ImgX2.height();
                        PicBufS = PicBufW * PicBufH * 4;
                        delete[] PicBuf;
                        PicBuf = new uchar[PicBufS > 0 ? PicBufS : 1];
                        for (int I = 0; I < PicBufS; I += 4)
                        {
                            PicBuf[I + 0] = 128;
                            PicBuf[I + 1] = 128;
                            PicBuf[I + 2] = 128;
                            PicBuf[I + 3] = 255;
                        }
                    }
                    uchar * ImgX_ = ImgX2.bits();
                    if (MsgType == '1')
                    {
                        for (int I = 0; I < PicBufS; I += 4)
                        {
                            PicBuf[I + 0] = ImgX_[I + 0];
                            PicBuf[I + 1] = ImgX_[I + 1];
                            PicBuf[I + 2] = ImgX_[I + 2];
                        }
                    }
                    else
                    {
                        int ValR;
                        int ValG;
                        int ValB;
                        for (int I = 0; I < PicBufS; I += 4)
                        {
                            ValB = ((int)PicBuf[I + 0]) + (((int)ImgX_[I + 0]) - 128);
                            ValG = ((int)PicBuf[I + 1]) + (((int)ImgX_[I + 1]) - 128);
                            ValR = ((int)PicBuf[I + 2]) + (((int)ImgX_[I + 2]) - 128);
                            if (ValB < 0) { ValB = 0; }
                            if (ValG < 0) { ValG = 0; }
                            if (ValR < 0) { ValR = 0; }
                            if (ValB > 255) { ValB = 255; }
                            if (ValG > 255) { ValG = 255; }
                            if (ValR > 255) { ValR = 255; }
                            PicBuf[I + 0] = ValB;
                            PicBuf[I + 1] = ValG;
                            PicBuf[I + 2] = ValR;
                        }
                    }
                }
                break;
            case '3':
                ForceNewPic(false);
                break;
            case '4':
                {
                    QString QS = QString(RecvBuf_);
                    emit NetLog(AddrPort(MsgAddr, MsgPort) + " - request " + QS + " received");
                    MsgSend("5" + QS);
                }
                break;
            case '5':
                {
                    QString QS = QString(RecvBuf_);
                    emit NetLog(AddrPort(MsgAddr, MsgPort) + " - response " + QS + " received");
                }
                break;
        }

        BufSize_ -= BufSize;
        if (BufSize_ == 0)
        {
            RecvBuf_.clear();
            BufSize = UINT32_MAX;
        }
        else
        {
            RecvBuf_.remove(0, BufSize);
            BufSize = SizeRead(RecvBuf_);
        }
    }
    NetMTX.unlock();
}

QImage PicNetwork::PicRecv(int W, int H)
{
    QImage Img(W, H, QImage::Format_ARGB32);
    uchar * ImgRaw = Img.bits();
    int RawSize = W * H * 4;
    NetMTX.lock();
    if ((WorkMode != 0) && (((PicBufW == W) && (PicBufH == H))))
    {
        for (int I = 0; I < RawSize; I += 4)
        {
            ImgRaw[I + 0] = PicBuf[I + 0]; // blue
            ImgRaw[I + 1] = PicBuf[I + 1]; // green
            ImgRaw[I + 2] = PicBuf[I + 2]; // red
            ImgRaw[I + 3] = 255;
        }
        RealPicDiff = false;
    }
    else
    {
        uchar Val;
        for (int I = 0; I < RawSize; I += 4)
        {
            Val = rand();
            ImgRaw[I + 0] = Val; // blue
            ImgRaw[I + 1] = Val; // green
            ImgRaw[I + 2] = Val; // red
            ImgRaw[I + 3] = 255;
        }
        if ((PicBufW > 0) && (PicBufH > 0))
        {
            RealPicW = PicBufW;
            RealPicH = PicBufH;
            RealPicDiff = true;
        }
        else
        {
            RealPicDiff = false;
        }
    }
    NetMTX.unlock();

    return Img;
}

QString PicNetwork::StatsGet()
{
    QString Msg = "";
    switch (WorkMode)
    {
        case 0:
            Msg = "Status: Disconnected";
            break;
        case 11:
            Msg = "Status: TCP server on " + AddrPort(SetAddr, SetPort);
            break;
        case 1:
            Msg = "Status: TCP server on " + AddrPort(SetAddr, SetPort) + " connected with " + AddrPort(TcpSocket_->peerAddress(), TcpSocket_->peerPort());
            break;
        case 2:
            Msg = "Status: TCP client connected with " + AddrPort(TcpSocket_->peerAddress(), TcpSocket_->peerPort());
            break;
        case 3:
            Msg = "Status: UDP bound with " + AddrPort(SetAddr, SetPort);
            break;
    }

    int Val = 0;
    int ValMin = 0;
    int ValMax = 0;
    ulong StatsSize_ = 0;
    if (StatsCount > 0)
    {
        Val = (StatsSize / StatsCount);
        ValMin = StatsMin;
        ValMax = StatsMax;
        StatsSize_ = StatsSize;
        StatsSize = 0;
        StatsMin = ULONG_MAX;
        StatsMax = 0;
        StatsCount = 0;
    }
    Msg = Msg + "\nSize: Min:" + DataSize(ValMin) + " Avg:" + DataSize(Val) + " Max:" + DataSize(ValMax) + "\nTransfer: " + DataSize(StatsSize_) + "/s";
    return Msg;
}

void PicNetwork::SizeWrite(uint S, QByteArray &Buf)
{
    Buf[0] = S >> 24;
    S = S & 16777215;
    Buf[1] = S >> 16;
    S = S & 65535;
    Buf[2] = S >> 8;
    S = S & 255;
    Buf[3] = S;
}

uint PicNetwork::SizeRead(QByteArray &Buf)
{
    uint S = 0;
    S = S + (uint)(((uchar)Buf[0]) << 24);
    S = S + (uint)(((uchar)Buf[1]) << 16);
    S = S + (uint)(((uchar)Buf[2]) << 8);
    S = S + (uint)(((uchar)Buf[3]));
    return S;
}
