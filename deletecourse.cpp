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

    QString queryRecordRow;
    bool isNumericalRow = selectedRecord.toInt();

    //checks for numerical user input
    if(!isNumericalRow)
    {
        QMessageBox::critical(this,"Error","Please enter a numerical row number.");
    }

    //checks to see if the record the user searched for exists
    deleteRecord.exec("SELECT ROWID FROM studentData WHERE ROWID ='"+selectedRecord+"'");
    deleteRecord.next();

    queryRecordRow = deleteRecord.value(0).toString();

    if(queryRecordRow == selectedRecord)
    {
        QMessageBox::information(this,"Deletion Successful","Record successfully found and deleted.");
        deleteRecord.exec("DELETE FROM studentData WHERE ROWID='"+selectedRecord+"'");
    }
    else
    {
        QMessageBox::critical(this,"Search Error","The record you are searching for was not found.");
    }

    ui->lineEdit_rowNumber->clear();
}
