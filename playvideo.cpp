#include "playvideo.h"
#include "ui_playvideo.h"

PlayVideo::PlayVideo (QWidget* parent) : QWidget (parent), _forceClose (false), ui (new Ui::PlayVideo)
{
    ui->setupUi (this);
    _dialog = new SonDialog (this);
    
    hide();
    
    setFocusPolicy (Qt::StrongFocus);
    
    QPalette pal = palette();
    pal.setColor (QPalette::Window, Qt::black);
    pal.setColor (QPalette::Button, Qt::gray);
    pal.setColor (QPalette::Highlight, Qt::red);
    setPalette (pal);
    
    ui->video->setAspectRatioMode (Qt::KeepAspectRatio);
    ui->slider->setPalette (pal);
    ui->sonBut->setPalette (pal);
    ui->exitBut->setPalette (pal);
    
    _player = new QMediaPlayer (this, QMediaPlayer::StreamPlayback);
    _player->setVideoOutput (ui->video);
    
    ui->stackedWidget->setCurrentIndex (1);
    
    timer = new QTimer (this);
    connect (timer, &QTimer::timeout, this, &PlayVideo::UpdateInterface);
    
    oldCursorPos = ui->stackedWidget->mapFromGlobal (QCursor::pos());
    timer->start (100);
    
    connect (_player, &QMediaPlayer::durationChanged, ui->slider, &QSlider::setMaximum);
    connect (ui->playBut, &QPushButton::clicked, this, &PlayVideo::tooglePausePlay);
    connect (ui->exitBut, &QPushButton::clicked, this, &PlayVideo::closeMedia);
    
    connect (ui->sonBut, &QPushButton::clicked, [ = ] {
    
        if (_player->state() == QMediaPlayer::PlayingState)
        {
            _player->pause();
            ui->playBut->setIcon (_2PM (Images::Icon::VideoPlay));
            
            setCursor (Qt::ArrowCursor);
            ui->stackedWidget->setCurrentIndex (1);
        }
        
        _dialog->exec();
    });
    
    connect (_dialog, &SonDialog::sonChanged, [ = ] {
        _player->setVolume (_dialog->getVolume());
    });
    
}

void PlayVideo::OpenMedia (QString location)
{
    setVisible (true);
    show();
    showFullScreen();
    
    grabKeyboard();
    
    _player->setMedia (QUrl (location));
    _player->setVolume (50);
    _player->play();
    
    ui->playBut->setIcon (_2PM (Images::Icon::VideoPause));
}

PlayVideo::~PlayVideo()
{
    delete ui;
}

void PlayVideo::UpdateInterface()
{
    updateSlider();
    
    if (_player->state() != QMediaPlayer::PlayingState) {
        setCursor (Qt::ArrowCursor);
        ui->stackedWidget->setCurrentIndex (1);
        return;
    }
    
    QRect zoneMouse = ui->stackedWidget->rect();
    QPoint cursorpos = ui->stackedWidget->mapFromGlobal (QCursor::pos());
    QPoint Diff = cursorpos - oldCursorPos;
    
    if (zoneMouse.contains (cursorpos) || qSqrt (Diff.x()*Diff.x() + Diff.y()*Diff.y()) > 20) {
        setCursor (Qt::ArrowCursor);
        ui->stackedWidget->setCurrentIndex (1);
    }
    else {
        ui->stackedWidget->setCurrentIndex (0);
        
        if (Diff == QPoint (0, 0)) {
            setCursor (Qt::BlankCursor);
        }
        else {
            setCursor (Qt::ArrowCursor);
        }
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
    ui->slider->setValue (0);
    
    setCursor (Qt::ArrowCursor);
    ui->stackedWidget->setCurrentIndex (1);
    
    hide();
    releaseKeyboard();
    emit MediaEnd();
}

void PlayVideo::updateSlider()
{
    qint64 delta = qAbs (ui->slider->value() - _player->position());
    
    if (delta < 1000) {
        ui->slider->setValue (static_cast<int> (_player->position()));
    }
    else {
        _player->setPosition (ui->slider->value());
    }
    
}

void PlayVideo::forceClose()
{
    _forceClose = true;
    close();
}
