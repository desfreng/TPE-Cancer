#ifndef PLAYVIDEO_H
#define PLAYVIDEO_H

#include <QWidget>
#include <QMediaPlayer>
#include <QTimer>

#include <QtDebug>

#include "buttonoverlay.h"
#include "medias.h"
#include "sondialog.h"

namespace Ui {
class PlayVideo;
}

class PlayVideo : public QWidget
{
        Q_OBJECT
        
    public:
        explicit PlayVideo (QWidget* parent = nullptr);
        ~PlayVideo();
        
    signals:
        void MediaEnd();
        
    public slots:
        void UpdateInterface();
        void OpenMedia (QString location);
        void updateSlider();
        void forceClose();
        
    protected:
        void closeEvent (QCloseEvent* event);
        void keyPressEvent (QKeyEvent* event);
        
    private slots:
        void closeMedia();
        void tooglePausePlay();
        
    private:
        bool _forceClose;
        
        Ui::PlayVideo* ui;
        
        QMediaPlayer* _player;
        QTimer* timer;
        
        QPoint oldCursorPos;
        SonDialog* _dialog;
};

#endif // PLAYVIDEO_H
