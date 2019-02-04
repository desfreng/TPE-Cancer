#include "playvideo.h"
#include "ui_playvideo.h"

PlayVideo::PlayVideo (QWidget* parent) : QWidget (parent), _forceClose (false), ui (new Ui::PlayVideo)
{
    setWindowFlags (Qt::WindowStaysOnTopHint);
    _mediaString = "";
    ui->setupUi (this);
    
    hide();
    
    setFocusPolicy (Qt::StrongFocus);
    
    QPalette pal = palette();
    pal.setColor (QPalette::Window, Qt::black);
    pal.setColor (QPalette::Button, Qt::gray);
    pal.setColor (QPalette::Highlight, Qt::red);
    pal.setColor (QPalette::Button, Qt::gray);
    setPalette (pal);
    
    ui->video->setAspectRatioMode (Qt::KeepAspectRatio);
    ui->volumeSlider->setPalette (pal);
    ui->exitBut->setPalette (pal);
    ui->Loading->setPalette (pal);
    
    _player = new QMediaPlayer (this, QMediaPlayer::StreamPlayback);
    _player->setVideoOutput (ui->video);
    
    movie = new QMovie (":/Misc/loader");
    ui->Loading->setMovie (movie);
    movie->start();
    
    ui->stackedWidget->setCurrentIndex (1);
    ui->VideoStacked->setCurrentIndex (0);
    
    connect (_player, QOverload<QMediaPlayer::Error>::of (&QMediaPlayer::error),
    [ = ] (QMediaPlayer::Error error) {
        switch (error) {
            case QMediaPlayer::NoError:
                return ;
                
            case QMediaPlayer::ServiceMissingError:
            case QMediaPlayer::FormatError:
                QMessageBox::information (this, "Lecture de la Video", "Une erreur est survenue lors de la lecture de la video. L'installation d'un pack de Codec Vidéo et Audio (tel que LAVFilters) peut résoudre ce problème\nErreur : " + QString (_player->errorString() + "\nCette video est disponible à l'adresse suivante : \n" + _mediaString));
                closeMedia();
                break;
                
            case QMediaPlayer::NetworkError:
                QMessageBox::information (this, "Lecture de la Video", "Une erreur est survenue lors de la lecture de la video. Le lecteur n'arrive pas a accéder à internet, Verifier votre connection Internet\nErreur : " + QString (_player->errorString() + "\nCette video est disponible à l'adresse suivante : \n" + _mediaString));
                closeMedia();
                break;
                
            default:
                QMessageBox::information (this, "Lecture de la Video", "Une erreur est survenue lors de la lecture de la video.\nErreur : " + QString (_player->errorString() + "\nCette video est disponible à l'adresse suivante : \n" + _mediaString));
                closeMedia();
        }
        
    });
    
    
    connect (_player, &QMediaPlayer::mediaStatusChanged, this, [ = ]() {
        if (_player->mediaStatus() == QMediaPlayer::StalledMedia) {
            ui->VideoStacked->setCurrentIndex (0);
            
        }
        else {
            ui->VideoStacked->setCurrentIndex (1);
        }
    });
    
    
    timer = new QTimer (this);
    connect (timer, &QTimer::timeout, this, &PlayVideo::UpdateInterface);
    
    oldCursorPos = ui->stackedWidget->mapFromGlobal (QCursor::pos());
    timer->start (100);
    
    connect (ui->playBut, &QPushButton::clicked, this, &PlayVideo::tooglePausePlay);
    connect (ui->exitBut, &QPushButton::clicked, this, &PlayVideo::closeMedia);
    connect (ui->volumeSlider, &QSlider::valueChanged, _player, &QMediaPlayer::setVolume);
}

void PlayVideo::OpenMedia (QString location)
{
    setVisible (true);
    show();
    showFullScreen();
    
    ui->volumeSlider->setValue (50);
    
    grabKeyboard();
    
    _mediaString = location;
    
    _player->setMedia (QUrl (location));
    _player->setVolume (50);
    _player->play();
    
    
    ui->playBut->setIcon (_2PM (Images::Icon::VideoPause));
}

PlayVideo::~PlayVideo()
{
    delete ui;
    delete movie;
}

void PlayVideo::UpdateInterface()
{


    if (_player->state() != QMediaPlayer::PlayingState) {
        setCursor (Qt::ArrowCursor);
        ui->stackedWidget->setCurrentIndex (1);
        return;
    }
    
    QRect zoneMouse = ui->stackedWidget->rect();
    QPoint cursorpos = ui->stackedWidget->mapFromGlobal (QCursor::pos());
    QPoint Diff = cursorpos - oldCursorPos;
    
    if (zoneMouse.contains (cursorpos) || Diff != QPoint (0, 0)) {
        setCursor (Qt::ArrowCursor);
        ui->stackedWidget->setCurrentIndex (1);
    }
    else {
        ui->stackedWidget->setCurrentIndex (0);
        setCursor (Qt::BlankCursor);
    }
    
    oldCursorPos = cursorpos;
}

void PlayVideo::closeEvent (QCloseEvent* event)
{
    if (_forceClose) {
        event->accept();
        releaseKeyboard();
        setCursor (Qt::ArrowCursor);
        _player->stop();
        emit MediaEnd();
    }
    else {
        event->ignore();
        closeMedia();
    }
}

void PlayVideo::keyPressEvent (QKeyEvent* event)
{
    if (event->key() == Qt::Key_Space) {
        tooglePausePlay();
    }
    else if (event->key() == Qt::Key_Escape) {
        closeMedia();
    }
}

void PlayVideo::tooglePausePlay()
{
    switch (_player->state()) {
        case QMediaPlayer::PlayingState:
            _player->pause();
            ui->playBut->setIcon (_2PM (Images::Icon::VideoPlay));
            break;
            
        case QMediaPlayer::StoppedState:
        case QMediaPlayer::PausedState:
            _player->play();
            ui->playBut->setIcon (_2PM (Images::Icon::VideoPause));
            setCursor (Qt::ArrowCursor);
            ui->stackedWidget->setCurrentIndex (1);
            break;
    }
    
}

void PlayVideo::closeMedia()
{
    _player->stop();
    
    setCursor (Qt::ArrowCursor);
    ui->stackedWidget->setCurrentIndex (1);
    
    hide();
    releaseKeyboard();
    emit MediaEnd();
}

void PlayVideo::forceClose()
{
    _forceClose = true;
    close();
}


