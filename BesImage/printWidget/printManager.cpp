#include "printManager.h"

PrintManager& PrintManager::GetInstance()
 {
     static PrintManager* instance = nullptr;
     if(instance == nullptr)
         instance = new PrintManager();

     return *instance;
 }

//获得打印参数 (如果未加载自动去文件读取，已加载则使用已载入的参数。bForceLoadFromFile 强制从文件获得最新参数)
bool  PrintManager::GetPrintParameter(PrintParameter& param, bool bForceLoadFromFile)
{

    return true;
}

//设置打印参数
bool PrintManager::SetPrintParameter(PrintParameter param)
{

    return true;
}

//打印一个图片
void PrintManager::PrintOnePixmap(const QPixmap& pixmap, QWidget *parent)
{
    m_pixmapToPrint = pixmap;

    QPrinter* printerPixmap= new QPrinter();

    printerPixmap->setPageSize(QPagedPaintDevice::A4);
    QPagedPaintDevice::Margins margins = QPagedPaintDevice::Margins{10,10,10,10};
    printerPixmap->setMargins(margins);
    printerPixmap->setOrientation(QPrinter::Portrait);
    printerPixmap->setOrientation(QPrinter::Landscape);

    QPrintDialog print(printerPixmap, parent);
    if (print.exec())
    {
       QPainter painterPixmap;
       painterPixmap.begin(printerPixmap);
       QRect rect = painterPixmap.viewport();
       double x = 1.0 * rect.width() / pixmap.width();
       double y = 1.0 * rect.height() / pixmap.height();
       painterPixmap.scale(x, y);
       painterPixmap.drawPixmap(0, 0, pixmap);
       painterPixmap.end();
    }
}

//预览一个图片
void PrintManager::PreviewPixmap(const QPixmap& pixmap, QWidget *parent)
{
    m_pixmapToPreview = pixmap;
    m_previewPaintDevice = parent;

    //创建打印预览对话框
    QPrinter printer;
    QPrintPreviewDialog preview(&printer, parent);

    // 当要生成预览页面时，发射paintRequested()信号
    connect(&preview, SIGNAL(paintRequested(QPrinter*)),this,SLOT(printPreviewSlot(QPrinter*)));

    preview.exec();
}

//打印多张图片
void PrintManager::PrintMultiPixmap(const QVector<QString>& vecImagePath, QWidget *parent)
{
    QPixmap pixmap;
    QVector<QPixmap> vecPixmap;
    for(auto& path: vecImagePath)
    {
        if(!pixmap.load(path))
        {
             qDebug() << "img load failed :" << path;
             continue;
        }

        vecPixmap.push_back(pixmap);
    }

    PrintMultiPixmap(vecPixmap, parent);
}

//打印多张图片
void PrintManager::PrintMultiPixmap(const QVector<QPixmap>& vecPixmap, QWidget *parent)
{
    m_vecPixmapToPrint = vecPixmap;

    if(m_vecPixmapToPrint.size() == 0)
        return;

    QPrinter* printer= new QPrinter();

    printer->setPageSize(QPagedPaintDevice::A4);
    QPagedPaintDevice::Margins margins = QPagedPaintDevice::Margins{10,10,10,10};
    printer->setMargins(margins);
    printer->setOrientation(QPrinter::Portrait);
    printer->setOrientation(QPrinter::Landscape);

    QPrintDialog* printDialog = new QPrintDialog(printer, parent);

    if (printDialog->exec() == QDialog::Accepted)
    {
        QPainter painter(printer);

        for(auto iter = m_vecPixmapToPrint.begin(); iter != m_vecPixmapToPrint.end(); iter++)
        {
            if (iter->width() > iter->height())
                printer->setPageOrientation(QPageLayout::Landscape);
            else
                printer->setPageOrientation(QPageLayout::Portrait);

            QRect pageOriginRect = printer->pageRect();
            QSize pageRect = QSize(pageOriginRect.width() - 8, pageOriginRect.height() - 8);
            QPixmap img = iter->scaled(pageRect, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            painter.drawPixmap(0, 0, img);

            if (iter != m_vecPixmapToPrint.end() - 1)
                printer->newPage();
        }
        painter.end();
        qDebug() << "print succeed!";
        return;
   }

    QObject::connect(printDialog, &QPrintDialog::finished,  this, [=]{
        printDialog->deleteLater();
        //m_printDialogVisible =  false;
    });

    qDebug() << "print failed!";

}

//预览当前选中图片
void PrintManager::printPreviewSlot(QPrinter *printerPixmap)
{
    printerPixmap->setPageSize(QPagedPaintDevice::A4);
    QPagedPaintDevice::Margins margins = QPagedPaintDevice::Margins{10,10,10,10};
    printerPixmap->setMargins(margins);
    printerPixmap->setOrientation(QPrinter::Portrait);
    printerPixmap->setOrientation(QPrinter::Landscape);
//    printerPixmap->setPageSize(QPrinter::Custom);
//    printerPixmap->setPaperSize(QSizeF(pixmap.height(),pixmap.width()),QPrinter::Point);

    QPainter painterPixmap(m_previewPaintDevice);
    painterPixmap.begin(printerPixmap);
    QRect rect = painterPixmap.viewport();
    double x = 1.0 * rect.width() / m_pixmapToPreview.width();
    double y = 1.0 * rect.height() / m_pixmapToPreview.height();
    painterPixmap.scale(x, y);
    painterPixmap.drawPixmap(0, 0, m_pixmapToPreview);
    painterPixmap.end();
}

//从默认路径中加载打印参数
bool PrintManager::LoadPrintSetting()
{
    return true;
}

//保存到打印参数
bool PrintManager::SavePrintSetting()
{
    return true;
}
