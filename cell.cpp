#include "cell.h"

cell::cell(char type)
{
	this->type = type;
	numAdjBomb = 0;
	broken = false;
	bombSet = false;
	toDraw = false;
	flagSet = false;
}

void cell::init(int numAdjBomb, int index, int size)
{
	this->numAdjBomb = numAdjBomb;
	this->size = size;
	font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
	std::string temp = std::to_string(numAdjBomb); 
	text.setString(temp);
	text.setCharacterSize(50);
	uint8_t red = 211;
	uint8_t green = 211;
	uint8_t blue = 211;
	uint8_t alpha = 255;
	switch(numAdjBomb)
	{
		case 0: { text.setFillColor(sf::Color(red, green, blue, alpha)); break;}
		case 1: { text.setFillColor(sf::Color::Cyan); break;}
		case 2: { text.setFillColor(sf::Color::Green); break;}
		case 3: { text.setFillColor(sf::Color::Red); break;}
		case 4: { text.setFillColor(sf::Color::Blue); break;}
		case 5: { text.setFillColor(sf::Color::Magenta); break;}
		case 6: { text.setFillColor(sf::Color::Yellow); break;}
		case 7: { text.setFillColor(sf::Color::Cyan); break;}
		case 8: { text.setFillColor(sf::Color::Black); break;}
	}

	text.setFont(font);
	bound = text.getLocalBounds();
	text.setOrigin(bound.left + bound.width / 2.0, bound.top + bound.height / 2.0);	
	int multX, multY;

	switch(size)
	{
		case 81:
		{
			int pos = index / 9;
			multY = pos;
			multX = index - (9 * pos);
			center = {50.f + (100 * multX), 50.f + (100 * multY)};	
			text.setPosition(center);
		break;
		}
		case 256:
		{
			int pos = index / 16;
			multY = pos;
			multX = index - (16 * pos);
			center = {28.125f + (56.25f * multX), 28.125f + (56.25f * multY)};
			text.setPosition(center);
		break;
		}
		case 480:
		{
			int pos = index / 30;
			multY = pos;
			multX = index - (30 * pos);
			center = {25.f + (50.f * multX), 25.f + (50.f * multY)};
			text.setPosition(center);
		break;
		}
	} 
}

		
char cell::get_type()
{
	return type;
}

int cell::get_num_adj_bomb()
{
	return numAdjBomb;
}

bool cell::get_to_draw()
{
	return toDraw;
}

bool cell::get_flag_set()
{
	return flagSet;
}

bool cell::get_broken()
{
	return broken;
}

sf::Text cell::get_num()
{
	return text;
}

sf::RectangleShape cell::get_block()
{
	return block;
}

void cell::start_break()
{
	uint8_t red = 211;
	uint8_t green = 211;
	uint8_t blue = 211;
	uint8_t alpha = 255;
	block.setFillColor(sf::Color(red, green, blue, alpha));
	switch(size)
	{
		case 81:
		{
			block.setSize({100.f, 100.f});
		break;
		}
		case 256:
		{	
			block.setSize({56.25f, 56.25f});
		break;
		}
		case 480:
		{
			block.setSize({50.f, 50.f});
		break;
		}
	}
	bound = block.getLocalBounds();
	block.setOrigin(bound.left + bound.width / 2.0, bound.top + bound.height / 2.00);
	block.setPosition(center);
	broken = true;
}

void cell::set_flag()
{
	if(flagSet)
	{
		flagSet = false;
		toDraw = false;
		return;
	}
	if(broken)
	{
		return;
	}

	texture.loadFromFile("/home/zaiah/Minesweeper/sprites/flag.png");
	sprite.setTexture(texture);
	bound = sprite.getLocalBounds();
	sprite.setOrigin(bound.left + bound.width / 2.0, bound.top + bound.height / 2.0);
	sprite.setPosition(center);
	switch(size)
	{
		case 81: {sprite.setScale(.25, .25); break;}
		case 256: {sprite.setScale(.2, .2); break;}
		case 480: {sprite.setScale(.18, .18); break;}
	}
	flagSet = true;
	toDraw = true;

}

sf::Sprite cell::get_flag()
{
	return sprite;
}

void cell::set_bomb()
{
	texture.loadFromFile("/home/zaiah/Minesweeper/sprites/images.jpg");
	sprite.setTexture(texture);
	bound = sprite.getLocalBounds();
	sprite.setOrigin(bound.left + bound.width / 2.0, bound.top + bound.height / 2.0);
	sprite.setPosition(center);
	switch(size)
	{
		case 81: {sprite.setScale(.25, .25); break;}
		case 256: {sprite.setScale(.2, .2); break;}
		case 480: {sprite.setScale(.18, .18); break;}
	}	
	
	bombSet = true;
	toDraw = true;
}

sf::Sprite cell::get_bomb()
{
	return sprite;
}

void cell::reveal()
{
	if(bombSet){return;}	
	set_bomb();

}
