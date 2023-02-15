#pragma once
#include "service.h"
#include "observer.h"
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


class Gui : public QWidget, public Observer {
private:
	Service* srv;
	bool sel = false;
	int selG = -1;
	Game g;

	///QLabel* lblDim;
	///QLabel* lblSquares;
	///QLabel* lblPlayer;
	QLineEdit*editDim;
	QLineEdit*editSquares;
	QLineEdit*editPlayer;
	QPushButton* buttAdd;

	QTableWidget*table;
	QPushButton* buttOpen;

	QLineEdit* updDim;
	QLineEdit* updSquares;
	QLineEdit* updPlayer;
	QLineEdit* updStage;
	QPushButton* buttAct;

	void initGuiComp();
	void connectSignalSlot();
	void reloadData(vector <Game> v);
public:
	void update();
	Gui(Service* nsrv) : srv(nsrv) {
		srv->addObs(this);
		initGuiComp();
		connectSignalSlot();
		reloadData(srv->getAll());
	}
};

class GameGui : public QWidget, public Observer {
private:
	Game*myg;
	QPushButton* buttSq[5][5];
	QLineEdit* editDim;
	void initGuiComp();
	void connectSignalSlot();
	void reloadData();
public:
	void update();
	GameGui(Game* nmyg) : myg(nmyg) {
		initGuiComp();
	}
};
