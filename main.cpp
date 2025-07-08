#include <SFML/Graphics.hpp>
#include <iostream>
#include "board.h"
#include "zones.h"
#include "cellManager.h"

void build_board(sf::RenderWindow &window, board &b);
int set_window_size(sf::RenderWindow &window);
int check_zones(sf::Vector2f mouse_pos, zones &z, int size);

int main()
{

	sf::RenderWindow window(sf::VideoMode(500, 900), "minesweeper", sf::Style::Resize | sf::Style::Close);
	window.clear(sf::Color::White);
	int size = set_window_size(window);
	board b(size);
	zones z(size);
	cellManager c(size);
	window.clear(sf::Color::White);
	build_board(window, b);
	window.display();
	srand(time(NULL));

	while(window.isOpen())
	{

		
		sf::Event event;
        	while (window.pollEvent(event))
        	{
        	    if (event.type == sf::Event::Closed)
        	        window.close();
        	}


		if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 

		{
			sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			int pos = check_zones(mousePos, z, size);
			std::cout << pos << std::endl;
		}
		/*
		else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
		{
			sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));			
			int pos = checkZones(mousePos, z);
			s.checkCell(pos, 'r');
		}
		
		if(!first)
		{
			if(s.getGameState()){break;}
			window.clear(sf::Color::White);
			drawBoard(window, b);
			s.drawAssets(window);
			window.display();
		}*/
	}


return 0;
}

void build_board(sf::RenderWindow &window, board &b)
{
	for(unsigned int i = 0; i < b.get_size(); i++)
	{
		window.draw(*(b.get_board(i)));
		std::cout << b.get_board(i)->getPosition().x << ", " << b.get_board(i)->getPosition().y << std::endl;
	}
}

int set_window_size(sf::RenderWindow &window)
{
	sf::RectangleShape* small = new sf::RectangleShape();
	sf::RectangleShape* med = new sf::RectangleShape();
	sf::RectangleShape* large = new sf::RectangleShape();
	sf::FloatRect* box_S = new sf::FloatRect(200.f, 200.f, 200.f, 150.f);
	sf::FloatRect* box_M = new sf::FloatRect(200.f, 400.f, 200.f, 150.f);
	sf::FloatRect* box_L = new sf::FloatRect(200.f, 600.f, 200.f, 150.f);
	small->setSize({200.f, 150.f});
	small->setPosition({150.f, 200.f});
	small->setFillColor(sf::Color::Red);
	med->setSize({200.f, 150.f});
	med->setPosition({150.f, 400.f});
	med->setFillColor(sf::Color::Red);
	large->setSize({200.f, 150.f});
	large->setPosition({150.f, 600.f});
	large->setFillColor(sf::Color::Red);

	sf::Font font;
	font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
	sf::Text* text_S = new sf::Text();
	sf::Text* text_M = new sf::Text();
	sf::Text* text_L = new sf::Text();
	
	text_S->setCharacterSize(50);
	text_M->setCharacterSize(50);
	text_L->setCharacterSize(50);
	
	text_S->setString("normal");
	text_M->setString("hard");
	text_L->setString("expert");

	text_S->setFillColor(sf::Color::Black);
	text_M->setFillColor(sf::Color::Black);
	text_L->setFillColor(sf::Color::Black);
	
	text_S->setFont(font);
	text_M->setFont(font);
	text_L->setFont(font);

	sf::FloatRect bounds = text_S->getLocalBounds();
	text_S->setOrigin(bounds.left + bounds.width / 2.0, bounds.top + bounds.height / 2.0);
	bounds = text_M->getLocalBounds();
	text_M->setOrigin(bounds.left + bounds.width / 2.0, bounds.top + bounds.height / 2.0);
	bounds = text_L->getLocalBounds();
	text_L->setOrigin(bounds.left + bounds.width / 2.0, bounds.top + bounds.height / 2.0);

	text_S->setPosition(small->getPosition().x + 100.f, small->getPosition().y + 75.f);
	text_M->setPosition(med->getPosition().x + 100.f, med->getPosition().y + 75.f);
	text_L->setPosition(large->getPosition().x + 100.f, large->getPosition().y + 75.f);

	
	window.clear(sf::Color::White);
	window.draw(*small);
	window.draw(*med);
	window.draw(*large);
	window.draw(*text_S);
	window.draw(*text_M);
	window.draw(*text_L);
	window.display();

	while(window.isOpen())
	{
		sf::Event event;
        	while (window.pollEvent(event))
        	{
        	    if(event.type == sf::Event::Closed)
		    {
			    window.close();
			    exit(1);
		    }
        	}


		if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
		{
			sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			if(box_S->contains(mousePos))
			{
				window.close();
				window.create(sf::VideoMode(900.f, 900.f), "Minesweeper");
				return 81;
			}
			else if(box_M->contains(mousePos))
			{
				window.close();
				window.create(sf::VideoMode(900.f, 900.f), "Minesweeper");
				return 256;
			}
			else if(box_L->contains(mousePos));
			{
				window.close();
				window.create(sf::VideoMode(1500.f, 800.f), "Minesweeper");
				return 480;
			}
		}	
		
	}
return NULL;
}

int check_zones(sf::Vector2f mouse_pos, zones &z, int size)
{
	for(int i = 0; i < size; i++)
	{
		if(z.getZones(i).contains(mouse_pos))
		{
			return i;
		}
	}
return NULL;
}

