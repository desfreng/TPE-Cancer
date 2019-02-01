#include "app.h"
#include "ui_app.h"

App::~App()
{
    delete ui;
    delete manager;
}

App::App (QWidget* parent) : QWidget (parent), ui (new Ui::App)
{
    ui->setupUi (this);
    
    overDroite = new ButtonOverlay (Images::Play, this);
    overDroite->setFixedSize (125, 125);
    overDroite->setVisible (false);
    
    overGauche = new ButtonOverlay (Images::Play, this);
    overGauche->setFixedSize (125, 125);
    overGauche->setVisible (false);
    
    //showFullScreen();
    
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
        launchVideo();
    });
    connect (overGauche, &ButtonOverlay::clicked, [ = ] {
        _butCliked = OverlayBut::Gauche;
        launchVideo();
    });
    
    cursorTimer = new QTimer (this);
    connect (cursorTimer, &QTimer::timeout, this, &App::updateOverlays);
    cursorTimer->start (100);
    
    manager = new ButManager (this);
    
    resetButton();
    homeCliked();
    
    manager->validate (ButManager::Introduction);
    manager->validate (ButManager::Partie1);
    manager->validate (ButManager::CancerEtIons);
    manager->validate (ButManager::Partie2);
    manager->validate (ButManager::Radiotherapie);
    manager->validate (ButManager::Chimiotherapie);
    manager->validate (ButManager::Partie3);
    manager->validate (ButManager::PourquoiIons);
    manager->validate (ButManager::ProductionParticules);
    manager->validate (ButManager::Partie4);
    manager->validate (ButManager::Experience);
    manager->validate (ButManager::Differences);
    manager->validate (ButManager::Conclusion);
}

void App::updateOverlays()
{
    QRect MiddleLabelRect = ui->Text2Label->rect();
    QPoint cursorpos = ui->Text2Label->mapFromGlobal (QCursor::pos());
    QPoint RectPos = ui->Text2Label->mapTo (this, ui->Text2Label->rect().topLeft());
    
    overDroite->setVisible (false);
    overGauche->setVisible (false);
    
    switch (_current) {
        case Page::Conclusion:
        case Page::None:
        case Page::Introduction:
            return;
            
        case Page::Partie1:
            if (MiddleLabelRect.contains (cursorpos)) {
                overGauche->setVisible (true);
                overGauche->move (RectPos + QPoint (425 - overGauche->width() / 2, 150 - overGauche->height() / 2));
            }
            
            break;
            
        case Page::Partie2:
        case Page::Partie3:
        case Page::Partie4:
            QRect Temp = MiddleLabelRect;
            Temp.setWidth (MiddleLabelRect.width() / 2);
            
            if (Temp.contains (cursorpos)) {
                overGauche->move (RectPos + QPoint (212 - overGauche->width() / 2, 150 - overGauche->height() / 2));
                overGauche->setVisible (true);
            }
            else if (MiddleLabelRect.contains (cursorpos) && !Temp.contains (cursorpos)) {
                overDroite->setVisible (true);
                overDroite->move (RectPos + QPoint (637 - overGauche->width() / 2, 150 - overGauche->height() / 2));
            }
            
            break;
    }
}

void App::resetButton()
{
    ui->IntroBut->setIcon (_2PM (Images::ButtonEnable::Introduction));
    ui->InfoBut->setIcon (_2PM (Images::ButtonEnable::Information));
    
    if (manager->isEnable (ButManager::Partie1)) {
        ui->P1But->setIcon (_2PM (Images::ButtonEnable::Partie1));
    }
    else {
        ui->P1But->setIcon (_2PM (Images::ButtonForbidden::Partie1));
    }
    
    if (manager->isEnable (ButManager::Partie2)) {
        ui->P2But->setIcon (_2PM (Images::ButtonEnable::Partie2));
    }
    else {
        ui->P2But->setIcon (_2PM (Images::ButtonForbidden::Partie2));
    }
    
    if (manager->isEnable (ButManager::Partie3)) {
        ui->P3But->setIcon (_2PM (Images::ButtonEnable::Partie3));
    }
    else {
        ui->P3But->setIcon (_2PM (Images::ButtonForbidden::Partie3));
    }
    
    if (manager->isEnable (ButManager::Partie4)) {
        ui->P4But->setIcon (_2PM (Images::ButtonEnable::Partie4));
    }
    else {
        ui->P4But->setIcon (_2PM (Images::ButtonForbidden::Partie4));
    }
    
    if (manager->isEnable (ButManager::Conclusion)) {
        ui->ConcluBut->setIcon (_2PM (Images::ButtonEnable::Conclusion));
    }
    else {
        ui->ConcluBut->setIcon (_2PM (Images::ButtonForbidden::Conclusion));
    }
}

void App::homeCliked()
{
    _current = Page::None;
    
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
    ui->IntroBut->setIcon (_2PM (Images::ButtonCliked::Introduction));
}

void App::Partie1Cliked()
{
    if (manager->isEnable (ButManager::Partie1)) {
    
        _current = Page::Partie1;
        
        ui->scrollArea->verticalScrollBar()->setValue (0);
        
        manager->validate (ButManager::Partie1);
        resetButton();
        ui->StackedView->setCurrentIndex (1);
        ui->P1But->setIcon (_2PM (Images::ButtonCliked::Partie1));
        ui->Text2Label->setPixmap (_2PM (Images::Preview::PartieI));
        ui->ComplementLabel->setPixmap (_2PM (Images::Complements::NoteI));
    }
    else {
        //TODO : Show Help Message
    }
}

void App::Partie2Cliked()
{
    if (manager->isEnable (ButManager::Partie2)) {
        _current = Page::Partie2;
        
        ui->scrollArea->verticalScrollBar()->setValue (0);
        
        manager->validate (ButManager::Partie2);
        resetButton();
        ui->StackedView->setCurrentIndex (1);
        ui->P2But->setIcon (_2PM (Images::ButtonCliked::Partie2));
        ui->Text2Label->setPixmap (_2PM (Images::Preview::PartieII));
        ui->ComplementLabel->setPixmap (_2PM (Images::Complements::NoteII));
    }
    else {
        //TODO : Show Help Message
    }
}

void App::Partie3Cliked()
{
    if (manager->isEnable (ButManager::Partie3)) {
        _current = Page::Partie3;
        
        ui->scrollArea->verticalScrollBar()->setValue (0);
        
        manager->validate (ButManager::Partie3);
        resetButton();
        ui->StackedView->setCurrentIndex (1);
        ui->P3But->setIcon (_2PM (Images::ButtonCliked::Partie3));
        ui->Text2Label->setPixmap (_2PM (Images::Preview::PartieIII));
        ui->ComplementLabel->setPixmap (_2PM (Images::Complements::NoteIII));
    }
    else {
    
        //TODO : Show Help Message
    }
}

void App::Partie4Cliked()
{
    if (manager->isEnable (ButManager::Partie4)) {
        _current = Page::Partie4;
        
        manager->validate (ButManager::Partie4);
        resetButton();
        
        ui->scrollArea->verticalScrollBar()->setValue (0);
        
        
        ui->StackedView->setCurrentIndex (1);
        ui->P4But->setIcon (_2PM (Images::ButtonCliked::Partie4));
        ui->Text2Label->setPixmap (_2PM (Images::Preview::PartieIV));
        ui->ComplementLabel->setPixmap (_2PM (Images::Complements::Vide));
    }
    else {
    
        //TODO : Show Help Message
    }
}

void App::conclusionCliked()
{
    if (manager->isEnable (ButManager::Conclusion)) {
        _current = Page::Conclusion;
        
        manager->validate (ButManager::Conclusion);
        resetButton();
        ui->StackedView->setCurrentIndex (0);
        ui->TextHomeLabel->setPixmap (_2PM (Images::Texte::Conclusion));
        ui->ConcluBut->setIcon (_2PM (Images::ButtonCliked::Conclusion));
    }
    else {
    
        //TODO : Show Help Message
    }
}

void App::informationCliked()
{
    _current = Page::None;
    
    resetButton();
    ui->StackedView->setCurrentIndex (0);
    ui->TextHomeLabel->setPixmap (_2PM (Images::Texte::Information));
    ui->InfoBut->setIcon (_2PM (Images::ButtonCliked::Information));
}

void App::NextPage()
{
    switch (_current) {
        case Page::Introduction:
        case Page::Conclusion:
        case Page::None:
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
        case Page::None:
        case Page::Conclusion:
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

void App::launchVideo()
{
    //TODO : Code Video Launch && Validate !
}
