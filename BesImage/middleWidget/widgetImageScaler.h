#ifndef WIDGET_IMAGE_SCALER_H
#define WIDGET_IMAGE_SCALER_H

#include <QObject>
#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QPainter>

//参考 https://www.cnblogs.com/lifexy/p/9057046.html

class WidgetImageScaler:public QWidget
{
    Q_OBJECT
public:
   explicit WidgetImageScaler(QWidget *parent);

   void SetImage(QImage image);
   void SetImage(QPixmap pixmap);
   void SetImage(QString imagePath);

   void initLayout();


   bool event(QEvent * event);
   void wheelEvent(QWheelEvent* e);     //鼠标滑轮事件

   void paintEvent(QPaintEvent *event);

   QPixmap m_pixmap;
   QPixmap m_pixmapToshow;

    int action;          //动作(放大,缩小,移动...)
    int pixW;            //图片宽
    int pixH;            //图片高

    QRect Paint;         //绘画区域

    float ratio;                //比例
    QPoint offset;              //一次的图片偏移值
    QPoint Alloffset;           //总偏移
    QLabel label;

    enum  Type {
            None          = 0,
            Amplification ,
            Shrink,
            Lift,
            Right,
            Up,
            Down,
            Move
        };
};

#endif // WIDGET_IMAGE_SCALER_H
