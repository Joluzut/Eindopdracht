#include "Gebruiker.h"

#include <chrono>
#include <iomanip>
#include <iostream>

void
Gebruiker::singleAction( volatile unsigned time )
{
    static std::mutex   cMutex;

    static unsigned     prevTime = -1;
    static unsigned     count    = 0;
    unsigned value;

    if (prevTime != time)
    {
        prevTime = time;
        count    = 0;
    }
    value = ++count;

    if ( value == 1 && !(time%100) )
    {
//        std::lock_guard<std::mutex> cLockguard(cMutex);
        std::cout << "time: " << std::setw(4) << time << " (" << std::setw(4) << count << ")" << std::endl;
    }

//    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
