#include "gui.h"

void Gui::reloadTable() {
    MyTable* tblModel = new MyTable(srv, flirtType);
    tbl->setModel(tblModel);
    tbl->resizeColumnsToContents();
    connectSignalSlotsTbl();
}

void Gui::reloadComboBox() {
    vector<string> types(srv->getTypes());
    string typeBefore = boxy->currentText().toStdString();
    boxy->clear();
    for (auto type : types) {
        boxy->addItem(QString::fromStdString(type));
        if (type == typeBefore) {
            boxy->setCurrentIndex(boxy->count() - 1);
        }
    }
}

void Gui::update() {
    reloadTable();
    reloadComboBox();
}

void Gui::initGuiComps() {
    QVBoxLayout* lyMain = new QVBoxLayout;
    setLayout(lyMain);

    QHBoxLayout* lyMainUp = new QHBoxLayout;

    QVBoxLayout* lyLeft = new QVBoxLayout;

    lblId = new QLabel("Sir, the id:");
    editId = new QLineEdit;
    lyLeft->addWidget(lblId);
    lyLeft->addWidget(editId);

    lblWheels = new QLabel("Sir, the wheels:");
    editWheels = new QLineEdit;
    lyLeft->addWidget(lblWheels);
    lyLeft->addWidget(editWheels);

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

    lyMainUp->addLayout(lyLeft);

    QVBoxLayout* lyMid = new QVBoxLayout;

    boxy = new QComboBox;
    vector<string> types(srv->getTypes());
    for (auto type : types) {
        boxy->addItem(QString::fromStdString(type));
        // QMessageBox::information(this, "Sir", QString::fromStdString(type));
    }

    lyMid->addWidget(boxy);

    lyMainUp->addLayout(lyMid);

    QVBoxLayout* lyRight = new QVBoxLayout;
    tbl = new QTableView;
    lyRight->addWidget(tbl);
    lyMainUp->addLayout(lyRight);
    lyMain->addLayout(lyMainUp);

    QHBoxLayout* lyMainDown = new QHBoxLayout;

    vip = new WindowForPaint(srv);
    lyMainDown->addWidget(vip);

    lyMain-> addLayout(lyMainDown);
}

void Gui::connectSignalSlots() {
    QObject::connect(buttAdd, &QPushButton::clicked, this, [&]() {
        string fields[4];
        fields[0] = editId->text().toStdString();
        fields[1] = editWheels->text().toStdString();
        fields[2] = editName->text().toStdString();
        fields[3] = editType->text().toStdString();
        string reterr = srv->addCar(fields);
        if (reterr.empty()) {
            QMessageBox::information(this, "Sir!", "Sir, your order was executed!\n");
        }
        else {
            QMessageBox::information(this, "Sir, bad news!", QString::fromStdString(reterr));
        }
        });
    QObject::connect(boxy, &QComboBox::currentIndexChanged, this, [&]() {
        flirtType = boxy->currentText().toStdString();
        reloadTable();
        });
}
void Gui::connectSignalSlotsTbl() {
    QObject::connect(tbl->selectionModel(), &QItemSelectionModel::selectionChanged, this, [&]() {
        if (!tbl->selectionModel()->selectedIndexes().isEmpty()) {
            auto selInd = tbl->selectionModel()->selectedIndexes().at(0);
            int selId = selInd.data(Qt::UserRole).toString().toInt();
            vip->setCar(srv->getCarById(selId));
        }
        });
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
    Tractor* car = this->srv->getAll()[row];

    if (role == Qt::UserRole) {
        return QString::fromStdString(to_string(car->getId()));
    }
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (column)
        {
        case 0:
            return QString::fromStdString(to_string(car->getId()));
        case 1:
            return QString::fromStdString(to_string(car->getWheels()));
        case 2:
            return QString::fromStdString(car->getName());
        case 3:
            return QString::fromStdString(car->getType());
        case 4:
            return QString::fromStdString(to_string(srv->getSameType(car->getType()) - 1));
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
        if (car->getType() == flirtType)
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
                return QString{ "Wheels" };
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

void WindowForPaint::paintEvent(QPaintEvent* ev) {

    if (car == NULL) {
        return;
    }
    QPainter p(this);
    int noWheels = car->getWheels();
    int i, x, y;
    for (i = 1, x = 0, y = 0; i <= noWheels; ++i, x += 40) {
        if (x >= 160) {
            x -= 160;
            y += 40;
        }
        p.drawEllipse(x, y, 20, 20);
    }
}

bool WindowForPaint::inDist(QPoint qp, int x, int y) {
    int xx = qp.x();
    int yy = qp.y();
    int xdif = xx - x;
    int ydif = yy - y;
    return xdif * xdif + ydif * ydif <= 100;
}

void WindowForPaint::mousePressEvent(QMouseEvent*ev) {
    
    int i, x, y;
    if (car == NULL) {
        return;
    }
    for(i = 0, x = 10, y = 10; i < car->getWheels(); ++i, x += 40) {
        if (x >= 160) {
            x -= 160;
            y += 40;
        }
        if (inDist(ev->pos(), x, y)) {
            srv->updCar(car->getId());
        }
    }
}

void WindowForPaint::setCar(Tractor*newCar) {
    car = newCar;
    update();
}

void WindowForPaint::update() {
    QWidget::update();
}

QSize WindowForPaint::minimumSizeHint() const {
    return QSize(160,160);
}

QSize WindowForPaint::sizeHint() const {
    return QSize(160, 160);
}
