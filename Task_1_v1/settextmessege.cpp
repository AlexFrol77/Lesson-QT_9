#include "settextmessege.h"
#include "ui_settextmessege.h"

SetTextMessege::SetTextMessege(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetTextMessege)
{
    ui->setupUi(this);
}

SetTextMessege::~SetTextMessege()
{
    delete ui;
}

void SetTextMessege::on_pb_sendTextMessege_clicked()
{
    QString textMessege = ui->te_setTextMessege->toPlainText();
    QByteArray dataMessege;
    QDataStream outTextMessege(&dataMessege, QIODevice::WriteOnly);
    outTextMessege << textMessege;
    udpWorker = new UDPworker;
    udpWorker->SendDatagramMessege(dataMessege);
    this->close();
}

