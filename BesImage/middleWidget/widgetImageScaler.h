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

	//图片操作类型
	enum  Type 
	{
		None = 0,
		Amplification,
		Shrink,
		Lift,
		Right,
		Up,
		Down,
		Move
	};

public:
   explicit WidgetImageScaler(QWidget *parent);

   //设置显示的图片
   void SetImage(QString imagePath);
   void SetImage(QImage image);
   void SetImage(QPixmap pixmap);

   void initLayout();

   //处理事件
   bool event(QEvent * event);
   void wheelEvent(QWheelEvent* e);     //鼠标滑轮事件
   void paintEvent(QPaintEvent *event);

private:
   QPixmap m_pixmap;			//传入的图像数据
   QPixmap m_pixmapToshow;		//中间变量

    int action;          //动作(放大,缩小,移动...)
    int pixW;            //图片宽
    int pixH;            //图片高

    QRect Paint;         //绘画区域

    float ratio;                //比例
    QPoint offset;              //一次的图片偏移值
    QPoint Alloffset;           //总偏移
    QLabel label;

};

#endif // WIDGET_IMAGE_SCALER_H
