#pragma once
#include<iostream>
#include<string>
#include"Animal.h"
class World;
class Turtle : public Animal
{
public:
	Turtle(int X, int Y, World* world);
	void action() override;
	void reproduction() override;
	~Turtle();
};

