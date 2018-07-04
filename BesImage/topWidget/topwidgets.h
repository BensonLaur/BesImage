#ifndef TOPWIDGETS_H
#define TOPWIDGETS_H

#include "global.h"
#include <QObject>
#include <QWidget>
#include<QPushButton>
#include<QLineEdit>
#include<QSpacerItem>
#include <QIcon>
#include <QLabel>

#include"baseWidget.h"
#include"myPushButton.h"
#include"toolbarWidget.h"

class TopWidgets : public baseWidget
{
    Q_OBJECT
public:
    explicit TopWidgets(QWidget *parent = 0);

    //设置黑白图标路径，路径可以是运行目录相对路径 或 绝对路径
    void SetIcon(QString iconBlackPath,QString iconWhitePath);
    void SetIcon(QIcon iconBlack, QIcon iconWhite);               //设置黑色白色2个颜色的Icon
    void SetIconIfPathValid(const QString&);                      //在路径有效时设置图标
    void SetTitle(QString title);                                 //设置标题
    void SetColorBlackOrWhite(bool setBlack);                     //设置整体颜色白色或黑色

    void initWidget();

signals:
   void OnHeaderMouseDoubleClickEvent(QMouseEvent *e);

protected:
    bool eventFilter(QObject *, QEvent *);

    virtual void mouseDoubleClickEvent(QMouseEvent *event);

public:
    QIcon           m_iconBlack;           //黑色图标
    QIcon           m_iconWhite;           //白色图标
    QPushButton     m_btnIcon;             //显示应用图标
    QLabel          m_labelTitle;          //应用标题标签
    myPushButton    m_btnexit;             //关闭按钮
    myPushButton    m_btnmini;             //最小化按钮
    toolbarWidget   m_toolbar;            //工具栏
};

#endif // TOPWIDGETS_H
