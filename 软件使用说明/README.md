
## 使用说明：

本项目旨在实现一个通用的图像查看器，可以通过配置，自定义地接入不同的软件。使用开源协议：MIT

<img src="https://github.com/BensonLaur/image-storage/raw/master/BesImage%20project/3.png" width="60%" height="60%">

使用步骤：

1、下载软件：版本 [V1.0.0.0](https://github.com/BensonLaur/BesImage/releases/download/v1.0/besimage.zip)

2、根据用途更改配置文件即可，配置文件位置为 settings\app.config

## 配置文件说明

文件结构：


    <?xml version="1.0" encoding="UTF-8" standalone="yes"?>
    <appConfig>
        <user>
            <functionMode>0</functionMode>
            <appTitle></appTitle>
            <iconPath></iconPath>
            <backgroundImagePath></backgroundImagePath>
            <initPath></initPath>
            <onlyShowOneImage>0</onlyShowOneImage>
            <closeDirTreeOnOpen>0</closeDirTreeOnOpen>
        </user>
        <default>
            <defaultBackgroundPath>resource/default/1.jpg</defaultBackgroundPath>
            <besimageBlackIcon>resource/default/besimage-black.ico</besimageBlackIcon>
            <besimageWhiteIcon>resource/default/besimage-white.ico</besimageWhiteIcon>
            <isWindowHeaderColorBlack>1</isWindowHeaderColorBlack>
        </default>
    </appConfig>

节点说明：

1、节点 *appConfig*
 
    <appConfig> 

子节点:
  
    <user>              用户自定义外部参数，决定软件展示的功能 以及 界面的展示元素
    <default>           程序默认参数定义，程序优先载入<default>参数，然后再应用 <user> 中被程序判定为有效的参数
 
2、节点 *user*

    <user> 

子节点：

    <functionMode>        0 表示全功能模式 1表示自定义功能模式；全功能模式下，其他 user 下的子节点的定义将全被忽略
    <appTitle>            软件显示的标题
    <iconPath>            Icon 图标路径，只支持绝对路径
    <backgroundImagePath> 背景图片路径，只支持绝对路径
    <initPath>            浏览目录的初始路径，为空表示浏览整个硬盘文件系统；支持文件夹 和 单个图片文件路
    <onlyShowOneImage>    是否启用只显示单个图片模式：0 表示不启用， 1表示启用；但图片模式 需要配合 initPath 使用，传入单个图片文件路径
    <closeDirTreeOnOpen>  是否在启动软件时，收起左边的目录树：0 表示不启用，1表示启用

2、节点 *default*

    <default> 

子节点：

    //以下节点路径建议使用相对路径（相对路径置相对运行目录路径，不以"盘符:" 和"/"、"\" 开头的路径）
    
    <defaultBackgroundPath>       程序默认的背景图片，支持绝对路径和相对路径
    <besimageBlackIcon>           程序黑色风格图标路径，支持绝对路径和相对路径
    <besimageWhiteIcon>           程序白色风格图标路径，支持绝对路径和相对路径
    <isWindowHeaderColorBlack>    窗口标题是否使用黑色风格，1 为是， 0 为否

