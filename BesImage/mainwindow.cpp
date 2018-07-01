#include "mainwindow.h"
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>

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

    //程序头
    connect(&topWidget.m_btnmini,SIGNAL(clicked(bool)),SLOT(showMinimized()));
    connect(&topWidget.m_btnexit,SIGNAL(clicked(bool)),SLOT(close()));
    connect(&topWidget, SIGNAL(OnHeaderMouseDoubleClickEvent(QMouseEvent*)),this,SLOT(OnHeaderMouseDoubleClickEvent(QMouseEvent*)));

    //工具栏
    connect(&topWidget.m_toolbar.btnReturn, SIGNAL(clicked(bool)), &midWidget,SLOT(returnToSelect()));
    connect(&topWidget.m_toolbar.btnPrintOne, SIGNAL(clicked(bool)),this, SLOT(printCurrentImage()));
    connect(&topWidget.m_toolbar.btnPrintAll, SIGNAL(clicked(bool)),this, SLOT(printCurrentDir()));
    connect(&topWidget.m_toolbar.btnPrintPreview, SIGNAL(clicked(bool)),this, SLOT(previewCurrentImage()));

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
    vlyout->setSpacing(0);


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



void MainWindow::previewCurrentImage()
{
    // 打印预览

   QPrinter printer;

   //创建打印预览对话框
   QPrintPreviewDialog preview(&printer, this);

   // 当要生成预览页面时，发射paintRequested()信号
   connect(&preview, SIGNAL(paintRequested(QPrinter*)),
                 &midWidget.pageShow.imageScaler,SLOT(printPreviewSlot(QPrinter*)));

   preview.exec();

}

void MainWindow::printCurrentImage()
{
    midWidget.pageShow.imageScaler.printCurrentImage();
}

void MainWindow::printCurrentDir()
{
    midWidget.pageSelect.printLastSelectFiles();
}



