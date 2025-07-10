#include <SFML/Graphics.hpp>
#include <iostream>
#include "board.h"
#include "zones.h"
#include "cellManager.h"
#include <ctime>

void build_board(sf::RenderWindow &window, board &b);
int set_window_size(sf::RenderWindow &window);
int check_zones(sf::Vector2f mouse_pos, zones &z, int size);
void end_game_loss(sf::RenderWindow &window, cellManager &c, board &b);

sf::Color grey((uint8_t)128, (uint8_t)128, (uint8_t)128, (uint8_t)255);

int main()
{

	sf::RenderWindow window(sf::VideoMode(500, 900), "minesweeper", sf::Style::Resize | sf::Style::Close);
	window.clear(grey);
	int size = set_window_size(window);
	srand(time(NULL));
	board b(size);
	zones z(size);
	cellManager c(size);
	window.clear(grey);
	build_board(window, b);
	c.draw_assets(window);
	window.display();
	srand(time(NULL));
	bool first = true;
	bool click = false;

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

			if(first)
			{
				c.init_cells(pos, size);
				first = false;
			}
			
			c.check_cell(pos, 'l');
			click = true;
		}
		else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
		{
		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));			
		int pos = check_zones(mousePos, z, size);
			c.check_cell(pos, 'r');
			click = true;
		}
		
		if(c.get_game_state())
		{
			end_game_loss(window, c, b);
			break;
		}

		if(!(first) && click)
		{
			window.clear(grey);
			c.draw_assets(window);
			build_board(window, b);
			window.display();
			click = false;
		}
	}


return 0;
}

void build_board(sf::RenderWindow &window, board &b)
{
	for(unsigned int i = 0; i < b.get_size(); i++)
	{
		window.draw(*(b.get_board(i)));
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

	
	window.clear(grey);
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

void end_game_loss(sf::RenderWindow &window, cellManager &c, board &b)
{
	for(int i = 0; i < 10; i++)
	{
		window.clear(grey);
		c.draw_assets(window);
		build_board(window, b);
		window.display();
		usleep(100000);
		window.clear(grey);
		c.draw_bomb(window);
		c.draw_assets(window);
		build_board(window, b);
		window.display();
		usleep(100000);
	}

	window.clear(grey);
	c.show_bombs(window);
	c.draw_assets(window);
	build_board(window, b);
	window.display();
	sleep(1);
	
	sf::Font font;
	font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
	sf::Text text;
	sf::FloatRect bound;
	text.setString("3");
	text.setCharacterSize(100);
	text.setFont(font);
	bound = text.getLocalBounds();
	text.setOrigin(bound.left + bound.width / 2.0, bound.top + bound.height / 2.0);
	text.setFillColor(sf::Color::Black);
	sf::Texture texture;
	texture.loadFromFile("/home/zaiah/Minesweeper/sprites/boom.png");
	sf::Sprite sprite;
	sprite.setTexture(texture);
	bound = sprite.getLocalBounds();
	sprite.setOrigin(bound.left + bound.width / 2.0, bound.top + bound.height / 2.0);
	sprite.setScale(4.f, 4.f);

	window.close();
	window.create(sf::VideoMode(400.f, 900.f), "BOOM 3");
	text.setPosition(window.getSize().x / 2.0, window.getSize().y / 2.0);
	window.clear(sf::Color::White);
	window.draw(text);
	window.display();
	sleep(1);
	text.setString("2");
	window.close();
	window.create(sf::VideoMode(400.f, 900.f), "BOOM 2");
	window.clear(sf::Color::White);
	window.draw(text);
	window.display();
	sleep(1);
	window.close();
	text.setString("1");
	window.create(sf::VideoMode(400.f, 900.f), "BOOM 1");
	window.clear(sf::Color::White);
	window.draw(text);
	window.display();
	sleep(1);
	window.close();
	window.create(sf::VideoMode(900.f, 900.f), "BOOOOOOM!!!!!");
	sprite.setPosition(window.getSize().x / 2.0, window.getSize().y / 2.0);
	text.setString("GAME OVER YOU LOSE");
	text.setPosition(window.getSize().x / 2.0, window.getSize().y / 2.0);
	window.clear(sf::Color::White);
	window.draw(sprite);
	window.draw(text);
	window.display();
	sleep(2);

	return;
}



