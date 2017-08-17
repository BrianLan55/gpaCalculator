#ifndef EDITCOURSE_H
#define EDITCOURSE_H

#include <QDialog>
#include<QSqlQuery>
#include<QMessageBox>
#include "mainwindow.h"

namespace Ui {
class editcourse;
}

class editcourse : public QDialog
{
    Q_OBJECT

public:
    explicit editcourse(QWidget *parent = 0);
    ~editcourse();

private slots:
    void on_pushButton_editCourse_clicked();

private:
    Ui::editcourse *ui;
};

#endif // EDITCOURSE_H
