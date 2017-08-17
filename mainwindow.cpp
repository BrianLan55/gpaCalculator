#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include "deletecourse.h"
#include"editcourse.h"


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
    this->setFixedSize(600,400);
}

 /************************************
  * Displays the tableview of classes*
  ***********************************/
void MainWindow::displayTableView()
{
    QSqlQueryModel *preTableModel = new QSqlQueryModel();
    QSqlQuery *preQuery = new QSqlQuery();

    preQuery->exec("SELECT rowid, course,units,grade FROM studentData");
    preTableModel->setQuery(*preQuery);
    ui->tableView_viewData->setModel(preTableModel);
    ui->tableView_viewData->verticalHeader()->setVisible(false);
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
    QString courseName = ui->lineEdit_courseName->text().toUpper();
    QString units      = ui->lineEdit_units->text();
    QString grade      = ui->lineEdit_grade->text().toUpper();
    QString numericalGrade;//numerical grade equivenant stored in the database.

    QSqlQuery enterData;

    bool flag = errorCheck(courseName, units, grade, numericalGrade);


    if(flag == true)
    {
        enterData.exec("INSERT INTO studentData(course, units, grade,numericalGrade) "
                       "VALUES ('"+courseName+"', '"+units+"', '"+grade+"','"+numericalGrade+"')");
    }

    displayTableView();
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
    QSqlQuery validateExistingRecords;

    double pointsEarned;  //The number of credits received multiplied by the grade received
    double totalCredits;  //The total number of credits possible
    double calculatedGpa = 0.0;

    int index1 = 0;
    int index2 = 0;
    int recordCount;

    QFont myFont("Ariel", 10, QFont::Bold);

    QString gpa; //The gpa converted from <calculatedGPA>to a QString
                 //in order to print to the qLabel <label_gpa>


    //Executing queries
    validateExistingRecords.exec("SELECT COUNT(*) FROM studentData");
    calcTotalCredits.exec("SELECT SUM (units) FROM studentData");
    calcPointsEarned.exec("SELECT SUM(units * numericalGrade) FROM studentData");

    //
    validateExistingRecords.next();
    recordCount = validateExistingRecords.value(0).toInt();

    //if there are records in the database values are pulled from the database to
    //calculate the user's gpa, else their gpa is set to 0
    if(recordCount != 0)
    {
        //Begin summing values from the database
        while( calcTotalCredits.next())
        {
            totalCredits = totalCredits + calcTotalCredits.value(index1).toInt();
            index1++;
        }

        while(calcPointsEarned.next())
        {
            pointsEarned = pointsEarned + calcPointsEarned.value(index2).toInt();
            index2++;
        }

        //calculates GPA
        calculatedGpa = pointsEarned / totalCredits;
     }//end if(recordCount != 0)
    else
    {
        calculatedGpa = 0.0;
    }

    //Converts the gpa into a QString and prints to
    //The qLabel <label_gpa>
   gpa = QString::number(calculatedGpa, 'f', 2);

   ui->label_gpa->setFont(myFont);
   ui->label_gpa->setText(gpa);

}

/*******************************************
 *When pushed the user is allowed to edit a*
 *existing record in the database.         *
 ******************************************/
void MainWindow::on_pushButton_editCourse_clicked()
{
    editcourse *editCourse = new editcourse();
    editCourse->show();
    displayTableView();
}

/*******************************************
 *Function takes in a QString containing a *
 *valid letter grade and calculates its    *
 * numerical equivelant                    *
 ******************************************/
QString calcNumGrade(QString &grade)
{
    QString numericalGrade;

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

    return numericalGrade;
}
/**********************************************************************************
 * This function takes in 4 QStrings: 3 by copy and 1 by value                    *
 * <numericalGrade:empty at the time>, * it checks for valid values, if the values*
 *  are valid it passes <grade:by copy> to the function                           *
 * [QString calcNumGrade(QString &string)] where the appropriate numerical grade  *
 *  is calculated. Finally after that function call ends <numericalGrade>         *
 * receives a valid value and returns a bool(true) to the main calling function.  *
 *********************************************************************************/
bool errorCheck(QString courseName, QString units, QString grade, QString &numericalGrade)
{
    QWidget *messageBoxPtr = new QWidget();//used to output a message box to the mainwindow since
                                           //<errorCheck> is not a function of the class <MainWindow>

    int checkUnits = units.toInt(); //used to check if input is numerical

    bool emptyFields  = courseName.isEmpty() || units.isEmpty() || grade.isEmpty();
    bool integerUnits = units.toInt();
    bool invalidUnits = checkUnits < 1 || checkUnits > 5;
    bool validGrades  = grade == 'A' || grade == 'B' || grade == 'C' || grade == 'D' || grade == 'F';
    bool flag = false; //used to check if the error checking tests were successful



    //Begin error checking
    if(emptyFields)
    {
        QMessageBox::critical(messageBoxPtr,"Input Error","Please fill in all fields.");
    }

    //checks for numerical data and units >=1 and units <=5
    else if(!integerUnits || invalidUnits)
    {
         QMessageBox::critical(messageBoxPtr,"Input Error","Please enter valid units(Units 0-5).");
    }

    //checks for valid letter grades
    else if(!validGrades)
    {
         QMessageBox::critical(messageBoxPtr,"Input Error","Please enter a valid grade(A,B,C,D or F).");
    }

    else
    {
        numericalGrade = calcNumGrade(grade);
        flag = true;
        QMessageBox::information(messageBoxPtr,"Sucess","Data successfully processed.");
    }
    return flag;
}


