
## 项目简介：

本项目旨在实现一个通用的图像查看器，可以通过配置，自定义地接入不同的软件。使用开源协议：MIT

当前最新截图：

<img src="https://github.com/BensonLaur/image-storage/raw/master/BesImage%20project/current.png" width="60%" height="60%">


<img src="https://github.com/BensonLaur/image-storage/raw/master/BesImage%20project/current2.png" width="60%" height="60%">


## 背景

BesImage, 图像查看器，旨在实现图像预览和打印功能。市面上已经有软件实现了预览和打印的功能了，但是如果要将该功能作为一个模块加入不同的软件中，在通用性上，就显得比较不足了——比如想要自定义皮肤，自定义软件语言，自定义功能项等。

## 功能

1、	可以预览查看单个文件夹下的所有图片

2、	可以查看单个图片文件

3、	以提供配置文件的方式，尽可能通用地接入不同的软件

配置项包括：

	1)	全功能模式 和 自定义功能模式
	2)	软件标题
	3)	软件图标路径
	4)	软件整体背景图片路径
	6)	是否只用于显示1张图片（自定义模式）
	7)	启用时是否默认文件目录树（自定义模式）
	8)	是否显示显示打印功能（自定义模式）
	9)	语言（初步 中、英）
	
## 开发环境

Qt 5.7.1 32-bit ( + MSVC 2015 编译器 | MingGW)

