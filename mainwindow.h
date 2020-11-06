#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Db.h"
#include <QMessageBox>
#include <QInputDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Db database;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_insertCard_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
