#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include<QSqlQuery>
#include<QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_submitData_clicked();

    void on_pushButton_clearFields_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
