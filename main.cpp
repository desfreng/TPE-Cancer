#include "app.h"
#include "videoplayer.h"

#include <QApplication>

#include "images.h"

QPixmap _2PM (QString image)
{
    return QPixmap::fromImage (QImage (image));
}

int main (int argc, char* argv[])
{
    QApplication a (argc, argv);
    
    //    App w;
    //    w.show();
    
    VideoPlayer p;
    p.show();
    
    return a.exec();
}
