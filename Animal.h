#pragma once
#include<iostream>
#include<string>
#include "Organism.h"
class World;
class Animal : public Organism
{
protected:
	bool countered = 0;
	Animal(int X, int Y, int str, int init, int Age, char sym, World* world);
public:
	void action();
	void collision();
	virtual void reproduction() = 0;
	bool attack_countered();
	bool flee();
};
