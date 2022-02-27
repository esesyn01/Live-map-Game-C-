#include<iostream>
#include<string>
#include"Sheep.h"
#include"Animal.h"
Sheep::Sheep(int X, int Y, World* world)
	:Animal(X, Y, 4, 4, 0, 'O', world)
{
	countered = 0;
	this->name = "Owca";
}
void Sheep::reproduction()
{
	int* tab = new int[4];
	for (int i = 0; i < 4; i++)
	{
		tab[i] = -1;
	}
	check_neighbourhood(tab);
	if (tab[0] == -1 || tab[1] == -1 || tab[2] == -1 || tab[3] == -1)
	{
		int X = this->get_x();
		int Y = this->get_y();
		this->randomize_rep(&X, &Y, tab);
		Sheep* newborn = new Sheep(X, Y, world);
		world->add(newborn);
	}
	delete[] tab;
}