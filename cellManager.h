#ifndef CELLMANAGER_H
#define CELLMANAGER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "graph.h"
#include "cell.h"
#include "ctime"
#include <unistd.h>
#include <algorithm>
#include <random>
#include <chrono>

typedef struct cordniates
{
int x, y;
}cords;

class cellManager
{
	public:
		
		cellManager(int size);
		void init_cells(int firstClick, int size);
		void draw_assets(sf::RenderWindow &window);
		void check_cell(int index, char type);
		void start_break(int index, std::vector<int> &seen);
		bool get_game_state();
		void draw_bomb(sf::RenderWindow &window);
		void break_block(int index);
		int check_index(int nx, int ny, int size);
		cords get_cords(int index, int size);
		void show_bombs(sf::RenderWindow &window);

	private:

		graph* connect;
		std::vector<cell*> store;
		bool gameOver;
		int bombIndex;

};

#endif
