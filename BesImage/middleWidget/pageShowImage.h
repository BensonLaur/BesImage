#ifndef MIDDLELEFTSTACKWIDGET2_H
#define MIDDLELEFTSTACKWIDGET2_H

#include <QObject>
#include <QWidget>
#include"baseWidget.h"
#include<QVBoxLayout>
#include <QStackedLayout>
#include <QImage>
#include <QLabel>
#include "widgetImageScaler.h"
#include "myPushButton.h"

class PageShowImage:public baseWidget
{
    Q_OBJECT
public:
   explicit PageShowImage(QWidget *parent);
    void initLayout();

public slots:

    //设置一张显示的图片
    void SetOneImageForShow(QString path);

    //设置一个集合显示的图片
    void SetBunchImageForShow(QVector<QString> vecImagePath, int indexSelect);

    //设置显示当前集合的第 indexSelect 张图片
    void ShowImageInSetShowing(int indexSelect);

    //更新左右按钮的显示状态
    void UpdateLeftRightButtonStatus();

protected:
    virtual void resizeEvent(QResizeEvent* event);

private:
    WidgetImageScaler imageScaler;

    myPushButton buttonLeft;
    myPushButton buttonRight;

};

#endif // MIDDLELEFTSTACKWIDGET2_H
