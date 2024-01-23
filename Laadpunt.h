#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "ClockListener.h"
#include <queue>
#include <mutex>

class Auto;

class Laadpunt : public ClockListener
{
public:
	Laadpunt();
	virtual ~Laadpunt();

	void createLaadpunt(int locatie, std::string naam, int ID);
	void showLaadpunt();
	void singleAction(volatile unsigned int) override;
	void addAuto(Auto* newAuto);
	int getID();
	int getLength();
	void showData();
	std::string getNaam();
	double getWachtrij();

private:
	std::string naam;
	std::queue<Auto*> wachtrijAuto;
	std::mutex queueMutex;
	int locatie;
	bool beschikbaar;
	double wachtrij;
	double totaleWachtrij;
	int alleWachtrij;
	int oplaadTijd;
	int ID;
	


};