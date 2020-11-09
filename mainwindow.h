#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Db.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QGridLayout>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QWidget *wdg = new QWidget;
    Db database;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:


    void b1();

    void b2();

    void b3();

    void b4();

    void b5();

    void b6();

    void b7();

    void b8();

    void b9();

    void b10();

    void on_insertCard_clicked();

    void on_screen1_clicked();

    void on_screen2_clicked();

    void on_screen3_clicked();

    void on_screen4_clicked();

    void on_screen5_clicked();

    void on_screen6_clicked();

    void on_screen7_clicked();

    void on_screen8_clicked();

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



    void on_insertCash_clicked();

private:
    void checkBlockCard(const size_t);

    void giveCash(const int);

    void changeSumCash(const int);

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
