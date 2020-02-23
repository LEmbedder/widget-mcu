#include "navprogress.h"

NavProgress::NavProgress(QWidget *parent) : QWidget(parent)
{
    maxStep = 13;
    currentStep = 7.9;
    navStyle = NavStyle_JD;
    background = QColor(Qt::gray);
    foreground = QColor(Qt::blue);
//    for(int i = 0; i< maxStep;i++)
//    {
        topInfo<<QString("待机")<<QString("延时(1)")<<QString("延时(2)")<<QString("延时(3)")<<QString("充气")<<QString("泄压")\
              <<QString("平衡1")<<QString("平衡2")<<QString("测试")<<QString("排气")<<QString("延时(4)")<<QString("延时(5)")\
             <<QString("延时(6)")<<QString("结束");
//    }
}

void NavProgress::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //根据不一样的样式绘制
    if (navStyle == NavStyle_JD) {
        //绘制背景
        drawBg_JD(&painter);
        //绘制文字
        drawText_JD(&painter);
        //绘制当前背景
        drawCurrentBg_JD(&painter);
        //绘制当前文字
//        drawCurrentText_JD(&painter);
    }
    else if (navStyle == NavStyle_TB) {
        //绘制背景
//        drawBg_TB(&painter);
        //绘制文字
//        drawText_TB(&painter);
        //绘制当前背景
//        drawCurrentBg_TB(&painter);
    }
    else if (navStyle == NavStyle_ZFB) {
        //绘制背景
//        drawBg_ZFB(&painter);
        //绘制文字
//        drawText_ZFB(&painter);
        //绘制当前背景
//        drawCurrentBg_ZFB(&painter);
    }

}

void NavProgress::drawBg_JD(QPainter *painter)
{
    painter->save();

    //圆半径为高度一定比例,计算宽度,将宽度等分
    int width = this->width() / maxStep;
    int height = this->height() / 2;
    int radius = height / 2;
    int initX = 0;
    int initY = height / 2 + radius / 5;

    //逐个绘制连接线条
    initX = width / 2;

    QPen pen;
    pen.setWidthF((double)radius / 4);
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(background);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);

    for (int i = 0; i < maxStep - 1; i++) {
        painter->drawLine(QPoint(initX+radius, initY), QPoint(initX + width-radius, initY));
        initX += width;
    }

    //逐个绘制圆
    initX = width / 2;
    painter->setPen(Qt::NoPen);
    painter->setBrush(background);

    for (int i = 0; i < maxStep; i++) {
        painter->drawEllipse(QPoint(initX, initY), radius, radius);
        initX += width;
    }

    //逐个绘制圆中的数字
    initX = width / 2;
    QFont font;
    font.setPixelSize(radius);
    painter->setFont(font);
    painter->setPen(foreground);
    painter->setBrush(Qt::NoBrush);

    for (int i = 0; i < maxStep; i++) {
        QRect textRect(initX - radius, initY - radius, radius * 2, radius * 2);
        painter->drawText(textRect, Qt::AlignCenter, QString::number(i + 1));
        initX += width;
    }

    painter->restore();
}

void NavProgress::drawText_JD(QPainter *painter)
{
    int width = this->width() / maxStep;
    int height = this->height() / 2;
    int initX = 0;
    int initY = height;

    painter->save();
    QFont font;
    font.setPixelSize(height / 3);
    painter->setFont(font);
    painter->setPen(background);
    painter->setBrush(Qt::NoBrush);

    for (int i = 0; i < maxStep; i++) {
        QRect textRect(initX, 0, width, 20);
        painter->drawText(textRect, Qt::AlignCenter, topInfo.at(i));
        initX += width;
    }

    painter->restore();
}

void NavProgress::drawCurrentBg_JD(QPainter *painter)
{
    //圆半径为高度一定比例,计算宽度,将宽度等分
    int width = this->width() / maxStep;
    int height = this->height() / 2;
    int radius = height / 2;
    int initX = 0;
    int initY = height / 2 + radius / 5;
    int currentStepTemp = (int)currentStep;
    double currentStepDot = currentStep- currentStepTemp;

    //逐个绘制连接线条
    initX = width / 2;
    QPen pen;
    pen.setWidthF((double)radius / 4);
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(foreground);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);

    for (int i = 0; i < currentStepTemp - 1; i++) {
        painter->drawLine(QPointF(initX+radius, initY), QPointF(initX + width-radius, initY));
        initX += width;
    }
    painter->drawLine(QPointF(initX+radius, initY), QPointF(initX+radius + (width-2*radius)*currentStepDot, initY));

    //逐个绘制圆
    initX = width / 2;
    painter->setPen(Qt::NoPen);
    painter->setBrush(foreground);

    for (int i = 0; i < currentStepTemp; i++) {
        painter->drawEllipse(QPoint(initX, initY), radius, radius);
        initX += width;
    }
}
