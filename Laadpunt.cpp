#include "Laadpunt.h"
#include "Auto.h"

Laadpunt::Laadpunt()
{
	this->ID = 0;
	this->naam = "";
	this->locatie = 0;
	this->beschikbaar = true;
	this->wachtrij = 0;
}

Laadpunt::~Laadpunt()
{

}

void Laadpunt::createLaadpunt(int locatie, std::string naam, int ID)
{
	this->ID = ID;
	this->naam = naam;
	this->locatie = locatie;
	this->beschikbaar = true;
	this->wachtrij = 0;
}

void Laadpunt::showLaadpunt()
{
	std::cout << "" << std::endl;
	std::cout << "Naam: " << naam << std::endl;
	std::cout << "Locatie: " << locatie << std::endl;
	std::cout << "Beschikbaar: " << beschikbaar << std::endl;
	std::cout << "Wachtrij: " << wachtrij << std::endl;
	std::cout << "ID: " << ID << std::endl;
}

void Laadpunt::singleAction(volatile unsigned int time)
{
	if (time % 300 == 0)
	{
		std::lock_guard<std::mutex> lock(queueMutex);

		std::cout << "Laadpunt: " << naam << " Wachtrij: " << wachtrijAuto.size() << std::endl;

		if (wachtrijAuto.size() > 0)
		{
			Auto* firstCar = wachtrijAuto.front();
			firstCar->fullCharge();
			wachtrijAuto.pop();
		}
	}
}



void Laadpunt::addAuto(Auto* newAuto)
{
	std::lock_guard<std::mutex> qLockguard(queueMutex);
	wachtrijAuto.push(newAuto);
}



int Laadpunt::getID()
{
	return ID;
}

int Laadpunt::getLength()
{
	return wachtrijAuto.size();
}