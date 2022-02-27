#include<iostream>
#include<string>
#include"Human.h"
class World;
Human::Human(int X, int Y, World* World)
	:Animal(X,Y,5,4,0,'H',World)
{
	cooldown = 0;
	countered = 0;
	this->name = "Czlowiek";
}
void Human::reproduction()
{

}
void Human::action()
{
	start_spell();
	int factor = 1;
	if (cooldown > 7)
	{
		factor++;
	}
	else
	{
		if (cooldown > 4)
		{
			int r = rand() % 2;
			factor += r;
		}
	}
	int command = this->world->get_cmd();
	int* tab = new int[4];
	int X = this->get_x();
	int Y = this->get_y();
	int tempx = X;
	int tempy = Y;
	this->world->clear_cell(X, Y);
	check_neighbourhood(tab);
	switch (command)
	{
	case 0:
		if (tab[0] != -2)
		{
			X -= factor;
		}
		break;
	case 1:
		if (tab[1] != -2)
		{
			X += factor;
		}
		break;
	case 2:
		if (tab[2] != -2)
		{
			Y -= factor;
		}
		break;
	case 3:
		if (tab[3] != -2)
		{
			Y += factor;
		}
		break;
	}
	if (X < 0 || X >= WORLD_WIDTH)
	{
		X = tempx;
	}
	if (Y < 0 || Y >= WORLD_HEIGHT)
	{
		Y = tempy;
	}
	this->set_x(X);
	this->set_y(Y);
	if (cooldown > 0)
	{
		cooldown--;
	}
	delete[] tab;
}
void Human::start_spell()
{
	if (this->world->get_special() == 1)
	{
		if (cooldown > 0)
		{
			cout << "Umiejetnosc odnowi sie za: " << cooldown << " rund\n";
		}
		else
		{
			cout << "Uzyto umiejetnosci\n";
			cooldown = 10;
		}
	}
}
Human::~Human()
{

}