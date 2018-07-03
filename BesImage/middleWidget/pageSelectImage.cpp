#include "pageSelectImage.h"
#include <QImageReader>
#include <QDebug>
#include "appConfig.h"

PageSelectImage::PageSelectImage(QWidget *parent) : baseWidget(parent),
  fileTree(this),
  imageList(this),
  m_btnhidelist(this),
  sizeIconLast(100,100)
{
    setStyleSheet("PageSelectImage{background:transparent;}");
    setMouseTracking(true);

    QList<QByteArray> listFormat =  QImageReader::supportedImageFormats();

    QStringList list;
    for(auto fomat:listFormat) list << fomat;
    //list << "png" << "bmp" << "jpg";
    SetImageSuffixFilters(list);

    initWidget();

    connect(&fileTree,SIGNAL(clicked(const QModelIndex&)),this,SLOT(showImgUnderTreeItem(const QModelIndex&)));

    connect(&m_btnhidelist,SIGNAL(clicked(bool)),this,SLOT(slot_btnclicked()));

    connect(&imageList, SIGNAL(doubleClicked(QModelIndex)),this, SLOT(OnClickImgItem(QModelIndex)));

}


bool PageSelectImage::eventFilter(QObject *o, QEvent *e)
{
    return QObject::eventFilter(o,e);
}

void PageSelectImage::wheelEvent(QWheelEvent *event)
{
    QPoint numPixels = event->pixelDelta();
    QPoint numDegrees = event->angleDelta() / 8;

    if ( QApplication::keyboardModifiers () == Qt::ControlModifier)
    {
        if (!numPixels.isNull()) {
            ScaleImageListOnce(numPixels.y() > 0);
        } else if (!numDegrees.isNull()) {
            QPoint numSteps = numDegrees / 15;
            ScaleImageListOnce(numSteps.y() > 0);
        }

        event->accept();
        return;
    }

    event->ignore();
}

void PageSelectImage::initWidget()
{
    /*初始化fileTree */
    //创建目录 model
    dirModel = new QDirModel(this);
    dirModel->setFilter(QDir::AllDirs|QDir::NoDotAndDotDot|QDir::Files);

    QStringList nameFilters;
    for(auto suffix: listSuffixFilters)
    {
        nameFilters << "*."+suffix;
    }
    dirModel->setNameFilters(nameFilters);

    dirModel->iconProvider()->setOptions(QFileIconProvider::DontUseCustomDirectoryIcons);

    fileTree.setModel(dirModel);
    QString rootPath = "";//"C:/Users/Benso/"; //="";
    if (!rootPath.isEmpty()) {
        const QModelIndex rootIndex = dirModel->index(QDir::cleanPath(rootPath));
        if (rootIndex.isValid())
            fileTree.setRootIndex(rootIndex);
    }

    // Demonstrating look and feel features
    fileTree.setAnimated(true);
    fileTree.setIndentation(15);
    fileTree.setSortingEnabled(false);
    fileTree.setColumnWidth(0, 260);
    fileTree.setColumnHidden(1, true);
    fileTree.setColumnHidden(2, true);
    fileTree.setColumnHidden(3, true);
    fileTree.setWindowTitle(QObject::tr("Dir View"));
    fileTree.setHeaderHidden(true);

    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(fileTree.sizePolicy().hasHeightForWidth());
    fileTree.setSizePolicy(sizePolicy);
    fileTree.setMaximumSize(QSize(300, 16777215));

    //定义QListWidget对象
    //设置QListWidget的显示模式
    imageList.setViewMode(QListView::IconMode);
    //设置QListWidget中单元项的图片大小
    imageList.setIconSize(sizeIconLast);
    //设置QListWidget中单元项的间距
    imageList.setSpacing(10);
    //设置自动适应布局调整（Adjust适应，Fixed不适应），默认不适应
    imageList.setResizeMode(QListWidget::Adjust);
    //设置不能移动
    imageList.setMovement(QListWidget::Static);

    //显示QListWidget
    imageList.show();

    m_btnhidelist.setFixedSize(13,55);
    setlistHideStyle();

    //将Tree 加入主窗口
    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->setSpacing(0);
    hLayout->addWidget(&fileTree);
    hLayout->addWidget(&m_btnhidelist);
    hLayout->addWidget(&imageList);

    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    gridLayout->addLayout(hLayout,0,0,1,1);

    this->setLayout(gridLayout);
}

void PageSelectImage::setlistShowStyle()
{
    m_btnhidelist.setStyleSheet("QPushButton{border-image:url(:/image/middlewidget/btn_listshow (1).png)}"
                                 "QPushButton:hover{border-image:url(:/image/middlewidget/btn_listshow (2).png)}"
                                 "QPushButton:pressed{border-image:url(:/image/middlewidget/btn_listshow (3).png)}");
}

void PageSelectImage::setlistHideStyle()
{
    m_btnhidelist.setStyleSheet("QPushButton{border-image:url(:/image/middlewidget/btn_listhide (1).png)}"
                                 "QPushButton:hover{border-image:url(:/image/middlewidget/btn_listhide (2).png)}"
                                 "QPushButton:pressed{border-image:url(:/image/middlewidget/btn_listhide (3).png)}");
}

 //载入文件夹/文件
bool PageSelectImage::LoadFloder(QString path)
{
    QFileInfo fi(path);

    //先确认路径是否有效
    if(!fi.isFile() && !fi.isDir())
    {
        return false;
    }

    QVector<QString> vecFilePath;

    if(fi.isDir())
    {
        //一级目录下寻找 souisrc 文件载入
        QDir dir(path);
        QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

        foreach(QFileInfo finfo ,file_list)
        {
           QString suffix = finfo.suffix().toLower();

           if(listSuffixFilters.contains(suffix))
               vecFilePath.push_back(finfo.absoluteFilePath());
        }

         emit(OnShowBtnBackToParent(false)); //取消其显示
    }
    else if(fi.isFile())
    {
        vecFilePath.push_back(path);

        if( AppConfig::GetInstance().IsValidOnlyShowOneImage())
        {
            emit(OnShowBtnBackToParent(false)); //只显示一张图片的模式时不显示返回父目录按钮

            //直接选中当前文件，自动切换到显示图片页面
            emit(OnSelectOnePath(path));

            return true;  //随便返回一个值（因为这个显示模式不用处理返回）
        }
        else
            //此时为展示一个图片，为了能够返回选中整个父目录（在根目录为父目录时无法直接做到），发送信号
            emit(OnShowBtnBackToParent(true));
    }

    vecLastFilePath = vecFilePath;

    emit(OnFilesSelectedChanged()); //选中的项发生改变

    imageList.clear();
    for(auto tmp : vecFilePath)
    {
        //定义QListWidgetItem对象
        QListWidgetItem *imageItem = new QListWidgetItem;
        //为单元项设置属性
        imageItem->setIcon(QIcon(tmp));
        //imageItem->setText(tr("Browse"));
        //重新设置单元项图片的宽度和高度
        imageItem->setSizeHint(sizeIconLast);

        //保存路径数据提示中，后面取出
        imageItem->setData(Qt::StatusTipRole, tmp);

        //将单元项添加到QListWidget中
        imageList.addItem(imageItem);
    }

    bNeedToReloadImageSet = true;

    return true;
}

//设置图片后缀名过滤，形如如"png"
void PageSelectImage::SetImageSuffixFilters(QStringList suffixList)
{
    listSuffixFilters = suffixList;
}

bool PageSelectImage::ScaleImageListOnce(bool bAdding)   //缩放列表一次， bAdding 表示是否增加大小
{
    if(bAdding)
        sizeIconLast += QSize(10,10);
    else
        sizeIconLast -= QSize(10,10);

    sizeIconLast.rheight() =  sizeIconLast.rheight() < 30 ? 30: (sizeIconLast.rheight() > 400 ? 400:sizeIconLast.rheight());
    sizeIconLast.rwidth() =  sizeIconLast.rwidth() < 30 ? 30: (sizeIconLast.rwidth() > 400 ? 400:sizeIconLast.rwidth());

    imageList.setIconSize(sizeIconLast);

    int size = imageList.count();
    for(int i = 0; i < size; i++)
        imageList.item(i)->setSizeHint(sizeIconLast);


    return true;
}

 //打印最后一次选择的图片
QVector<QString> PageSelectImage::getLastSelectFiles()
{
    return vecLastFilePath;
}

//当前选中的文件集合是否为空
bool PageSelectImage::isCurrentSelectFileSetEmpty()
{
    return vecLastFilePath.empty();
}

//设置文件树的根目录
void PageSelectImage::SetFileTreeRootPath(QString rootPath)
{
    if (!rootPath.isEmpty()) {
        const QModelIndex rootIndex = dirModel->index(QDir::cleanPath(rootPath));
        if (rootIndex.isValid()){
            fileTree.setRootIndex(rootIndex);

            showImgUnderTreeItem(rootIndex);
        }
        else
            emit(OnShowBtnBackToParent(false)); //没有设置有效根路径的情况下，确认不显示目录返回按钮
    }
    else
        emit(OnShowBtnBackToParent(false));
}

void PageSelectImage::showImgUnderTreeItem(const QModelIndex &index)
{
    modelIndexLast = index;  //保存最后选中的modelIndex

    QString path = index.data().toString();
    QModelIndex ParentIndex = index.parent();
    while(ParentIndex.isValid())
    {
        path = ParentIndex.data().toString() + "\\" + path;
        ParentIndex = ParentIndex.parent();
    }

    LoadFloder(path);
}

void PageSelectImage::slot_btnclicked()
{
    if(fileTree.isHidden())//如果是隐藏的
    {
        fileTree.show();
        setlistHideStyle();
    }
    else
    {
        fileTree.hide();
        setlistShowStyle();
    }
}


void PageSelectImage::OnClickImgItem(const QModelIndex &index)
{
    // path selected
    QString pathSel = index.data(Qt::StatusTipRole).toString();

    QVector<QString> vecImagePath;
    int curSel = 0;
    for(int i =0; i < imageList.count(); i++)
    {
        QString path = imageList.item(i)->data(Qt::StatusTipRole).toString();

        if(!QFile::exists(path)) //不存在的文件,跳过
            continue;

        QDir dir(path);
        if(dir.exists())  //目录，跳过
            continue;

        vecImagePath.push_back(path);

        if(path == pathSel)
            curSel = i;
    }

    //发送选择路径的信号，pageShowImage 的槽会接收路径显示图片
    //emit(OnSelectOnePath(tip));

    if(bNeedToReloadImageSet)
    {
        emit( OnSelectBunchPath(vecImagePath, curSel));  //发送整个图像集合
        bNeedToReloadImageSet = false;
    }
    else
        emit( OnSelectIndexInSet(curSel));      //发送显示的图像下标即可
}

 //选中最后项的父项
void PageSelectImage::selectParentOfLastItem()
{
    fileTree.setCurrentIndex(modelIndexLast.parent());
    showImgUnderTreeItem(modelIndexLast.parent());
}
