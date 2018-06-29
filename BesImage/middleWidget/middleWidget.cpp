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

    connect(&pageSelect, SIGNAL(OnSelectPath(QString)), &pageShow, SLOT(SetImageForShow(QString)));
    connect(&pageSelect, SIGNAL(OnSelectPath(QString)), this, SLOT(SwitchToShowPage()));
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
