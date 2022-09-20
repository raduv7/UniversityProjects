#include "menu.h"
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>
#include <QHeaderView>
#include <QMessageBox>
#include <iostream>

using namespace std;

GUI::GUI(ActivityService& srv) : srv(srv) {
    flirtType = flirtDescr = "";
    string ui;
    initializeGUIComponents();
    connectSignalsSlots();
    reloadActivityList(srv.getAll(flirtDescr, flirtType));
}


void GUI::initializeGUIComponents() {

    //impartim fereastra in 2: in stanga, butoane+labels+qlineedits
    //iar in dreapta: tabelul cu melodii

    //"stanga" si "dreapta" pentru ca este QHBoxLayout
    //se adauga componente incepand din stanga, pe orizontala
    //aici: "left" component, then "right" component
    //care la randul lor contin alte componente

    //main layout
    QHBoxLayout* lyMain = new QHBoxLayout;
    this->setLayout(lyMain);


    //left part of the window
    //pentru aceasta parte setam layout vertical
    QWidget* left = new QWidget;
    QVBoxLayout* lyLeft = new QVBoxLayout;
    left->setLayout(lyLeft);

    //componente pentru functionalitatea de adaugare a unei melodii
    //folosim un QFormLayout pentru detaliile de adaugare a unei melodii
    QWidget* form = new QWidget;
    QFormLayout* lyForm = new QFormLayout;
    form->setLayout(lyForm);
    editTitlu = new QLineEdit;
    editArtist = new QLineEdit;
    editGen = new QLineEdit;
    editDurata = new QLineEdit;

    lyForm->addRow(lblTitlu, editTitlu);
    lyForm->addRow(lblArtist, editArtist);
    lyForm->addRow(lblGen, editGen);
    lyForm->addRow(lblDurata, editDurata);
    btnAddSong = new QPushButton("Add activity, sir!");
    btnActSong = new QPushButton("Update activity, sir!");
    btnDelSong = new QPushButton("Delete activity, sir!");
    btnFndSong = new QPushButton("Find activity, sir!");
    lyForm->addWidget(btnAddSong);
    lyForm->addWidget(btnActSong);
    lyForm->addWidget(btnDelSong);
    lyForm->addWidget(btnFndSong);

    //adaugam toate componentele legate de adaugare melodie
    //in layout-ul care corespunde partii din stanga a ferestrei
    lyLeft->addWidget(form);


    //Radio Buttons: ne ajuta cand trebuie sa selectam doar o 
    //optiune din mai multe (doar un RadioButton poate fi selectat
    //la un moment dat)


    //vs. CheckBox (see documentation)
    //also see documentation on QGroupBox, QRadioButton pentru detalii

    //cream un GroupBox pentru radiobuttons care corespund 
    //criteriilor de sortare pe care le avem (dupa artist+titlu 
    //si durata) + butonul de sortare

    QVBoxLayout* lyRadioBox = new QVBoxLayout;
    this->groupBox->setLayout(lyRadioBox);
    lyRadioBox->addWidget(radioSrtArtistTitlu);
    lyRadioBox->addWidget(radioSrtDurata);

    btnSortSongs = new QPushButton("Sort activities, sir!");
    lyRadioBox->addWidget(btnSortSongs);

    //adaugam acest grup in partea stanga, 
    //dupa componentele pentru adaugare in layout-ul vertical
    lyLeft->addWidget(groupBox);

    //cream un form pentru filtrarea dupa gen 
    QWidget* formFilter = new QWidget;
    QFormLayout* lyFormFilter = new QFormLayout;
    formFilter->setLayout(lyFormFilter);
    editFilterType = new QLineEdit();
    editFilterDescr = new QLineEdit();
    lyFormFilter->addRow(lblFilterCriteriaType, editFilterType);
    lyFormFilter->addRow(lblFilterCriteriaDescr, editFilterDescr);
    btnFilterSongs = new QPushButton("Filter activities, sir!");
    lyFormFilter->addWidget(btnFilterSongs);

    lyLeft->addWidget(formFilter);

    //Buton folosit pentru a reincarca datele
    //i.e. afisam toate melodiile in tabel, in ordinea initiala din fisier
    btnDelAllData = new QPushButton("Delete all data, sir!");
    btnGenAllData = new QPushButton("Generate all data, sir!");
    btnUndo = new QPushButton("Undo last operation, sir!");
    btnReloadData = new QPushButton("Reload data, sir!");
    lyLeft->addWidget(btnDelAllData);
    lyLeft->addWidget(btnGenAllData);
    lyLeft->addWidget(btnUndo);
    lyLeft->addWidget(btnReloadData);


    //componenta right - contine doar tabelul cu melodii
    QWidget* right = new QWidget;
    QVBoxLayout* lyRight = new QVBoxLayout;
    right->setLayout(lyRight);

    int noLines = 10;
    int noColumns = 4;
    this->tableSongs = new QTableWidget{ noLines, noColumns };

    //setam header-ul tabelului
    QStringList tblHeaderList;
    tblHeaderList << "Name" << "Description" << "Type" << "Duration";
    this->tableSongs->setHorizontalHeaderLabels(tblHeaderList);

    //optiune pentru a se redimensiona celulele din tabel in functie de continut
    this->tableSongs->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


    lyRight->addWidget(tableSongs);

    lyMain->addWidget(left);
    lyMain->addWidget(right);
}



void GUI::connectSignalsSlots() {
    QObject::connect(btnAddSong, &QPushButton::clicked, this, &GUI::guiAdd);
    QObject::connect(btnActSong, &QPushButton::clicked, this, &GUI::guiAct);
    QObject::connect(btnDelSong, &QPushButton::clicked, this, &GUI::guiDel);
    QObject::connect(btnFndSong, &QPushButton::clicked, this, &GUI::guiFnd);

    QObject::connect(btnSortSongs, &QPushButton::clicked, [&]() {
        if (this->radioSrtArtistTitlu->isChecked()) {
                srv.sort("asc", "description");
                this->reloadActivityList(srv.getAll(flirtDescr,flirtType));
            }
        else if (this->radioSrtDurata->isChecked()) {
                srv.sort("asc", "duration");
                this->reloadActivityList(srv.getAll(flirtDescr,flirtType));
            }
        });

    QObject::connect(btnFilterSongs, &QPushButton::clicked, [&]() {
            flirtType = this->editFilterType->text().toStdString();
            flirtDescr = this->editFilterDescr->text().toStdString();
            /*            char chr;
            if (filterC.size() > 1) {
                chr = filterC[0];
            }
            flirtDescr = "";
            flirtType = "";

            for (; filterC[0] != ':' && !filterC.empty();filterC.erase(filterC.begin()));
            filterC.erase(filterC.begin());


            if ( 'd' == chr || chr == 'D') {
                flirtDescr = filterC;
            }
            if ( 't' == chr || chr == 'T') {
                flirtType = filterC;

            }
            */
            

            // QMessageBox::information(this, "Info", QString::fromStdString(flirtDescr + " " + flirtType));

            this->reloadActivityList(srv.getAll(flirtDescr,flirtType));
        });
/*
    QObject::connect(btnDelAllData, &QPushButton::clicked, [&]() {
        this->reloadActivityList(srv.getAll(flirtDescr,flirtType));
        });

    QObject::connect(btnGenAllData, &QPushButton::clicked, [&]() {
        this->reloadActivityList(srv.getAll(flirtDescr,flirtType));
        });

    QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
        this->reloadActivityList(srv.getAll(flirtDescr,flirtType));
        });
        */


    QObject::connect(btnDelAllData, &QPushButton::clicked, this, &GUI::guiDelAll);
    QObject::connect(btnGenAllData, &QPushButton::clicked, this, &GUI::guiGenAll);
    QObject::connect(btnUndo, &QPushButton::clicked, this, &GUI::guiUndo);
    QObject::connect(btnReloadData, &QPushButton::clicked, [&]() {
        this->reloadActivityList(srv.getAll(flirtDescr,flirtType));
        });

}

void GUI::reloadActivityList(vector<Activity> acts) {
    this->tableSongs->clearContents();
    this->tableSongs->setRowCount(acts.size());

    int lineNumber = 0;

    for (auto& act : acts) {
        this->tableSongs->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(act.getName())));
        this->tableSongs->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(act.getDescr())));
        this->tableSongs->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(act.getType())));
        this->tableSongs->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(act.getTime())));
        lineNumber++;
    }
}

    // try {

void GUI::guiAdd() {
        //preluare detalii din QLineEdit-uri
        string name = editTitlu->text().toStdString();
        string descr = editGen->text().toStdString();
        string type = editArtist->text().toStdString();
        int time = editDurata->text().toInt();

        //optional - golim QLineEdit-urile dupa apasarea butonului
        editTitlu->clear();
        editArtist->clear();
        editGen->clear();
        editDurata->clear();

        if (this->srv.add(name + ";" + type + ";" + descr + ";" + to_string(time))) {
            QMessageBox::information(this, "Info", QString::fromStdString("Activity added with success, sir!"));
        }
        else {
            QMessageBox::information(this, "Info", QString::fromStdString("Already added, sir!"));
        }
        this->reloadActivityList(this->srv.getAll(flirtDescr, flirtType));

        //afisam un mesaj pentru a anunta utilizatorul ca melodia s-a adaugat
        
}

void GUI::guiAct() {
        //preluare detalii din QLineEdit-uri
        string name = editTitlu->text().toStdString();
        string descr = editGen->text().toStdString();
        string type = editArtist->text().toStdString();
        int time = editDurata->text().toInt();

        //optional - golim QLineEdit-urile dupa apasarea butonului
        editTitlu->clear();
        editArtist->clear();
        editGen->clear();
        editDurata->clear();

        if (this->srv.update(name + ";" + type + ";" + descr + ";" + to_string(time))) {
            QMessageBox::information(this, "Info", QString::fromStdString("Activity updated with success, sir!"));
        }
        else {
            QMessageBox::information(this, "Info", QString::fromStdString("No such activity, sir!"));
        }
        this->reloadActivityList(this->srv.getAll(flirtDescr, flirtType));

        //afisam un mesaj pentru a anunta utilizatorul ca melodia s-a adaugat
        
}

void GUI::guiDel() {
        //preluare detalii din QLineEdit-uri
        string name = editTitlu->text().toStdString();
        string descr = editGen->text().toStdString();
        string type = editArtist->text().toStdString();
        int time = editDurata->text().toInt();

        //optional - golim QLineEdit-urile dupa apasarea butonului
        editTitlu->clear();
        editArtist->clear();
        editGen->clear();
        editDurata->clear();

        if (this->srv.del(name)) {
            QMessageBox::information(this, "Info", QString::fromStdString("Activity deleted with success, sir!"));
        }
        else {
            QMessageBox::information(this, "Info", QString::fromStdString("No such activity, sir!"));
        }
        this->reloadActivityList(this->srv.getAll(flirtDescr, flirtType));

        //afisam un mesaj pentru a anunta utilizatorul ca melodia s-a adaugat
        
}

void GUI::guiFnd() {
        //preluare detalii din QLineEdit-uri
        string name = editTitlu->text().toStdString();
        string descr = editGen->text().toStdString();
        string type = editArtist->text().toStdString();
        int time = editDurata->text().toInt();

        //optional - golim QLineEdit-urile dupa apasarea butonului
        editTitlu->clear();
        editArtist->clear();
        editGen->clear();
        editDurata->clear();

        string ret;
        if (this->srv.findActivity(name, ret)) {
            QMessageBox::information(this, "Info", QString::fromStdString("Found, sir: " + ret));
        }
        else {
            QMessageBox::information(this, "Info", QString::fromStdString("No such activity, sir!"));

        }
        this->reloadActivityList(this->srv.getAll(flirtDescr, flirtType));

        //afisam un mesaj pentru a anunta utilizatorul ca melodia s-a adaugat
        
}

void GUI::guiDelAll() {

        this->srv.delAll();
        this->reloadActivityList(this->srv.getAll(flirtDescr, flirtType));

}

void GUI::guiGenAll() {

        this->srv.generateAll("10");
        this->reloadActivityList(this->srv.getAll(flirtDescr, flirtType));

}

void GUI::guiUndo() {

        this->srv.undo();
        this->reloadActivityList(this->srv.getAll(flirtDescr, flirtType));

}


    /*
    }
    catch (RepoException& re) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
    }
    catch (ValidationException& ve) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
    }
    */










/*//
// Created by Radu on 3/28/2022.
//

#include "menu.h"
#include <iostream>

void help() {
    printf("You can use the following commands, sir:\n"
        "1 for adding\n"
        "2 for updating\n"
        "3 for deleting\n"
        "4 finding an activity\n"
        "5 for filtering\n"
        "6 for sorting\n"
        "! for showing all (filtered and sorted)\n"
        "? for getting help\n"
        "x for exiting\n");
}

void UserInterface::addSubmenu() {
    string ui;
    printf("For adding enter your input in the following format, sir: <name>;<descr>;<type>;<time>\n"
        "You can return by entering '<', sir!\n");
    getline(cin, ui);
    if (ui == "<") {
        return;
    }
    else {
        if (srv.add(ui)) {
            printf("Added with succes, sir!\n");
        }
        else {
            printf("Wrong input or there is already such activity, sir!\n");
        }
    }
}

void UserInterface::updateSubmenu() {
    string ui;
    printf("For updating enter your input in the following format, sir: <name>;<descr>;<type>;<time>\n"
        "You can return by entering '<', sir!\n");
    getline(cin, ui);
    if (ui == "<") {
        return;
    }
    else {
        if (srv.update(ui)) {
            printf("Updated with succes, sir!\n");
        }
        else {
            printf("Wrong input or there was no such activity, sir!\n");
        }
    }
}

void UserInterface::delSubmenu() {
    string ui;
    printf("For deleting enter your input in the following format, sir: <name>\n"
        "You can return by entering '<', sir!\n");
    getline(cin, ui);
    if (ui == "<") {
        return;
    }
    else {
        if (srv.del(ui)) {
            printf("Deleted with succes, sir!\n");
        }
        else {
            printf("Wrong input or there was no such activity, sir!\n");
        }
    }
}

void UserInterface::findSubmenu() {
    string ui;
    printf("For finding enter your input in the following format, sir: <name>\n"
        "You can return by entering '<', sir!\n");
    getline(cin, ui);
    if (ui == "<") {
        return;
    }
    else {
        string toPrint;
        if (srv.findActivity(ui, toPrint)) {
            cout << toPrint;
            printf("Found with succes, sir!\n");
        }
        else {
            printf("Wrong input or there was no such activity, sir!\n");
        }
    }
}

void UserInterface::filterSubmenu() {
    string ui;
    printf("For filtering enter your input in the following format, sir:"
        " <0 for filtering the description field/ 1 for filtering the type field>\n"
        "You can return by entering '<', sir!\n");
    getline(cin, ui);
    if (ui == "<") {
        return;
    }
    else if (ui == "0" || ui == "1") {
        bool field;
        if (ui == "0") {
            field = false;
        }
        else {
            field = true;
        }

        printf("Enter the value to search for in the following format, sir: <value>\n"
            "You can return by entering '<', sir!\n");
        getline(cin, ui);
        if (ui == "<") {
            return;
        }
        else {
            if (field) {
                flirtType = ui;
            }
            else {
                flirtDescr = ui;
            }
        }
    }
    else {
        printf("Wrong input, sir!");
        return;
    }
    printf("Filtered with succes, sir!\n");
}

void UserInterface::sortSubmenu() {
    string ui;
    printf("For sorting enter your input in the following format, sir:"
        " <asc for ascending order/ desc for descending order>\n"
        "You can return by entering '<', sir!\n");
    getline(cin, ui);
    if (ui == "<") {
        return;
    }
    else if (ui == "asc" || ui == "desc") {
        string order = ui;

        printf("Enter the field to sort for in the following format, sir: <name/ description/ type/ duration>\n"
            "You can return by entering '<', sir!\n");
        getline(cin, ui);
        if (ui == "name" || ui == "description" || ui == "type" || ui == "duration") {
            const string& field = ui;
            srv.sort(order, field);
        }
        else {
            printf("Wrong input, sir!");
            return;
        }
    }
    else {
        printf("Wrong input, sir!");
        return;
    }
    printf("Sorted with succes, sir!\n");
}

void UserInterface::delAllSubmenu() {
    srv.delAll();
    printf("Deleted all instances with succes, sir!\n");
}

void UserInterface::generateByNameSubmenu() {
    string ui;
    printf("For generating by name enter your input in the following format, sir: <name>\n"
        "You can return by entering '<', sir!\n");
    getline(cin, ui);
    if (ui == "<") {
        return;
    }
    else {
        if (srv.generateByName(ui)) {
            printf("Generated by name with succes, sir!\n");
        }
        else {
            printf("Wrong input, sir!\n");
        }
    }
}

void UserInterface::generateAllSubmenu() {
    string ui;
    printf("For generating all enter your input in the following format, sir: <number of new activities>\n"
        "You can return by entering '<', sir!\n");
    getline(cin, ui);
    if (ui == "<") {
        return;
    }
    else {
        if (srv.generateAll(ui)) {
            printf("Generated all with succes, sir!\n");
        }
        else {
            printf("Wrong input, sir!\n");
        }
    }
}

void UserInterface::reportTypesSubmenu() {
    unordered_map <string, ReportItem> toPrint = srv.reportTypes();
    for (auto& instance : toPrint) {
        instance.second.display();
    }
}

void UserInterface::undoSubmenu() {
    srv.undo();
}

void UserInterface::showAll() {
    int i;
    vector <Activity> toPrintV = srv.getAll(flirtDescr, flirtType);
    string toPrintLine;
    for (i = 0; i < toPrintV.size(); ++i) {
        toPrintV[i].activityToLine(toPrintLine);
        cout << toPrintLine;
    }
}

UserInterface::UserInterface(ActivityService& srv) : srv(srv) {
    flirtType = flirtDescr = "";
    string ui;
    printf("Welcome, sir! ");
    for (; true;) {
        printf("You are in the main menu. Enter your command, sir!\n");
        getline(cin, ui);
        if (ui == "1") {
            addSubmenu();
        }
        else if (ui == "2") {
            updateSubmenu();
        }
        else if (ui == "3") {
            delSubmenu();
        }
        else if (ui == "4") {
            findSubmenu();
        }
        else if (ui == "5") {
            filterSubmenu();
        }
        else if (ui == "6") {
            sortSubmenu();
        }
        else if (ui == "7") {
            delAllSubmenu();
        }
        else if (ui == "8") {
            generateByNameSubmenu();
        }
        else if (ui == "9") {
            generateAllSubmenu();
        }
        else if (ui == "0") {
            reportTypesSubmenu();
        }
        else if (ui == "<") {
            undoSubmenu();
        }
        else if (ui == "!") {
            showAll();
        }
        else if (ui == "?") {
            help();
        }
        else if (ui == "x") {
            break;
        }
        else {
            printf("Wrong input, sir! Double check your input doesn't have any spaces or any other characters, sir!\n");
            help();
        }
    }
}*/