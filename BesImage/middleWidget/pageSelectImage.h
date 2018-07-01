#ifndef PAGE_SELCET_H
#define PAGE_SELCET_H

#include <QApplication>
#include <QObject>
#include <QWidget>
#include<QPushButton>
#include<QLineEdit>
#include<QSpacerItem>

#include"baseWidget.h"
#include"myPushButton.h"
#include <QTreeView>
#include <QListWidget>
#include <QDirModel>
#include <QDir>
#include <QFileIconProvider>
#include <QHBoxLayout>

#include <QPainter>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>

class PageSelectImage : public baseWidget
{

    Q_OBJECT
public:
    explicit PageSelectImage(QWidget *parent = 0);

    void initWidget();

    void setlistShowStyle();
    void setlistHideStyle();

    bool LoadFloder(QString path);                      //载入文件夹/文件

    void SetImageSuffixFilters(QStringList suffixList); //设置图片后缀名过滤，形如如"png"

    bool ScaleImageListOnce(bool bAdding);              //缩放列表一次， bAdding 表示是否增加大小

    void printLastSelectFiles();                        //打印最后一次选择的图片

protected:
    bool eventFilter(QObject *, QEvent *);


public Q_SLOTS:
    void showImgUnderTreeItem(const QModelIndex &index);    //显示文件树项对应的图片

    virtual void wheelEvent(QWheelEvent *event);

    void slot_btnclicked();

    void OnClickImgItem(const QModelIndex &index);

 signals:
    void OnSelectOnePath(QString imagePath);                            //选中一个显示的路径
    void OnSelectBunchPath(QVector<QString> vecImagePath, int curSel);  //选中整个路径集合
    void OnSelectIndexInSet(int curSel);                                //选中集合中的某个下标

private:
    QTreeView fileTree;             //文件树
    QListWidget imageList;          //缩略图标
    myPushButton m_btnhidelist;     //隐藏列表

private:

    QStringList  listSuffixFilters;         //文件后缀列表，形如"png"
    QSize sizeIconLast;                     //最后显示的图标大小
    QVector<QString> vecLastFilePath;       //最后一次选择的文件夹路径

    bool bNeedToReloadImageSet;     //标记是否需要重新载入整个图像集合

};


#endif // PAGE_SELCET_H
