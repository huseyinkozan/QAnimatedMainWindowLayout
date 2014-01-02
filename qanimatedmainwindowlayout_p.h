#ifndef QANIMATEDMAINWINDOWLAYOUT_P_H
#define QANIMATEDMAINWINDOWLAYOUT_P_H

#include <QObject>
#include "qanimatedmainwindowlayout.h"
#include <QEasingCurve>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>


class QAnimatedMainWindowLayout;


class QAnimatedMainWindowLayoutPrivate : public QObject
{
    Q_OBJECT
public:
    explicit QAnimatedMainWindowLayoutPrivate(QAnimatedMainWindowLayout * p);
    virtual ~QAnimatedMainWindowLayoutPrivate();

    void setGeometry(const QRect & rect);

    void deleteAll();

    void addItem(QWidgetItem * item, QAnimatedMainWindowLayout::LayoutAreas area, bool hidden);

    void setSpacing(int space, QAnimatedMainWindowLayout::LayoutAreas area);
    int spacing(QAnimatedMainWindowLayout::LayoutAreas area) const;

    void setHiddenStateStrecth(int stretch, QAnimatedMainWindowLayout::LayoutAreas area);
    qreal hiddenStateStrecth(QAnimatedMainWindowLayout::LayoutAreas area) const;

    void setStrecth(int stretch, QAnimatedMainWindowLayout::LayoutAreas area);
    int strecth(QAnimatedMainWindowLayout::LayoutAreas area) const;

    void setEasingCurve(const QEasingCurve &easing, QAnimatedMainWindowLayout::LayoutAreas area);
    QEasingCurve easingCurve(QAnimatedMainWindowLayout::LayoutAreas area) const;

    void setAnimationDuration(uint duration, QAnimatedMainWindowLayout::LayoutAreas area);
    int animationDuration(QAnimatedMainWindowLayout::LayoutAreas area);

    void setZOrder(int z, QAnimatedMainWindowLayout::LayoutAreas area);
    int zOrder(QAnimatedMainWindowLayout::LayoutAreas area) const;

    QLayoutItem *itemAt(int i) const;
    QLayoutItem *takeAt(int i);
    int count() const;
    QSize sizeHint();
    QSize minimumSize();
    bool isEmpty() const;
    void setDirty();
    bool isDirty() const;

signals:
    void allAnimationsFinished();
    void showAnimationFinished(QAnimatedMainWindowLayout::LayoutAreas area);
    void hideAnimationFinished(QAnimatedMainWindowLayout::LayoutAreas area);


public slots:
    void showAll();
    void hideAll();
    void show(QAnimatedMainWindowLayout::LayoutAreas area);
    void hide(QAnimatedMainWindowLayout::LayoutAreas area);

private:
    friend class QAnimatedMainWindowLayout;
    QAnimatedMainWindowLayout * m_public;

    struct Wrapper
    {
        Wrapper(QWidgetItem * i,QAnimatedMainWindowLayout::LayoutAreas a,bool h)
            { item = i; area = a; isHidden = h;}
        ~Wrapper()
            { if (item) delete item; }
        QWidgetItem * item;
        QAnimatedMainWindowLayout::LayoutAreas area;
        bool isHidden;
    };
    QList<Wrapper*> m_list;

    bool m_dirty;
    bool m_hintSizeNeedRecalc;
    bool m_minimumSizeNeedRecalc;
    bool m_animating;

    int m_spacing[QAnimatedMainWindowLayout::LayoutAreasMax];
    int m_hiddenStateStretch[QAnimatedMainWindowLayout::LayoutAreasMax];
    int m_stretch[QAnimatedMainWindowLayout::LayoutAreasMax];
    int m_zOrder[QAnimatedMainWindowLayout::LayoutAreasMax];

    uint m_duration[QAnimatedMainWindowLayout::LayoutAreasMax];
    QEasingCurve m_easingCurves[QAnimatedMainWindowLayout::LayoutAreasMax];

    QSize m_hintSizeCache;
    QSize m_minimumSizeCache;

    Wrapper * wrapperAt(QAnimatedMainWindowLayout::LayoutAreas area, QList<Wrapper*> list) const;
    QSize calcSize(int * w, int * h, size_t sz) const;
    QRect geometryOf(QAnimatedMainWindowLayout::LayoutAreas area, QList<Wrapper*> list, const QRect &rect, const QRect &adjustedRect);
};

#endif // QANIMATEDMAINWINDOWLAYOUT_P_H
