#include "qanimatedmainwindowlayout_p.h"


QAnimatedMainWindowLayoutPrivate::QAnimatedMainWindowLayoutPrivate(
        QAnimatedMainWindowLayout *p)
    : QObject(p)
    , m_public(p)
    , m_dirty(true)
    , m_hintSizeNeedRecalc(true)
    , m_minimumSizeNeedRecalc(true)
    , m_animating(false)
{
    for (int i = 0; i < QAnimatedMainWindowLayout::LayoutAreasMax; ++i) {
        m_spacing[i] = 10;
        m_hiddenStateStretch[i] = 0;
        m_stretch[i] = 0;
        m_duration[i] = 250;
    }
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

    for (int i = 0; i < m_list.size(); ++i) {
        Wrapper * wr = m_list.at(i);
        wr->item->setGeometry(geometryOf(wr->area, m_list, rect, adjustedRect));
    }
}

void QAnimatedMainWindowLayoutPrivate::deleteAll()
{
    while ( ! m_list.isEmpty())
        delete m_list.takeFirst();
}

void QAnimatedMainWindowLayoutPrivate::addItem(
        QWidgetItem *item, QAnimatedMainWindowLayout::LayoutAreas area,
        bool hidden)
{
    Q_CHECK_PTR(item);
    Q_ASSERT(wrapperAt(area, m_list) == NULL);
    m_list.append(new Wrapper(item, area, hidden));
}

void QAnimatedMainWindowLayoutPrivate::setSpacing(
        int space, QAnimatedMainWindowLayout::LayoutAreas area)
{
    if (area == QAnimatedMainWindowLayout::CenterLayoutArea) {
        for (int i = 0; i < QAnimatedMainWindowLayout::LayoutAreasMax; ++i) {
            m_spacing[i] = space;
        }
    }
    else {
        m_spacing[area] = space;
    }
    m_public->invalidate();
}

int QAnimatedMainWindowLayoutPrivate::spacing(
        QAnimatedMainWindowLayout::LayoutAreas area) const
{
    return m_spacing[area];
}

void QAnimatedMainWindowLayoutPrivate::setHiddenStateStrecth(
        int stretch, QAnimatedMainWindowLayout::LayoutAreas area)
{
    m_hiddenStateStretch[area] = stretch;
    m_public->invalidate();
}

qreal QAnimatedMainWindowLayoutPrivate::hiddenStateStrecth(
        QAnimatedMainWindowLayout::LayoutAreas area) const
{
    return m_hiddenStateStretch[area];
}

void QAnimatedMainWindowLayoutPrivate::setStrecth(
        int stretch, QAnimatedMainWindowLayout::LayoutAreas area)
{
    m_stretch[area] = stretch;
    m_public->invalidate();
}

int QAnimatedMainWindowLayoutPrivate::strecth(
        QAnimatedMainWindowLayout::LayoutAreas area) const
{
    return m_stretch[area];
}

void QAnimatedMainWindowLayoutPrivate::setEasingCurve(
        const QEasingCurve &easing, QAnimatedMainWindowLayout::LayoutAreas area)
{
    m_easingCurves[area] = easing;
}

QEasingCurve QAnimatedMainWindowLayoutPrivate::easingCurve(
        QAnimatedMainWindowLayout::LayoutAreas area) const
{
    return m_easingCurves[area];
}

void QAnimatedMainWindowLayoutPrivate::setAnimationDuration(
        uint duration, QAnimatedMainWindowLayout::LayoutAreas area)
{
    m_duration[area] = duration;
}

int QAnimatedMainWindowLayoutPrivate::animationDuration(
        QAnimatedMainWindowLayout::LayoutAreas area)
{
    return m_duration[area];
}

void QAnimatedMainWindowLayoutPrivate::setZOrder(
        int z, QAnimatedMainWindowLayout::LayoutAreas area)
{
    m_zOrder[area] = z;
}

int QAnimatedMainWindowLayoutPrivate::zOrder(
        QAnimatedMainWindowLayout::LayoutAreas area) const
{
    return m_zOrder[area];
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

void QAnimatedMainWindowLayoutPrivate::showAll()
{
    // TODO
}

void QAnimatedMainWindowLayoutPrivate::hideAll()
{
    // TODO
}

void QAnimatedMainWindowLayoutPrivate::show(
        QAnimatedMainWindowLayout::LayoutAreas area)
{
    if ( ! wrapperAt(area, m_list)->isHidden)
        return;
    QList<Wrapper*> list;
    foreach (Wrapper * wr, m_list) {
        list.append(new Wrapper(wr->item, wr->area, wr->isHidden));
    }
    Wrapper * wr = wrapperAt(area, list);
    wr->isHidden = false;

    int lm, tm, rm, bm;
    m_public->getContentsMargins(&lm, &tm, &rm, &bm);
    QRect rect = m_public->geometry();
    QRect adjustedRect = rect.adjusted(lm, tm, -rm, -bm);

    for (int i = 0; i < m_list.size(); ++i) {
        Wrapper * wr = m_list.at(i);
        QRect startRect = geometryOf(wr->area, m_list, rect, adjustedRect);
        QRect endRect = geometryOf(wr->area, list, rect, adjustedRect);
        if (startRect != endRect) {
            // TODO : setup property animation and set geometry properties
            ;
        }
    }
    while ( ! list.isEmpty())
        delete list.takeFirst();
}

void QAnimatedMainWindowLayoutPrivate::hide(
        QAnimatedMainWindowLayout::LayoutAreas area)
{
    // TODO
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
    int ls = m_spacing[QAnimatedMainWindowLayout::LeftLayoutArea];
    int rs = m_spacing[QAnimatedMainWindowLayout::RightLayoutArea];
    int ts = m_spacing[QAnimatedMainWindowLayout::TopLayoutArea];
    int bs = m_spacing[QAnimatedMainWindowLayout::BottomLayoutArea];
    int ws = (lw ? ls : 0) + (rw ? rs : 0);
    int hs = (th ? ts : 0) + (bh ? bs : 0);
    return QSize(lw + cw + rw + ws, lh + hs);
}

QRect QAnimatedMainWindowLayoutPrivate::geometryOf(
        QAnimatedMainWindowLayout::LayoutAreas area, QList<Wrapper *> list
        , const QRect & rect, const QRect & adjustedRect)
{
    return QRect();
}





