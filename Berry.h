#pragma once
#include<iostream>
#include<string>
#include"Plant.h"
class World;
class Berry : public Plant
{
public:
	Berry(int X, int Y, World* world);
	void action() override;
	~Berry();
};