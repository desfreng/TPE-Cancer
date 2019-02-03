#include "app.h"
#include "ui_app.h"

App::~App()
{
    _videoPlayer->forceClose();
    delete _videoPlayer;
    delete ui;
    delete manager;
}

App::App (QWidget* parent) : QWidget (parent), ui (new Ui::App)
{
    setWindowFlags (Qt::WindowStaysOnTopHint);
    
    ui->setupUi (this);
    
    _videoPlayer = new PlayVideo;
    
    overDroite = new ButtonOverlay (Images::Icon::Play, this);
    overDroite->setFixedSize (125, 125);
    overDroite->setVisible (false);
    
    overGauche = new ButtonOverlay (Images::Icon::Play, this);
    overGauche->setFixedSize (125, 125);
    overGauche->setVisible (false);
    
    
    QPalette pal = palette();
    
    pal.setColor (QPalette::Background, QColor (207, 226, 243));
    setAutoFillBackground (true);
    setPalette (pal);
    
    pal.setColor (QPalette::Background, QColor (250, 250, 250));
    ui->scrollArea->setPalette (pal);
    ui->HomeScrollArea->setPalette (pal);
    
    connect (ui->IntroBut, &QPushButton::clicked, this, &App::introductionCliked);
    connect (ui->P1But, &QPushButton::clicked, this, &App::Partie1Cliked);
    connect (ui->P2But, &QPushButton::clicked, this, &App::Partie2Cliked);
    connect (ui->P3But, &QPushButton::clicked, this, &App::Partie3Cliked);
    connect (ui->P4But, &QPushButton::clicked, this, &App::Partie4Cliked);
    connect (ui->ConcluBut, &QPushButton::clicked, this, &App::conclusionCliked);
    connect (ui->InfoBut, &QPushButton::clicked, this, &App::informationCliked);
    
    connect (ui->NextBut, &QPushButton::clicked, this, &App::NextPage);
    connect (ui->PrevBut, &QPushButton::clicked, this, &App::PreviousPage);
    
    connect (ui->HomeBut, &QPushButton::clicked, this, &App::homeCliked);
    
    connect (overDroite, &ButtonOverlay::clicked, [ = ] {
        _butCliked = OverlayBut::Droite;
        initVideo();
    });
    connect (overGauche, &ButtonOverlay::clicked, [ = ] {
        _butCliked = OverlayBut::Gauche;
        initVideo();
    });
    
    cursorTimer = new QTimer (this);
    connect (cursorTimer, &QTimer::timeout, this, &App::updateOverlays);
    cursorTimer->start (100);
    
    manager = new ButManager (this);
    connect (manager, &ButManager::needUpdate, this, &App::resetButton);
    
    connect (_videoPlayer, &PlayVideo::MediaEnd, [ = ] {
        show();
        showFullScreen();
    });
    
    homeCliked();
}

void App::updateSizes()
{
    int heightNotes = ui->scrollArea->height();
    ui->RightBar->setMaximumSize (5, heightNotes);
    ui->RightBar->setFixedSize (5, heightNotes);
    ui->LeftBar->setMaximumSize (5, heightNotes);
    ui->LeftBar->setFixedSize (5, heightNotes);
    
    int widthNotes = ui->scrollArea->width();
    ui->UpBar->setMaximumSize (widthNotes, 5);
    ui->UpBar->setFixedSize (widthNotes, 5);
    ui->DownBar->setMaximumSize (widthNotes, 5);
    ui->DownBar->setFixedSize (widthNotes, 5);
    
    
    int heightHome = ui->HomeScrollArea->height();
    ui->HomeRight->setMaximumSize (5, heightHome);
    ui->HomeRight->setFixedSize (5, heightHome);
    ui->HomeLeft->setMaximumSize (5, heightHome);
    ui->HomeLeft->setFixedSize (5, heightHome);
    
    int widthHome = ui->HomeScrollArea->width();
    ui->HomeUp->setMaximumSize (widthHome, 5);
    ui->HomeUp->setFixedSize (widthHome, 5);
    ui->HomeDown->setMaximumSize (widthHome, 5);
    ui->HomeDown->setFixedSize (widthHome, 5);
}

void App::updateOverlays()
{
    updateSizes();
    
    QRect MiddleLabelRect = ui->Text2Label->rect();
    QPoint cursorpos = ui->Text2Label->mapFromGlobal (QCursor::pos());
    QPoint RectPos = ui->Text2Label->mapTo (this, ui->Text2Label->rect().topLeft());
    
    overDroite->setVisible (false);
    overGauche->setVisible (false);
    
    switch (_current) {
        case Page::Introduction:
        case Page::Conclusion:
        case Page::Information:
        case Page::Home:
            return;
            
        case Page::Partie1:
            if (MiddleLabelRect.contains (cursorpos)) {
                overGauche->move (RectPos + QPoint (425 - overGauche->width() / 2, 150 - overGauche->height() / 2));
                overGauche->setVisible (manager->isEnable (ButManager::CancerEtAdn));
            }
            
            break;
            
        case Page::Partie2:
        case Page::Partie3:
        case Page::Partie4:
        
            QRect Temp = MiddleLabelRect;
            Temp.setWidth (MiddleLabelRect.width() / 2);
            
            if (Temp.contains (cursorpos)) {
                overGauche->move (RectPos + QPoint (212 - overGauche->width() / 2, 150 - overGauche->height() / 2));
                
                switch (_current) {
                    case Page::Partie2:
                        overGauche->setVisible (manager->isEnable (ButManager::Chimiotherapie));
                        break;
                        
                    case Page::Partie3:
                        overGauche->setVisible (manager->isEnable (ButManager::PourquoiIons));
                        break;
                        
                    case Page::Partie4:
                        overGauche->setVisible (manager->isEnable (ButManager::Experience));
                        break;
                        
                    default :
                        break;
                }
            }
            else if (MiddleLabelRect.contains (cursorpos) && !Temp.contains (cursorpos)) {
            
                overDroite->move (RectPos + QPoint (637 - overGauche->width() / 2, 150 - overGauche->height() / 2));
                
                switch (_current) {
                    case Page::Partie2:
                        overDroite->setVisible (manager->isEnable (ButManager::Radiotherapie));
                        break;
                        
                    case Page::Partie3:
                        overDroite->setVisible (manager->isEnable (ButManager::ProductionParticules));
                        break;
                        
                    case Page::Partie4:
                        overDroite->setVisible (manager->isEnable (ButManager::Differences));
                        break;
                        
                    default :
                        break;
                }
            }
            
            break;
    }
}

void App::resetButton()
{
    ui->IntroBut->setIcon (_2PM (Images::ButtonNormal::Introduction));
    ui->InfoBut->setIcon (_2PM (Images::ButtonNormal::Information));
    
    if (manager->isEnable (ButManager::Partie1)) {
        ui->P1But->setIcon (_2PM (Images::ButtonNormal::Partie1));
    }
    else {
        ui->P1But->setIcon (_2PM (Images::ButtonForbidden::Partie1));
    }
    
    if (manager->isEnable (ButManager::Partie2)) {
        ui->P2But->setIcon (_2PM (Images::ButtonNormal::Partie2));
    }
    else {
        ui->P2But->setIcon (_2PM (Images::ButtonForbidden::Partie2));
    }
    
    if (manager->isEnable (ButManager::Partie3)) {
        ui->P3But->setIcon (_2PM (Images::ButtonNormal::Partie3));
    }
    else {
        ui->P3But->setIcon (_2PM (Images::ButtonForbidden::Partie3));
    }
    
    if (manager->isEnable (ButManager::Partie4)) {
        ui->P4But->setIcon (_2PM (Images::ButtonNormal::Partie4));
    }
    else {
        ui->P4But->setIcon (_2PM (Images::ButtonForbidden::Partie4));
    }
    
    if (manager->isEnable (ButManager::Conclusion)) {
        ui->ConcluBut->setIcon (_2PM (Images::ButtonNormal::Conclusion));
    }
    else {
        ui->ConcluBut->setIcon (_2PM (Images::ButtonForbidden::Conclusion));
    }
    
    switch (_current) {
        case Page::Introduction:
            ui->IntroBut->setIcon (_2PM (Images::ButtonCliked::Introduction));
            break;
            
        case Page::Partie1:
            ui->P1But->setIcon (_2PM (Images::ButtonCliked::Partie1));
            break;
            
        case Page::Partie2:
            ui->P2But->setIcon (_2PM (Images::ButtonCliked::Partie2));
            break;
            
        case Page::Partie3:
            ui->P3But->setIcon (_2PM (Images::ButtonCliked::Partie3));
            break;
            
        case Page::Partie4:
            ui->P4But->setIcon (_2PM (Images::ButtonCliked::Partie4));
            break;
            
        case Page::Conclusion:
            ui->ConcluBut->setIcon (_2PM (Images::ButtonCliked::Conclusion));
            break;
            
        case Page::Information:
            ui->InfoBut->setIcon (_2PM (Images::ButtonCliked::Information));
            break;
            
        case Page::Home:
            break;
    }
}

void App::homeCliked()
{
    _current = Page::Home;
    
    resetButton();
    
    ui->StackedView->setCurrentIndex (0);
    ui->TextHomeLabel->setPixmap (_2PM ("")/*TODO: Make Home Page*/);
}

void App::introductionCliked()
{
    manager->validate (ButManager::Introduction);
    _current = Page::Introduction;
    
    resetButton();
    
    ui->StackedView->setCurrentIndex (0);
    ui->TextHomeLabel->setPixmap (_2PM (Images::Texte::Introduction));
}

void App::Partie1Cliked()
{
    if (manager->isEnable (ButManager::Partie1)) {
        manager->validate (ButManager::Partie1);
        _current = Page::Partie1;
        
        resetButton();
        
        ui->StackedView->setCurrentIndex (1);
        ui->Text2Label->setPixmap (_2PM (Images::Affiche::Partie1));
        ui->ComplementLabel->setPixmap (_2PM (Images::Complements::Note1));
        ui->scrollArea->verticalScrollBar()->setValue (0);
    }
    else {
        QMessageBox::information (this, tr ("Partie non accessible"), tr ("Cette video n'est pas encore accessible. Essayez de consulter les parties et videos précedentes pour débloquer celle-ci !"));
    }
}

void App::Partie2Cliked()
{
    if (manager->isEnable (ButManager::Partie2)) {
        manager->validate (ButManager::Partie2);
        _current = Page::Partie2;
        
        resetButton();
        
        ui->StackedView->setCurrentIndex (1);
        ui->Text2Label->setPixmap (_2PM (Images::Affiche::Partie2));
        ui->ComplementLabel->setPixmap (_2PM (Images::Complements::Note2));
        ui->scrollArea->verticalScrollBar()->setValue (0);
    }
    else {
        QMessageBox::information (this, tr ("Partie non accessible"), tr ("Cette video n'est pas encore accessible. Essayez de consulter les parties et videos précedentes pour débloquer celle-ci !"));
    }
}

void App::Partie3Cliked()
{
    if (manager->isEnable (ButManager::Partie3)) {
        manager->validate (ButManager::Partie3);
        _current = Page::Partie3;
        
        resetButton();
        
        ui->StackedView->setCurrentIndex (1);
        ui->Text2Label->setPixmap (_2PM (Images::Affiche::Partie3));
        ui->ComplementLabel->setPixmap (_2PM (Images::Complements::Note3));
        ui->scrollArea->verticalScrollBar()->setValue (0);
    }
    else {
        QMessageBox::information (this, tr ("Partie non accessible"), tr ("Cette video n'est pas encore accessible. Essayez de consulter les parties et videos précedentes pour débloquer celle-ci !"));
    }
}

void App::Partie4Cliked()
{
    if (manager->isEnable (ButManager::Partie4)) {
        manager->validate (ButManager::Partie4);
        _current = Page::Partie4;
        
        resetButton();
        
        ui->StackedView->setCurrentIndex (1);
        ui->Text2Label->setPixmap (_2PM (Images::Affiche::Partie4));
        ui->ComplementLabel->setPixmap (_2PM (Images::Complements::Vide));
        ui->scrollArea->verticalScrollBar()->setValue (0);
    }
    else {
        QMessageBox::information (this, tr ("Partie non accessible"), tr ("Cette video n'est pas encore accessible. Essayez de consulter les parties et videos précedentes pour débloquer celle-ci !"));
    }
}

void App::conclusionCliked()
{
    if (manager->isEnable (ButManager::Conclusion)) {
        manager->validate (ButManager::Conclusion);
        _current = Page::Conclusion;
        
        resetButton();
        
        ui->StackedView->setCurrentIndex (0);
        ui->TextHomeLabel->setPixmap (_2PM (Images::Texte::Conclusion));
    }
    else {
        QMessageBox::information (this, tr ("Partie non accessible"), tr ("Cette video n'est pas encore accessible. Essayez de consulter les parties et videos précedentes pour débloquer celle-ci !"));
    }
}

void App::informationCliked()
{
    _current = Page::Information;
    
    resetButton();
    
    ui->StackedView->setCurrentIndex (0);
    ui->TextHomeLabel->setPixmap (_2PM (Images::Texte::Information));
}

void App::NextPage()
{
    switch (_current) {
        case Page::Introduction:
        case Page::Conclusion:
        case Page::Information:
        case Page::Home:
            break;
            
        case Page::Partie1:
            Partie2Cliked();
            break;
            
        case Page::Partie2:
            Partie3Cliked();
            break;
            
        case Page::Partie3:
            Partie4Cliked();
            break;
            
        case Page::Partie4:
            conclusionCliked();
            break;
            
    }
}

void App::PreviousPage()
{
    switch (_current) {
        case Page::Introduction:
        case Page::Conclusion:
        case Page::Information:
        case Page::Home:
            break;
            
        case Page::Partie1:
            introductionCliked();
            break;
            
        case Page::Partie2:
            Partie1Cliked();
            break;
            
        case Page::Partie3:
            Partie2Cliked();
            break;
            
        case Page::Partie4:
            Partie3Cliked();
            break;
            
    }
}

void App::initVideo()
{
    switch (_current) {
        case Page::Introduction:
        case Page::Conclusion:
        case Page::Information:
        case Page::Home:
            return;
            
        case Page::Partie1:
            if (manager->isEnable (ButManager::CancerEtAdn)) {
                manager->validate (ButManager::CancerEtAdn);
                launchVideo (ButManager::CancerEtAdn);
            }
            else {
                QMessageBox::information (this, tr ("Video non accessible"), tr ("Cette video n'est pas encore accessible. Essayez de consulter les parties et videos précedentes pour débloquer celle-ci !"));
            }
            
            break;
            
        case Page::Partie2:
            if (_butCliked == OverlayBut::Droite) {
            
                if (manager->isEnable (ButManager::Radiotherapie)) {
                    manager->validate (ButManager::Radiotherapie);
                    launchVideo (ButManager::Radiotherapie);
                }
                else {
                    QMessageBox::information (this, tr ("Video non accessible"), tr ("Cette video n'est pas encore accessible. Essayez de consulter les parties et videos précedentes pour débloquer celle-ci !"));
                }
                
            }
            else if (_butCliked == OverlayBut::Gauche) {
            
                if (manager->isEnable (ButManager::Chimiotherapie)) {
                    manager->validate (ButManager::Chimiotherapie);
                    launchVideo (ButManager::Chimiotherapie);
                }
                else {
                    QMessageBox::information (this, tr ("Video non accessible"), tr ("Cette video n'est pas encore accessible. Essayez de consulter les parties et videos précedentes pour débloquer celle-ci !"));
                }
                
            }
            
            break;
            
        case Page::Partie3:
            if (_butCliked == OverlayBut::Droite) {
            
                if (manager->isEnable (ButManager::ProductionParticules)) {
                    manager->validate (ButManager::ProductionParticules);
                    launchVideo (ButManager::ProductionParticules);
                }
                else {
                    QMessageBox::information (this, tr ("Video non accessible"), tr ("Cette video n'est pas encore accessible. Essayez de consulter les parties et videos précedentes pour débloquer celle-ci !"));
                }
                
            }
            else if (_butCliked == OverlayBut::Gauche) {
            
                if (manager->isEnable (ButManager::PourquoiIons)) {
                    manager->validate (ButManager::PourquoiIons);
                    launchVideo (ButManager::PourquoiIons);
                }
                else {
                    QMessageBox::information (this, tr ("Video non accessible"), tr ("Cette video n'est pas encore accessible. Essayez de consulter les parties et videos précedentes pour débloquer celle-ci !"));
                }
                
            }
            
            break;
            
        case Page::Partie4:
            if (_butCliked == OverlayBut::Droite) {
            
                if (manager->isEnable (ButManager::Differences)) {
                    manager->validate (ButManager::Differences);
                    launchVideo (ButManager::Differences);
                }
                else {
                    QMessageBox::information (this, tr ("Video non accessible"), tr ("Cette video n'est pas encore accessible. Essayez de consulter les parties et videos précedentes pour débloquer celle-ci !"));
                }
                
            }
            else if (_butCliked == OverlayBut::Gauche) {
            
                if (manager->isEnable (ButManager::Experience)) {
                    manager->validate (ButManager::Experience);
                    launchVideo (ButManager::Experience);
                }
                else {
                    QMessageBox::information (this, tr ("Video non accessible"), tr ("Cette video n'est pas encore accessible. Essayez de consulter les parties et videos précedentes pour débloquer celle-ci !"));
                }
            }
            
            break;
    }
}

void App::launchVideo (ButManager::Module video)
{
    hide();
    
    switch (video) {
        case ButManager::CancerEtAdn:
            _videoPlayer->OpenMedia (Videos::CancerEtAdn);
            break;
            
        case ButManager::Chimiotherapie:
            _videoPlayer->OpenMedia (Videos::Chimiotherapie);
            break;
            
        case ButManager::Radiotherapie:
            _videoPlayer->OpenMedia (Videos::Radiotherapie);
            break;
            
        case ButManager::PourquoiIons:
            _videoPlayer->OpenMedia (Videos::PourquoiIons);
            break;
            
        case ButManager::ProductionParticules:
            _videoPlayer->OpenMedia (Videos::PorductionParticule);
            break;
            
        case ButManager::Experience:
            _videoPlayer->OpenMedia (Videos::Experience);
            break;
            
        case ButManager::Differences:
            _videoPlayer->OpenMedia (Videos::Differences);
            break;
            
        default:
            break;
    }
}
