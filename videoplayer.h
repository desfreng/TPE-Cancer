#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QSlider>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTimer>

#include "buttonoverlay.h"
#include "images.h"

class VideoPlayer : public QWidget
{
        Q_OBJECT
        
    public:
        explicit VideoPlayer (QWidget* parent = nullptr);
        ~VideoPlayer();
        
    private:
        QMediaPlayer* _player;
        QVideoWidget* _videoSurface;
        
        QSlider* _slider;
        QPushButton* _audioBut;
        QPushButton* _exitBut;
        
        ButtonOverlay* _button;
        
        QTimer* timer;
};

#endif // VIDEOPLAYER_H
