#ifndef CELL_H
#define CELL_H
#include <SFML/Graphics.hpp>
#include <iostream>

class cell
{

	public:
		
		cell(char type, int numAdjBomb);
		char get_type();
		int get_num_adj_bomb();
		bool get_to_draw();
		bool get_flag_set();
		bool get_broken();
		sf::RectangleShape get_block();

	private:
		
		char type;
		sf::Sprite sprite;
		int numAdjBomb;
		sf::RectangleShape block;
		bool broken;
		bool bombSet;
		bool toDraw;
		bool flagSet;
		sf::Font font;
		sf::Text text;
};

#endif
