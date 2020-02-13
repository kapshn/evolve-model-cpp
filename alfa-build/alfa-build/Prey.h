#pragma once
#define hS 80;
class Prey
{
	int hungryState;
	int currPosX;
	int currPosY;

	
public:
	void move(int wayX, int wayY);
	void getHungry(int state);
	int getPosX();
	int getPosY();
	int getState();
	void eatGrass();
	Prey();
	void setPos(int spaceX, int spaceY);
	~Prey();
};

