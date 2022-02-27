#pragma once
#include<iostream>
#include<string>
#include"Animal.h"
class World;
class Antelope : public Animal
{
public:
	Antelope(int X, int Y, World* world);
	void reproduction() override;
	void action() override;
	~Antelope()
	{

	}
};
