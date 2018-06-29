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

class PageSelectImage : public baseWidget
{

    Q_OBJECT
public:
    explicit PageSelectImage(QWidget *parent = 0);

    void initWidget();

    void setlistShowStyle();
    void setlistHideStyle();

    bool LoadFloder(QString path); //载入文件夹

    bool ScaleImageListOnce(bool bAdding);   //缩放列表一次， bAdding 表示是否增加大小

protected:
    bool eventFilter(QObject *, QEvent *);


public Q_SLOTS:
    void showSelectedImg(const QModelIndex &index);

    virtual void wheelEvent(QWheelEvent *event);

    void slot_btnclicked();
private:
    QTreeView fileTree;             //文件树

    QListWidget imageList;          //缩略图标

    myPushButton m_btnhidelist;     //隐藏列表
private:

    QVector<QString> vecLastFilePath;
    QSize sizeIconLast;

};


#endif // PAGE_SELCET_H
