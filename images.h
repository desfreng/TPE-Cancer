#ifndef IMAGES_H
#define IMAGES_H

#include <QString>
#include <QPixmap>

QPixmap _2PM (QString image);

namespace Images {

const QString Play = ":/Others/play";

namespace ButtonCliked {
const QString Conclusion = ":/ButtonCliked/conclu_Act";
const QString Information = ":/ButtonCliked/info_Act";
const QString Introduction = ":/ButtonCliked/intro_Act";
const QString Partie1 = ":/ButtonCliked/p1_Act";
const QString Partie2 = ":/ButtonCliked/p2_Act";
const QString Partie3 = ":/ButtonCliked/p3_Act";
const QString Partie4 = ":/ButtonCliked/p4_Act";
}

namespace ButtonEnable {
const QString Conclusion = ":/ButtonEnable/conclu-Act";
const QString Information = ":/ButtonEnable/info_In";
const QString Introduction = ":/ButtonEnable/intro_In";
const QString Partie1 = ":/ButtonEnable/p1_In";
const QString Partie2 = ":/ButtonEnable/p2_In";
const QString Partie3 = ":/ButtonEnable/p3_In";
const QString Partie4 = ":/ButtonEnable/p4_In";
}

namespace ButtonForbidden {
const QString Conclusion = ":/ButtonForbidden/conclu_forbid";
const QString Partie1 = ":/ButtonForbidden/p1_forbid";
const QString Partie2 = ":/ButtonForbidden/p2_forbid";
const QString Partie3 = ":/ButtonForbidden/p3_forbid";
const QString Partie4 = ":/ButtonForbidden/p4_forbid";
}

namespace Complements {
const QString NoteI = ":/Complement/Note I";
const QString NoteII = ":/Complement/Note II";
const QString NoteIII = ":/Complement/Note III";
const QString Vide = ":/Complement/Vide";

}

namespace Preview {
const QString PartieI = ":/Preview/partie I";
const QString PartieII = ":/Preview/partie II";
const QString PartieIII = ":/Preview/partie III";
const QString PartieIV = ":/Preview/partie IV";
}

namespace Texte {
const QString Conclusion = ":/Text/conclu";
const QString Information = ":/Text/info";
const QString Introduction = ":/Text/intro";
}

namespace Icon {
const QString Son = ":/Icon/sonIcon";
const QString Quit = ":/Icon/quitIcon";
}
}

#endif // IMAGES_H
