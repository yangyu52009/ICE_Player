#include <QHeaderView>
#include <QMenu>
#include <QNetworkReply>

#include "iceplayer.h"
#include "nofocusdelegate.h"
IcePlayer::IcePlayer(QWidget *parent) : QWidget(parent)
{
    this->init_ui ();
    this->init_player ();
    this->init_connections ();
    this->init_window ();
    this->init_menu_acions ();
}

void IcePlayer::init_ui()
{

    /*! 初始化专辑图片标签*/
    this->m_picLabel = new QLabel ( this );
    m_picLabel->setGeometry ( QRect (40, 45, 100, 100) );
    m_picLabel->setScaledContents ( true ); //自动缩放内容
    m_picLabel->setPixmap (QPixmap (":/resource/default_album.jpg") );

    this->m_nameLabel = new IceLabel ( this );
    m_nameLabel->setGeometry ( QRect(150, 55, 550, 50) );

    this->m_musicianLabel = new QLabel ( this );
    m_musicianLabel->setGeometry ( QRect (150, 85, 220, 15) );

    this->m_albumLabel = new QLabel( this );
    m_albumLabel->setGeometry ( QRect (150, 115, 220, 15) );

    this->m_playSlider = new QSlider ( this );
    m_playSlider->setObjectName ( QStringLiteral( "playSlider" ));
    m_playSlider->setStyleSheet ("QSlider::groove:horizontal { border: 0px; height: 4px;}"
                                 "QSlider::sub-page:horizontal { background: #0096ff;}"
                                 "QSlider::add-page:horizontal { background-color: lightgray;}"
                                 "QSlider::handle:horizontal { background-color: white;"
                                 " width: 10px; border: #51b5fb 10px; border-radius: 5px;"
                                 " margin: -3px 0px -3px 0px; }");
    m_playSlider->setGeometry ( QRect (40, 150, 290, 20) );
    m_playSlider->setOrientation ( Qt::Horizontal ); //设置方向

    this->m_timeLabel = new QLabel ( this );
    m_timeLabel->setObjectName ( QStringLiteral( "timeLabel" ));
    m_timeLabel->setGeometry ( QRect ( 340, 150, 51, 16 ));

    this->playlistTabel = new QTableWidget ( this );
    playlistTabel->setObjectName ( QStringLiteral ( "playlistTable" ));
    playlistTabel->setGeometry ( QRect ( 25, 240, 350, 320 ) );
    playlistTabel->setItemDelegate (new NoFocusDelegate());

    this->m_addButton = new ICE_Button ( this );
    m_addButton->setObjectName (QStringLiteral ( "addButton" ) );
    m_addButton->setGeometry ( QRect (40, 190, 31, 31 ) );
    this->m_modeButton = new ICE_Button ( this );
    m_modeButton->setObjectName ( QStringLiter("modeButton") );
    m_modeButton->setGeometry ( QRect( 290, 190, 31 ,31) );
    this->m_lastButton = new ICE_Button ( this );
    m_lastButton->setObjectName ( QStringLiteral ("lastButton") );
    m_lastButton->setGeometry ( QRect(120, 185, 41, 41) );
    this->m_nextButton = new ICE_Button ( this );
    m_nextButton->setObjectName ( QStringLiteral( "nextButton" ) );
    m_nextButton->setGeometry ( QRect (240, 185, 41, 41));
    this->m_lyrButton = new ICE_Button ( this );
    m_lyrButton->setObjectName ( QStringLiteral("lyricButton") );
    m_lyrButton->setGeometry ( QRext (80, 190, 31, 31) );
    this->m_playButton = new ICE_Button ( this );
    m_playButton->setObjectName ( QStringLiteral ("playButton") );
    m_playButton->setGeometry ( QRect (170, 175, 61, 61) );
    this->m_pauseButton = new ICE_Button ( this );
    m_pauseButton->setObjectName ( QStringLiteral ("pasueButton") );
    m_pauseButton->setGeometry ( QRect (170, 175, 61, 61));
    m_pauseButton->setVisible ( false ); //这是按钮和上面的按钮在同一位置，所以默认情况下就是隐藏的状态

    /*! 音量控制按钮*/
    this->m_volButton = new ICE_Vol_Button ( this );
    m_volButton->setObjectName ( QStringLiteral ("volButton") );
    m_volButton->setGeometry ( QRect (333, 193, 31, 31) );
    m_volButton->ICE_Set_Volume ( 100 ); //设置默认值
    /*! mini窗口按钮*/
    this->m_miniForm = new ICE_Button ( this );
    m_miniForm->setObjectName ( QStringLiteral ( "mminButton"));
    m_miniForm->setGeometry ( QRect (307, 3, 29, 31) );
    this->m_minButton = new ICE_Button ( this );
    m_minButton->setObjectName ( QStringLiteral ("minButton"));
    m_minButton->setGeometry ( QRect (337, 3, 29, 31) );
    this->m_exitButton = new ICE_Button ( this );
    m_exitButton->setObjectName ( QStringLiteral ( "exitButton" ));
    m_exitButton->setGeometry ( QRect (364, 3, 29, 31) );
    this->m_logoButton = new ICE_Button ( this );
    m_logoButton->setObjectName ( QStringLiteral ( "logoButton" ));
    m_logoButton->setGeometry ( QRect (8, 3, 120, 48) );

    this->m_logoButton->raise ();
    this->m_picLabel->raise ();
    this->m_playSlider->raise ();
    this->m_timeLabel->raise ();
    this->playlistTabel->raise ();
    this->m_addButton->raise ();
    this->m_modeButton->raise ();
    this->m_exitButton->raise ();
    this->m_nextButton->raise ();
    this->m_lyrButton->raise ();
    this->m_playButton->raise ();
    this->m_volButton->raise ();
    this->m_mminButton->raise ();
    this->m_minButton->raise ();
    this->m_exitButton->raise ();

    this->m_timeLabel->setText ( QString ("00:00"));
    this->m_nameLabel->setText ( QString ("Name ") );
    this->m_musicianLabel->setText ( QString ("Musician") );
    this->m_albumLabel->setText ( QString ( "Album") );

    /*! 设置图标*/

    const QString str = QString( "QPushButton {background-color: rgba(255, 255, 255, 0)"
                                 "border-style: solid; border-width: 0px; border-color: rgba (255, 255, 255, 0)}"  );
    QIcon icon_play, icon_play_focus;
    icon_play.addFile (QStringLiteral (":/resource/播放按钮-主界面.png") );
    icon_play_focus.addFile ( QStringLiteral (":/resource/播放按钮-主界面2.png"));
    this->m_playButton->ice_set_ButtonIcon (icon_play, icon_play_focus);
    m_playButton->setIconSize ( QSize (60, 60));
    m_playButton->setFlat ( true );
    m_playButton->setFocusPolicy ( Qt::NoFocus );
    m_playButton->setStyleSheet ( str );
    QIcon icon_pause, icon_pause_focus;
    icon_pause.addFile ( QStringLiteral (":/resource/暂停按钮-主界面.png") );
    icon_pause_focus.addFile ( QStringLiteral (":/resource/暂停按钮-主界面2.png") );
    this->m_pauseButton->ice_set_ButtonIcon ( icon_pause, icon_pause_focus);
    m_pauseButton->setIconSize ( QSize (60, 60) );
    m_pauseButton->setFlat (true);
    m_pauseButton->setFocusPolicy ( Qt::NoFocus );
    m_pauseButton->setStyleSheet ( str );
    QIcon icon_lyric, icon_lyric_focus;
    icon_lyric.addFile ( QStringLiteral (":/resource/歌词按钮.png") );
    icon_lyric_focus.addFile ( QStringLiteral (":/resource/歌词按钮2.png"));
    this->m_lyrButton->ice_set_ButtonIcon (icon_lyric, icon_lyric_focus);
    m_lyrButton->setIconSize ( QSize (25, 25) );
    m_lyrButton->setFlat ( true );
    m_lyrButton->setFocusPolicy ( Qt::NoFocus );
    m_lyrButton->setStyleSheet ( str );
    QIcon icon_exit, icon_exit_focus;
    icon_exit.addFile ( QStringLiteral (":/resource/关闭按钮.png") );
    icon_exit_focus.addFile ( QStringLiteral (":/resource/关闭按钮2.png") );
    this->m_exitButton->ice_set_ButtonIcon ( icon_exit, icon_exit_focus );
    m_exitButton->setIconSize ( QSize (20, 20));
    m_exitButton->setFocusPolicy ( Qt::NoFocus );
    m_exitButton->setFlat ( true );
    m_exitButton->setStyleSheet ( str );
    QIcon icon_min, icon_min_focus;
    icon_min.addFile ( QStringLiteral (":/resource/迷你模式按钮.png") );
    icon_min_focus.addFile ( QStringLiteral (":/resource/迷你模式按钮2.png") );
    this->m_minButton->ice_set_ButtonIcon ( icon_min, icon_min_focus);
    m_minButton->setIconSize ( QSize (20, 20) );
    m_minButton->setFlat ( true );
    m_minButton->setFocusPolicy ( Qt::NoFocus );
    m_minButton->setStyleSheet ( str );
    QIcon icon_mmin, icon_mmin_focus;
    icon_mmin.addFile ( QStringLiteral (":/resource/缩小按钮.png"));
    icon_mmin_focus.addFile ( QStringLiteral (":/resource/缩小按钮2.png") );
    this->m_mminButton->ice_set_ButtonIcon ( icon_mmin, icon_mmin_focus );
    m_mminButton->setIconSize ( QSize (20, 20) );
    m_mminButton->setFlat ( true );
    m_mminButton->setFocusPolicy ( Qt::NoFocus );
    m_mminButton->setStyleSheet ( str );
    QIcon icon_logo, icon_logo_focus;
    icon_logo.addFile ( QStringLiteral (":/resource/左上角logo按钮.png") );
    icon_logo_focus.addFile ( QStringLiteral (":/resource/左上角logo按钮2.png"));
    m_logoButton->ice_set_ButtonIcon (icon_logo, icon_logo_focus);
    m_logoButton->setIconSize ( QSize (120, 48) );
    m_logoButton->setFlat ( true );
    m_logoButton->setFocusPolicy ( Qt::NoFocus );
    m_logoButton->setStyleSheet ( str );
    QIcon icon_next, icon_next_focus;
    icon_next.addFile (QStringLiteral (":/resource/下一曲.png"));
    icon_next_focus.addFile ( QStringLiteral (":/resource/下一曲2.png") );
    this->m_nextButton->ice_set_ButtonIcon (icon_next, icon_next_focus);
    m_nextButton->setIconSize (QSize ( 40, 40));
    m_nextButton->setFlat ( true );
    m_nextButton->setFocusPolicy ( Qt::NoFocus );
    m_nextButton->setStyleSheet ( str );
    QIcon icon_last, icon_last_focus;
    icon_last.addFile ( QStringLiteral(":/resource/上一曲.png") );
    icon_last_focus.addFile ( QStringLiteral (":/resource/上一曲2.png") );
    m_lastButton->ice_set_ButtonIcon (icon_last, icon_last_focus);
    m_lastButton->setFlat ( true );
    m_lastButton->setIconSize (QSize (40, 40));
    m_lastButton->setFocusPolicy ( Qt::NoFocus );
    m_lastButton->setStyleSheet ( str );
    QIcon icon_mode, icon_mode_focus;
    icon_mode.addFile ( QStringLiteral (":/resource/播放模式.png"));
    icon_mode_focus.addFile ( QStringLiteral (":/resource/播放模式2.png") );
    this->m_modeButton->ice_set_ButtonIcon ( icon_mode, icon_mode_focus );
    m_modeButton->setFlat ( true );
    m_modeButton->setIconSize ( QSize (25, 25) );
    m_modeButton->setFocusPolicy ( Qt::NoFocus );
    m_modeButton->setStyleSheet ( str );
    QIcon icon_add, icon_add_focus;
    icon_add.addFile ( QStringLiteral (":/resource/添加歌曲.png") );
    icon_add_focus.addFile ( QStringLiteral ( ":/resource/添加歌曲2.png" ));
    this->m_addButton->ice_set_ButtonIcon ( icon_add, icon_add_focus);
    m_addButton->setFlat ( true );
    m_addButton->setIconSize ( QSize (25, 25) );
    m_addButton->setFocusPolicy ( Qt::NoFocus );
    m_addButton->setStyleSheet ( str );

    /*! 去除标题栏*/
    this->setWindowFlags (Qt::FramelessWindowHint | this->windowFlags () );
    /*! 半透明*/
    this->setWindowOpacity ( 0.9 );
    /*! 设置窗口的固定大小*/
    this->setFixedSize ( 400, 600 );

    /*! 设置音乐信息字体颜色*/
    //颜色
    QColor fontcolor (1, 149, 255 );

    QPalette fontPalette = this->m_nameLabel->palette ();
    fontPalette.setColor (QPalette::WindowText, fontcolor);
    this->m_nameLabel->setPalette (fontPalette);


    fontPalette = this->m_musicianLabel->palette ();
    fontPalette.setColor (QPalette::WindowText, fontcolor);
    this->m_musicianLabel->setPalette (fontPalette);

    fontPalette = this->m_albumLabel->palette ();
    fontPalette.setColor (QPalette::WindowText, fontcolor);
    this->m_albumLabel->setPalette (fontPalette);

    QColor timeColor (106, 182, 240);
    QPalette timePalette = this->m_timeLabel;
    timePalette.setColor (QPalette::WindowText, timeColor);
    this->m_timeLabel->setPalette (timePalette);
    //字体
    this->m_nameLabel->setFont (QFont (QString::fromLocal8Bit ("微软雅黑"), 12));
    QFont othersfont (QString::fromLocal8Bit ("微软雅黑"), 9);
    this->m_musicianLabel->setFont (othersfont);
    this->m_albumLabel->setFont (othersfont);
    this->m_timeLabel->setFont (othersfont);

    this->m_volSlider = new QSlider (this->m_volButton);
    m_volSlider->setObjectName ( QStringLiteral ("volSlider"));
    m_volSlider->setStyleSheet ( "QSlider::groove:horizontal{border:0px;height:4px;}"
                                 "QSlider::sub-page:horizontal{background: '#0096ff'}"
                                 "QSlider::add-page:horizontal{background:lightgray}"
                                 "QSlider::handle:horizontal{background:white;"
                                 "width:10px; border: #51b5fb 10px;"
                                 "border-radius:5px;margin: -3px 0xp -3px 0px;}");
    m_volSlider->setGeometry ( QRect(40, 150, 290,20));
    m_volSlider->setOrientation ( Qt::Horizontal );

    if(this->playlistTabel->columnCount () < 1)
        playlistTabel->setColumnCount (2); //设置为2 列

    QTableWidgetItem * _qtablewidgetitem = QTableWidgetItem();
    playlistTabel->setHorizontalHeaderItem (0, _qtablewidgetitem);

    //设置列宽
    playlistTabel->setColumnWidth (0, 300);
    playlistTabel->setColumnWidth (1, 45);
    //禁止编辑单元格的内容
    playlistTabel->setEditTriggers ( QAbstractItemView::NoEditTriggers );
    //选中一行
    playlistTabel->setSelectionBehavior (QAbstractItemView::SelectRows);
    //去掉水平滚动条
    playlistTabel->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    //去掉垂直表头
    playlistTabel->verticalHeader ()->setFixedWidth ( 0 );
    //去掉水平表头
    playlistTabel->horizontalHeader ()->setFixedHeight ( 0 );
    //设置为无边框
    playlistTabel->setFrameShape ( QFrame::NoFrame );
    //设置不显示格子线
    playlistTabel->setShowGrid (  false );
    //设置右键菜单
    playlistTabel->setContextMenuPolicy ( Qt::CustomContextMenu );
    //设置背景颜色
    QPalette pal = playlistTabel->palette ();
    pal.setBrush (QPalette::Base, QBrush (QColor ( 255, 255, 255)));
    playlistTabel->setPalette (pal);
    //设置竖直滚动条样式
    playlistTabel->setStyleSheet ( "QScrollBar { background: transparent; width: 10px;}"
                                   "QScrollBar::handle { background: lightgray;"
                                   " border: 2px solid transparent; border-radius: 5px;}"
                                   "QScrollBar::handle:hover { background: gray;}"
                                   "QScrollBar::sub-line { background: transparent;}"
                                   "QScrollBar::add-line { background: transparent;}" );
    //使得拖动操作生效
    playlistTabel->setAcceptDrops ( true );
    this->setAcceptDrops ( true );

}

void IcePlayer::init_player()
{
    this->m_mediaPlayer = new QMediaPlayer ( this );
    this->m_mediaPlayerList = new QMediaPlaylist ( this );
    m_mediaPlayer->setPlaylist ( m_mediaPlayerList );
    this->m_playMode = IcePlayer::SINGAL;

    this->m_preIndex = -1;
    this->m_currentIndex = 0;
}

void IcePlayer::init_connections()
{
    //mediaplayer
    connect ( this->m_mediaPlayer, &QMediaPlayer::positionChanged,
              this, &IcePlayer::ice_update_position);
    connect ( this->m_mediaPlayer, &QMediaPlayer::durationChanged,
              this, &IcePlayer::ice_update_duration);
    connect ( this->m_mediaPlayer, &QMediaPlayer::stateChanged,
              this, &IcePlayer::ice_update_state);
    connect ( this->m_mediaPlayer, &QMediaPlayer::metaDataChanged ,
              this, &IcePlayer::ice_update_mete_data);
    //playslider
    connect ( this->m_playSlider, &QSlider::sliderMoved,
              this, &IcePlayer::ice_set_play_position);
    connect ( this->m_playSlider, &QSlider::sliderReleased,
              this, &IcePlayer::ice_set_postion);
    //volButton
    connect ( this->m_volButton, &ICE_Vol_Button::ICE_Volume_changed,
              this->m_mediaPlayer, &QMediaPlayer::setVolume);
    //playlistTable
    connect ( this->playlistTabel, &QTableWidget::cellDoubleClicked,
              this, &IcePlayer::ice_playlisttable_cell_double_clicked);
    connect ( this->playlistTabel, &QTableWidget::customContextMenuRequested,
              this, &IcePlayer::ice_playlisttable_menu_requested);
    //addButton
    connect ( this->m_addButton, &ICE_Button::clicked,
              this, &IcePlayer::ice_open_music);
    //exitButton
    connect ( this->m_exitButton, &ICE_Button::clicked,
              this, &IcePlayer::close);
    //playButton
    connect ( this->m_playButton, &ICE_Button::clicked,
              this, &IcePlayer::ice_play_button_clicked);
    //lryicButton
    connect ( this->m_lyrButton, &ICE_Button::clicked,
              this, &IcePlayer::ice_lyric_button_clicked);
    //logoButton
    connect ( this->m_logoButton, &ICE_Button::clicked,
              this, &IcePlayer::ice_log_button_clicked);
    //modeButton
    connect ( this->m_modeButton, &ICE_Button::clicked,
              this, &IcePlayer::ice_mode_button_clicked);
    //nextButton
    connect ( this->m_nextButton, &ICE_Button::clicked,
              this, &IcePlayer::ice_next_button_clicked);
    //lastButton
    connect ( this->m_lastButton, &ICE_Button::clicked,
              this, &IcePlayer::ice_last_button_clicked);
    //pauseButton
    connect ( this->m_pauseButton, &ICE_Button::clicked,
              this, &IcePlayer::ice_pasue_button_clicked);
    //minButton
    connect ( this->m_minButton, &ICE_Button::clicked,
              this, &IcePlayer::ice_min_button_clicked);
    //mminButton
    connect ( this->m_mminButton, &ICE_Button::clicked,
              this, &IcePlayer::showMinimized);
}

void IcePlayer::init_window()
{
    //        aboutForm = new ICE_About_Form(this);
    this->iceLrc = new ICE_Lrc ( this );

    this->m_miniForm = new ICE_MiniWindow ( this );
    m_miniForm->ICE_Set_Parent ( this );
    m_miniForm->hide ();
}

void IcePlayer::init_menu_acions()
{
    this->m_modeSingal = new QAction (QString::fromLocal8Bit ( "单曲播放 "), this);
    this->m_modeListCircle = new QAction (QString::fromLocal8Bit ( "列表循环" ), this);
    this->m_modeSingalCircle = new QAction (QString::fromLocal8Bit ( "单曲循环" ), this);
    this->m_modeRandom = new QAction ( QString::fromLocal8Bit ("随机播放"), this);

    this->connect ( this->m_modeSingal, &QAction::triggered,
                   this, &IcePlayer::ice_set_play_mode);
    this->connect ( this->m_modeListCircle, &QAction::triggered,
                    this, &IcePlayer::ice_set_play_mode);
    this->connect ( this->m_modeSingalCircle, &QAction::triggered,
                    this, &IcePlayer::ice_set_play_mode);
    this->connect ( this->m_modeRandom, &QAction::triggered,
                    this, &IcePlayer::ice_set_play_mode);

    this->modeActionGroup = new QActionGroup ( this );
        modeActionGroup->addAction (m_modeSingal);
        modeActionGroup->addAction (m_modeListCircle);
        modeActionGroup->addAction (m_modeSingalCircle);
        modeActionGroup->addAction (m_modeRandom);

    m_modeSingal->setCheckable ( true );
    m_modeSingalCircle->setCheckable ( true );
    m_modeListCircle->setCheckable ( true );
    m_modeRandom->setCheckable ( true );
    m_modeRandom->setChecked ( true );

    const QString str = QString(
        "QMenu {padding: 5px; background: white; border: 1px solid gray}"
        "QMenu::item {padding: 0px 40px 0px 30px; height: 25px;}"
        "QMenu::item:selected:enabled {background: '#0096ff';color: white;}"
        "QMenu::item:selected:!enabled {background: transparent;}"
        "QMenu::separator {height: 1px; background: lightgray; margin: 5px 0px 5px 0px;}");

    this->m_playModeMenu = new QMenu ( this->m_modeButton );
        m_playModeMenu->setStyleSheet ( str );

        m_playModeMenu->addActions ( modeActionGroup->actions ());

  //------------------------------------------------------------//
    this->m_contextMenuLess = new QMenu (this->playlistTabel);
    this->m_contextMenuMore = new QMenu (this->playlistTabel);

    this->m_addMusic = new QAction ( QString::fromLocal8Bit ("添加歌曲"), this);
    this->m_addfileDiv = new QAction ( QString::fromLocal8Bit ("添加目录"), this);
    this->m_removeCurr = new QAction ( QString::fromLocal8Bit ("移除本曲"), this);
    this->m_removeAll = new QAction ( QString::fromLocal8Bit ("移除所有"), this);

    connect ( this->m_addMusic, &QAction::triggered,
              this, &IcePlayer::ice_open_music);
    connect ( this->m_addfileDiv, &QAction::triggered,
              this, &IcePlayer::ice_open_dir);
    connect ( this->m_removeCurr, &QAction::triggered,
              this, &IcePlayer::ice_remove_current_music);
    connect ( this->m_removeAll, &QAction::triggered,
              this, &IcePlayer::ice_clear_list);

    this->m_contextMenuLess->addAction (m_addMusic);
        m_contextMenuLess->addAction (m_addfileDiv);
        m_contextMenuLess->addSeparator ();
        m_contextMenuLess->addAction (m_removeAll);

    this->m_contextMenuMore->addAction (m_addMusic);
        m_contextMenuMore->addAction (m_addfileDiv);
        m_contextMenuMore->addSeparator ();
        m_contextMenuMore->addAction (m_removeCurr);
        m_contextMenuMore->addAction (m_removeAll);

    m_contextMenuLess->setStyleSheet ( str );
    m_contextMenuMore->setStyleSheet ( str );

}

void IcePlayer::init_network()
{
    this->networker = NetWorker::instance (); //得到该类的唯一的实例对象
    this->receiveState = RECEIVE_INFO;

    connect (this->networker, &NetWorker::finished,
             [=] (QNetworkReply* reply)
         {
        switch (receiveState) {
        case RECEIVE_INFO:

            break;
        case RECEIVE_LINK:
            break;
        case RECEIVE_LRC:
            break;
        case RECEIVE_PIC:
            break;
        default:
            break;
        }
        reply->abort ();
    }});

}

