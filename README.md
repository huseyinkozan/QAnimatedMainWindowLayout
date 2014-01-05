
QAnimatedMainWindowLayout
=========================

Usage
-----

Create 

    QAnimatedMainWindowLayout * amwl = new QAnimatedMainWindowLayout;

Add widgets

    amwl->addLeftWidget(leftGroupBox);
    amwl->addRightWidget(rightGroupBox);
    amwl->addTopWidget(topGroupBox);
    amwl->addBottomWidget(bottomGroupBox);
    amwl->addCenterWidget(centerGroupBox);

Do fine tunes

    amwl->setEasingCurve(QEasingCurve::OutBack);
    amwl->setAnimationDuration(500);

Initialize stretch values

    // disable animation for initialization
    amwl->setAnimationEnabled(false);
    amwl->setLeftPercentage(leftDoubleSpinBox->value());
    amwl->setRightPercentage(rightDoubleSpinBox->value());
    amwl->setTopPercentage(topDoubleSpinBox->value());
    amwl->setBottomPercentage(bottomDoubleSpinBox->value());
    amwl->setCenterPercentage(centerDoubleSpinBox->value());
    amwl->setAnimationEnabled(true);

Set some of the widgets layout

    frame->setLayout(amwl);

Now, on every change on stretch property will done with an animation.