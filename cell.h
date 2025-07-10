#ifndef CELL_H
#define CELL_H
#include <SFML/Graphics.hpp>
#include <iostream>

class cell
{

	public:
		
		cell(char type);
		void init(int numAdjBomb, int index, int size);
		char get_type();
		int get_num_adj_bomb();
		bool get_to_draw();
		bool get_flag_set();
		bool get_broken();
		sf::Text get_num();
		sf::RectangleShape get_block();
		void start_break();
		void set_flag();
		sf::Sprite get_flag();
		void set_bomb();
		sf::Sprite get_bomb();
		void reveal();

	private:
		
		char type;
		int size;
		sf::Texture texture;
		sf::Sprite sprite;
		int numAdjBomb;
		sf::RectangleShape block;
		bool broken;
		bool bombSet;
		bool toDraw;
		bool flagSet;
		sf::Font font;
		sf::Text text;
		sf::Vector2f center;
		sf::FloatRect bound;
};

#endif
