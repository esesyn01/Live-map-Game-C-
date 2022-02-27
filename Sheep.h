#pragma once
#include<iostream>
#include<string>
#include"Animal.h"
class World;
class Sheep : public Animal
{
public:
	Sheep(int X, int Y, World* world);
	void reproduction() override;
};

