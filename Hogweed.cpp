#include<iostream>
#include<string>
#include"Hogweed.h"
Hogweed::Hogweed(int X, int Y, World* world) :
	Plant(X, Y, 10, 0, 0, 'h', world)
{
	this->name = "Barszcz sosnowskiego";
}
void Hogweed::action()
{
	int* tab = new int[4];
	for (int i = 0; i < 4; i++)
	{
		tab[i] = -1;
	}
	check_neighbourhood(tab);
	for (int i = 0; i < 4; i++)
	{
		if (tab[i] >= 0)
		{
			Organism* temp = this->get_Organism(tab[i]);
			char s = temp->get_sym();
			int c = which_class(s);
			if (c <= ANTELOPE)
			{
				die(&temp);
				tab[i] = -1;
			}
			temp = nullptr;
			delete temp;
		}
	}
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
				Hogweed* newborn = new Hogweed(X, Y, world);
				world->add(newborn);
				world->add_comment("Barszcz sosnowskiego rozmnaza sie");
			}
		}
	}
	delete[] tab;
}
Hogweed::~Hogweed()
{

}