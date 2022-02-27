#pragma once
#include<iostream>
#include<string>
#include"Animal.h"
class Human :public Animal
{
	bool countered;
	int cooldown;
public:
	Human(int X, int Y, World* World);
	void action() override;
	void start_spell();
	void reproduction();
	~Human();
};
