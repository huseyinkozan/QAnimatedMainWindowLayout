#include "qanimatedmainwindowlayout_p.h"
#include <QWidget>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>



QAnimatedMainWindowLayoutPrivate::QAnimatedMainWindowLayoutPrivate(
        QAnimatedMainWindowLayout *p)
    : QObject(p)
    , m_public(p)
    , m_dirty(true)
    , m_hintSizeNeedRecalc(true)
    , m_minimumSizeNeedRecalc(true)
    , m_animating(false)
    , m_isAnimationEnabled(true)
    , m_spacing(10)
    , m_duration(250)
{
    for (int i = 0; i < QAnimatedMainWindowLayout::LayoutAreasMax; ++i) {
        m_stretch[i] = 0.0;
    }
    m_stretch[QAnimatedMainWindowLayout::CenterLayoutArea] = 1.0;
}

QAnimatedMainWindowLayoutPrivate::~QAnimatedMainWindowLayoutPrivate()
{
    deleteAll();
}

void QAnimatedMainWindowLayoutPrivate::setGeometry(const QRect &rect)
{
    if (m_animating)
        return;
    if (isEmpty())
        return;

    int lm, tm, rm, bm;
    m_public->getContentsMargins(&lm, &tm, &rm, &bm);
    QRect adjustedRect = rect.adjusted(lm, tm, -rm, -bm);

    int stretchs[QAnimatedMainWindowLayout::LayoutAreasMax];
    for (int i = 0; i < QAnimatedMainWindowLayout::LayoutAreasMax; ++i) {
        if (m_stretch[i] < 1.0)
            stretchs[i] = 0;
        else
            stretchs[i] = (int) m_stretch[i];
    }

    for (int i = 0; i < m_list.size(); ++i) {
        Wrapper * wr = m_list.at(i);
        wr->item->setGeometry(
                    geometryOf(wr->area, adjustedRect, stretchs, m_stretch));
    }
}

void QAnimatedMainWindowLayoutPrivate::deleteAll()
{
    while ( ! m_list.isEmpty())
        delete m_list.takeFirst();
}

void QAnimatedMainWindowLayoutPrivate::addItem(
        QWidget *widget, QAnimatedMainWindowLayout::LayoutAreas area)
{
    Q_CHECK_PTR(widget);
    if (wrapperAt(area, m_list) != NULL)
        return;
    m_list.append(new Wrapper(widget, area));
}

void QAnimatedMainWindowLayoutPrivate::setStrecth(
        qreal stretch, QAnimatedMainWindowLayout::LayoutAreas area)
{
    if (m_stretch[area] == stretch)
        return;
    if (stretch < 0.0)
        m_stretch[area] = 0.0;
    else
        m_stretch[area] = stretch;
    if (m_isAnimationEnabled) {
        setupPropertyAnimation(stretch, area);
        return;
    }
    m_public->invalidate();
}

void QAnimatedMainWindowLayoutPrivate::setSpacing(int space)
{
    m_spacing = space;
    m_public->invalidate();
}

void QAnimatedMainWindowLayoutPrivate::setAnimationEnabled(bool enabled)
{
    m_isAnimationEnabled = enabled;
}


void QAnimatedMainWindowLayoutPrivate::setAnimationDuration(uint duration)
{
    m_duration = duration;
}

void QAnimatedMainWindowLayoutPrivate::setEasingCurve(const QEasingCurve &easing)
{
    m_easingCurves = easing;
}

int QAnimatedMainWindowLayoutPrivate::strecth(
        QAnimatedMainWindowLayout::LayoutAreas area) const
{
    if (m_stretch[area] < 1.0)
        return 0;
    else
        return (int)m_stretch[area];
}

qreal QAnimatedMainWindowLayoutPrivate::percentage(
        QAnimatedMainWindowLayout::LayoutAreas area) const
{
    if (m_stretch[area] >= 1.0 || m_stretch[area] < 0)
        return 0.0;
    else
        return m_stretch[area];
}

int QAnimatedMainWindowLayoutPrivate::spacing() const
{
    return m_spacing;
}

bool QAnimatedMainWindowLayoutPrivate::isAnimationEnabled() const
{
    return m_isAnimationEnabled;
}

const QEasingCurve &QAnimatedMainWindowLayoutPrivate::easingCurve() const
{
    return m_easingCurves;
}

int QAnimatedMainWindowLayoutPrivate::animationDuration()
{
    return m_duration;
}

QLayoutItem *QAnimatedMainWindowLayoutPrivate::itemAt(int i) const
{
    if (i < 0 || i >= m_list.size())
        return NULL;
    return m_list.at(i)->item;
}

QLayoutItem *QAnimatedMainWindowLayoutPrivate::takeAt(int i)
{
    if (i < 0 || i >= m_list.size())
        return NULL;
    Wrapper * w = m_list.takeAt(i);
    if (w == NULL)
        return NULL;
    QWidgetItem * item = w->item;
    delete w;
    return item;
}

int QAnimatedMainWindowLayoutPrivate::count() const
{
    return m_list.size();
}

QSize QAnimatedMainWindowLayoutPrivate::sizeHint()
{
    if ( ! m_hintSizeNeedRecalc)
        return m_hintSizeCache;

    int h[QAnimatedMainWindowLayout::LayoutAreasMax] = {0};
    int w[QAnimatedMainWindowLayout::LayoutAreasMax] = {0};

    for (int i = 0; i < m_list.size(); ++i) {
        Wrapper * wr = m_list.at(i);
        QSize sh = wr->item->sizeHint();
        h[wr->area] = sh.height();
        w[wr->area] = sh.width();
    }
    m_hintSizeCache = calcSize(w, h, QAnimatedMainWindowLayout::LayoutAreasMax);
    m_hintSizeNeedRecalc = false;
    return m_hintSizeCache;
}

QSize QAnimatedMainWindowLayoutPrivate::minimumSize()
{
    if ( ! m_hintSizeNeedRecalc)
        return m_minimumSizeCache;

    int h[QAnimatedMainWindowLayout::LayoutAreasMax] = {0};
    int w[QAnimatedMainWindowLayout::LayoutAreasMax] = {0};

    for (int i = 0; i < m_list.size(); ++i) {
        Wrapper * wr = m_list.at(i);
        QSize sh = wr->item->minimumSize();
        h[wr->area] = sh.height();
        w[wr->area] = sh.width();
    }
    m_minimumSizeCache = calcSize(
                w, h, QAnimatedMainWindowLayout::LayoutAreasMax);
    m_hintSizeNeedRecalc = false;
    return m_minimumSizeCache;

}

bool QAnimatedMainWindowLayoutPrivate::isEmpty() const
{
    return m_list.isEmpty();
}

void QAnimatedMainWindowLayoutPrivate::setDirty()
{
    m_dirty = true;
    m_hintSizeNeedRecalc = true;
    m_minimumSizeNeedRecalc = true;
}

bool QAnimatedMainWindowLayoutPrivate::isDirty() const
{
    return m_dirty;
}

void QAnimatedMainWindowLayoutPrivate::animationFinished()
{
    m_animating = false;
    m_public->invalidate();
}


QAnimatedMainWindowLayoutPrivate::Wrapper *QAnimatedMainWindowLayoutPrivate::wrapperAt(
        QAnimatedMainWindowLayout::LayoutAreas area, QList<Wrapper *> list) const
{
    for (int i = 0; i < list.size(); ++i) {
        if (list.at(i)->area == area)
            return list.at(i);
    }
    return NULL;
}

QSize QAnimatedMainWindowLayoutPrivate::calcSize(int *w, int *h, size_t sz) const
{
    Q_ASSERT(sz == QAnimatedMainWindowLayout::LayoutAreasMax);
    int lw = w[QAnimatedMainWindowLayout::LeftLayoutArea];
    int rw = w[QAnimatedMainWindowLayout::RightLayoutArea];
    int tw = w[QAnimatedMainWindowLayout::TopLayoutArea];
    int bw = w[QAnimatedMainWindowLayout::BottomLayoutArea];
    int cw = w[QAnimatedMainWindowLayout::CenterLayoutArea];
    int lh = h[QAnimatedMainWindowLayout::LeftLayoutArea];
    int rh = h[QAnimatedMainWindowLayout::RightLayoutArea];
    int th = h[QAnimatedMainWindowLayout::TopLayoutArea];
    int bh = h[QAnimatedMainWindowLayout::BottomLayoutArea];
    int ch = h[QAnimatedMainWindowLayout::CenterLayoutArea];
    if (tw > cw)
        cw = tw;
    if (bw > cw)
        cw = bw;
    if (rh > lh)
        lh = rh;
    if ((th+ch+bh) > lh)
        lh = th+ch+bh;
    int ls = m_spacing;
    int rs = m_spacing;
    int ts = m_spacing;
    int bs = m_spacing;
    int ws = (lw ? ls : 0) + (rw ? rs : 0);
    int hs = (th ? ts : 0) + (bh ? bs : 0);
    return QSize(lw + cw + rw + ws, lh + hs);
}

QRect QAnimatedMainWindowLayoutPrivate::geometryOf(
        QAnimatedMainWindowLayout::LayoutAreas area,
        const QRect & rect, int * stretch, qreal * realStretch)
{
    Wrapper * wr = wrapperAt(area, m_list);
    if (wr == NULL)
        return QRect();

    QRect r = rect;
    QSize minSize = wr->item->minimumSize();
    int totalVerticalStretch =
            stretch[QAnimatedMainWindowLayout::TopLayoutArea]
            + stretch[QAnimatedMainWindowLayout::CenterLayoutArea]
            + stretch[QAnimatedMainWindowLayout::BottomLayoutArea];
    int totalHorizontalStretch =
            stretch[QAnimatedMainWindowLayout::LeftLayoutArea]
            + stretch[QAnimatedMainWindowLayout::CenterLayoutArea]
            + stretch[QAnimatedMainWindowLayout::RightLayoutArea];

    if (totalHorizontalStretch == 0)
        totalHorizontalStretch = 1;
    if (totalVerticalStretch == 0)
        totalVerticalStretch = 1;

    qreal horizontalPercentage = r.width() / totalHorizontalStretch;
    qreal verticalPercentage = r.height() / totalVerticalStretch;

    int newWidth = horizontalPercentage * stretch[area];
    int newHeight = verticalPercentage * stretch[area];
    bool isPercentage = (realStretch[area] > 0 && realStretch[area] < 1.0);
    if (isPercentage) {
        newWidth = r.width() * realStretch[area];
        newHeight = r.height() * realStretch[area];
    }

    int lm, tm, rm, bm;
    m_public->getContentsMargins(&lm, &tm, &rm, &bm);

    if (area == QAnimatedMainWindowLayout::LeftLayoutArea) {
        r.setRight(r.left() + newWidth - (isPercentage ? 0 : (m_spacing+lm)));
        if (r.width() < minSize.width()) {
            int right = r.x() + r.width();
            r.setWidth(minSize.width());
            r.translate(-(r.right() - right), 0);
        }
    }
    else if (area == QAnimatedMainWindowLayout::RightLayoutArea) {
        r.setLeft(r.right() - newWidth + (isPercentage ? 0 : (m_spacing+rm)));
        if (r.width() < minSize.width()) {
            r.setWidth(minSize.width());
        }
    }
    else if (area == QAnimatedMainWindowLayout::TopLayoutArea) {
        r.setBottom(r.top() + newHeight - (isPercentage ? 0 : (m_spacing+tm)));
        if (r.height() < minSize.height()) {
            int bottom = r.y() + r.height();
            r.setHeight(minSize.height());
            r.translate(0, -(r.bottom() - bottom));
        }
    }
    else if (area == QAnimatedMainWindowLayout::BottomLayoutArea) {
        r.setTop(r.bottom() - newHeight + (isPercentage ? 0 : (m_spacing+bm)));
        if (r.height() < minSize.height()) {
            r.setHeight(minSize.height());
        }
    }
    else if (area == QAnimatedMainWindowLayout::CenterLayoutArea) {
        // note: no need to add spacing; if no left, no spacing, and if left, left will add spacing
        r.setLeft(r.left() + (horizontalPercentage * stretch[QAnimatedMainWindowLayout::LeftLayoutArea]));
        r.setRight(r.right() - (horizontalPercentage * stretch[QAnimatedMainWindowLayout::RightLayoutArea]));
        r.setTop(r.top() + (verticalPercentage * stretch[QAnimatedMainWindowLayout::TopLayoutArea]));
        r.setBottom(r.bottom() - (verticalPercentage * stretch[QAnimatedMainWindowLayout::BottomLayoutArea]));
    }

    if (area == QAnimatedMainWindowLayout::TopLayoutArea
            || area == QAnimatedMainWindowLayout::BottomLayoutArea) {
        // narrow horizotally
        r.setLeft(r.left() + (horizontalPercentage * stretch[QAnimatedMainWindowLayout::LeftLayoutArea]));
        r.setRight(r.right() - (horizontalPercentage * stretch[QAnimatedMainWindowLayout::RightLayoutArea]));
    }
    return r;
}

void QAnimatedMainWindowLayoutPrivate::setupPropertyAnimation(
        qreal newStretch, QAnimatedMainWindowLayout::LayoutAreas area)
{
    int stretchs[QAnimatedMainWindowLayout::LayoutAreasMax];
    for (int i = 0; i < QAnimatedMainWindowLayout::LayoutAreasMax; ++i) {
        if (m_stretch[i] < 1.0)
            stretchs[i] = 0;
        else
            stretchs[i] = (int) m_stretch[i];
    }
    if (newStretch < 1.0)
        stretchs[area] = 0;
    else
        stretchs[area] = (int) newStretch;


    int lm, tm, rm, bm;
    m_public->getContentsMargins(&lm, &tm, &rm, &bm);
    QRect adjustedRect = m_public->geometry().adjusted(lm, tm, -rm, -bm);

    QParallelAnimationGroup * animationGroup = new QParallelAnimationGroup;

    for (int i = 0; i < QAnimatedMainWindowLayout::LayoutAreasMax; ++i) {
        Wrapper * wr = wrapperAt((QAnimatedMainWindowLayout::LayoutAreas) i, m_list);
        if (wr == NULL)
            continue;
        QWidget * w = wr->item->widget();
        QPropertyAnimation * animation = new QPropertyAnimation(w, "geometry");
        animation->setEndValue(
                    geometryOf(
                        (QAnimatedMainWindowLayout::LayoutAreas) i,
                        adjustedRect, stretchs, m_stretch)
                    );
        animation->setDuration(m_duration);
        animation->setEasingCurve(m_easingCurves);
        animationGroup->addAnimation(animation);
    }
    connect(animationGroup, SIGNAL(finished()), this, SLOT(animationFinished()));
    connect(animationGroup, SIGNAL(finished()), m_public, SIGNAL(animationFinished()));
    m_animating = true;
    animationGroup->start(QAbstractAnimation::DeleteWhenStopped);
}





