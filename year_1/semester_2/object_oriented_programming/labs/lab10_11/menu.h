#pragma once

#include <QtWidgets/QMainWindow>
#include "activityService.h"
#include <QTableWidget>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QGroupBox>

class GUI : public QWidget {
public:
	GUI(ActivityService& srv);
private:

	ActivityService srv;
	string flirtDescr, flirtType;


	QLabel* lblTitlu = new QLabel{ "Nume activitate:" };
	QLabel* lblGen = new QLabel{ "Descriere activitate:" };
	QLabel* lblArtist = new QLabel{ "Tip activitate:" };
	QLabel* lblDurata = new QLabel{ "Durata activitate:" };

	QLineEdit* editTitlu;
	QLineEdit* editArtist;
	QLineEdit* editGen;
	QLineEdit* editDurata;

	QPushButton* btnAddSong;
	QPushButton* btnActSong;
	QPushButton* btnDelSong;
	QPushButton* btnFndSong;

	QGroupBox* groupBox = new QGroupBox(tr("Sorting options:"));

	QRadioButton* radioSrtArtistTitlu = new QRadioButton(QString::fromStdString("Descriere"));
	QRadioButton* radioSrtDurata = new QRadioButton(QString::fromStdString("Durata"));
	QPushButton* btnSortSongs;

	QLabel* lblFilterCriteriaType = new QLabel{ "Filtering type:" };
	QLineEdit* editFilterType;
	QLabel* lblFilterCriteriaDescr = new QLabel{ "Filtering description:" };
	QLineEdit* editFilterDescr;
	QPushButton* btnFilterSongs;

	QPushButton* btnDelAllData;
	QPushButton* btnGenAllData;
	QPushButton* btnUndo;
	QPushButton* btnReloadData;

	QTableWidget* tableSongs;

    void initializeGUIComponents();

    void connectSignalsSlots();

	void guiAdd();
	void guiAct();
	void guiDel();
	void guiFnd();

	void guiDelAll();
	void guiGenAll();
	void guiUndo();
    void reloadActivityList(vector<Activity> acts);

    void addSubmenu();
    void updateSubmenu();
    void delSubmenu();
    void findSubmenu();
    void filterSubmenu();
    void sortSubmenu();
    void delAllSubmenu();
    void generateByNameSubmenu();
    void generateAllSubmenu();
    void reportTypesSubmenu();
    void undoSubmenu();
    void showAll();
};