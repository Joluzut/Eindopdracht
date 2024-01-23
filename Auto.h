#pragma once
#include <string>
#include <iostream>
#include "ClockListener.h"
#include "Laadpunt.h"
class Auto: public ClockListener
{
public:
    Auto();
    virtual ~Auto();
    void createAuto(int id, int type, int soc, Laadpunt* laadpunt, int locatie, int tijd);
    void showAuto();
    void singleAction(volatile unsigned int) override;
    int getID();
    void fullCharge();

    //voor de laadpunt class die twee autos met elkaar vergelijkt
    bool operator==(const Auto& other) const {
        return this->id == other.id;
    }

private:
    int id;
    int type;
    int accucapaciteit;
    int verbruik;
    double SoC;
    double locatie;
    int tijd;
    std::string naam;
    bool wachten;
    Laadpunt* laadpunt;
};
