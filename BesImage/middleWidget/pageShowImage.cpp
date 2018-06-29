#include "pageShowImage.h"

PageShowImage::PageShowImage(QWidget*parent)
    :baseWidget(parent)
    ,image("E:\\project\\Qt project\\BesImage\\BesImage\\image\\middlewidget\\lab_backups.png")
    ,imageLabel(this)
    //,imageScaler(this)
{
    setStyleSheet("baseWidget{background:black;}");
    initLayout();
}


void PageShowImage::initLayout()
{
//    imageScaler.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
//    imageScaler.setMinimumSize(500,500);
//    imageScaler.setMaximumSize(2000,2000);

    //imageScaler.SetImage("C:\\Users\\Benso\\Desktop\\12313123.png");

//    QHBoxLayout* hLayout = new QHBoxLayout();
//    hLayout->addWidget(&imageLabel);
//    setLayout(hLayout);

//    QSize labelSize = imageScaler.size();


//    imageLabel.setAlignment(Qt::AlignCenter);
}
