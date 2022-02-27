#pragma once
#include<iostream>
#include<string>
#include"Organism.h"
using namespace std;
class Plant : public Organism
{
protected:
	Plant(int X, int Y, int str, int init, int Age, char sym, World* world);
public:
	void action() override;
	void collision() override;
	void eat(Organism** anim) override;
};