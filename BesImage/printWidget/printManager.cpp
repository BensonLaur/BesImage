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
    if(!m_hasLoad || bForceLoadFromFile)
    {
        QString confPath;
        if(!MakeSureConfigPathAvailable(confPath))  //获得路径
            return false;

        if(!QFile::exists(confPath))  //不存在，自动创建配置，并提示
        {
            param = PrintParameter();

            if(SetPrintParameter(param))
                QMessageBox::information(nullptr,tr("提示"),tr("配置文件不存在，已自动创建")+":" + confPath,
                                        QMessageBox::Yes,QMessageBox::Yes);
            else
                QMessageBox::information(nullptr,tr("提示"),tr("配置文件不存在，自动创建失败")+":" + confPath,
                                        QMessageBox::Yes,QMessageBox::Yes);

            m_param = param;

        }
        else //存在，读取配置
        {
            if(!LoadPrintSetting())
                QMessageBox::information(nullptr,tr("提示"),tr("载入配置文件失败")+":" + confPath,
                                        QMessageBox::Yes,QMessageBox::Yes);
        }

        m_hasLoad = true;
    }

    param = m_param;

    return true;
}

//设置打印参数
bool PrintManager::SetPrintParameter(PrintParameter param)
{
    m_param = param;

    return SavePrintSetting();
}

//获得页大小枚举字符串映射
const QVector<QPair<int, QString>>& PrintManager::GetPaperSizeEnumStringMap()
{
  if(vecPaperSizePair.size() == 0) //只在第一次构建初始化
  {
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::A4 	), tr("A4 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::B5 	), tr("B5 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Letter 	), tr("Letter ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Legal 	), tr("Legal ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Executive 	), tr("Executive ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::A0 	), tr("A0 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::A1 	), tr("A1 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::A2 	), tr("A2 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::A3 	), tr("A3 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::A5 	), tr("A5 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::A6 	), tr("A6 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::A7 	), tr("A7 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::A8 	), tr("A8 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::A9 	), tr("A9 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::B0 	), tr("B0 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::B1 	), tr("B1 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::B10 	), tr("B10 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::B2 	), tr("B2 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::B3 	), tr("B3 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::B4 	), tr("B4 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::B6 	), tr("B6 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::B7 	), tr("B7 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::B8 	), tr("B8 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::B9 	), tr("B9 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::C5E 	), tr("C5E ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Comm10E 	), tr("Comm10E ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::DLE 	), tr("DLE ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Folio 	), tr("Folio ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Ledger 	), tr("Ledger ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Tabloid 	), tr("Tabloid ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Custom 	), tr("Custom ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::A10 	), tr("A10 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::A3Extra 	), tr("A3Extra ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::A4Extra 	), tr("A4Extra ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::A4Plus 	), tr("A4Plus ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::A4Small 	), tr("A4Small ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::A5Extra 	), tr("A5Extra ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::B5Extra 	), tr("B5Extra ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::JisB0 	), tr("JisB0 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::JisB1 	), tr("JisB1 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::JisB2 	), tr("JisB2 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::JisB3 	), tr("JisB3 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::JisB4 	), tr("JisB4 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::JisB5 	), tr("JisB5 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::JisB6 	), tr("JisB6 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::JisB7 	), tr("JisB7 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::JisB8 	), tr("JisB8 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::JisB9 	), tr("JisB9 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::JisB10 	), tr("JisB10 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::AnsiC 	), tr("AnsiC ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::AnsiD 	), tr("AnsiD ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::AnsiE 	), tr("AnsiE ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::LegalExtra 	), tr("LegalExtra ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::LetterExtra 	), tr("LetterExtra ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::LetterPlus 	), tr("LetterPlus ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::LetterSmall 	), tr("LetterSmall ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::TabloidExtra 	), tr("TabloidExtra ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::ArchA 	), tr("ArchA ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::ArchB 	), tr("ArchB ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::ArchC 	), tr("ArchC ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::ArchD 	), tr("ArchD ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::ArchE 	), tr("ArchE ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Imperial7x9 	), tr("Imperial7x9 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Imperial8x10 	), tr("Imperial8x10 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Imperial9x11 	), tr("Imperial9x11 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Imperial9x12 	), tr("Imperial9x12 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Imperial10x11 	), tr("Imperial10x11 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Imperial10x13 	), tr("Imperial10x13 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Imperial10x14 	), tr("Imperial10x14 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Imperial12x11 	), tr("Imperial12x11 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Imperial15x11 	), tr("Imperial15x11 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::ExecutiveStandard 	), tr("ExecutiveStandard ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Note 	), tr("Note ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Quarto 	), tr("Quarto ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Statement 	), tr("Statement ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::SuperA 	), tr("SuperA ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::SuperB 	), tr("SuperB ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Postcard 	), tr("Postcard ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::DoublePostcard 	), tr("DoublePostcard ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Prc16K 	), tr("Prc16K ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Prc32K 	), tr("Prc32K ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Prc32KBig 	), tr("Prc32KBig ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::FanFoldUS 	), tr("FanFoldUS ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::FanFoldGerman 	), tr("FanFoldGerman ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::FanFoldGermanLegal 	), tr("FanFoldGermanLegal ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopeB4 	), tr("EnvelopeB4 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopeB5 	), tr("EnvelopeB5 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopeB6 	), tr("EnvelopeB6 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopeC0 	), tr("EnvelopeC0 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopeC1 	), tr("EnvelopeC1 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopeC2 	), tr("EnvelopeC2 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopeC3 	), tr("EnvelopeC3 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopeC4 	), tr("EnvelopeC4 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopeC6 	), tr("EnvelopeC6 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopeC65 	), tr("EnvelopeC65 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopeC7 	), tr("EnvelopeC7 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Envelope9 	), tr("Envelope9 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Envelope11 	), tr("Envelope11 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Envelope12 	), tr("Envelope12 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Envelope14 	), tr("Envelope14 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopeMonarch 	), tr("EnvelopeMonarch ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopePersonal 	), tr("EnvelopePersonal ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopeChou3 	), tr("EnvelopeChou3 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopeChou4 	), tr("EnvelopeChou4 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopeInvite 	), tr("EnvelopeInvite ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopeItalian 	), tr("EnvelopeItalian ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopeKaku2 	), tr("EnvelopeKaku2 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopeKaku3 	), tr("EnvelopeKaku3 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopePrc1 	), tr("EnvelopePrc1 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopePrc2 	), tr("EnvelopePrc2 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopePrc3 	), tr("EnvelopePrc3 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopePrc4 	), tr("EnvelopePrc4 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopePrc5 	), tr("EnvelopePrc5 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopePrc6 	), tr("EnvelopePrc6 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopePrc7 	), tr("EnvelopePrc7 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopePrc8 	), tr("EnvelopePrc8 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopePrc9 	), tr("EnvelopePrc9 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopePrc10 	), tr("EnvelopePrc10 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopeYou4 	), tr("EnvelopeYou4 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::NPageSize  	), tr("NPageSize  ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::NPaperSize 	), tr("NPaperSize ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::AnsiA 	), tr("AnsiA ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::AnsiB 	), tr("AnsiB ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopeC5 	), tr("EnvelopeC5 ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::EnvelopeDL 	), tr("EnvelopeDL ")));
    vecPaperSizePair.push_back(QPair<int, QString>(((int)QPagedPaintDevice::PageSize::Envelope10	), tr("Envelope10")));
  }
  return vecPaperSizePair;
}


//打印一个图片
void PrintManager::PrintOnePixmap(const QPixmap& pixmap, QWidget *parent)
{
    m_pixmapToPrint = pixmap;

    //获得打印参数
    PrintParameter param;
    GetPrintParameter(param);

    //设置打印参数
    QPrinter* printerPixmap= new QPrinter();
    printerPixmap->setPageSize(GetPaperSizeEnumByIndex(param.pageSize));
    printerPixmap->setMargins(param.margins);
    printerPixmap->setOrientation((QPrinter::Orientation)param.orientation);

    QPrintDialog print(printerPixmap, parent);
    if (print.exec())
    {
        if(!param.keepAspectRatio) //不保持纵横比，可通过缩放QPainter坐标系实现
        {
           QPainter painterPixmap;                      //创建Painter
           painterPixmap.begin(printerPixmap);          //在printer上面画
           QRect rect = painterPixmap.viewport();
           double x = 1.0 * rect.width() / pixmap.width();
           double y = 1.0 * rect.height() / pixmap.height();
           painterPixmap.scale(x, y);                   //缩放Painter 自身的坐标系（适应图片比例）
           painterPixmap.drawPixmap(0, 0, pixmap);
           painterPixmap.end();
        }
        else
        {
            //其实保不保持都可以用下面逻辑直接实现，上面逻辑 可参考用

            QPainter painter(printerPixmap);          //直接从printer上创建painter

            QRect pageOriginRect = printerPixmap->pageRect();
            QSize pageRect = QSize(pageOriginRect.width(), pageOriginRect.height());
            QPixmap img = pixmap.scaled(pageRect,
                         param.keepAspectRatio ? Qt::KeepAspectRatio : Qt::IgnoreAspectRatio,
                         Qt::SmoothTransformation);

            painter.drawPixmap(0, 0, img);  //在原来坐标系上，直接画 缩放后的图像

            painter.end();                            //绘制结束
        }
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

    //获得打印参数
    PrintParameter param;
    GetPrintParameter(param);

    //设置打印参数
    QPrinter* printer= new QPrinter();
    printer->setPageSize(GetPaperSizeEnumByIndex(param.pageSize));
    printer->setMargins(param.margins);
    printer->setOrientation((QPrinter::Orientation)param.orientation);

    QPrintDialog* printDialog = new QPrintDialog(printer, parent);

    if (printDialog->exec() == QDialog::Accepted)
    {
        QPainter painter(printer);          //直接从printer上创建painter

        for(auto iter = m_vecPixmapToPrint.begin(); iter != m_vecPixmapToPrint.end(); iter++)
        {
            QRect pageOriginRect = printer->pageRect();
            QSize pageRect = QSize(pageOriginRect.width(), pageOriginRect.height());
            QPixmap img = iter->scaled(pageRect,
                       param.keepAspectRatio ? Qt::KeepAspectRatio : Qt::IgnoreAspectRatio,
                       Qt::SmoothTransformation);

            painter.drawPixmap(0, 0, img);  //在原来坐标系上，直接画 缩放后的图像

            if (iter != m_vecPixmapToPrint.end() - 1)
                printer->newPage();
        }
        painter.end();
        qDebug() << "print succeed!";
        return;
   }

    QObject::connect(printDialog, &QPrintDialog::finished,  this, [=](){
        printDialog->deleteLater();
        //m_printDialogVisible =  false;
    });

    qDebug() << "print failed!";

}

//预览当前选中图片
void PrintManager::printPreviewSlot(QPrinter *printerPixmap)
{
    //获得打印参数
    PrintParameter param;
    GetPrintParameter(param);

    //设置打印参数
    printerPixmap->setPageSize(GetPaperSizeEnumByIndex(param.pageSize));
    printerPixmap->setMargins(param.margins);
    printerPixmap->setOrientation((QPrinter::Orientation)param.orientation);

    //printerPixmap->setPageSize(QPrinter::Custom);
    //printerPixmap->setPaperSize(QSizeF(pixmap.height(),pixmap.width()),QPrinter::Point);

    if(!param.keepAspectRatio) //不保持纵横比，可通过缩放QPainter坐标系实现
    {
        QPainter painterPixmap(m_previewPaintDevice);       //创建Painter
        painterPixmap.begin(printerPixmap);                 //在printer上面画
        QRect rect = painterPixmap.viewport();
        double x = 1.0 * rect.width() / m_pixmapToPreview.width();
        double y = 1.0 * rect.height() / m_pixmapToPreview.height();
        painterPixmap.scale(x, y);                          //缩放Painter 自身的坐标系（适应图片比例）
        painterPixmap.drawPixmap(0, 0, m_pixmapToPreview);
        painterPixmap.end();
    }
    else
    {
        //其实保不保持都可以用下面逻辑直接实现，上面逻辑 可参考用

        QPainter painter(printerPixmap);          //直接从printer上创建painter

        QRect pageOriginRect = printerPixmap->pageRect();
        QSize pageRect = QSize(pageOriginRect.width(), pageOriginRect.height());
        QPixmap img = m_pixmapToPreview.scaled(pageRect,
                     param.keepAspectRatio ? Qt::KeepAspectRatio : Qt::IgnoreAspectRatio,
                     Qt::SmoothTransformation);

        painter.drawPixmap(0, 0, img);  //在原来坐标系上，直接画 缩放后的图像

        painter.end();                            //绘制结束
    }
}

//从默认路径中加载打印参数
bool PrintManager::LoadPrintSetting()
{
    QString confPath;
    if(!MakeSureConfigPathAvailable(confPath))  //确保配置路径可用，并获得了路径
        return false;

    //打开文件
    QFile file(confPath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) { // 只读模式打开文件
            qDebug() << QString("Cannot read file %1(%2).").arg(confPath).arg(file.errorString());
            return false;
    }

    PrintParameter param;

    //读取示例参考: https://blog.csdn.net/liang19890820/article/details/52808829

    //将配置从xml文件读出
    QXmlStreamReader reader(&file);

    QString strElementName = "";

    // 解析 XML，直到结束
    while (!reader.atEnd()) {

        // 读取下一个元素
        QXmlStreamReader::TokenType nType = reader.readNext();

        if (nType == QXmlStreamReader::StartElement)
        {
            strElementName = reader.name().toString();
            if (QString::compare(strElementName, "printConfig") == 0) // 根元素
            {
                parseConfig(reader, param);  //解析 printConfig
            }
        }
    }

    if (reader.hasError()) {  // 解析出错
           qDebug() << QObject::tr("错误信息：%1  行号：%2  列号：%3  字符位移：%4").arg(reader.errorString()).arg(reader.lineNumber()).arg(reader.columnNumber()).arg(reader.characterOffset());
    }

    file.close();  // 关闭文件

    m_param = param;

    return true;
}

//解析config
void PrintManager::parseConfig(QXmlStreamReader &reader, PrintParameter &param)
{
    while (!reader.atEnd()) {

        reader.readNext();
        if (reader.isStartElement()) {  // 开始元素
            QString strElementName = reader.name().toString();
            if(strElementName == "pageSizeEnum")
            {
                param.pageSize = reader.readElementText().toInt();
            }
            else if(strElementName == "margins")
            {
                parseMargins(reader, param);
            }
            else if(strElementName == "orientationEnum")
            {
                param.orientation = (QPrinter::Orientation)reader.readElementText().toInt();
            }
            else if(strElementName == "keepAspectRatio")
            {
                param.keepAspectRatio = reader.readElementText().toInt() == 0 ? false:true;
            }
        }
        else if(reader.isEndElement()) {

            QString strElementName = reader.name().toString();
            if (QString::compare(strElementName, "printConfig") == 0) {
                break;  // 跳出
            }
        }
    }
}

//解析config
void PrintManager::parseMargins(QXmlStreamReader &reader, PrintParameter &param)
{
    while (!reader.atEnd()) {

        reader.readNext();
        if (reader.isStartElement()) {  // 开始元素
            QString strElementName = reader.name().toString();
            if(strElementName == "left")
            {
                param.margins.left = reader.readElementText().toDouble();
            }
            else if(strElementName == "top")
            {
                param.margins.top = reader.readElementText().toDouble();
            }
            else if(strElementName == "right")
            {
                param.margins.right = reader.readElementText().toDouble();
            }
            else if(strElementName == "bottom")
            {
                param.margins.bottom = reader.readElementText().toDouble();
            }
        }
        else if(reader.isEndElement()) {

            QString strElementName = reader.name().toString();
            if (QString::compare(strElementName, "margins") == 0) {
                break;  // 跳出
            }
        }
    }
}

//保存到打印参数
bool PrintManager::SavePrintSetting()
{
    QString confPath;
    if(!MakeSureConfigPathAvailable(confPath))  //确保配置路径可用，并获得了路径
        return false;

    //打开文件
    QFile file(confPath);
    if (!file.open(QFile::WriteOnly | QFile::Text)) { // 只写模式打开文件
            qDebug() << QString("Cannot write file %1(%2).").arg(confPath).arg(file.errorString());
            return false;
    }

    //将配置写入xml文件
    QXmlStreamWriter writer(&file);

    writer.setAutoFormatting(true); // 自动格式化
    writer.writeStartDocument("1.0", true);  // 开始文档（XML 声明）

    writer.writeStartElement("printConfig"); // 开始元素<printConfig>

    writer.writeTextElement("pageSizeEnum", QString::number((int)m_param.pageSize));

    writer.writeStartElement("margins"); // 开始元素<margins>

    writer.writeTextElement("left", QString::number((double)m_param.margins.left));
    writer.writeTextElement("top", QString::number((double)m_param.margins.top));
    writer.writeTextElement("right", QString::number((double)m_param.margins.right));
    writer.writeTextElement("bottom", QString::number((double)m_param.margins.bottom));

    writer.writeEndElement();  // 结束子元素 </margins>

    writer.writeTextElement("orientationEnum", QString::number((int)m_param.orientation));

    writer.writeTextElement("keepAspectRatio", QString::number(m_param.keepAspectRatio?1:0));

    writer.writeEndElement();  // 结束子元素 </printConfig>

    writer.writeEndDocument();  // 结束文档

    file.close();  // 关闭文件

    return true;
}

//确保配置路径可用，返回配置路径
bool PrintManager::MakeSureConfigPathAvailable(QString &path)
{
    QString StrSettingsDir = QCoreApplication::applicationDirPath() + "/settings";

    //如果settings 目录不存在则创建目录
    QDir SettingDir(StrSettingsDir);
    if(!SettingDir.exists())
    {
        if(!SettingDir.mkpath(StrSettingsDir))
        {
            QMessageBox::information(nullptr,tr("提示"),tr("无法为配置创建目录")+":" + StrSettingsDir,
                                    QMessageBox::Yes,QMessageBox::Yes);
            return false;
        }
    }

    //得到目标路径
    path = StrSettingsDir + "/print.config";
    return  true;
}

//通过下标获得页面大小的枚举值
QPagedPaintDevice::PageSize PrintManager::GetPaperSizeEnumByIndex(int index)
{
    const QVector<QPair<int, QString>>& PrintManager = GetPaperSizeEnumStringMap();
    if(index < 0 || index > PrintManager.size())
        return QPagedPaintDevice::PageSize::A4;
    else
        return (QPagedPaintDevice::PageSize)GetPaperSizeEnumStringMap()[index].first;
}
