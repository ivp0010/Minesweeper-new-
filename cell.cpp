#include "cell.h"

cell::cell(char type, int numAdjBomb)
{
	this->type = type;
	this->numAdjBomb = numAdjBomb;
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

sf::RectangleShape cell::get_block()
{
	return block;
}
