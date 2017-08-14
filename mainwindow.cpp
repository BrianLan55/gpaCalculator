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

    QString courseName = ui->lineEdit_courseName->text();
    QString units      = ui->lineEdit_units->text();
    QString grade      = ui->lineEdit_grade->text().toUpper();

    int checkUnits = units.toInt(); //used to check if input is numerical

    bool emptyFields  = courseName.isEmpty() || units.isEmpty() || grade.isEmpty();
    bool integerUnits = units.toInt();
    bool invalidUnits = checkUnits < 1 || checkUnits > 5;
    bool validGrades  = grade == 'A' || grade == 'B' || grade == 'C' || grade == 'D' || grade == 'F';

    QSqlQuery enterData;



    //Begin error checking
    if(emptyFields)
    {
        QMessageBox::critical(this,"Input Error","Please fill in all fields.");
    }

    //checks for numerical data and units >=1 and units <=5
    else if(!integerUnits || invalidUnits)
    {
         QMessageBox::critical(this,"Input Error","Please enter valid units(Units 0-5).");
    }

    //checks for valid letter grades
    else if(!validGrades)
    {
         QMessageBox::critical(this,"Input Error","Please enter a valid grade(A,B,C,D or F).");
    }

    else
    {
        enterData.exec("INSERT INTO studentData(course, units, grade) VALUES ('"+courseName+"', '"+units+"', '"+grade+"')");
        QMessageBox::information(this,"Sucess","Data successfully processed.");
    }
}

/*******************************
 *Clears all fields when pushed*
 ******************************/
void MainWindow::on_pushButton_clearFields_clicked()
{
    ui->lineEdit_courseName->clear();
    ui->lineEdit_grade->clear();
    ui->lineEdit_units->clear();
}
