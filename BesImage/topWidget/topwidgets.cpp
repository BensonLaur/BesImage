#include "topwidgets.h"
#include<QPushButton>
#include<QLabel>
#include<QHBoxLayout>
#include<QDebug>
#include<QFile>
#include<QApplication>


TopWidgets::TopWidgets(QWidget *parent) :
    baseWidget(parent)
  ,m_btnexit(this)
  ,m_btnmini(this)
    ,m_toolbar(this)
{
    setStyleSheet("TopWidgets{background:transparent;}");
    setMouseTracking(true);
    initWidget();
}

bool TopWidgets::eventFilter(QObject *o, QEvent *e)
{
    return QObject::eventFilter(o,e);
}


void TopWidgets::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit(OnHeaderMouseDoubleClickEvent(event));
}

void TopWidgets::initWidget()
{
    setMinimumSize(500,90);
    setMaximumSize(1920,90);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    QVBoxLayout *hmainyout=new QVBoxLayout;

    QHBoxLayout *hHeaderlyout=new QHBoxLayout;

    QHBoxLayout *hyout1=new QHBoxLayout;

    m_btnexit.setFixedSize(18,18);
    m_btnmini.setFixedSize(16,16);

    m_btnexit.setObjectName("m_btnexit");
    m_btnmini.setObjectName("m_btnmini");

    m_btnexit.setStyleSheet("QPushButton{border-image:url(:/image/topwidget/btn_close (1).png);}"
                             "QPushButton::hover{border-image:url(:/image/topwidget/btn_close (2).png);}"
                             "QPushButton::pressed{border-image:url(:/image/topwidget/btn_close (3).png);}");
    m_btnmini.setStyleSheet("QPushButton{border-image:url(:/image/topwidget/btn_mini (1).png);}"
                             "QPushButton::hover{border-image:url(:/image/topwidget/btn_mini (2).png);}"
                             "QPushButton::pressed{border-image:url(:/image/topwidget/btn_mini (3).png);}");

    hyout1->addWidget(&m_btnmini);
    hyout1->addWidget(&m_btnexit);
    hyout1->setSpacing(12);

   //hHeaderlyout->addSpacerItem(new QSpacerItem(80,30,QSizePolicy::Maximum));//设置它最大膨胀！！！
    hHeaderlyout->addSpacerItem(new QSpacerItem(110,50,QSizePolicy::Expanding));//膨胀
    hHeaderlyout->addLayout(hyout1);
    hHeaderlyout->setSpacing(0);
    hHeaderlyout->setContentsMargins(16,0,15,0);

    hmainyout->setSpacing(0);
    hmainyout->addLayout(hHeaderlyout);
    hmainyout->addWidget(&m_toolbar);
    hmainyout->setContentsMargins(0,0,0,0);

    setLayout(hmainyout);
}
