#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "database.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowTitle("Media Manager");
    setWindowOpacity(1);

    // create GUI
//    buildWindow();

    // -- DATABASE INIT --
    database = new Database();

    ui->tableView->setDragEnabled(true);
    ui->tableView->setDropIndicatorShown(true);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setDragDropMode(QAbstractItemView::InternalMove);
    ui->tableView->setDragDropOverwriteMode(false);
    ui->tableView->setDropIndicatorShown(true);
    setAcceptDrops(true);
}

void MainWindow::buildWindow() {

    // -- set fixed size --
    const int WIN_W = 320;
    const int WIN_H = 180;
    setMinimumSize(WIN_W, WIN_H);
    setMaximumSize(WIN_W, WIN_H);

    QWidget * content = new QWidget;
    setCentralWidget(content);

    QVBoxLayout * layoutMain = new QVBoxLayout;
    content->setLayout(layoutMain);

    // -- VERT SPACER --
    layoutMain->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));

    // -- INPUT ROW --
    QHBoxLayout * layoutRow = new QHBoxLayout;
    layoutMain->addLayout(layoutRow);

    // input field
    mInputText = new QLineEdit;
    mInputText->setPlaceholderText("1 - 10");
    mInputText->setValidator(new QIntValidator(mInputText));

    connect(mInputText, &QLineEdit::textChanged, this, &MainWindow::onInput);

    layoutRow->addWidget(mInputText);

    // search button
    mButtonSearch = new QPushButton("SEARCH");
    mButtonSearch->setEnabled(false);

    connect(mButtonSearch, &QPushButton::clicked, this, &MainWindow::onSearchClicked);

    layoutRow->addWidget(mButtonSearch);

    // -- OUTPUT ROW --
    mOutputText = new QLabel("...");
    mOutputText->setAlignment(Qt::AlignCenter);
    layoutMain->addWidget(mOutputText);

    // -- VERT SPACER --
    layoutMain->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));
}

void MainWindow::databasePopulate() {
    QSqlQuery query;

    if(!query.exec("INSERT INTO people(name) VALUES('Eddie Guerrero')"))
        qWarning() << "MainWindow::databasePopulate - ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO people(name) VALUES('Gordon Ramsay')"))
        qWarning() << "MainWindow::databasePopulate - ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO people(name) VALUES('Alan Sugar')"))
        qWarning() << "MainWindow::databasePopulate - ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO people(name) VALUES('Dana Scully')"))
        qWarning() << "MainWindow::databasePopulate - ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO people(name) VALUES('Lila	Wolfe')"))
        qWarning() << "MainWindow::databasePopulate - ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO people(name) VALUES('Ashley Williams')"))
        qWarning() << "MainWindow::databasePopulate - ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO people(name) VALUES('Karen Bryant')"))
        qWarning() << "MainWindow::databasePopulate - ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO people(name) VALUES('Jon Snow')"))
        qWarning() << "MainWindow::databasePopulate - ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO people(name) VALUES('Linus Torvalds')"))
        qWarning() << "MainWindow::databasePopulate - ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO people(name) VALUES('Hayley Moore')"))
        qWarning() << "MainWindow::databasePopulate - ERROR: " << query.lastError().text();
}

// ===== PRIVATE SLOTS =====
void MainWindow::onInput()
{
    if(mInputText->text().length() > 0)
        mButtonSearch->setEnabled(true);
    else
        mButtonSearch->setEnabled(false);
}

void MainWindow::onSearchClicked()
{
    QSqlQuery query;
    query.prepare("SELECT name FROM people WHERE id = ?");
    query.addBindValue(mInputText->text().toInt());

    if(!query.exec())
        qWarning() << "MainWindow::OnSearchClicked - ERROR: " << query.lastError().text();

    if(query.first())
        mOutputText->setText(query.value(0).toString());
    else
        mOutputText->setText("person not found");
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
    qDebug() << "DRAG ENTER EVENT!";
    event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event) {
    qDebug() << "DROP EVENT!";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tableView_customContextMenuRequested(const QPoint &pos)
{

}
