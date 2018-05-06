#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QStandardItemModel"
#include <stdio.h>
#include "QVariant"
#include <ctime>
#include <QCloseEvent>
#include "QTextEdit"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStandardItemModel *model = new QStandardItemModel(24,2,this); //24 Rows and 2 Columns

    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Аттенюатор")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Фаза")));

    this->fillTableModelWithRandomData(model);

    ui->tableView->setModel(model);

    connect(ui->send_data_button, SIGNAL (clicked()), this, SLOT (sendData()));
    connect(ui->listen_button, SIGNAL (clicked()), this, SLOT (toggleServerAndClientSockets()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::toggleServerAndClientSockets() {
    unsigned short localPort = ui->local_port_input->toPlainText().toUShort();
    unsigned short port = ui->port_input->toPlainText().toUShort();

    if (connectionManager.isConnectionOpened()) {
        connectionManager.closeSocket();
        ui->listen_button->setText("Listen");
        ui->send_data_button->setEnabled(false);
    } else {
        int result = connectionManager.openClientSocket(port);
        if (result == 0) {
            ui->send_data_button->setEnabled(true);
        }
        ui->listen_button->setText("Cancel");
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if(connectionManager.isConnectionOpened()) {
        connectionManager.closeSocket();
    }
    event->accept();
}

void MainWindow::sendData() {
    char collectedData[1024];
    this->collectDataFromTable(collectedData);
    printf(collectedData);
    connectionManager.sendData(collectedData);
}

char* MainWindow::collectDataFromTable(char* outData) {
    char res[1024] = "";

    for(int row = 0; row < 24; row++) {

        // 1. append number of channel

        strcat(res, this->convertIntToChar(row + 1));

        // 2. Append 1 - is hardcoded
        strcat(res, this->convertIntToChar(1));

        // 3. Append value of phase and attenuator(col = 0, col = 1)
        for(int col = 2; col > 0; col--) {
            // get data from table cell
            QVariant qVariant = ui->tableView->model()->data(ui->tableView->model()->index(row,col));
            int storedValue = qVariant.toInt();


            strcat(res, this->convertIntToChar(storedValue));
            // printf("row=%d, col=%d: %d\n",row,col,storedValue);
        }
    }

    printf(res);
    for (int i = 0; i < 1024; i++) {
        outData[i] = res[i];
    }
}

void MainWindow::fillTableModelWithRandomData(QStandardItemModel *model) {
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    for(int col = 0; col < 2; col++) {
        for(int row = 0; row < 24; row++) {
            int randomValue = 1 + std::rand()/((RAND_MAX + 1u)/64);
            // printf("randomValue: %d", randomValue);
            model->setItem(row, col, new QStandardItem(QString::number(randomValue)));
        }
    }

}

const char* MainWindow::convertIntToChar(int number) {
    return std::to_string(number).c_str();
}

//const char* MainWindow::getDataFromTextEdit(QTextEdit*& qTextEdit) {
//    return qTextEdit->toPlainText().toUShort();
//}
