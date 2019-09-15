#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QPen>
#include <QColor>

class ProgressBar : public QWidget
{
    Q_OBJECT

private:
    int itemNumber;
    qreal widthtWidth;
    qreal widthtHeight;
    qreal irregularMapWidth;
    qreal irregularMapHeight;


    QColor backGroundColor;
    QColor foreGroundColor;
    QPixmap map;
    QPixmap maptemp;
    QPixmap irregularMapFirst;
    QPixmap irregularMapFirst2;
    QPixmap irregularMap;
    QPixmap irregularMap2;
    QPixmap irregularMap3;
    QPixmap irregularMapEnd;
    void drawItem();
    void drawItemFirst();
    void drawBottomMap();
    void drawItemEnd();
    void fillMapUpdate(QPixmap tmpmap);
public:
    explicit ProgressBar(QWidget *parent = 0);
    void fillMap();
    void setProgressValue(double value);
protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void resizeEvent(QResizeEvent *event);
signals:

public slots:
};

#endif // PROGRESSBAR_H
