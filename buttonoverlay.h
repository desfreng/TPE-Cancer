#ifndef BUTTONOVERLAY_H
#define BUTTONOVERLAY_H

#include <QPushButton>
#include <QWidget>
#include <QPainter>

class ButtonOverlay : public QPushButton
{
    public:
        explicit ButtonOverlay (QString ImagePath, QWidget* parent = nullptr);
        ~ButtonOverlay();
        
    protected:
        void paintEvent (QPaintEvent*);
        
    private:
        QPixmap* _pixMap;
};

#endif // BUTTONOVERLAY_H
