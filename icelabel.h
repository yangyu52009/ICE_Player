#ifndef ICELABEL_H
#define ICELABEL_H
#include <QLabel>
#include <QTimer>



/*****************************************************
**Copyright(C), 2017-2018, zl software.
**Version: 0.01
**Author: zlyangyu
**Date: 20170808
**Description:
**      设置可以滚动的Label显示文字
** eg：
**
**      IceLabel label( this );
**      label.ICE_Set_Text( "Hello World!", 500 ); //显示的文字， 移动速度/ms
**
** status: OK
*****************************************************/
class IceLabel : public QLabel
{
    Q_OBJECT
public:
    explicit IceLabel(QWidget* parent= 0);
    ~IceLabel();

    void ICE_Set_Text(const QString& context=0, const int ms=0);
    void ICE_Stop();
private slots:
    void ice_time_out();
private:
    void ice_init(int ms=0);

private:
    QString m_Context;
    QTimer* m_Timer;
    int m_Ms;
    int m_Pos;
};

#endif // ICELABEL_H
