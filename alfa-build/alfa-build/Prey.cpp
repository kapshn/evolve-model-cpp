#include "pch.h"
#include "Prey.h"
#include <cstdlib>



void Prey::eatGrass()
{
	hungryState += 3;
	int check = hS;
	hungryState = hungryState > check ? check : hungryState;
}

void Prey::move(int wayX, int wayY)
{
	currPosX = wayX;
	currPosY = wayY;
}

void Prey::getHungry(int state)
{
	hungryState-=state;
	hungryState = hungryState > 0 ? hungryState : 0;
}

int Prey::getPosX()
{
	return currPosX;
}

int Prey::getPosY()
{
	return currPosY;
}

int Prey::getState()
{
	return hungryState;
}

Prey::Prey()
{
	int check = hS;
	check = (int)(0.8*check);
	hungryState = check;
	currPosX = NULL;
	currPosY = NULL;
}

void Prey::setPos(int spaceX, int spaceY)
{
	//hungryState = hS;
	int check = hS;
	check = (int)(0.8*check);
	hungryState = check;
	currPosX = rand() % spaceX;
	currPosY = rand() % spaceY;
}


Prey::~Prey()
{
}
