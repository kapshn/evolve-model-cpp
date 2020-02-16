#include "pch.h"
#include "Plot.h"
#include <iostream>
#include "ConsoleColor.h"
//#include <Windows.h>

using namespace std;


int Plot::getNeighbours(int posX, int posY)
{
	int neighbours = 0;
	for (int i = posX - 1; i < posX + 2; i++){
		for (int j = posY - 1; j < posY + 2; j++) {
			if (i > 0 && i < spaceX && j>0 && j < spaceY && plotCopy[i][j].getState()>0) neighbours++;
		}
	}
	neighbours -= plotCopy[posX][posY].getState() > 0 ? 1 : 0;
	return neighbours > 0 ? neighbours : 0;
}

void Plot::copyCells()
{
	for (int i = 0; i < spaceX; i++){
		for (int j = 0; j < spaceY; j++) {
			plotCopy[i][j] = plotCells[i][j];
		}
	}
}

void Plot::plotGrow()
{
	copyCells();
	for (int i = 0; i < spaceX; i++) {
		for (int j = 0; j < spaceY; j++) {
			plotCells[i][j].growRule(getNeighbours(i, j));
		}
	}
}

void Plot::printPlot()
{
	system("cls");
	refreshPlotPrey();
	for (int i = 0; i < spaceX; i++)
	{
		for (int j = 0; j < spaceY; j++) {
			//char printChar = (char)plotCells[i][j].getState();
			//if (printChar == (char)"0") printChar = (char)".";
			//if (plotPrey[i][j] == 1) printChar = (char)"@";
			if (plotPrey[i][j] >= 0) { 
				cout << red << "@"<< white; 
			}
			else {
				if (plotCells[i][j].getState() == 0){
					cout << ".";
				}
				else { 
					if (plotCells[i][j].getState()>2) cout << green <<plotCells[i][j].getState()<<white; 
					else
					{
						cout << brown << plotCells[i][j].getState() << white;
					}
				}
			}
			
			//cout << printChar;
		}
		cout << endl;

	}
	cout << endl;
	for (int i = 0; i < preyCount; i++)
	{
		cout << "Prey " << i << ": hungry state = " << preys[i].getState()<<"   under " << plotCells[preys[i].getPosX()][preys[i].getPosY()].getState() << " (" << preys[i].getPosX() << "; " << preys[i].getPosY() << ")" <<endl;
	}
	cout << "Current step: " << currGeneration<<endl;
}

void Plot::pathFind(int currPrey)
{
	refreshPlotPrey();



	int maxHungry = hS;
	maxHungry = (int)(0.8*maxHungry);

	int preyPosX = preys[currPrey].getPosX();
	int preyPosY = preys[currPrey].getPosY();
	int nearGrassPosX = spaceX;
	int nearGrassPosY = spaceY;
	for (int i = 0; i < spaceX; i++) {
		for (int j = 0; j < spaceY; j++) {
			if ((plotCells[i][j].getState() > 2)&&(abs(nearGrassPosX) + abs(nearGrassPosY)>abs(preyPosX-i)+abs(preyPosY-j))) {
				nearGrassPosX = preyPosX - i;
				nearGrassPosY = preyPosY - j;
			}
		}
	}
	int wayX;
	int wayY;
	if (nearGrassPosX == spaceX && nearGrassPosY == spaceY) {
		wayX = 0;
		wayY = 0;
	}
	else
	{
		wayX = nearGrassPosX > 0 ? -1 : 1;
		wayY = nearGrassPosY > 0 ? -1 : 1;
		if ((abs(nearGrassPosX) > abs(nearGrassPosY)) && plotPrey[preyPosX + wayX][preyPosY] != -1) {
			wayX = 0;
		}
		if ((abs(nearGrassPosX) < abs(nearGrassPosY)) && plotPrey[preyPosX][preyPosY + wayY] != -1) {
			wayY = 0;
		}
	}
	if ((abs(nearGrassPosX) < abs(nearGrassPosY)) && wayX!=0 && wayY!=0) {
		wayX = 0;
	}
	if ((abs(nearGrassPosX) > abs(nearGrassPosY)) && wayX != 0 && wayY != 0) {
		wayY = 0;
	}
	
	if ((preys[currPrey].getState() != 0) && nearGrassPosX == 0 && nearGrassPosY == 0) {
		plotCells[preyPosX][preyPosY].eatGrass(); 
		preys[currPrey].eatGrass();
	}
	else
	{
		if ((preys[currPrey].getState() != 0) && (preys[currPrey].getState() < (maxHungry))) { 
			preys[currPrey].move(preyPosX + wayX, preyPosY + wayY); 
		}
	}
	if ((preys[currPrey].getState() != 0) && (preys[currPrey].getState() >= (maxHungry))) createOffspring(currPrey);

	preys[currPrey].getHungry(1);
	deleteDeadPrey(currPrey);



}

void Plot::refreshPlotPrey()
{
	for (int i = 0; i < spaceX; i++) {
		for (int j = 0; j < spaceY; j++) {
			plotPrey[i][j] = -1;
		}
	}
	for (int i = 0; i < preyCount; i++)
	{
		plotPrey[preys[i].getPosX()][preys[i].getPosY()] = i;
	}

}

void Plot::createOffspring(int currPrey)
{
	refreshPlotPrey();
	int preyPosX = preys[currPrey].getPosX();
	int preyPosY = preys[currPrey].getPosY();
	int nearPreyX = spaceX;
	int nearPreyY = spaceY;
	int preyPartner = -1;
	for (int i = 0; i < spaceX; i++) {
		for (int j = 0; j < spaceY; j++) {
			if ((plotPrey[i][j] > -1)&& (plotPrey[i][j] != currPrey) && (abs(nearPreyX) + abs(nearPreyY) > abs(preyPosX - i) + abs(preyPosY - j))) {
				nearPreyX = preyPosX - i;
				nearPreyY = preyPosY - j;
				preyPartner = plotPrey[i][j];
			}
		}
	}
	int halfHungry=hS;
	halfHungry = (int)(0.5*halfHungry);
	if (preyPartner != -1) {
		if (abs(nearPreyX) + abs(nearPreyY) == 1 && preys[preyPartner].getState() > halfHungry) {
			preyCount++;
			Prey *tmpPreys;
			tmpPreys = new Prey[preyCount - 1];
			for (int i = 0; i < preyCount - 1; i++)
			{
				tmpPreys[i] = preys[i];
			}
			delete[] preys;
			preys = new Prey[preyCount];
			for (int i = 0; i < preyCount - 1; i++)
			{
				preys[i] = tmpPreys[i];
			}
			delete[] tmpPreys;
			if (preyPosX < spaceX && plotPrey[preyPosX + 1][preyPosY] == -1) {
				preys[preyCount - 1].move(preyPosX + 1, preyPosY);
			}
			else
			{
				if (preyPosX > 0 && plotPrey[preyPosX - 1][preyPosY] == -1) preys[preyCount - 1].move(preyPosX - 1, preyPosY);
			}
			if (preyPosY < spaceY && plotPrey[preyPosX][preyPosY + 1] == -1) {
				preys[preyCount - 1].move(preyPosX, preyPosY + 1);
			}
			else
			{
				if (preyPosY > 0 && plotPrey[preyPosX][preyPosY - 1] == -1) preys[preyCount - 1].move(preyPosX, preyPosY - 1);
			}
			halfHungry = hS;
			halfHungry = (int)(0.3*halfHungry);
			preys[currPrey].getHungry(halfHungry);
			preys[preyPartner].getHungry(halfHungry);
			preys[preyCount - 1].getHungry(halfHungry);
		}
	}
}

void Plot::deleteDeadPrey(int currPrey)
{
	if (preys[currPrey].getState() == 0) {
		Prey *tmpPreys;
		tmpPreys = new Prey[preyCount];
		for (int i = 0; i < currPrey; i++)
		{
			tmpPreys[i] = preys[i];
		}
		for (int i = currPrey + 1; i < preyCount; i++)
		{
			tmpPreys[i-1] = preys[i];
		}
		delete[] preys;
		preyCount--;
		preys = new Prey[preyCount];
		for (int i = 0; i < preyCount; i++)
		{
			preys[i] = tmpPreys[i];
		}
		delete[] tmpPreys;
	}
}

Plot::Plot(int countOfPrey)
{
	preyCount = countOfPrey;
	preys = new Prey[preyCount];
	for (int i = 0; i < preyCount; i++)
	{
		preys[i].setPos(spaceX, spaceY);
	}
	currGeneration = 0;
}

Plot::~Plot()
{
}

void Plot::nextGen()
{
	while (1) {
		
		plotGrow();
		currGeneration++;
		for (int i = 0; i < preyCount; i++)
		{
			pathFind(i);
		}
		printPlot();
		Sleep(10);
		//cin.get();
	
	}
}
