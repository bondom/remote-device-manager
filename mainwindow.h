#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "connection_manager.h"
#include "QStandardItemModel"
#include "QCloseEvent"
#include "QTextEdit"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    ConnectionManager connectionManager;
    Ui::MainWindow *ui;
    char* collectDataFromTable(char* outData);
    void fillTableModelWithRandomData(QStandardItemModel *model);
    void closeEvent(QCloseEvent *event);

    // helpers
    const char* convertIntToChar(int number);
    // const char* getDataFromTextEdit(QTextEdit*& qTextEdit);
signals:
public slots: // is a function that is used to accept and respond to a signal.
    void toggleServerAndClientSockets();
    void sendData();
};

#endif // MAINWINDOW_H
