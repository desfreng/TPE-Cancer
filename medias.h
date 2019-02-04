#ifndef IMAGES_H
#define IMAGES_H

#include <QString>
#include <QPixmap>

QPixmap _2PM (QString image);

namespace Images {

namespace ButtonCliked {
const QString Conclusion = ":/ButtonClicked/conclusion";
const QString Information = ":/ButtonClicked/information";
const QString Introduction = ":/ButtonClicked/introduction";
const QString Partie1 = ":/ButtonClicked/partie1";
const QString Partie2 = ":/ButtonClicked/partie2";
const QString Partie3 = ":/ButtonClicked/partie3";
const QString Partie4 = ":/ButtonClicked/partie4";
}

namespace ButtonNormal {
const QString Conclusion = ":/ButtonNormal/conclusion";
const QString Information = ":/ButtonNormal/information";
const QString Introduction = ":/ButtonNormal/introduction";
const QString Partie1 = ":/ButtonNormal/partie1";
const QString Partie2 = ":/ButtonNormal/partie2";
const QString Partie3 = ":/ButtonNormal/partie3";
const QString Partie4 = ":/ButtonNormal/partie4";
}

namespace ButtonForbidden {
const QString Conclusion = ":/ButtonForbidden/conclusion";
const QString Partie1 = ":/ButtonForbidden/partie1";
const QString Partie2 = ":/ButtonForbidden/partie2";
const QString Partie3 = ":/ButtonForbidden/partie3";
const QString Partie4 = ":/ButtonForbidden/partie4";
}

namespace Complements {
const QString Note1 = ":/Complement/note1";
const QString Note2 = ":/Complement/note2";
const QString Note3 = ":/Complement/note3";
const QString Vide = ":/Complement/emptynote";

}

namespace Affiche {
const QString Partie1 = ":/Affiches/partie1";
const QString Partie2 = ":/Affiches/partie2";
const QString Partie3 = ":/Affiches/partie3";
const QString Partie4 = ":/Affiches/partie4";
}

namespace Texte {
const QString Conclusion = ":/Textes/conclusion";
const QString Information = ":/Textes/information";
const QString Introduction = ":/Textes/introduction";
const QString Bienvenue = ":/Textes/bienvenue";
}

namespace Icon {
const QString Son = ":/Icon/iconson";
const QString Quit = ":/Icon/iconquit";
const QString Play = ":/Icon/imageplay";
const QString VideoPause = ":/Icon/videopause";
const QString VideoPlay = ":/Icon/videoplay";
}
}

namespace Videos {
const QString VideoTest = "https://sample-videos.com/video123/mp4/720/big_buck_bunny_720p_30mb.mp4";

const QString CancerEtAdn = "https://drive.google.com/uc?export=download&id=1jElIxwp8IEjy9sWoz5aySdYbuolleX9g";

const QString Chimiotherapie = "https://drive.google.com/uc?export=download&id=1hb21jfXJVQb3PjGIzLRiDTW46f27LZ15";
const QString Radiotherapie = "https://drive.google.com/uc?export=download&id=1bKmIQtNNmLS0zq6ynnaRrleE9emw8MFe";

const QString PourquoiIons = "https://drive.google.com/uc?export=download&id=1gRg7-bwMi_Vpi3SBc8DY59OOlSSo-QBN";
const QString PorductionParticule = "https://drive.google.com/uc?export=download&id=1XH111fBHGCllqrDtpin7WNIrG_xmpCVr";

const QString Experience = "https://drive.google.com/uc?export=download&id=1a-VHdEUo-XSMG2X52SfdQGjYOcOam_JB";
const QString Differences = "https://drive.google.com/uc?export=download&id=1Hnv0oVe6p9BSOxFWyrs8zQv_X6fK9TJA";

}
#endif // IMAGES_H
