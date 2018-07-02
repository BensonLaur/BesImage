#include "printSettingDialog.h"
#include<QPushButton>
#include<QLabel>
#include<QHBoxLayout>
#include<QDebug>
#include<QFile>
#include<QApplication>


PrintSettingDialog::PrintSettingDialog(QWidget *parent) :
    baseDialog(parent)
{
    setStyleSheet("TopWidgets{background:transparent;}");
    setMouseTracking(true);

    setupUi(&m_mainwid);        //初始化UI 布局

    QDoubleValidator* validator = new QDoubleValidator(0,1,2,this);
    lineEditLeftMargin->setValidator(validator);
    lineEditTopMargin->setValidator(validator);
    lineEditRightMargin->setValidator(validator);
    lineEditBottomMargin->setValidator(validator);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    connect(comboBoxPaperSize, SIGNAL(currentIndexChanged(int)), this, SLOT(curComboPaperSizeChange(int)));
    connect(radioButtonPortrait, SIGNAL(toggled(bool)), this, SLOT(radioChanged()));

    connect(lineEditLeftMargin,SIGNAL(textChanged(QString)),this,SLOT(marginLeftChanged(QString)));
    connect(lineEditTopMargin,SIGNAL(textChanged(QString)),this,SLOT(marginTopChanged(QString)));
    connect(lineEditRightMargin,SIGNAL(textChanged(QString)),this,SLOT(marginRightChanged(QString)));
    connect(lineEditBottomMargin,SIGNAL(textChanged(QString)),this,SLOT(marginBottomChanged(QString)));

    connect(checkboxKeepAspectRatio, SIGNAL(toggled(bool)), this, SLOT(checkboxChanged()));
}


void PrintSettingDialog::setupUi(QWidget *MainWindow)
{
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QStringLiteral("MainWindow"));
    MainWindow->resize(300, 300);

    vLayoutMain = new QVBoxLayout();
    vLayoutMain->setSpacing(6);
    vLayoutMain->setObjectName(QStringLiteral("vLayoutMain"));
    vLayoutMain->setContentsMargins(30, 60, 30, 30);


    groupBoxPaperSize = new QGroupBox(MainWindow);
    groupBoxPaperSize->setObjectName(QStringLiteral("groupBoxPaperSize"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(groupBoxPaperSize->sizePolicy().hasHeightForWidth());
    groupBoxPaperSize->setSizePolicy(sizePolicy);
    groupBoxPaperSize->setMinimumSize(QSize(200, 90));
    groupBoxPaperSize->setMaximumSize(QSize(1920, 90));


    layoutGroupBoxPaperSize = new QHBoxLayout(groupBoxPaperSize);   //纸张大小对应的groupBox
    layoutGroupBoxPaperSize->setSpacing(6);
    layoutGroupBoxPaperSize->setContentsMargins(11, 11, 11, 11);
    layoutGroupBoxPaperSize->setObjectName(QStringLiteral("layoutGroupBoxPaperSize"));

    hlayoutPaperSize = new QHBoxLayout();       //纸张大小
    hlayoutPaperSize->setSpacing(6);
    hlayoutPaperSize->setObjectName(QStringLiteral("hlayoutPaperSize"));
    labelPaperSize = new QLabel(groupBoxPaperSize);
    labelPaperSize->setObjectName(QStringLiteral("labelPaperSize"));
    QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(labelPaperSize->sizePolicy().hasHeightForWidth());
    labelPaperSize->setSizePolicy(sizePolicy1);
    labelPaperSize->setMinimumSize(QSize(100, 25));
    labelPaperSize->setMaximumSize(QSize(100, 25));
    labelPaperSize->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    hlayoutPaperSize->addWidget(labelPaperSize);

    comboBoxPaperSize = new QComboBox(groupBoxPaperSize);
    comboBoxPaperSize->setObjectName(QStringLiteral("comboBoxPaperSize"));
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(comboBoxPaperSize->sizePolicy().hasHeightForWidth());
    comboBoxPaperSize->setSizePolicy(sizePolicy2);
    comboBoxPaperSize->setMinimumSize(QSize(150, 25));
    comboBoxPaperSize->setMaximumSize(QSize(300, 25));

    hlayoutPaperSize->addWidget(comboBoxPaperSize);

    layoutGroupBoxPaperSize->addLayout(hlayoutPaperSize);



    vLayoutMain->addWidget(groupBoxPaperSize);

    hLayoutOrientAndMargins = new QHBoxLayout();
    hLayoutOrientAndMargins->setSpacing(6);
    hLayoutOrientAndMargins->setObjectName(QStringLiteral("hLayoutOrientAndMargins"));
    groupBoxOrientation = new QGroupBox(MainWindow);
    groupBoxOrientation->setObjectName(QStringLiteral("groupBoxOrientation"));
    QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(groupBoxOrientation->sizePolicy().hasHeightForWidth());
    groupBoxOrientation->setSizePolicy(sizePolicy3);
    groupBoxOrientation->setMinimumSize(QSize(100, 100));
    groupBoxOrientation->setMaximumSize(QSize(200, 200));
    horizontalLayout_7 = new QHBoxLayout(groupBoxOrientation);
    horizontalLayout_7->setSpacing(6);
    horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
    vLayoutOrientation = new QVBoxLayout();
    vLayoutOrientation->setSpacing(6);
    vLayoutOrientation->setObjectName(QStringLiteral("vLayoutOrientation"));
    radioButtonPortrait = new QRadioButton(groupBoxOrientation);
    radioButtonPortrait->setObjectName(QStringLiteral("radioButtonPortrait"));

    vLayoutOrientation->addWidget(radioButtonPortrait);

    radioButtonLandscape = new QRadioButton(groupBoxOrientation);
    radioButtonLandscape->setObjectName(QStringLiteral("radioButtonLandscape"));

    vLayoutOrientation->addWidget(radioButtonLandscape);


    horizontalLayout_7->addLayout(vLayoutOrientation);


    hLayoutOrientAndMargins->addWidget(groupBoxOrientation);

    groupBoxMargins = new QGroupBox(MainWindow);
    groupBoxMargins->setObjectName(QStringLiteral("groupBoxMargins"));
    sizePolicy3.setHeightForWidth(groupBoxMargins->sizePolicy().hasHeightForWidth());
    groupBoxMargins->setSizePolicy(sizePolicy3);
    groupBoxMargins->setMinimumSize(QSize(200, 100));
    groupBoxMargins->setMaximumSize(QSize(400, 200));
    horizontalLayout_6 = new QHBoxLayout(groupBoxMargins);
    horizontalLayout_6->setSpacing(6);
    horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
    gLayoutMargins = new QGridLayout();
    gLayoutMargins->setSpacing(6);
    gLayoutMargins->setObjectName(QStringLiteral("gLayoutMargins"));
    hLayoutMarginLeft = new QHBoxLayout();
    hLayoutMarginLeft->setSpacing(6);
    hLayoutMarginLeft->setObjectName(QStringLiteral("hLayoutMarginLeft"));
    labelLeftMargin = new QLabel(groupBoxMargins);
    labelLeftMargin->setObjectName(QStringLiteral("labelLeftMargin"));
    sizePolicy1.setHeightForWidth(labelLeftMargin->sizePolicy().hasHeightForWidth());
    labelLeftMargin->setSizePolicy(sizePolicy1);
    labelLeftMargin->setMinimumSize(QSize(60, 25));
    labelLeftMargin->setMaximumSize(QSize(60, 25));
    labelLeftMargin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    hLayoutMarginLeft->addWidget(labelLeftMargin);

    lineEditLeftMargin = new QLineEdit(groupBoxMargins);
    lineEditLeftMargin->setObjectName(QStringLiteral("lineEditLeftMargin"));
    sizePolicy1.setHeightForWidth(lineEditLeftMargin->sizePolicy().hasHeightForWidth());
    lineEditLeftMargin->setSizePolicy(sizePolicy1);
    lineEditLeftMargin->setMinimumSize(QSize(50, 0));
    lineEditLeftMargin->setMaximumSize(QSize(60, 16777215));

    hLayoutMarginLeft->addWidget(lineEditLeftMargin);

    gLayoutMargins->addLayout(hLayoutMarginLeft, 0, 0, 1, 1);

    hLayoutMarginRight = new QHBoxLayout();
    hLayoutMarginRight->setSpacing(6);
    hLayoutMarginRight->setObjectName(QStringLiteral("hLayoutMarginRight"));
    labelRightMargin = new QLabel(groupBoxMargins);
    labelRightMargin->setObjectName(QStringLiteral("labelRightMargin"));
    sizePolicy1.setHeightForWidth(labelRightMargin->sizePolicy().hasHeightForWidth());
    labelRightMargin->setSizePolicy(sizePolicy1);
    labelRightMargin->setMinimumSize(QSize(60, 25));
    labelRightMargin->setMaximumSize(QSize(60, 25));
    labelRightMargin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    hLayoutMarginRight->addWidget(labelRightMargin);

    lineEditRightMargin = new QLineEdit(groupBoxMargins);
    lineEditRightMargin->setObjectName(QStringLiteral("lineEditRightMargin"));
    sizePolicy1.setHeightForWidth(lineEditRightMargin->sizePolicy().hasHeightForWidth());
    lineEditRightMargin->setSizePolicy(sizePolicy1);
    lineEditRightMargin->setMinimumSize(QSize(50, 0));
    lineEditRightMargin->setMaximumSize(QSize(60, 16777215));

    hLayoutMarginRight->addWidget(lineEditRightMargin);


    gLayoutMargins->addLayout(hLayoutMarginRight, 0, 1, 1, 1);

    hLayoutMarginTop = new QHBoxLayout();
    hLayoutMarginTop->setSpacing(6);
    hLayoutMarginTop->setObjectName(QStringLiteral("hLayoutMarginTop"));
    labelTopMargin = new QLabel(groupBoxMargins);
    labelTopMargin->setObjectName(QStringLiteral("labelTopMargin"));
    sizePolicy1.setHeightForWidth(labelTopMargin->sizePolicy().hasHeightForWidth());
    labelTopMargin->setSizePolicy(sizePolicy1);
    labelTopMargin->setMinimumSize(QSize(60, 25));
    labelTopMargin->setMaximumSize(QSize(60, 25));
    labelTopMargin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    hLayoutMarginTop->addWidget(labelTopMargin);

    lineEditTopMargin = new QLineEdit(groupBoxMargins);
    lineEditTopMargin->setObjectName(QStringLiteral("lineEditTopMargin"));
    sizePolicy1.setHeightForWidth(lineEditTopMargin->sizePolicy().hasHeightForWidth());
    lineEditTopMargin->setSizePolicy(sizePolicy1);
    lineEditTopMargin->setMinimumSize(QSize(50, 0));
    lineEditTopMargin->setMaximumSize(QSize(60, 16777215));

    hLayoutMarginTop->addWidget(lineEditTopMargin);


    gLayoutMargins->addLayout(hLayoutMarginTop, 1, 0, 1, 1);

    hLayoutMarginBottom = new QHBoxLayout();
    hLayoutMarginBottom->setSpacing(6);
    hLayoutMarginBottom->setObjectName(QStringLiteral("hLayoutMarginBottom"));
    labelBottomMargin = new QLabel(groupBoxMargins);
    labelBottomMargin->setObjectName(QStringLiteral("labelBottomMargin"));
    sizePolicy1.setHeightForWidth(labelBottomMargin->sizePolicy().hasHeightForWidth());
    labelBottomMargin->setSizePolicy(sizePolicy1);
    labelBottomMargin->setMinimumSize(QSize(60, 25));
    labelBottomMargin->setMaximumSize(QSize(60, 25));
    labelBottomMargin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    hLayoutMarginBottom->addWidget(labelBottomMargin);

    lineEditBottomMargin = new QLineEdit(groupBoxMargins);
    lineEditBottomMargin->setObjectName(QStringLiteral("lineEditBottomMargin"));
    sizePolicy1.setHeightForWidth(lineEditBottomMargin->sizePolicy().hasHeightForWidth());
    lineEditBottomMargin->setSizePolicy(sizePolicy1);
    lineEditBottomMargin->setMinimumSize(QSize(50, 0));
    lineEditBottomMargin->setMaximumSize(QSize(60, 16777215));

    hLayoutMarginBottom->addWidget(lineEditBottomMargin);

    gLayoutMargins->addLayout(hLayoutMarginBottom, 1, 1, 1, 1);

    horizontalLayout_6->addLayout(gLayoutMargins);  //距边值 layout 加入到 groupBoxMargins 对应的 horizontalLayout_6


    hLayoutOrientAndMargins->addWidget(groupBoxMargins);


    vLayoutMain->addLayout(hLayoutOrientAndMargins);

    checkboxKeepAspectRatio = new QCheckBox(MainWindow);
    checkboxKeepAspectRatio->setObjectName(QStringLiteral("checkboxKeepAspectRatio"));
    checkboxKeepAspectRatio->setText(tr("保持图像原比例"));
    checkboxKeepAspectRatio->setMinimumHeight(30);
    QSizePolicy sizePolicyCheckbox(QSizePolicy::Minimum, QSizePolicy::Fixed);
    sizePolicyCheckbox.setHorizontalStretch(0);
    checkboxKeepAspectRatio->setSizePolicy(sizePolicyCheckbox);
    vLayoutMain->addWidget(checkboxKeepAspectRatio);

    buttonBox = new QDialogButtonBox(MainWindow);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    buttonBox->button(QDialogButtonBox::Ok)->setText("确定");
    buttonBox->button(QDialogButtonBox::Cancel)->setText("取消");

    vLayoutMain->addWidget(buttonBox);

    MainWindow->setLayout(vLayoutMain);

#ifndef QT_NO_SHORTCUT
    labelPaperSize->setBuddy(comboBoxPaperSize);
    labelLeftMargin->setBuddy(lineEditLeftMargin);
    labelRightMargin->setBuddy(lineEditRightMargin);
    labelTopMargin->setBuddy(lineEditTopMargin);
    labelBottomMargin->setBuddy(lineEditBottomMargin);
#endif // QT_NO_SHORTCUT

    retranslateUi(MainWindow);

    //QMetaObject::connectSlotsByName(MainWindow);
} // setupUi

//恢复载入界面数据
void PrintSettingDialog::restoreUiData(PrintParameter param)
{   
    //恢复 comboBoxPaperSize 数据
    comboBoxPaperSize->clear();

    QVector<QPair<int, QString>> vecPaperSizePair
                = PrintManager::GetInstance().GetPaperSizeEnumStringMap();

    QStringList pageSizeList;
    for(auto& pair: vecPaperSizePair)
    {
          pageSizeList << pair.second;
    }

    comboBoxPaperSize->addItems(pageSizeList);

    comboBoxPaperSize->setCurrentIndex(param.pageSize);

    //恢复 groupBoxOrientation 数据
    if(param.orientation == QPrinter::Orientation::Landscape)
        radioButtonLandscape->setChecked(true);
    else
        radioButtonPortrait->setChecked(true);

    //恢复 margins 4 个文本数据
    lineEditLeftMargin->setText(QString::number(param.margins.left));
    lineEditTopMargin->setText(QString::number(param.margins.top));
    lineEditRightMargin->setText(QString::number(param.margins.right));
    lineEditBottomMargin->setText(QString::number(param.margins.bottom));

    //保持比例checkbox
    checkboxKeepAspectRatio->setChecked(param.keepAspectRatio);
}

void PrintSettingDialog::retranslateUi(QWidget *MainWindow)
{
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
    groupBoxPaperSize->setTitle(QApplication::translate("MainWindow", "\347\272\270\345\274\240", Q_NULLPTR));
    labelPaperSize->setText(QApplication::translate("MainWindow", "\345\244\247\345\260\217(&Z):", Q_NULLPTR));
    groupBoxOrientation->setTitle(QApplication::translate("MainWindow", "\346\226\271\345\220\221", Q_NULLPTR));
    radioButtonPortrait->setText(QApplication::translate("MainWindow", "\347\272\265\345\220\221(&O)", Q_NULLPTR));
    radioButtonLandscape->setText(QApplication::translate("MainWindow", "\346\250\252\345\220\221(&A)", Q_NULLPTR));
    groupBoxMargins->setTitle(QApplication::translate("MainWindow", "\351\241\265\350\276\271\350\267\235(\346\257\253\347\261\263)", Q_NULLPTR));
    labelLeftMargin->setText(QApplication::translate("MainWindow", "\345\267\246(&L):", Q_NULLPTR));
    labelRightMargin->setText(QApplication::translate("MainWindow", "\345\217\263(&R):", Q_NULLPTR));
    labelTopMargin->setText(QApplication::translate("MainWindow", "\344\270\212(&T):", Q_NULLPTR));
    labelBottomMargin->setText(QApplication::translate("MainWindow", "\344\270\213(&B):", Q_NULLPTR));
} // retranslateUi



void PrintSettingDialog::curComboPaperSizeChange(int index)
{
    QVector<QPair<int, QString>> vecPaperSizePair
                = PrintManager::GetInstance().GetPaperSizeEnumStringMap();

    if(index == -1 || index >= vecPaperSizePair.size())
        return;

    m_param.pageSize = index;
}


void PrintSettingDialog::radioChanged()
{
    m_param.orientation = radioButtonLandscape->isChecked() ?
                QPrinter::Orientation::Landscape : QPrinter::Orientation::Portrait;
}


void PrintSettingDialog::marginLeftChanged(QString text)
{
    m_param.margins.left = text.toDouble();
}

void PrintSettingDialog::marginTopChanged(QString text)
{
    m_param.margins.top = text.toDouble();
}

void PrintSettingDialog::marginRightChanged(QString text)
{
    m_param.margins.right = text.toDouble();
}

void PrintSettingDialog::marginBottomChanged(QString text)
{
    m_param.margins.bottom = text.toDouble();
}

void PrintSettingDialog::checkboxChanged()
{
    m_param.keepAspectRatio = checkboxKeepAspectRatio->isChecked();
}
