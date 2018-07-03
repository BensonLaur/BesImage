#ifndef TOOLBAR_WIDGET_H
#define TOOLBAR_WIDGET_H

#include "global.h"
#include <QObject>
#include <QWidget>
#include "baseWidget.h"
#include "myPushButton.h"
#include <QHBoxLayout>
#
class toolbarWidget:public baseWidget
{
    Q_OBJECT
public:
    explicit toolbarWidget(QWidget*p=0);

    void initLayout();

protected:
//    void mouseMoveEvent(QMouseEvent*);
//    void leaveEvent(QEvent *);
//    void focusInEvent(QFocusEvent *);


public:
    myPushButton btnReturn;
    myPushButton btnPrintAll;
    myPushButton btnPrintOne;
    myPushButton btnPrintPreview;
    myPushButton btnSetting;
    myPushButton btnBackParent;     //从选中单个文件状态回到选中父目录状态
};

#endif // TOOLBAR_WIDGET_H
