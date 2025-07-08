#include "board.h"

board::board(int size)
{
	switch(size)
	{
		case 81:
		{
			for(unsigned int i = 1; i < 9; i++)
			{
				sf::RectangleShape* new_rect_v = new sf::RectangleShape();
				new_rect_v->setSize({1.f, 900.f});
				new_rect_v->setPosition({100.f * i, 0.f});
				new_rect_v->setFillColor(sf::Color::Black);
				sf::RectangleShape* new_rect_h = new sf::RectangleShape();
				new_rect_h->setSize({900.f, 1.f});
				new_rect_h->setPosition({0.f, 100.f * i});
				new_rect_h->setFillColor(sf::Color::Black);
				grid.push_back(new_rect_v);
				grid.push_back(new_rect_h);
			}
			this->size = grid.size();
		break;
		}
		case 256:
		{
			for(unsigned int i = 1; i < 16; i++)
			{
				sf::RectangleShape* new_rect_v = new sf::RectangleShape();
				new_rect_v->setSize({1.f, 1000.f});
				new_rect_v->setPosition({56.25f * i, 0.f});
				new_rect_v->setFillColor(sf::Color::Black);
				sf::RectangleShape* new_rect_h = new sf::RectangleShape();
				new_rect_h->setSize({1000.f, 1.f});
				new_rect_h->setPosition({0.f, 56.25f * i});
				new_rect_h->setFillColor(sf::Color::Black);
				grid.push_back(new_rect_v);
				grid.push_back(new_rect_h);
			}
			this->size = grid.size();
		break;
		}
		case 480:
		{
			for(unsigned int i = 1; i < 16; i++)
			{
				sf::RectangleShape* new_rect_h = new sf::RectangleShape();
				new_rect_h->setSize({1500.f, 1.f});
				new_rect_h->setPosition({0.f, 50.f * i});
				new_rect_h->setFillColor(sf::Color::Black);
				grid.push_back(new_rect_h);
			}

			for(unsigned int i = 1; i < 30; i++)
			{
				sf::RectangleShape* new_rect_v = new sf::RectangleShape();
				new_rect_v->setSize({1.f, 800.f});
				new_rect_v->setPosition({50.f * i, 0.f});
				new_rect_v->setFillColor(sf::Color::Black);
				grid.push_back(new_rect_v);
			}
			this->size = grid.size();
		break;
		}
	}
	
}

sf::RectangleShape* board::get_board(int x)
{
	return grid[x];
}

int board::get_size()
{
	return size;
}


