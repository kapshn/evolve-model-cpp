#pragma once
#include"fieldCell.h"
#include "Prey.h"
#define spaceX 30
#define spaceY 60

class Plot
{
	FieldCell plotCells[spaceX][spaceY];
	FieldCell plotCopy[spaceX][spaceY];

	int currGeneration;

	Prey *preys;
	int preyCount;
	int plotPrey[spaceX][spaceY];

	int getNeighbours(int posX, int posY);
	void copyCells();
	void plotGrow();
	void printPlot();
	void pathFind(int currPrey);
	void refreshPlotPrey();
	void createOffspring(int currPrey);
	void deleteDeadPrey(int currPrey);
	
public:
	Plot(int countOfPrey);
	~Plot();
	void nextGen();
};

