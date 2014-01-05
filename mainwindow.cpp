#include "mainwindow.h"
#include <QEasingCurve>

#include "qanimatedmainwindowlayout.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    QAnimatedMainWindowLayout * amwl = new QAnimatedMainWindowLayout;


    connect(leftDoubleSpinBox, SIGNAL(valueChanged(double)), amwl, SLOT(setLeftPercentage(qreal)));
    connect(rightDoubleSpinBox, SIGNAL(valueChanged(double)), amwl, SLOT(setRightPercentage(qreal)));
    connect(topDoubleSpinBox, SIGNAL(valueChanged(double)), amwl, SLOT(setTopPercentage(qreal)));
    connect(bottomDoubleSpinBox, SIGNAL(valueChanged(double)), amwl, SLOT(setBottomPercentage(qreal)));
    connect(centerDoubleSpinBox, SIGNAL(valueChanged(double)), amwl, SLOT(setCenterPercentage(qreal)));

    amwl->addLeftWidget(leftGroupBox);
    amwl->addRightWidget(rightGroupBox);
    amwl->addTopWidget(topGroupBox);
    amwl->addBottomWidget(bottomGroupBox);
    amwl->addCenterWidget(centerGroupBox);

    amwl->setEasingCurve(QEasingCurve::OutBack);
    amwl->setAnimationDuration(500);

    // disable animation for initialization
    amwl->setAnimationEnabled(false);
    amwl->setLeftPercentage(leftDoubleSpinBox->value());
    amwl->setRightPercentage(rightDoubleSpinBox->value());
    amwl->setTopPercentage(topDoubleSpinBox->value());
    amwl->setBottomPercentage(bottomDoubleSpinBox->value());
    amwl->setCenterPercentage(centerDoubleSpinBox->value());
    amwl->setAnimationEnabled(true);

    QLayout * fl = frame->layout();
    if (fl)
        delete fl;
    frame->setLayout(amwl);
}

MainWindow::~MainWindow()
{
}
