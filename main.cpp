#include "Clock.h"
#include "Gebruiker.h"
#include "setSimulatie.h"
#include <iostream>

int main()
{
    while (1)
    {
        int userInput;
        do
        {
            std::cout << "Geef de hoeveelheid elektrische auto's (0-100): ";
            std::cin >> userInput;

            //controle voor geldige invoer
            if (std::cin.fail() || userInput < 0 || userInput > 100)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "Ongeldige invoer. Voer een getal tussen 0 en 100 in." << std::endl;
            }
            else
            {
                break;
            }
        } while (true);
        //start simulatie
        setSimulatie* simulatie = new setSimulatie(userInput);
        //verwijder simulatie
        delete simulatie;
        //reset clock
        Clock::instance().reset();
    }

    return 0;
}
