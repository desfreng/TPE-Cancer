#include "videoplayer.h"

VideoPlayer::VideoPlayer (QWidget* parent) : QWidget (parent)
{
    QPalette pal = palette();
    pal.setColor (QPalette::Window, Qt::black);
    pal.setColor (QPalette::Button, Qt::gray);
    pal.setColor (QPalette::Highlight, Qt::red);
    setPalette (pal);
    
    _videoSurface = new QVideoWidget;
    
    _slider = new QSlider;
    _slider->setOrientation (Qt::Horizontal);
    _slider->setPalette (pal);
    
    _audioBut = new QPushButton;
    _audioBut->setPalette (pal);
    _audioBut->setFixedSize (30, 30);
    _audioBut->setIconSize (_audioBut->size() * 4 / 5);
    _audioBut->setIcon (_2PM (Images::Icon::Son));
    
    _exitBut = new QPushButton;
    _exitBut->setPalette (pal);
    _exitBut->setPalette (pal);
    _exitBut->setFixedSize (30, 30);
    _exitBut->setIconSize (_exitBut->size() * 4 / 5);
    _exitBut->setIcon (_2PM (Images::Icon::Quit));
    
    _button = new ButtonOverlay ("");
    
    
    _player = new QMediaPlayer();
    _player->setMedia (QUrl ("https://sample-videos.com/video123/mp4/720/big_buck_bunny_720p_1mb.mp4"));
    _player->setVideoOutput (_videoSurface);
    _player->play();
    
    QHBoxLayout* bar = new QHBoxLayout;
    bar->addWidget (_audioBut);
    bar->addWidget (_slider);
    bar->addWidget (_exitBut);
    
    QVBoxLayout* principal = new QVBoxLayout;
    principal->addWidget (_videoSurface);
    principal->addLayout (bar);
    
    setLayout (principal);
    
    timer = new QTimer (this);
    connect (timer, &QTimer::timeout, [ = ] {
        _audioBut->setVisible (!_audioBut->isVisible());
        _exitBut->setVisible (!_exitBut->isVisible());
        _slider->setVisible (!_slider->isVisible());
    });
    timer->start (1000);
}

VideoPlayer::~VideoPlayer()
{

}
