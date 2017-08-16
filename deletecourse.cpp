#include "deletecourse.h"
#include "ui_deletecourse.h"


deletecourse::deletecourse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deletecourse)
{
    ui->setupUi(this);
    displayTableView();
}

deletecourse::~deletecourse()
{
    delete ui;
}

/************************************
 * Displays the tableview of classes*
 ***********************************/
void deletecourse::displayTableView()
{
   QSqlQueryModel *preTableModel = new QSqlQueryModel();
   QSqlQuery *preQuery = new QSqlQuery();

   preQuery->exec("SELECT course,units,grade FROM studentData");
   preTableModel->setQuery(*preQuery);
   ui->tableView_viewData->setModel(preTableModel);
   ui->tableView_viewData->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   ui->tableView_viewData->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


/**********************************
 * Deletes a selected record from *
 * the database by course name    *
 *********************************/
void deletecourse::on_pushButton_deleteCourse_clicked()
{
    QString selectedRecord = ui->lineEdit_rowNumber->text();
    QSqlQuery deleteRecord;

    deleteRecord.exec("DELETE FROM studentData WHERE course='"+selectedRecord+"'");
    displayTableView();
}
