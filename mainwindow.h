#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"


class MainWindow : public QMainWindow, public Ui_MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

};

#endif // MAINWINDOW_H
