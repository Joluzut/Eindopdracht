#pragma once

#include "Auto.h"
#include "Laadpunt.h"
#include "ClockListener.h"
#include <vector>

class setSimulatie : public ClockListener
{
public:
    setSimulatie(int percentage);
    virtual ~setSimulatie();
    void maakAuto();
    void showAuto();
    void maakLaadpunt();
    void singleAction(volatile unsigned int) override;

private:
    int percentage;
    int hoeveelheidDU;
    int hoeveelheidUD;
    std::vector<Auto*> autosDU;
    std::vector<Auto*> autosUD;
    std::vector<Laadpunt*> laadpunten;
};

