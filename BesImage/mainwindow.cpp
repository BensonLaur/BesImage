#include "mainwindow.h"


MainWindow *MainWindow::s_pMainWnd=NULL;

MainWindow*MainWindow::GetInstance()
{
    if(!s_pMainWnd)
        s_pMainWnd=new MainWindow;
    return s_pMainWnd;
}


MainWindow::MainWindow(QWidget *parent)
    : baseWindow(parent),topWidget(this),midWidget(this)
{
    setMinimumSize(1008,698);
    m_mainwid.setStyleSheet("QLabel{color:white;}"
                             "QWidget{background:transparent;}");//"Widget{background: rgb(0,140,230);}"//border-image:url(:/image/skin/1.png)

    initUI();


    connect(&topWidget.m_btnmini,SIGNAL(clicked(bool)),SLOT(showMinimized()));
    connect(&topWidget.m_btnexit,SIGNAL(clicked(bool)),SLOT(close()));
    connect(&topWidget, SIGNAL(OnHeaderMouseDoubleClickEvent(QMouseEvent*)),this,SLOT(OnHeaderMouseDoubleClickEvent(QMouseEvent*)));
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

void MainWindow::OnHeaderMouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    if(!isMaximized())
    {
        showMaximized();
        setGeometry(-4,-4,width()+8,height()+8);//最大显示
    }
    else
        showNormal();
}



