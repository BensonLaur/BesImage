#include "topwidgets.h"
#include<QPushButton>
#include<QLabel>
#include<QHBoxLayout>
#include<QDebug>
#include<QFile>
#include<QApplication>


TopWidgets::TopWidgets(QWidget *parent) : baseWidget(parent)
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
    setMinimumSize(500,50);
    setMaximumSize(1920,50);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    QHBoxLayout *hmainyout=new QHBoxLayout;

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

   //hmainyout->addSpacerItem(new QSpacerItem(80,30,QSizePolicy::Maximum));//设置它最大膨胀！！！
    hmainyout->addSpacerItem(new QSpacerItem(110,30,QSizePolicy::Expanding));//膨胀
    hmainyout->addLayout(hyout1);
    hmainyout->setSpacing(0);
    hmainyout->setContentsMargins(16,0,15,0);
    setLayout(hmainyout);
}
