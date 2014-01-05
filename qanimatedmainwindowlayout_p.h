#ifndef QANIMATEDMAINWINDOWLAYOUT_P_H
#define QANIMATEDMAINWINDOWLAYOUT_P_H

#include <QObject>
#include "qanimatedmainwindowlayout.h"
#include <QEasingCurve>


class QAnimatedMainWindowLayout;


class QAnimatedMainWindowLayoutPrivate : public QObject
{
    Q_OBJECT
public:
    explicit QAnimatedMainWindowLayoutPrivate(QAnimatedMainWindowLayout * p);
    virtual ~QAnimatedMainWindowLayoutPrivate();

    void setGeometry(const QRect & rect);

    void deleteAll();

    void addItem(QWidget *widget, QAnimatedMainWindowLayout::LayoutAreas area);

    void setStrecth(qreal stretch, QAnimatedMainWindowLayout::LayoutAreas area);
    void setSpacing(int space);
    void setAnimationEnabled(bool enabled);
    void setAnimationDuration(uint duration);
    void setEasingCurve(const QEasingCurve &easing);

    int strecth(QAnimatedMainWindowLayout::LayoutAreas area) const;
    qreal percentage(QAnimatedMainWindowLayout::LayoutAreas area) const;
    int spacing() const;
    bool isAnimationEnabled() const;
    const QEasingCurve & easingCurve() const;
    int animationDuration();

    QLayoutItem *itemAt(int i) const;
    QLayoutItem *takeAt(int i);
    int count() const;
    QSize sizeHint();
    QSize minimumSize();
    bool isEmpty() const;
    void setDirty();
    bool isDirty() const;

private slots:
    void animationFinished();

private:
    friend class QAnimatedMainWindowLayout;
    QAnimatedMainWindowLayout * m_public;

    struct Wrapper
    {
        Wrapper(QWidget * w,QAnimatedMainWindowLayout::LayoutAreas a)
            { item = new QWidgetItem(w); area = a;}
        ~Wrapper()
            { if (item) delete item; }
        QWidgetItem * item;
        QAnimatedMainWindowLayout::LayoutAreas area;
    };
    QList<Wrapper*> m_list;

    bool m_dirty;
    bool m_hintSizeNeedRecalc;
    bool m_minimumSizeNeedRecalc;
    bool m_animating;
    bool m_isAnimationEnabled;

    qreal m_stretch[QAnimatedMainWindowLayout::LayoutAreasMax];

    int m_spacing;
    uint m_duration;
    QEasingCurve m_easingCurves;

    QSize m_hintSizeCache;
    QSize m_minimumSizeCache;

    Wrapper * wrapperAt(
            QAnimatedMainWindowLayout::LayoutAreas area,
            QList<Wrapper*> list) const;
    QSize calcSize(int * w, int * h, size_t sz) const;
    QRect geometryOf(
            QAnimatedMainWindowLayout::LayoutAreas area,
            const QRect &rect,
            int *stretch,
            qreal *realStretch);
    void setupPropertyAnimation(
            qreal newStretch, QAnimatedMainWindowLayout::LayoutAreas area);
};

#endif // QANIMATEDMAINWINDOWLAYOUT_P_H
