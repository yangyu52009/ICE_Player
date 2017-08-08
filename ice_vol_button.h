#ifndef ICE_VOL_BUTTON_H
#define ICE_VOL_BUTTON_H
#include <QWidget>
#include <QSlider>
#include <QWidgetAction>
#include "ice_button.h"



/*****************************************************
**Copyright(C), 2017-2025, zl software.
**Version: 0.02
**Author: yangyu
**Date: 20170808
**Description: 定制的单击之后显示音量条的按钮
**depend: class ice_button 图形按钮
*****************************************************/
class ICE_Vol_Button : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int ICE_Volume
               READ ICE_Get_Volume
               WRITE ICE_Set_Volume
               NOTIFY ICE_Volume_changed)
public:
    ICE_Vol_Button(QWidget* parnet = 0);
    /*! 返回音量值（1-100）*/
    int ICE_Get_Volume() const;
    /*! 设置音量条是否可见*/
    void ICE_Set_Slider_Visiabel( bool );
    /*! 设置按钮图形， 普通显示；鼠标滑上的效果*/
    void ICE_Set_ButtonICON(const QIcon &noramalIcon,
                            const QIcon &focusIcon);
public slots:
    /*! 点击音量调条得音量增加一部分*/
    void ICE_increase_Volume();
    /*! 点击音量条使得音量减少一部分*/
    void ICE_Descrease_Volume();
    /*! 设置音量*/
    void ICE_Set_Volume(int volume);
    /*! 按钮的单击事件弹出菜单*/
    void ICE_Button_Clicked();
signals:
    /*! 音量改变信号*/
    void ICE_Volume_changed(int volume);
private:
    ICE_Button* m_button; //该widget唯一显示的组件 图像按钮

    QMenu* m_menu; //单击按钮显示该菜单

    QWidgetAction* m_action; //可以容纳其他widget的QAction的子类，可以作为菜单项
    QSlider* m_slider; //放在QWidgetAction中显示
};

#endif // ICE_VOL_BUTTON_H
