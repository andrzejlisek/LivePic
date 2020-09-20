#ifndef PICNETWORK_H
#define PICNETWORK_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QString>
#include <QThread>
#include <iostream>
#include <QPixmap>
#include <queue>
#include <mutex>
#include <QBuffer>
#include "settings.h"

using namespace std;

class PicNetwork : public QThread
{
    /* Protocol
     * 0 - Text message
     * 1 - Picture - normal
     * 2 - Picture - differential
     * 3 - Demand picture refresh
     * 4 - Communication test - ask
     * 5 - Communication test - answer
     */

    Q_OBJECT
public:
    PicNetwork();
    ~PicNetwork();
    void StartBind(QString Addr, int Port);
    void StartSrv(QString Addr, int Port);
    void StartCli(QString Addr, int Port);
    void Stop();
    int WorkMode = 0;
    void MsgSend(QString Msg);
    void PicSend(QImage *Msg);
    QImage PicRecv(int W, int H);
    QString StatsGet();
    QString ToQS(int N);
    Settings * Settings_;
    QString AddrPort(QHostAddress Addr, int Port);
    QString AddrPort(QString Addr, int Port);
    QString AddrPort(string Addr, int Port);
    QString ErrorMsg = "";
    QString DataSize(ulong S);
    bool RealPicDiff = false;
    int RealPicW = 0;
    int RealPicH = 0;
    void ForceNewPic(bool NetMtxLock);
private:
    ulong StatsSize = 0;
    ulong StatsMin = ULONG_MAX;
    ulong StatsMax = 0;
    ulong StatsCount = 0;
    QTcpServer * TcpServer_;
    QTcpSocket * TcpSocket_;
    QUdpSocket * UdpSocket_;
    QString SetAddr;
    int SetPort;
    void SizeWrite(uint S, QByteArray &Buf);
    uint SizeRead(QByteArray &Buf);
    bool NetSend(QByteArray &Buf);
    queue<QByteArray> RecvBuf;
    QByteArray RecvBuf_;
    mutex NetMTX;
    int PicBufS = 0;
    int PicBufW = 0;
    int PicBufH = 0;
    uchar * PicBuf;
    void MsgRecvEvent(QByteArray &Msg, QHostAddress MsgAddr, quint16 MsgPort);
signals:
    void NetLog(QString Msg);
private slots:
    void SrvConn();
    void TcpMsgRecvEvent();
    void UdpMsgRecvEvent();
    void DisconnectSrvEvent();
    void DisconnectCliEvent();
    void DisconnectUdpEvent();
};

#endif // PICNETWORK_H
