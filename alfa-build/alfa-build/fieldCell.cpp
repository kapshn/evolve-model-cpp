#include "pch.h"
#include "fieldCell.h"
#include <cstdlib>
#include <ctime>
using namespace std;



void FieldCell::growRule(int neighbours)
{


	if (currState<9)
	{
		cooldown -= (neighbours % 3);
		if (cooldown< 1) {
			currState++;
			cooldown = cd*currState;
		}
	}
	if (currState == 0 && neighbours == 0) {
		int chanceToGrow = (rand() % 50) == 42 ? 1 : 0;
		if (chanceToGrow == 1) {
			currState++;
			cooldown = cd;
		}
	}
}

int FieldCell::getState()
{
	return currState;
}

void FieldCell::eatGrass()
{
	currState -= 3;
	cooldown = cd;
}



FieldCell::FieldCell()
{
	int randState = 1+(rand() % 30);
	for (int i = 10; i > 0; i--) {
		if ((randState > 0)) {
			randState -= i;
			if ((randState<= 0)&&(randState+i>0))
			{
				currState = 10 - i;
			}
		}
	}
}


FieldCell::~FieldCell()
{
}
