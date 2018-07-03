#include "mainwindow.h"
#include "baseDialog.h"

#include "printSettingDialog.h"

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
    connect(&topWidget, SIGNAL(OnHeaderMouseDoubleClickEvent(QMouseEvent*)),this,SLOT(OnWindowHeaderDbClick(QMouseEvent*)));

    //工具栏
    connect(&topWidget.m_toolbar.btnReturn, SIGNAL(clicked(bool)), &midWidget,SLOT(returnToSelect()));
    connect(&topWidget.m_toolbar.btnPrintOne, SIGNAL(clicked(bool)),this, SLOT(printCurrentImage()));
    connect(&topWidget.m_toolbar.btnPrintAll, SIGNAL(clicked(bool)),this, SLOT(printCurrentDir()));
    connect(&topWidget.m_toolbar.btnPrintPreview, SIGNAL(clicked(bool)),this, SLOT(previewCurrentImage()));
    connect(&topWidget.m_toolbar.btnSetting, SIGNAL(clicked(bool)),this, SLOT(settingPrintParam()));

    connect(&midWidget.m_stackwid,SIGNAL(currentChanged(int)),this,SLOT(pageChanged(int)));
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

    pageChanged(0);                     //启用禁用页面1时的工具按钮

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

void MainWindow::OnWindowHeaderDbClick(QMouseEvent *e)
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


void MainWindow::settingPrintParam()
{
    PrintParameter param;
    bool bRet = PrintManager::GetInstance().GetPrintParameter(param);
    if(!bRet)
        return; //获取失败，中间已经报错，这里直接返回

    PrintSettingDialog dlg(this);
    dlg.LoadParam(param);
    if(dlg.exec() == QDialog::Accepted)
    {
        dlg.GetParam(param);
        PrintManager::GetInstance().SetPrintParameter(param);
    }
}

void MainWindow::previewCurrentImage()
{
    //获得当前展示图片
    QPixmap pixmap;
    midWidget.pageShow.imageScaler.GetCurrentPixMap(pixmap);

    // 打印预览
    PrintManager::GetInstance().PreviewPixmap(pixmap, this);
}

void MainWindow::printCurrentImage()
{
    //获得当前展示图片
    QPixmap pixmap;
    midWidget.pageShow.imageScaler.GetCurrentPixMap(pixmap);

    PrintManager::GetInstance().PrintOnePixmap(pixmap, this);
}

void MainWindow::printCurrentDir()
{
    QVector<QString> vecImgPath = midWidget.pageSelect.getLastSelectFiles();

    PrintManager::GetInstance().PrintMultiPixmap(vecImgPath, this);
}

//页面发生改变
void MainWindow::pageChanged(int index)
{
    //不同的页面启用不同的工具栏按钮
    if(index == 0)
    {
        topWidget.m_toolbar.btnReturn.setEnabled(false);
        topWidget.m_toolbar.btnPrintOne.setEnabled(false);

        if(midWidget.pageSelect.isCurrentSelectFileSetEmpty())
            topWidget.m_toolbar.btnPrintAll.setEnabled(false);
        else
            topWidget.m_toolbar.btnPrintAll.setEnabled(true);

        topWidget.m_toolbar.btnPrintPreview.setEnabled(false);
        topWidget.m_toolbar.btnSetting.setEnabled(true);
    }
    else if(index == 1)
    {

        topWidget.m_toolbar.btnReturn.setEnabled(true);
        topWidget.m_toolbar.btnPrintOne.setEnabled(true);

        topWidget.m_toolbar.btnPrintAll.setEnabled(false);

        topWidget.m_toolbar.btnPrintPreview.setEnabled(true);
        topWidget.m_toolbar.btnSetting.setEnabled(true);
    }

}



