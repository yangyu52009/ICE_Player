#include "ice_button.h"




ICE_Button::ICE_Button(QWidget *parent):
    QPushButton(parent)
{
    this->setFocusPolicy (Qt::NoFocus);//设置图标无焦点

}

ICE_Button::~ICE_Button ()
{

}

void ICE_Button::ice_set_ButtonIcon(const QIcon &noramalIcon,
                                    const QIcon &focusIcon,
                                    const QIcon &pressedIcon)
{
    this->m_normalIcon = noramalIcon;
    this->m_focusIcon = focusIcon;
    this->m_pressedIcon = pressedIcon;
    this->setIcon (this->m_normalIcon);
}

void ICE_Button::mousePressEvent(QMouseEvent *event)
{
    if( !this->isEnabled () && !this->m_pressedIcon.isNull ())
        this->setIcon ( this->m_pressedIcon );

    QPushButton::mousePressEvent (event);
}

void ICE_Button::mouseReleaseEvent(QMouseEvent *event)
{
    if( this->isEnabled () && !this->m_focusIcon.isNull ())
        this->setIcon (this->m_focusIcon);
    QPushButton::mouseReleaseEvent (event);
}

void ICE_Button::enterEvent(QEvent *event)
{
    if(!this->isEnabled () && !this->m_focusIcon.isNull ())
        this->setIcon ( this->m_focusIcon );
}

void ICE_Button::leaveEvent(QEvent *event)
{
    if( this->isEnabled () )
        this->setIcon ( this->m_normalIcon );
}
