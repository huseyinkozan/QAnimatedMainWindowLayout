#include "mainwindow.h"
#include <QEasingCurve>

#include "qanimatedmainwindowlayout.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    QAnimatedMainWindowLayout * amwl = new QAnimatedMainWindowLayout;

    connect(leftSpinBox, SIGNAL(valueChanged(int)), amwl, SLOT(setLeftStretch(int)));
    connect(rightSpinBox, SIGNAL(valueChanged(int)), amwl, SLOT(setRightStretch(int)));
    connect(topSpinBox, SIGNAL(valueChanged(int)), amwl, SLOT(setTopStretch(int)));
    connect(bottomSpinBox, SIGNAL(valueChanged(int)), amwl, SLOT(setBottomStretch(int)));
    connect(centerSpinBox, SIGNAL(valueChanged(int)), amwl, SLOT(setCenterStretch(int)));

    amwl->addLeftWidget(leftGroupBox);
    amwl->addRightWidget(rightGroupBox);
    amwl->addTopWidget(topGroupBox);
    amwl->addBottomWidget(bottomGroupBox);
    amwl->addCenterWidget(centerGroupBox);

    amwl->setEasingCurve(QEasingCurve::OutBack);
    amwl->setAnimationDuration(500);

    amwl->setAnimationEnabled(false);
    amwl->setLeftStretch(leftSpinBox->value());
    amwl->setRightStretch(rightSpinBox->value());
    amwl->setTopStretch(topSpinBox->value());
    amwl->setBottomStretch(bottomSpinBox->value());
    amwl->setCenterStretch(centerSpinBox->value());
    amwl->setAnimationEnabled(true);

    centralWidget()->setLayout(amwl);
}

MainWindow::~MainWindow()
{
}
