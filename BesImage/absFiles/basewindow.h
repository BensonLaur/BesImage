#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include<QPaintEvent>
#include<QPainterPath>
#include<qmath.h>
#include<QPainter>
#include<QPainter>
#include<QStyleOption>
#include"AbsFrameLessAutoSize.h"

enum BGFillMode     //背景图片的填充模式
{
    BG_FILL_MODE_KEEP_ASPECT_RATIO_AND_FULL =0, //保持纵横比，且填满窗口
    BG_FILL_MODE_IGNORE_ASPECT_RATIO_AND_FULL,  //忽略纵横比，拉升填满窗口
    BG_FILL_MODE_ORIGINAL_SIZE_SINGLE,          //使用原来尺寸，不管是否填满窗口
    BG_FILL_MODE_ORIGINAL_SIZE_FULL,            //使用原来尺寸，不填满窗口时，重复图片
};

class Widget:public QWidget
{
    Q_OBJECT
public:
   explicit Widget(QWidget*parent=0);

    void SetBackgroundFillMode(BGFillMode fillMode);

    void setCurBGPic(const QString&);

    void clearBg();

    const QString currentSkinPath(){return m_curPixPath;}

    inline QPixmap getRectPix(const QRect&rect){update();return  m_curPix.copy(rect);}


protected:
    virtual void paintEvent(QPaintEvent *);
 public slots:
    void setSkin(const QString &str);
private:
    QString m_curPixPath;
    QPixmap m_netPic;
    QPixmap m_skinPic;
    QPixmap m_curPix; //not the normal size

    BGFillMode m_BGFillMode;        //背景填充模式
};

class baseWindow : public AbsFrameLessAutoSize
{
    Q_OBJECT
public:
    explicit baseWindow(QWidget *parent = 0);
    Widget m_mainwid;
protected:
    virtual void paintEvent(QPaintEvent *);   //实现白色背景 和 阴影效果
 private:

};

#endif // BASEWINDOW_H
