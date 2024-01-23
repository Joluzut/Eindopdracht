#include "setSimulatie.h"
#include "Clock.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <process.h>
#include <random>
#include <iomanip>

setSimulatie::setSimulatie(int percentage)
{
    this->percentage = percentage;
    minuten = 0;
    //aantal auto's berekenen
    hoeveelheidTotaal = static_cast<int>((percentage * (3688+4321)) / 100);
    laadpunten.resize(2, nullptr);
    autos.resize(hoeveelheidTotaal, nullptr);

    //random generator
    std::random_device rd;
    std::mt19937 gen(rd());
    
    //laadpunten aanmaken
    for (int i = 0; i < 2; i++) {
        laadpunten[i] = new Laadpunt();
    }

    //laadpunten vullen
    maakLaadpunt();

    //auto's aanmaken
    for (int i = 0; i < hoeveelheidTotaal; i++) {
        autos[i] = new Auto();
    }

    //auto's vullen
    maakAuto();

    std::cout << "Start Simulatie" << std::endl;
    //start klok
    Clock::instance().loop(3600);
    
     
    std::cout << "Simulatie klaar resultaten:" << std::endl;
    //resultaten
    laadpunten[0]->showData();
    laadpunten[1]->showData();

}

setSimulatie::~setSimulatie()
{
    std::cout << "Simulatie gestopt" << std::endl;

    for (int i = 0; i < hoeveelheidTotaal; i++) {
        delete autos[i];
    }

    for (int i = 0; i < 2; i++) {
        delete laadpunten[i];
    } 
}

void setSimulatie::maakAuto()
{
    int random;
    int idAuto;
    int idLaadpunt;
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> randomDist(0, 100);
    std::uniform_int_distribution<> randomSoC(10, 100);
    std::uniform_int_distribution<> randomTime(0, 3600);

    for (int i = 0; i < hoeveelheidTotaal; i++)
    {
        random = randomDist(gen);
        //genereer random auto gebaseerd gegeven getallen
        if (random < 51)
        {
            //tesla
            idAuto = 0;
        }
        else if (random < 76)
        {
            //kia
            idAuto = 1;
        }
        else
        {
            //volkswagen
            idAuto = 2;
        }
        random = randomDist(gen);
        //genereer random startpunt/laadpunt gebaseerd gegeven getallen
        if (random < 54)
        {
			idLaadpunt = 0;
		}
        else
        {
			idLaadpunt = 1;
		}
        //auto's aanmaken met genereerde gegevens
        autos[i]->createAuto(i, idAuto, randomSoC(gen), laadpunten[idLaadpunt], 0, randomTime(gen));
        //autos[i]->showAuto();  
    }
}

void setSimulatie::maakLaadpunt()
{
    //laadpunten aanmaken
    laadpunten[0]->createLaadpunt(30, "Lingehorst", 1);
    laadpunten[1]->createLaadpunt(12, "Bisde", 2);
    //laadpunten[0]->showLaadpunt();
    //laadpunten[1]->showLaadpunt();
}

void setSimulatie::singleAction(volatile unsigned int time)
{
    if (time % 60 == 1)//elke minuut laat de simulatie de gegevens zien
    {
          minuten++;
        std::cout << std::setw(12) << std::left << "Laadpunt:" << std::setw(12) << laadpunten[0]->getNaam()
            << std::setw(12) << std::left << "Wachtrij:" << std::setw(5) << laadpunten[0]->getLength()
            << std::setw(12) << std::left << "Wachttijd:" << std::setw(5) << laadpunten[0]->getWachtrij() 
            << std::setw(5) << std::left << "Tijd:" << minuten << std::endl;

        std::cout << std::setw(12) << std::left << "Laadpunt:" << std::setw(12) << laadpunten[1]->getNaam()
            << std::setw(12) << std::left << "Wachtrij:" << std::setw(5) << laadpunten[1]->getLength()
            << std::setw(12) << std::left << "Wachttijd:" << std::setw(5) << laadpunten[1]->getWachtrij()
            << std::setw(5) << std::left << "Tijd:" << minuten << std::endl;
    }
}
