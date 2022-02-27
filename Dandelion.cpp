#include<iostream>
#include<string>
#include"Dandelion.h"
Dandelion::Dandelion(int X, int Y, World* world) :
	Plant(X, Y, 0, 0, 0, 'D', world)
{
	this->name = "Mlecz";
}
void Dandelion::action()
{
	for (int k = 0; k < 3; k++)
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
			int r = rand() % 4;
			if (r == 1)
			{
				r = rand() % 2;
				if (r == 1)
				{
					this->randomize_rep(&X, &Y, tab);
					Dandelion* newborn = new Dandelion(X, Y, world);
					world->add(newborn);
					world->add_comment("Mlecz rozmnaza sie");
				}
			}
		}
		delete[] tab;
	}
}
Dandelion::~Dandelion()
{

}