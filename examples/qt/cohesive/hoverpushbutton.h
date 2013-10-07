#ifndef HOVERPUSHBUTTON_H
#define HOVERPUSHBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class HoverPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit HoverPushButton(QWidget *parent = 0);
private:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
signals:
    void onHover(QEvent *event, bool hover, QObject* sender);
};

#endif // HOVERPUSHBUTTON_H
