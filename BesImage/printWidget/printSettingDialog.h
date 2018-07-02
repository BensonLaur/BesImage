#ifndef PRINT_SETTING_DIALOG_H
#define PRINT_SETTING_DIALOG_H

#include "global.h"
#include <QObject>
#include <QWidget>
#include<QPushButton>
#include<QSpacerItem>

#include "baseDialog.h"
#include"myPushButton.h"

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>


class PrintSettingDialog : public baseDialog
{
    Q_OBJECT
public:
    explicit PrintSettingDialog(QWidget *parent = 0);
    void initWidget();

    void setupUi(QWidget *MainWindow);          //设置界面布局

    void restoreUiData();                       //恢复载入界面数据

    void retranslateUi(QWidget *MainWindow);



public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *vLayoutMain;
    QGroupBox *groupBoxPaperSize;
    QHBoxLayout *layoutGroupBoxPaperSize;
    QHBoxLayout *hlayoutPaperSize;
    QLabel *labelPaperSize;
    QComboBox *comboBoxPaperSize;
    QHBoxLayout *hLayoutOrientAndMargins;
    QGroupBox *groupBoxOrientation;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *vLayoutOrientation;
    QRadioButton *radioButtonPortrait;
    QRadioButton *radioButtonLandscape;
    QGroupBox *groupBoxMargins;
    QHBoxLayout *horizontalLayout_6;
    QGridLayout *gLayoutMargins;
    QHBoxLayout *hLayoutMarginLeft;
    QLabel *labelLeftMargin;
    QLineEdit *lineEditLeftMargin;
    QHBoxLayout *hLayoutMarginRight;
    QLabel *labelRightMargin;
    QLineEdit *lineEditRightMargin;
    QHBoxLayout *hLayoutMarginTop;
    QLabel *labelTopMargin;
    QLineEdit *lineEditTopMargin;
    QHBoxLayout *hLayoutMarginBottom;
    QLabel *labelBottomMargin;
    QLineEdit *lineEditBottomMargin;
    QDialogButtonBox *buttonBox;

};

#endif // PRINT_SETTING_DIALOG_H
