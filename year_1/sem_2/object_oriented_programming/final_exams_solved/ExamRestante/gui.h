#pragma once
#include "service.h"
#include <cstdlib>
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
#include <QComboBox>

class Gui : public QWidget, public Observer {
private:
	Service* srv;
	string flirtType;

	QLabel* lblId;
	QLabel* lblPrice;
	QLabel* lblName;
	QLabel* lblType;

	QLineEdit* editId;
	QLineEdit* editPrice;
	QLineEdit* editName;
	QLineEdit* editType;

	QPushButton* buttAdd;

	QComboBox* boxy;

	QTableView* tbl;

	void reloadTable();
	void reloadComboBox();
	void openWtfs();
	void initGuiComps();
	void connectSignalSlots();
public:
	Gui(Service* newSrv) : srv(newSrv) {
		srv->addObs(this);
		flirtType = "radu7;radu7";
		initGuiComps();
		connectSignalSlots();
		reloadTable();
		reloadComboBox();
		openWtfs();
	}
	~Gui() {
		srv->delObs(this);
	}

	void update(int reqId = 0);
};

class MyTable : public QAbstractTableModel {
private:
	Service* srv;
	string flirtType;
public:
	MyTable(Service* nsrv, const string&newFlirtType, QObject* parent = NULL) : srv(nsrv), flirtType(newFlirtType) { }

	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
	int columnCount(const QModelIndex& parent = QModelIndex{}) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

class WindowForType : public QWidget, public Observer {
private:
	Service* srv;
	string type;
	int lastNoc;
	vector<int> xx, yy;

	void initWtfComps();
	void connectSignalSlots();
	void paintEvent(QPaintEvent*) override;
	void focusInEvent(QFocusEvent*) override;
	void focusOutEvent(QFocusEvent*) override;
public:
	WindowForType(Service* newSrv, string newType) : srv(newSrv), type(newType) { 
		srv->addObs(this);
		lastNoc = 0;
		initWtfComps();
	}
	~WindowForType() {
		srv->delObs(this);
	}

	void update(int reqId = 0);
};