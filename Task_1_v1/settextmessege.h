#ifndef SETTEXTMESSEGE_H
#define SETTEXTMESSEGE_H

#include <QDialog>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include "udpworker.h"

namespace Ui {
class SetTextMessege;
}

class SetTextMessege : public QDialog
{
    Q_OBJECT

public:
    explicit SetTextMessege(QWidget *parent = nullptr);
    ~SetTextMessege();

private slots:
    void on_pb_sendTextMessege_clicked();

private:
    Ui::SetTextMessege *ui;
    UDPworker* udpWorker;
};

#endif // SETTEXTMESSEGE_H
