﻿#include "myPushButton.h"
#include<QPainter>
#include<QDebug>
#include<QFontMetrics>
#include<QToolTip>

#include"mySlider.h"

myPushButton::myPushButton(QWidget*parent):QPushButton(parent)
{
    setCursor(Qt::PointingHandCursor);
    setFlat(true);
    setStyleSheet("QPushButton{background:transparent;}");
}
myPushButton::myPushButton(const QString& str, QWidget *parent):QPushButton(str,parent)
{
     setCursor(Qt::PointingHandCursor);
     setFlat(true);
     setStyleSheet("QPushButton{background:transparent;}");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
volButton::volButton(const QString& normal,const QString& hover,const QString& pressed,QWidget*parent):QPushButton(parent)//5个连一串
{
    m_partnerslider=NULL;
    m_isenter=false;
    m_index=0;
    m_isvolempty=100;
    m_savevol=100;
    setCursor(Qt::PointingHandCursor);

    QPixmap pixTemp(normal);
    for(int i=0;i<5;i++)
    m_listnormal<<pixTemp.copy(i*(pixTemp.width()/5),0,pixTemp.width()/5,pixTemp.height());

    pixTemp.load(hover);
    for(int i=0;i<5;i++)
    m_listhover<<pixTemp.copy(i*(pixTemp.width()/5),0,pixTemp.width()/5,pixTemp.height());

    pixTemp.load(pressed);
    for(int i=0;i<5;i++)
    m_listpressed<<pixTemp.copy(i*(pixTemp.width()/5),0,pixTemp.width()/5,pixTemp.height());


}
void volButton::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    if(!m_isenter)
    p.drawPixmap((width()-m_listnormal.at(0).width())/2,(height()-m_listnormal.at(0).height())/2,m_listnormal.at(m_index));
    else
    {
        p.drawPixmap((width()-m_listhover.at(0).width())/2,(height()-m_listhover.at(0).height())/2,m_listhover.at(m_index));
    }

}
void volButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        QPushButton::mousePressEvent(e);
    }
}
void volButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {

        if(this->contentsRect().contains(mapFromGlobal(QCursor::pos())))
        {
            if(m_isvolempty==0)//如果没有音量就 设置一个
            {
                emit setMute(m_savevol);
            }
            else//如果有音量 设置音量为0;
            {
                m_savevol=m_partnerslider->value();
                emit setMute(0);
            }
        }
       QPushButton::mouseReleaseEvent(e);
    }
}

void volButton::setButtonPixmap(int value)
{
    m_isenter=false;
    if(value==0)
        m_index=4;
    if(value>2&&value<=30)
       m_index=1;
    if(value>30)
       m_index=2;
    update();
  m_isvolempty=value;//判断值为0;
}
void volButton::enterEvent(QEvent *)
{
    m_isenter=true;
    update();
}
void volButton::leaveEvent(QEvent *)
{
    m_isenter=false;
    update();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
stackButton::stackButton(const QString& pixnormal,const QString& pixhover,const QString& pixsel,QWidget*parent)
    :QPushButton(parent)
    ,m_pixnormal(pixnormal)
    , m_pixhover(pixhover)
    ,m_pixselected(pixsel)
    ,m_index(-1)
    ,m_enter(false)
    ,m_pressed(false)
{
    setCursor(Qt::PointingHandCursor);
    setFlat(true);
}
void stackButton::paintEvent(QPaintEvent *e)
{
    QPushButton::paintEvent(e);
    QPainter p(this);
    if(!m_enter&&!m_pressed)//初始化
    p.drawPixmap((width()-m_pixnormal.width())/2,(height()-m_pixnormal.height())/2,m_pixnormal);

    if(m_enter&&!m_pressed)//未选中进入
     p.drawPixmap((width()-m_pixhover.width())/2,(height()-m_pixhover.height())/2,m_pixhover);

    if(m_pressed)//选中
     p.drawPixmap((width()-m_pixselected.width())/2,(height()-m_pixselected.height())/2,m_pixselected);
}
void stackButton::setselected(bool sel)//用于控制pix显示
{
    m_pressed=sel;
    update();
}
void stackButton::mousePressEvent(QMouseEvent *e)
{
    QPushButton::mousePressEvent(e);
    if(e->button()==Qt::LeftButton)
    {
        m_pressed=true;
        update();
    }
}
void stackButton::enterEvent(QEvent *e)
{
    QPushButton::enterEvent(e);
    m_enter=true;
    update();
}
void stackButton::leaveEvent(QEvent *e)
{
    QPushButton::leaveEvent(e);
    m_enter=false;
    update();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
leftPixButton::leftPixButton(QString pixnormal, QString pixhover, QWidget *parent)
    :QPushButton(parent)
    ,m_enter(false)
    ,m_pressed(false)
    ,m_pixnormal(pixnormal)
    ,m_pixhover(pixhover)

{}
void leftPixButton::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    if(!m_enter)//初始化
    p.drawPixmap(44,(height()-m_pixnormal.height())/2,m_pixnormal);

    if(m_enter)//hover
     p.drawPixmap(44,(height()-m_pixhover.height())/2,m_pixhover);

}
void leftPixButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        m_enter=true;
        update();
    }
    QPushButton::mousePressEvent(e);
}
void leftPixButton::enterEvent(QEvent *)
{
    m_enter=true;
    update();
}
void leftPixButton::leaveEvent(QEvent *)
{
    m_enter=false;
    update();
}
//////////////////////////////////////////////////////////////////////////////////////
volButton2::volButton2(const QString& normal,const QString& hover,const QString& pressed,QWidget*parent)
    :QPushButton(parent)//5个连一串
   , m_partnerslider(NULL)
    , m_isenter(false)
    , m_savevol(100)
    , m_isvolempty(100)
    , m_index(0)
{
    setCursor(Qt::PointingHandCursor);

    QPixmap pixTemp(normal);
    for(int i=0;i<5;i++)
    m_listnormal<<pixTemp.copy(i*(pixTemp.width()/5),0,pixTemp.width()/5,pixTemp.height());

    pixTemp.load(hover);
    for(int i=0;i<5;i++)
    m_listhover<<pixTemp.copy(i*(pixTemp.width()/5),0,pixTemp.width()/5,pixTemp.height());

    pixTemp.load(pressed);
    for(int i=0;i<5;i++)
    m_listpressed<<pixTemp.copy(i*(pixTemp.width()/5),0,pixTemp.width()/5,pixTemp.height());


    m_timer.setSingleShot(true);
    connect(&m_timer,SIGNAL(timeout()),this,SIGNAL(sig_hideVolWidget()));
}

void volButton2::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    if(!m_isenter)
    p.drawPixmap((width()-m_listnormal.at(0).width())/2,(height()-m_listnormal.at(0).height())/2,m_listnormal.at(m_index));
    else
    {
        p.drawPixmap((width()-m_listhover.at(0).width())/2,(height()-m_listhover.at(0).height())/2,m_listhover.at(m_index));
    }
}
void volButton2::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        QPushButton::mousePressEvent(e);
    }
}
void volButton2::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {

        if(this->contentsRect().contains(mapFromGlobal(QCursor::pos())))
        {
            if(m_isvolempty==0)//如果没有音量就 设置一个
            {
                emit setMute(m_savevol);
            }
            else//如果有音量 设置音量为0;
            {
                m_savevol=m_partnerslider->value();
                emit setMute(0);
            }
        }
       QPushButton::mouseReleaseEvent(e);
    }
}

void volButton2::setButtonPixmap(int value)
{
    m_isenter=false;
    if(value==0)
        m_index=4;
    if(value>2&&value<=30)
       m_index=1;
    if(value>30)
       m_index=2;
    update();
  m_isvolempty=value;//判断值为0;
}
void volButton2::enterEvent(QEvent *)
{
    m_isenter=true;
    m_timer.stop();
    update();
}
void volButton2::leaveEvent(QEvent *)
{
    m_isenter=false;
    m_timer.start(500);
    update();
}
