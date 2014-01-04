#ifndef QANIMATEDMAINWINDOWLAYOUT_H
#define QANIMATEDMAINWINDOWLAYOUT_H

#include <QLayout>

class QAnimatedMainWindowLayoutPrivate;
class QEasingCurve;


class QAnimatedMainWindowLayout : public QLayout
{
    Q_OBJECT

    Q_PROPERTY(int leftStretch READ leftStretch WRITE setLeftStretch)
    Q_PROPERTY(int rightStretch READ rightStretch WRITE setRightStretch)
    Q_PROPERTY(int topStretch READ topStretch WRITE setTopStretch)
    Q_PROPERTY(int bottomStretch READ bottomStretch WRITE setBottomStretch)
    Q_PROPERTY(int centerStretch READ centerStretch WRITE setCenterStretch)
    Q_PROPERTY(int spacing READ spacing WRITE setSpacing)
    Q_PROPERTY(bool animationEnabled READ isAnimationEnabled WRITE setAnimationEnabled)
    Q_PROPERTY(uint animationDuration READ animationDuration WRITE setAnimationDuration)

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

    void addLeftWidget(QWidget *item);
    void addRightWidget(QWidget *item);
    void addTopWidget(QWidget *item);
    void addBottomWidget(QWidget *item);
    void addCenterWidget(QWidget *item);
    void addWidget(QWidget *item, LayoutAreas area);

public slots:
    void setLeftStretch(int stretch);
    void setRightStretch(int stretch);
    void setTopStretch(int stretch);
    void setBottomStretch(int stretch);
    void setCenterStretch(int stretch);
    void setSpacing(int space);
    void setAnimationEnabled(bool enabled);
    void setAnimationDuration(uint duration);
    void setEasingCurve(const QEasingCurve &easing);

public:
    int leftStretch() const;
    int rightStretch() const;
    int topStretch() const;
    int bottomStretch() const;
    int centerStretch() const;
    int spacing() const;
    bool isAnimationEnabled() const;
    uint animationDuration() const;
    const QEasingCurve & easingCurve() const;

    // QLayout interface
private:
    virtual void addItem(QLayoutItem *);
public:
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
    void animationFinished();

private:
    // Q_DISABLE_COPY
    QAnimatedMainWindowLayout(const QAnimatedMainWindowLayout &);
    QAnimatedMainWindowLayout &operator=(const QAnimatedMainWindowLayout &);

    QAnimatedMainWindowLayoutPrivate * m_private;
    friend class QAnimatedMainWindowLayoutPrivate;
};

#endif // QANIMATEDMAINWINDOWLAYOUT_H
