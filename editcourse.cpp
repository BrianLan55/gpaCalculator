#include "editcourse.h"
#include "ui_editcourse.h"


editcourse::editcourse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editcourse)
{
    ui->setupUi(this);
    this->setFixedSize(200,200);
}

editcourse::~editcourse()
{
    delete ui;
}

void editcourse::on_pushButton_editCourse_clicked()
{
    QString courseID   = ui->lineEdit_courseID->text();
    QString courseName = ui->lineEdit_courseName->text().toUpper();
    QString units      = ui->lineEdit_units->text();
    QString grade      = ui->lineEdit_grade->text().toUpper();
    QString numericalGrade;//numerical grade equivenant stored in the database.
    QString queryRecordRow;

    QSqlQuery editCourse;

    editCourse.exec("SELECT ROWID FROM studentData WHERE ROWID='"+courseID+"'");
    editCourse.next();

    queryRecordRow = editCourse.value(0).toString();

    if(queryRecordRow == courseID)
    {
        bool flag = errorCheck(courseName, units, grade, numericalGrade);

        if(flag == true)
        {
            editCourse.exec("UPDATE studentData SET course='"+courseName+"', units ='"+units+"',grade='"+grade+"', numericalGrade='"+numericalGrade+"' WHERE ROWID='"+courseID+"' ");
        }
    }
    else
    {
        QMessageBox::critical(this,"Search Error", "The record you are searching for was not found.");
    }

    ui->lineEdit_courseID->clear();
    ui->lineEdit_courseName->clear();
    ui->lineEdit_units->clear();
    ui->lineEdit_grade->clear();
}
