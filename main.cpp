/********
  CLASS NAME: Main
  PURPOSE: Starts up the system. Displays the login form to the user.

  TRACEABILITY: This class traces back to..

  CREATED BY: Nisrin Abou-Seido
  LAST MODIFIED: March 20, 2011

***********/


#include <QtGui/QApplication>
#include "login.h"

#include <iostream>

#include "eobcproject.h"
#include "messagecontrol.h"
#include "QDebug"
#include "xmlgenerator.h"
using namespace std;


/*******make sure the file JNFconfig.conf is in home/<userfolder>/<yourusername>/.config directory*************/


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login *w = new Login();
    w->show();


    QSettings settings("JNFconfig"); // opens the configuration file. File should be located in: home/<userfolder>/<yourusername>/.config



    //get the database path
    settings.beginGroup("database");
    QString dbPath =  settings.value("db_filepath").toString();
    qDebug() << dbPath;

    settings.endGroup();

    //get myFacilityID and IP address and whether facility is a main facility

    settings.beginGroup("myfacility");

    DataStorage::myFacilityID= settings.value("id").toInt();
    DataStorage::myFacilityIPaddress= settings.value("IPaddress").toString();
    QString is_main= settings.value("isMain").toString();

    settings.endGroup();

    qDebug() << is_main;
    if(is_main == "true")
        DataStorage::isMain = true;
    else
        DataStorage::isMain = false;


    qDebug() << DataStorage::isMain;
    qDebug() << DataStorage::isMainFacility();


    //initialize the Message control which listens for incoming messages
    MessageControl* messageControl = new MessageControl();

   //pass "connection handle" to the Database class
   //handle errors if database connection fails
   //check that tables exist
   //close database connection
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "permanent");
        QMessageBox error;
        db.setDatabaseName(dbPath);
        //connect to the database
        bool isOpen = db.open();
        if (!isOpen){
            //handle the errors if the database connection fails
            error.setText("Connection failed");
            error.exec();
        }else {
            //pass the connection to the Database class through the DataStorage class
            //also need to check that tables exist
            Database::Initialize();
        }
    }


    //qDebug()<<xmlgenerator::patientOperationXML("Add","2343",3,4,true,"March 4, 2010","March 5, 2010","Paula","Moo",1,2);

    //qDebug()<<"bop";

    //qDebug()<<xmlgenerator::rebuild();
    //qDebug()<<xmlgenerator::rebuildResponse();
    //qDebug()<<xmlgenerator::addFacility(3,1,34,45,5,6,8,"Homeland",true,"Hospital");
    //qDebug()<<xmlgenerator::addBeds(4,3,1,0,0,true);



    DataStorage::addFacility("The JNF hospital",400,400,3,3,"Hospital");
    DataStorage::addFacility("CHEO", 56, 45, 3, 23, "Hospital");
    DataStorage::addFacility("General Hospital", 70, 80, 2, 20, "Hospital");
    DataStorage::addFacility("Nursing Home 1",200,200,5,15, "Nursing Home");

    DataStorage::addBeds(3,10,"AC");
    DataStorage::addBeds(3,14,"CCC");

    DataStorage::addBeds(23,24,"AC");
    DataStorage::addBeds(23,5,"CCC");

    DataStorage::addBeds(15,14,"LTC");

    DataStorage::addPatientToWaitingList("12","Joe", "Black",1,"120112T11:33:54");
    DataStorage::addPatientToWaitingList("13","Jane", "Black",1,"120112T11:33:54");
    DataStorage::addPatientToWaitingList("14","Bob", "Smith",1,"120112T11:33:54");

    DataStorage::addPatientToWaitingList("12","Joe", "Black",2,"120112T11:33:54");
    DataStorage::addPatientToWaitingList("13","Jane", "Black",2,"120112T11:33:54");
    DataStorage::addPatientToWaitingList("14","Bob", "Smith",2,"120112T11:33:54");

    DataStorage::assignPatientToBed(3,"12",1,"120112T11:33:54");
    DataStorage::assignPatientToBed(3,"13",1,"120112T11:33:54");
    DataStorage::assignPatientToBed(3,"14",1,"120112T11:33:54");



    return a.exec();
}
