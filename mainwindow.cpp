#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qanimatedmainwindowlayout.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QAnimatedMainWindowLayout * amwl = new QAnimatedMainWindowLayout;

    amwl->addLeftWidget(ui->leftGroupBox);
    amwl->addRightWidget(ui->rightGroupBox);
    amwl->addTopWidget(ui->topGroupBox);
    amwl->addBottomWidget(ui->bottomGroupBox);
    amwl->addCenterWidget(ui->textEdit);

    ui->centralWidget->setLayout(amwl);
}

MainWindow::~MainWindow()
{
    delete ui;
}
