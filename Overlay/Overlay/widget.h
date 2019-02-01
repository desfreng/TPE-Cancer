#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QMessageBox>
#include "buttonoverlay.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
        Q_OBJECT
        
    public:
        explicit Widget (QWidget* parent = nullptr);
        ~Widget();
        
    protected:
        bool event (QEvent* event);
        
    private:
        Ui::Widget* ui;
        ButtonOverlay* _but;
};

#endif // WIDGET_H
