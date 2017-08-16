#ifndef ICE_LRC_LABEL_H
#define ICE_LRC_LABEL_H
#include "icelabel.h"

class ICE_Lrc_Label : public IceLabel
{
    Q_OBJECT
public:
    explicit ICE_Lrc_Label(QWidget* parent = 0);
    ~ICE_Lrc_Label ();
    //开始歌词遮罩
    void ICE_Start_Lrc_Mask ();
    //停止歌词遮罩
    void ICE_Stop_Lrc_Mask ();
    //调整字体大小
    void ICE_Set_Size (int size);

    // QWidget interface
protected:
    //绘制窗体
    virtual void paintEvent(QPaintEvent *event) override;
    //菜单事件
    virtual void contextMenuEvent(QContextMenuEvent *event) override;
private slots:
    void ice_time_out ();
private:
    QLinearGradient linearGradient;
    QLinearGradient maskLinearGradient;
    QFont lrcFont;
    QTimer *lrcTimer;
    qreal lrcMaskWidth;
    qreal lrcMaskWidthInterval;
    QPoint offset;
};

#endif // ICE_LRC_LABEL_H
