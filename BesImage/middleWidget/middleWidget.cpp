#include "middleWidget.h"
#include<QPushButton>
#include<QLabel>
#include<QHBoxLayout>
#include<QDebug>
#include<QFile>
#include<QApplication>


MiddleWidget::MiddleWidget(QWidget *parent) : baseWidget(parent),
    pageSelect(this),
    pageShow(this),
    m_animation(this,"m_x"),
    m_Widanimation(this,"geometry")
{

    initWidget();
    initAnimation();

    connect(&pageSelect, SIGNAL(OnSelectOnePath(QString)), &pageShow, SLOT(SetOneImageForShow(QString)));
    connect(&pageSelect, SIGNAL(OnSelectOnePath(QString)), this, SLOT(SwitchToShowPage()));

    connect(&pageSelect, SIGNAL(OnSelectBunchPath(QVector<QString>,int)), &pageShow, SLOT(SetBunchImageForShow(QVector<QString>,int)));
    connect(&pageSelect, SIGNAL(OnSelectBunchPath(QVector<QString>,int)), this, SLOT(SwitchToShowPage()));

    connect(&pageSelect, SIGNAL(OnSelectIndexInSet(int)), &pageShow, SLOT(ShowImageInSetShowing(int)));
    connect(&pageSelect, SIGNAL(OnSelectIndexInSet(int)), this, SLOT(SwitchToShowPage()));



}

void MiddleWidget::initWidget()
{
    QVBoxLayout *vlyout=new QVBoxLayout;
    m_stackwid.setFrameShadow(QFrame::Plain);
    m_stackwid.setFrameShape(QFrame::NoFrame);
    m_stackwid.addWidget(&pageSelect);
    m_stackwid.addWidget(&pageShow);
    m_stackwid.setContentsMargins(0,0,0,0);

    m_btn[0]=new stackButton(":/image/middlewidget/btn_music (1).png",":/image/middlewidget/btn_music (2).png",":/image/middlewidget/btn_music (3).png",this);
    m_btn[1]=new stackButton(":/image/middlewidget/btn_cloud (1).png",":/image/middlewidget/btn_cloud (2).png",":/image/middlewidget/btn_cloud (3).png",this);

    m_btn[0]->setFixedHeight(40);
    m_btn[1]->setFixedHeight(40);

    QHBoxLayout *hlyout=new QHBoxLayout;
    hlyout->addWidget(m_btn[0]);
    hlyout->addWidget(m_btn[1]);
    hlyout->setContentsMargins(0,0,0,0);
    hlyout->setSpacing(0);

    vlyout->addLayout(hlyout);
    vlyout->addWidget(&m_stackwid);
    vlyout->setSpacing(0);
    vlyout->setContentsMargins(0,0,0,0);
    setLayout(vlyout);

    for(int i=0;i<2;i++)
    {
        m_btn[i]->setObjectName(QString::number(i));
        connect(m_btn[i],SIGNAL(pressed()),this,SLOT(slot_btn()));
    }

    connect(&m_stackwid,SIGNAL(currentChanged(int)),this,SLOT(slot_changeButtonSelected(int)));

    m_stackwid.setCurrentIndex(0);//选中第一个stackwidget
    m_btn[0]->setselected(true);
}


void MiddleWidget::initAnimation()
{
    m_pix=QPixmap(":/image/middlewidget/indicator.png");
    m_index=-1;
    m_preindex=-1;
    m_preItem=0;
    m_x=0;
    m_isAnima=true;

    m_animation.setDuration(200);
    m_stackwid.setCurrentIndex(0);
    connect(&m_animation,SIGNAL(finished()),this,SLOT(slot_finished()));

    m_Widanimation.setTargetObject(&m_stackwid);
    m_Widanimation.setDuration(200);
}

void MiddleWidget::slot_btn()
{
    m_preindex=m_stackwid.currentIndex();
    m_stackwid.setCurrentIndex(sender()->objectName().toInt());
}

void MiddleWidget::slot_changeButtonSelected(int index)
{
    m_isAnima=true;
    m_index=index;
    m_animation.setStartValue(m_preindex*m_btn[0]->width());
    m_animation.setEndValue(index*m_btn[0]->width());
    m_animation.start();

    for(int i=0;i<2;i++)
    {
        if(i==index)
        {
           m_btn[index]->setselected(true);
        }
        else
        {
          m_btn[i]->setselected(false);
        }
    }

    if(index>m_preItem)
    {
        m_Widanimation.setTargetObject(&m_stackwid);
        m_Widanimation.setStartValue(QRect(m_stackwid.width(),40,m_stackwid.width(),m_stackwid.height()));
        m_Widanimation.setEndValue(QRect(0,40,m_stackwid.width(),m_stackwid.height()));
        m_Widanimation.start();
    }
    if(index<m_preItem)
    {
        m_Widanimation.setTargetObject(&m_stackwid);
        m_Widanimation.setStartValue(QRect(-m_stackwid.width(),40,m_stackwid.width(),m_stackwid.height()));
        m_Widanimation.setEndValue(QRect(0,40,m_stackwid.width(),m_stackwid.height()));
        m_Widanimation.start();
    }
    m_preItem=index;
}

void MiddleWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(Qt::transparent);
    p.setBrush(QColor(255,255,255,100));//刷透明区域
    p.drawRect(-1,-1,width(),height()+1);
    p.setPen(QColor(230,230,230));

   if(m_isAnima)
    {
       if(m_isDrawVerticalLine)
       p.drawLine(width()-1,0,width()-1,height());//vertical line

        p.drawLine(0,m_btn[0]->y()+m_btn[0]->height()-1,m_x+(m_btn[0]->width()-m_pix.width())/2-1,m_btn[0]->y()+m_btn[0]->height()-1);//first line
        p.drawLine(m_x+(m_btn[0]->width()-m_pix.width())/2+m_pix.width(),m_btn[0]->y()+m_btn[0]->height()-1,width(),m_btn[0]->y()+m_btn[0]->height()-1);//second line
        p.drawPixmap(m_x+(m_btn[0]->width()-m_pix.width())/2,m_btn[0]->y()+m_btn[0]->height()-m_pix.height()+1,m_pix);
    }
    else
    {
       if(m_isDrawVerticalLine)
       p.drawLine(width()-1,0,width()-1,height());

       p.drawLine(0,m_btn[0]->y()+m_btn[0]->height()-1,m_index*m_btn[0]->width()+(m_btn[0]->width()-m_pix.width())/2-1,m_btn[0]->y()+m_btn[0]->height()-1);
       p.drawLine(m_index*m_btn[0]->width()+(m_btn[0]->width()-m_pix.width())/2+m_pix.width(),m_btn[0]->y()+m_btn[0]->height()-1,width(),m_btn[0]->y()+m_btn[0]->height()-1);
       p.drawPixmap(m_index*m_btn[0]->width()+(m_btn[0]->width()-m_pix.width())/2,m_btn[0]->y()+m_btn[0]->height()-m_pix.height()+1,m_pix);
    }
}

int MiddleWidget::x() const
{
    return m_x;
}

void MiddleWidget::setX(int x)
{
    m_x = x;
    update();
}

