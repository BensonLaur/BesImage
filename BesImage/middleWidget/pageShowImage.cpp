#include "pageShowImage.h"

PageShowImage::PageShowImage(QWidget*parent)
    :baseWidget(parent)
    ,imageScaler(this)
{
    setStyleSheet("baseWidget{background:black;}");
    initLayout();
}


void PageShowImage::initLayout()
{
    SetImageForShow(":/image/skin/default.jpg");

	QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->addWidget(&imageScaler);
	setLayout(hLayout);
}


void PageShowImage::SetImageForShow(QString path)
{
    imageScaler.SetImage(QImage(path));
}
