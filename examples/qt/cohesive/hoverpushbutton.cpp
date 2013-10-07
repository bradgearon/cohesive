#include "hoverpushbutton.h"

HoverPushButton::HoverPushButton(QWidget *parent) : QPushButton(parent)
{
    this->setMouseTracking(true);
}

void HoverPushButton::enterEvent(QEvent *event) {
    emit onHover(event, true, this);
}

void HoverPushButton::leaveEvent(QEvent *event){
    emit onHover(event, false, this);
}


