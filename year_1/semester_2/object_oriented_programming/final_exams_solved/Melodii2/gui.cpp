#include "gui.h"

void Gui::reloadTable() {
    MyTable* myModel = new MyTable(srv);
    tbl->setModel(myModel);
    tbl->resizeColumnsToContents();
    connectSignalSlotsForTable();
    lastId = -1;
}

void Gui::reloadTbl1() {
    vector<Song*> acts = srv->getAll();
    tbl1->clearContents();
    tbl1->setRowCount(acts.size());

    int lineNumber = 0;

    for (auto act : acts) {
        tbl1->setItem(lineNumber, 0, new QTableWidgetItem(QString::number(act->getId())));
        tbl1->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(act->getName())));
        tbl1->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(act->getWriter())));
        tbl1->setItem(lineNumber, 3, new QTableWidgetItem(QString::fromStdString(act->getGenre())));
        lineNumber++;
    }
}

void Gui::initGuiComps() {
    resize(1024, 512);
    QHBoxLayout* lyMain = new QHBoxLayout;
    setLayout(lyMain);

    QVBoxLayout* lyLeft = new QVBoxLayout;

    lblName = new QLabel("Sir, the name:");
    editName = new QLineEdit;
    lyLeft->addWidget(lblName);
    lyLeft->addWidget(editName);

    lblWriter = new QLabel("Sir, the writer:");
    editWriter = new QLineEdit;
    lyLeft->addWidget(lblWriter);
    lyLeft->addWidget(editWriter);

    lblGenre = new QLabel("Sir, the genre:");
    editGenre = new QLineEdit;
    lyLeft->addWidget(lblGenre);
    lyLeft->addWidget(editGenre);

    buttAdd = new QPushButton("Sir, order to add!");
    buttDel = new QPushButton("Sir, order to delete!");
    lyLeft->addWidget(buttAdd);
    lyLeft->addWidget(buttDel);

    lyMain->addLayout(lyLeft);

    QVBoxLayout* lyMid = new QVBoxLayout;

    tbl1 = new QTableWidget(srv->getAll().size(), 4);

    QStringList tblHeaderList;
    tblHeaderList << "Id" << "Name" << "Writer" << "Genre";
    this->tbl1->setHorizontalHeaderLabels(tblHeaderList);
    this->tbl1->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    lyMid->addWidget(tbl1);

    lyMain->addLayout(lyMid);

    QVBoxLayout* lyRight = new QVBoxLayout;

    tbl = new QTableView;
    lyRight->addWidget(tbl);

    lyMain->addLayout(lyRight);
}

void Gui::connectSignalSlots() {
    QObject::connect(buttAdd, &QPushButton::clicked, this, [&]() {
        string fields[3];
        fields[0] = editName->text().toStdString();
        fields[1] = editWriter->text().toStdString();
        fields[2] = editGenre->text().toStdString();
        string err = srv->addSong(fields);
        if (err.empty()) {
            QMessageBox::information(this, "Sir, your attention is needed!", "Sir, you order was executed successfully!");
        }
        else {
            QMessageBox::information(this, "Sir, your attention is needed!", QString::fromStdString(err));
        }
        });
    QObject::connect(buttDel, &QPushButton::clicked, this, [&]() {
        if (lastId == -1) {
            QMessageBox::information(this, "Sir, bad news!\n", "Sir, you must select a song!\n");
        }
        else {
            srv->delSong(lastId);
            QMessageBox::information(this, "Sir, your attention is needed!", "Sir, you order was executed successfully!");
        }
        });
}

void Gui::connectSignalSlotsForTable() {
    QObject::connect(tbl->selectionModel(), &QItemSelectionModel::selectionChanged, this, [&]() {
        if (tbl->selectionModel()->selectedIndexes().isEmpty()) {
            lastId = -1;
        }
        else {
            auto selInd = tbl->selectionModel()->selectedIndexes().at(0);
            QString selQStr = selInd.data(Qt::UserRole).toString();
            lastId = selQStr.toInt();
        }
        });
}

void Gui::paintEvent(QPaintEvent* ev) {
    QPainter p(this);
    vector<int> genres(srv->countAllGenres());
    for (int i = 1; i <= genres[0]; ++i) {
        p.drawEllipse(- 10 * i, - 10 * i, 20 * i, 20 * i);
    }
    for (int i = 1; i <= genres[1]; ++i) {
        p.drawEllipse(1024 - 10 * i, - 10 * i, 20 * i, 20 * i);
    }
    for (int i = 1; i <= genres[2]; ++i) {
        p.drawEllipse(1024 - 10 * i, 512 - 10 * i, 20 * i, 20 * i);
    }
    for (int i = 1; i <= genres[3]; ++i) {
        p.drawEllipse(- 10 * i, 512 - 10 * i, 20 * i, 20 * i);
    }
}

void Gui::update() {
    QWidget::update();
    reloadTable();
    reloadTbl1();
}

int MyTable::rowCount(const QModelIndex& parent) const {
    return srv->getAll().size();
}

int MyTable::columnCount(const QModelIndex& parent) const {
    return 6;
}

QVariant MyTable::data(const QModelIndex& index, int role) const {
    int row = index.row();
    int column = index.column();

    if (row >= this->srv->getAll().size())
    {
        return QVariant();
    }
    Song* song = this->srv->getAll()[row];

    if (role == Qt::UserRole) {
        return QString::fromStdString(to_string(song->getId()));
    }
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (column)
        {
        case 0:
            return QString::fromStdString(to_string(song->getId()));
        case 1:
            return QString::fromStdString(song->getName());
        case 2:
            return QString::fromStdString(song->getWriter());
        case 3:
            return QString::fromStdString(song->getGenre());
        case 4:
            return QString::fromStdString(to_string(srv->countWriter(song->getWriter()) - 1));
        case 5:
            return QString::fromStdString(to_string(srv->countGenre(song->getGenre()) - 1));
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
        if (row % 4 <= 1)
        {
            return QBrush{ QColor{"aqua"} };
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
                return QString{ "Name" };
            case 2:
                return QString{ "Writer" };
            case 3:
                return QString{ "Genre" };
            case 4:
                return QString{ "Same writer" };
            case 5:
                return QString{ "Same genre" };
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
