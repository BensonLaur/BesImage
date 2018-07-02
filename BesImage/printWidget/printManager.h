#ifndef PRINTMANAGER_H
#define PRINTMANAGER_H

#include <QDebug>
#include <QObject>
#include <QPainter>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>

class PrintParameter{
public:
        QPagedPaintDevice::PageSize pageSize;   //页面大小
        QPagedPaintDevice::Margins  margins;    //页边距（单位为毫米）
        QPrinter::Orientation       orientation;//方向
};

class PrintManager: public QObject{

    Q_OBJECT

    /* 单例访问打印管理器 */
public:
    static PrintManager& GetInstance();

    ~PrintManager(){}

private:
    PrintManager(){}

public:
    //获得打印参数 (如果未加载自动去文件读取，已加载则使用已载入的参数。bForceLoadFromFile 强制从文件获得最新参数)
    bool GetPrintParameter(PrintParameter& param, bool bForceLoadFromFile);
    bool SetPrintParameter(PrintParameter param);                   //设置打印参数

    //打印一个图片
    void PrintOnePixmap(const QPixmap& pixmap, QWidget *parent = Q_NULLPTR);

    //预览一个图片
    void PreviewPixmap(const QPixmap& pixmap, QWidget *parent = Q_NULLPTR);

    //打印多张图片
    void PrintMultiPixmap(const QVector<QString>& vecImagePath, QWidget *parent = Q_NULLPTR);

    //打印多张图片
    void PrintMultiPixmap(const QVector<QPixmap>& vecPixmap, QWidget *parent = Q_NULLPTR);

public slots:
    //预览当前选中图片
    void printPreviewSlot(QPrinter *printerPixmap);

private:

    //从默认路径中加载打印参数
    bool LoadPrintSetting();

    //保存到打印参数
    bool SavePrintSetting();

private:
    PrintParameter m_param;                 //打印参数

private:
    QWidget *m_previewPaintDevice;
    QPixmap m_pixmapToPreview;              //要预览的图片
    QPixmap m_pixmapToPrint;                //要打印的单个图片
    QVector<QPixmap> m_vecPixmapToPrint;    //要打印的多个图片
};

#endif // PRINTMANAGER_H
