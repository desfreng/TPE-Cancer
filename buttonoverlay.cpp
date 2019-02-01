#include "buttonoverlay.h"

ButtonOverlay::ButtonOverlay (QString ImagePath, QWidget* parent) : QPushButton (parent)
{
    setFlat (true);
    
    setAutoFillBackground (false);
    setWindowFlags (Qt::FramelessWindowHint);
    setAttribute (Qt::WA_TranslucentBackground);
    
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