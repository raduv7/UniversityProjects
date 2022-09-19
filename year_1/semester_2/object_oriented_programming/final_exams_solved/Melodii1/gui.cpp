#include "gui.h"

void Gui::initGuiComps() {
    resize(1024, 512);

    QVBoxLayout*lyMain = new QVBoxLayout;
    setLayout(lyMain);

    QHBoxLayout* lyMainUp = new QHBoxLayout;

    QVBoxLayout* lyLeft = new QVBoxLayout;

    lblRank = new QLabel("Sir, the rank:");
    lblName = new QLabel("Sir, the name:");

    editRank = new QSlider;
    editRank->setOrientation(Qt::Horizontal);
    editRank->setMinimum(0);
    editRank->setMaximum(10);
    editName = new QLineEdit;
    lyLeft->addWidget(lblRank);
    lyLeft->addWidget(editRank);
    lyLeft->addWidget(lblName);
    lyLeft->addWidget(editName);

    buttUpd = new QPushButton("Sir, order to update!");
    buttDel = new QPushButton("Sir, order to delete!");
    lyLeft->addWidget(buttUpd);
    lyLeft->addWidget(buttDel);

    lyMainUp->addLayout(lyLeft);
    

    QVBoxLayout* lyRight = new QVBoxLayout;

    tbl = new QTableView;
    lyRight->addWidget(tbl);

    lyMainUp->addLayout(lyRight);

    lyMain->addLayout(lyMainUp);

    QHBoxLayout* lyMainDown = new QHBoxLayout;

    widgetPainter = new WidgetPaintsRanks(srv);
    widgetPainter->resize(1024, 256);
    lyMain->addWidget(widgetPainter);
    widgetPainter->show();

    lyMain->addLayout(lyMainDown);
    update();
}

void Gui::connectSignalSlots() {
    QObject::connect(buttUpd, &QPushButton::clicked, this, [&]() {
        int newRank = editRank->value();
        string newName = editName->text().toStdString();
        string upderrs = srv->updSong(lastId, newRank, newName);
        if (!upderrs.empty()) {
            QMessageBox::information(this, "Sir, bad news!", QString::fromStdString(upderrs));
        }
        });
    QObject::connect(buttDel, &QPushButton::clicked, this, [&]() {
        string ret = srv->delSong(lastId);
        if (!ret.empty()) {
            QMessageBox::information(this, "Sir, bad news!", QString::fromStdString(ret));
        }
        });
}

void Gui::connectSignalSlotsForMyTbl() {
    QObject::connect(tbl->selectionModel(), &QItemSelectionModel::selectionChanged, this, [&]() { 
        
        if (tbl->selectionModel()->selectedIndexes().isEmpty()) {
            lastId = -1;
        }
        else {
            auto selectedIndex = tbl->selectionModel()->selectedIndexes().at(0);
            QString selectedIdQStr = selectedIndex.data(Qt::UserRole).toString();
            int selectedId = selectedIdQStr.toInt();
            lastId = selectedId;

            QString selectedRankQStr = selectedIndex.siblingAtColumn(1).data(Qt::EditRole).toString();
            editRank->setValue(selectedRankQStr.toInt());
            QString selectedNameQStr = selectedIndex.siblingAtColumn(2).data(Qt::EditRole).toString();
            editName->setText(selectedNameQStr);
        }
        });
}

void Gui::reloadMyTable() {
    MyTable* myModel = new MyTable(srv);
    tbl->setModel(myModel);
    tbl->resizeColumnsToContents();
}

void Gui::update() {
	reloadMyTable();
    connectSignalSlotsForMyTbl();
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
            return QString::fromStdString(to_string(song->getRank()));
        case 2:
            return QString::fromStdString(song->getName());
        case 3:
            return QString::fromStdString(song->getWriter());
        case 4:
            return QString::fromStdString(to_string(srv->countSongsAtRank(song->getRank()) - 1));
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
            return QBrush{ QColor{169, 196, 169} };
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
                return QString{ "Rank" };
            case 2:
                return QString{ "Title" };
            case 3:
                return QString{ "Author" };
            case 4:
                return QString{ "Other songs with the same rank" };
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

void WidgetPaintsRanks::paintEvent(QPaintEvent* ev) {
    QPainter p(this);
    vector<int> rankHeights(srv->getAllRanks());
    int maxHeight = 0;
    for (auto height : rankHeights) {
        if (height > maxHeight) {
            maxHeight = height;
        }
    }
    for (int i = 0; i <= 10; ++i) {
        p.drawRect(100*i, 0, 24, (240 * rankHeights[i]) / maxHeight);
    }
}

QSize WidgetPaintsRanks::minimumSizeHint() const {
    return QSize(1024, 256);
}

QSize WidgetPaintsRanks::sizeHint() const {
    return QSize(1024, 256);
}

void WidgetPaintsRanks::update() {
    QWidget::update();
}