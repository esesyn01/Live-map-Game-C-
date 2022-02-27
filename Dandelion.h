#pragma once
#include<iostream>
#include<string>
#include"Plant.h"
class World;
class Dandelion : public Plant
{
public:
	Dandelion(int X, int Y, World* world);
	void action() override;
	~Dandelion();
};