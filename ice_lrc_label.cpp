#include "ice_lrc_label.h"

#include <QMenu>
#include <QPainter>

ICE_Lrc_Label::ICE_Lrc_Label(QWidget *parent)
{
    this->setText (QString::fromLocal8Bit ("ICEPlayer"));
    this->linearGradient.setStart ( 0, 10);
        linearGradient.setFinalStop ( 0, 40);
        linearGradient.setColorAt (0 ,QColor (1, 150, 255));
    lrcFont.setFamily ( QString::fromLocal8Bit ("微软雅黑"));
    lrcFont.setPointSize ( 25 );
}

ICE_Lrc_Label::~ICE_Lrc_Label()
{

}

void ICE_Lrc_Label::ICE_Start_Lrc_Mask()
{

}

void ICE_Lrc_Label::ICE_Stop_Lrc_Mask()
{
    this->update ();
}

void ICE_Lrc_Label::ICE_Set_Size(int size)
{
    this->lrcFont.setPointSize ( size );
}

void ICE_Lrc_Label::paintEvent(QPaintEvent *event)
{
    QPainter painter ( this );
    painter.setFont ( lrcFont );
    if (this->text ().size () > 2) {
        this->setText ("Music...");
    }
    QString tmp = this->text ();
    //tmp.toUtf8 ();
    //绘制底层文字 作为 阴影
    painter.setPen ( QColor ( 90, 105, 115, 200));
    painter.drawText ( 1, 1, 800, 60, Qt::AlignCenter, tmp);
    //绘制表面的文字
    painter.setPen (QPen (this->linearGradient, 0));
    painter.drawText ( 0, 0, 800, 60, Qt::AlignCenter, tmp);

}

void ICE_Lrc_Label::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu;
    menu.addAction (QString::fromLocal8Bit ( "隐藏"), this->parent (), SLOT(hide()));
    menu.exec (QCursor::pos ());
}

void ICE_Lrc_Label::ice_time_out()
{
    this->update ();
}
