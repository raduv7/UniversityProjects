#include "gui.h"

void Gui::reloadTable() {
    MyTable* myNewModel = new MyTable(srv, flirtType);
    tbl->setModel(myNewModel);
    tbl->resizeColumnsToContents();
}

void Gui::reloadComboBox() {
    vector<string> types(srv->getTypes());
    string beforeText = boxy->currentText().toStdString();
    if (boxy->currentIndex() == -1) {
        beforeText = "radu7;radu7";
        // QMessageBox::information(this, "Sir!", "Sir, we got them!\n");
    }
    boxy->clear();
    for (auto type : types) {
        boxy->addItem(QString::fromStdString(type));
        if (type == beforeText) {
            boxy->setCurrentIndex(boxy->count() - 1);
        }
    }
    if (beforeText == "radu7;radu7") {
        boxy->setCurrentIndex(- 1);
    }
}

void Gui::openWtfs() {
    vector<string> types(srv->getTypes());
    WindowForType* newWtf;
    for (auto type : types) {
        newWtf = new WindowForType(srv, type);
        newWtf->show();
    }
}

void Gui::initGuiComps() {
    QHBoxLayout* lyMain = new QHBoxLayout;
    setLayout(lyMain);


    QVBoxLayout* lyLeft = new QVBoxLayout;

    lblId = new QLabel("Sir, the id:");
    editId = new QLineEdit;
    lyLeft->addWidget(lblId);
    lyLeft->addWidget(editId);

    lblPrice = new QLabel("Sir, the price:");
    editPrice = new QLineEdit;
    lyLeft->addWidget(lblPrice);
    lyLeft->addWidget(editPrice);

    lblName = new QLabel("Sir, the name:");
    editName = new QLineEdit;
    lyLeft->addWidget(lblName);
    lyLeft->addWidget(editName);

    lblType = new QLabel("Sir, the type:");
    editType = new QLineEdit;
    lyLeft->addWidget(lblType);
    lyLeft->addWidget(editType);

    buttAdd = new QPushButton("\nSir, order to add!\n");
    lyLeft->addWidget(buttAdd);

    lyMain->addLayout(lyLeft);


    QVBoxLayout* lyMid = new QVBoxLayout;

    boxy = new QComboBox;
    lyMid->addWidget(boxy);

    lyMain->addLayout(lyMid);


    QVBoxLayout* lyRight = new QVBoxLayout;

    tbl = new QTableView;
    lyRight->addWidget(tbl);

    lyMain->addLayout(lyRight);
}

void Gui::connectSignalSlots() {
    QObject::connect(buttAdd, &QPushButton::clicked, this, [&]() {
        string fields[4];
        fields[0] = editId->text().toStdString();
        fields[1] = editPrice->text().toStdString();
        fields[2] = editName->text().toStdString();
        fields[3] = editType->text().toStdString();
        string ret = srv->add(fields);
        if (ret.empty()) {
            QMessageBox::information(this, "Sir!\n", "\nSir, your order was executed successfully!\n");
        }
        else {
            QMessageBox::information(this, "Sir, bad news!\n", QString::fromStdString(ret));
        }
        });
    QObject::connect(boxy, &QComboBox::currentIndexChanged, this, [&]() {
        flirtType = boxy->currentText().toStdString();
        reloadTable();
        });
}

void Gui::update(int reqId) {
    if (reqId == 7) {
        reloadTable();
        reloadComboBox();
    }
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
    Prod* prod = this->srv->getAll()[row];

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
            return QString::fromStdString(prod->getName());
        case 3:
            return QString::fromStdString(prod->getType());
        case 4:
            return QString::fromStdString(to_string(srv->countType(prod->getType()) - 1));
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
        if (prod->getType() == flirtType)
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
                return QString{ "Name" };
            case 3:
                return QString{ "Type" };
            case 4:
                return QString{ "Same type" };
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

void WindowForType::initWtfComps() {
    resize(256,256);
    setWindowTitle(QString::fromStdString(type));
}

void WindowForType::connectSignalSlots() {
    QObject::connect(this, &QWidget::focusPolicy, this, [&]() { return; });
}

void WindowForType::focusInEvent(QFocusEvent*ev) {
    QMessageBox::information(this,"Sir!","Sir, focudes in!\n");
}
void WindowForType::focusOutEvent(QFocusEvent*ev) {
    QMessageBox::information(this, "Sir!", "Sir, focudes out!\n");
}

void WindowForType::paintEvent(QPaintEvent*ev) {
    if (lastNoc == srv->countType(type)) {
        QPainter p(this);
        int i;
        for (i = 0; i < xx.size(); ++ i) {
            p.drawEllipse(xx[i], yy[i], 20, 20);
        }
        return;
    }
    lastNoc = srv->countType(type);
    xx.clear();
    yy.clear();
    QPainter p(this);
    // QMessageBox::information(this, "Sir", "Sir, req executed!\n");

    int i, j, noc = srv->countType(type);
    int x, y;

    for (i = 0; i < noc; ++ i) {
        for(; true;) {
            bool found;
            x = rand() % 231 + 3;
            y = rand() % 231 + 3;
            for (j = 0, found = false; j < xx.size(); ++j) {
                if (xx[j] == x && yy[j] == y) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                break;
            }
        }
        xx.push_back(x);
        yy.push_back(y);
        p.drawEllipse(x, y, 20, 20);
    }
}

void WindowForType::update(int reqId) {
    if (reqId == 7) {
        //QMessageBox::information(this, "Sir", "Sir, req executed!\n");
        repaint();
    }
    else {
        //QMessageBox::information(this, "Sir", "Sir, req declined!\n");
    }
}