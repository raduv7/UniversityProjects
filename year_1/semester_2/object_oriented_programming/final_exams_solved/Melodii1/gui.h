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

	QLabel* lblRank;
	QLabel* lblName;
	QSlider* editRank;
	QLineEdit* editName;

	QPushButton* buttUpd;
	QPushButton* buttDel;

	QTableView* tbl;
	QWidget*widgetPainter;

	void initGuiComps();
	void connectSignalSlots();
	void connectSignalSlotsForMyTbl();
	void reloadMyTable();
public:
	Gui(Service*newSrv) : srv(newSrv), lastId(-1) {
		initGuiComps();
		connectSignalSlots();

		srv->addObs(this);
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

	int getLastId() const;
};

class WidgetPaintsRanks : public QWidget, public Observer {
private:
	Service* srv;
	void paintEvent(QPaintEvent*) override;
public:
	WidgetPaintsRanks(Service* newSrv, QWidget*parent = nullptr) : srv(newSrv), QWidget(parent) {
		srv->addObs(this);
		update();
	}
	~WidgetPaintsRanks() {
		srv->delObs(this);
	}
	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;
	void update();
};