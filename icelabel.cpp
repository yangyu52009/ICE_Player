#include "icelabel.h"

IceLabel::IceLabel(QWidget *parent):
    QLabel(parent)
{
    this->ice_init ();
}
IceLabel::~IceLabel ()
{
    this->ICE_Stop ();
}

void IceLabel::ICE_Set_Text(const QString &context, const int ms)
{
    bool b = false;

    this->m_Context = context;
    this->m_Ms = ms;

    if(this->m_Ms != 0){
        if(m_Timer == NULL){ //这里犯了一个低级的错误，居然使用了赋值，而不是比较运算
            m_Timer = new QTimer(this);

            if(m_Timer) {
                b = connect (this->m_Timer, &QTimer::timeout,
                             this, &IceLabel::ice_time_out);
                this->m_Timer->start (this->m_Ms);
            }
        }
    }

}

void IceLabel::ICE_Stop()
{
    if(this->m_Timer){
        if(m_Timer->isActive ())
            m_Timer->stop ();
        delete this->m_Timer;
        m_Timer = NULL;
    }
}

void IceLabel::ice_time_out()
{
    QString str = "";
    if(this->m_Pos > this->m_Context.count ()) {
        m_Pos = 0;
    }
    str = this->m_Context.mid (m_Pos);
    this->setText (str);
    m_Pos ++;
}

void IceLabel::ice_init(int ms)
{

    this->m_Timer = NULL;

    this->m_Ms = ms;
    this->m_Context = "";
    this->m_Pos = 0;
}
