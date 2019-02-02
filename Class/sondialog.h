#ifndef SONDIALOG_H
#define SONDIALOG_H

#include <QDialog>
#include <QSlider>
#include <QLabel>
#include <QFormLayout>

class SonDialog : public QDialog
{
        Q_OBJECT
        
    public:
        SonDialog (QWidget* parent = nullptr);
        
        int getVolume();
        
    signals:
        void sonChanged (int volume);
        
    private:
        QSlider* _sonSlider;
        QLabel* _textLabel;
};

#endif // SONDIALOG_H
