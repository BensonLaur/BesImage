#ifndef APPCONFIG_H
#define APPCONFIG_H

#include "global.h"
#include <QDebug>
#include <QObject>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

enum  FunctionMode              //软件功能模式
{
    FUNCTION_FULL = 0,          //全功能模式
    FUNCTION_CUSTOM             //自定义功能模式
};

class AppConfigParameter        //应用配置参数
{
public:
        ////////////////////////////////////////////////
        ///  外部参数自定义
        ///
        FunctionMode                functionMode;           //软件功能模式
        QString                     appTitle;               //软件标题
        QString                     iconPath;               //图标路径
        QString                     backgroundImagePath;    //背景图片路径
        QString                     initPath;               //启用软件时读取的路径（目录路径或文件路径）
        bool                        onlyShowOneImage;       //是否只用于显示一张图片
        bool                        closeDirTreeOnOpen;     //是否在启用时默认关闭文件树


        ////////////////////////////////////////////////
        ///  内部部参数自定义
        ///

        QString                     defaultBackgroundPath;  //默认背景图片路径
        QString                     besimageBlackIcon;      //默认黑色Icon路径
        QString                     besimageWhiteIcon;      //默认白色Icon路径
        bool                        isWindowHeaderColorBlack;//窗口头部颜色（黑色或白色）

        AppConfigParameter()
        {
            functionMode = FUNCTION_FULL;
            appTitle = "BesImage";
            iconPath = "";
            backgroundImagePath = "";
            initPath = "";
            onlyShowOneImage = false;
            closeDirTreeOnOpen = false;

            defaultBackgroundPath = "resource/default/background-main-1.jpg";
            besimageBlackIcon = "resource/default/besimage-black.ico";
            besimageWhiteIcon = "resource/default/besimage-white.ico";
            isWindowHeaderColorBlack = true;
        }
};

class AppConfig: public QObject{

    Q_OBJECT

    /* 单例访问 */
public:
    static AppConfig& GetInstance();

    ~AppConfig(){}

private:
    AppConfig():m_hasLoad(false){}

public:
    //获得参数 (如果未加载自动去文件读取，已加载则使用已载入的参数。bForceLoadFromFile 强制从文件获得最新参数)
    bool GetAppParameter(AppConfigParameter& param, bool bForceLoadFromFile = false);
    bool SetAppParameter(const AppConfigParameter&  param);                             //设置参数

    bool IsValidOnlyShowOneImage();         //判断当前配置是否是有效的“只显示一张图片”
private:

    //从默认路径中加载打印参数
    bool LoadAppConfig();

    //解析config
    void parseConfig(QXmlStreamReader &reader, AppConfigParameter &param);

    //解析user
    void parseUser(QXmlStreamReader &reader, AppConfigParameter &param);

    //解析default
    void parseDefault(QXmlStreamReader &reader, AppConfigParameter &param);

    //保存参数
    bool SaveAppConfig();

    bool MakeSureConfigPathAvailable(QString &path);  //确保配置路径可用，返回配置路径


private:
    AppConfigParameter m_param;             //应用参数
    bool               m_hasLoad;           //标记是否已经加载参数
};

#endif // APPCONFIG_H
