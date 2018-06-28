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
    //const QString rootPath = parser.positionalArguments().isEmpty()
    //    ? QString() : parser.positionalArguments().first();

    MainWindow m;
    m.show();

//    QDirModel model;
//    model.setFilter(QDir::AllDirs|QDir::NoDotAndDotDot|QDir::Files);

//    QStringList nameFilters;
//    nameFilters << "*.bmp" << "*.png";
//    model.setNameFilters(nameFilters);

//    model.iconProvider()->setOptions(QFileIconProvider::DontUseCustomDirectoryIcons);

////    if (parser.isSet(dontUseCustomDirectoryIconsOption))
////        model.iconProvider()->setOptions(QFileIconProvider::DontUseCustomDirectoryIcons);

//    QTreeView fileTree;
//    fileTree.setModel(&model);
//    QString rootPath = "C:/";
//    if (!rootPath.isEmpty()) {
//        const QModelIndex rootIndex = model.index(QDir::cleanPath(rootPath));
//        if (rootIndex.isValid())
//            fileTree.setRootIndex(rootIndex);
//    }

//    // Demonstrating look and feel features
//    fileTree.setAnimated(true);
//    fileTree.setIndentation(15);
//    fileTree.setSortingEnabled(true);
//    //const QSize availableSize = QApplication::desktop()->availableGeometry(&tree).size();
//    fileTree.resize(QSize(500,500));
////    fileTree.setColumnWidth(0, 500*0.9);
////    fileTree.setColumnHidden(1, true);
////    fileTree.setColumnHidden(2, true);
////    fileTree.setColumnHidden(3, true);

//    fileTree.setWindowTitle(QObject::tr("Dir View"));
//    fileTree.show();

    return app.exec();
}
