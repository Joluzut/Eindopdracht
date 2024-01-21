#pragma once

#include "ClockListener.h"

#include <string>

class Gebruiker : public ClockListener
{
public:
                    Gebruiker() = default;
    virtual        ~Gebruiker() = default;

public:
            void    singleAction( volatile unsigned )   override;
};

