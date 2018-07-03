#ifndef PRINTMANAGER_H
#define PRINTMANAGER_H

#include <QDebug>
#include <QObject>
#include <QPainter>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class PrintParameter{
public:
        //QPagedPaintDevice::PageSize pageSize;     //页面大小
        int                         pageSize;       //由原来存储枚举改为存储总列表下标
        QPagedPaintDevice::Margins  margins;        //页边距（单位为毫米）
        QPrinter::Orientation       orientation;    //方向
        bool                        keepAspectRatio;//是否保持图片纵横比例

        PrintParameter()
        {
            pageSize = QPagedPaintDevice::PageSize::A4;
            margins = {0,0,0,0};
            orientation = QPrinter::Orientation::Portrait;
            keepAspectRatio = false;
        }
};

class PrintManager: public QObject{

    Q_OBJECT

    /* 单例访问打印管理器 */
public:
    static PrintManager& GetInstance();

    ~PrintManager(){}

private:
    PrintManager():m_hasLoad(false){}

public:
    //获得打印参数 (如果未加载自动去文件读取，已加载则使用已载入的参数。bForceLoadFromFile 强制从文件获得最新参数)
    bool GetPrintParameter(PrintParameter& param, bool bForceLoadFromFile = false);
    bool SetPrintParameter(PrintParameter param);                   //设置打印参数

    const QVector<QPair<int, QString>>& GetPaperSizeEnumStringMap();       //获得页大小枚举字符串映射

    //打印一个图片
    void PrintOnePixmap(const QPixmap& pixmap, QWidget *parent = Q_NULLPTR);

    //预览一个图片
    void PreviewPixmap(const QPixmap& pixmap, QWidget *parent = Q_NULLPTR);

    //打印多张图片
    void PrintMultiPixmap(const QVector<QString>& vecImagePath, QWidget *parent = Q_NULLPTR);

    //打印多张图片
    void PrintMultiPixmap(const QVector<QPixmap>& vecPixmap, QWidget *parent = Q_NULLPTR);

private slots:
    //预览当前选中图片
    void printPreviewSlot(QPrinter *printerPixmap);

private:

    //从默认路径中加载打印参数
    bool LoadPrintSetting();

    //解析config
    void parseConfig(QXmlStreamReader &reader, PrintParameter &param);

    //解析margins
    void parseMargins(QXmlStreamReader &reader, PrintParameter &param);

    //保存到打印参数
    bool SavePrintSetting();

    bool MakeSureConfigPathAvailable(QString &path);  //确保配置路径可用，返回配置路径

    //通过下标获得页面大小的枚举值
    QPagedPaintDevice::PageSize GetPaperSizeEnumByIndex(int index);

private:
    PrintParameter m_param;                 //打印参数
    bool           m_hasLoad;               //标记是否已经加载参数


    QVector<QPair<int, QString>> vecPaperSizePair; //储存页面大小枚举和字符串表示的映射

private:
    QWidget *m_previewPaintDevice;
    QPixmap m_pixmapToPreview;              //要预览的图片
    QPixmap m_pixmapToPrint;                //要打印的单个图片
    QVector<QPixmap> m_vecPixmapToPrint;    //要打印的多个图片
};

#endif // PRINTMANAGER_H
