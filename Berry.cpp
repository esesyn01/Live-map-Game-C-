#include<iostream>
#include<string>
#include"Berry.h"
Berry::Berry(int X, int Y, World* world) :
	Plant(X, Y, 99, 0, 0, 'B', world)
{
	this->name = "Wilcze jagody";
}
void Berry::action()
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
				Berry* newborn = new Berry(X, Y, world);
				world->add(newborn);
				world->add_comment("Wilcze jagody rozmnaza sie");
			}
		}
	}
	delete[] tab;
}
Berry::~Berry()
{

}