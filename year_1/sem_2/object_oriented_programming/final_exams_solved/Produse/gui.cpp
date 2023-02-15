#include "gui.h"

void Gui::reloadMyTable(int nmaxPrice) {
    MyTable* myModel = new MyTable{ srv, nmaxPrice };
    myTbl->setModel(myModel);
    myTbl->resizeColumnsToContents();
}

void Gui::initGuiComps() {
    resize(1024, 512);
    QHBoxLayout* lyMain = new QHBoxLayout;
    setLayout(lyMain);



    QVBoxLayout*lyLeft = new QVBoxLayout;

    lblId = new QLabel("Sir, the id:");
    editId = new QLineEdit();
    lyLeft->addWidget(lblId);
    lyLeft->addWidget(editId);
    
    lblPrice = new QLabel("Sir, the price:");
    editPrice = new QLineEdit();
    lyLeft->addWidget(lblPrice);
    lyLeft->addWidget(editPrice);
    
    lblType = new QLabel("Sir, the type:");
    editType = new QLineEdit();
    lyLeft->addWidget(lblType);
    lyLeft->addWidget(editType);
    
    lblName = new QLabel("Sir, the name:");
    editName = new QLineEdit();
    lyLeft->addWidget(lblName);
    lyLeft->addWidget(editName);

    buttAdd = new QPushButton("Sir, order to add!");
    lyLeft->addWidget(buttAdd);

    sldr = new QSlider();
    sldr->setMinimum(1);
    sldr->setMaximum(100);
    sldr->setValue(100);
    sldr->setOrientation(Qt::Horizontal);
    lyLeft->addWidget(sldr);

    lyMain->addLayout(lyLeft);



    QVBoxLayout* lyRight = new QVBoxLayout;

    myTbl = new QTableView;
    lyRight->addWidget(myTbl);

    lyMain->addLayout(lyRight);

    reloadMyTable();
}

void Gui::connectSignalSlots() {
    QObject::connect(sldr, &QSlider::valueChanged, this, [&]() { 
        //QMessageBox::information(this, "Sire, titlu", QString::fromStdString(to_string(sldr->value())));
        reloadMyTable(sldr->value());
        });

    QObject::connect(buttAdd, &QPushButton::clicked, this, [&]() {
        string fields[4];
        fields[0] = editId->text().toStdString();
        fields[1] = editPrice->text().toStdString();
        fields[2] = editType->text().toStdString();
        fields[3] = editName->text().toStdString();
        string addErr = srv->addProd(fields);
        if (addErr.empty()) {
            QMessageBox::information(this, "Sir, congrats!", "Sir, your order was executed!");
        }
        else {
            QMessageBox::information(this, "Sir, bad news!", QString::fromStdString(addErr));
        }
        });
}

void Gui::update() {
    reloadMyTable();
}

int MyTable::rowCount(const QModelIndex& parent) const {
    return srv->getAll().size();
}
int MyTable::columnCount(const QModelIndex& parent) const {
    return 5;
}
QVariant MyTable::data(const QModelIndex& index, int role) const {
    int row = index.row();
    int column = index.column();

    if (row >= this->srv->getAll().size())
    {
        return QVariant();
    }
    Product*prod = this->srv->getAll()[row];

    if (role == Qt::UserRole) {
        return QString::fromStdString(to_string(prod->getId()));
    }
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (column)
        {
        case 0:
            return QString::fromStdString(to_string(prod->getId()));
        case 1:
            return QString::fromStdString(to_string(prod->getPrice()));
        case 2:
            return QString::fromStdString(prod->getType());
        case 3:
            return QString::fromStdString(prod->getName());
        case 4:
            return QString::fromStdString(to_string(prod->getVowelsNr()));
        default:
            break;
        }
    }
    if (role == Qt::FontRole)
    {
        QFont font("Calibri", 14, QFont::Normal, false);
        return font;
    }
    if (role == Qt::BackgroundRole)
    {
        if (prod->getPrice() <= maxPrice)
        {
            return QBrush{ QColor{"red"} };
        }
        else
        {
            return QBrush{ QColor {81, 144, 256} };
        }
    }
    return QVariant();
}
QVariant MyTable::headerData(int section, Qt::Orientation orientation, int role) const {

    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
                return QString{ "Id" };
            case 1:
                return QString{ "Price" };
            case 2:
                return QString{ "Type" };
            case 3:
                return QString{ "Name" };
            case 4:
                return QString{ "Nr of vowels" };
            default:
                break;
            }
        }
    }
    if (role == Qt::FontRole)
    {
        QFont font("Calibri", 18, QFont::Bold, false);
        return font;
    }

    return QVariant{};
}


void WindowForType::initComps() {
    setWindowTitle(QString::fromStdString(type));

    QVBoxLayout* lyMain = new QVBoxLayout;
    setLayout(lyMain);

    string lblCounterStr = "Sir, there are ";
    lblCounterStr += to_string(srv->prodCounter(type));
    lblCounterStr += " products of this type!";
    lblCounter = new QLabel(QString::fromStdString(lblCounterStr));

    lyMain->addWidget(lblCounter);
}

void WindowForType::update() {
    string lblCounterStr = "Sir, there are ";
    lblCounterStr += to_string(srv->prodCounter(type));
    lblCounterStr += " products of this type!";
    lblCounter->setText(QString::fromStdString(lblCounterStr));
}