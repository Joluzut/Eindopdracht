#pragma once

#include "Auto.h"
#include <vector>

class setSimulatie {
public:
    setSimulatie(int percentage);
    virtual ~setSimulatie();
    void maakAuto();

private:
    int percentage;
    int hoeveelheidDU;
    int hoeveelheidUD;
    std::vector<Auto> autosDU;
    std::vector<Auto> autosUD;
};
