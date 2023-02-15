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
	Service* srv;
	int lastId;

	QLabel* lblName;
	QLabel* lblWriter;
	QLabel* lblGenre;
	QLineEdit* editName;
	QLineEdit* editWriter;
	QLineEdit* editGenre;

	QPushButton* buttAdd;
	QPushButton* buttDel;

	QTableWidget*tbl1;

	QTableView* tbl;

	void reloadTable();
	void reloadTbl1();

	void initGuiComps();
	void connectSignalSlots();
	void connectSignalSlotsForTable();

	void paintEvent(QPaintEvent*) override;
public:
	Gui(Service* newSrv) : srv(newSrv) {
		srv->addObs(this);
		initGuiComps();
		connectSignalSlots();
		update();
	}
	~Gui() {
		srv->delObs(this);
	}

	void update();
};

class MyTable : public QAbstractTableModel {
private:
	Service* srv;
public:
	MyTable(Service* nsrv, QObject* parent = NULL) : srv(nsrv) { }

	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
	int columnCount(const QModelIndex& parent = QModelIndex{}) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};