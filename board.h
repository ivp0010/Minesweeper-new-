#ifndef BOARD_H
#define BOARD_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class board
{
	public:
		
		board(int size);
		sf::RectangleShape* get_board(int x);
		int get_size();

	private:
		
		std::vector<sf::RectangleShape*> grid;
		int size;

};

#endif
