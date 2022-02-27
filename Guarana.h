#pragma once
#include<iostream>
#include<string>
#include"Plant.h"
class World;
class Guarana : public Plant
{
public:
	Guarana(int X, int Y, World* world);
	void action() override;
	~Guarana();
};