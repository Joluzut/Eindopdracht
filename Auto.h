#pragma once

#include "ClockListener.cpp"
#include <string>
#include <iostream>

class Auto : public ClockListener
{
public:
    Auto();
    virtual ~Auto() = default;
    void createAuto(int type, int soc, int bestemming, int locatie);
    void showAuto();

    void singleAction(volatile unsigned) override;


private:
    int type;
    int accucapaciteit;
    int verbruik;
    int SoC;
    int locatie;
    std::string naam;
    int bestemming;
};
