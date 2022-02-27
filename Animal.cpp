#include<iostream>
#include<string>
#include"Animal.h"
using namespace std;
Animal::Animal(int X, int Y, int str, int init, int Age, char sym, World* world)
	:Organism(X,Y,str,init,Age,sym,world)
{
	countered = 0;  // zmiena ktora okresla czy zwierze powinno wrocic na pole poprzednie
}
bool Animal::attack_countered() // funkcja sprawdzajaca odbicie ataku
{
	int X = this->get_x();
	int Y = this->get_y();
	int str = this->get_str();
	char op = world->board[Y][X];
	if (op == 'Z')
	{
		if (str < 5) return true;
	}
	return false;
}
bool Animal::flee() // funkcja dla antylopy, w ktorej ma mozliwosc ucieczki z pola walki
{
	int r = rand() % 2;
	if (r == 1)
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
			this->randomize_inempty(X,Y,tab);
			this->world->set_cell(this->get_x(), this->get_y(), 'A');
			this->world->add_comment("Antylopa uciekla");
			delete[] tab;
			return true;
		}
		delete[] tab;
		return false;
	}
	return false;
}
void Animal::collision() // metoda kolizji dla zwierzat
{
	if (this->countered == 1)
	{
		this->countered = 0;
		return;
	}
	int X = this->get_x();
	int Y = this->get_y();
	char s = this->get_sym();
	char op = world->board[Y][X];
	int my_class = this->which_class(s);
	int opponent_class = which_class(op);
	if (opponent_class != EMPTY)
	{
		if (my_class == opponent_class)  // klasy sa te same, wiec dochodzi do rozmnazania
		{
			int* tab = new int[4];
			for (int i = 0; i < 4; i++)
			{
				tab[i] = -1;
			}
			check_neighbourhood(tab);
			if (tab[0] != -2 || tab[1] != -2 || tab[2] != -2 || tab[3] != -2)
			{
				this->randomize_move(X,Y,tab);
			}
			delete[] tab;
			this->collision();
			this->world->add_comment(this->get_name() + " rozmnaza sie");
			reproduction();
		}
		else
		{
			Organism* first = this;
			Organism* second;
			second = world->tab_by_pos[search(X, Y,op)];
			if (opponent_class < ANTELOPE) // klasa od czlowieka do wszystkich zwierzat poza antylopa, zwykla walka
			{
				battle(&first, &second);
				if ((*first).get_init() >= 0)
				{
					world->board[Y][X] = (*first).get_sym();
				}
				else
				{
					world->board[Y][X] = (*second).get_sym();
				}
			}
			else
			{
				if (opponent_class == ANTELOPE) // wywolanie molziwosci ucieczki antylopy
				{
					bool f = second->flee();
					if (!f)
					{
						battle(&first, &second);
						if ((*first).get_init() >= 0)
						{
							world->board[Y][X] = (*first).get_sym();
						}
						else
						{
							world->board[Y][X] = (*second).get_sym();
						}
					}
					else
					{
						world->board[Y][X] = (*first).get_sym();
					}
				}
				else  // sytuacja napotkania rosliny, jedzenie rosliny
				{
					second->eat(&first);
				}
			}
			first = nullptr;
			second = nullptr;
			delete first;
			delete second;
		}
	}
	else // puste pole 
	{
		world->board[Y][X] = this->get_sym();
	}
}
void Animal::action()
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
		if (this->countered == 1) // sprawdzenie czy zowl odbil atak
		{
			this->set_x(X);
			this->set_y(Y);
			world->board[Y][X] = this->get_sym();
			this->world->add_comment("Zolw odbija atak");
		}
	}
	delete[] tab;
}
