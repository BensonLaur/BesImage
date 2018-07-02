#ifndef PRINT_SETTING_DIALOG_H
#define PRINT_SETTING_DIALOG_H

#include "global.h"
#include <QObject>
#include <QWidget>
#include<QPushButton>
#include<QSpacerItem>

#include "baseDialog.h"
#include"myPushButton.h"
#include "printManager.h"

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
#include <QtWidgets/QCheckBox>


class PrintSettingDialog : public baseDialog
{
    Q_OBJECT
public:
    explicit PrintSettingDialog(QWidget *parent = 0);

    void setupUi(QWidget *MainWindow);          //设置界面布局

    void restoreUiData(PrintParameter param);   //恢复载入界面数据(使用外部LoadParam的数据)

    void retranslateUi(QWidget *MainWindow);

    void LoadParam(const PrintParameter& param)
    {
        m_param = param;                 //第一次将数据保存，在restoreUiData 中初始化数据
                                         //     会触发槽的执行中途改变 m_param，比如combobox构建中会触发2次选中时间，第一次是0
        restoreUiData(param);            //恢复载入界面数据
    }
    void GetParam(PrintParameter& param)
    {
        param = m_param;
    }

public slots:
    void curComboPaperSizeChange(int index);
    void radioChanged();
    void marginLeftChanged(QString text);
    void marginTopChanged(QString text);
    void marginRightChanged(QString text);
    void marginBottomChanged(QString text);
    void checkboxChanged();
private:
    PrintParameter m_param;

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
    QCheckBox *checkboxKeepAspectRatio;
    QDialogButtonBox *buttonBox;

};

#endif // PRINT_SETTING_DIALOG_H
