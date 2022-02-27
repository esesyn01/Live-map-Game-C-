#include<iostream>
#include<vector>
#include<algorithm>
#include<conio.h>
#include<fstream>
#include"World.h"
#include"Organism.h"
#include"Sheep.h"
#include"Wolf.h"
#include"Turtle.h"
#include"Fox.h"
#include"Antelope.h"
#include"Grass.h"
#include"Guarana.h"
#include"Dandelion.h"
#include"Hogweed.h"
#include"Berry.h"
#include"Human.h"
using namespace std;
World::World()
{
	srand(time(NULL));
	special = 0;
	cmd = -1;
	end = 0;
}
void World::add(Organism* newborn)   // dodanie organizmu do zbioru organizmow
{
	tab_by_init.push_back(newborn);
	tab_by_pos.push_back(newborn);
	int X = (*newborn).get_x();
	int Y = (*newborn).get_y();
	board[Y][X] = (*newborn).get_sym();
}
void World::sort_for_turn()  // sortowanie organizmow w kolejnosci ruchu
{
	sort(tab_by_init.begin(), tab_by_init.end(), [](Organism* a, Organism* b) {
		if (a->get_init() != b->get_init())
		{
			return a->get_init() > b->get_init();
		}
		else
		{
			return a->get_age() > b->get_age();
		}
		});
}
void World::sort_for_draw()  // sortowanie organizmow w kolejnosci rysowania
{
	sort(tab_by_pos.begin(), tab_by_pos.end(), [](Organism* a, Organism* b) {
		if (a->get_y() != b->get_y())
		{
			return a->get_y() < b->get_y();
		}
		else
		{
			return a->get_x() < b->get_x();
		}
		});
}
void World::turn_all()   // wywolywanie logiki calej tury
{
	cmd = command();
	sort_for_turn();
	int g = tab_by_init.size();
	for (int i = 0; i < g; i++)
	{
		if (tab_by_init[i]->get_init() >= 0)  // obsluga kazdego organizmu
		{
			tab_by_init[i]->action();
			tab_by_init[i]->collision();
			tab_by_init[i]->aging();
		}
	}
	sort_for_turn();
	int l = tab_by_init.size() - 1;
	while (tab_by_init[l]->get_init() < 0)  // usuwanie martwych organizmow (inicjatywa ustawiona wczesniej na -1)
	{
		if (tab_by_init[l]->get_name() == "Czlowiek")
		{
			this->set_end(1);
		}
		tab_by_init[l] = nullptr;
		delete tab_by_init[l];
		tab_by_init.pop_back();
		l--;
	}
}
void World::add_comment(string a)
{
	comment.push_back(a);
}
void World::view_comment()
{
	for (int i = 0; i < comment.size(); i++)
	{
		cout << comment[i] << "\n";
	}
	comment.clear();
}
void World::clear_cell(int x, int y)
{
	board[y][x] = ' ';
}
void World::set_cell(int x, int y, char s)
{
	board[y][x] = s;
}
void World::initialize()
{
	for (int i = 0; i < WORLD_HEIGHT; i++)
	{
		for (int k = 0; k < WORLD_WIDTH; k++)
		{
			board[i][k] = ' ';
		}
	}
	sort_for_draw();
	for (int i = 0; i < tab_by_pos.size(); i++)
	{
		if (tab_by_pos[i]->get_init() >= 0)
		{
			board[tab_by_pos[i]->get_y()][tab_by_pos[i]->get_x()] = tab_by_pos[i]->get_sym();
		}
	}
}
void World::setsymbols()  // ustawienie symboli organizmow na mapie swiata dla pewnosci
{
	tab_by_pos = tab_by_init;
	sort_for_draw();
	for (int i = 0; i < tab_by_pos.size(); i++)
	{
		if (tab_by_pos[i]->get_init() >= 0)
		{
			board[tab_by_pos[i]->get_y()][tab_by_pos[i]->get_x()] = tab_by_pos[i]->get_sym();
		}
	}
}
void World::drawWorld()
{
	setsymbols();
	cout << "Wiktor Kawka 184417\n";
	for (int i = 0; i < WORLD_WIDTH + 2; i++)  // rysowanie borderu
	{
		cout << "=";
	}
	cout << "\n";
	for (int i = 0; i < WORLD_HEIGHT; i++)
	{
		cout << "|";
		for (int k = 0; k < WORLD_WIDTH; k++)  // rysowanie mapy
		{
			cout << board[i][k];
		}
		cout << "|\n";
	}
	for (int i = 0; i < WORLD_WIDTH + 2; i++)
	{
		cout << "=";
	}
	cout << "\n";
}
int World::command()  // funkcja do wczytania ruchu czlowieka lub aktywowania umiejetnosci lub zapisu
{
	while (1)
	{
		unsigned char kodzik = _getch();
		if (kodzik == 224)
		{
			switch (kodzik = _getch())
			{
			case 72:
				return 2;
				break;
			case 75:
				return 0;
				break;
			case 77:
				return 1;
				break;
			case 80:
				return 3;
				break;
			}
		}
		else
		{
			if (kodzik == 's' && special==0)
			{
				special = 1;
			}
			else
			{
				if (kodzik == 'z')
				{
					save();
					cout << "Zapisano stan gry\n";
				}
				else
				{
					cout << "Niepoprawna komenda\n";
				}
			}
		}
	}
	return -1;
}
bool World::get_special()
{
	return special;
}
int World::get_cmd()
{
	return cmd;
}
void World::set_special(bool a)
{
	this->special = a;
}
bool World::get_end()
{
	return end;
}
void World::set_end(bool a)
{
	this->end = a;
}
void World::start_world()  // defaultowe ustawienie swiata
{
	Sheep* O1 = new Sheep(5, 5, this);
	Sheep* O4 = new Sheep(6, 5, this);
	Sheep* O2 = new Sheep(2, 6, this);
	Sheep* O3 = new Sheep(12, 7, this);
	Wolf* W1 = new Wolf(4, 5, this);
	Wolf* W2 = new Wolf(40, 20, this);
	Wolf* W3 = new Wolf(32, 9, this);
	Antelope* A1 = new Antelope(5, 4, this);
	Antelope* A5 = new Antelope(7, 4, this);
	Antelope* A6 = new Antelope(1, 1, this);
	Antelope* A7 = new Antelope(57, 24, this);
	Antelope* A8 = new Antelope(34, 15, this);
	Antelope* A9 = new Antelope(28, 10, this);
	Antelope* A10 = new Antelope(19, 19, this);
	Turtle* T1 = new Turtle(16, 8,this);
	Turtle* T2 = new Turtle(67, 29, this);
	Turtle* T3 = new Turtle(2, 8, this);
	Fox* F1 = new Fox(32, 18,this);
	Fox* F2 = new Fox(56, 22, this);
	Fox* F3 = new Fox(7, 20, this);
	Fox* F4 = new Fox(22, 2, this);
	Hogweed* h1 = new Hogweed(40, 21, this);
	Hogweed* h2 = new Hogweed(4, 3, this);
	Hogweed* h3 = new Hogweed(68, 12, this);
	Dandelion* D1 = new Dandelion(45, 25,this);
	Dandelion* D2 = new Dandelion(57, 8, this);
	Dandelion* D3 = new Dandelion(14, 5, this);
	Berry* B1 = new Berry(19, 27, this);
	Berry* B2 = new Berry(2, 2, this);
	Berry* B3 = new Berry(3, 29, this);
	Grass* g1 = new Grass(75, 12, this);
	Grass* g2 = new Grass(67, 15, this);
	Grass* g3 = new Grass(42, 3, this);
	Guarana* G1 = new Guarana(13, 13, this);
	Guarana* G2 = new Guarana(24, 5, this);
	Guarana* G3 = new Guarana(11, 26, this);
	Guarana* G4 = new Guarana(48, 5, this);
	Human* H = new Human(10, 10, this);
	add(H);
	add(O1);
	add(O4);
	add(O2);
	add(O3);
	add(W1);
	add(W2);
	add(W3);
	add(A1);
	add(A5);
	add(A6);
	add(A7);
	add(A8);
	add(A9);
	add(A10);
	add(T1);
	add(T2);
	add(T3);
	add(F1);
	add(F2);
	add(F3);
	add(F4);
	add(h1);
	add(h2);
	add(h3);
	add(g1);
	add(g2);
	add(g3);
	add(G1);
	add(G2);
	add(G3);
	add(G4);
	add(B1);
	add(B2);
	add(B3);
	add(D1);
	add(D2);
	add(D3);

}
void World::save() // zapis swiata
{
	ofstream file("save.txt");
	if (file.is_open())
	{
		sort_for_turn();
		file << tab_by_init.size() << "\n";
		for (int i = 0; i < tab_by_init.size(); i++)
		{
			file << tab_by_init[i]->get_sym() << " " << tab_by_init[i]->get_x() << " " << tab_by_init[i]->get_y() << "\n";
		}
		file.close();
	}
	else
	{
		cout << "blad";
	}
}
void World::load() // wczytanie swiata
{
	ifstream file("load.txt");
	if (file.is_open())
	{
		int t;
		file >> t;
		int X, Y;
		char s;
		for (int i = 0; i < t; i++)
		{
			file >> s>>X>>Y;
			Organism* newb;
			switch (s)   // ustalenie klasy organizmu ktory nalezy stworzyc
			{
			case 'H':
				newb = new Human(X, Y, this);
				add(newb);
				break;
			case 'O':
				newb = new Sheep(X, Y, this);
				add(newb);
				break;
			case 'W':
				newb= new Wolf(X, Y, this);
				add(newb);
				break;
			case 'L':
				newb = new Fox(X, Y, this);
				add(newb);
				break;
			case 'Z':
				newb = new Turtle(X, Y, this);
				add(newb);
				break;
			case 'A':
				newb = new Antelope(X, Y, this);
				add(newb);
				break;
			case 'D':
				newb = new Dandelion(X, Y, this);
				add(newb);
				break;
			case 'G':
				newb = new Guarana(X, Y, this);
				add(newb);
				break;
			case 'g':
				newb= new Grass(X, Y, this);
				add(newb);
				break;
			case 'h':
				newb = new Hogweed(X, Y, this);
				add(newb);
				break;
			case 'B':
				newb = new Berry(X, Y, this);
				add(newb);
				break;
			default:
				break;

			}
		}
		file.close();
		setsymbols();
	}
	else
	{
		cout << "Blad";
	}
}
World::~World() // destruktor swiata i zwalnianie pamieci
{
	tab_by_init = tab_by_pos;
	int l = tab_by_init.size(); 
	while (l--)
	{
		tab_by_init[l] = nullptr;
		tab_by_pos[l] = nullptr;
		delete tab_by_init[l];
		delete tab_by_pos[l];
		tab_by_init.pop_back();
		tab_by_pos.pop_back();
	}
}