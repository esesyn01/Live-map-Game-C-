#pragma once
#include<iostream>
#include<string>
#include"Plant.h"
class World;
class Grass : public Plant
{
	public:
		Grass(int X, int Y, World* world);
		void action() override;
		~Grass();
};