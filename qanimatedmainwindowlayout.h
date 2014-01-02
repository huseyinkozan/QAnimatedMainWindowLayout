#ifndef QANIMATEDMAINWINDOWLAYOUT_H
#define QANIMATEDMAINWINDOWLAYOUT_H

#include <QLayout>

class QAnimatedMainWindowLayoutPrivate;
class QEasingCurve;


class QAnimatedMainWindowLayout : public QLayout
{
    Q_OBJECT

public:
    enum LayoutAreas {
        LeftLayoutArea = 0,
        RightLayoutArea,
        TopLayoutArea,
        BottomLayoutArea,
        CenterLayoutArea,
        LayoutAreasMax
    };

public:
    explicit QAnimatedMainWindowLayout(QWidget *parent = 0);
    virtual ~QAnimatedMainWindowLayout();

    virtual void addWidget(
            QWidgetItem * item, LayoutAreas area, bool hidden = false);

    void setSpacing(int space, LayoutAreas area);
    int spacing(LayoutAreas area) const;

    void setHiddenStateStrecth(int stretch, LayoutAreas area);
    int hiddenStateStretch(LayoutAreas area) const;

    void setStrecth(int stretch, LayoutAreas area);
    int stretch(LayoutAreas area) const;

    void setEasingCurve(const QEasingCurve &easing, LayoutAreas area);
    QEasingCurve easingCurve(LayoutAreas area) const;

    void setAnimationDuration(uint duration, LayoutAreas area);
    uint animationDuration(LayoutAreas area);

    void setZOrder(int z, LayoutAreas area);
    int zOrder(LayoutAreas area) const;

    // QLayout interface
public:
    virtual void addItem(QLayoutItem *);
    virtual QLayoutItem *itemAt(int index) const;
    virtual QLayoutItem *takeAt(int index);
    virtual int count() const;

    // QLayoutItem interface
public:
    virtual QSize sizeHint() const;
    virtual QSize minimumSize() const;
    virtual void setGeometry(const QRect &rect);
    virtual bool isEmpty() const;
    virtual bool hasHeightForWidth() const;
    virtual void invalidate();

signals:
    void allAnimationsFinished();
    void showAnimationFinished(LayoutAreas area);
    void hideAnimationFinished(LayoutAreas area);

public slots:
    void showAll();
    void hideAll();
    void show(LayoutAreas area);
    void hide(LayoutAreas area);

private:
    // Q_DISABLE_COPY
    QAnimatedMainWindowLayout(const QAnimatedMainWindowLayout &);
    QAnimatedMainWindowLayout &operator=(const QAnimatedMainWindowLayout &);

    QAnimatedMainWindowLayoutPrivate * m_private;
    friend class QAnimatedMainWindowLayoutPrivate;
};

#endif // QANIMATEDMAINWINDOWLAYOUT_H
