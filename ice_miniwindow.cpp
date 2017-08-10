#include "ice_miniwindow.h"

#include <QMenu>
#include <QPainter>
//使用这个宏,注释掉部分有对外依赖的代码,因为这个部分的依赖在测试的时候没有实现,无法测试
//#define _zTEST_

ICE_MiniWindow::ICE_MiniWindow(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowFlags (Qt::FramelessWindowHint |
                          Qt::Tool |
                          Qt::WindowStaysOnBottomHint |
                          this->windowFlags () );
    this->setStyleSheet ("QWidget { outline: no;}");
    this->setAttribute (Qt::WA_TranslucentBackground);//设置支持透明背景

    this->setWindowOpacity ( 0.9 ); //透明度

    this->setFixedSize ( 100, 100 ); //固定窗口大小
    //设置图形按钮
    this->m_playButton = new ICE_Button (this);
        m_playButton->setObjectName (QStringLiteral(" playButton "));
        m_playButton->setGeometry (QRect(29, 29, 34, 34));

    this->m_pauseButton = new ICE_Button( this );
        m_pauseButton->setObjectName (QStringLiteral( " pauseButton "));
        m_pauseButton->setGeometry (QRect(24, 29, 34, 34));

   this->m_miniNextButton = new ICE_Button( this );
        m_miniNextButton->setObjectName (QStringLiteral("nextButton"));
        m_miniNextButton->setGeometry (QRect(61, 48, 34, 34));

    QIcon icon_play;
    icon_play.addFile ( QStringLiteral(":/resource/播放按钮mini.png"));
    m_playButton->ice_set_ButtonIcon (icon_play, icon_play);
    m_playButton->setIconSize (QSize(34, 34));
    m_playButton->setFlat (true);
    m_playButton->setFocusPolicy (Qt::NoFocus); //设置没有焦点框
    m_playButton->setStyleSheet ("QPushButton {background-color: rgba(255, 255, 255, 0);"
                                 "border-style: solid;"
                                 "border-width: 0px;"
                                 "border-color: rgba(255, 255, 255, 0)}");
    QIcon icon_pause;
    icon_pause.addFile (QStringLiteral(":/resource/暂停按钮mini.png"));
    m_pauseButton->ice_set_ButtonIcon (icon_pause, icon_pause);
    m_pauseButton->setIconSize (QSize(34, 34));
    m_pauseButton->setFlat (true);
    m_playButton->setFocusPolicy (Qt::NoFocus);
    m_playButton->setStyleSheet ("QPushButton {background-color: rgba(255, 255, 255, 0);"
                                 "border-style: solid;"
                                 "border-width: 0px;"
                                 "border-color: rgba(255, 255, 255, 0)}");

    QIcon icon_next;
    icon_next.addFile (QStringLiteral(":/resource/前进按钮mini.png"));
    m_miniNextButton->ice_set_ButtonIcon (icon_next, icon_next);

    m_miniNextButton->setIconSize (QSize(9 ,15));
    m_miniNextButton->setFlat (true);
    m_miniNextButton->setFocusPolicy (Qt::NoFocus);
    m_miniNextButton->setStyleSheet ("QPushButton {background-color: rgba(255, 255, 255, 0);"
                                     "border-style: solid;"
                                     "border-width: 0px;"
                                     "border-color: rgba(255, 255, 255, 0)}");

    this->ice_init_menu_actions ();//设置菜单项

    this->connect (this->m_playButton, &ICE_Button::clicked,
                   this, &ICE_MiniWindow::ice_play);
    this->connect (this->m_pauseButton, &ICE_Button::clicked,
                   this, &ICE_MiniWindow::ice_pause);
    this->connect (this->m_miniNextButton, &ICE_Button::clicked,
                   this, &ICE_MiniWindow::ice_next_music);

}

ICE_MiniWindow::~ICE_MiniWindow()
{

}

void ICE_MiniWindow::ICE_Set_Parent(QWidget *parent)
{
#ifndef _zTEST_
       this->m_parentForm = parent;
#endif
}

void ICE_MiniWindow::ICE_Init_Play_Mode(int vol)
{
#ifndef _zTEST_
    switch (this->m_parentForm->playMode() ) {
    case 0:
        m_mode0->setChecked (true);
        break;
    case 1:
        m_mode1->setChecked (true);
        break;
    case 2:
        m_mode2->setChecked (true);
        break;
    case 3:
        m_mode3->setChecked (true);
        break;
    }
    if (this->m_parentForm->playButton->usVisible()) {
        this->m_playButton->setVisible (true);
        this->m_pauseButton->setVisible (false);
    }else {
        this->m_playButton->setVisible ( false);
        this->m_pauseButton->setVisible ( true );
    }

    this->m_volSlider->setValue (vol);
#endif
}

void ICE_MiniWindow::ice_back_to_main()
{
#ifndef _zTEST_
    this->m_parentForm->show();
#endif
}

void ICE_MiniWindow::ice_next_music()
{
#ifndef _zTEST_
    this->m_parentForm->ice_next_button_clicked();
#endif
}

void ICE_MiniWindow::ice_last_music()
{
#ifndef _zTEST_
    this->m_parentForm->ice_last_button_clicked();
#endif
}

void ICE_MiniWindow::ice_play()
{
#ifndef _zTEST_
    this->m_parentForm->ice_play_button_clicked();
#endif
    this->m_pauseButton->setVisible (true);
    this->m_playButton->setVisible (false);
}

void ICE_MiniWindow::ice_pause()
{
#ifndef _zTEST_
    this->m_parentForm->ice_pause_button_clicked();
#endif
    this->m_pauseButton->setVisible (false);
    this->m_playButton->setVisible (true);
}

void ICE_MiniWindow::ice_setMode()
{
    if(this->m_mode0->isChecked ())
    {
#ifndef _zTEST_
        this->m_parentForm->ICE_set_mode_from_mini(0);
#endif
    }
    else if (this->m_mode1->isChecked ())
    {
#ifndef _zTEST_
        this->m_parentForm->ICE_set_mode_from_mini(1);
#endif
    }else if (this->m_mode2->isChecked ())
    {
#ifndef _zTEST_
        this->m_parentForm->ICE_set_mode_from_mini(2);
#endif
    }else if (this->m_mode3->isChecked ())
    {
#ifndef _zTEST_
        this->m_parentForm->ICE_set_mode_from_mini(3);
#endif
    }
}

void ICE_MiniWindow::ice_exit()
{
#ifndef _zTEST_
    this->m_parentForm->close ();
    this->close ();
#endif
}

void ICE_MiniWindow::ice_lyric_action()
{
#ifndef _zTEST_
    this->m_parentForm->ice_lyric_button_clicked();
#endif
}

void ICE_MiniWindow::ice_update_vol(int vol)
{
#ifndef _zTEST_
    this->m_parentForm->ICE_set_vol_from_mini( vol );
#endif
}
void ICE_MiniWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter (this);
    //绘制背景
    painter.drawPixmap (0, 0, QPixmap ( ":/resource/mini.png" ));
}

void ICE_MiniWindow::contextMenuEvent(QContextMenuEvent *event)
{
    this->m_Menu->exec (QCursor::pos ());

    QWidget::contextMenuEvent (event);
}

void ICE_MiniWindow::ice_init_menu_actions()
{
    this->m_mode0 = new QAction (QString::fromLocal8Bit ("单曲循环"), this);
    this->m_mode1 = new QAction (QString::fromLocal8Bit ("列表循环"), this);
    this->m_mode2 = new QAction (QString::fromLocal8Bit ("单曲循环"), this);
    this->m_mode3 = new QAction (QString::fromLocal8Bit ("随机循环"), this);
    //设置可以选中
    m_mode0->setCheckable (true);
    m_mode1->setCheckable (true);
    m_mode2->setCheckable (true);
    m_mode3->setCheckable (true);
    //默认被选中
    m_mode0->setChecked (true);

    this->connect (this->m_mode0, &QAction::triggered,
                   this, &ICE_MiniWindow::ice_setMode);
    this->connect (this->m_mode1, &QAction::triggered,
                   this, &ICE_MiniWindow::ice_setMode);
    this->connect (this->m_mode2, &QAction::triggered,
                   this, &ICE_MiniWindow::ice_setMode);
    this->connect (this->m_mode3, &QAction::triggered,
                   this, &ICE_MiniWindow::ice_setMode);


    this->m_modeGroup = new QActionGroup (this);
        m_modeGroup->addAction (m_mode0);
        m_modeGroup->addAction (m_mode1);
        m_modeGroup->addAction (m_mode2);
        m_modeGroup->addAction (m_mode3);

    this->m_mainForm = new QAction (QString::fromLocal8Bit ("返回主界面"), this);
    this->m_exit = new QAction (QString::fromLocal8Bit ("退出"), this);
    this->m_next = new QAction (QString::fromLocal8Bit ("下一曲"), this);
    this->m_last = new QAction (QString::fromLocal8Bit ("上一曲"), this);
    this->m_lyric = new QAction (QString::fromLocal8Bit ("桌面歌词"), this);

    this->m_volSlider = new QSlider (Qt::Horizontal, this);
        m_volSlider->setRange ( 0, 100 );
        m_volSlider->setGeometry (QRect(26, 0, 75 ,25));
        this->connect (this->m_volSlider, SIGNAL(valueChanged(int)),
                       this, SIGNAL(volumeChanged(int)));
        //在原作者的源代码中没有volumeChanged这个信号，不知是怎样的编译的

        m_volSlider->setStyleSheet ("QSlider::groove:horizontal {border: 0px;height: 4px;}"
                                    "QSlider::sub-page:horizontal {background: #0096ff; }"
                                    "QSlider::add-page:horizontal {background: lightgray; }"
                                    "QSlider::handle:horizontal {background: white; width: 10px; "
                                    "border: #51b5fb 10px; border-radius: 5px; margin: -3px 0px -3px 0px;}");

        this->m_setVolume = new QWidgetAction (this);
            m_setVolume->setDefaultWidget ( this->m_volSlider );

        this->m_Menu = new QMenu (this);
            m_Menu->addAction (this->m_mainForm);
            m_Menu->addSeparator ();
            m_Menu->addAction (this->m_setVolume);
            m_Menu->addSeparator ();
            m_Menu->addAction (this->m_next);
            m_Menu->addAction (this->m_last);
            m_Menu->addSeparator ();
            m_Menu->addActions (this->m_modeGroup->actions ());
            m_Menu->addSeparator ();
            m_Menu->addAction (this->m_lyric);
            m_Menu->addSeparator ();
            m_Menu->addAction (this->m_exit);

        this->m_Menu->setStyleSheet ("QMenu { padding: 5px; background: white; border: solid 1px gray;}"
                                     "QMenu::item { padding: 0px 40px 0px 30px; height: 25px;}"
                                     "QMenu::item::selected::enabled { background: #0096ff; color: white; }"
                                     "QMenu::item::selected::!enabled { background: transparent; }"
                                     "QMenu::separator {height: 1px; background: lightgray; margin: 5px 0px 5px 0px; }");

        this->connect (this->m_exit, &QAction::triggered,
                       this, &ICE_MiniWindow::ice_exit);
        this->connect (this->m_mainForm, &QAction::triggered,
                       this, &ICE_MiniWindow::ice_back_to_main);
        this->connect (this->m_next, &QAction::triggered,
                       this, &ICE_MiniWindow::ice_next_music);
        this->connect (this->m_last, &QAction::triggered,
                       this, &ICE_MiniWindow::ice_last_music);
        this->connect (this->m_lyric, &QAction::triggered,
                       this, &ICE_MiniWindow::ice_lyric_action);

        this->connect (this->m_playButton, &ICE_Button::clicked,
                       this, &ICE_MiniWindow::ice_play);
        this->connect (this->m_pauseButton, &ICE_Button::clicked,
                       this, &ICE_MiniWindow::ice_pause);
        this->connect (this->m_volSlider, SIGNAL(valueChanged(int)),
                       this, SLOT(ice_update_vol(int)));
}


void ICE_MiniWindow::mousePressEvent(QMouseEvent *event)
{
#ifdef Q_OS_WIN
    if (ReleaseCapture ()){
        QWidget* pWindow = this->window ();
        SendMessageA ((HWND)(pWindow->winId ()),
                      WM_SYSCOMMAND,
                      SC_MOVE + HTCAPTION,
                      0);
    }
#endif
}
