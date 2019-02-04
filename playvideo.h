#ifndef PLAYVIDEO_H
#define PLAYVIDEO_H

#include <QWidget>
#include <QMediaPlayer>
#include <QTimer>
#include <QMovie>
#include <QMessageBox>

#include "medias.h"

#include "Class/buttonoverlay.h"

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
        
        QMovie* movie;
        
        QPoint oldCursorPos;
        QString _mediaString;
};

#endif // PLAYVIDEO_H
