#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //database object created to open a connection to the database
    database *obj;
    obj = database::getInstance();
    obj->SetDBPath("C:/Users/Brian/Documents/QtProjects/gpa/gpa.sqlite");

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/***************************************************************
 * When the pushButton <submitData> is clicked the user's data *
 * will be stored in the database.                             *
 **************************************************************/
void MainWindow::on_pushButton_submitData_clicked()
{
    /*
    QString courseName = ui->lineEdit_courseName->text();
    QString units      = ui->lineEdit_units->text();
    QString grade      = ui->lineEdit_grade->text();

    QSqlQuery enterData;

    enterData.exec("INSERT INTO studentData(course, units, grade) VALUES ('"+courseName+"', '"+units+"', '"+grade+"')");
    */
}
