#include "sondialog.h"

SonDialog::SonDialog (QWidget* parent) : QDialog (parent)
{
    _sonSlider = new QSlider;
    _sonSlider->setRange (0, 100);
    _sonSlider->setTickInterval (10);
    _sonSlider->setTickPosition (QSlider::TicksBelow);
    _sonSlider->setOrientation (Qt::Horizontal);
    _sonSlider->setMinimumWidth (100);
    _sonSlider->setValue (50);
    
    _textLabel = new QLabel;
    _textLabel->setText (tr ("Volume :"));
    
    QFormLayout* layout = new QFormLayout;
    layout->addRow (_textLabel, _sonSlider);
    
    setLayout (layout);
    
    connect (_sonSlider, &QSlider::valueChanged, [ = ] {
        emit sonChanged (_sonSlider->value());
    });
}

int SonDialog::getVolume()
{
    return _sonSlider->value();
}
