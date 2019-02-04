#ifndef BUTMANAGER_H
#define BUTMANAGER_H

#include <QObject>

class ButManager : public QObject
{
        Q_OBJECT
    public:
    
        enum Module {
            Introduction = 0,
            
            Partie1 = 1,
            CancerEtAdn = 2,
            
            Partie2 = 3,
            Chimiotherapie = 4,
            Radiotherapie = 5,
            
            Partie3 = 6,
            PourquoiIons = 7,
            ProductionParticules = 8,
            
            Partie4 = 9,
            Experience = 10,
            Differences = 11,
            
            Conclusion = 12,
        };
        
        explicit ButManager (QObject* parent = nullptr);
        ~ButManager();
        
        void validate (Module mod);
        bool canSee (Module mod);
        bool haveSeen (Module mod);
        
    signals:
        void needUpdate();
        
    private :
        void updateBut();
        
        bool tab[13];
        
};

#endif // BUTMANAGER_H
