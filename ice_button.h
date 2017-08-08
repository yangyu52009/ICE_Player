#ifndef ICE_BUTTON_H
#define ICE_BUTTON_H
#include <QPushButton>

class ICE_Button : public QPushButton
{
    Q_OBJECT
public:
    ICE_Button(QWidget* parent = 0);
    ~ICE_Button();

    /*! 设置按钮图标，如果只指定一个图标，那么全部使用该图标*/
    void ice_set_ButtonIcon(const QIcon& noramalIcon,
                            const QIcon& focusIcon = QIcon(),
                            const QIcon& pressedIcon = QIcon());


private:
    QIcon m_normalIcon;
    QIcon m_focusIcon;
    QIcon m_pressedIcon;


    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
};

#endif // ICE_BUTTON_H
