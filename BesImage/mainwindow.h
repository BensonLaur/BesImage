#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QFileSystemModel>
#include <QDirModel>
#include <QFileIconProvider>
#include <QTreeView>
#include <QListWidget>
#include <QAbstractScrollArea>
#include "absFiles/basewindow.h"
#include "topWidget/topwidgets.h"
#include "middleWidget/middleWidget.h"

class MainWindow : public baseWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initUI();          //初始化UI

    void clearBackground();

    void setCurBGPic(const QString&);



private:
    TopWidgets topWidget;
    MiddleWidget midWidget;


    QString lastResultMessage;                      //储存最后的结果信息
};

#endif // MAINWINDOW_H
