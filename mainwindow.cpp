#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include "deletecourse.h"


/*********************************
 * MainWindow default constructor*
 ********************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //database object created to open a connection to the database
    database *obj;
    obj = database::getInstance();
    obj->SetDBPath("C:/Users/Brian/Documents/QtProjects/gpa/gpa.sqlite");

    ui->setupUi(this);
    displayTableView();
}

 /************************************
  * Displays the tableview of classes*
  ***********************************/
void MainWindow::displayTableView()
{
    QSqlQueryModel *preTableModel = new QSqlQueryModel();
    QSqlQuery *preQuery = new QSqlQuery();

    preQuery->exec("SELECT course,units,grade FROM studentData");
    preTableModel->setQuery(*preQuery);
    ui->tableView_viewData->setModel(preTableModel);
    ui->tableView_viewData->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_viewData->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

/*******************************
 *MainWindow default destructor*
 ******************************/
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
    QString numericalGrade;//numerical grade equivenant stored in the database.

    int checkUnits = units.toInt(); //used to check if input is numerical

    bool emptyFields  = courseName.isEmpty() || units.isEmpty() || grade.isEmpty();
    bool integerUnits = units.toInt();
    bool invalidUnits = checkUnits < 1 || checkUnits > 5;
    bool validGrades  = grade == 'A' || grade == 'B' || grade == 'C' || grade == 'D' || grade == 'F';

    QSqlQuery enterData;


    if(grade =='A')
    {
        numericalGrade = '4';
    }
    else if(grade == 'B')
    {
        numericalGrade = '3';
    }
    else if(grade == 'C')
    {
        numericalGrade = '2';
    }
    else if(grade == 'D')
    {
        numericalGrade = '1';
    }
    else
    {
        numericalGrade = '0';
    }
\

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
        enterData.exec("INSERT INTO studentData(course, units, grade,numericalGrade) VALUES ('"+courseName+"', '"+units+"', '"+grade+"','"+numericalGrade+"')");
        QMessageBox::information(this,"Sucess","Data successfully processed.");
        displayTableView();
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

/**********************************
 *Shows the delete a course window*
 *********************************/
void MainWindow::on_pushButton_deleteCourse_clicked()
{


    deletecourse *removeClass = new deletecourse();
    removeClass->show();
    on_pushButton_refresh_clicked();

}


/*****************************
 * When pushed the tableView *
 * updates its data          *
 ****************************/
void MainWindow::on_pushButton_refresh_clicked()
{
    displayTableView();
}

/********************************************
 * When pushed the method calculates the gpa*
 * of the user and prints it to a qLabel.   *
 *******************************************/
void MainWindow::on_pushButton_calculateGPA_clicked()
{
    QSqlQuery calcPointsEarned;
    QSqlQuery calcTotalCredits;

    double pointsEarned;  //The number of units received multiplied by the grade received
    double totalCredits;  //The total number of credits possible
    double calculatedGpa;

    int index1 = 0;
    int index2 = 0;

    QString gpa; //The gpa converted from <calculatedGPA>to a QString
                 //in order to print to the qLabel <label_gpa>


    //Executing queries
    calcTotalCredits.exec("SELECT SUM (units) FROM studentData");
    calcPointsEarned.exec("SELECT SUM(units * numericalGrade) FROM studentData");


    //Begin summing values from the database
    while( calcTotalCredits.next())
    {
        totalCredits = totalCredits + calcTotalCredits.value(index1).toInt();
        index1++;
    }

   while(calcPointsEarned.next())
   {
       pointsEarned = pointsEarned +calcPointsEarned.value(index2).toInt();
       index2++;
   }

   //Calculates the gpa, converts it into a QString and prints to
   //The qLabel <label_gpa>
   calculatedGpa = pointsEarned / totalCredits;
   gpa = QString::number(calculatedGpa, 'f', 2);
   ui->label_gpa->setText(gpa);
}
