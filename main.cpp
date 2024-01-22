#include "Clock.h"
#include "Gebruiker.h"
#include "setSimulatie.h"


#include <iostream>

int main()
{
    while (1)
    {
        int userInput;
        std::cout << "Geef de hoeveelheid elektrische auto's: ";
        std::cin >> userInput;
        setSimulatie* simulatie = new setSimulatie(userInput);

        delete simulatie;
        Clock::instance().reset();
    }
    

    return 0;
}
