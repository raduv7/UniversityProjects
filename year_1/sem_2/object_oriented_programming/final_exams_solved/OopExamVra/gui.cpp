#include "gui.h"


void Gui::update() {
	reloadData(srv->getAll());
}

void Gui::initGuiComp() {
	QHBoxLayout*lyMain = new QHBoxLayout;
	this->setLayout(lyMain);

	//left
	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	///lblDim = new QLabel("dim");
	///lyLeft->addWidget(lblDim);
	editDim = new QLineEdit;
	lyLeft->addWidget(editDim);
	///lblSquares = new QLabel("squares");
	///lyLeft->addWidget(lblDim);
	editSquares = new QLineEdit;
	lyLeft->addWidget(editSquares);
	///lblPlayer = new QLabel("player");
	///lyLeft->addWidget(lblDim);
	editPlayer = new QLineEdit;
	lyLeft->addWidget(editPlayer);

	buttAdd = new QPushButton("Add new game, sir!");
	lyLeft->addWidget(buttAdd);


	//middle
	QWidget* mid= new QWidget;
	QVBoxLayout* lyMid= new QVBoxLayout;
	mid->setLayout(lyMid);
	int nlin = 10;
	int ncol = 5;
	table = new QTableWidget{ nlin, ncol };
	QStringList tableHeader;
	tableHeader << "Id" << "Dim" << "Squares" << "CurrentPlayer" << "Stage";
	table->setHorizontalHeaderLabels(tableHeader);
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	lyMid->addWidget(table);

	buttOpen = new QPushButton("Open game, sir!");
	lyMid->addWidget(buttOpen);


	//right
	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	updDim = new QLineEdit;
	lyRight->addWidget(updDim);
	updSquares = new QLineEdit;
	lyRight->addWidget(updSquares);
	updPlayer = new QLineEdit;
	lyRight->addWidget(updPlayer);
	updStage = new QLineEdit;
	lyRight->addWidget(updStage);

	buttAct = new QPushButton("Update game, sir!");
	lyRight->addWidget(buttAct);

	lyMain->addWidget(left);
	lyMain->addWidget(mid);
	lyMain->addWidget(right);
}

void Gui::connectSignalSlot() {
	QObject::connect(buttAdd, &QPushButton::clicked, this, [&]() {
		srv->add(editDim->text().toStdString(), editSquares->text().toStdString(), editPlayer->text().toStdString());

		});
	QObject::connect(buttOpen, &QPushButton::clicked, this, [&]() {
		GameGui* gameguy = new GameGui{&g};
		srv->addObs(gameguy);
		gameguy->show();
		});
	QObject::connect(buttAct, &QPushButton::clicked, this, [&]() {
		srv->act(g.getId(), updDim->text().toStdString(), updSquares->text().toStdString(), updPlayer->text().toStdString(), updStage->text().toStdString());

		});
	QObject::connect(table, &QTableWidget::itemSelectionChanged, [&]() {
		auto selected = table->selectedItems();
		if (selected.isEmpty()) {
			sel = false;
		}
		else {
			sel = true;
			auto item = selected.at(0);
			try {
				selG = stoi(item->data(0).toString().toStdString());
			}
			catch (...) {
				;
			}
			//QMessageBox::information(this, "Info", item->data(0).toString());
			g = ( * srv )[selG];
			updDim->setText(QString::fromStdString(to_string(g.getDim())));
			updSquares->setText(QString::fromStdString(g.getSquares()));
			string player = "";
			player += g.getPlayer();
			updPlayer->setText(QString::fromStdString(player));
			updStage->setText(QString::fromStdString(g.getStg()));
		}
		});
}

void Gui::reloadData(vector <Game> v) {
	table->clearContents();
	table->setRowCount(v.size());

	int i;
	i = 0;
	for (auto g : v) {
		table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(to_string(g.getId()))));
		table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(to_string(g.getDim()))));
		table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(g.getSquares())));
		string player = "";
		player += g.getPlayer();
		table->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(player)));
		table->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(g.getStg())));
		++i;
	}
	table->resizeColumnsToContents();
}

void GameGui::initGuiComp() {
	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);
	//editDim = new QLineEdit;
	//lyMain->addWidget(editDim);
	int i,j, dim  = myg->getDim();
	for (i = 0; i < dim; ++i) {
		for (j = 0; j < myg->getDim(); ++j) {
			string butstr = "";
			butstr += myg->getSquares()[i * dim + j];
			buttSq[i][j] = new QPushButton(QString::fromStdString(butstr));
			lyMain->addWidget(buttSq[i][j]);
		}
	}
}

void GameGui::connectSignalSlot() {
	;
}

void GameGui::update() {
	reloadData();
}

void GameGui::reloadData() {
}