#ifndef ICEPLAYER_H
#define ICEPLAYER_H

#include <QMediaPlayer>
#include <QWidget>
#include <QMap>
#include <QSlider>
#include <QTableWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMenu>
#include <QActionGroup>

#include "ice_button.h"
#include "icelabel.h"
#include "ice_vol_button.h"
#include "networker.h"
#include "ice_miniwindow.h"
#include "ice_lrc.h"
//枚举播放模式
enum ICE_Play_Mode
{
    SINGAL = 0, //单曲，只放一次
    LISTCIRCLE, //列表循环
    SINGALCIRCLE, //单曲循环
    RANDOM    //随机
};
enum
{
    RECEIVE_INFO = 0, //网络音乐信息
    RECEIVE_LINK, //
    RECEIVE_PIC, //专辑图片
    RECEIVE_LRC //歌词
};


class IcePlayer : public QWidget
{
    Q_OBJECT
    /*! 设置mini窗口为主窗口类的友元类，
     * 从而使其可以直接的访问IcePlayer类的私有部分
    */
    friend class ICE_MiniWindow;

public:
    explicit IcePlayer(QWidget *parent = 0);
    ~IcePlayer(const QString& filepath);
signals:

public slots:
    /*! 从mini窗口放主窗口*/
    void ICE_goback_to_main();
    /*! 接受mini窗口传来的参数设置播放模式*/
    void ICE_set_mode_from_mini(int mode);
    /*! 接受mini窗口传来的参数设置音量*/
    void ICE_set_vol_from_mini(int vol);
private slots:
    /*! 打开目录*/
    void ice_open_dir();
    /*! 添加mp3格式的文件*/
    void ice_open_music();
    /*! 删除指定行的音乐*/
    void ice_remove_current_music();
    /*! 清空播放列表*/
    void ice_clear_list();
    /*! 打开右键菜单*/
    void ice_playlisttable_menu_requested(const QPoint& pos);
    /*! 双击播放音乐*/
    void ice_playlisttable_cell_double_clicked(int row, int);
    /*! 更新音乐信息*/
    void ice_update_mete_data();
    /*! 更新进度条位置*/
    void ice_update_duration(qint64 duration);
    /*! 更新播放状态*/
    void ice_update_state(QMediaPlayer::State state);
    /*! 设置播放进度*/
    void ice_set_postion();
    /*! 更新歌词时间显示*/
    void ice_update_position(qint64 position);

    //设置各按钮的单击事件，激活各按钮
    void ice_play_button_clicked();
    void ice_lyric_button_clicked();
    void ice_log_button_clicked();
    void ice_mode_button_clicked();
    void ice_pasue_button_clicked();
    void ice_min_button_clicked();
    void ice_next_button_clicked();
    void ice_last_button_clicked();

    /*! 设置播放模式*/
    void ice_set_play_mode();
    /*! 解析LRC歌词*/
    void ice_reslove_lrc(const QString& source_file_name);
    /*! 程序打开时读取播放列表文件*/
    void ice_reed_list();
    /*! 程序关闭时*/
    void ice_close();
    /*! 保存播放列表*/
    void ice_write_list();
    /*! 设置当前的播放位置*/
    void ice_set_play_position(int pos);
    /*! 获取播放位置*/
    int ice_get_play_position();
private:
    void init_ui(); //初始化UI组件，并进行基本的设置
    void init_player(); //初始化播放器及其相关类
    void init_connections();//连接用到的信号和槽
    void init_window(); //初始化 其它的窗口
    void init_menu_acions(); //初始化 菜单
    void init_network ();
private:
    ICE_Lrc* iceLrc;
    QMap<qint64, QString> m_lrcMap;

    QStringList m_playList;
    QString m_playingFile;
    QString m_iceDir;

    int m_preIndex;
    int m_currentIndex;
    int m_playMode; // ICE_Play_Mode

    /*! 都是图形按钮*/
    ICE_Button* m_minButton;
    ICE_Button* m_exitButton;
    ICE_Button* m_addButton;
    ICE_Button* m_lyrButton;
    ICE_Button* m_lastButton;
    ICE_Button* m_nextButton;
    ICE_Button* m_playButton;
    ICE_Button* m_pauseButton;
    ICE_Button* m_modeButton;
    ICE_Button* m_mminButton;
    ICE_Button* m_logoButton;

    IceLabel* m_nameLabel;
    QLabel* m_musicianLabel;
    QLabel* m_albumLabel;
    QLabel* m_timeLabel;
    QLabel* m_picLabel; //主窗口的专辑图片

    QSlider* m_playSlider;
    QSlider* m_volSlider;

    QTableWidget* playlistTabel;

    QMediaPlayer* m_mediaPlayer;
    QMediaPlaylist* m_mediaPlayerList;

    QMenu* m_contextMenuLess;
    QMenu* m_contextMenuMore;
    QMenu* m_playModeMenu;

    QActionGroup* modeActionGroup;
    QAction* m_modeSingal;
    QAction* m_modeListCircle;
    QAction* m_modeSingalCircle;
    QAction* m_modeRandom;
    QAction* m_addMusic;
    QAction* m_addfileDiv;
    QAction* m_removeCurr;
    QAction* m_removeAll;

    ICE_Vol_Button* m_volButton; //单击显示menu窗口控制音量的按钮
    ICE_MiniWindow* m_miniForm;

    NetWorker* networker;
    QString songName;
    QString songArtist;
    QString songId;
    QString picUrl;
    QString lrcUrl;
    int receiveState;

    int playPosition;

};

#endif // ICEPLAYER_H
