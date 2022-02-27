#pragma once
#include<iostream>
#include<string>
using namespace std;
enum {    // typ enum pomocny w kilku funkcjach do ustalenia typu organizmu
	HUMAN,
	SHEEP,
	WOLF,
	FOX,
	TURTLE,
	ANTELOPE,
	HOGWEED,
	DANDELION,
	GRASS,
	BERRY,
	GUARANA,
	EMPTY
};
class World;
class Organism 
{
protected:
	int x, y;
	int strength;
	int initiative;
	int age;
	char symbol;
	World* world;
	string name;
	Organism(int X, int Y, int str, int init, int Age, char sym, World* world);
public:
	virtual void action() = 0;
	virtual void collision() = 0;
	void draw();
	virtual void eat(Organism** anim);
	virtual bool flee();
	int get_x() const;
	void set_x(int x);
	int get_y() const;
	void set_y(int y);
	int get_str() const;
	void set_str(int str);
	int get_init() const;
	void set_init(int init);
	int get_age() const;
	void set_age(int age);
	char get_sym() const;
	void set_sym(char sym);
	string get_name();
	int which_class(char s);
	void aging();
	bool left_bound();
	bool right_bound();
	bool upper_bound();
	bool down_bound();
	int search(int X, int Y);
	int search(int X, int Y, char op);
	Organism* get_Organism(int i);
	void check_neighbourhood(int tab[]);
	void randomize_move(int X, int Y, int tab[]);
	void randomize_inempty(int X, int Y, int tab[]);
	void randomize_rep(int* X, int* Y, int tab[]);
	void battle(Organism** first, Organism** second);
	void die(Organism** organism);
};
#include"World.h"