#include "app.h"
#include "ui_app.h"

App::App (QWidget* parent) : QWidget (parent), ui (new Ui::App)
{
    ui->setupUi (this);
    //    showFullScreen();
    
    QPalette pal = palette();
    
    pal.setColor (QPalette::Background, QColor (207, 226, 243));
    setAutoFillBackground (true);
    setPalette (pal);
    
    pal.setColor (QPalette::Background, QColor (250, 250, 250));
    ui->scrollArea->setPalette (pal);
}

App::~App()
{
    delete ui;
}
