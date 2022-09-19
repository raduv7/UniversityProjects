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

class WindowForType : public QWidget, public Observer {
private:
	Service* srv;
	string type;

	QLabel* lblCounter;

	void initComps();
public:
	WindowForType(Service* nsrv, string ntype) : srv(nsrv), type(ntype) {
		srv->addOb(this);
		initComps();
	}
	~WindowForType() {
		srv->delOb(this);
	}

	void update();
};

class Gui : public QWidget, public Observer {
private:
	Service* srv;
	vector<WindowForType*> winds;

	QLineEdit* editId;
	QLineEdit* editPrice;
	QLineEdit* editType;
	QLineEdit* editName;
	QPushButton* buttAdd;
	QLabel* lblId;
	QLabel* lblPrice;
	QLabel* lblType;
	QLabel* lblName;

	QSlider*sldr;

	QTableView* myTbl;

	void reloadMyTable(int nmaxPrice = 100);
	void initGuiComps();
	void connectSignalSlots();
public:
	Gui(Service* nsrv) : srv(nsrv) { 
		initGuiComps();
		connectSignalSlots();

		vector<string> types(srv->getAllTypes());

		for (auto type : types) {
			WindowForType*nwind = new WindowForType(srv, type);
			winds.push_back(nwind);
			nwind->show();
		}
		srv->addOb(this);
	};
	~Gui() {
		srv->delOb(this);
		for (auto wind : winds) {
			delete wind;
		}
	}

	void update();
};


class MyTable : public QAbstractTableModel {
private:
	Service* srv;
	int maxPrice;
public:
	MyTable(Service* nsrv, int nmaxPrice, QObject* parent = NULL) : srv(nsrv), maxPrice(nmaxPrice) { }

	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
	int columnCount(const QModelIndex& parent = QModelIndex{}) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};
