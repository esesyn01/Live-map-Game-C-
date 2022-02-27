#include<iostream>
#include<string>
#include"Turtle.h"
#include"Animal.h"
Turtle::Turtle(int X, int Y, World* world)
	:Animal(X, Y, 2, 1, 0, 'Z', world)
{
	countered = 0;
	this->name = "Zolw";
}
void Turtle::action()
{
	int m = rand() % 4;
	if (m == 3)
	{
		int* tab = new int[4];
		for (int i = 0; i < 4; i++)
		{
			tab[i] = -1;
		}
		check_neighbourhood(tab);
		if (tab[0] != -2 || tab[1] != -2 || tab[2] != -2 || tab[3] != -2)
		{
			int X = this->get_x();
			int Y = this->get_y();
			world->clear_cell(X, Y);
			this->randomize_move(X, Y, tab);
		}
		delete[] tab;
	}
	else
	{
		this->countered = 1;
	}
}
void Turtle::reproduction()
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
		Turtle* newborn = new Turtle(X, Y, world);
		world->add(newborn); 
	}
}
Turtle::~Turtle()
{

}
