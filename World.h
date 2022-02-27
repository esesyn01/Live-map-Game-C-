#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include"Organism.h"
#define WORLD_WIDTH 80
#define WORLD_HEIGHT 30
using namespace std;
class Organism;
class World
{
	char board[WORLD_HEIGHT][WORLD_WIDTH] = {};
	int cmd;
	bool special;
	bool end;
	vector< Organism* > tab_by_init;
	vector< Organism* > tab_by_pos;
	vector< string > comment;
public:
	World();
	void turn_all();
	void drawWorld();
	void sort_for_turn();
	void sort_for_draw();
	void start_world();
	void initialize();
	void add(Organism* newborn);
	void setsymbols();
	void clear_cell(int x, int y);
	void set_cell(int x, int y, char s);
	void add_comment(string a);
	void view_comment();
	bool get_special();
	bool get_end();
	void set_end(bool a);
	void set_special(bool a);
	void save();
	void load();
	int get_cmd();
	int command();
	~World();
	friend class Organism;
	friend class Animal;
	friend class Plant;
};
