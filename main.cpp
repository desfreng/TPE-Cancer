#include "app.h"
#include <QApplication>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "medias.h"

QPixmap _2PM (QString image)
{
    return QPixmap::fromImage (QImage (image));
}

int main (int argc, char* argv[])
{
    QApplication a (argc, argv);
    
    App w;
    w.showFullScreen();
    
    return a.exec();
}
