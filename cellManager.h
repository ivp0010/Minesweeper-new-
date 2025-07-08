#ifndef CELLMANAGER_H
#define CELLMANAGER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "graph.h"
#include "cell.h"

typedef struct cordniates
{
int x, y;
}cords;

class cellManager
{
	public:
		
		cellManager(int size);
		void draw_assets(sf::RenderWindow &window);
		void check_cell(int index, char type);
		void start_break(int index, std::vector<int> &seen);
		void set_flag(int index);
		bool get_game_state();
		void draw_bomb(int index, sf::RenderWindow &window);
		void break_block(int index);
		int check_index(int nx, int ny, int size);
		cords get_cords(int index, int size);

	private:

		graph* connect;
		std::vector<cell*> store;
		bool gameOver;

};

#endif
