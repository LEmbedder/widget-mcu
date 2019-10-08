#include "progressbar.h"

ProgressBar::ProgressBar(QWidget *parent) : QWidget(parent)
{
    itemNumber = 10;

    widthtWidth = 700;
    widthtHeight = 30;
    irregularMapWidth = 1.0*widthtWidth/itemNumber+9;
    irregularMapHeight = widthtHeight;

    map = QPixmap(widthtWidth,widthtHeight);
    map.fill(Qt::transparent);
    maptemp = QPixmap(widthtWidth,widthtHeight);
    maptemp.fill(Qt::transparent);
    irregularMap = QPixmap(irregularMapWidth,irregularMapHeight);
    irregularMap.fill(Qt::transparent);
    irregularMap2 = QPixmap(irregularMapWidth,irregularMapHeight);
    irregularMap2.fill(Qt::transparent);
    irregularMapFirst = QPixmap(irregularMapWidth,irregularMapHeight);
    irregularMapFirst.fill(Qt::transparent);
    irregularMapFirst2 = QPixmap(irregularMapWidth,irregularMapHeight);
    irregularMapFirst2.fill(Qt::transparent);
    irregularMapEnd = QPixmap(irregularMapWidth,irregularMapHeight);
    irregularMapEnd.fill(Qt::transparent);


    drawBottomMap();
    drawItemFirst();
    drawItem();
    drawItemEnd();

    fillMap();
}

void ProgressBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,maptemp);
}

void ProgressBar::resizeEvent(QResizeEvent *event)
{
}
void ProgressBar::drawBottomMap()
{
    QPainter painter;
    painter.begin(&map);
    QBrush brush(QColor(Qt::gray), Qt::SolidPattern);
    painter.setBrush(brush);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); //抗锯齿和使用平滑转换算法
    painter.drawRoundedRect(QRect(0,0,map.width(),map.height()),9,9);
    painter.end();

}
void ProgressBar::drawItemFirst()
{
    QPainter painter;
    painter.begin(&irregularMapFirst);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); //抗锯齿和使用平滑转换算法
    QBrush brush(QColor(0, 0, 255), Qt::SolidPattern);
    //使用画刷
    painter.setBrush(brush);
    static const QPointF points[5] = {
        QPointF(0,0),
        QPointF(irregularMapWidth - 20, 0),
        QPointF(irregularMapWidth,      irregularMapHeight/2),
        QPointF(irregularMapWidth - 20, irregularMapHeight),
        QPointF(0, irregularMapHeight),
    };
    //使用四个点绘制多边形
    painter.drawPolygon(points, 5);
    painter.end();

    irregularMapFirst2 = irregularMapFirst;


}
void ProgressBar::drawItem(void)
{
    irregularMap.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&irregularMap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); //抗锯齿和使用平滑转换算法
    irregularMap.fill(Qt::transparent);
    QBrush brush(QColor(0, 0, 255), Qt::SolidPattern);
    //使用画刷
    painter.setBrush(brush);
    static const QPointF points[6] = {
        QPointF(0,0),
        QPointF(irregularMapWidth - 20, 0),
        QPointF(irregularMapWidth,      irregularMapHeight/2),
        QPointF(irregularMapWidth - 20, irregularMapHeight),
        QPointF(0, irregularMapHeight),
        QPointF(20,irregularMapHeight/2),
    };
    //使用四个点绘制多边形
    painter.drawPolygon(points, 6);
    painter.end();

    painter.begin(&irregularMap2);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); //抗锯齿和使用平滑转换算法
    irregularMap2.fill(Qt::transparent);
    brush.setColor(QColor(0,255,255));
    painter.setBrush(brush);
    painter.drawPolygon(points, 6);
    painter.end();

}
void ProgressBar::drawItemEnd()
{
    QPainter painter;
    painter.begin(&irregularMapEnd);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); //抗锯齿和使用平滑转换算法
    QBrush brush(QColor(0, 0, 255), Qt::SolidPattern);
    //使用画刷
    painter.setBrush(brush);
    static const QPointF points[5] = {
        QPointF(0,0),
        QPointF(irregularMapWidth, 0),
        QPointF(irregularMapWidth,      irregularMapHeight),
        QPointF(0, irregularMapHeight),
        QPointF(20, irregularMapHeight/2),
    };
    //使用四个点绘制多边形
    painter.drawPolygon(points, 5);
    painter.end();


}
void ProgressBar::fillMap()
{
    QPainter painter;
    painter.begin(&map);
    painter.drawPixmap(0,0,irregularMapFirst2);

    int intx;
    for(int i = 1;i < itemNumber-1;i++)
    {
        intx = irregularMapWidth*i - 10*i;
        painter.drawPixmap(intx,0,irregularMap);
        intx = intx+irregularMapWidth;
    }
    painter.drawPixmap(map.width()-irregularMapWidth,0,irregularMapEnd);
    painter.end();

}
void ProgressBar::fillMapUpdate(QPixmap tmpmap)
{
    QPainter painter;
    painter.begin(&map);
    painter.drawPixmap(0,0,irregularMapFirst);

//    int intx;
//    for(int i = 1;i < itemNumber-1;i++)
//    {
//        intx = irregularMapWidth*i - 10*i;
//        painter.drawPixmap(intx,0,tmpmap);
//        intx = intx+irregularMapWidth;
//    }
    painter.drawPixmap(map.width()-irregularMapWidth,0,irregularMapEnd);
    painter.end();

}

void ProgressBar::setProgressValue(double value)
{
    maptemp = map;
    irregularMapFirst2 =  irregularMapFirst;
    QPainter painter;
    int tmpValue = (int)value;
    double valueDot = value - tmpValue;
    double drawWidth = 0;
    /*填充第一个不规则图像*/
    if(tmpValue < 1)
    {
        painter.begin(&irregularMapFirst2);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); //抗锯齿和使用平滑转换算法
        QBrush brush(QColor(0, 255, 255), Qt::SolidPattern);
        //使用画刷
        painter.setBrush(brush);
        if(tmpValue < 1)
        {
            drawWidth = (irregularMapWidth-20)*valueDot;

        }
        else{
            drawWidth = irregularMapWidth -20;
        }
        QPointF points[5] = {
            QPointF(0,0),
            QPointF(drawWidth - 0, 0),
            QPointF(drawWidth+20,      irregularMapHeight/2),
            QPointF(drawWidth - 0, irregularMapHeight),
            QPointF(0, irregularMapHeight),
        };
        painter.drawPolygon(points, 5);
        painter.end();

        fillMap();
    }
    /*填充中间的不规则图像*/
    else if(tmpValue < (itemNumber-1))
    {
        /*1:填满第一个不规则图像*/
        painter.begin(&irregularMapFirst2);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        QBrush brush(QColor(0, 255, 255), Qt::SolidPattern);
        //使用画刷
        painter.setBrush(brush);
        QPointF points[5] = {
            QPointF(0,0),
            QPointF(irregularMapWidth - 20, 0),
            QPointF(irregularMapWidth,      irregularMapHeight/2),
            QPointF(irregularMapWidth - 20, irregularMapHeight),
            QPointF(0, irregularMapHeight),
        };
        painter.drawPolygon(points, 5);
        painter.end();
        painter.begin(&maptemp);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        painter.drawPixmap(0,0,irregularMapFirst2);
        painter.end();

        /*填充中间的不规则图像*/
        painter.begin(&maptemp);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        int intx;
        int i;
        for(i = 1;i < tmpValue;i++)
        {
            intx = irregularMapWidth*i - 10*i;
            painter.drawPixmap(intx,0,irregularMap2);
            intx = intx+irregularMapWidth;
        }
        if(valueDot != 0)
        {
            painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); //抗锯齿和使用平滑转换算法
            brush.setColor(QColor(0, 255, 255));
            //使用画刷
            painter.setBrush(brush);
            intx = irregularMapWidth*i - 10*i;
            drawWidth = (irregularMapWidth-20)*valueDot;
            double intxx = drawWidth + intx;
            QPointF points2[6] = {
                QPointF(intx,0),
                QPointF(intxx - 0, 0),
                QPointF(intxx+20,      irregularMapHeight/2),
                QPointF(intxx - 0, irregularMapHeight),
                QPointF(intx, irregularMapHeight),
                QPointF(intx+20,irregularMapHeight/2),
            };
            //使用四个点绘制多边形
            painter.drawPolygon(points2, 6);

        }
        painter.end();


    }
    else
    {
        /*1:填满第一个不规则图像*/
        painter.begin(&irregularMapFirst2);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        QBrush brush(QColor(0, 255, 255), Qt::SolidPattern);
        //使用画刷
        painter.setBrush(brush);
        const QPointF points[5] = {
            QPointF(0,0),
            QPointF(irregularMapWidth - 20, 0),
            QPointF(irregularMapWidth,      irregularMapHeight/2),
            QPointF(irregularMapWidth - 20, irregularMapHeight),
            QPointF(0, irregularMapHeight),
        };
        painter.drawPolygon(points, 5);
        painter.end();
        painter.begin(&maptemp);
        painter.drawPixmap(0,0,irregularMapFirst2);
        painter.end();

        int intx;
        painter.begin(&maptemp);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        if(value < itemNumber)
        {
            /*2:填充中间的不规则图像*/
            int i;
            for(i = 1;i < tmpValue ;i++)
            {
                intx = irregularMapWidth*i - 10*i;
                painter.drawPixmap(intx,0,irregularMap2);
                intx = intx+irregularMapWidth;
            }

        }


        /*3:最后一个图像*/
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); //抗锯齿和使用平滑转换算法
        brush.setColor(QColor(0, 255, 255));
        painter.setBrush(brush);
        intx = maptemp.width() - irregularMapWidth;
        if(value <= itemNumber)
        {
            double intxx = irregularMapWidth*valueDot+intx;
            const QPointF points3[6] = {
                QPointF(intx,0),
                QPointF(intxx, 0),
                QPointF(intxx+20,      irregularMapHeight/2),
                QPointF(intxx, irregularMapHeight),
                QPointF(intx, irregularMapHeight),
                QPointF(intx+20, irregularMapHeight/2),
            };
            //使用四个点绘制多边形
            painter.drawPolygon(points3, 6);

        }
        else if(((value- itemNumber)< 1e-2)&&(itemNumber < value)){
            intx = maptemp.width()-irregularMapWidth;
            const QPointF points3[5] = {
                QPointF(intx,0),
                QPointF(intx+irregularMapWidth, 0),
                QPointF(intx+irregularMapWidth,      irregularMapHeight),
                QPointF(intx, irregularMapHeight),
                QPointF(intx+20, irregularMapHeight/2),
            };
            //使用四个点绘制多边形
            painter.drawPolygon(points3, 5);
        }

        painter.end();
    }
    update();
}
