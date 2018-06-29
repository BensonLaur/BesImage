#ifndef MIDDLELEFTSTACKWIDGET2_H
#define MIDDLELEFTSTACKWIDGET2_H

#include <QObject>
#include <QWidget>
#include"baseWidget.h"
#include<QVBoxLayout>
#include <QImage>
#include <QLabel>
#include "widgetImageScaler.h"

class PageShowImage:public baseWidget
{
    Q_OBJECT
public:
   explicit PageShowImage(QWidget *parent);
    void initLayout();

    QImage image;
    QLabel imageLabel;

    //WidgetImageScaler imageScaler;
};

#endif // MIDDLELEFTSTACKWIDGET2_H
