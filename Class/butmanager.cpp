#include "butmanager.h"

ButManager::ButManager (QObject* parent) : QObject (parent)
{
    for (int i = 0; i < 13; i++) {
        tab[i] = false;
    }
}

ButManager::~ButManager() {}

void ButManager::validate (Module mod)
{
    if (tab[mod] != true) {
        tab[mod] = true;
        
        emit needUpdate();
    }
}

bool ButManager::canSee (Module mod)
{
    if (mod == Module::Introduction) {
        return true;
    }
    else {
        return tab[mod - 1];
    }
}

bool ButManager::haveSeen (ButManager::Module mod)
{
    return tab[mod];
}
