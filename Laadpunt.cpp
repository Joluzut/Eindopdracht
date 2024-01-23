#include "Laadpunt.h"
#include "Auto.h"
#include <iomanip>

Laadpunt::Laadpunt()
{
	this->ID = 0;
	this->naam = "";
	this->locatie = 0;
	this->beschikbaar = true;
	this->wachtrij = 0;
	this->totaleWachtrij = 0;
	this->oplaadTijd = 0;
}

Laadpunt::~Laadpunt()
{

}

void Laadpunt::createLaadpunt(int locatie, std::string naam, int ID)
{
	//maak laadpunt aan met gegeven parameters
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
	wachtrij = getLength() * 5;
	//voor gemiddelde berekenen
	totaleWachtrij = totaleWachtrij + wachtrij;
	if (getLength() > 0)
	{//als er autos in de wachtrij staan
		oplaadTijd++;
		wachtrij = wachtrij - oplaadTijd / 60;
		//wachtrij wordt minder als de auto aan het opladen is
		if (oplaadTijd == 300)
		{//als de auto 5 minuten heeft opgeladen
			std::lock_guard<std::mutex> lock(queueMutex);//lock de queue
			Auto* firstCar = wachtrijAuto.front();//haal de eerste auto uit de queue
			firstCar->fullCharge();//laad de auto vol
			wachtrijAuto.pop();//haal de auto uit de queue
			oplaadTijd = 0;
		}
	}
}

void Laadpunt::showData()
{
	std::cout << std::setw(12) << std::left << "Laadpunt:" << std::setw(12) << getNaam()
	<< std::setw(12) << std::left << "Wachtrij:" << std::setw(5) << getLength()
	<< std::setw(12) << std::left << "Totale Wachtrij:" << std::setw(5) << alleWachtrij
	<< std::setw(5) << std::left << "Gemiddelde Wachttijd:" << std::setw(5) << totaleWachtrij / 3600.00  << std::endl;
}

void Laadpunt::addAuto(Auto* newAuto)
{
	alleWachtrij++;
	std::lock_guard<std::mutex> qLockguard(queueMutex);//lock de queue
	wachtrijAuto.push(newAuto);//voeg auto toe aan de queue
}



int Laadpunt::getID()
{
	return ID;
}

int Laadpunt::getLength()
{
	return wachtrijAuto.size();
}

std::string Laadpunt::getNaam()
{
	return naam;
}

double Laadpunt::getWachtrij()
{
	return wachtrij;
}