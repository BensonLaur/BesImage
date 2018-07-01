#include "toolbarWidget.h"

toolbarWidget::toolbarWidget(QWidget*p)
    :baseWidget(p)
    ,btnReturn  (this)
    ,btnPrintAll(this)
    ,btnPrintOne(this)
    ,btnPrintPreview(this)
{
    setMouseTracking(true);
    setStyleSheet("QWidget{background:black;}");

    initLayout();
}

void toolbarWidget::initLayout()
{
    setMinimumSize(500,50);
    setMaximumSize(1920,50);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    QHBoxLayout *hmainyout=new QHBoxLayout;

    QHBoxLayout *hyout1=new QHBoxLayout;

    btnReturn.setFixedSize(50,50);
    btnPrintAll.setFixedSize(50,50);
    btnPrintOne.setFixedSize(50,50);
    btnPrintPreview.setFixedSize(50,50);

    btnReturn.setObjectName("btnPrintOne");
    btnPrintAll.setObjectName("btnPrintAll");
    btnPrintOne.setObjectName("btnPrintOne");
    btnPrintPreview.setObjectName("btnPrintOne");

    btnReturn.setStyleSheet("QPushButton{border-image:url(:/image/toolbar/btnReturn-normal.png)}"
                            "QPushButton:hover{border-image:url(:/image/toolbar/btnReturn-hover.png)}"
                            "QPushButton:pressed{border-image:url(:/image/toolbar/btnReturn-press.png)}");
    btnPrintAll.setStyleSheet("QPushButton{border-image:url(:/image/toolbar/print-all-normal.png)}"
                              "QPushButton:hover{border-image:url(:/image/toolbar/print-all-hover.png)}"
                              "QPushButton:pressed{border-image:url(:/image/toolbar/print-all-press.png)}");
    btnPrintOne.setStyleSheet("QPushButton{border-image:url(:/image/toolbar/print-one-normal.png)}"
                            "QPushButton:hover{border-image:url(:/image/toolbar/print-one-hover.png)}"
                            "QPushButton:pressed{border-image:url(:/image/toolbar/print-one-press.png)}");
    btnPrintPreview.setStyleSheet("QPushButton{border-image:url(:/image/toolbar/print-preview-normal.png)}"
                            "QPushButton:hover{border-image:url(:/image/toolbar/print-preview-hover.png)}"
                            "QPushButton:pressed{border-image:url(:/image/toolbar/print-preview-press.png)}");

    hyout1->addWidget(&btnPrintPreview);
    hyout1->addWidget(&btnPrintOne);
    hyout1->addWidget(&btnPrintAll);
    hyout1->addWidget(&btnReturn);
    hyout1->setSpacing(0);

    hmainyout->addSpacerItem(new QSpacerItem(110,50,QSizePolicy::Expanding));//膨胀
    hmainyout->addLayout(hyout1);
    hmainyout->setSpacing(0);
    hmainyout->setContentsMargins(0,0,0,0);
    setLayout(hmainyout);
}

