#include "mainwindow.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setApplicationVersion(QString("1.0.0.0"));
    QCommandLineParser parser;
    parser.setApplicationDescription("Qt Dir View Example 【Qt目录查看例子】");
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption dontUseCustomDirectoryIconsOption("c", "设置 QFileIconProvider::DontUseCustomDirectoryIcons");
    parser.addOption(dontUseCustomDirectoryIconsOption);
    parser.addPositionalArgument("directory", "The directory to start in.");
    parser.process(app);
    const QString rootPath = parser.positionalArguments().isEmpty()
        ? QString() : parser.positionalArguments().first();


    app.setStyleSheet("QMenu{background-color: white;border: 1px solid rgb(214,214,214);}"
                    "QMenu::item{height: 28px;padding: 0px 20px 0px 40px;font-size : 12px;color: rgb(102, 102, 102);font-family: 微软雅黑;}"
                    "QMenu::item:focus{padding: -1;}"
                    "QMenu::item:!enabled{color:rgb(150,150,150);}"
                    "QMenu::item:selected{color: white;background-color: rgb(22, 154, 243);}"
                    "QMenu::icon{position: absolute;left: 12px;}"
                    "QMenu::separator{height:1px;background: rgb(209,209,209);margin:4px 0px 4px 0px;}"
                    "QPushButton:focus{padding: -1;}"
                    "QLabel:focus{padding: -1;}");

    MainWindow*pMain = MainWindow::GetInstance();
    pMain->show();

    return app.exec();
}
