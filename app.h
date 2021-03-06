#ifndef APP_H
#define APP_H

#include <QWidget>
#include <QtDebug>
#include <QMouseEvent>
#include <QTimer>
#include <QScrollBar>
#include <QMessageBox>
#include <QResizeEvent>

#include "medias.h"
#include "Class/butmanager.h"
#include "Class/buttonoverlay.h"
#include "playvideo.h"

namespace Ui {
class App;
}

class App : public QWidget
{
        Q_OBJECT
        
    public:
        enum Page {
            Home = 0,
            Introduction = 1,
            Partie1 = 2,
            Partie2 = 3,
            Partie3 = 4,
            Partie4 = 5,
            Conclusion = 6,
            Information = 7,
        };
        enum OverlayBut {
            Gauche,
            Droite,
        };
        
        explicit App (QWidget* parent = nullptr);
        ~App();
        
    public slots:
        void homeCliked();
        void introductionCliked();
        void informationCliked();
        void conclusionCliked();
        void Partie1Cliked();
        void Partie2Cliked();
        void Partie3Cliked();
        void Partie4Cliked();
        
        void NextPage();
        void PreviousPage();
        
    protected slots:
        void resetButton();
        
    private:
        void updateOverlays();
        void initVideo();
        void updateSizes();
        
        void launchVideo (ButManager::Module video);
        
        Page _current;
        OverlayBut _butCliked;
        
        ButManager* manager;
        Ui::App* ui;
        
        ButtonOverlay* overDroite;
        ButtonOverlay* overGauche;
        
        QTimer* cursorTimer;
        
        PlayVideo* _videoPlayer;
};

#endif // APP_H
