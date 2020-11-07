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

    void on_screen1_clicked();

    void on_reset_clicked();

    void on_b1_clicked();

    void on_b2_clicked();

    void on_b3_clicked();
    void on_b4_clicked();
    void on_b5_clicked();
    void on_b6_clicked();
    void on_b7_clicked();
    void on_b8_clicked();
    void on_b9_clicked();

    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
