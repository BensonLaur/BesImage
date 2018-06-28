#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initUI();
    connect(fileTree,SIGNAL(doubleClicked(const QModelIndex&)),this,SLOT(showSelectedImg(const QModelIndex&)));
    //connect(fileTree, SLOT(currentChanged(QModelIndex,QModelIndex), SIGNAL())
}

MainWindow::~MainWindow()
{

}

//初始化UI
void MainWindow::initUI()
{
    this->resize(700, 600);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));

    /* 初始化fileTree */
    //创建目录 model
    QDirModel *model = new QDirModel(centralWidget);
    model->setFilter(QDir::AllDirs|QDir::NoDotAndDotDot|QDir::Files);

    QStringList nameFilters;
    nameFilters << "*.bmp" << "*.png";
    model->setNameFilters(nameFilters);

    model->iconProvider()->setOptions(QFileIconProvider::DontUseCustomDirectoryIcons);


    fileTree = new QTreeView(centralWidget);

    fileTree->setModel(model);
    QString rootPath = "";//"C:/Users/Benso/"; //="";
    if (!rootPath.isEmpty()) {
        const QModelIndex rootIndex = model->index(QDir::cleanPath(rootPath));
        if (rootIndex.isValid())
            fileTree->setRootIndex(rootIndex);
    }

    // Demonstrating look and feel features
    fileTree->setAnimated(true);
    fileTree->setIndentation(15);
    fileTree->setSortingEnabled(true);
    fileTree->setColumnWidth(0, 300);
    fileTree->setColumnHidden(1, true);
    fileTree->setColumnHidden(2, true);
    fileTree->setColumnHidden(3, true);
    fileTree->setWindowTitle(QObject::tr("Dir View"));

    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(fileTree->sizePolicy().hasHeightForWidth());
    fileTree->setSizePolicy(sizePolicy);
    fileTree->setMaximumSize(QSize(300, 16777215));

    //定义QListWidget对象
    imageList = new QListWidget;
    //设置QListWidget的显示模式
    imageList->setViewMode(QListView::IconMode);
    //设置QListWidget中单元项的图片大小
    imageList->setIconSize(QSize(100,100));
    //设置QListWidget中单元项的间距
    imageList->setSpacing(10);
    //设置自动适应布局调整（Adjust适应，Fixed不适应），默认不适应
    imageList->setResizeMode(QListWidget::Adjust);
    //设置不能移动
    imageList->setMovement(QListWidget::Static);

    //显示QListWidget
    imageList->show();


    //将Tree 加入主窗口
    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->setSpacing(6);
    hLayout->addWidget(fileTree);
    hLayout->addWidget(imageList);

    QGridLayout* gridLayout = new QGridLayout(centralWidget);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    gridLayout->addLayout(hLayout,0,0,1,1);

    this->setCentralWidget(centralWidget);
}

bool MainWindow::LoadFloder(QString DirPath) //载入文件夹
{
    //先确认目录是否存在
    if(!QDir().exists(DirPath))
    {
        lastResultMessage = QObject::tr("翻译源输出目录不存在")+":"+DirPath;
        return false;
    }

    //一级目录下寻找 souisrc 文件载入
     QDir dir(DirPath);
     QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

     QVector<QString> vecFilePath;
     foreach(QFileInfo finfo ,file_list)
     {
        if(finfo.suffix()=="png" || finfo.suffix()=="bmp")
        {
            vecFilePath.push_back(finfo.absoluteFilePath());
        }
     }

    imageList->clear();
    for(auto tmp : vecFilePath)
    {
        //定义QListWidgetItem对象
        QListWidgetItem *imageItem = new QListWidgetItem;
        //为单元项设置属性
        imageItem->setIcon(QIcon(tmp));
        //imageItem->setText(tr("Browse"));
        //重新设置单元项图片的宽度和高度
        imageItem->setSizeHint(QSize(100,120));
        //将单元项添加到QListWidget中
        imageList->addItem(imageItem);
    }

    return true;
}


void MainWindow::showSelectedImg(const QModelIndex &index)
{
    QString path = index.data().toString();
    QModelIndex ParentIndex = index.parent();
    while(ParentIndex.isValid())
    {
        path = ParentIndex.data().toString() + "\\" + path;
        ParentIndex = ParentIndex.parent();
    }
    LoadFloder(path);
}
