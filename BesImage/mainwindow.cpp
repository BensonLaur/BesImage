#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : baseWindow(parent),topWidget(this),midWidget(this)
{

    setMinimumSize(1008,698);
    m_mainwid.setStyleSheet("QLabel{color:white;}"
                             "QWidget{background:transparent;}");//"Widget{background: rgb(0,140,230);}"//border-image:url(:/image/skin/1.png)

    initUI();
}

MainWindow::~MainWindow()
{

}

//初始化UI
void MainWindow::initUI()
{
    QVBoxLayout *vlyout=new QVBoxLayout;
    vlyout->addWidget(&topWidget);
    vlyout->addWidget(&midWidget);

    m_mainwid.setLayout(vlyout);

    setCurBGPic(":/image/skin/default.jpg");
}


void MainWindow::clearBackground()
{
    m_mainwid.clearBg();
}

inline void MainWindow::setCurBGPic(const QString&strPic)
{
   m_mainwid.setCurBGPic(strPic);
}


