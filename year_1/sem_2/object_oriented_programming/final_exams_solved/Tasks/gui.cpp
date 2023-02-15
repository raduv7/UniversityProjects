#include "gui.h"

// aci incepe Guiu

void Gui::initComps() {
    resize(512,512);
    QVBoxLayout* lyMain = new QVBoxLayout;
    setLayout(lyMain);

    lblMyProgrammer = new QLabel("Filter tasks, sir:");
    lyMain->addWidget(lblMyProgrammer);
    editMyProgrammer = new QLineEdit;
    lyMain->addWidget(editMyProgrammer);

    lblAdd = new QLabel("Add tasks, sir:");
    lyMain->addWidget(lblAdd);
    editAddId = new QLineEdit;
    lyMain->addWidget(editAddId);
    editAddDescr = new QLineEdit;
    lyMain->addWidget(editAddDescr);
    editAddState = new QLineEdit;
    lyMain->addWidget(editAddState);
    editAddProgrammers = new QLineEdit;
    lyMain->addWidget(editAddProgrammers);
    buttAdd = new QPushButton("Add, sir!");
    lyMain->addWidget(buttAdd);

    myTbl = new QTableView;
    lyMain->addWidget(myTbl);

    reloadMyTable();
}

void Gui::connectSignalSlots() {
    QObject::connect(editMyProgrammer, &QLineEdit::editingFinished, this, [&]() {
        programmer = editMyProgrammer->text().toStdString();
        // QMessageBox::information(this, "Programmer info bro", QString::fromStdString(programmer));
        reloadMyTable();
        });
    QObject::connect(buttAdd, &QPushButton::clicked, this, [&]() {
        string line[4];
        line[0] = editAddId->text().toStdString();
        line[1] = editAddDescr->text().toStdString();
        line[2] = editAddState->text().toStdString();
        line[3] = editAddProgrammers->text().toStdString();
        srv->add(line);
        });
}


void Gui::reloadMyTable() {
    MyTable* myModel = new MyTable{ srv, programmer };
    myTbl->setModel(myModel);
    myTbl->resizeColumnsToContents();
}

void Gui::createWindowsForStates() {
    WindowForState* newWindows[3];
    for (int i = 0; i < 3; ++i) {
        newWindows[i] = new WindowForState(srv, i);
        newWindows[i]->show();
    }
}

void Gui::update() {
    reloadMyTable();
}


// aci incepe WindowForState

void WindowForState::initComps() {
    resize(512, 512);
    string myTitle = statesStr[stateCode];
    myTitle[0] += 'A'-'a';
    setWindowTitle(QString::fromStdString(myTitle));

    QVBoxLayout* lyMain = new QVBoxLayout;
    setLayout(lyMain);

    buttState0 = new QPushButton("Open, sir!");
    buttState1 = new QPushButton("In progress, sir!");
    buttState2 = new QPushButton("Closed, sir!");
    if (stateCode != 0) {
        lyMain->addWidget(buttState0);
    }
    if (stateCode != 1) {
        lyMain->addWidget(buttState1);
    }
    if (stateCode != 2) {
        lyMain->addWidget(buttState2);
    }

    myTbl = new QTableView;
    reloadMyTable();
    lyMain->addWidget(myTbl);
}


void WindowForState::setTaskState(int updateTaskId, string nstate) {
    srv->update(updateTaskId, nstate);
}

void WindowForState::connectSignalSlots() {
    connectSignalSlotsForTable();

    QObject::connect(buttState0, &QPushButton::clicked, this, [&]() {
        setTaskState(lastId, statesStr[0]);
        });
    QObject::connect(buttState1, &QPushButton::clicked, this, [&]() {
        setTaskState(lastId, statesStr[1]);
        });
    QObject::connect(buttState2, &QPushButton::clicked, this, [&]() {
        setTaskState(lastId, statesStr[2]);
        });
}

void WindowForState::connectSignalSlotsForTable() {

    QObject::connect(myTbl->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {

        if (myTbl->selectionModel()->selectedIndexes().isEmpty()) {
            lastId = -1;
        }
        else {
            auto selIndex = myTbl->selectionModel()->selectedIndexes().at(0);
            QString sidQStr = selIndex.data(Qt::UserRole).toString();
            int sid = stoi(sidQStr.toStdString());
            lastId = sid;
        }
        });
}

void WindowForState::reloadMyTable() {
    MyTable* myModel = new MyTable{ srv, stateCode };
    myTbl->setModel(myModel);
    myTbl->resizeColumnsToContents();
}

void WindowForState::update() {
    reloadMyTable();
    connectSignalSlotsForTable();
}

// aci incepe MyTable


int MyTable::rowCount(const QModelIndex& parent) const {
	return getAll().size();
}
int MyTable::columnCount(const QModelIndex& parent) const {
	return 4;
}
QVariant MyTable::data(const QModelIndex& index, int role) const {
    int row = index.row();
    int column = index.column();

    if (row == this->srv->getAll().size())
    {
        return QVariant();
    }
    Task tsk = getAll()[row];

    if (role == Qt::UserRole) {
        return QString::fromStdString(to_string(tsk.getId()));
    }
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (column)
        {
        case 0:
            return QString::fromStdString(to_string(tsk.getId()));
        case 1:
            return QString::fromStdString(tsk.getDescr());
        case 2:
            return QString::fromStdString(tsk.getState());
        case 3:
            return QString::fromStdString(to_string(tsk.getWorkersNr()));
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
                return QString{ "Descr" };
            case 2:
                return QString{ "State" };
            case 3:
                return QString{ "Nr of programmers" };
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

vector<Task> MyTable::getAll() const {
	vector<Task> ret;
	if (stateCode == -1) {
        if (programmer.empty()) {
    		ret = srv->getAll();
        }
        else {
            ret = srv->getAll(programmer);
        }
	}
	else {
		ret = srv->getAll(stateCode);
	}
	return ret;
}