#include "setSimulatie.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

setSimulatie::setSimulatie(int percentage)
{
    this->percentage = percentage;
    hoeveelheidDU = percentage / 100 * 3688;
    hoeveelheidUD = percentage / 100 * 4321;
    srand(static_cast<unsigned>(time(NULL)));

    
    autosDU.resize(hoeveelheidDU, Auto());
    autosUD.resize(hoeveelheidUD, Auto());
}

setSimulatie::~setSimulatie()
{
	

}

void setSimulatie::maakAuto()
{
    for (int i = 0; i < hoeveelheidDU; i++)
    {
        // Auto(int type, int soc, int bestemming, int locatie);
        autosDU[i].createAuto(i % 3, 10 + (rand() % 91), 1, rand() % 40);
        autosDU[i].showAuto();
    }
    for (int i = 0; i < hoeveelheidUD; i++)
    {
        autosUD[i].createAuto(i % 3, 10 + (rand() % 91), 2, rand() % 40);
        autosUD[i].showAuto();
    }
}
