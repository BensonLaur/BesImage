#include "basewindow.h"
#include<QGridLayout>
#include<QPushButton>
#include<QDebug>
#include<QLineEdit>

baseWindow::baseWindow(QWidget *parent)
    : AbsFrameLessAutoSize(parent),
     m_mainwid(this)
{
    m_border=8;
    setMinimumSize(550,440);
    setWindowFlags(Qt::FramelessWindowHint);

    setAttribute(Qt::WA_TranslucentBackground,true);

    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    m_mainwid.setAutoFillBackground(true);
    QGridLayout *lyout=new QGridLayout;
    lyout->addWidget(&m_mainwid);
    lyout->setContentsMargins(4,4,4,4);
    setLayout(lyout);
}
void baseWindow::paintEvent(QPaintEvent *e)
{
    AbsFrameLessAutoSize::paintEvent(e);
    QPainter painter(this);
 // draw shadow margin

    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(9, 9, this->width()-18, this->height()-18);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color(0, 0, 0, 50);
    for(int i=0; i<9; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(9-i, 9-i, this->width()-(9-i)*2, this->height()-(9-i)*2);
        color.setAlpha(150 - qSqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }
}
////////////////////////////////////////////////////////////////////
Widget::Widget(QWidget *parent):QWidget(parent)
{
    m_BGFillMode = BG_FILL_MODE_KEEP_ASPECT_RATIO_AND_FULL;
}

void Widget::SetBackgroundFillMode(BGFillMode fillMode)
{
    m_BGFillMode = fillMode;
}

void Widget::setCurBGPic(const QString &strPix)
{
    m_netPic.load(strPix);
    update();
}

void Widget::clearBg()
{
    m_netPic.load("");
    update();
}


void Widget::setSkin(const QString &skin)
{
    m_skinPic.load(skin);
    m_curPixPath=skin;
    update();
}
void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    switch(m_BGFillMode)
    {
    case BG_FILL_MODE_KEEP_ASPECT_RATIO_AND_FULL:   //保持纵横比，且填满窗口
        {
            float d =(float)m_netPic.height()/m_netPic.width();
            int h=d*width();
            int w=height()/d;
            if(h<height())//如果图片高度小于窗口高度
                painter.drawPixmap(0,0,w,height(),m_netPic);
            else
                painter.drawPixmap(0,0,width(),h,m_netPic);
        }
        break;
    case BG_FILL_MODE_IGNORE_ASPECT_RATIO_AND_FULL:  //忽略纵横比，拉升填满窗口
        {
            QPixmap pixmapToShow = m_netPic;
            pixmapToShow.scaled(width(), height(),Qt::IgnoreAspectRatio);
            painter.drawPixmap(0,0,width(),height(),pixmapToShow);
        }
        break;
    case BG_FILL_MODE_ORIGINAL_SIZE_SINGLE:  //忽略纵横比，拉升填满窗口
        {
            QPixmap pixmapToShow = m_netPic;
            pixmapToShow.scaled(width(), height(),Qt::IgnoreAspectRatio);
            painter.drawPixmap(0,0,pixmapToShow);
        }
        break;

     case BG_FILL_MODE_ORIGINAL_SIZE_FULL:   //使用原来尺寸，不填满窗口时，重复图片
        {
            QPixmap pixmapToShow = m_netPic;
            pixmapToShow.scaled(width(), height(),Qt::IgnoreAspectRatio);

            for(int i =0; i *pixmapToShow.width() < width(); i++)
            {
                for(int j=0; j*pixmapToShow.height() < height(); j++)
                    painter.drawPixmap(i * pixmapToShow.width(),j * pixmapToShow.height(),pixmapToShow);
            }
        }
        break;

    default:
        break;
    }

}


