#include "deletecourse.h"
#include "ui_deletecourse.h"


deletecourse::deletecourse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deletecourse)
{
    ui->setupUi(this);
    this->setFixedSize(175,150);
}

deletecourse::~deletecourse()
{
    delete ui;
}

/**********************************
 * Deletes a selected record from *
 * the database by course row ID  *
 *********************************/
void deletecourse::on_pushButton_deleteCourse_clicked()
{
    QString selectedRecord = ui->lineEdit_rowNumber->text();
    QSqlQuery deleteRecord;
    bool isRowNum = selectedRecord.toInt();


    if(!isRowNum)
    {
        QMessageBox::critical(this,"Error","Please enter a numerical row number.");
    }
    else
    {
        deleteRecord.exec("DELETE FROM studentData WHERE ROWID='"+selectedRecord+"'");
    }

    ui->lineEdit_rowNumber->clear();
}
