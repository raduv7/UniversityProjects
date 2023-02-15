#include "gui.h"

void GUI::initGuiComp() {

    QHBoxLayout* lyMain = new QHBoxLayout;
    this->setLayout(lyMain);

    // left
    QWidget* left = new QWidget;
    QVBoxLayout* lyLeft = new QVBoxLayout;
    left->setLayout(lyLeft);

    editName = new QLineEdit;
    lyLeft->addWidget(editName);
    editType = new QLineEdit;
    lyLeft->addWidget(editType);
    editDescr = new QLineEdit;
    lyLeft->addWidget(editDescr);

    btnAdd = new QPushButton("Add element, sir!");
    btnDel= new QPushButton("Delete element, sir!");

    lyLeft->addWidget(btnAdd);
    lyLeft->addWidget(btnDel);

    // right
    QWidget* right = new QWidget;
    QVBoxLayout* lyRight = new QVBoxLayout;
    right->setLayout(lyRight);

    btnOpenCrud = new QPushButton("Open a brand new edit screen, sir!");
    btnOpenReadOnly = new QPushButton("Open a brand new display screen, sir!");

    lyLeft->addWidget(btnOpenCrud);
    lyLeft->addWidget(btnOpenReadOnly);

    lyMain->addWidget(left);
    lyMain->addWidget(right);
}

void GUI::connectSigns() {
    QObject::connect(btnAdd, &QPushButton::clicked, this, [&]() {
        string newName = this->editName->text().toStdString();
        string newType = this->editType->text().toStdString();
        string newDescr = this->editDescr->text().toStdString();
        srv->add(newName, newType, newDescr);
        });
    QObject::connect(btnDel, &QPushButton::clicked, this, [&]() {
        string newName = this->editName->text().toStdString();
        string newType = this->editType->text().toStdString();
        string newDescr = this->editDescr->text().toStdString();
        srv->del(newName, newType, newDescr);
        });
    QObject::connect(btnOpenCrud, &QPushButton::clicked, this, [&]() {
        WindowCrud* newWCrud = new WindowCrud(srv);
        srv->addObserver(newWCrud);
        newWCrud->show();
        });
    QObject::connect(btnOpenReadOnly, &QPushButton::clicked, this, [&]() {
        WindowReadOnly* newWReadOnly = new WindowReadOnly(srv);
        srv->addObserver(newWReadOnly);
        newWReadOnly->show();
        });
}



/// <summary>
/// MyQTableModel
/// </summary>

int MyQTableModel::rowCount(const QModelIndex& parent) const {
    return this->srv->size();
}

int MyQTableModel::columnCount(const QModelIndex& parent) const {
    return 3;
}

QVariant MyQTableModel::data(const QModelIndex& index, int role) const {
    int row = index.row();
    int column = index.column();

    if (row == this->srv->size())
    {
        return QVariant();
    }
    BundleElement elem = ( * (this->srv) )[row];
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (column)
        {
        case 0:
            return QString::fromStdString(elem.getName());
        case 1:
            return QString::fromStdString(elem.getType());
        case 2:
            return QString::fromStdString(elem.getDescr());
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
        if (row % 4 == 0 || row % 4 == 1)
        {
            return QBrush{ QColor{172, 196, 163} };
        }
        else
        {
            return QBrush{ QColor {82, 146, 242} };
        }
    }
    return QVariant();
}
QVariant MyQTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
                return QString{ "Name" };
            case 1:
                return QString{ "Type" };
            case 2:
                return QString{ "Descr" };
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



/// <summary>
/// Crud ops Window
/// </summary>

void WindowCrud::initWCrudComp() {
    QVBoxLayout* lyMain = new QVBoxLayout;
    this->setLayout(lyMain);

    QLabel* nameLabel = new QLabel("Crud window, sir!");
    lyMain->addWidget(nameLabel);

    int noLines = 10;
    int noColumns = 3;
    this->tblBundle = new QTableWidget{ noLines, noColumns };

    QStringList tblHeaderList;
    tblHeaderList << "Name" << "Type" << "Descr";
    this->tblBundle->setHorizontalHeaderLabels(tblHeaderList);
    this->tblBundle->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    this->setupMyTbl(srv);
    myTblBundle->horizontalHeader()->setStretchLastSection(true);
    lyMain->addWidget(myTblBundle);

    // lyMain->addWidget(tblBundle);

    btnClear = new QPushButton("Clear all, sir!");
    btnGenerate = new QPushButton("Generate new, sir!");

    lyMain->addWidget(btnClear);
    lyMain->addWidget(btnGenerate);
}

void WindowCrud::connectWCrudSigns() {
    QObject::connect(btnClear, &QPushButton::clicked, [&]() {
        srv->clear();
        });
    QObject::connect(btnGenerate, &QPushButton::clicked, [&]() {
        srv->generate();
        });
}

void WindowCrud::reloadWCrudTable(vector <BundleElement> v) {

    this->tblBundle->clearContents();
    this->tblBundle->setRowCount(v.size());

    int lineNumber = 0;

    for (auto& act : v) {
        this->tblBundle->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(act.getName())));
        this->tblBundle->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(act.getType())));
        this->tblBundle->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(act.getDescr())));
        lineNumber++;
    }
}

void WindowCrud::update() {
    reloadWCrudTable(srv->getAll());
    reloadMyTbl();
}

void WindowCrud::setupMyTbl(Service*newSrv) {
    this->myTblBundle = new QTableView();
    MyQTableModel* myModel = new MyQTableModel{ this->srv };
    this->myTblBundle->setModel(myModel);
    this->myTblBundle->resizeColumnsToContents();
}

void WindowCrud::reloadMyTbl() {
    MyQTableModel* myModel = new MyQTableModel{ this->srv };
    this->myTblBundle->setModel(myModel);
    this->myTblBundle->resizeColumnsToContents();
}


/// <summary>
/// Paint Window
/// </summary>

void WindowReadOnly::initWReadOnlyComp() {
    ;
}

void WindowReadOnly::connectWReadOnlySigns() {
    ;
}

void WindowReadOnly::paintEvent(QPaintEvent* ev) {
    QPainter p(this);
    int x = 0;
    int y = 0;
    for (int i = 0; i < srv->size(); ++i) {
        p.drawRect(x, y, 10, 10);
        x = rand() % 400 + 1;
        y = rand() % 400 + 1;
        qDebug() << x << " " << y;
        QRectF target(x, y, 100, 94);
        QRectF source(0, 0, 732, 720);
        QImage image("sun.jpg");

        p.drawImage(target, image, source);

        x += 40;
    }
}

void WindowReadOnly::update() {
    QWidget::update();
}