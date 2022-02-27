#include<iostream>
#include<string>
#include"Plant.h"
using namespace std;
Plant::Plant(int X, int Y, int str, int init, int Age, char sym, World* world)
	:Organism(X, Y, str, init, Age, sym, world)
{

}
void Plant::action()  
{
	
}
void Plant::collision()
{

}
void Plant::eat(Organism** anim) // funkcja obslugujaca jedzenie roslin
{
	char me = this->get_sym();
	char op = (*anim)->get_sym();
	int X = this->get_x();
	int Y = this->get_y();
	Organism* temp = this;    // rozne dzialania w zaleznosci od gatunku rosliny
	if (me == 'G')
	{
		int s = (*anim)->get_str();
		(*anim)->set_str(s + 3);
		die(&temp);
		world->board[Y][X] = op;
	}
	if (me == 'h' || me == 'B')
	{
		die(anim);
		die(&temp);
		world->board[Y][X] = ' ';
	}
	if (me == 'g' || me == 'D')
	{
		die(&temp);
		world->board[Y][X] = op;
	}
	temp = nullptr;
	delete temp;
}
