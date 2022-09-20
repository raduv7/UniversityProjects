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

class GUI : public QWidget {
private:
	Service*srv;

	QPushButton* btnAdd;
	QPushButton* btnDel;
	QPushButton* btnOpenCrud;
	QPushButton* btnOpenReadOnly;

	QLineEdit* editName;
	QLineEdit* editType;
	QLineEdit* editDescr;

	void initGuiComp();
	void connectSigns();
public:
	GUI(Service*newSrv) : srv(newSrv) {
		initGuiComp();
		connectSigns();
	}
	~GUI() = default;
};

class MyQTableModel : public QAbstractTableModel {
private:
	Service*srv;
public:
	MyQTableModel(Service* newSrv, QObject* parent = NULL) : srv(newSrv) { }

	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
	int columnCount(const QModelIndex& parent = QModelIndex{}) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

class WindowCrud : public QWidget, public Observer {
private:
	Service*srv;

	QTableWidget* tblBundle;

	QTableView* myTblBundle;

	QPushButton* btnClear;
	QPushButton* btnGenerate;

	void initWCrudComp();
	void connectWCrudSigns();
	void reloadWCrudTable(vector <BundleElement> v);

	void setupMyTbl(Service*newSrv);
	void reloadMyTbl();
public:
	void update();
	WindowCrud(Service*newSrv) : srv(newSrv) {
		initWCrudComp();
		connectWCrudSigns();
		reloadWCrudTable(srv->getAll());
	}
};

class WindowReadOnly : public QWidget, public Observer {
private:
	Service* srv;
	void initWReadOnlyComp();
	void connectWReadOnlySigns();
	void paintEvent(QPaintEvent*) override;
public:
	void update();
	WindowReadOnly(Service* newSrv) : srv(newSrv) {
		initWReadOnlyComp();
		connectWReadOnlySigns();
		update();
	}
};