#include "widgetImageScaler.h"

WidgetImageScaler::WidgetImageScaler(QWidget *parent):
    QWidget(parent),
    Paint(10,10,810,810),
    Alloffset(0,0),
    label("100%",this)
{
    ratio= 1.0;             //初始化图片缩放比例
    action = Type::None;
    pixW = 985;            //设置图片尺寸为985*740
    pixH = 740;

}

void WidgetImageScaler::SetImage(QImage image)
{
    m_pixmap = QPixmap::fromImage(image);
}

void WidgetImageScaler::SetImage(QPixmap pixmap)
{
    m_pixmap = pixmap;
}

void WidgetImageScaler::SetImage(QString imagePath)
{
    m_pixmap = QPixmap::fromImage(QImage(imagePath));
}

void WidgetImageScaler::initLayout()
{

}


bool WidgetImageScaler::event(QEvent * event)
{
//    static bool press=false;
//    static QPoint PreDot;

//    if(event->type() == QEvent::MouseButtonPress )
//    {
//        QMouseEvent *mouse = dynamic_cast<QMouseEvent* >(event);

//        //判断鼠标是否是左键按下,且鼠标位置是否在绘画区域
//        if(mouse->button()==Qt::LeftButton &&Paint.contains(mouse->pos()))
//        {
//            press=true;
//            QApplication::setOverrideCursor(Qt::OpenHandCursor); //设置鼠标样式

//            PreDot = mouse->pos();
//        }
//    }
//    else if(event->type() == QEvent::MouseButtonRelease)
//    {
//        QMouseEvent *mouse = dynamic_cast<QMouseEvent* >(event);

//        //判断鼠标是否是左键释放,且之前是在绘画区域
//        if(mouse->button()==Qt::LeftButton && press )
//        {
//            QApplication::setOverrideCursor(Qt::ArrowCursor); //改回鼠标样式
//            press=false;
//        }
//    }

//    if(event->type() == QEvent::MouseMove)              //移动图片
//    {
//       if(press)
//       {
//          QMouseEvent *mouse = dynamic_cast<QMouseEvent* >(event);

//          offset.setX(mouse->x() - PreDot.x());
//          offset.setY(mouse->y() - PreDot.y());
//          PreDot = mouse->pos();
//          action = Type::Move;
//          this->update();
//       }
//     }
    return QWidget::event(event);
}

//鼠标滑轮事件
void WidgetImageScaler::wheelEvent(QWheelEvent* e)
{
//    if (e->delta()>0) {      //上滑,缩小

//        action=Type::Shrink;
//        this->update();

//     } else {                    //下滑,放大
//         action=Type::Amplification;
//         this->update();
//     }

//     e->accept();
}

void WidgetImageScaler::paintEvent(QPaintEvent *event)
{
//    QPainter painter(this);
//     int NowW = ratio *pixW;
//     int NowH = ratio *pixH;

//   if(action==Type::Amplification)           //缩小
//   {
//         ratio-=0.1*ratio;
//       if(ratio<0.018)
//         ratio = 0.01;

//       /*显示比例*/
//       QString str;
//       str.sprintf("%.0f%",ratio*100);
//       label.setText(str) ;
//   }
//   else  if(action==Type::Shrink)           //放大
//   {

//        ratio+=0.1*ratio;
//      if(ratio>4.5)
//        ratio = 5.000;

//       /*显示比例*/
//       QString str;
//       str.sprintf("%.0f%",ratio*100);
//       label.setText(str);
//   }
//   if(action==Type::Amplification || action==Type::Shrink)      //更新图片
//   {
//     NowW = ratio *pixW;
//     NowH = ratio *pixH;
//     m_pixmapToshow = m_pixmap;                 //重新装载,因为之前的图片已经被缩放过
//     m_pixmapToshow = m_pixmapToshow.scaled(NowW, NowH,Qt::KeepAspectRatio);
//     action=Type::None;

//   }

//   if(action==Type::Move)                    //移动
//   {
//       int offsetx=Alloffset.x()+offset.x();
//       Alloffset.setX(offsetx);

//       int offsety=Alloffset.y()+offset.y();
//       Alloffset.setY(offsety);
//       action=Type::None;
//   }

//   if(abs(Alloffset.x())>=(Paint.width()/2 + NowW/2 -10))    //限制X偏移值
//   {
//       if(Alloffset.x()>0)
//           Alloffset.setX(Paint.width()/2 + NowW/2 -10);
//       else
//        Alloffset.setX(-Paint.width()/2 + -NowW/2 +10);
//   }
//   if(abs(Alloffset.y())>=(Paint.height()/2 + NowH/2 -10))    //限制Y偏移值
//   {
//       if(Alloffset.y()>0)
//           Alloffset.setY(Paint.height()/2 + NowH/2 -10);
//       else
//        Alloffset.setY(-Paint.height()/2 + -NowH/2 +10);

//   }

//   int x = Paint.width()/2 + Alloffset.x() -NowW/2;
//   if(x<0)
//       x=0;

//   int y = Paint.height()/2 + Alloffset.y() -NowH/2;
//   if(y<0)
//       y=0;

//   int  sx = NowW/2 - Paint.width()/2 - Alloffset.x();
//   if(sx<0)
//       sx=0;

//   int  sy = NowH/2 - Paint.height()/2 - Alloffset.y();
//   if(sy<0)
//       sy=0;

//   int w =(NowW - sx)>Paint.width()? Paint.width() : (NowW - sx);
//   if(w>(Paint.width()-x))
//       w = Paint.width()-x;

//   int h =(NowH - sy)>Paint.height()? Paint.height() : (NowH - sy);
//   if(h>(Paint.height()-y))
//       h = Paint.height()-y;

//     painter.drawRect(Paint.x()-1,Paint.y()-1,Paint.width()+1,Paint.height()+1); //画框
//     painter.drawTiledPixmap(x+Paint.x(),y+Paint.y(),w,h,m_pixmapToshow,sx,sy);             //绘画图形

}
