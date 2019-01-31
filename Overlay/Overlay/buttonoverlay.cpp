#include "buttonoverlay.h"

ButtonOverlay::ButtonOverlay (QWidget* parent) : QPushButton (parent)
{
    setFlat (true);
    
    setAutoFillBackground (false);
    setWindowFlags (Qt::FramelessWindowHint);
    setAttribute (Qt::WA_TranslucentBackground);
    
}

ButtonOverlay::~ButtonOverlay()
{

}

void ButtonOverlay::paintEvent (QPaintEvent*)
{
    QPainter painter (this);
    painter.setRenderHint (QPainter::Antialiasing);
    painter.setPen (Qt::NoPen);
    painter.setBrush (QColor (100, 100, 100, 127));
    
    painter.drawRect (0, 0, width(),  height());
}
