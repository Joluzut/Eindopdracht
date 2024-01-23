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
    void maakLaadpunt();
    void singleAction(volatile unsigned int) override;

private:
    int percentage;
    int hoeveelheidTotaal;
    int minuten;
    std::vector<Auto*> autos;
    std::vector<Laadpunt*> laadpunten;
};

