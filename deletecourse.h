#ifndef DELETECOURSE_H
#define DELETECOURSE_H

#include <QDialog>
#include<QSqlQuery>
#include<QMessageBox>
#include<QtSql>



namespace Ui
{
    class deletecourse;
}

class deletecourse : public QDialog
{
    Q_OBJECT

public:
    explicit deletecourse(QWidget *parent = 0);
    ~deletecourse();

private slots:
    void on_pushButton_deleteCourse_clicked();



private:
    Ui::deletecourse *ui;
};

#endif // DELETECOURSE_H
