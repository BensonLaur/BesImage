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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initUI();          //初始化UI

    bool LoadFloder(QString DirPath); //载入文件夹

public Q_SLOTS:
    void showSelectedImg(const QModelIndex &index);


    private:
    QTreeView* fileTree;    //文件树
    QListWidget *imageList; //缩略图标



    QString lastResultMessage;                      //储存最后的结果信息
};

#endif // MAINWINDOW_H
