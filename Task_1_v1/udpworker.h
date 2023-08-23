#ifndef UDPWORKER_H
#define UDPWORKER_H

#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDateTime>
#include <QDebug>

#define BIND_PORT_ONE 12345
#define BIND_PORT_TWO 12346

class UDPworker : public QObject
{
    Q_OBJECT
public:
    explicit UDPworker(QObject *parent = nullptr);
    void InitSocket( void );
    void ReadDatagram( QNetworkDatagram datagram);
    void SendDatagram(QByteArray data);

    void SendDatagramMessege(QByteArray dataMessege);
    void ReadDataMessege(QNetworkDatagram dataMes);

private slots:
    void readPendingDatagrams(void);
    void PendingMessege(void);

private:
    QUdpSocket* serviceUdpSocket;
    QUdpSocket* messegeUdpSocket;
    QUdpSocket* receiverUdpMessege;


signals:
    void sig_sendTimeToGUI(QDateTime data);
    void sig_sendMessegeTextToGUI(QString textMessege, QString addressSender, uint16_t sizeMessege);
};

#endif // UDPWORKER_H
