#ifndef BUTTONOVERLAY_H
#define BUTTONOVERLAY_H

#include <QPushButton>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QtMath>

class ButtonOverlay : public QPushButton
{
    public:
        explicit ButtonOverlay (QString ImagePath, QWidget* parent = nullptr);
        ~ButtonOverlay();
        
    protected:
        void paintEvent (QPaintEvent*);
        void mousePressEvent (QMouseEvent* event);
        
    private:
        QPixmap* _pixMap;
};

#endif // BUTTONOVERLAY_H
