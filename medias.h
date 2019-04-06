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

const QString CancerEtAdn = "https://drive.google.com/open?id=1RvVXRrh8fKqGhD51p8V23ERBgijJbOj1";
//https://drive.google.com/uc?export=download&id=1RvVXRrh8fKqGhD51p8V23ERBgijJbOj1";

const QString Chimiotherapie = "https://drive.google.com/uc?export=download&id=1IkgT1x1tnOOCflcCUEd8o8OZlgv59-Wz";
const QString Radiotherapie = "https://drive.google.com/uc?export=download&id=1TnEfs_pcBYMNp3_cp7lRF2IqFzM0dPEx";

const QString PourquoiIons = "https://drive.google.com/uc?export=download&id=1fsLn-D_yGxQFy3wvtdZkTrBH7jTGEZR9";
const QString PorductionParticule = "https://drive.google.com/uc?export=download&id=1kL3UZ9DgAJDnGhBEPOZEPmJZKijoiae9";

const QString Experience = "https://drive.google.com/uc?export=download&id=1MITtpL1itgxORqbR0GmyUfbrdrQ1zJb8";
const QString Differences = "https://drive.google.com/uc?export=download&id=10EDfNl7gWiqf7IGdEYJoIFzyNSv3BcYT";

}
#endif // IMAGES_H
