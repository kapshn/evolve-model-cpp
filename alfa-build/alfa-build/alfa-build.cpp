// alfa-build.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "Plot.h"
#include <ctime>
#include <cstdlib>

int main()
{
	srand(time(0));
	Plot game(7);
	game.nextGen();
}

