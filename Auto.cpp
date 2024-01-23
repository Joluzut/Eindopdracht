#include "Auto.h"

Auto::Auto()
{
	this->id = 0;
	this->type = 0;
	this->accucapaciteit = 0;
	this->verbruik = 0;
	this->SoC = 0;
	this->locatie = 0;
	this->tijd = 0;
	this->naam = "";
	this->wachten = 0;
	this->laadpunt = nullptr;
}

Auto::~Auto()
{

}


void Auto::createAuto(int id, int type, int soc, Laadpunt* laadpunt, int locatie, int tijd)
{
	//maak auto aan met gegeven parameters
	this->id = id;
	this->type = type;
	this-> SoC = soc;
	this->laadpunt = laadpunt;
	this->locatie = locatie;
	this->tijd = tijd;

	switch (type)
	{
	//auto specifieke gegevens
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
	//autos krijgen een random tijd, als de tijd voorbij is gaat de auto rijden
	//zodra de auto voorbij de 40000 meter is stopt de auto met rijden
	{
		if (laadpunt->getID() == 1 && SoC <= 20 && locatie >= 29972 && locatie <= 30028)
		{
		//Lingehorst bereikt en te weinig SoC
			if (wachten == 0)
			{
				laadpunt->addAuto(this);
			}
			wachten = 1;
		}
		else if (laadpunt->getID() == 2 && SoC <= 20 && locatie >= 11972 && locatie <= 12028)
		{
		//Bisde bereikt en te weinig SoC
			if(wachten == 0)
			{
				laadpunt->addAuto(this);
			}
			wachten = 1;
		}
		else
		{
			//100 km/u = 27.78 m/s
			locatie = locatie + 27.78;
			//60 kWh = 60.000 Wh		68 kWh = 68.000 Wh		62 kWh = 62.000 Wh
			//142 Wh/km = 0,142 Wh/m	168 Wh/km = 0,168 Wh/m	166 Wh/km = 0,166 Wh/m
			//0,142 / 60.000 * 100 = % per meter
			SoC = SoC - ((verbruik / 1000.0) / (accucapaciteit * 10000.0) * 100.0 * 27.78);
			wachten = 0;
		}
	}
}

void Auto::fullCharge()
{
	//laad auto op tot 100%
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
	std::cout << "Bestemming: " << laadpunt->getID() << std::endl;
	std::cout << "Tijd: " << tijd << std::endl;
}

int Auto::getID()
{
	return id;
}

