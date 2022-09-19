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
#include <QMouseEvent>

class WindowForPaint;

class Gui : public QWidget, public Observer {
private:
	Service* srv;
	string flirtType;

	QLabel*lblId;
	QLabel*lblWheels;
	QLabel*lblName;
	QLabel*lblType;
	QLineEdit* editId;
	QLineEdit* editWheels;
	QLineEdit* editName;
	QLineEdit* editType;

	QPushButton*buttAdd;

	QComboBox*boxy;

	QTableView*tbl;

	WindowForPaint* vip;

	void initGuiComps();
	void connectSignalSlots();
	void connectSignalSlotsTbl();
	void reloadTable();
	void reloadComboBox();
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
	string flirtType;
public:
	MyTable(Service* nsrv, string newFlirtType, QObject* parent = NULL) : srv(nsrv), flirtType(newFlirtType) { }

	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
	int columnCount(const QModelIndex& parent = QModelIndex{}) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

class WindowForPaint : public QWidget, public Observer {
private:
	Tractor* car;
	Service* srv;

	void paintEvent(QPaintEvent*) override;

	static bool inDist(QPoint qp, int x, int y);
	void mousePressEvent(QMouseEvent*ev) override;
public:
	WindowForPaint(Service*newSrv) : car(NULL), srv(newSrv) {
		srv->addObs(this);
	}
	~WindowForPaint() {
		srv->delObs(this);
	}

	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;

	void setCar(Tractor* newCar);
	void update();
};