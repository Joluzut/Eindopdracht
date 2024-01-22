#include "setSimulatie.h"
#include "Clock.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <process.h>
#include <random>

setSimulatie::setSimulatie(int percentage)
{
    std::cout << "Simulatie start" << std::endl;
    this->percentage = percentage;

    hoeveelheidDU = static_cast<int>((percentage * 3688) / 100);
    hoeveelheidUD = static_cast<int>((percentage * 4321) / 100);
    //hoeveelheidDU = 3;
    //hoeveelheidUD = 3;
    
    std::random_device rd;
    std::mt19937 gen(rd());

    Clock::instance().loop(3600);
    
     
    std::cout << "Simulatie gestart" << std::endl;
    std::cout << laadpunten[0]->getLength() << std::endl;
    std::cout << laadpunten[1]->getLength() << std::endl;

}

setSimulatie::~setSimulatie()
{
    std::cout << "Simulatie gestopt" << std::endl;

    for (int i = 0; i < hoeveelheidDU; i++) {
        delete autosDU[i];
    }

    for (int i = 0; i < hoeveelheidUD; i++) {
        delete autosUD[i];
    }

    for (int i = 0; i < 2; i++) {
        delete laadpunten[i];
    } 
}

void setSimulatie::maakAuto()
{
    int random;
    int idAuto;
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> randomDist(0, 100);
    std::uniform_int_distribution<> randomSoC(10, 100);
    std::uniform_int_distribution<> randomLoc(0, 40);
    std::uniform_int_distribution<> randomTime(0, 3600);

    std::cout << "maakautos start" << std::endl;

    for (int i = 0; i < hoeveelheidDU; i++)
    {
        random = randomDist(gen);
        if (random < 51)
        {
            idAuto = 0;
        }
        else if (random < 76)
        {
            idAuto = 1;
        }
        else
        {
            idAuto = 2;
        }

        autosDU[i]->createAuto(i, idAuto, randomSoC(gen), laadpunten[0], randomLoc(gen), randomTime(gen));
    }

    for (int i = 0; i < hoeveelheidUD; i++)
    {
        random = randomDist(gen);
        if (random < 51)
        {
            idAuto = 0;
        }
        else if (random < 76)
        {
            idAuto = 1;
        }
        else
        {
            idAuto = 2;
        }

        autosUD[i]->createAuto(i, idAuto, randomSoC(gen), laadpunten[1], randomLoc(gen), randomTime(gen));
    }
    std::cout << "maakautos klaar" << std::endl;
}

void setSimulatie::showAuto()
{
    std::cout << "showautos start" << std::endl;
    for (int i = 0; i < hoeveelheidDU; i++)
    {
        autosDU[i]->showAuto();
    }
    for (int i = 0; i < hoeveelheidUD; i++)
    {
        autosUD[i]->showAuto();
    }
    std::cout << "showautos klaar" << std::endl;
}

void setSimulatie::maakLaadpunt()
{
    laadpunten[0]->createLaadpunt(30, "Lingehorst", 1);
    laadpunten[1]->createLaadpunt(12, "Bisde", 2);
    laadpunten[0]->showLaadpunt();
    laadpunten[1]->showLaadpunt();
}

void setSimulatie::singleAction(volatile unsigned int time)
{
    if (time == 1)
    {
        autosDU.resize(hoeveelheidDU, nullptr);
        autosUD.resize(hoeveelheidUD, nullptr);
        laadpunten.resize(2, nullptr);

        for (int i = 0; i < hoeveelheidDU; i++) {
            autosDU[i] = new Auto();
        }

        for (int i = 0; i < hoeveelheidUD; i++) {
            autosUD[i] = new Auto();
        }

        for (int i = 0; i < 2; i++) {
            laadpunten[i] = new Laadpunt();
        }
        maakAuto();
        maakLaadpunt();
        //showAuto();
    }
}
