#ifndef ICE_MINIWINDOW_H
#define ICE_MINIWINDOW_H

#include <QWidget>
#include <QAction>
#include <QActionGroup>
#include <QWidgetAction>
#include <QSlider>
#include "ice_button.h"
class IcePlayer;

/*****************************************************
**Copyright(C), 2017-2025, zl software.
**Version: 0.1
**Author: zl
**Date: 20170810
**Description: 播放器的迷你窗口 ,依赖于 ICE_Button 图形按钮 和 主界面ICEplay
**PS: 1.测试发现原作者代码中关于窗口移动的代码已经无法使用,需要使用替代的方法
** 使用模拟Window事件的方式,发现生成移动框,暂时没有解决.
** 2. 测试发现 该窗口显示之后,播放和暂停按钮同时出现,但是由于主窗口对外API没有完成,需要根据播放
** 进行调节,之后再解决.
** 3.非测试模式(没有 _ZTEST_ ),需要导入主窗口的头文件之后才能进行编译,因为调用了主窗口中的实现.
*****************************************************/
#ifdef Q_OS_WIN
#pragma comment (lib, "user32.lib")
#include <QMouseEvent>
#include <qt_windows.h>
#endif
class ICE_MiniWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ICE_MiniWindow(QWidget *parent = 0);
    ~ICE_MiniWindow();

    void ICE_Set_Parent (QWidget* parent);
    void ICE_Init_Play_Mode (int vol);

private slots:
    //这里的槽实现都是调用的主窗口中的实现,可能需要调整对应调用.
    void ice_back_to_main ();
    void ice_next_music ();
    void ice_last_music ();
    void ice_play ();
    void ice_pause ();
    void ice_setMode();
    void ice_exit ();
    void ice_lyric_action ();
    void ice_update_vol ( int );

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void contextMenuEvent (QContextMenuEvent* event);

    void ice_init_menu_actions();

signals:
    void volumeChanged (int);
private:
    ICE_Button* m_playButton;
    ICE_Button* m_pauseButton;
    ICE_Button* m_miniNextButton;

    QMenu* m_Menu;
    QActionGroup* m_modeGroup;

    QAction* m_mode0;
    QAction* m_mode1;
    QAction* m_mode2;
    QAction* m_mode3;

    QAction* m_mainForm;
    QAction* m_exit;
    QAction* m_next;
    QAction* m_last;
    QAction* m_lyric;
    QWidgetAction* m_setVolume;
    QSlider* m_volSlider;

    IcePlayer* m_parentForm;

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
};

#endif // ICE_MINIWINDOW_H
