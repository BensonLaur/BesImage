#ifndef TOOLBAR_WIDGET_H
#define TOOLBAR_WIDGET_H

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
};

#endif // TOOLBAR_WIDGET_H
