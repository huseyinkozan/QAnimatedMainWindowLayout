#include "qanimatedmainwindowlayout.h"
#include "qanimatedmainwindowlayout_p.h"


QAnimatedMainWindowLayout::QAnimatedMainWindowLayout(QWidget *parent)
    : QLayout(parent)
    , m_private(new QAnimatedMainWindowLayoutPrivate(this))
{
}

QAnimatedMainWindowLayout::~QAnimatedMainWindowLayout()
{
}

void QAnimatedMainWindowLayout::addLeftWidget(QWidget *item)
{
    m_private->addItem(item, LeftLayoutArea);
}

void QAnimatedMainWindowLayout::addRightWidget(QWidget *item)
{
    m_private->addItem(item, RightLayoutArea);
}

void QAnimatedMainWindowLayout::addTopWidget(QWidget *item)
{
    m_private->addItem(item, TopLayoutArea);
}

void QAnimatedMainWindowLayout::addBottomWidget(QWidget *item)
{
    m_private->addItem(item, BottomLayoutArea);
}

void QAnimatedMainWindowLayout::addCenterWidget(QWidget *item)
{
    m_private->addItem(item, CenterLayoutArea);
}

void QAnimatedMainWindowLayout::addWidget(
        QWidget *item, QAnimatedMainWindowLayout::LayoutAreas area)
{
    m_private->addItem(item, area);
}

void QAnimatedMainWindowLayout::setLeftStretch(int stretch)
{
    m_private->setStrecth((qreal) stretch, LeftLayoutArea);
}

void QAnimatedMainWindowLayout::setRightStretch(int stretch)
{
    m_private->setStrecth((qreal) stretch, RightLayoutArea);

}

void QAnimatedMainWindowLayout::setTopStretch(int stretch)
{
    m_private->setStrecth((qreal) stretch, TopLayoutArea);

}

void QAnimatedMainWindowLayout::setBottomStretch(int stretch)
{
    m_private->setStrecth((qreal) stretch, BottomLayoutArea);

}

void QAnimatedMainWindowLayout::setCenterStretch(int stretch)
{
    m_private->setStrecth((qreal) stretch, CenterLayoutArea);

}

void QAnimatedMainWindowLayout::setLeftPercentage(qreal stretch)
{
    m_private->setStrecth(stretch, LeftLayoutArea);
}

void QAnimatedMainWindowLayout::setRightPercentage(qreal stretch)
{
    m_private->setStrecth(stretch, RightLayoutArea);
}

void QAnimatedMainWindowLayout::setTopPercentage(qreal stretch)
{
    m_private->setStrecth(stretch, TopLayoutArea);
}

void QAnimatedMainWindowLayout::setBottomPercentage(qreal stretch)
{
    m_private->setStrecth(stretch, BottomLayoutArea);
}

void QAnimatedMainWindowLayout::setCenterPercentage(qreal stretch)
{
    m_private->setStrecth(stretch, CenterLayoutArea);
}

void QAnimatedMainWindowLayout::setSpacing(int space)
{
    m_private->setSpacing(space);
}

void QAnimatedMainWindowLayout::setAnimationEnabled(bool enabled)
{
    m_private->setAnimationEnabled(enabled);
}

void QAnimatedMainWindowLayout::setAnimationDuration(uint duration)
{
    m_private->setAnimationDuration(duration);
}

void QAnimatedMainWindowLayout::setEasingCurve(const QEasingCurve &easing)
{
    m_private->setEasingCurve(easing);
}

int QAnimatedMainWindowLayout::leftStretch() const
{
    return m_private->strecth(LeftLayoutArea);
}

int QAnimatedMainWindowLayout::rightStretch() const
{
    return m_private->strecth(RightLayoutArea);
}

int QAnimatedMainWindowLayout::topStretch() const
{
    return m_private->strecth(TopLayoutArea);
}

int QAnimatedMainWindowLayout::bottomStretch() const
{
    return m_private->strecth(BottomLayoutArea);
}

int QAnimatedMainWindowLayout::centerStretch() const
{
    return m_private->strecth(CenterLayoutArea);
}

qreal QAnimatedMainWindowLayout::leftPercentage() const
{
    return m_private->percentage(LeftLayoutArea);
}

qreal QAnimatedMainWindowLayout::rightPercentage() const
{
    return m_private->percentage(RightLayoutArea);
}

qreal QAnimatedMainWindowLayout::topPercentage() const
{
    return m_private->percentage(TopLayoutArea);
}

qreal QAnimatedMainWindowLayout::bottomPercentage() const
{
    return m_private->percentage(BottomLayoutArea);
}

qreal QAnimatedMainWindowLayout::centerPercentage() const
{
    return m_private->percentage(CenterLayoutArea);
}

int QAnimatedMainWindowLayout::spacing() const
{
    return m_private->spacing();
}

bool QAnimatedMainWindowLayout::isAnimationEnabled() const
{
    return m_private->isAnimationEnabled();
}

uint QAnimatedMainWindowLayout::animationDuration() const
{
    return m_private->animationDuration();
}

const QEasingCurve &QAnimatedMainWindowLayout::easingCurve() const
{
    return m_private->easingCurve();
}

void QAnimatedMainWindowLayout::addItem(
        QLayoutItem *)
{
    Q_ASSERT(false);
}

QLayoutItem *QAnimatedMainWindowLayout::itemAt(
        int index) const
{
    return m_private->itemAt(index);
}

QLayoutItem *QAnimatedMainWindowLayout::takeAt(
        int index)
{
    return takeAt(index);
}

int QAnimatedMainWindowLayout::count() const
{
    return m_private->count();
}

QSize QAnimatedMainWindowLayout::sizeHint() const
{
    return m_private->sizeHint();
}

QSize QAnimatedMainWindowLayout::minimumSize() const
{
    return m_private->minimumSize();
}

void QAnimatedMainWindowLayout::setGeometry(const QRect & rect)
{
    if (m_private->isDirty() || rect != geometry()) {
        m_private->setGeometry(rect);
        QLayout::setGeometry(rect);
    }
}

bool QAnimatedMainWindowLayout::isEmpty() const
{
    return m_private->isEmpty();
}

bool QAnimatedMainWindowLayout::hasHeightForWidth() const
{
    return false;
}

void QAnimatedMainWindowLayout::invalidate()
{
    m_private->setDirty();
    QLayout::invalidate();
}

