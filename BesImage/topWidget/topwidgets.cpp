#include "topwidgets.h"
#include<QPushButton>
#include<QLabel>
#include<QHBoxLayout>
#include<QDebug>
#include<QFile>
#include<QApplication>
#include <QDir>

TopWidgets::TopWidgets(QWidget *parent) :
    baseWidget(parent)
  ,m_iconBlack(":/image/main/besimage-black.ico")
  ,m_iconWhite(":/image/main/besimage-white.ico")
  ,m_btnIcon(this)
  ,m_labelTitle(this)
  ,m_btnexit(this)
  ,m_btnmini(this)
    ,m_toolbar(this)
{
    setStyleSheet("TopWidgets{background:transparent;}");
    setMouseTracking(true);

    initWidget();
}

//设置运行目录相对路径Icon
void TopWidgets::SetIcon(QString iconBlackPath,QString iconWhitePath)
{
    //使用相对路径尝试构建出有效路径，如果无法构建出存在的文件路径，使用系统默认资源
    QString strBlackPath = ":/image/main/besimage-black.ico";

    if(QFile::exists(iconBlackPath))
        strBlackPath = iconBlackPath;
    else if(QFile::exists(QCoreApplication::applicationDirPath() +"/"+ iconBlackPath))
        strBlackPath = QCoreApplication::applicationDirPath() +"/"+ iconBlackPath;

    //使用相对路径尝试构建出有效路径，如果无法构建出存在的文件路径，使用系统默认资源
    QString strWhitePath = ":/image/main/besimage-white.ico";

    if(QFile::exists(iconWhitePath))
        strWhitePath = iconWhitePath;
    else if(QFile::exists(QCoreApplication::applicationDirPath() +"/"+ iconWhitePath))
        strWhitePath = QCoreApplication::applicationDirPath() +"/"+ iconWhitePath;

    SetIcon(QIcon(strBlackPath),QIcon(strWhitePath));
}


//设置黑色白色2个颜色的Icon
void TopWidgets::SetIcon(QIcon iconBlack, QIcon iconWhite)
{
    m_iconBlack = iconBlack;
    m_iconWhite = iconWhite;
}

//设置标题
void TopWidgets::SetTitle(QString title)
{
    m_labelTitle.setText(title);
}

//设置整体颜色白色或黑色
void TopWidgets::SetColorBlackOrWhite(bool setBlack)
{
    if(setBlack)
    {
        m_btnIcon.setIcon(m_iconBlack);
        m_labelTitle.setStyleSheet("QLabel{background:transparent;color:black;font-family:Microsoft Yahei;font-weight:bold;font-size:20px;}");
        m_btnexit.setStyleSheet("QPushButton{border-image:url(:/image/topwidget/btn_close_black(1).png);}"
                                 "QPushButton::hover{border-image:url(:/image/topwidget/btn_close_black(2).png);}"
                                 "QPushButton::pressed{border-image:url(:/image/topwidget/btn_close_black(3).png);}");
        m_btnmini.setStyleSheet("QPushButton{border-image:url(:/image/topwidget/btn_mini_black(1).png);}"
                                 "QPushButton::hover{border-image:url(:/image/topwidget/btn_mini_black(2).png);}"
                                 "QPushButton::pressed{border-image:url(:/image/topwidget/btn_mini_black(3).png);}");
    }
    else
    {
        m_btnIcon.setIcon(m_iconWhite);
        m_labelTitle.setStyleSheet("QLabel{background:transparent;color:white;font-family:Microsoft Yahei;font-weight:bold;font-size:20px;}");
        m_btnexit.setStyleSheet("QPushButton{border-image:url(:/image/topwidget/btn_close (1).png);}"
                                 "QPushButton::hover{border-image:url(:/image/topwidget/btn_close (2).png);}"
                                 "QPushButton::pressed{border-image:url(:/image/topwidget/btn_close (3).png);}");
        m_btnmini.setStyleSheet("QPushButton{border-image:url(:/image/topwidget/btn_mini (1).png);}"
                                 "QPushButton::hover{border-image:url(:/image/topwidget/btn_mini (2).png);}"
                                 "QPushButton::pressed{border-image:url(:/image/topwidget/btn_mini (3).png);}");
    }
}


void TopWidgets::initWidget()
{
    setMinimumSize(500,90);
    setMaximumSize(1920,90);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    QVBoxLayout *hmainyout=new QVBoxLayout;

    QHBoxLayout *hHeaderlyout=new QHBoxLayout;

    ////////////////////////////////////////////////////////
    /// \brief hyout1
    ///
    QHBoxLayout *hyout1=new QHBoxLayout;

    m_btnIcon.setIcon(QIcon(":/image/main/besimage-black.ico"));
    m_btnIcon.setIconSize(QSize(32,32));
    m_labelTitle.setText("BesImage");
    m_labelTitle.setStyleSheet("QLabel{background:transparent;color:black;font-family:Microsoft Yahei;font-weight:bold;font-size:20px;}");

    hyout1->addWidget(&m_btnIcon);
    hyout1->addSpacing(0);
    hyout1->addWidget(&m_labelTitle);
    hyout1->setSpacing(5);
    hyout1->setContentsMargins(0,0,0,0);

    ////////////////////////////////////////////////////////
    /// \brief hyout2
    ///
    QHBoxLayout *hyout2=new QHBoxLayout;

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

    hyout2->addWidget(&m_btnmini);
    hyout2->addWidget(&m_btnexit);
    hyout2->setSpacing(12);

    ///////////////////////////////////////////////////////////

   //hHeaderlyout->addSpacerItem(new QSpacerItem(80,30,QSizePolicy::Maximum));//设置它最大膨胀！！！
    hHeaderlyout->addLayout(hyout1);
    hHeaderlyout->addSpacerItem(new QSpacerItem(110,50,QSizePolicy::Expanding));//膨胀
    hHeaderlyout->addLayout(hyout2);
    hHeaderlyout->setSpacing(0);
    hHeaderlyout->setContentsMargins(16,0,15,0);

    hmainyout->setSpacing(0);
    hmainyout->addLayout(hHeaderlyout);
    hmainyout->addWidget(&m_toolbar);
    hmainyout->setContentsMargins(0,0,0,0);

    setLayout(hmainyout);
}



bool TopWidgets::eventFilter(QObject *o, QEvent *e)
{
    return QObject::eventFilter(o,e);
}


void TopWidgets::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit(OnHeaderMouseDoubleClickEvent(event));
}
