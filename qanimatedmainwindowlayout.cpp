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

void QAnimatedMainWindowLayout::addWidget(
        QWidgetItem *item, QAnimatedMainWindowLayout::LayoutAreas area,
        bool hidden)
{
    m_private->addItem(item, area, hidden);
}

void QAnimatedMainWindowLayout::setSpacing(
        int space, QAnimatedMainWindowLayout::LayoutAreas area)
{
    m_private->setSpacing(space, area);
}

int QAnimatedMainWindowLayout::spacing(
        QAnimatedMainWindowLayout::LayoutAreas area) const
{
    return m_private->spacing(area);
}

void QAnimatedMainWindowLayout::setHiddenStateStrecth(
        int stretch, LayoutAreas area)
{
    m_private->setHiddenStateStrecth(stretch, area);
}

int QAnimatedMainWindowLayout::hiddenStateStretch(
        LayoutAreas area) const
{
    return m_private->hiddenStateStrecth(area);
}

void QAnimatedMainWindowLayout::setStrecth(
        int stretch, QAnimatedMainWindowLayout::LayoutAreas area)
{
    m_private->setStrecth(stretch, area);
}

int QAnimatedMainWindowLayout::stretch(
        QAnimatedMainWindowLayout::LayoutAreas area) const
{
    return m_private->strecth(area);
}

void QAnimatedMainWindowLayout::setEasingCurve(
        const QEasingCurve &easing, QAnimatedMainWindowLayout::LayoutAreas area)
{
    m_private->setEasingCurve(easing, area);
}

QEasingCurve QAnimatedMainWindowLayout::easingCurve(
        QAnimatedMainWindowLayout::LayoutAreas area) const
{
    return m_private->easingCurve(area);
}

void QAnimatedMainWindowLayout::setAnimationDuration(
        uint duration, QAnimatedMainWindowLayout::LayoutAreas area)
{
    m_private->setAnimationDuration(duration, area);
}

uint QAnimatedMainWindowLayout::animationDuration(
        QAnimatedMainWindowLayout::LayoutAreas area)
{
    return m_private->animationDuration(area);
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
    m_private->sizeHint();
}

QSize QAnimatedMainWindowLayout::minimumSize() const
{
    m_private->minimumSize();
}

void QAnimatedMainWindowLayout::setGeometry(
        const QRect & rect)
{
    if (m_private->isDirty() || rect != geometry()) {
        int lm, tm, rm, bm;
        getContentsMargins(&lm, &tm, &rm, &bm);
        m_private->setGeometry(rect.adjusted(lm, tm, -rm, -bm));
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

void QAnimatedMainWindowLayout::showAll()
{
    m_private->showAll();
}

void QAnimatedMainWindowLayout::hideAll()
{
    m_private->hideAll();
}

void QAnimatedMainWindowLayout::show(
        QAnimatedMainWindowLayout::LayoutAreas area)
{
    m_private->show(area);
}

void QAnimatedMainWindowLayout::hide(
        QAnimatedMainWindowLayout::LayoutAreas area)
{
    m_private->hide(area);
}
