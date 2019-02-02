#include "app.h"
#include <QApplication>

#include "medias.h"

QPixmap _2PM (QString image)
{
    return QPixmap::fromImage (QImage (image));
}

int main (int argc, char* argv[])
{
    QApplication a (argc, argv);
    
    App w;
    w.show();
    
    return a.exec();
}
