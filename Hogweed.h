#pragma once
#include<iostream>
#include<string>
#include"Plant.h"
class World;
class Hogweed : public Plant
{
public:
	Hogweed(int X, int Y, World* world);
	void action() override;
	~Hogweed();
};