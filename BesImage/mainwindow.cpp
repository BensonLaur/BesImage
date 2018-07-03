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

    connect(&midWidget.pageSelect,SIGNAL(OnFilesSelectedChanged()),
                                    this,SLOT(UpdateToolbarOnFilesSelectedChanged()));
    connect(&midWidget.pageSelect,SIGNAL(OnSelectSingleFileInTree(bool)), this,
                                    SLOT(ShowBtnBackToParent(bool)));

    connect(&topWidget.m_toolbar.btnBackParent, SIGNAL(clicked(bool)),
                    &midWidget.pageSelect, SLOT(selectParentOfLastItem()));

    //根据AppConfig 配置程序
    ApplyAppConfig();
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

void MainWindow::ApplyAppConfig()
{
    AppConfigParameter param;
    AppConfig::GetInstance().GetAppParameter(param);
    //AppConfig::GetInstance().SetAppParameter(param);

    /* 先使用程序的默认设置项来设置程序 */

    //设置背景图片
    setCurBGPic(param.defaultBackgroundPath);

    //设置标题、黑白2个风格图标，然后设置使用黑
    topWidget.SetIcon(param.besimageBlackIcon, param.besimageWhiteIcon);
    topWidget.SetColorBlackOrWhite(param.isWindowHeaderColorBlack);


    /* 使用有效的用户配置项来定义程序 */
    topWidget.SetTitle(param.appTitle);
    midWidget.pageSelect.SetFileTreeRootPath(param.initPath);

    if(AppConfig::GetInstance().IsValidOnlyShowOneImage())
    {
        //不显示返回按钮
         topWidget.m_toolbar.btnReturn.setVisible(false);

         //其他逻辑，在 上面 midWidget.pageSelect.SetFileTreeRootPath(param.initPath); 之后
         //    首先触发 showImgUnderTreeItem(rootIndex);
         //        然后 其中 LoadFloder(path); 载入列表时
         //             判断单个文件时，是IsValidOnlyShowOneImage ，则emit(OnSelectOnePath(path));
         //                 从而触发相关信号自动改变部分控件
    }
}

void MainWindow::clearBackground()
{
    m_mainwid.clearBg();
}

inline void MainWindow::setCurBGPic(const QString& path)
{
    //使用相对路径尝试构建出有效路径，如果无法构建出存在的文件路径，使用系统默认资源
    QString imagePath;

    if(QFile::exists(path))
        imagePath = path;
    else if(QFile::exists(QCoreApplication::applicationDirPath() +"/"+ path))
        imagePath = QCoreApplication::applicationDirPath() +"/"+ path;

   m_mainwid.setCurBGPic(imagePath);
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
        topWidget.m_toolbar.btnReturn.setVisible(false);
        topWidget.m_toolbar.btnPrintOne.setVisible(false);

        if(midWidget.pageSelect.isCurrentSelectFileSetEmpty())
            topWidget.m_toolbar.btnPrintAll.setVisible(false);
        else
            topWidget.m_toolbar.btnPrintAll.setVisible(true);

        topWidget.m_toolbar.btnPrintPreview.setVisible(false);
        topWidget.m_toolbar.btnSetting.setVisible(true);
    }
    else if(index == 1)
    {
        topWidget.m_toolbar.btnReturn.setVisible(true);
        topWidget.m_toolbar.btnPrintOne.setVisible(true);

        topWidget.m_toolbar.btnPrintAll.setVisible(false);

        topWidget.m_toolbar.btnPrintPreview.setVisible(true);
        topWidget.m_toolbar.btnSetting.setVisible(true);
    }
}

//在选中树发生改变后 更新工具栏
void MainWindow::UpdateToolbarOnFilesSelectedChanged()
{
    if(midWidget.pageSelect.isCurrentSelectFileSetEmpty())
        topWidget.m_toolbar.btnPrintAll.setVisible(false);
    else
        topWidget.m_toolbar.btnPrintAll.setVisible(true);
}

//显示回到显示父目录的状态的按钮
void MainWindow::ShowBtnBackToParent(bool bIsSingleFile)
{
     topWidget.m_toolbar.btnBackParent.setVisible(bIsSingleFile);
}
