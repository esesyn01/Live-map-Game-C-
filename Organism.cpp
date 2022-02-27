#include<iostream>
#include<string>
#include"Organism.h"
using namespace std;
Organism::Organism(int X, int Y, int str, int init, int Age, char sym, World* WOrld)
	:x(X), y(Y), strength(str), initiative(init), age(Age), symbol(sym),world(WOrld)
{}
int Organism::get_age() const
{
	return this->age;
}
int Organism::get_x() const
{
	return this->x;
}
int Organism::get_y() const
{
	return this->y;
}
int Organism::get_str() const
{
	return this->strength;
}
int Organism::get_init() const
{
	return this->initiative;
}
char Organism::get_sym() const
{
	return this->symbol;
}
string Organism::get_name()
{
	return this->name;
}
void Organism::set_age(int age)
{
	this->age = age;
}
void Organism::set_x(int x)
{
	this->x = x;
}
void Organism::set_y(int y)
{
	this->y = y;
}
void Organism::set_str(int str)
{
	this->strength = str;
}	
void Organism::set_init(int init)
{
	this->initiative = init;
}
void Organism::set_sym(char sym)
{
	this->symbol = sym;
}
int Organism::which_class(char s)  // ustalenie klasy organizmu z uzyciem enuma
{
	return s == 'H' ? HUMAN :
		s == 'O' ? SHEEP :
		s == 'W' ? WOLF :
		s == 'Z' ? TURTLE :
		s == 'L' ? FOX :
		s == 'A' ? ANTELOPE :
		s == 'G' ? GUARANA :
		s == 'g' ? GRASS :
		s == 'h' ? HOGWEED :
		s == 'B' ? BERRY :
		s == 'D' ? DANDELION :
		EMPTY;
}
void Organism::draw()
{
	cout << this->get_sym();
}
bool Organism::down_bound()   // sprawdzanie, czy badane pole nie jest granica swiata
{
	if (y == WORLD_HEIGHT - 1) return 1;
	return 0;
}
bool Organism::upper_bound()
{
	if (y == 0) return 1;
	return 0;
}
bool Organism::left_bound()
{
	if (x == 0) return 1;
	return 0;
}
bool Organism::right_bound()
{
	if (x == WORLD_WIDTH - 1) return 1;
	return 0;
}
void Organism::eat(Organism** anim)
{

}
void Organism::randomize_move(int X, int Y,int tab[]) // losowy kierunek do poruszania sie
{
	int r = rand() % 4;
	while (tab[r] == -2)  // -2 oznacza border, patrz check_neighbourhood()
	{
		r = rand() % 4;
	}
	switch (r)
	{
	case 0:
		this->set_x(X - 1);
		break;
	case 1:
		this->set_x(X + 1);
		break;
	case 2:
		this->set_y(Y - 1);
		break;
	case 3:
		this->set_y(Y + 1);
		break;
	}
}
void Organism::randomize_inempty(int X, int Y, int tab[]) // losowe wolne pole 
{
	int r = rand() % 4;
	while (tab[r] != -1) // - 1 oznacza wolne pole, patrz check_neighbourhood()
	{
		r = rand() % 4;
	}
	switch (r)
	{
	case 0:
		this->set_x(X - 1);
		break;
	case 1:
		this->set_x(X + 1);
		break;
	case 2:
		this->set_y(Y - 1);
		break;
	case 3:
		this->set_y(Y + 1);
		break;
	}
}
void Organism::randomize_rep(int* X, int* Y, int tab[]) // losowe wolne pole dla nowego organizmu
{
	int r = rand() % 4;
	while (tab[r] != -1)
	{
		r = rand() % 4;
	}
	int temp1 = *X;
	int temp2 = *Y;
	switch (r)
	{
	case 0:
		temp1--;
		break;
	case 1:
		temp1++;
		break;
	case 2:
		temp2--;
		break;
	case 3:
		temp2++;
		break;
	}
	*X = temp1;
	*Y = temp2;
}
bool Organism::flee()
{
	return false;
}
int Organism::search(int X, int Y) // wyszukanie organizmu po jego koordynatach
{
	for (int i = 0; i < world->tab_by_pos.size(); i++)
	{
		if (world->tab_by_pos[i]->get_x() == X && world->tab_by_pos[i]->get_y() == Y)
		{
			return i;
		}
	}
}
int Organism::search(int X, int Y,char op) // wyszukanie organizmu po jego koordynatach i znaku
{
	for (int i = 0; i < world->tab_by_pos.size(); i++)
	{
		if (world->tab_by_pos[i]->get_x() == X && world->tab_by_pos[i]->get_y() == Y && world->tab_by_pos[i]->get_sym()==op)
		{
			return i;
		}
	}
}
Organism* Organism::get_Organism(int i)
{
	return world->tab_by_pos[i];
}
void Organism::check_neighbourhood(int tab[])  // funckja sprawdzajaca sasiedztwo aktualnie odwiedzonego pola
{                                             // operuje na tablicy tab o rozmiarze 4
	char neighbour;                             // tab[0] - oznacza pole sasiednie po lewej
	int neighbour_class;                         // tab[1] - oznacza pole sasiednie po prawej
	if (!left_bound())                             // tab[2] - oznacza pole sasiednie u gory
	{                                               // tab[3] - oznacza pole sasiednie na dole
		neighbour = world->board[y][x - 1];           // Wartosci zwracane dla pol:
		neighbour_class = which_class(neighbour);       // -2 - pole nie istnieje(znajdujemy sie na granicy swiata)
		if (neighbour_class != EMPTY)                    // -1 - pole jest wolne
		{                                                // 0,1,2... - indeks organizmu znajdujacego sie na badanym polu
			tab[0]=search(x - 1, y);
		}
	}
	else
	{
		tab[0] = -2;
	}
	if (!right_bound())
	{
		neighbour = world->board[y][x + 1];
		neighbour_class = which_class(neighbour);
		if (neighbour_class != EMPTY)
		{
			tab[1]=search(x + 1, y);
		}
	}
	else
	{
		tab[1] = -2;
	}
	if (!upper_bound())
	{
		neighbour = world->board[y - 1][x];
		neighbour_class = which_class(neighbour);
		if (neighbour_class != EMPTY)
		{
			tab[2]=search(x, y-1);

		}
	}
	else
	{
		tab[2] = -2;
	}
	if (!down_bound())
	{
		neighbour = world->board[y + 1][x];
		neighbour_class = which_class(neighbour);
		if (neighbour_class != EMPTY)
		{
			tab[3]=search(x, y+1);
		}
	}
	else
	{
		tab[3] = -2;
	}
}
void Organism::aging()
{
	this->age++;
}
void Organism::die(Organism** organism) // funkcja obslugujaca smierc organizmu
{
	(*organism)->set_sym(' ');
	(*organism)->set_init(-1);   // oflagowanie organizmu jako zmatly i czyszczenie go z planszy
	(*organism)->world->clear_cell((*organism)->get_x(), (*organism)->get_y());
	world->add_comment((*organism)->get_name() + " zginal ");
}
void Organism::battle(Organism** first, Organism** second)  // funkcja obsugujaca walke 2 zwierzat
{
	world->add_comment((*first)->get_name() + " walczy z " + (*second)->get_name());
	if ((*first)->get_str() > (*second)->get_str())   // symbol silniejszego zwierzecia zostaje na planszy, drugie umiera
	{
		world->board[y][x] = (*first)->get_sym();
		die(second);
	}
	else
	{
		if ((*first)->get_str() < (*second)->get_str())
		{
			world->board[y][x] = (*second)->get_sym();
			die(first);
		}
		else                           // losowe ustawienie 2 zwierzecia w przypadku 2 zwierzat innych gatunkow o jednakowej sile
		{
			int* tab = new int[4];
			check_neighbourhood(tab);
			if (tab[0] != -2 && tab[1] != -2 && tab[2] != -2 && tab[3] != -2)
			{
				int r = rand() % 4;
				switch (r)
				{
				case 0:
					(*first)->set_x((*first)->get_x() - 1);
					break;
				case 1:
					(*first)->set_x((*first)->get_x() + 1);
					break;
				case 2:
					(*first)->set_y((*first)->get_y() - 1);
					break;
				case 3:
					(*first)->set_y((*first)->get_y() + 1);
					break;
				}
				(*first)->collision();
			}
		}
	}
}