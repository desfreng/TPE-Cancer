#ifndef BUTTONOVERLAY_H
#define BUTTONOVERLAY_H

#include <QPushButton>
#include <QWidget>
#include <QPainter>

class ButtonOverlay : public QPushButton
{
    public:
        explicit ButtonOverlay (QWidget* parent = nullptr);
        ~ButtonOverlay();
        
    protected:
        void paintEvent (QPaintEvent*);
};

#endif // BUTTONOVERLAY_H
