#include "ice_vol_button.h"
#include <QMenu>


ICE_Vol_Button::ICE_Vol_Button(QWidget *parent):
    QWidget(parent)
{
    this->m_slider = new QSlider(Qt::Horizontal, this);
    m_slider->setRange ( 0, 100 );
    m_slider->setGeometry (QRect(26, 0, 75, 25));
    this->connect (this->m_slider, &QSlider::valueChanged,
                   this, &ICE_Vol_Button::ICE_Volume_changed);
    m_slider->setStyleSheet ("QSlider::groove:horizontal{border:0px;height:4px;}"
                             "QSlider::sub-page:horizontal{background: #0096ff}"
                             "QSlider::add-page:horizontal{background: lightgray}"
                             "QSlider::handle:horizontal{background:white;"
                             "width:10px;border: #51b5fb 10px;"
                             "border-radius:5px;margin:-3px 0px -3px 0px;}");

    this->m_button = new ICE_Button(this);

    QIcon icon_button, icon_button_focus;
    icon_button.addFile (QStringLiteral(":/resource/音量调节.png"),QSize(),
                         QIcon::Normal, QIcon::Off);
    icon_button_focus.addFile (QStringLiteral(":/resource/音量调节2.png"));
    this->ICE_Set_ButtonICON (icon_button, icon_button_focus);
    m_button->setFlat (true);
    m_button->setFocusPolicy (Qt::NoFocus);

    m_button->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");
    //将这个按钮设置为无边框，没有焦点框
    m_button->setGeometry (QRect(0, 0, 25, 25));

    this->connect (this->m_button, &ICE_Button::clicked,
                   this, &ICE_Vol_Button::ICE_Button_Clicked);

    this->m_menu = new QMenu(this);

    this->m_action = new QWidgetAction(this);
    m_action->setDefaultWidget (this->m_slider);
    m_menu->addAction(m_action);
}

int ICE_Vol_Button::ICE_Get_Volume() const
{
    return this->m_slider->value ();
}

void ICE_Vol_Button::ICE_Set_Slider_Visiabel(bool val)
{
    this->m_slider->setVisible (val);
}

void ICE_Vol_Button::ICE_Set_ButtonICON(const QIcon &noramalIcon,
                                        const QIcon &focusIcon)
{
    m_button->ice_set_ButtonIcon (noramalIcon, focusIcon);
}

void ICE_Vol_Button::ICE_increase_Volume()
{
    this->m_slider->triggerAction (QSlider::SliderPageStepAdd);
}
void ICE_Vol_Button::ICE_Descrease_Volume ()
{
    this->m_slider->triggerAction (QSlider::SliderPageStepSub);
}

void ICE_Vol_Button::ICE_Set_Volume(int volume)
{
    this->m_slider->setValue (volume);
}


void ICE_Vol_Button::ICE_Button_Clicked()
{
    this->m_menu->exec(QCursor::pos ());
}

