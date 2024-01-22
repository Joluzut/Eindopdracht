#include "Clock.h"
#include "Gebruiker.h"
#include "setSimulatie.h"

#include <iostream>
#include <vector>

#define MAX_TIME            3600
#define MAX_PARTICIPANTS   10000

void timeLoop()
{
    Clock::instance().loop( MAX_TIME );
}

int main()
{
    setSimulatie* simulatie = new setSimulatie(5);
    

    delete simulatie;

    //Clock::instance().reset();

    return 0;
}
