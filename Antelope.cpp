#include<iostream>
#include<string>
#include"Antelope.h"
#include"Animal.h"
Antelope::Antelope(int X, int Y, World* world)
	:Animal(X, Y, 4, 4, 0, 'A', world)
{
	this->countered = 0;
	this->name = "Antylopa";
}
void Antelope::reproduction()
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
		Antelope* newborn = new Antelope(X, Y, world);
		world->add(newborn);
	}
	delete[] tab;
}
void Antelope::action()
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
		this->countered = attack_countered();
		if (this->countered == 1)
		{
			this->set_x(X);
			this->set_y(Y);
			world->set_cell(X,Y,this->get_sym());
		}
		X = this->get_x();
		Y = this->get_y();
		check_neighbourhood(tab);
		this->randomize_move(X, Y, tab);
		this->countered = attack_countered();
		if (this->countered == 1)
		{
			this->set_x(X);
			this->set_y(Y);
			world->set_cell(X, Y, this->get_sym());
		}
	}
	delete[] tab;
}
