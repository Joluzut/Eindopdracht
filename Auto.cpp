#include "Auto.h"

Auto::Auto() : type(0), accucapaciteit(0), verbruik(0), SoC(0), locatie(0), naam(""), bestemming(0)
{
	
}

void Auto::createAuto(int type, int soc, int bestemming, int locatie)
{
	this->type = type;
	this-> SoC = soc;
	this->bestemming = bestemming;
	this->locatie = locatie;

	switch (type)
	{
	case 1:
		naam = "Tesla Model 3";
		accucapaciteit = 60;
		verbruik = 142;
		break;
	case 2:
		naam = "Kia Niro";
		accucapaciteit = 68;
		verbruik = 168;
		break;
	case 3:
		naam = "Volkswagen ID.3";
		accucapaciteit = 62;
		verbruik = 166;
		break;
	}
}

void Auto::singleAction(volatile unsigned)
{

}

void Auto::showAuto()
{
	std::cout << "Naam: " << naam << std::endl;
	std::cout << "Accucapaciteit: " << accucapaciteit << std::endl;
	std::cout << "Verbruik: " << verbruik << std::endl;
	std::cout << "SoC: " << SoC << std::endl;
	std::cout << "Locatie: " << locatie << std::endl;
	std::cout << "Bestemming: " << bestemming << std::endl;
}

