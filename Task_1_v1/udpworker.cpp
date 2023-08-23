#include "udpworker.h"

UDPworker::UDPworker(QObject *parent) : QObject(parent)
{

}

/*!
 * @brief Метод инициализирует UDP сервер
 */
void UDPworker::InitSocket()
{

    serviceUdpSocket = new QUdpSocket(this);
    receiverUdpMessege = new QUdpSocket(this);
    /*
     * Соединяем присваиваем адрес и порт серверу и соединяем функцию
     * обраотчик принятых пакетов с сокетом
     */
    serviceUdpSocket->bind(QHostAddress::LocalHost, BIND_PORT_ONE);
    receiverUdpMessege->bind(QHostAddress::LocalHost, BIND_PORT_TWO);

    connect(serviceUdpSocket, &QUdpSocket::readyRead, this, &UDPworker::readPendingDatagrams);
    connect(receiverUdpMessege, &QUdpSocket::readyRead, this, &UDPworker::PendingMessege);

}

/*!
 * @brief Метод осуществляет обработку принятой датаграммы
 */
void UDPworker::ReadDatagram(QNetworkDatagram datagram)
{
    QByteArray data;
    data = datagram.data();
    QDataStream inStr(&data, QIODevice::ReadOnly);
    QDateTime dateTime;
    inStr >> dateTime;

    emit sig_sendTimeToGUI(dateTime);
}

/*!
 * @brief Метод осуществляет опередачу датаграммы
 */
void UDPworker::SendDatagram(QByteArray data)
{
    /*
     *  Отправляем данные на localhost и задефайненный порт
     */
    serviceUdpSocket->writeDatagram(data, QHostAddress::LocalHost, BIND_PORT_ONE);
}

void UDPworker::SendDatagramMessege(QByteArray dataMessege)
{
    messegeUdpSocket = new QUdpSocket(this);
    QNetworkDatagram datagramMessege;
    datagramMessege.setData(dataMessege);
    datagramMessege.setDestination(QHostAddress::LocalHost, BIND_PORT_TWO);
    messegeUdpSocket->writeDatagram(datagramMessege);
}

void UDPworker::ReadDataMessege(QNetworkDatagram dataMes)
{
    QByteArray dataMessege;
    dataMessege = dataMes.data();
    QString addressSender = dataMes.senderAddress().toString();
    uint16_t sizeMessege = dataMessege.size();
    QString textMessege;
    QDataStream inTextMessege(&dataMessege, QIODevice::ReadOnly);

    inTextMessege >> textMessege;

    emit sig_sendMessegeTextToGUI(textMessege, addressSender, sizeMessege);
}

/*!
 * @brief Метод осуществляет чтение датаграм из сокета
 */
void UDPworker::readPendingDatagrams( void )
{
    /*
     *  Производим чтение принятых датаграмм
     */
    while(serviceUdpSocket->hasPendingDatagrams()){
            QNetworkDatagram datagram = serviceUdpSocket->receiveDatagram();
            ReadDatagram(datagram);
    }
}

void UDPworker::PendingMessege()
{
    while(receiverUdpMessege->hasPendingDatagrams()) {
        QNetworkDatagram datagramMes = receiverUdpMessege->receiveDatagram();
        ReadDataMessege(datagramMes);
    }
}
