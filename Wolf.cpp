#include<iostream>
#include<string>
#include"Wolf.h"
#include"Animal.h"
Wolf::Wolf(int X, int Y, World* world)
	:Animal(X, Y, 9, 5, 0, 'W', world)
{
	countered = 0;
	this->name = "Wilk";
}
void Wolf::reproduction()
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
		Wolf* newborn = new Wolf(X, Y, world);
		world->add(newborn);
	}
	delete[] tab;
}
Wolf::~Wolf()
{

}
