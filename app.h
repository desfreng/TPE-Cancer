#ifndef APP_H
#define APP_H

#include <QWidget>
#include <QtDebug>
#include <QMouseEvent>
#include <QTimer>
#include <QScrollBar>

#include "images.h"
#include "butmanager.h"
#include "buttonoverlay.h"

namespace Ui {
class App;
}

class App : public QWidget
{
        Q_OBJECT
        
    public:
        enum Page {
            Introduction = 0,
            Partie1 = 1,
            Partie2 = 2,
            Partie3 = 3,
            Partie4 = 4,
            Conclusion = 5,
            None = -1,
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
        
    private:
        void updateOverlays();
        void resetButton();
        void launchVideo();
        
        Page _current;
        OverlayBut _butCliked;
        
        ButManager* manager;
        Ui::App* ui;
        
        ButtonOverlay* overDroite;
        ButtonOverlay* overGauche;
        
        QTimer* cursorTimer;
};

#endif // APP_H
