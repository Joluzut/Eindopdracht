#include "Auto.h"

Auto::Auto() : type(0), accucapaciteit(0), verbruik(0), SoC(0), locatie(0), naam(""), bestemming(0), tijd(0)
{
	
}

Auto::~Auto()
{

}


void Auto::createAuto(int id, int type, int soc, Laadpunt* laadpunt, int locatie, int tijd)
{
	this->id = id;
	this->type = type;
	this-> SoC = soc;
	this->laadpunt = laadpunt;
	this->locatie = locatie;
	this->tijd = tijd;

	switch (type)
	{
	case 0:
		naam = "Tesla Model 3";
		accucapaciteit = 60;
		verbruik = 142;
		break;
	case 1:
		naam = "Kia Niro";
		accucapaciteit = 68;
		verbruik = 168;
		break;
	case 2:
		naam = "Volkswagen ID.3";
		accucapaciteit = 62;
		verbruik = 166;
		break;
	}
}


void Auto::singleAction(volatile unsigned int time)
{
	if (time >= tijd && locatie <= 40000)
	{
		if (laadpunt->getID() == 1 && SoC <= 20 && locatie >= 29972 && locatie <= 30028)
		{
			if (wachten == 0)
			{
				laadpunt->addAuto(this);
			}
			wachten = 1;
		}
		else if (laadpunt->getID() == 2 && SoC <= 20 && locatie >= 11972 && locatie <= 12028)
		{
			if(wachten == 0)
			{
				laadpunt->addAuto(this);
			}
			wachten = 1;
		}
		else
		{
			//100 km/u = 28 m/s
			locatie = locatie + 28;
			//60 kWh = 60.000 Wh		68 kWh = 68.000 Wh		62 kWh = 62.000 Wh
			//142 Wh/km = 0,142 Wh/m	168 Wh/km = 0,168 Wh/m	166 Wh/km = 0,166 Wh/m
			SoC = SoC - ((verbruik / 1000.0) / (accucapaciteit * 10000.0) * 100.0 * 28.0);
			wachten = 0;
		}
		
		//std::cout << "Naam: "<< naam << " SoC: " << std::to_string(SoC) << " Locatie: "<< locatie << " Wachten: " << wachten << std::endl;
	}
}

void Auto::fullCharge()
{
	SoC = 100;
	wachten = 0;
}


void Auto::showAuto()
{
	std::cout << "" << std::endl;
	std::cout << "Naam: " << naam << std::endl;
	std::cout << "Accucapaciteit: " << accucapaciteit << std::endl;
	std::cout << "Verbruik: " << verbruik << std::endl;
	std::cout << "SoC: " << SoC << std::endl;
	std::cout << "Locatie: " << locatie << std::endl;
	std::cout << "Bestemming: " << bestemming << std::endl;
	std::cout << "Tijd: " << tijd << std::endl;
}

int Auto::getID()
{
	return id;
}

