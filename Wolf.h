#pragma once
#include<iostream>
#include<string>
#include"Animal.h"
class World;
class Wolf : public Animal
{
public:
	Wolf(int X, int Y, World* world);
	void reproduction() override;
	~Wolf();
};

