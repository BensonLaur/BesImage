#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVBoxLayout>
#include "absFiles/basewindow.h"
#include "topWidget/topwidgets.h"
#include "middleWidget/middleWidget.h"
#include "appConfig.h"

class MainWindow : public baseWindow
{
    friend class baseWidget;           //baseWidget 需要访问 MainWindow 的 mouseMoveEvent 以实现鼠标图标正常行为
    Q_OBJECT

public:
    //实现单例模式访问
    static MainWindow *GetInstance();

    ~MainWindow(){}

private:
    static MainWindow *s_pMainWnd;

    MainWindow(QWidget *parent = 0);

private:
    void initUI();                      //初始化UI
    void ApplyAppConfig();              //应用配置

    void clearBackground();

    void setCurBGPic(const QString&);           //直接设置背景图片
    void setCurBGPicIfValid(const QString&);    //在路径有效时设置背景图片

public slots:

    void OnWindowHeaderDbClick(QMouseEvent *e);     //窗口头双击

    void settingPrintParam();           //设置打印参数
    void previewCurrentImage();         //预览当前图片
    void printCurrentImage();           //打印当前图片
    void printCurrentDir();             //打印整个目录的图片

    void pageChanged(int index);        //页面发生改变

    void UpdateToolbarOnFilesSelectedChanged();  //在选中树发生改变后 更新工具栏

    void ShowBtnBackToParent(bool);      //显示回到显示父目录的状态的按钮
private:
    TopWidgets topWidget;               //窗口上部控件
    MiddleWidget midWidget;             //窗口中间控件
};

#endif // MAINWINDOW_H
