#ifndef APP_H
#define APP_H

#include <QWidget>

namespace Ui {
class App;
}

class App : public QWidget
{
    Q_OBJECT
    
public:
    explicit App(QWidget *parent = nullptr);
    ~App();
    
private:
    Ui::App *ui;
};

#endif // APP_H
