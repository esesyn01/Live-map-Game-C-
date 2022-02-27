#pragma once
#include<iostream>
#include<string>
#include"Animal.h"
class World;
class Fox : public Animal
{
public:
	Fox(int X, int Y, World* world);
	void action() override;
	void reproduction() override;
	void can_move(int tab[]);
	~Fox();
};

