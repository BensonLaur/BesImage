#include "widgetImageScaler.h"

WidgetImageScaler::WidgetImageScaler(QWidget *parent):
    baseWidget(parent),
    Alloffset(0,0),
    label("100%",this)
{
    ratio= 1.0;             //初始化图片缩放比例
    action = Type::None;
}

void WidgetImageScaler::SetImage(QString imagePath)
{
	SetImage(QImage(imagePath));
}

void WidgetImageScaler::SetImage(QImage image)
{
	SetImage(QPixmap::fromImage(image));
}

void WidgetImageScaler::SetImage(QPixmap pixmap)
{
    QVector<QPixmap> vecPixmap;
    vecPixmap.push_back(pixmap);
    SetImageSet(vecPixmap);    //构建一个只包含一个图片元素的集合
}

//设置显示图片集合(curIndex要显示的图片下标)
void WidgetImageScaler::SetImageSet(QVector<QString> vecPath, int curIndex)
{
    QVector<QImage> vecImage;
    for(auto path:vecPath)
        vecImage.push_back(QImage(path));

    SetImageSet(vecImage, curIndex);
}

void WidgetImageScaler::SetImageSet(QVector<QImage> vecImage, int curIndex)
{
    QVector<QPixmap> vecPixmap;
    for(auto image:vecImage)
        vecPixmap.push_back(QPixmap::fromImage(image));

    SetImageSet(vecPixmap, curIndex);
}

void WidgetImageScaler::SetImageSet(QVector<QPixmap> vecPixmap, int curIndex)
{
    m_vecPixmap = vecPixmap;

    //设置当前显示的图像下标
    if(m_vecPixmap.size() == 0)
        m_indexCurPixmap = -1;
    else
    {
        if(curIndex > m_vecPixmap.size())
            m_indexCurPixmap =  0;
        else
            m_indexCurPixmap = curIndex;
    }

    if(m_indexCurPixmap == -1)
        initImageDataWithPixmap(QPixmap::fromImage(QImage(":/image/skin/default.jpg")));  //显示默认图片
    else
        initImageDataWithPixmap(m_vecPixmap[m_indexCurPixmap]); //显示当前指定的图片
}

//显示下一张图片
bool WidgetImageScaler::ShowNextImage()
{
    if(m_indexCurPixmap < 0 || m_indexCurPixmap >= m_vecPixmap.size())
        return false;

    int nNextIndex = m_indexCurPixmap + 1;

    if(nNextIndex >= m_vecPixmap.size())
        return false;

    initImageDataWithPixmap(m_vecPixmap[nNextIndex]); //显示下一张的图片

    m_indexCurPixmap = nNextIndex;

    return true;
}

//显示上一张图片
bool WidgetImageScaler::ShowPreImage()
{
    if(m_indexCurPixmap < 0 || m_indexCurPixmap >= m_vecPixmap.size())
        return false;

    int nPreIndex = m_indexCurPixmap - 1;

    if(nPreIndex < 0 )
        return false;

    initImageDataWithPixmap(m_vecPixmap[nPreIndex]); //显示上一张的图片

    m_indexCurPixmap = nPreIndex;

    return true;
}


//显示选中的图片
bool WidgetImageScaler::ShowSelImage(int indexSel)
{
    if(indexSel < 0 || indexSel >= m_vecPixmap.size())
        return false;

    initImageDataWithPixmap(m_vecPixmap[indexSel]); //显示指定图片

    m_indexCurPixmap = indexSel;

    return true;
}

//预览当前图片
void WidgetImageScaler::printPreviewSlot(QPrinter *printerPixmap)
{
    if(m_vecPixmap.size() == 0 || m_indexCurPixmap < 0 || m_indexCurPixmap >= m_vecPixmap.size())
        return;


    //获取界面的图片
    QPixmap pixmap = m_vecPixmap[m_indexCurPixmap];

    printerPixmap->setPageSize(QPagedPaintDevice::A4);
    QPagedPaintDevice::Margins margins = QPagedPaintDevice::Margins{10,10,10,10};
    printerPixmap->setMargins(margins);
    printerPixmap->setOrientation(QPrinter::Portrait);
    printerPixmap->setOrientation(QPrinter::Landscape);
//    printerPixmap->setPageSize(QPrinter::Custom);
//    printerPixmap->setPaperSize(QSizeF(pixmap.height(),pixmap.width()),QPrinter::Point);

    QPainter painterPixmap(this);
    painterPixmap.begin(printerPixmap);
    QRect rect = painterPixmap.viewport();
    double x = 1.0 * rect.width() / pixmap.width();
    double y = 1.0 * rect.height() / pixmap.height();
    painterPixmap.scale(x, y);
    painterPixmap.drawPixmap(0, 0, pixmap);
    painterPixmap.end();
}

void WidgetImageScaler::printCurrentImage()
{
    if(m_vecPixmap.size() == 0 || m_indexCurPixmap < 0 || m_indexCurPixmap >= m_vecPixmap.size())
        return;

    QPrinter* printerPixmap= new QPrinter();
    QPixmap pixmap = m_vecPixmap[m_indexCurPixmap];


    printerPixmap->setPageSize(QPagedPaintDevice::A4);
    QPagedPaintDevice::Margins margins = QPagedPaintDevice::Margins{10,10,10,10};
    printerPixmap->setMargins(margins);
    printerPixmap->setOrientation(QPrinter::Portrait);
    printerPixmap->setOrientation(QPrinter::Landscape);

    QPrintDialog print(printerPixmap, this);
    if (print.exec())
    {
       QPainter painterPixmap;
       painterPixmap.begin(printerPixmap);
       QRect rect = painterPixmap.viewport();
       double x = 1.0 * rect.width() / pixmap.width();
       double y = 1.0 * rect.height() / pixmap.height();
       painterPixmap.scale(x, y);
       painterPixmap.drawPixmap(0, 0, pixmap);
       painterPixmap.end();
    }
}

//查询当前是否有下一张图片
bool WidgetImageScaler::HasNextImage()
{
    if(m_indexCurPixmap == -1)
        return false;

    int nNextIndex = m_indexCurPixmap + 1;

    if(nNextIndex >= m_vecPixmap.size())
        return false;

    return true;
}

//查询当前是否有上一张图片
bool WidgetImageScaler::HasPreImage()
{
    if(m_indexCurPixmap == -1)
        return false;

    int nPreIndex = m_indexCurPixmap - 1;

    if(nPreIndex < 0 )
        return false;

    return true;
}

//初始化显示图像的数据
void WidgetImageScaler::initImageDataWithPixmap(const QPixmap& pixmap)
{
    m_pixmapToshow =  m_pixmap = pixmap;

    pixW = m_pixmap.width();
    pixH = m_pixmap.height();

    ratio= 1.0;             //初始化图片缩放比例
    action = Type::None;
    Alloffset =QPoint(0,0),
    label.setText("100%");

    if(!ScaleBigImageToFit())//对大图缩放率进行调整，适应窗口大小
        update();
}

//缩放较大的图片适应窗口
bool WidgetImageScaler::ScaleBigImageToFit()
{
    QSize sizeWindow = this->size();

	if (sizeWindow == QSize(100, 30))  //特殊处理，该尺寸认为窗口还没有完成初始化
		return false;

    sizeWindow -= QSize(20, 20);
    QRect paintRect = QRect(10, 10, sizeWindow.width() , sizeWindow.height());

    double dRateWindowHW =  1.0 * paintRect.height() / paintRect.width();
    double dRatePixmap = 1.0 * pixH / pixW;

    if(dRatePixmap > dRateWindowHW)
    {
        if(pixH > paintRect.height())
        {
            //以高为基准，调整缩放率
            ratio = 1.0 * paintRect.height() / pixH;
            action=Type::Amplification;
            update();
            return true;
        }
    }
    else
    {
        if(pixW > paintRect.width())
        {
            //以宽为基准，调整缩放率
            ratio =1.0 * paintRect.width() / pixW;
            action=Type::Amplification;
            update();
            return true;
        }
    }

    return false;
}


bool WidgetImageScaler::event(QEvent * event)
{
    static bool press=false;
    static QPoint PreDot;

    if(event->type() == QEvent::MouseButtonPress )
    {
        QMouseEvent *mouse = dynamic_cast<QMouseEvent* >(event);

        //判断鼠标是否是左键按下,且鼠标位置是否在绘画区域
        if(mouse->button()==Qt::LeftButton &&Paint.contains(mouse->pos()))
        {
            press=true;
            setCursor(Qt::OpenHandCursor);//设置鼠标样式

            PreDot = mouse->pos();
        }
    }
    else if(event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *mouse = dynamic_cast<QMouseEvent* >(event);

        //判断鼠标是否是左键释放,且之前是在绘画区域
        if(mouse->button()==Qt::LeftButton && press )
        {
            setCursor(Qt::ArrowCursor);//改回鼠标样式
            press=false;
        }
    }

    if(event->type() == QEvent::MouseMove)              //移动图片
    {
       if(press)
       {
          QMouseEvent *mouse = dynamic_cast<QMouseEvent* >(event);

          offset.setX(mouse->x() - PreDot.x());
          offset.setY(mouse->y() - PreDot.y());
          PreDot = mouse->pos();
          action = Type::Move;
          this->update();
       }
     }
    else
       return QWidget::event(event);  //其他消息交给父类

    event->accept();  //处理了的部分不再传递下去
    return true;
}

//鼠标滑轮事件
void WidgetImageScaler::wheelEvent(QWheelEvent* e)
{
    if (e->delta()>0) {      //上滑,缩小

        action=Type::Shrink;
        this->update();

     } else {                    //下滑,放大
         action=Type::Amplification;
         this->update();
     }

     e->accept();
}

void WidgetImageScaler::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

	//获得当前窗口的大小
	QSize sizeWindow = this->size();
	sizeWindow -= QSize(20, 20);
	Paint = QRect(10, 10, sizeWindow.width() , sizeWindow.height());

     QPainter painter(this);
     int NowW = ratio *pixW;
     int NowH = ratio *pixH;

   if(action==Type::Amplification)           //缩小
   {
         ratio-=0.1*ratio;
       if(ratio<0.018)
         ratio = 0.01;

       /*显示比例*/
       QString str;
       str.sprintf("%.0f%%",ratio*100);
       label.setText(str) ;
   }
   else  if(action==Type::Shrink)           //放大
   {

        ratio+=0.1*ratio;
      if(ratio>4.5)
        ratio = 5.000;

       /*显示比例*/
       QString str;
       str.sprintf("%.0f%%",ratio*100);
       label.setText(str);
   }
   if(action==Type::Amplification || action==Type::Shrink)      //更新图片
   {
     NowW = ratio *pixW;
     NowH = ratio *pixH;
     m_pixmapToshow = m_pixmap;                 //重新装载,因为之前的图片已经被缩放过
     m_pixmapToshow = m_pixmapToshow.scaled(NowW, NowH,Qt::KeepAspectRatio,Qt::SmoothTransformation);
     action=Type::None;

   }

   if(action==Type::Move)                    //移动
   {
       int offsetx=Alloffset.x()+offset.x();
       Alloffset.setX(offsetx);

       int offsety=Alloffset.y()+offset.y();
       Alloffset.setY(offsety);
       action=Type::None;
   }

   if(abs(Alloffset.x())>=(Paint.width()/2 + NowW/2 -10))    //限制X偏移值
   {
       if(Alloffset.x()>0)
           Alloffset.setX(Paint.width()/2 + NowW/2 -10);
       else
        Alloffset.setX(-Paint.width()/2 + -NowW/2 +10);
   }
   if(abs(Alloffset.y())>=(Paint.height()/2 + NowH/2 -10))    //限制Y偏移值
   {
       if(Alloffset.y()>0)
           Alloffset.setY(Paint.height()/2 + NowH/2 -10);
       else
        Alloffset.setY(-Paint.height()/2 + -NowH/2 +10);

   }

   int x = Paint.width()/2 + Alloffset.x() -NowW/2;
   if(x<0)
       x=0;

   int y = Paint.height()/2 + Alloffset.y() -NowH/2;
   if(y<0)
       y=0;

   int  sx = NowW/2 - Paint.width()/2 - Alloffset.x();
   if(sx<0)
       sx=0;

   int  sy = NowH/2 - Paint.height()/2 - Alloffset.y();
   if(sy<0)
       sy=0;

   int w =(NowW - sx)>Paint.width()? Paint.width() : (NowW - sx);
   if(w>(Paint.width()-x))
       w = Paint.width()-x;

   int h =(NowH - sy)>Paint.height()? Paint.height() : (NowH - sy);
   if(h>(Paint.height()-y))
       h = Paint.height()-y;

     painter.drawRect(Paint.x()-1,Paint.y()-1,Paint.width()+1,Paint.height()+1); //画框
     painter.drawTiledPixmap(x+Paint.x(),y+Paint.y(),w,h,m_pixmapToshow,sx,sy);             //绘画图形


	 //void QPainter::drawTiledPixmap(int x, int y, int w int h const QPixmap & pixmap, int sx = 0, int sy = 0);
	 ////平铺显示pixmap
	 ////x y w h :表示绘画区域
	 ////sx  sy  :表示Qpixmap绘画起始位置
}


void WidgetImageScaler::resizeEvent(QResizeEvent *event)
{
    ScaleBigImageToFit();
    baseWidget::resizeEvent(event);
}
