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
#include"topSearchTipsWidget.h"

class TopWidgets : public baseWidget
{

    Q_OBJECT
public:
    explicit TopWidgets(QWidget *parent = 0);
    void initWidget();

    myPushButton m_btnexit;
    myPushButton m_btnmini;

signals:
   void OnHeaderMouseDoubleClickEvent(QMouseEvent *e);

protected:
    bool eventFilter(QObject *, QEvent *);

    virtual void mouseDoubleClickEvent(QMouseEvent *event);
signals:
};

#endif // TOPWIDGETS_H
