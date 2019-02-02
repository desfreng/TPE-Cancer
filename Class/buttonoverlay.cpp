#include "buttonoverlay.h"

ButtonOverlay::ButtonOverlay (QString ImagePath, QWidget* parent) : QPushButton (parent)
{
    setFlat (true);
    
    setAutoFillBackground (false);
    setWindowFlags (Qt::FramelessWindowHint);
    
    _pixMap = new QPixmap (ImagePath);
}

ButtonOverlay::~ButtonOverlay()
{
    delete _pixMap;
}

void ButtonOverlay::paintEvent (QPaintEvent*)
{
    QPainter painter (this);
    painter.setRenderHint (QPainter::Antialiasing);
    painter.setBackgroundMode (Qt::TransparentMode);
    painter.setPen (Qt::NoPen);
    
    painter.drawPixmap (rect(), *_pixMap);
}

void ButtonOverlay::mousePressEvent (QMouseEvent* event)
{
    QPoint Diff = event->pos() - rect().center();
    int radius = width() / 2;
    
    if (qSqrt (Diff.x()*Diff.x() + Diff.y()*Diff.y()) <= radius) {
        emit clicked();
    }
}
