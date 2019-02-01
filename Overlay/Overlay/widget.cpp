#include "widget.h"
#include "ui_widget.h"

Widget::Widget (QWidget* parent) : QWidget (parent), ui (new Ui::Widget)
{
    ui->setupUi (this);
    
    _but = new ButtonOverlay (":/Test/play", this);
    
    _but->setFixedSize (QSize (200, 200));
    _but->setGeometry (width() / 2 / -_but->width() / 2, height() / -_but->height() / 2, _but->width(), _but->height());
    _but->show();
    
    connect (_but, &ButtonOverlay::clicked, [ = ] {
        QMessageBox::information (this, "Yes !", "Cliked !");
    });
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::event (QEvent* event)
{
    switch (event->type()) {
        case QEvent::Show:
            _but->show();
            QTimer::singleShot (50, this, [ = ] {
                _but->setGeometry ((width() - _but->width()) / 2, (height() - _but->height()) / 2, _but->width(), _but->height());
            });
            //Wait until the Main Window be shown
            break;
            
        case QEvent::WindowActivate:
        case QEvent::Resize:
        case QEvent::Move:
            _but->setGeometry ((width() - _but->width()) / 2, (height() - _but->height()) / 2, _but->width(), _but->height());
            break;
            
        default:
            break;
    }
    
    return QWidget::event (event);
}
