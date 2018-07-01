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
    friend class baseWidget;   //baseWidget 需要访问 MainWindow 的 mouseMoveEvent 以实现鼠标图标正常行为
    Q_OBJECT

public:
    ~MainWindow();

    //get Instance
    static MainWindow *GetInstance();

private:  //实现单例模式访问
    static MainWindow *s_pMainWnd;

    MainWindow(QWidget *parent = 0);

private:
    void initUI();          //初始化UI

    void clearBackground();

    void setCurBGPic(const QString&);

public slots:
    void OnHeaderMouseDoubleClickEvent(QMouseEvent *e);


private:
    TopWidgets topWidget;
    MiddleWidget midWidget;
};

#endif // MAINWINDOW_H
