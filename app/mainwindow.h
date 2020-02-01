#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "database.h"

#include <QMainWindow>
#include <QDragMoveEvent>

class QLabel;
class QLineEdit;
class QPushButton;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_tableView_customContextMenuRequested(const QPoint &pos);
    void onInput();
    void onSearchClicked();

protected:
    void dropEvent(QDropEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;

private:
    Ui::MainWindow *ui;

    void buildWindow();

    void databasePopulate();

    Database * database;
    QLineEdit * mInputText;
    QPushButton * mButtonSearch;
    QLabel * mOutputText;
};

#endif // MAINWINDOW_H
