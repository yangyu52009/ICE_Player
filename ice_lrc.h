#ifndef ICE_LRC_H
#define ICE_LRC_H

#include <QWidget>
#include "ice_lrc_label.h"
class ICE_Lrc : public QWidget
{
    Q_OBJECT
public:
    explicit ICE_Lrc(QWidget *parent = 0);
    ~ICE_Lrc ();

    //开始歌词遮罩
    void ICE_Start_Lrc_Mask (qint64 intervaltime);
    //停止歌词遮罩
    void ICE_Stop_Lrc_Mask ();
    QString text () const ;
    void setText (QString& t);

private:
    ICE_Lrc_Label* lrcLabel;

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif // ICE_LRC_H
