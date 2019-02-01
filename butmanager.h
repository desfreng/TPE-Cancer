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
            CancerEtIons = 2,
            
            Partie2 = 3,
            Radiotherapie = 4,
            Chimiotherapie = 5,
            
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
        bool isEnable (Module mod);
        
    signals:
        void needUpdate();
        
    private :
        void updateBut();
        
        bool tab[13];
        
};

#endif // BUTMANAGER_H