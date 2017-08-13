#include "database.h"

bool database::isCreated = false;
database *database::instance = NULL;



//creates the path to the database
void database::SetDBPath(const QString &path)
{
  myDatabase = QSqlDatabase::addDatabase("QSQLITE");
  myDatabase.setDatabaseName(path);

  if(!myDatabase.open())
  {
      std::cout << "Error::the database has failed to open.\n";
  }
  else
  {
      std::cout << "Database connection successful.\n";
  }
}

//destructor sets flag to false
database::~database()
{
   isCreated = false;
}

//gets the instance of the database object
database *database::getInstance()
{
    if (!isCreated)
    {
        instance = new database();
        isCreated = true;
        return instance;
    }
    else
    {
        return instance;
    }
}
