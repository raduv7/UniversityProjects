#pragma once
#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>
#include <QTableWidget>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>
#include <QHeaderView>
#include <QMessageBox>
#include <iostream>
#include "Service.h"

class GUI : public QWidget {
private:
	Service srv;
	bool devSelected;
	string selType, selModel, selColor;
	int selYear, selPrice;

	QPushButton* btnRemove;
	QTableWidget* tableDevs;


	QPushButton* btnSortModel;
	QPushButton* btnSortPrice;
	QPushButton* btnUnsort;
	
	QLineEdit* editType;
	QLineEdit* editModel;
	QLineEdit* editColor;
	QLineEdit* editYear;
	QLineEdit* editPrice;


	void initializeGUIComponents();
	void connectSignalsSlots();

	void reloadList(vector <Device> v);
	void guiSortModel();
	void guiSortPrice();
	void guiUnsort();
public:
	GUI(Service newSrv) : srv(newSrv) {
		initializeGUIComponents();
		connectSignalsSlots();
		reloadList(srv.getAll());
		devSelected = false;
	};
};