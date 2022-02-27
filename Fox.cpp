#include<iostream>
#include<string>
#include"Fox.h"
#include"Animal.h"
Fox::Fox(int X, int Y, World* world)
	:Animal(X, Y, 3, 7, 0, 'L', world)
{
	this->countered = 0;
	this->name = "Lis";
}
void Fox::can_move(int tab[])
{
	for (int i = 0; i < 4; i++)   // zmiana konwencji:
	{                             // -1 oznacza pole na ktore lis moze sie poruszyc
		if (tab[i] == -1)          // 0 oznacza pole, na ktorym jest silniejsze zwierze
		{                           // dalej operujemy na tablicy tab[4]
			tab[i] = -1;
		}
		else
		{
			if (tab[i] != -2)
			{
				Organism* temp = this->get_Organism(tab[i]); 
				if (temp->get_str() <= this->get_str())
				{
					tab[i] = -1;
				}
				else
				{
					tab[i] = 0;
				}
				temp = nullptr;
				delete temp;
			}
			else
			{
				tab[i] = -2;
			}
		}
	}
}
void Fox::action()
{
	int* tab = new int[4];
	for (int i = 0; i < 4; i++)
	{
		tab[i] = -1;
	}
	check_neighbourhood(tab);
	can_move(tab);
	if (tab[0] == -1 || tab[1] == -1 || tab[2] == -1 || tab[3] == -1)
	{
		
		int X = this->get_x();
		int Y = this->get_y();
		world->clear_cell(X, Y);
		this->randomize_inempty(X, Y, tab);
		this->countered = attack_countered();
		if (this->countered == 1)
		{
			this->set_x(X);
			this->set_y(Y);
			world->set_cell(X, Y, this->get_sym());
		}
	}
	else
	{
		this->countered = 1;
	}
	delete[] tab;
}
void Fox::reproduction()
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
		Fox* newborn = new Fox(X, Y, world);
		world->add(newborn);
	}
	delete[] tab;
}
Fox::~Fox()
{

}
