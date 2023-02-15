#pragma once
#include "service.h"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>
#include <QTableWidget>
#include <QListWidget>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QGroupBox>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>
#include <QHeaderView>
#include <QMessageBox>
#include <QWindow>
#include <QGridLayout>
#include <QWidget>
#include <QTableWidget>
#include <QDebug>
#include <QPainter>


class Gui : public QWidget, public Observer {
private:
	Service*srv;
	string programmer = "";

	QLabel* lblMyProgrammer;
	QLineEdit*editMyProgrammer;

	QLabel* lblAdd;
	QLineEdit* editAddId;
	QLineEdit* editAddDescr;
	QLineEdit* editAddState;
	QLineEdit* editAddProgrammers;
	QPushButton* buttAdd;

	QTableView* myTbl;

	void initComps();
	void connectSignalSlots();
	void reloadMyTable();
	void createWindowsForStates();
public:
	Gui(Service* nsrv) : srv(nsrv) {
		srv->addObserver(this);
		initComps();
		connectSignalSlots();
		createWindowsForStates();
	}
	~Gui() {
		srv->delObserver(this);
	}

	void update() override;
};

class WindowForState : public QWidget, public Observer {
private:
	int stateCode;
	int lastId = -1;
	Service* srv;

	string statesStr[3] = { "open", "inprogress", "closed" };


	QPushButton* buttState0;
	QPushButton* buttState1;
	QPushButton* buttState2;
	QTableView* myTbl;

	void initComps();
	void connectSignalSlots();
	void connectSignalSlotsForTable();
	void reloadMyTable();
	void setTaskState(int updateTaskId, string nstate);
public:
	WindowForState(Service* nsrv, const int nstateCode) : srv(nsrv), stateCode(nstateCode) { 
		srv->addObserver(this);
		initComps();
		connectSignalSlots();
	}
	~WindowForState() {
		srv->delObserver(this);
	}

	void update();
};

class MyTable : public QAbstractTableModel {
private:
	Service* srv;
	string programmer = "";
	int stateCode = -1;
public:
	MyTable(Service* nsrv, const int nstateCode, QObject* parent = NULL) : srv(nsrv), stateCode(nstateCode) { }
	MyTable(Service* nsrv, const string nprogrammer, QObject* parent = NULL) : srv(nsrv), programmer(nprogrammer) { }

	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
	int columnCount(const QModelIndex& parent = QModelIndex{}) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	int lastSelectedId() const;
	vector<Task> getAll() const;
};