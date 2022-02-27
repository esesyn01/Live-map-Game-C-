#include<iostream>
#include<string>
#include "World.h"
#include "Organism.h"
#include "Animal.h"
#include"Sheep.h"
using namespace std;
int main()
{
	World swiat;
	swiat.initialize();
	cout << "Nacisnij klawisz 'T' na klawiaturze, aby wczytac stan swiata z pliku, w innym przypadku zostanie zainicjowany swiat domyslny\n";
	char c;
	cin >> c;
	if (c == 't' || c == 'T')
	{
		swiat.load();
	}
	else
	{
		swiat.start_world();
	}
	swiat.drawWorld();
	bool q = 0;
	while(!q)
	{
		swiat.turn_all();
		cout << "\n";
		cout << "\n";
		cout << "\n";
		swiat.drawWorld();
		swiat.view_comment();
		q = swiat.get_end();
	}
	return 0;
}