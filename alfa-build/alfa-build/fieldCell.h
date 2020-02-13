#pragma once
#define cd 100

class FieldCell
{
	int currState;
	int cooldown = cd;

public:
	void growRule(int neighbours);
	int getState();
	void eatGrass();
	
	FieldCell();
	~FieldCell();
};

