#include "topSearchTipsWidget.h"
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QEventLoop>
#include<QLineEdit>
#include<QDebug>
topSearchTipsWidget::topSearchTipsWidget(QWidget*p)
    :QListWidget(p)
{

    setMouseTracking(true);
    setStyleSheet("QListWidget{background:white;border:1px solid rgb(214,214,214);}"
                  "QListWidget::item{color:rgb(102,102,102);height:30;}");
    setFrameShadow(QFrame::Plain);//设置平的样式
    setFrameShape(QFrame::NoFrame);//设置无边样式
    setFocusPolicy(Qt::NoFocus);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平scrollbar禁用
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//垂直scrollbar禁用
    setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    setSelectionMode ( QAbstractItemView::NoSelection);//单选
    prerow=-1;
}

void topSearchTipsWidget::mouseMoveEvent(QMouseEvent*e)
{
    QListWidget::mouseMoveEvent(e);
     QListWidgetItem *listitem=this->itemAt(this->mapFromGlobal(QCursor::pos()));
        if(listitem==Q_NULLPTR)
        {
            for(int row=0;row<this->count();row++)
            {
                this->item(row)->setBackgroundColor(Qt::transparent);
            }
        }
        else
        {
            QListWidgetItem *plistitem=this->item(prerow);
            if(plistitem!=Q_NULLPTR)
            {
                plistitem->setBackgroundColor(Qt::transparent);
            }
            listitem->setBackgroundColor(QColor(244,244,244));
            prerow=this->row(listitem);
        }

}

void topSearchTipsWidget::leaveEvent(QEvent *e)
{
    QListWidget::leaveEvent(e);

    QListWidgetItem *plistitem=this->item(prerow);
    if(plistitem!=Q_NULLPTR)
    {
        plistitem->setBackgroundColor(Qt::transparent);
        plistitem->setTextColor(QColor(102,102,102));
    }
}
void topSearchTipsWidget::focusInEvent(QFocusEvent *e)
{
   QListWidget::focusInEvent(e);
}

