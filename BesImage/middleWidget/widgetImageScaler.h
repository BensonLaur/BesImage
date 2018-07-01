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
#include "baseWidget.h"

//参考 https://www.cnblogs.com/lifexy/p/9057046.html

class WidgetImageScaler:public baseWidget
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

   //设置显示的图片（显示集合将只包含当前设置图片）
   void SetImage(QString imagePath);
   void SetImage(QImage image);
   void SetImage(QPixmap pixmap);

   //设置显示图片集合(curIndex要显示的图片下标)
   void SetImageSet(QVector<QString> vecPath, int curIndex = 0);
   void SetImageSet(QVector<QImage> vecImage, int curIndex = 0);
   void SetImageSet(QVector<QPixmap> vecPixmap, int curIndex = 0);

   bool ShowSelImage(int indexSel); //显示选中的图片

   bool HasNextImage();             //查询当前是否有下一张图片
   bool HasPreImage();              //查询当前是否有上一张图片

public slots:
   bool ShowNextImage();            //显示下一张图片
   bool ShowPreImage();             //显示上一张图片

private:
   void initImageDataWithPixmap(const QPixmap& pixmap);        //初始化显示图像的数据
   bool ScaleBigImageToFit();                                  //缩放较大的图片适应窗口

 protected:

   //处理事件
   virtual bool event(QEvent * event);
   virtual void wheelEvent(QWheelEvent* e);     //鼠标滑轮事件
   virtual void paintEvent(QPaintEvent *event);
   virtual void resizeEvent(QResizeEvent *event);


private:
   QPixmap m_pixmap;                //传入的图像数据
   QPixmap m_pixmapToshow;          //中间变量

   QVector<QPixmap> m_vecPixmap;    //储存的图像集合
   int m_indexCurPixmap;            //当前显示的图片下标

   /* 显示图像相关计算参数 */
    int action;             //动作(放大,缩小,移动...)
    int pixW;               //图片宽
    int pixH;               //图片高

    QRect Paint;            //绘画区域

    double ratio;            //比例
    QPoint offset;          //一次的图片偏移值
    QPoint Alloffset;       //总偏移
    QLabel label;           //缩放比例提示标签

};

#endif // WIDGET_IMAGE_SCALER_H
