#include "pageShowImage.h"

PageShowImage::PageShowImage(QWidget*parent)
    :baseWidget(parent)
    ,imageScaler(this)
    ,buttonLeft("<",this)
    ,buttonRight(">",this)
{
    setStyleSheet("baseWidget{background:black;}");

    buttonLeft.setStyleSheet("QPushButton{border-image:url(:/image/showImage/leftButton-normal.png)}"
                             "QPushButton:hover{border-image:url(:/image/showImage/leftButton-hover.png)}"
                             "QPushButton:pressed{border-image:url(:/image/showImage/leftButton-press.png)}");

    buttonRight.setStyleSheet("QPushButton{border-image:url(:/image/showImage/rightButton-normal.png)}"
                              "QPushButton:hover{border-image:url(:/image/showImage/rightButton-hover.png)}"
                              "QPushButton:pressed{border-image:url(:/image/showImage/rightButton-press.png)}");


    initLayout();

    connect(&buttonLeft, SIGNAL(released()), &imageScaler, SLOT(ShowPreImage()));
    connect(&buttonRight, SIGNAL(released()), &imageScaler, SLOT(ShowNextImage()));

    //以下2个连接必须在上面连接之后，以按顺序先选择图片后，在执行检测图片显示状态和更新按钮状态
    connect(&buttonLeft, SIGNAL(released()), this, SLOT(UpdateLeftRightButtonStatus()));
    connect(&buttonRight, SIGNAL(released()), this, SLOT(UpdateLeftRightButtonStatus()));
}


void PageShowImage::initLayout()
{
    SetOneImageForShow(":/image/skin/default.jpg");

    QStackedLayout* stackLayout = new QStackedLayout();
    stackLayout->setStackingMode(QStackedLayout::StackAll); //所有控件都可见
    stackLayout->addWidget(&imageScaler);
    stackLayout->addWidget(&buttonLeft);
    stackLayout->addWidget(&buttonRight);

    stackLayout->setCurrentIndex(0);
    stackLayout->setCurrentIndex(1);
    stackLayout->setCurrentIndex(2);

    setLayout(stackLayout);

    UpdateLeftRightButtonStatus();
}

//设置一张显示的图片
void PageShowImage::SetOneImageForShow(QString path)
{
    imageScaler.SetImage(QImage(path));

    UpdateLeftRightButtonStatus();
}

//设置一个集合显示的图片
void PageShowImage::SetBunchImageForShow(QVector<QString> vecImagePath, int indexSelect)
{
    imageScaler.SetImageSet(vecImagePath, indexSelect);

    UpdateLeftRightButtonStatus();
}

//设置显示当前集合的第 indexSelect 张图片
void PageShowImage::ShowImageInSetShowing(int indexSelect)
{
    imageScaler.ShowSelImage(indexSelect);

    UpdateLeftRightButtonStatus();
}

//更新左右按钮的显示状态
void PageShowImage::UpdateLeftRightButtonStatus()
{
    buttonLeft.setVisible(imageScaler.HasPreImage());
    buttonRight.setVisible(imageScaler.HasNextImage());

    //本来改变按钮可见状态即可，不知为什么 左右按钮 自动变回了整个窗口的大小，
    //在此处重新改变大小也无效，而在 resizeEvent 中改变大小却可以
    //故可以改变大小，触发 resizeEvent

    resize(size()-QSize(1,1));      //这里目的是为了触发 resizeEvent
    resize(size()+QSize(1,1));
}

void PageShowImage::resizeEvent(QResizeEvent* event)
{
    baseWidget::resizeEvent(event);

    QRect paranetRect = this->geometry();
    QRect leftRect = QRect(0,paranetRect.height()/2 - 80,80,160);
    QRect rightRect = QRect(paranetRect.width() - 80,paranetRect.height()/2 - 80,80,160);

    buttonLeft.setGeometry(leftRect);
    buttonRight.setGeometry(rightRect);
    imageScaler.setGeometry(paranetRect);
}

