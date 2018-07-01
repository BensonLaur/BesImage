#ifndef TOPWIDGETS_H
#define TOPWIDGETS_H

#include "global.h"
#include <QObject>
#include <QWidget>
#include<QPushButton>
#include<QLineEdit>
#include<QSpacerItem>

#include"baseWidget.h"
#include"myPushButton.h"
#include"toolbarWidget.h"

class TopWidgets : public baseWidget
{
    Q_OBJECT
public:
    explicit TopWidgets(QWidget *parent = 0);
    void initWidget();


signals:
   void OnHeaderMouseDoubleClickEvent(QMouseEvent *e);

protected:
    bool eventFilter(QObject *, QEvent *);

    virtual void mouseDoubleClickEvent(QMouseEvent *event);


public:
    myPushButton m_btnexit;
    myPushButton m_btnmini;
    toolbarWidget m_toolbar;
};

#endif // TOPWIDGETS_H
