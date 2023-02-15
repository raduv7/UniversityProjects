
#include "Gui.h"
void GUI::initializeGUIComponents() {

    QHBoxLayout* lyMain = new QHBoxLayout;
    this->setLayout(lyMain);

    // left

    QWidget* left = new QWidget;
    QVBoxLayout* lyLeft = new QVBoxLayout;
    left->setLayout(lyLeft);

    

    btnSortModel = new QPushButton("Sort after model, sir!");
    btnSortPrice = new QPushButton("Sort after price, sir!");
    btnUnsort = new QPushButton("Back to unsorted, sir!");

    lyLeft->addWidget(btnSortModel);
    lyLeft->addWidget(btnSortPrice);
    lyLeft->addWidget(btnUnsort);

    editType = new QLineEdit;
    lyLeft->addWidget(editType);
    editModel = new QLineEdit;
    lyLeft->addWidget(editModel);
    editColor = new QLineEdit;
    lyLeft->addWidget(editColor);
    editYear = new QLineEdit;
    lyLeft->addWidget(editYear);
    editPrice = new QLineEdit;
    lyLeft->addWidget(editPrice);
    


    // right

    QWidget* right = new QWidget;
    QVBoxLayout* lyRight = new QVBoxLayout;
    right->setLayout(lyRight);

    int noLines = 8;
    int noColumns = 3;
    this->tableDevs = new QTableWidget{ noLines, noColumns };

    QStringList devHeaderList;
    devHeaderList << "Model" << "Culoare" << "Pret";
    this->tableDevs->setHorizontalHeaderLabels(devHeaderList);

    this->tableDevs->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


    lyRight->addWidget(tableDevs);

    lyMain->addWidget(left);
    lyMain->addWidget(right);
}

void GUI::connectSignalsSlots() {
    QObject::connect(btnSortModel, &QPushButton::clicked, this, &GUI::guiSortModel);
    QObject::connect(btnSortPrice, &QPushButton::clicked, this, &GUI::guiSortPrice);
    QObject::connect(btnUnsort, &QPushButton::clicked, this, &GUI::guiUnsort);

    QObject::connect(tableDevs, &QTableWidget::itemSelectionChanged, [&]() {
        auto selected = tableDevs->selectedItems();
        if (selected.isEmpty()) {
            devSelected = false;
        }
        else {
            devSelected = true;
            auto item = selected.at(0);
            selModel = item->data(0).toString().toStdString();
            Device dev = srv.getOnly(selModel);
            editType->setText(QString::fromStdString(dev.getType()));
            editModel->setText(QString::fromStdString(dev.getModel()));
            editColor->setText(QString::fromStdString(dev.getColor()));
            editYear->setText(QString::fromStdString(to_string(dev.getYear())));
            editPrice->setText(QString::fromStdString(to_string(dev.getPrice())));
        }
        });

}

void GUI::reloadList(vector <Device> v) {

    this->tableDevs->clearContents();
    this->tableDevs->setRowCount(v.size());

    int lineNumber = 0;

    for (auto& act : v)  {
        this->tableDevs->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(act.getModel())));
        this->tableDevs->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(act.getColor())));
        this->tableDevs->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(to_string(act.getPrice()))));
        
        //this->tableDevs->item->setBackgroundColor();
        lineNumber++;
    }
}

void GUI::guiSortModel() {
    reloadList(srv.getSortedModel());
}

void GUI::guiSortPrice() {
    reloadList(srv.getSortedPrice());
}

void GUI::guiUnsort() {
    reloadList(srv.getAll());
}